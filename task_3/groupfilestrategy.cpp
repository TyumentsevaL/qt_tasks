#include "groupfilestrategy.h"
#include <QDir>

//#define USE_MIME

#ifdef USE_MIME
#include <QMimeDatabase>
#include <QMimeType>
    const QString GroupFileStrategy::DIR_MIME = "no-app/dir";
#else
    const QString GroupFileStrategy::DIR_MIME = "dir";
#endif

QHash<QString, QString> GroupFileStrategy::getDirectoryInfo(const QString &path)
{
    QHash<QString, QString> result;

    if (!QFile::exists(path)) {
        return {};
    }

    const QFileInfo pathInfo(path);
    if (!pathInfo.isDir()) {
        result.insert(path, QStringLiteral("100%"));
    }

    qint64 total = getTotalSize(pathInfo.absoluteFilePath()); // hope, caching works
    QHash<QString, qint64> typeSizes;
#ifdef USE_MIME
    QMimeDatabase db;
#endif

    QDir directory(path);
    for (const auto& it : directory.entryInfoList(QDir::Dirs | QDir::Files| QDir::NoDotAndDotDot
                                                  | QDir::Hidden | QDir::NoSymLinks, QDir::Name)) {
        qint64 current = getTotalSize(it.absoluteFilePath());
#ifdef USE_MIME
        QString typeName = it.isDir()
                    ? GroupFileStrategy::DIR_MIME
                    : db.mimeTypeForFile(it.absoluteFilePath(), QMimeDatabase::MatchExtension).name();
#else
        QString typeName = it.isDir()
                    ? GroupFileStrategy::DIR_MIME
                    : it.suffix();
#endif
        typeSizes[typeName] += current;
    }

    for (const QString &typeName : typeSizes.keys()) {
        qint64 current = typeSizes[typeName];
        double percent = 1. * current / total;
        if (percent > SIZE_PRESIZION) {
            result.insert(typeName, QString::number(percent * 100, 'f', 2) + "%");
        } else {
            result.insert(typeName, QString("< 0.01%"));
        }
    }

    return result;
}
