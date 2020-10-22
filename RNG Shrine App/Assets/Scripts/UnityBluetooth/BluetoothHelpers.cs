namespace UnityBluetooth
{
    public class BluetoothHelpers
    {
        public static BluetoothDeviceType GetDeviceType(BluetoothDeviceSubType subType)
        {
            return (BluetoothDeviceType) ((int) subType & 0x1F00);
        }

        public static bool IsProbablyDataCapable(BluetoothDeviceType deviceClass) {
            switch (deviceClass) {
                case BluetoothDeviceType.Computer:
                case BluetoothDeviceType.Phone:
                    return true;
                default:
                    return false;
            }
        }
    }
}