#include "directorystatsmainwindow.h"
#include "ui_directorystatsmainwindow.h"

DirectoryStatsMainWindow::DirectoryStatsMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DirectoryStatsMainWindow)
{
    ui->setupUi(this);
}

DirectoryStatsMainWindow::~DirectoryStatsMainWindow()
{
    delete ui;
}
