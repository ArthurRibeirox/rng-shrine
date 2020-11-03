package com.android_serial_port;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.app.Activity;
import android.util.Log;

import com.unity3d.player.UnityPlayer;
import java.util.HashMap;

public class SerialJavaUnityInterface implements ServiceConnection, SerialListener {

    private BluetoothAdapter bluetoothAdapter;
    private HashMap<String, BluetoothDevice> addressToDevice = new HashMap<String, BluetoothDevice>();

    private enum Connected { False, Pending, True }
    private Connected connected = Connected.False;
    private BluetoothDevice connectedDevice;

    private SerialService service;
    private boolean initialStart = true;

    private String receivedBuffer;

    private SerialJavaUnityInterface() {
        if(UnityPlayer.currentActivity.getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH))
            bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        Log.e("SerialJavaUnityInterface", "Starting SerialService");
        UnityPlayer.currentActivity.bindService(new Intent(UnityPlayer.currentActivity, SerialService.class), this, Context.BIND_AUTO_CREATE);
        UnityPlayer.currentActivity.startService(new Intent(UnityPlayer.currentActivity, com.android_serial_port.SerialService.class));

        receivedBuffer = "";
    }

    public void RefreshBluetoothDevices() {
        addressToDevice.clear();

        if(bluetoothAdapter != null) {
            for (BluetoothDevice device : bluetoothAdapter.getBondedDevices()) {
                if (device.getType() != BluetoothDevice.DEVICE_TYPE_LE)
                    BondedDeviceDiscovered(device);
            }
        }
    }

    public void BondedDeviceDiscovered(BluetoothDevice bluetoothDevice)
    {
        UnityPlayer.UnitySendMessage("BluetoothController", "OnBondedDeviceDiscovered", bluetoothDevice.getAddress());
        addressToDevice.put(bluetoothDevice.getAddress(), bluetoothDevice);
    }

    public BluetoothDevice GetDeviceByAddress(String address) {
        return addressToDevice.get(address);
    }

    public void ConnectToDevice(String deviceAddress) {
        try {
            connectedDevice = GetDeviceByAddress(deviceAddress);
            connected = Connected.Pending;

            Log.d("SerialJavaUnityInterface", "Trying to connect to device: " + connectedDevice.getName());

            SerialSocket socket = new SerialSocket(UnityPlayer.currentActivity.getApplicationContext(), connectedDevice);
            service.connect(socket);
        } catch (Exception e) {
            onSerialConnectError(e);
        }
    }

    public void disconnect() {
        connected = Connected.False;
        connectedDevice = null;
        service.disconnect();

        UnityPlayer.UnitySendMessage("BluetoothController", "OnBluetoothDeviceDisconnected", "");
    }

    public void SendData(String str) {
        if(connected != Connected.True) {
            Log.e("SerialJavaUnityInterface", "Trying to SendData while not connected to device");
            return;
        }

        try {
            byte[] data = (str + TextUtil.newline).getBytes();
            service.write(data);
        } catch (Exception e) {
            onSerialIoError(e);
        }
    }

    private void Receive(byte[] data) {
        receivedBuffer = receivedBuffer.concat(new String(data));

        boolean endingInNewLine = receivedBuffer.charAt(receivedBuffer.length() - 1) == TextUtil.newlineChar;
        String[] splitLines = receivedBuffer.split(TextUtil.newline);

        for(int index = 0; index < splitLines.length - 1; index++) {
            ReportDataReceived(splitLines[index]);
        }

        if (endingInNewLine)
        {
            ReportDataReceived(splitLines[splitLines.length - 1]);
            receivedBuffer = "";
        }
        else
        {
            receivedBuffer = splitLines[splitLines.length - 1];
        }
    }

    private void ReportDataReceived(String data)
    {
        UnityPlayer.UnitySendMessage("BluetoothController", "OnDataReceived", data);
    }

    /*
     * ServiceConnection
     */

    @Override
    public void onServiceConnected(ComponentName name, IBinder binder) {
        Log.e("SerialJavaUnityInterface", "onServiceConnected: " + name);
        service = ((SerialService.SerialBinder) binder).getService();
        service.attach(this);
    }

    @Override
    public void onServiceDisconnected(ComponentName name) {
        service = null;
    }

    /*
     * SerialListener
     */

    @Override
    public void onSerialConnect() {
        connected = Connected.True;
        UnityPlayer.UnitySendMessage("BluetoothController", "OnBluetoothDeviceConnected", connectedDevice.getAddress());
    }

    @Override
    public void onSerialConnectError(Exception e) {
        Log.e("SerialJavaUnityInterface", "onSerialConnectError: " + e.getMessage());
        disconnect();
    }

    @Override
    public void onSerialRead(byte[] data) {
        Receive(data);
    }

    @Override
    public void onSerialIoError(Exception e) {
        Log.e("SerialJavaUnityInterface", "onSerialIoError: " + e.getMessage());
        disconnect();
    }

    /*
     * Singleton
     */

    private static SerialJavaUnityInterface singleton;

    public static SerialJavaUnityInterface instance()
    {
        if(singleton == null)
        {
            singleton = new SerialJavaUnityInterface();
        }

        return singleton;
    }
}