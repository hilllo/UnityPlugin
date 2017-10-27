#pragma once

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
}