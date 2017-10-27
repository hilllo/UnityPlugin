#include "cppplugin.h"

#include <algorithm>
#include <string>
#include <sstream>

namespace {
	int kInt = 666;
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


// Callbacks ==========================
CPP_DLL void CppPlugin::Debug_SetCallBack(DebugCallBack callback) {
	CppPlugin::gDebugCallBack = callback;
}

CPP_DLL void CppPlugin::Debug_Use() {
	Debug::Log("Log from C++", 0);
	Debug::Log("Warning from C++", 1);
	Debug::Log("Error from C++", 2);
}
