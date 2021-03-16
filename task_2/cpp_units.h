#ifndef CPP_UNITS_H
#define CPP_UNITS_H

#include "core_units.h"

namespace cpp {

class CppClassUnit : public core::ClassUnit
{
public:
    using ClassUnit::ClassUnit;

    void add(const std::shared_ptr<Unit>& unit, Flags flags) override;

    std::string compile(unsigned int level = 0) const override;
};

// --------------------------------------------- *** --------------------------------------------- //

class CppMethodUnit : public core::MethodUnit
{
public:
    using MethodUnit::MethodUnit;
    std::string compile(unsigned int level = 0) const override;
};

// --------------------------------------------- *** --------------------------------------------- //

class CppPrintOperatorUnit : public core::PrintOperatorUnit
{
public:
    using PrintOperatorUnit::PrintOperatorUnit;
    std::string compile(unsigned int level = 0) const override;
};

// --------------------------------------------- *** --------------------------------------------- //

class CppUnitFactory : public core::UnitFactory
{
public:
    std::shared_ptr<core::ClassUnit> createClassUnit(const std::string& name, core::Unit::Flags /*flags*/) const override;

    std::shared_ptr<core::MethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, core::Unit::Flags flags) const override;

    std::shared_ptr<core::PrintOperatorUnit> createPrintOperatorUnit(const std::string& text) const override;
};

} // namespace cpp

#endif // CPP_UNITS_H
