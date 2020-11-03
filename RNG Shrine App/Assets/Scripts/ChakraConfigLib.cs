using RNG.Enums;
using ServiceLocator;
using UnityBluetooth;
using UnityEngine;

namespace RNG
{
    public static class ChakraConfigLib
    {
        private static BluetoothController Controller => GameServices.GetService<BluetoothController>();

        public static Color SetRandomColor(Chakra chakra)
        {
            var color = new Color(Random.value, Random.value, Random.value);
            SendCommand(ChakraMode.StaticColor, chakra, ColorToCommand(color));

            return color;
        }

        private static string ColorToCommand(Color color)
        {
            return $"{color.r*255:F0},{color.g*255:F0},{color.b*255:F0}";
        }

        private static void SendCommand(ChakraMode mode, Chakra chakra, string options)
        {
            var command = $"{(int) mode}|{(int) chakra}|{options}";
            Debug.Log(command);
            Controller.SendData(command);
        }
    }
}