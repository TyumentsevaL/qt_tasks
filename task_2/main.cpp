#include <iostream>

#include "cpp_units.h"

using namespace core;

std::string generateProgram() {
    CppClassUnit myClass("MyClass");

    myClass.add(std::make_shared<CppMethodUnit>("testFunc1", "void", 0),
                ClassUnit::PUBLIC);
    myClass.add(std::make_shared<CppMethodUnit>("testFunc2", "void", MethodUnit::STATIC),
                ClassUnit::PRIVATE);
    myClass.add(std::make_shared<CppMethodUnit>("testFunc3", "void", MethodUnit::VIRTUAL | MethodUnit::CONST),
                ClassUnit::PUBLIC);

    auto method = std::make_shared<CppMethodUnit>("testFunc4", "void", MethodUnit::STATIC);
    method->add(std::make_shared<CppPrintOperatorUnit>(R"(Hello, world!\n)" ));
    myClass.add(method, ClassUnit::PROTECTED);

    return myClass.compile();
}

int main(int argc, char *argv[])
{
    std::cout << generateProgram() << std::endl;
    return 0;
}
