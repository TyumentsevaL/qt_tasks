#ifndef CSHARP_UNITS_H
#define CSHARP_UNITS_H

#include "core_units.h"

namespace csharp {

class CsharpClassUnit : public core::ClassUnit
{
public:
    using ClassUnit::ClassUnit;

    void add(const std::shared_ptr<Unit>& unit, Flags flags) override;

    std::string compile(unsigned int level = 0) const override;
};

// --------------------------------------------- *** --------------------------------------------- //

/*!
 * \brief The CsharpMethodUnit class это класс для генерации методов.
 * Я попыталась обработать все модификаторы, но вряд ли это получилось корректно,
 * там очень много сочетаний, если их гуглить, я не понимаю C# так хорошо ((
 */
class CsharpMethodUnit : public core::MethodUnit
{
public:
    using MethodUnit::MethodUnit;
    std::string compile(unsigned int level = 0) const override;
};

// --------------------------------------------- *** --------------------------------------------- //

class CsharpPrintOperatorUnit : public core::PrintOperatorUnit
{
public:
    using PrintOperatorUnit::PrintOperatorUnit;
    std::string compile(unsigned int level = 0) const override;
};

// --------------------------------------------- *** --------------------------------------------- //

class CsharpUnitFactory : public core::UnitFactory
{
public:
    std::shared_ptr<core::ClassUnit> createClassUnit(const std::string& name, core::Unit::Flags flags) const override;

    std::shared_ptr<core::MethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, core::Unit::Flags flags) const override;

    std::shared_ptr<core::PrintOperatorUnit> createPrintOperatorUnit(const std::string& text) const override;
};

} // namespace csharp

#endif // CSHARP_UNITS_H
