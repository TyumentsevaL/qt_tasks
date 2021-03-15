#include "printoperatorunit.h"

#include <sstream>

PrintOperatorUnit::PrintOperatorUnit(const std::string &text)
    : m_text(text)
{ }

std::string PrintOperatorUnit::compile(unsigned int level) const
{
    std::stringstream ss;
    ss << core::generateShift(level)
       << "printf( \""
       << m_text
       << "\" );\n";
    return ss.str();
}
