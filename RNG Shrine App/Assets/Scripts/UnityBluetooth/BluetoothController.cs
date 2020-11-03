using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace UnityBluetooth
{
    public class BluetoothController : MonoBehaviour
    {
        public Action<BluetoothDeviceWrapper> BondedDeviceDiscovered;
        public Action<BluetoothDeviceWrapper> BluetoothDeviceConnected;
        public Action BluetoothDeviceDisconnected;

        public BluetoothDeviceWrapper connectedDevice;

        private Dictionary<string, BluetoothDeviceWrapper> addressToDevice;
        private AndroidJavaObject javaInterface;

        public void RefreshDevices()
        {
            javaInterface.Call("RefreshBluetoothDevices");
        }

        public void ConnectToDevice(string deviceAddress)
        {
            javaInterface.Call("ConnectToDevice", deviceAddress);
        }

        public void SendData(string data)
        {
            javaInterface.Call("SendData", data);
        }

        // Java callback
        private void OnBluetoothDeviceConnected(string deviceAddress)
        {
            Debug.Assert(connectedDevice == null || connectedDevice.Address == deviceAddress, "Connecting to a device whilst connected to another.");

            connectedDevice = addressToDevice[deviceAddress];
            connectedDevice.IsConnected = true;

            Debug.Log($"Connected to device: {connectedDevice}");

            BluetoothDeviceConnected?.Invoke(connectedDevice);
        }

        // Java callback
        private void OnBluetoothDeviceDisconnected(string _)
        {
            Debug.Log($"Disconnected from device: {connectedDevice}");

            if (connectedDevice != null)
                connectedDevice.IsConnected = false;

            connectedDevice = null;

            BluetoothDeviceDisconnected?.Invoke();
        }

        // Java callback
        private void OnBondedDeviceDiscovered(string deviceAddress)
        {
            var javaDevice = javaInterface.Call<AndroidJavaObject>("GetDeviceByAddress", deviceAddress);
            var deviceWrapper = new BluetoothDeviceWrapper(javaDevice, this);
            addressToDevice[deviceAddress] = deviceWrapper;

            BondedDeviceDiscovered?.Invoke(deviceWrapper);
        }

        // Java callback
        private void OnDataReceived(string data)
        {
            Debug.Log($"OnDataReceived: {data}");
        }

        private void InitJavaInterface()
        {
            using (AndroidJavaClass javaPlugin = new AndroidJavaClass("com.android_serial_port.SerialJavaUnityInterface"))
            {
                javaInterface = javaPlugin.CallStatic<AndroidJavaObject>("instance");
                RefreshDevices();
            }
        }

        private void Awake()
        {
            addressToDevice = new Dictionary<string, BluetoothDeviceWrapper>();
            InitJavaInterface();
        }
    }
}