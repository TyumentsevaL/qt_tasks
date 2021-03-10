#include "fileinfowatcher.h"

#include <QFileInfo>
#include <QDateTime>
#include <QDebug>

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
    if (m_fileData.empty()) {
        return QString("No data yet for path: %1").arg(m_watchedFilePath);
    }

    if (!m_fileData[EXISTS_INFO].toBool()) {
        return QString("File removed or never existed: %1").arg(m_watchedFilePath);
    }

    return QString("Watched path -- %1\n  Name: %2\n  Size: %3\n  Last modified: %4\n\n")
            .arg(m_watchedFilePath)
            .arg(m_fileData[BASE_NAME_INFO].toString())
            .arg(m_fileData[SIZE_INFO].toLongLong())
            .arg(m_fileData[LAST_MODIFIED_INFO].toDateTime().toString(Qt::ISODate));
}

void FileInfoWatcher::fileInfoUpdated(const QFileInfo &newInfo)
{
    if (newInfo.filePath() == m_watchedFilePath) {
        m_fileData[EXISTS_INFO] = newInfo.exists();
        if (newInfo.exists()) {
            m_fileData[SIZE_INFO] = newInfo.size();
            m_fileData[BASE_NAME_INFO] = newInfo.baseName();
            m_fileData[LAST_MODIFIED_INFO] = newInfo.lastModified();
        }

        emit fileChanged();
    }
}
