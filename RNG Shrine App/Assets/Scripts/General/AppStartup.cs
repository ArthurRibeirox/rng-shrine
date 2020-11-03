using RNG;
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
            GameServices.RegisterService(new SceneController());

            DontDestroyOnLoad(gameObject);
            Destroy(this);
        }
    }
}