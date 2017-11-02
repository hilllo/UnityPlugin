#pragma once
#include "TestClass.h"
#include <Windows.h>

#define CPP_DLL __declspec(dllexport)

namespace CppPlugin{

	namespace Debug {
		/*
		* Output message in Unity debugger
		* @param message
		* @param type - 0: Log    1: Warning    2: Error
		*/
		void Log(const char* message, int type);
	}	

	extern "C" {
		CPP_DLL int GetkInt();
		CPP_DLL void SetkInt(int i);

		CPP_DLL void GetValues(int& val1, double& val2);

		CPP_DLL void GetString(char* str);
		CPP_DLL void PassString(char* dest, const char* src);
		CPP_DLL void GetLPWSTR(LPWSTR str);
		CPP_DLL void PassLPCWSTR(LPWSTR dest, LPCWSTR src);
		typedef void(*LPCWSTRCallBack)(LPCWSTR str);
		CPP_DLL void GetLPCWSTRfromCallback(LPCWSTRCallBack callback);

		CPP_DLL void Sort(int a[], int length);

		// Object
		CPP_DLL TestClass* TestClass_Create(const char* name);
		CPP_DLL void TestClass_GetName(TestClass* test, char* name);
		CPP_DLL void TestClass_Delete(TestClass* test);

		// Struct
		CPP_DLL void TestStruct_GetStruct(TestStruct* testStruct);
		CPP_DLL void TestStruct_PassStruct(TestCSStruct testStruct);
		typedef void(*GetStructCallBack)(TestCSStruct testStruct);
		CPP_DLL void TestStruct_GetStructbyCallback(GetStructCallBack callback);

		// Callbacks
		typedef void(*DebugCallBack)(const char* message, int type);
		static DebugCallBack gDebugCallBack = nullptr;
		CPP_DLL void Debug_SetCallBack(DebugCallBack callback);
		CPP_DLL void Debug_Use();
	}
}