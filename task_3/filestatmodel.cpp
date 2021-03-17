#include "filestatmodel.h"
#include "abstractdirectorystrategy.h"

FileStatModel::FileStatModel(QObject *parent)
    : QFileSystemModel(parent)
{
    connect(this, &QFileSystemModel::rootPathChanged, [this](const QString &newPath) {
        if (m_statStrategy) {
            m_cachedStats = m_statStrategy->getDirectoryInfo(newPath);
        }
    });
}

void FileStatModel::setStatisticsStrategy(const QSharedPointer<AbstractDirectoryStrategy> &strategy)
{
    m_statStrategy = strategy;
}

int FileStatModel::columnCount(const QModelIndex &parent) const
{
    int realColumnCount = QFileSystemModel::columnCount(parent);
    return realColumnCount + 1;
}

QVariant FileStatModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && section == columnCount() - 1 && role == Qt::DisplayRole) {
        return QStringLiteral("Stats");
    }
    return QFileSystemModel::headerData(section, orientation, role);
}

QVariant FileStatModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.column() == columnCount() - 1 && role == Qt::DisplayRole) {
//        const QString path = filePath(index);
        return "todo";
    }

    return QFileSystemModel::data(index, role);
}
