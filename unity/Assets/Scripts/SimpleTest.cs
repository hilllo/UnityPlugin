using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using UnityEngine;

namespace CppPlugin {
    public class SimpleTest : MonoBehaviour {

        #region Fields

        [SerializeField]
        private KeyCode _runKey;

        [SerializeField]
        private int[] _array = new int[5];

        #endregion Fields

        private void Update() {
            if (Input.GetKeyDown(_runKey))
                RunTests();
        }

        // Use this for initialization
        public void RunTests() {

            StringBuilder sb = new StringBuilder();
            IntPtr pTest;
            int x;
            double y;
            CppPluginDll.TestStruct testS = new CppPluginDll.TestStruct();

            Debug.Log("===================== Test TestUnity ===================== ");

            CppPluginDll.GetValues(out x, out y);
            Debug.Log("[GetValues] " + x + " " + y);

            Debug.Log("[GetkInt] " + CppPluginDll.GetkInt());
            CppPluginDll.SetkInt((int)Time.realtimeSinceStartup);
            Debug.Log("[SetkInt] " + CppPluginDll.GetkInt());

            sb.Append("This is a very very very very very very very veryvery very very veryvery very very very very very long long long  string.");
            Debug.Log("Initializing - " + sb.ToString() + ", Length: " + sb.Length + ", Capability: " + sb.Capacity);

            CppPluginDll.Sort(this._array, this._array.Length);
            sb.Length = 0;
            for (int i = 0; i < this._array.Length; i++) { sb.Append(this._array[i] + " "); }
            Debug.Log("[Sort] " + sb.ToString() + ", Length: " + sb.Length + ", Capability: " + sb.Capacity);

            sb.Length = 0;
            CppPluginDll.GetString(sb);
            Debug.Log("[GetString] " + sb.ToString() + ", Length: " + sb.Length + ", Capability: " + sb.Capacity);

            sb.Length = 0;
            CppPluginDll.PassString(sb, "This is a string from C#");
            Debug.Log("[PassString] " + sb.ToString() + ", Length: " + sb.Length + ", Capability: " + sb.Capacity);

            sb.Length = 0;
            pTest = CppPluginDll.TestClass_Create("UnityTest");
            CppPluginDll.TestClass_GetName(pTest, sb);
            Debug.Log("[TestClass_GetName] " + sb.ToString() + ", Length: " + sb.Length + ", Capability: " + sb.Capacity);
            CppPluginDll.TestClass_Delete(pTest);
            pTest = IntPtr.Zero;

            CppPluginDll.Debug_SetCallBack(CppPluginDll.OnDebugCallback);
            CppPluginDll.Debug_Use();

            CppPluginDll.TestStruct_GetStruct(ref testS);
            Debug.Log("[TestStruct_GetStruct] " + testS.num + " " + testS.floatNum + " " + Marshal.PtrToStringAnsi(testS.str));

            Debug.Log("===================== End TestUnity ===================== ");
        }
    }
}

