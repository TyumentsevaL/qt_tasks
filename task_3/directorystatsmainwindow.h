#ifndef DIRECTORYSTATSMAINWINDOW_H
#define DIRECTORYSTATSMAINWINDOW_H

#include <QWidget>

namespace Ui {
class DirectoryStatsMainWindow;
}

class DirectoryStatsMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DirectoryStatsMainWindow(QWidget *parent = nullptr);
    ~DirectoryStatsMainWindow();

private:
    Ui::DirectoryStatsMainWindow *ui;
};

#endif // DIRECTORYSTATSMAINWINDOW_H
