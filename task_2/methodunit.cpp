#include "methodunit.h"

#include <sstream>

MethodUnit::MethodUnit(const std::string& name, const std::string& returnType, Flags flags)
    : m_name(name)
    , m_returnType(returnType)
    , m_flags(flags)
{ }

void MethodUnit::add(const std::shared_ptr<Unit> &unit, Unit::Flags)
{
    m_body.push_back(unit);
}

std::string MethodUnit::compile(unsigned int level) const
{
    std::stringstream result;
    result << core::generateShift(level);

    if( m_flags & STATIC ) {
        result << "static ";
    } else if( m_flags & VIRTUAL ) {
        result << "virtual ";
    }

    result << m_returnType
           << " "
           << m_name
           << "()";
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
