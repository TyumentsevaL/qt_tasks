#ifndef UNIT_H
#define UNIT_H

#include <memory>
#include <string>

namespace core {
/*!
 * \brief The Unit class это у нас типа abstract base для сущностей,
 * чтобы было дерево вложенности
 */
class Unit {
public:
    using Flags = unsigned int;
public:
    virtual ~Unit() = default;

    virtual void add(const std::shared_ptr<Unit>&, Flags);

    virtual std::string compile(unsigned int level = 0) const = 0;
};

/*!
 * \brief generateShift -- форматирование, это НЕ часть единицы абстрации, потому свободная функция
 * \param level         -- уровень вложенности
 * \return              -- отступ
 */
std::string generateShift(unsigned int level);

} // namespace core

#endif // UNIT_H
