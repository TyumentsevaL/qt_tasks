#ifndef FILEINFOWATCHER_H
#define FILEINFOWATCHER_H

#include <QObject>
#include <QVariant>

QT_FORWARD_DECLARE_CLASS(QFileInfo)

/*!
 * \brief The FileInfoWatcher class это просто демонстрационный подписчик
 * для оповещений о состояниях файла, какого-то конкретного, но можно менять
 */
class FileInfoWatcher : public QObject
{
    Q_OBJECT
public:
    enum FileInfoType {
        BASE_NAME_INFO,
        SIZE_INFO,
        EXISTS_INFO,
        LAST_MODIFIED_INFO,
        INFO_COUNT
    };

    explicit FileInfoWatcher(const QString &watchedFilePath, QObject *parent = nullptr);

    void setWatchedFile(const QString &path);

    QString getInfoToString() const;

signals:
    void fileChanged();

public slots:
    void fileInfoUpdated(const QFileInfo& newInfo);

private:
    QString m_watchedFilePath;
    QHash<int, QVariant> m_fileData;
};

#endif // FILEINFOWATCHER_H
