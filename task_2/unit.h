#ifndef UNIT_H
#define UNIT_H

#include <memory>
#include <string>
#include <vector>

namespace core {
/*!
 * \brief The Unit class это у нас типа abstract base для сущностей,
 * чтобы было дерево вложенности
 */
class Unit {
public:
    using Flags = unsigned int;
public:
    virtual ~Unit() = default;

    virtual void add(const std::shared_ptr<Unit>&, Flags);

    virtual std::string compile(unsigned int level = 0) const = 0;
};

// --------------------------------------------- *** --------------------------------------------- //

/*!
 * \brief The ClassUnit class это abstract base для классов
 */
class ClassUnit : public Unit
{
public:
    enum AccessModifier {
        PUBLIC,
        PROTECTED,
        PRIVATE
    };
    static const std::vector<std::string> ACCESS_MODIFIERS;

public:
    explicit ClassUnit(const std::string& name);

protected:
    using Fields = std::vector<std::shared_ptr<Unit>>;
    std::string m_name;
    std::vector<Fields> m_fields;
};

// --------------------------------------------- *** --------------------------------------------- //

/*!
 * \brief The ClassUnit class это abstract base для методов
 */
class MethodUnit : public Unit
{
public:
    enum Modifier {
        STATIC = 1,
        CONST = 1 << 1,
        VIRTUAL = 1 << 2
    };

public:
    MethodUnit(const std::string& name, const std::string& returnType, Flags flags);

protected:
    std::string m_name;
    std::string m_returnType;

    Flags m_flags;
    std::vector<std::shared_ptr<Unit>> m_body;
};

// --------------------------------------------- *** --------------------------------------------- //

/*!
 * \brief The ClassUnit class это abstract base для вывода в консоль
 */
class PrintOperatorUnit : public core::Unit {
public:
    explicit PrintOperatorUnit(const std::string& text);

protected:
    std::string m_text;
};

// --------------------------------------------- *** --------------------------------------------- //

/*!
 * \brief The UnitFactory class это абстрактный интерфейс для фабрик генерации
 */
class UnitFactory
{
public:
    enum CompileLanguage {
        CPP,
        CSHARP,
        JAVA
    };

    virtual ~UnitFactory() {}

    virtual std::shared_ptr<ClassUnit> createClassUnit() = 0;

    virtual std::shared_ptr<MethodUnit> createMethodUnit() = 0;

    virtual std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit() = 0;
};

// --------------------------------------------- *** --------------------------------------------- //

/*!
 * \brief generateShift -- форматирование, это НЕ часть единицы абстрации, потому свободная функция
 * \param level         -- уровень вложенности
 * \return              -- отступ
 */
std::string generateShift(unsigned int level);

} // namespace core

#endif // UNIT_H
