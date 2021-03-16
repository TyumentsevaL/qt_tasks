#ifndef CLASSUNIT_H
#define CLASSUNIT_H

#include "unit.h"

class CppClassUnit : public core::ClassUnit
{
public:
    using ClassUnit::ClassUnit;

    void add(const std::shared_ptr<Unit>& unit, Flags flags);

    std::string compile(unsigned int level = 0) const;
};

#endif // CLASSUNIT_H
