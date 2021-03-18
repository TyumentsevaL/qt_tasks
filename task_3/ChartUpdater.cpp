#include "chartupdater.h"
#include "abstractdirectorystrategy.h"

#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>

ChartUpdater::ChartUpdater(const QSharedPointer<QtCharts::QChart> &chart, QObject *parent)
    : QObject(parent)
    , m_chart(chart)
    , m_mode(PIE_MODE)
{ }

void ChartUpdater::setDisplayMode(ChartUpdater::DisplayMode mode)
{
    m_mode = mode;
    updateStatistics();
}

void ChartUpdater::setStatisticsStrategy(const QSharedPointer<AbstractDirectoryStrategy> &strategy)
{
    m_statStrategy = strategy;
}

void ChartUpdater::updateStatistics()
{
    if (m_mode == PIE_MODE)
    {
//        m_chart->removeAllSeries();
//        QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
//        auto info = m_statStrategy->getDirectoryInfo();
//        for (auto& name : info.keys()) {
//            series->append(fileMode ? QFileInfo(name).fileName() : name, info[name]);
//        }
//        chart->addSeries(series);
    }

    if (m_mode == BAR_MODE)
    {

    }
}
