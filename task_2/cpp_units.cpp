#include "cpp_units.h"
#include <sstream>

namespace cpp {

void CppClassUnit::add(const std::shared_ptr<Unit> &unit, Unit::Flags flags)
{
    auto accessModifier = PRIVATE;
    if(flags <= ClassUnit::PRIVATE) { // иначе игнорируем, ошибку не кидаем, но можем
        accessModifier = static_cast<AccessModifier>(flags);
    }
    m_fields[accessModifier].push_back(unit);
}

std::string CppClassUnit::compile(unsigned int level) const
{
    std::stringstream result;
    result << core::generateShift(level)
           << "class "
           << m_name
           << " {\n";

    for(size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
        if(m_fields[i].empty()) {
            continue;
        }
        result << ACCESS_MODIFIERS[i] << ":\n";
        for(const auto& f : m_fields[i]) {
            result << f->compile(level + 1);
        }
        result << "\n";
    }
    result << core::generateShift(level) << "};\n";

    return result.str();
}

// --------------------------------------------- *** --------------------------------------------- //

std::string CppMethodUnit::compile(unsigned int level) const
{
    std::stringstream result;
    result << core::generateShift(level);

    if (m_flags & STATIC) {
        result << "static ";
    } else if (m_flags & VIRTUAL) {
        result << "virtual ";
    }

    result << m_returnType << " "  << m_name  << "()";

    if( m_flags & CONST ) {
        result << " const";
    }
    result << " {\n";

    for(const auto& b : m_body) {
        result << b->compile(level + 1);
    }
    result << core::generateShift(level) + "}\n";

    return result.str();
}

// --------------------------------------------- *** --------------------------------------------- //

std::string CppPrintOperatorUnit::compile(unsigned int level) const
{
    std::stringstream ss;
    ss << core::generateShift(level) << "printf( \"" << m_text << "\" );\n";
    return ss.str();
}

// --------------------------------------------- *** --------------------------------------------- //

std::shared_ptr<core::ClassUnit> CppUnitFactory::createClassUnit(const std::string &name, core::Unit::Flags) const
{
    return std::make_shared<CppClassUnit>(name);
}

std::shared_ptr<core::MethodUnit> CppUnitFactory::createMethodUnit(const std::string &name, const std::string &returnType, core::Unit::Flags flags) const
{
    return std::make_shared<CppMethodUnit>(name, returnType, flags);
}

std::shared_ptr<core::PrintOperatorUnit> CppUnitFactory::createPrintOperatorUnit(const std::string &text) const
{
    return std::make_shared<CppPrintOperatorUnit>(text);
}

}
