#include "unit.h"
#include <stdexcept>

void core::Unit::add(const std::shared_ptr<core::Unit> &, core::Unit::Flags)
{
    throw std::runtime_error("Not supported");
}

std::string core::generateShift(unsigned int level)
{
    static const char DEFAULT_SHIFT = ' '; // TODO: support tabs via global config
    return std::string(4 * level, DEFAULT_SHIFT);
}
