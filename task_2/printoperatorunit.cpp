#include "printoperatorunit.h"

#include <sstream>

std::string CppPrintOperatorUnit::compile(unsigned int level) const
{
    std::stringstream ss;
    ss << core::generateShift(level)
       << "printf( \""
       << m_text
       << "\" );\n";
    return ss.str();
}
