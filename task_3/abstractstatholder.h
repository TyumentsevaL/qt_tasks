#ifndef ABSTRACTSTATHOLDER_H
#define ABSTRACTSTATHOLDER_H

#include <QSharedPointer>
class AbstractDirectoryStrategy;

class AbstractStatHolder
{
public:
    virtual ~AbstractStatHolder() {}

    /*!
     * \brief setStatsGrouped -- это костыль, потому что задумка со стратегиями
     * совершенно загадочна. Мб это сработало бы для переписанной модели, которая
     * отображает типы файлов сразу, но пока так пусть будет
     * \param grouped         -- смотреть ли по расширениям
     */
    void setStatsGrouped(bool grouped);

    virtual void setStatisticsStrategy(const QSharedPointer<AbstractDirectoryStrategy> &strategy);

    void updateStatistics(const QString& path);

protected:
    virtual void updateStatisticsImpl(const QString& path) = 0;

protected:
    bool m_statIsGrouped = false;
    QSharedPointer<AbstractDirectoryStrategy> m_statStrategy = nullptr;
    QString m_path;
};

#endif // ABSTRACTSTATHOLDER_H
