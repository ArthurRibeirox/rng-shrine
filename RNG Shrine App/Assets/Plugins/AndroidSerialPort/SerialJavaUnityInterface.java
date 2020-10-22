package android_serial_port;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.app.Activity;

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

    private SerialJavaUnityInterface() {
        if(UnityPlayer.currentActivity.getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH))
            bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        // prevents service destroy on unbind from recreated activity caused by orientation change
        UnityPlayer.currentActivity.startService(new Intent(UnityPlayer.currentActivity, SerialService.class));
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
        UnityPlayer.UnitySendMessage("SerialController", "OnBondedDeviceDiscovered", bluetoothDevice.getAddress());
        addressToDevice.put(bluetoothDevice.getAddress(), bluetoothDevice);
    }

    public BluetoothDevice GetDeviceByAddress(String address) {
        return addressToDevice.get(address);
    }

    public void ConnectToDevice(String deviceAddress) {
        try {
            connectedDevice = GetDeviceByAddress(deviceAddress);
            connected = Connected.Pending;

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
    }

    /*
     * ServiceConnection
     */

    @Override
    public void onServiceConnected(ComponentName name, IBinder binder) {
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
        UnityPlayer.UnitySendMessage("SerialController", "OnBluetoothDeviceConnected", connectedDevice.getAddress());
    }

    @Override
    public void onSerialConnectError(Exception e) {
        System.out.print("connection failed: " + e.getMessage());
        disconnect();
    }

    @Override
    public void onSerialRead(byte[] data) {
        // receive(data);
    }

    @Override
    public void onSerialIoError(Exception e) {
        System.out.print("connection lost: " + e.getMessage());
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