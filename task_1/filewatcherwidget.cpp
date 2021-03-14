#include "filewatcherwidget.h"
#include "ui_filewatcherwidget.h"

FileWatcherWidget::FileWatcherWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileWatcherWidget)
{
    ui->setupUi(this);
}

FileWatcherWidget::~FileWatcherWidget()
{
    delete ui;
}
