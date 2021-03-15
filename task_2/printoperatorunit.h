#ifndef PRINTOPERATORUNIT_H
#define PRINTOPERATORUNIT_H

#include "unit.h"

class PrintOperatorUnit : public core::Unit {
public:
    explicit PrintOperatorUnit(const std::string& text);

    std::string compile( unsigned int level = 0 ) const;

private:
    std::string m_text;
};

#endif // PRINTOPERATORUNIT_H
