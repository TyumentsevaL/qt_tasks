#ifndef METHODUNIT_H
#define METHODUNIT_H

#include "unit.h"
#include <vector>

class CppMethodUnit : public core::MethodUnit {
public:
    using MethodUnit::MethodUnit;

    void add(const std::shared_ptr< Unit >& unit, Flags /* flags */ = 0);

    std::string compile( unsigned int level = 0 ) const;
};
#endif // METHODUNIT_H
