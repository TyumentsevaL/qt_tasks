#include <QCoreApplication>
#include <QDebug>

#include <memory>
#include <QFileInfo>
#include <QDir>
#include "listfilestrategy.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::shared_ptr<AbstractDirectoryStrategy> strategy = std::make_shared<ListFileStrategy>();

    const QString currentDir = QDir::currentPath();
    for (auto& item : strategy->getDirectoryInfo(currentDir + "/..")) {
        qDebug() << QFileInfo(item.first).fileName() << " : " << item.second;
    }
    return a.exec();
}
