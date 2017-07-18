/*
** filemodel.h
**
** Copyright © Beyond Skyrim Development Team, 2017.
** This file is part of OPENCK (https://github.com/Beyond-Skyrim/openck)
**
** OpenCK is free software; this file may be used under the terms of the GNU
** General Public License version 3.0 or later as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** OpenCK is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**
** Please review the following information to ensure the GNU General Public
** License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** You should have received a copy of the GNU General Public License version
** 3.0 along with OpenCK; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** Created Date: 18-Jul-2017
*/

#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractItemModel>
#include <QVector>
#include <QVariant>
#include <QList>

namespace Models
{
    class FileModelItem;
    class FileModel;
}

class FileModelItem
{
public:
    explicit FileModelItem(const QVector<QVariant> &data, FileModelItem *parent = 0);
    ~FileModelItem();

    FileModelItem *child(int number);
    FileModelItem *parent();
    quint32 childCount() const;
    quint32 columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    quint32 childNumber() const;
    bool setData(int column, const QVariant &value);

private:
    /**
     * List of child items belonging to the current item.
     * @brief childItems List of child items.
     */
    QList<FileModelItem*> childItems;
    /**
     * Dynamic array containing data entries for current item.
     * @brief itemData Vector of data entries.
     */
    QVector<QVariant> itemData;
    /**
     * Pointer to parent item. This is null if the item is a root node.
     * @brief parentItem Pointer to parent item.
     */
    FileModelItem *parentItem;
};

class FileModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    FileModel(const QStringList &headers, QObject *parent = 0);
    ~FileModel();

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    FileModelItem* getItem(const QModelIndex &index) const;
    /**
     * Root item of the data model.
     * @brief rootItem Root of model.
     */
    FileModelItem* rootItem;
};

#endif // FILEMODEL_H
