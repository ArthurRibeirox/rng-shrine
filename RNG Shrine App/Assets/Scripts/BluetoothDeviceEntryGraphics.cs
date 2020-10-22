using TMPro;
using UnityBluetooth;
using UnityEngine;
using UnityEngine.UI;

namespace RNG
{
    public class BluetoothDeviceEntryGraphics : MonoBehaviour
    {
        [SerializeField]
        private TMP_Text deviceName;
        [SerializeField]
        private TMP_Text deviceAddress;
        [SerializeField]
        private Button button;

        private BluetoothDeviceWrapper deviceWrapper;

        public void Setup(BluetoothDeviceWrapper bluetoothDeviceWrapper)
        {
            deviceWrapper = bluetoothDeviceWrapper;

            deviceName.text = deviceWrapper.Name;
            deviceAddress.text = deviceWrapper.Address;
        }

        private void OnClick()
        {
            deviceWrapper.Connect();
        }

        private void Awake()
        {
            button.onClick.AddListener(OnClick);
        }
    }
}