#ifndef LISTFILESTRATEGY_H
#define LISTFILESTRATEGY_H

#include "abstractdirectorystrategy.h"

class ListFileStrategy : public AbstractDirectoryStrategy
{
public:
    QHash<QString, double> getDirectoryInfo(const QString &path) override;
};

#endif // LISTFILESTRATEGY_H
