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
class Unit
{
public:
    using Flags = unsigned int;
public:
    virtual ~Unit() = default;

    virtual void add(const std::shared_ptr<Unit>&, Flags = 0);

    virtual std::string compile(unsigned int level = 0) const = 0;
};

// --------------------------------------------- *** --------------------------------------------- //

/*!
 * \brief The ClassUnit class это abstract base для классов
 * Пришлось подправить всякое из-за managed языков, там у класса тоже модификаторы
 */
class ClassUnit : public Unit
{
public:
    enum AccessModifier {
        PUBLIC,
        PROTECTED,
        PRIVATE,
        INTERNAL,
        PROTECTED_INTERNAL,
        PRIVATE_PROTECTED,
        FINAL,
        ABSTRACT
    };
    static const std::vector<std::string> ACCESS_MODIFIERS;

public:
    explicit ClassUnit(const std::string& name, core::Unit::Flags flags = 0);

protected:
    using Fields = std::vector<std::shared_ptr<Unit>>;
    Flags m_flag;
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
        STATIC			= 1,
        CONST			= 1 << 1,
        VIRTUAL			= 1 << 2,
        ABSTRACT		= 1 << 3,
        ASYNC			= 1 << 4,
        UNSAFE			= 1 << 5,
        SEALED			= 1 << 6,
        FINAL			= SEALED,
        SYNCHRONIZED	= 1 << 8
    };

public:
    MethodUnit(const std::string& name, const std::string& returnType, Flags flags);

    void add(const std::shared_ptr<Unit>& unit, Flags = 0) override;

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
class PrintOperatorUnit : public core::Unit
{
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
    /*!
     * \brief The CompileLanguage enum не используется,
     * просто может пригодиться для switch
     */
    enum CompileLanguage {
        CPP = 1,
        CSHARP,
        JAVA
    };

    virtual ~UnitFactory() {}

    /*!
     * \brief createClassUnit -- создаёт сущность для "компиляции" класса. Не факт, что все corner-case
     * тонкости учтены в потомках, но абстрактная фабрика демонстрируется.
     * \param name            -- имя класса, тут понятно
     * \param flags           -- в C# и Java имеют модификаторы доступа к классу, потому тут флаг. C++ пусть игнорирует
     * \return                -- полиморфный указатель на юнит класса какого-то языка вернётся
     */
    virtual std::shared_ptr<ClassUnit> createClassUnit(const std::string& name, Unit::Flags flags = 0) const = 0;

    virtual std::shared_ptr<MethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Unit::Flags flags) const = 0;

    virtual std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(const std::string& text) const = 0;
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
