#include "TestClass.h"

CppPlugin::TestClass::TestClass(char* name)
	: mName(name) {}

CppPlugin::TestClass::~TestClass() {}

char* CppPlugin::TestClass::GetName() {
	return this->mName;
}