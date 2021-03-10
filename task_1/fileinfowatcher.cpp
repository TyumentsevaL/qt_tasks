#include "fileinfowatcher.h"

#include <QFileInfo>
#include <QDateTime>

FileInfoWatcher::FileInfoWatcher(const QString &watchedFilePath, QObject *parent)
    : QObject(parent)
    , m_watchedFilePath(watchedFilePath)
{ }

void FileInfoWatcher::setWatchedFile(const QString &path)
{
    m_watchedFilePath = path;
}

QString FileInfoWatcher::getInfoToString() const
{
    if (m_watchedFileInfo.fileName().isEmpty()) {
        return QString("No data yet for path: %1").arg(m_watchedFilePath);
    }

    if (!m_watchedFileInfo.exists()) {
        return QString("File removed or never existed: %1").arg(m_watchedFilePath);
    }

    return QString("Watched path -- %1\n  Name: %2\n  Size: %3\n  Last modified: %4\n\n")
            .arg(m_watchedFilePath)
            .arg(m_watchedFileInfo.baseName())
            .arg(m_watchedFileInfo.size())
            .arg(m_watchedFileInfo.lastModified().toString(Qt::ISODate));
}

void FileInfoWatcher::fileInfoUpdated(const QFileInfo &newInfo)
{
    if (newInfo.filePath() == m_watchedFilePath) {
        m_watchedFileInfo = newInfo;
        emit fileChanged();
    }
}
