#ifndef CPP_UNITS_H
#define CPP_UNITS_H

#include "core_units.h"

class CppClassUnit : public core::ClassUnit
{
public:
    using ClassUnit::ClassUnit;

    void add(const std::shared_ptr<Unit>& unit, Flags flags);

    std::string compile(unsigned int level = 0) const;
};

// --------------------------------------------- *** --------------------------------------------- //

class CppMethodUnit : public core::MethodUnit {
public:
    using MethodUnit::MethodUnit;

    void add(const std::shared_ptr< Unit >& unit, Flags /* flags */ = 0);

    std::string compile( unsigned int level = 0 ) const;
};

// --------------------------------------------- *** --------------------------------------------- //

class CppPrintOperatorUnit : public core::PrintOperatorUnit {
public:
    using PrintOperatorUnit::PrintOperatorUnit;
    std::string compile( unsigned int level = 0 ) const;
};


#endif // CPP_UNITS_H
