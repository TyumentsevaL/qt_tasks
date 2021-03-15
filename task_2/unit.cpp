#include "unit.h"

#include <stdexcept>

void Unit::add(const std::shared_ptr<Unit> &, Unit::Flags)
{
    throw std::runtime_error( "Not supported" );
}

std::string Unit::generateShift(unsigned int level) const
{
    static const auto DEFAULT_SHIFT = " ";
    std::string result;
    for( unsigned int i = 0; i < level; ++i ) {
        result += DEFAULT_SHIFT;
    }
    return result;
}

// -------------------------------------------------- *** --------------------------------------------------

PrintOperatorUnit::PrintOperatorUnit(const std::string &text)
    : m_text(text)
{ }

std::string PrintOperatorUnit::compile(unsigned int level) const
{
    return generateShift( level ) + "printf( \"" + m_text + "\" );\n";
}
