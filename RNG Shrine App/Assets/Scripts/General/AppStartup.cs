using GameSignals;
using RNG;
using ServiceLocator;
using UnityEngine;
using UnityEngine.Android;

namespace General
{
    public class AppStartup : MonoBehaviour
    {
        [SerializeField]
        private UnitySerialPort unitySerialPort;

        private void Awake()
        {
            GameServices.RegisterService(unitySerialPort);
        }
    }
}