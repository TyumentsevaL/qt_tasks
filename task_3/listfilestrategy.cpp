#include "listfilestrategy.h"

#include <QDir>
#include <QDebug>

QList<AbstractDirectoryStrategy::FileInfo> ListFileStrategy::getDirectoryInfo(const QString &path)
{
    QList<AbstractDirectoryStrategy::FileInfo> result;

    if (!QFile::exists(path)) {
        return result;
    }

    const QFileInfo pathInfo(path);
    if (!pathInfo.isDir()) {
        result.append(qMakePair(path, QStringLiteral("100%")));
    }

    qint64 total = getTotalDirSize(pathInfo.absolutePath()); // hope, caching works

    QDir directory(path);
    for (const auto& it : directory.entryInfoList(QDir::Dirs | QDir::Files| QDir::NoDotAndDotDot
                                                  | QDir::Hidden | QDir::NoSymLinks, QDir::Name)) {
        qint64 current = getTotalDirSize(it.absoluteFilePath());
        double percent = 1. * current / total;
        if (percent > SIZE_PRESIZION) {
            result.append(qMakePair(it.absoluteFilePath(), QString::number(percent * 100, 'f', 2) + "%"));
        } else {
            result.append(qMakePair(it.absoluteFilePath(), QString("< 0.01%")));
        }
    }

    return result;
}
