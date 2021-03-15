#ifndef UNITFACTORY_H
#define UNITFACTORY_H

#include <memory>

class ClassUnit;
class MethodUnit;
class PrintOperatorUnit;

/*!
 * \brief The UnitFactory class это абстрактный интерфейс для фабрик генерации
 */
class UnitFactory
{
public:
    enum CompileLanguage
    {
        CPP,
        CSHARP,
        JAVA
    };

    virtual ~UnitFactory() {}

    virtual std::shared_ptr<ClassUnit> createClassUnit() = 0;

    virtual std::shared_ptr<MethodUnit> createMethodUnit() = 0;

    virtual std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit() = 0;
};

#endif // UNITFACTORY_H
