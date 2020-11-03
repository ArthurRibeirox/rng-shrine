using RNG.Enums;
using UnityEngine;
using UnityEngine.UI;

namespace RNG
{
    public class ChakraConfigGraphics : MonoBehaviour
    {
        [SerializeField]
        private Chakra chakra;

        [SerializeField]
        private Image image;

        public void SetRandomColor()
        {
            var color = ChakraConfigLib.SetRandomColor(chakra);
            image.color = color;
        }
    }
}