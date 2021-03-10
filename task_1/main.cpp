#include <QCoreApplication>
#include <QSharedPointer>
#include <QDir>
#include <QDebug>

#include "filewatchermanager.h"
#include "fileinfowatcher.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileWatcherManager& manager = FileWatcherManager::Instance();

    const QString currentDir = QDir::currentPath();
    const QStringList sampleFiles = {
        currentDir + "/../task_1/main.cpp",
        currentDir + "/../task_1/fileinfowatcher.h",
        currentDir + "/../task_1/task_1.pro"
    };

    QVector<QSharedPointer<FileInfoWatcher>> watchers;
    watchers.reserve(sampleFiles.size());

    for(const QString &path : sampleFiles) {
        auto watcher = QSharedPointer<FileInfoWatcher>::create(path);
        watchers.append(watcher);
        QObject::connect(&manager, &FileWatcherManager::fileChanged, watcher.get(), &FileInfoWatcher::fileInfoUpdated);
        QObject::connect(watcher.get(), &FileInfoWatcher::fileChanged, [watcher]{
            qInfo().noquote() << watcher->getInfoToString();
        });
    }

    if (manager.addPaths(sampleFiles).size() > 0) {
        return -1;
    }

    return a.exec();
}
