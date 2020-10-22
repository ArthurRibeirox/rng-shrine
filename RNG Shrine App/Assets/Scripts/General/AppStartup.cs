using ServiceLocator;
using UnityBluetooth;
using UnityEngine;

namespace General
{
    public class AppStartup : MonoBehaviour
    {
        [SerializeField]
        private BluetoothController bluetoothController;

        private void Awake()
        {
            GameServices.RegisterService(bluetoothController);

            DontDestroyOnLoad(gameObject);
            Destroy(this);
        }
    }
}