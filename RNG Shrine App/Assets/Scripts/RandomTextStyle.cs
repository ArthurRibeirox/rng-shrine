using System.Collections.Generic;
using TMPro;
using UnityEngine;

namespace RNG
{
    public class RandomTextStyle : MonoBehaviour
    {
        [SerializeField]
        private TMP_Text text;

        [SerializeField]
        private List<TMP_FontAsset> possibleFonts;
        [SerializeField]
        private List<Vector4> margins;

        [SerializeField]
        private int forceIndex = -1;

        private void Start()
        {
            var index = forceIndex != -1 ? forceIndex : Random.Range(0, possibleFonts.Count);
            text.font = possibleFonts[index];
            text.margin = margins[index];

            Destroy(this);
        }
    }
}
