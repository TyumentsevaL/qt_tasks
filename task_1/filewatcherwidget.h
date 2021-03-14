#ifndef FILEWATCHERWIDGET_H
#define FILEWATCHERWIDGET_H

#include <QWidget>

namespace Ui {
class FileWatcherWidget;
}

class FileWatcherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileWatcherWidget(QWidget *parent = nullptr);
    ~FileWatcherWidget();

private:
    Ui::FileWatcherWidget *ui;
};

#endif // FILEWATCHERWIDGET_H
