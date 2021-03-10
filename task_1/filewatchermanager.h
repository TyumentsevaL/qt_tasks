#ifndef FILEWATCHERMANAGER_H
#define FILEWATCHERMANAGER_H

#include <QObject>
#include <QFileInfo>

QT_FORWARD_DECLARE_CLASS(QTimer)

/*!
 * \brief The FileWatcherManager class это менеджер,
 * который наблюдает за файлами. Названия списаны с QFileSystemWatcher, но
 * принцип работы проще -- по таймеру проверяет список файлов, есть ли изменения.
 * Это или удаление, или дата изменения поменялась.
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

    /*!
     * \brief addPath -- добавляет файл для наблюдения
     * \param path    -- путь до файла
     * \return        -- если это папка или файла нет, то false
     */
    bool addPath(const QString &path);

    /*!
     * \brief addPaths -- добавляет пачкой файлы
     * \param paths    -- пути до наблюдаемых файлов
     * \return         -- список файлов, которые добавить не вышло
     */
    QStringList addPaths(const QStringList &paths);

    /*!
     * \brief files -- список наблюдаемых файлов возвращает
     * \return
     */
    QStringList files() const;

    /*!
     * \brief removePath -- удаляет путь из наблюдения
     * \param path       -- что удалить
     * \return           -- если такого файла уже нет, ничего не удалится
     */
    bool removePath(const QString &path);

    /*!
     * \brief removePaths -- удаляет несклько путей из наблюдения
     * \param paths       -- что удалить
     * \return            -- список файлов, которые удалить из наблюдения не вышло
     */
    QStringList removePaths(const QStringList &paths);

signals:
    /*!
     * \brief fileChanged -- сигнал, что что-то поменялось в одном из наблюдаемых файлов
     * \param newInfo     -- новые данные о файле
     */
    void fileChanged(const QFileInfo& newInfo);

private:
    explicit FileWatcherManager();

private:
    QTimer *m_checkTimer;
    QHash<QString, QFileInfo> m_watchedFilesData;
};

#endif // FILEWATCHERMANAGER_H
