#include "filewatcherwidget.h"
#include "ui_filewatcherwidget.h"

#include <QFileDialog>

#include "fileinfowatcher.h"
#include "filewatchermanager.h"

FileWatcherWidget::FileWatcherWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileWatcherWidget)
{
    ui->setupUi(this);

    // ------- config UI -------

    FileWatcherManager::Instance().setSendsInitInfo(true);

    connect(ui->choosePushButton, &QAbstractButton::clicked, [this]{
        const QString path = QFileDialog::getOpenFileName(this, "Выберите файл для наблюдения", QDir::currentPath(), "Any file (*.*)");
        watchers[path] = new FileInfoWatcher(path, this);
        QObject::connect(&FileWatcherManager::Instance(), &FileWatcherManager::fileChanged, watchers[path], &FileInfoWatcher::fileInfoUpdated);
        FileWatcherManager::Instance().addPath(path);
        ui->filesListWidget->addItem(path);
    });

    connect(ui->deletePushButton, &QAbstractButton::clicked, [this]{
        int row = ui->filesListWidget->currentRow();
        if (row >= 0) {
            const QString path = ui->filesListWidget->currentItem()->text();
            FileWatcherManager::Instance().removePath(path);
            if (watchers.contains(path)) {
                watchers[path]->deleteLater();
            }
            ui->filesListWidget->model()->removeRow(row);
        }
    });

    connect(ui->filesListWidget->selectionModel(), &QItemSelectionModel::currentRowChanged
            , [this](const QModelIndex &current, const QModelIndex &/*previous*/) {
        const QString path = current.data().toString();
        if (watchers.contains(path)) {
            ui->infoTextEdit->setText(watchers[path]->getInfoToString());
        }
    });

    connect(ui->refreshPushButton, &QAbstractButton::clicked, [this]{
        const QModelIndex currentIndex = ui->filesListWidget->currentIndex();
        if (currentIndex.isValid()) {
            ui->infoTextEdit->setText(watchers[currentIndex.data().toString()]->getInfoToString());
        }
    });
}

FileWatcherWidget::~FileWatcherWidget()
{ }
