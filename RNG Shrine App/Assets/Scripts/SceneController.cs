using ServiceLocator;
using UnityBluetooth;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace RNG
{
    public class SceneController
    {
        public SceneController()
        {
            GameServices.GetService<BluetoothController>().BluetoothDeviceConnected += OnBluetoothDeviceConnected;
            GameServices.GetService<BluetoothController>().BluetoothDeviceDisconnected += OnBluetoothDeviceDisconnected;
        }

        private void OnBluetoothDeviceConnected(BluetoothDeviceWrapper deviceWrapper)
        {
            Debug.Log($"Bluetooth Device Connected: {deviceWrapper}");
            SceneManager.LoadScene("MainScene");
        }

        private void OnBluetoothDeviceDisconnected()
        {
            Debug.Log($"Bluetooth Device OnBluetoothDeviceDisconnected");
            SceneManager.LoadScene("BluetoothConnectionScene");
        }

        ~SceneController()
        {
            GameServices.GetService<BluetoothController>().BluetoothDeviceConnected -= OnBluetoothDeviceConnected;
            GameServices.GetService<BluetoothController>().BluetoothDeviceDisconnected -= OnBluetoothDeviceDisconnected;
        }
    }
}