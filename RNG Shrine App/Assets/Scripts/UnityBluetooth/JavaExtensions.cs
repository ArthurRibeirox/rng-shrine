using System;
using UnityEngine;

namespace UnityBluetooth
{
    public static class JavaExtensions
    {
        public static bool IsNull(this AndroidJavaObject androidJavaObject)
        {
            return androidJavaObject == null || androidJavaObject.GetRawObject() == IntPtr.Zero;
        }

        public static bool IsNull(this AndroidJavaClass androidJavaClass)
        {
            return androidJavaClass == null || androidJavaClass.GetRawClass() == IntPtr.Zero;
        }
    }
}