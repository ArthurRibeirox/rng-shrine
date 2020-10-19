using ServiceLocator;
using UnityEngine;

namespace RNG
{
    public class LightCommand : MonoBehaviour
    {
        private UnitySerialPort unitySerialPort;

        private BluetoothConnection bluetoothConnection;

        private void SendRGBCommand()
        {
            var message = $"1|{Random.Range(0, 256)},{Random.Range(0, 256)},{Random.Range(0, 256)}";
            // bluetoothConnection.SendCommand(message);
            unitySerialPort.SendSerialData(message);
        }

        private void Update()
        {
            if (Input.touches.Length > 0 && Input.touches[0].phase == TouchPhase.Began)
            {
                SendRGBCommand();
            }
        }

        private void Awake()
        {
            // bluetoothConnection = GameServices.GetService<BluetoothConnection>();
            unitySerialPort = GameServices.GetService<UnitySerialPort>();
        }
    }
}