#ifndef JAVA_UNITS_H
#define JAVA_UNITS_H

#include "core_units.h"

namespace java {

class JavaClassUnit : public core::ClassUnit
{
public:
    using ClassUnit::ClassUnit;

    void add(const std::shared_ptr<Unit>& unit, Flags flags) override;

    // тут копипаста из C#
    std::string compile(unsigned int level = 0) const override;
};

// --------------------------------------------- *** --------------------------------------------- //

/*!
 * \brief The JavaMethodUnit class это про методы в Java,
 *  тут я тоже не уверена, что обработала все сочетания правильно, пыталась немного
 */
class JavaMethodUnit : public core::MethodUnit
{
public:
    using MethodUnit::MethodUnit;
    std::string compile(unsigned int level = 0) const override;
};

// --------------------------------------------- *** --------------------------------------------- //

class JavaPrintOperatorUnit : public core::PrintOperatorUnit
{
public:
    using PrintOperatorUnit::PrintOperatorUnit;
    std::string compile(unsigned int level = 0) const override;
};

// --------------------------------------------- *** --------------------------------------------- //

class JavaUnitFactory : public core::UnitFactory
{
public:
    std::shared_ptr<core::ClassUnit> createClassUnit(const std::string& name, core::Unit::Flags flags) const override;

    std::shared_ptr<core::MethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, core::Unit::Flags flags) const override;

    std::shared_ptr<core::PrintOperatorUnit> createPrintOperatorUnit(const std::string& text) const override;
};

} // namespace java

#endif // JAVA_UNITS_H
