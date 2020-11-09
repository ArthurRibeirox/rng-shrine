using UnityEngine;
using UnityEngine.UI;

namespace RNG
{
    public class RandomBackgroundColor : MonoBehaviour
    {
        [SerializeField]
        private Image image;

        private void Start()
        {
            Color.RGBToHSV(image.color, out var h, out var s, out var v);
            image.color = Color.HSVToRGB(Random.value, s, v);

            Destroy(this);
        }
    }
}