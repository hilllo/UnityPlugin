#include "cppplugin.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h>

namespace {
	int kInt = 666;
	std::wstring kWStr = L"This is a kstring from wstring in C++";
	LPCWSTR kLPCWSTR = L"This is a kLPCWSTR from LPCWSTR in C++";
}

void CppPlugin::Debug::Log(const char* message, int type) {
	std::stringstream ss;
	ss << "[CppPlugin] " << message;

	const std::string tmp = ss.str();
	const char* tmsg = tmp.c_str();
	if (CppPlugin::gDebugCallBack != nullptr)
		CppPlugin::gDebugCallBack(tmsg, type);
}

CPP_DLL void CppPlugin::GetValues(int& val1, double& val2) {
	val1 = 123;
	val2 = 22.972;
}

CPP_DLL void CppPlugin::GetString(char* str) {
	std::string s = "This is a string from a std::string in C++";
	memcpy(str, s.data(), s.size());
	str[(int)s.size()] = 0;
}

CPP_DLL void CppPlugin::PassString(char* dest, const char* src) {
	std::string s(src);
	s.append(", now pass it back from C++");
	memcpy(dest, s.data(), s.size());
	dest[(int)s.size()] = 0;
}

CPP_DLL void CppPlugin::GetLPWSTR(LPWSTR str) {
	wmemcpy((wchar_t*)str, kWStr.data(), kWStr.size());
	str[(int)kWStr.size()] = 0;
}

CPP_DLL void CppPlugin::PassLPCWSTR(LPWSTR dest, LPCWSTR src) {
	std::string stds = CW2A(src);
	//Debug::Log(stds.c_str(), 0);

	wmemcpy((wchar_t*)dest, (wchar_t*)src, wcslen(src));
	dest[(int)wcslen(src)] = 0;
}

CPP_DLL void CppPlugin::GetLPCWSTRfromCallback(LPCWSTRCallBack callback) {
	callback(kLPCWSTR);
}

CPP_DLL int CppPlugin::GetkInt() {
	return kInt;
}

CPP_DLL void CppPlugin::SetkInt(int i) {
	kInt = i;
}

CPP_DLL void CppPlugin::Sort(int a[], int length) {
	std::sort(a, a + length);
}

// Object ==========================
CPP_DLL CppPlugin::TestClass* CppPlugin::TestClass_Create(const char* name) {
	return new TestClass((char*)name);
}

CPP_DLL void CppPlugin::TestClass_GetName(CppPlugin::TestClass* pTest, char* name) {
	std::string s(pTest->GetName());
	memcpy(name, s.data(), s.size());
	name[(int)s.size()] = 0;
}

CPP_DLL void CppPlugin::TestClass_Delete(CppPlugin::TestClass* pTest) {
	delete pTest;
}

// Struct ==========================
CPP_DLL void CppPlugin::TestStruct_GetStruct(TestStruct* testStruct) {
	testStruct->num = 42;
	testStruct->floatNum = 42.42f;

	std::string s = "String in struct";
	testStruct->str = s.c_str();
	Debug::Log(testStruct->str, 0);
}

CPP_DLL void CppPlugin::TestStruct_PassStruct(TestCSStruct testStruct) {
	Debug::Log("Get structure form c#", 0);
	std::wstringstream wss;
	wss << testStruct.str1 << " " << testStruct.str2 << " " << testStruct.str3;
	if (testStruct.i == (unsigned)0)
		wss << " false";
	else if (testStruct.i == (unsigned)1)
		wss << " true";
	std::wstring ws = wss.str();
	std::string s(ws.begin(), ws.end());
	Debug::Log(s.c_str(), 0);
}

CPP_DLL void CppPlugin::TestStruct_GetStructbyCallback(GetStructCallBack callback) {
	Debug::Log("Get structure form C++", 0);
	TestCSStruct testStruct;
	testStruct.str1 = L"I set this struct";
	testStruct.str2 = L"in";
	testStruct.str3 = L"the cpp dll!";
	testStruct.i = (unsigned)1;

	std::wstringstream wss;
	wss << testStruct.str1 << " " << testStruct.str2 << " " << testStruct.str3;
	if (testStruct.i == (unsigned)0)
		wss << " false";
	else if (testStruct.i == (unsigned)1)
		wss << " true";
	std::wstring ws = wss.str();
	std::string s(ws.begin(), ws.end());
	Debug::Log(s.c_str(), 0);

	callback(testStruct);
}

// Callbacks ==========================
CPP_DLL void CppPlugin::Debug_SetCallBack(DebugCallBack callback) {
	CppPlugin::gDebugCallBack = callback;
}

CPP_DLL void CppPlugin::Debug_Use() {
	Debug::Log("Log from C++", 0);
	Debug::Log("Warning from C++", 1);
	Debug::Log("Error from C++", 2);
}
