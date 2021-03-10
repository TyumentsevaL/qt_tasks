#ifndef FILEINFOWATCHER_H
#define FILEINFOWATCHER_H

#include <QObject>
#include <QFileInfo>

QT_FORWARD_DECLARE_CLASS(QFileInfo)

/*!
 * \brief The FileInfoWatcher class это просто демонстрационный подписчик
 * для оповещений о состояниях файла, какого-то конкретного, но можно менять его.
 * На момент создания класс сугубо демонстрационный, весь вывод информации о файле,
 * приходящей по сигналу, можно было бы сделать без этого класса, сразу печатать.
 */
class FileInfoWatcher : public QObject
{
    Q_OBJECT
public:
    explicit FileInfoWatcher(const QString &watchedFilePath, QObject *parent = nullptr);

    /*!
     * \brief setWatchedFile
     * \param path
     */
    void setWatchedFile(const QString &path);

    /*!
     * \brief watchedFile -- возвращает путь, за которым "наблюдает" класс
     * \return
     */
    QString watchedFile() const;

    /*!
     * \brief getInfoToString -- возвращает удобночитаемую строку с инфой о файле
     * \return                -- строка с переносами, что-то про файл
     */
    QString getInfoToString() const;

signals:
    /*!
     * \brief fileChanged -- сигнал, который оповещает, что инфао файле обновилась,
     * превращает этот класс в очень простенький прокси
     */
    void fileChanged();

public slots:
    /*!
     * \brief fileInfoUpdated -- слот, чтобы подписаться на обновляения о файле
     * \param newInfo         -- новая инфа о файле
     */
    void fileInfoUpdated(const QFileInfo& newInfo);

private:
    QString m_watchedFilePath;
    QFileInfo m_watchedFileInfo;
};

#endif // FILEINFOWATCHER_H
