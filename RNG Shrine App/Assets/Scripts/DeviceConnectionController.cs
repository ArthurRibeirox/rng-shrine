using System;
using System.Collections.Generic;
using ServiceLocator;
using UnityBluetooth;
using UnityEngine;

namespace RNG
{
    public class DeviceConnectionController : MonoBehaviour
    {
        [SerializeField]
        private BluetoothDeviceEntryGraphics bluetoothDeviceEntryPrefab;
        [SerializeField]
        private RectTransform entryButtonsParent;

        private BluetoothController bluetoothController;

        private List<BluetoothDeviceEntryGraphics> deviceEntries = new List<BluetoothDeviceEntryGraphics>();

        private void OnBondedDeviceDiscovered(BluetoothDeviceWrapper deviceWrapper)
        {
            var newEntry = Instantiate(bluetoothDeviceEntryPrefab, entryButtonsParent);
            newEntry.Setup(deviceWrapper);
            deviceEntries.Add(newEntry);
        }

        private void Start()
        {
            bluetoothController = GameServices.GetService<BluetoothController>();
            bluetoothController.BondedDeviceDiscovered += OnBondedDeviceDiscovered;
        }

        private void OnDestroy()
        {
            bluetoothController.BondedDeviceDiscovered -= OnBondedDeviceDiscovered;
        }
    }
}