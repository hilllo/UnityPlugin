using AOT;
using System.Runtime.InteropServices;
using System.Text;
using System;

namespace CppPlugin {
    public class CppPluginDll {

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct TestStruct {
            public int num;
            public float floatNum;
            public IntPtr str;
        }

        public struct TestCSStruct {
            [MarshalAs(UnmanagedType.LPWStr)]
            public string str1;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string str2;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string str3;
            [MarshalAs(UnmanagedType.SysUInt)]
            public uint i;
        }

        #region Simple Func

        [DllImport("cppplugin")]
        public static extern int GetkInt();

        [DllImport("cppplugin")]
        public static extern void SetkInt(int i);

        [DllImport("cppplugin")]
        public static extern void GetValues(out int val1, out double val2);


        [DllImport("cppplugin")]
        public static extern void GetString(StringBuilder sb);

        [DllImport("cppplugin")]
        public static extern void PassString(StringBuilder dest, string src);

        [DllImport("cppplugin", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern void GetLPWSTR([MarshalAsAttribute(UnmanagedType.LPWStr)] StringBuilder sb);

        [DllImport("cppplugin", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern void PassLPCWSTR([MarshalAsAttribute(UnmanagedType.LPWStr)] StringBuilder sb, [MarshalAsAttribute(UnmanagedType.LPWStr)] string str);

        public delegate void LPCWSTRCallBack([MarshalAsAttribute(UnmanagedType.LPWStr)] string str);
        public static void OnLPCWSTRCallBack([MarshalAsAttribute(UnmanagedType.LPWStr)] string str) {
            UnityEngine.Debug.Log("[OnLPCWSTRCallBack] Get string from callback:" + str);
        }
        [DllImport("cppplugin", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern void GetLPCWSTRfromCallback(LPCWSTRCallBack cb);

        [DllImport("cppplugin")]
        public static extern void Sort(int[] a, int length);

        #endregion Simple Func

        #region Object Func

        [DllImport("cppplugin")]
        public static extern IntPtr TestClass_Create(string name);

        [DllImport("cppplugin")]
        public static extern void TestClass_GetName(IntPtr pTestObject, StringBuilder sb);

        [DllImport("cppplugin")]
        public static extern void TestClass_Delete(IntPtr pTestObject);

        #endregion Object Func

        #region Struct Func
        [DllImport("cppplugin")]
        public static extern void TestStruct_GetStruct([MarshalAs(UnmanagedType.Struct)] ref TestStruct testS);
        [DllImport("cppplugin")]
        public static extern void TestStruct_PassStruct([MarshalAs(UnmanagedType.Struct)] TestCSStruct testStruct);


        public delegate void GetStructCallBack([MarshalAs(UnmanagedType.Struct)] TestCSStruct testStruct);
        [MonoPInvokeCallback(typeof(GetStructCallBack))]
        public static void OnGetStructCallBack([MarshalAs(UnmanagedType.Struct)] TestCSStruct testStruct) {
            UnityEngine.Debug.Log(testStruct.str1 + " " + testStruct.str2 + " " + testStruct.str3 + " " + testStruct.i);
        }
        [DllImport("cppplugin", CallingConvention = CallingConvention.Cdecl)]
        public static extern void TestStruct_GetStructbyCallback(GetStructCallBack cb);

        #endregion Struct Func

        #region Callback Func

        public delegate void DebugCallback(IntPtr request, int type);
        [MonoPInvokeCallback(typeof(DebugCallback))]
        public static void OnDebugCallback(IntPtr request, int type) {
            string debug_string = Marshal.PtrToStringAnsi(request);
            switch (type) {
                case 0:
                    UnityEngine.Debug.Log(debug_string);
                    break;
                case 1:
                    UnityEngine.Debug.LogWarning(debug_string);
                    break;
                case 2:
                    UnityEngine.Debug.LogError(debug_string);
                    break;
                default:
                    UnityEngine.Debug.LogWarning(debug_string + "(Log type define error)");
                    break;
            }
        }

        [DllImport("cppplugin", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Debug_SetCallBack(DebugCallback cb);

        [DllImport("cppplugin", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Debug_Use();

        #endregion Callback Func

    }
}

