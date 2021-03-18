#ifndef DIRECTORYSTATSMAINWINDOW_H
#define DIRECTORYSTATSMAINWINDOW_H

#include <QWidget>

namespace Ui {
class DirectoryStatsMainWindow;
}

namespace QtCharts {
    class QChartView;
    class QChart;
}

QT_FORWARD_DECLARE_CLASS(QModelIndex)
class AbstractDirectoryStrategy;
class AbstractStatHolder;
class CustomFileModel;
class ChartUpdater;

class DirectoryStatsMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DirectoryStatsMainWindow(QWidget *parent = nullptr);
    ~DirectoryStatsMainWindow();

private:
    void chooseTreeFolder(const QString &path);
    void handleTreeSelection(const QModelIndex &index);

private slots:
    void updateStatsViews();

private:
    const QSharedPointer<Ui::DirectoryStatsMainWindow> ui;
    CustomFileModel *m_treeModel;
    CustomFileModel *m_tableModel;

    QSharedPointer<AbstractDirectoryStrategy> m_fileStatStrategy;
    QSharedPointer<AbstractDirectoryStrategy> m_fileGroupStatStrategy;

    QSharedPointer<QtCharts::QChart> m_chart;
    QtCharts::QChartView *m_chartView;
    ChartUpdater    *m_chartUpdater;

    AbstractStatHolder* m_chartStatHolder;
    QList<AbstractStatHolder*> m_statHolders;
};

#endif // DIRECTORYSTATSMAINWINDOW_H
