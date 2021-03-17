#include "abstractdirectorystrategy.h"

#include <QDir>

// в корне терабайтного диска лучше не запускать
qint64 AbstractDirectoryStrategy::getTotalDirSize(const QString &path)
{
    if (m_dirSizeCache.contains(path)) {
        return m_dirSizeCache[path];
    }
    qint64 result = 0;

    if (QFileInfo(path).isDir()) {
        QDir directory(path);
        for (const auto& it : directory.entryInfoList(QDir::Dirs | QDir::Files| QDir::NoDotAndDotDot
                                                      | QDir::Hidden | QDir::NoSymLinks, QDir::Name | QDir::Type)) {
            if (it.isDir()) {
                result += getTotalDirSize(it.absoluteFilePath());
            } else {
                result += it.size();
            }
        }
    }
    else {
        result += QFileInfo(path).size();
    }

    return result;
}
