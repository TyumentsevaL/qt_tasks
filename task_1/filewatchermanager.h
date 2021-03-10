#ifndef FILEWATCHERMANAGER_H
#define FILEWATCHERMANAGER_H

#include <QObject>
#include <QFileInfo>

QT_FORWARD_DECLARE_CLASS(QTimer)

/*!
 * \brief The FileWatcherManager class это менеджер,
 * который наблюдает за файлами. Названия списаны с QFileSystemWatcher, но
 * принцип работы проще -- по таймеру проверяет список файлов, есть ли изменения.
 * Сделан как синглтон, согласно заданию. НЕ потокобезопасен.
 */
class FileWatcherManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(FileWatcherManager)
public:
    static FileWatcherManager& Instance()
    {
        static FileWatcherManager instance;
        return instance;
    }

    bool addPath(const QString &path);

    QStringList addPaths(const QStringList &paths);

    QStringList files() const;

    bool removePath(const QString &path);

    QStringList removePaths(const QStringList &paths);

signals:
    void fileChanged(const QFileInfo& newInfo);

private:
    explicit FileWatcherManager();

private:
    QTimer *m_checkTimer;
    QHash<QString, QFileInfo> m_watchedFilesData;
};

#endif // FILEWATCHERMANAGER_H
