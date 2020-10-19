using UnityEngine;
using System.IO.Ports;

namespace RNG
{
    public class BluetoothConnection
    {
        private const string port = "COM5";
        private const int baudRates = 115200;

        private SerialPort serialPort;

        public void OpenConnection()
        {
            serialPort = new SerialPort(port, baudRates, Parity.None, 8, StopBits.One);

            serialPort.Open();
        }

        public void SendCommand(string cmd)
        {
            serialPort.Write(cmd);
        }

        public BluetoothConnection()
        {
            OpenConnection();
        }
    }
}
