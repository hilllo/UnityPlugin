#pragma once
#include <windows.h>

namespace CppPlugin {
	class TestClass {
	public:
		TestClass();
		TestClass(char* name);
		~TestClass();

		char* GetName();

	private:
		char* mName;
	};

	struct TestStruct {
	public:
		int num;
		float floatNum;
		const char* str;
	};

	struct TestCSStruct {
	public:
		LPCWSTR str1;
		LPCWSTR str2;
		LPCWSTR str3;
		unsigned i;
	};
}