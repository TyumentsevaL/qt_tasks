#include "directorystatsmainwindow.h"
#include "ui_directorystatsmainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>

#include "filestatmodel.h"
#include "listfilestrategy.h"
#include "groupfilestrategy.h"

DirectoryStatsMainWindow::DirectoryStatsMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DirectoryStatsMainWindow)
    , m_treeModel(new CustomFileModel(this))
    , m_tableModel(new CustomFileModel(this))
    , m_fileStatStrategy(QSharedPointer<ListFileStrategy>::create())
    , m_fileGroupStatStrategy(QSharedPointer<GroupFileStrategy>::create())
    , m_chart(new QtCharts::QChart)
    , m_axisY(new QtCharts::QValueAxis)
    , m_chartView(new QtCharts::QChartView(m_chart.data(), this))
{
    ui->setupUi(this);

    // -------- config UI --------

    connect(ui->choosePushButton, &QAbstractButton::clicked, [this]{
        const QString path = QFileDialog::getExistingDirectory(this, "Выберите папку для статистики", QDir::currentPath());
        if (!path.isEmpty()) {
            chooseTreeFolder(path);
        }
    });
    ui->listFilesRadioButton->setChecked(true);

    m_treeModel->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    ui->filesTreeView->setModel(m_treeModel);
    ui->filesTreeView->header()->setSectionResizeMode(QHeaderView::Stretch);

    m_tableModel->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    ui->filesTableView->setModel(m_tableModel);
    ui->filesTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->filesTreeView->selectionModel(), &QItemSelectionModel::currentRowChanged
            , [this](const QModelIndex &current, const QModelIndex &/*previous*/) {
        handleTreeSelection(current);
    });

    // -------------
    auto strategyToggler =  [this]{
        bool goodStats = ui->listFilesRadioButton->isChecked();
        if (goodStats) {
            m_treeModel->setStatisticsStrategy(m_fileStatStrategy);
            m_tableModel->setStatisticsStrategy(m_fileStatStrategy);
        } else {
            m_treeModel->setStatisticsStrategy(m_fileGroupStatStrategy);
            m_tableModel->setStatisticsStrategy(m_fileGroupStatStrategy);
        }

        m_treeModel->updateStatistics();
        m_tableModel->updateStatistics();
        m_treeModel->setStatsGrouped(!goodStats);
        m_tableModel->setStatsGrouped(!goodStats);
    };

    connect(ui->listFilesRadioButton, &QRadioButton::toggled, this, strategyToggler);
    connect(ui->groupFilesRadioButton, &QRadioButton::toggled, this, strategyToggler);
    strategyToggler();

    // -------------
    chooseTreeFolder(QDir::currentPath());
    ui->statsViewStackedWidget->setCurrentIndex(0); // table

    // ------------- *** charts *** ------------- //

    QVBoxLayout *layout = new QVBoxLayout(ui->chartPage);
    ui->chartPage->setLayout(layout);
    layout->setMargin(0);
    layout->addWidget(m_chartView);

    m_chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    m_chart->addAxis(m_axisY.data(), Qt::AlignLeft);
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);

    connect(ui->statsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        ui->statsViewStackedWidget->setCurrentIndex(index > 0 ? 1 : 0);
    });

}

DirectoryStatsMainWindow::~DirectoryStatsMainWindow()
{ }

void DirectoryStatsMainWindow::chooseTreeFolder(const QString &path)
{
    ui->dirLineEdit->setText(path);
    ui->filesTreeView->setRootIndex(m_treeModel->setRootPath(path));

    ui->filesTableView->setRootIndex(m_tableModel->setRootPath(""));

    if (!ui->filesTreeView->selectionModel()->selectedIndexes().isEmpty()) {
        handleTreeSelection(ui->filesTreeView->selectionModel()->selectedIndexes().first());
    } else {
        ui->filesTableView->hide();
    }
}

void DirectoryStatsMainWindow::handleTreeSelection(const QModelIndex &index)
{
    const QString currPath = m_treeModel->filePath(index);
    bool isDir = QFileInfo(currPath).isDir();
    ui->filesTableView->setVisible(isDir);
    if (isDir) {
        ui->filesTableView->setRootIndex(m_tableModel->setRootPath(currPath));
    }
}
