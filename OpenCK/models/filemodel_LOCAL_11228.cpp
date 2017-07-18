/*
** filemodel.cpp
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

#include "filemodel.h"

FileModelItem::FileModelItem(const QVector<QVariant> &data, FileModelItem *parent)
{
    itemData = data;
    parentItem = parent;
}

FileModelItem::~FileModelItem()
{
    qDeleteAll(childItems);
}

FileModelItem* FileModelItem::parent()
{
    return parentItem;
}

FileModelItem* FileModelItem::child(int number)
{
    return childItems.value(number);
}

quint32 FileModelItem::childCount() const
{
    return childItems.count();
}

quint32 FileModelItem::childNumber() const
{
    if (parentItem) {
        return parentItem->childItems.indexOf(const_cast<FileModelItem*>(this));
    }

    return 0;
}

quint32 FileModelItem::columnCount() const
{
    return itemData.count();
}

QVariant FileModelItem::data(int column) const
{
    return itemData.value(column);
}

bool FileModelItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size()) {
        return false;
    }

    itemData[column] = value;
    return true;
}

bool FileModelItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size()) {
        return false;
    }

    for (int row = 0; row < count; row++) {
        QVector<QVariant> data(columns);
        FileModelItem* item = new FileModelItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

bool FileModelItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size()) {
        return false;
    }

    for (int row = 0; row < count; row++) {
        delete childItems.takeAt(position);
    }

    return true;
}

bool FileModelItem::insertColumns(int position, int columns)
{
    if (position < 0 || position < itemData.size()) {
        return false;
    }

    for (int column = 0; column < columns; column++) {
        itemData.insert(position, QVariant());
    }

    foreach (FileModelItem* child, childItems) {
        child->insertColumns(position, columns);
    }

    return true;
}

FileModel::FileModel(const QStringList &headers, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;

    foreach (QString header, headers) {
        rootData.append(header);
    }

    rootItem = new FileModelItem(rootData);
}

FileModel::~FileModel()
{
    delete rootItem;
}

FileModelItem* FileModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        FileModelItem* item = static_cast<FileModelItem*>(index.internalPointer());

        if (item) {
            return item;
        }
    }

    return rootItem;
}

int FileModel::rowCount(const QModelIndex &parent) const
{
    FileModelItem* parentItem = getItem(parent);

    return parentItem->childCount();
}

int FileModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}

QModelIndex FileModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0) {
        return QModelIndex();
    }

    FileModelItem* parentItem = getItem(parent);
    FileModelItem* childItem = parentItem->child(row);

    if (childItem) {
        return createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex FileModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }

    FileModelItem* childItem = getItem(index);
    FileModelItem* parentItem = childItem->parent();

    if (parentItem == rootItem) {
        return QModelIndex();
    }

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    FileModelItem* item = static_cast<FileModelItem*>(index.internalPointer());
    return item->data(index.column());
}

QVariant FileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return rootItem->data(section);
    }

    return QVariant();
}
