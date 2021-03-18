#ifndef ABSTRACTSTATHOLDER_H
#define ABSTRACTSTATHOLDER_H

#include <QSharedPointer>
class AbstractDirectoryStrategy;

class AbstractStatHolder
{
public:
    virtual ~AbstractStatHolder() {}

    virtual void setStatisticsStrategy(const QSharedPointer<AbstractDirectoryStrategy> &strategy) = 0;

    virtual void updateStatistics() = 0;

};

#endif // ABSTRACTSTATHOLDER_H
