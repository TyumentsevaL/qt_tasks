#ifndef FILEWATCHERWIDGET_H
#define FILEWATCHERWIDGET_H

#include <QWidget>

namespace Ui {
class FileWatcherWidget;
}

class FileInfoWatcher;

class FileWatcherWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileWatcherWidget(QWidget *parent = nullptr);
    ~FileWatcherWidget();

private:
    QSharedPointer<Ui::FileWatcherWidget> ui;
    // не особенно нужно, больше для демонстрации
    QHash<QString, FileInfoWatcher*> watchers;
};

#endif // FILEWATCHERWIDGET_H
