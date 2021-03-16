#include <iostream>
#include <unordered_map>

#include "cpp_units.h"
#include "csharp_units.h"
#include "java_units.h"

std::string generateProgram(std::shared_ptr<core::UnitFactory> &factory)
{
    using namespace core;
    std::shared_ptr<ClassUnit> myClass = factory->createClassUnit("MyClass", ClassUnit::PRIVATE_PROTECTED);

    myClass->add(factory->createMethodUnit("testFunc1", "void", MethodUnit::SEALED)
                 , ClassUnit::PUBLIC);
    myClass->add(factory->createMethodUnit("testFunc2", "void", MethodUnit::STATIC | MethodUnit::UNSAFE)
                 , ClassUnit::PRIVATE);
    myClass->add(factory->createMethodUnit("testFunc3", "void", MethodUnit::VIRTUAL | MethodUnit::ABSTRACT | MethodUnit::CONST)
                 , ClassUnit::PUBLIC);

    auto method = factory->createMethodUnit("testFunc4", "void", MethodUnit::STATIC);
    method->add(factory->createPrintOperatorUnit(R"(Hello, world!\n)" ));
    myClass->add(method, ClassUnit::PROTECTED);

    return myClass->compile();
}

int main(int argc, char *argv[])
{
    // не нужен, я знаю, это демонстрация
//     UnitFactory::CompileLanguage language = UnitFactory::CPP;

    // демонстрация, как можно enum использовать
//    if (option > 0 && option < 4) { // можно было в int хранить, да
//        language = static_cast<UnitFactory::CompileLanguage>(option);
//    } else {
//        std::cerr << "Language options are: 1 -- cpp, 2 -- csharp, 3 -- java" << std::endl;
//        return -1;
//    }

    // -----------------------------------------------

    int option = 1; //cpp
    if (argc == 2) {
        option = std::atoi(argv[1]);
        if (/*option <= 0 || option >= 4*/ option != 1) {
            std::cerr << "Language options are: 1 -- cpp, 2 -- csharp, 3 -- java" << std::endl;
            return -1;
        }
    }

    std::unordered_map<int, std::shared_ptr<core::UnitFactory>> factories = {
        {1, std::make_shared<cpp::CppUnitFactory>()},
        {2, std::make_shared<csharp::CsharpUnitFactory>()},
        {3, std::make_shared<java::JavaUnitFactory>()}
    };

    std::cout << generateProgram(factories[option]) << std::endl;
    return 0;
}
