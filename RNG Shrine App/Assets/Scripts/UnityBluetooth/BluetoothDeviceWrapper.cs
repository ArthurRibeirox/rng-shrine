using System;
using UnityEngine;

namespace UnityBluetooth
{
    public sealed class BluetoothDeviceWrapper
    {
        public string Name { get; }
        public string Address { get; }
        public BluetoothBondState BondState => (BluetoothBondState) bluetoothDeviceJavaObject.Call<int>("getBondState");
        public BluetoothDeviceType DeviceType { get; }
        public BluetoothDeviceSubType DeviceSubType { get; }
        public bool IsConnectable { get; }

        public bool IsConnected;

        private readonly AndroidJavaObject bluetoothDeviceJavaObject;
        private readonly BluetoothController bluetoothController;

        public BluetoothDeviceWrapper(AndroidJavaObject bluetoothDeviceJavaObject, BluetoothController bluetoothController)
        {
            try
            {
                if (bluetoothDeviceJavaObject.IsNull())
                    throw new ArgumentNullException(nameof(bluetoothDeviceJavaObject));

                this.bluetoothDeviceJavaObject = bluetoothDeviceJavaObject;
                this.bluetoothController = bluetoothController;

                Name = bluetoothDeviceJavaObject.Call<string>("getName");
                Address = bluetoothDeviceJavaObject.Call<string>("getAddress");

                AndroidJavaObject deviceClassJavaObject =
                    bluetoothDeviceJavaObject.Call<AndroidJavaObject>("getBluetoothClass");
                int deviceClassFull = deviceClassJavaObject.Call<int>("getDeviceClass");

                DeviceSubType = (BluetoothDeviceSubType) deviceClassFull;
                DeviceType = BluetoothHelpers.GetDeviceType(DeviceSubType);
                IsConnectable = BluetoothHelpers.IsProbablyDataCapable(DeviceType);

                Name = string.IsNullOrEmpty(Name) ? Address : Name.Trim();

                Debug.Log($"New BluetoothDevice: {this}");
            }
            catch
            {
                Debug.LogError("Exception while converting BluetoothDevice");
                throw;
            }
        }

        public void Connect()
        {
            bluetoothController.ConnectToDevice(Address);
        }

        public override string ToString()
        {
            return $"{Name} [{Address}], class: {DeviceSubType}, connectable: {IsConnectable}";
        }

        #region Comparison methods and operators

        private bool Equals(BluetoothDeviceWrapper other)
        {
            return string.Equals(Address, other.Address, StringComparison.InvariantCultureIgnoreCase);
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;

            return obj is BluetoothDeviceWrapper wrapper && Equals(wrapper);
        }

        public override int GetHashCode()
        {
            return Address != null ? Address.GetHashCode() : 0;
        }

        public static bool operator ==(BluetoothDeviceWrapper left, BluetoothDeviceWrapper right)
        {
            return Equals(left, right);
        }

        public static bool operator !=(BluetoothDeviceWrapper left, BluetoothDeviceWrapper right)
        {
            return !Equals(left, right);
        }

        #endregion Comparison methods and operators
    }
}