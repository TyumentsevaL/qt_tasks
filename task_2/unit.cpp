#include "unit.h"
#include <stdexcept>

namespace core {

void core::Unit::add(const std::shared_ptr<core::Unit> &, core::Unit::Flags)
{
    throw std::runtime_error("Not supported");
}

// --------------------------------------------- *** --------------------------------------------- //

const std::vector<std::string> ClassUnit::ACCESS_MODIFIERS = { "public",
                                                               "protected",
                                                               "private" };

ClassUnit::ClassUnit(const std::string& name)
    : m_name(name)
{
    m_fields.resize(ACCESS_MODIFIERS.size());
}

// --------------------------------------------- *** --------------------------------------------- //

MethodUnit::MethodUnit(const std::string& name, const std::string& returnType, Flags flags)
    : m_name(name)
    , m_returnType(returnType)
    , m_flags(flags)
{ }

// --------------------------------------------- *** --------------------------------------------- //

PrintOperatorUnit::PrintOperatorUnit(const std::string &text)
    : m_text(text)
{ }

// --------------------------------------------- *** --------------------------------------------- //

std::string core::generateShift(unsigned int level)
{
    static const char DEFAULT_SHIFT = ' '; // TODO: support tabs via global config
    return std::string(4 * level, DEFAULT_SHIFT);
}

} // namespace core
