#ifndef CHARTUPDATER_H
#define CHARTUPDATER_H

#include "abstractstatholder.h"
#include <QObject>

namespace QtCharts {
    class QChart;
}

class ChartUpdater : public QObject, public AbstractStatHolder
{
    Q_OBJECT
public:
    enum DisplayMode {
        PIE_MODE,
        BAR_MODE
    };

    explicit ChartUpdater(const QSharedPointer<QtCharts::QChart> &chart, QObject *parent = nullptr);

    void setDisplayMode(DisplayMode mode);

    void setStatisticsStrategy(const QSharedPointer<AbstractDirectoryStrategy> &strategy) override;

    void updateStatistics() override;

private:
    QSharedPointer<AbstractDirectoryStrategy> m_statStrategy = nullptr;
    QSharedPointer<QtCharts::QChart> m_chart;
    DisplayMode m_mode;
};

#endif // CHARTUPDATER_H
