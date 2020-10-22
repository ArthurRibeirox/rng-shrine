using System;
using System.Collections.Generic;
using UnityEngine;

namespace UnityBluetooth
{
    public class BluetoothController : MonoBehaviour
    {
        public Action<BluetoothDeviceWrapper> BondedDeviceDiscovered;
        public Action<BluetoothDeviceWrapper> BluetoothDeviceConnected;

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
        private void OnBondedDeviceDiscovered(string deviceAddress)
        {
            var javaDevice = javaInterface.Call<AndroidJavaObject>("GetDeviceByAddress", deviceAddress);
            var deviceWrapper = new BluetoothDeviceWrapper(javaDevice, this);
            addressToDevice[deviceAddress] = deviceWrapper;

            BondedDeviceDiscovered?.Invoke(deviceWrapper);
        }

        private void Awake()
        {
            addressToDevice = new Dictionary<string, BluetoothDeviceWrapper>();

            using (AndroidJavaClass javaPlugin = new AndroidJavaClass("android_serial_port.SerialJavaUnityInterface"))
            {
                javaInterface = javaPlugin.CallStatic<AndroidJavaObject>("instance");
                RefreshDevices();
            }
        }
    }
}