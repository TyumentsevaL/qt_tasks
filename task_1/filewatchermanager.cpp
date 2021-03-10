#include "filewatchermanager.h"

#include <QTimer>
#include <QFile>
#include <QDateTime>

namespace  {
const int DEFAULT_RECHECKPERIOD = 200; // make a param?
}

FileWatcherManager::FileWatcherManager()
    : QObject(nullptr)
    , m_checkTimer(new QTimer(this))
{
    m_checkTimer->setInterval(DEFAULT_RECHECKPERIOD);
    m_checkTimer->setSingleShot(false);
    m_checkTimer->start();

    connect(m_checkTimer, &QTimer::timeout, [this]{
        for(const QString& filePath : m_watchedFilesData.keys()) {
            QFileInfo newInfo(filePath);
            if (newInfo.exists()) {
                if (newInfo.lastModified() != m_watchedFilesData[filePath].lastModified()) {
                    m_watchedFilesData[filePath] = newInfo;
                    emit fileChanged(newInfo);
                }
            } else {
                m_watchedFilesData.remove(filePath);
                emit fileChanged(newInfo);
            }
        }
    });
}

bool FileWatcherManager::addPath(const QString &path)
{
    if (!QFile::exists(path) || m_watchedFilesData.contains(path)) {
        return false;
    }

    QFileInfo info(path);
    if (info.isDir()) {
        return false;
    }

    m_watchedFilesData.insert(path, info);
//    emit fileChanged(info); // uncomment to send initial info
    return true;
}

QStringList FileWatcherManager::addPaths(const QStringList &paths)
{
    QStringList result;
    for(const QString &path : paths) {
        if (!addPath(path)) {
            result.append(path);
        }
    }
    return result;
}

QStringList FileWatcherManager::files() const
{
    return m_watchedFilesData.keys();
}

bool FileWatcherManager::removePath(const QString &path)
{
    return m_watchedFilesData.remove(path) > 0;
}

QStringList FileWatcherManager::removePaths(const QStringList &paths)
{
    QStringList result;
    for(const QString &path : paths) {
        if (!removePath(path)) {
            result.append(path);
        }
    }
    return result;
}
