/*
** formmodel.cpp
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
** Created Date: 26-Jul-2017
*/

#include "formmodel.h"
#include "parser.h"

//!@file filemodel.cpp Source for the File Model and its respective items.

/**
 * Initialise FileModelItem with specified data and parent pointer.
 * Parent is 0 if the item is a root node.
 * @brief Initialise FileModelItem.
 * @param data Data that items will contain.
 * @param parent Pointer to parent item.
 */
FormModelItem::FormModelItem(const QVector<QVariant> &data, FormModelItem* parent)
{
    itemData = data;
    parentItem = parent;
}

/**
 * Recursively delete all child items.
 * @brief Destructor. Delete all children.
 */
FormModelItem::~FormModelItem()
{
    qDeleteAll(childItems);
}

/**
 * Returns a pointer to the parent item of the current node.
 * @brief Return the parent item.
 * @return Pointer to parent item.
 */
FormModelItem* FormModelItem::parent()
{
    return parentItem;
}

/**
 * Returns a pointer to a specified child item of the current node.
 * @brief Returns a child item.
 * @param number The column number of the requested child item.
 * @return Pointer to child item.
 */
FormModelItem* FormModelItem::child(int number)
{
    return childItems.value(number);
}

/**
 * Returns the number of child items belonging to the current node.
 * @brief Returns number of children.
 * @return Number of children.
 */
int FormModelItem::childCount() const
{
    return childItems.count();
}

/**
 * Returns a pointer to a specified child of the current node.
 * @brief Returns a child item.
 * @return Child item at specified column.
 */
int FormModelItem::childNumber() const
{
    if (parentItem) {
        return parentItem->childItems.indexOf(const_cast<FormModelItem*>(this));
    }

    return 0;
}

/**
 * Returns the number of columns in the data model.
 * @brief Returns number of columns.
 * @return The number of colums in the data model.
 */
int FormModelItem::columnCount() const
{
    return itemData.count();
}

/**
 * Returns the data of an item at the specified column.
 * @brief Returns data contained in one column.
 * @param column The column to retrieve data from.
 * @return Data contained in specified column of the item.
 */
QVariant FormModelItem::data(int column) const
{
    return itemData.value(column);
}

/**
 * Set data of the item in a specified column.
 * @brief Set data in a certain column.
 * @param column Column in which data is set.
 * @param value Data to be set.
 * @return Confirmation of data change.
 */
bool FormModelItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size()) {
        return false;
    }

    itemData[column] = value;
    return true;
}

/**
 * Add a number of children to the item.
 * @brief Add children to the item.
 * @param position Determines where to start adding child items.
 * @param count Number of items to add.
 * @param columns Number of columns that children will contain.
 * @return True if successful, false otherwise.
 */
bool FormModelItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size()) {
        return false;
    }

    for (int row = 0; row < count; row++) {
        QVector<QVariant> data(columns);
        FormModelItem* item = new FormModelItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

/**
 * Removes a number of children from the item.
 * @brief Remove children.
 * @param position Position at which to start removing children.
 * @param count Number of children to remove.
 * @return True if successful, false otherwise.
 */
bool FormModelItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size()) {
        return false;
    }

    for (int row = 0; row < count; row++) {
        delete childItems.takeAt(position);
    }

    return true;
}

/**
 * Add columns to the entire model recursively.
 * @brief Add columns to model.
 * @param position Position at which to insert columns.
 * @param columns Number of columns to add.
 * @return True if successful, false otherwise.
 */
bool FormModelItem::insertColumns(int position, int columns)
{
    if (position < 0 || position < itemData.size()) {
        return false;
    }

    for (int column = 0; column < columns; column++) {
        itemData.insert(position, QVariant());
    }

    foreach (FormModelItem* child, childItems) {
        child->insertColumns(position, columns);
    }

    return true;
}

/**
 * Removes columns from a FileModelItem.
 * @brief Remove columns from model.
 * @param position Position at which to remove columns.
 * @param columns Number of columns to remove.
 * @return True if successful, false otherwise.
 */
bool FormModelItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size()) {
        return false;
    }

    for (int column = 0; column < columns; column++) {
        itemData.remove(position);
    }

    foreach (FormModelItem *child, childItems) {
        child->removeColumns(position, columns);
    }

    return true;
}

/**
 * Initialise a new FileModel with headers.
 * @brief Initialise a FileModel.
 * @param headers Headers to insert into model.
 * @param parent Parent QAbstractItemModel to inherit from.
 */
FormModel::FormModel(const QStringList &headers, QObject* parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;

    foreach (QString header, headers) {
        rootData.append(header);
    }

    rootItem = new FormModelItem(rootData);
}

/**
 * Destructor. Delete root item and all others recursively.
 * @brief Delete root item on destruction.
 */
FormModel::~FormModel()
{
    delete rootItem;
}

/**
 * Returns the item at a given index.
 * @brief FileModel::getItem Retrieve an item.
 * @param index Index to specify item.
 * @return Item at given index.
 */
FormModelItem* FormModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        FormModelItem* item = static_cast<FormModelItem*>(index.internalPointer());

        if (item) {
            return item;
        }
    }

    return rootItem;
}

/**
 * Return the number of rows in an item.
 * @brief FileModel::rowCount Return number of rows.
 * @param parent Index of a model item.
 * @return Count of rows in model.
 */
int FormModel::rowCount(const QModelIndex &parent) const
{
    FormModelItem* parentItem = getItem(parent);

    return parentItem->childCount();
}

/**
 * Return the number of columns in the model.
 * @brief Return number of columns.
 * @return Number of columns.
 */
int FormModel::columnCount(const QModelIndex &/*parent*/) const
{
    return rootItem->columnCount();
}

/**
 * Return the index of an item in the model.
 * @brief Return the index of an item.
 * @param row Row of desired item.
 * @param column Column of desired item.
 * @param parent Parent of desired item.
 * @return Index of a specified item.
 */
QModelIndex FormModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0) {
        return QModelIndex();
    }

    FormModelItem* parentItem = getItem(parent);
    FormModelItem* childItem = parentItem->child(row);

    if (childItem) {
        return createIndex(row, column, childItem);
    }

    return QModelIndex();
}

/**
 * Return the parent of a specified item at an index.
 * @brief FileModel::parent Return a parent item.
 * @param index Index of the selected item.
 * @return Parent of the selected item.
 */
QModelIndex FormModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }

    FormModelItem* childItem = getItem(index);
    FormModelItem* parentItem = childItem->parent();

    if (parentItem == rootItem) {
        return QModelIndex();
    }

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

/**
 * Return the data of a specified item.
 * @brief Return item data.
 * @param index Index of a desired item.
 * @param role DisplayRole of a desired item.
 * @return Item data.
 */
QVariant FormModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    FormModelItem* item = static_cast<FormModelItem*>(index.internalPointer());
    return item->data(index.column());
}

/**
 * Returns the data contained within the header of the model.
 * @brief Return header data.
 * @param section Header section.
 * @param orientation Orientation of model.
 * @param role DisplayRole of index.
 * @return Header data at position.
 */
QVariant FormModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return rootItem->data(section);
    }

    return QVariant();
}

/**
 * Insert columns into the FileModel.
 * @brief Insert columns into the data model.
 * @param position Position at which to insert columns.
 * @param columns Number of columns to insert.
 * @param parent Index at which to insert columns.
 * @return True if successful, false otherwise.
 */
bool FormModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

/**
 * Insert rows into the FileModel at a specified position.
 * @brief Insert rows into data model.
 * @param position Position at which to start inserting rows.
 * @param rows Number of rows to insert.
 * @param parent Index at which to insert rows.
 * @return True if successful, false otherwise.
 */
bool FormModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    FormModelItem* parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

/**
 * Remove a specified number of columns from the FileModel.
 * @brief Remove columns from model.
 * @param position Position at which to remove columns.
 * @param columns Number of columns to remove.
 * @param parent Parent item to remove columns from.
 * @return True if successful, false otherwise.
 */
bool FormModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0) {
        removeRows(0, rowCount());
    }

    return success;
}

/**
 * Remove a number of rows from the FileModel.
 * @brief Remove rows from the model.
 * @param position Row to begin removal.
 * @param rows Number of rows to remove.
 * @param parent Parent item to remove rows from.
 * @return True if successful, false otherwise.
 */
bool FormModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    FormModelItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

/**
 * Display the data of any form as entries in the tree model.
 * @brief Display the data of a form in the model.
 * @param form Form to be read.
 */
void FormModel::readForm(Form *form, QString name)
{
    if (rowCount() > 0) {
        removeRows(0, rowCount());
    }

    rootItem->setData(1, name);
    readFormHeader(&form->getHeader());

    switch (form->getType()) {
        case 'TES4':
            readTES4((TES4Form*)form);
            break;
        case 'GMST':
            readGMST((GMSTForm*)form);
            break;
        case 'KYWD':
            readKYWD((KYWDForm*)form);
            break;
    }
}

/**
 * Display the data of a form header as entries in the tree model.
 * @brief Display a form header in the model.
 * @param header Form header.
 */
void FormModel::readFormHeader(FormHeader* header)
{
    rootItem->insertChildren(rootItem->childCount(), 1, 2);
    FormModelItem* parentItem = rootItem->child(rootItem->childCount() - 1);
    parentItem->setData(0, QString("Record Header"));
    parentItem->insertChildren(parentItem->childCount(), 6, 2);
    QStringList formData;
    formData << "Data Size (Bytes)" << "Flags" << "ID" << "Revision" << "Version" << "Unknown Integer";

    for (int i = 0; i < 6; i++) {
        FormModelItem* item = parentItem->child(i);
        item->setData(0, formData[i]);

        QString columnData;

        switch (i) {
            case 0:
                columnData = QString::number((uint)header->dataSize);
                break;
            case 1:
                columnData = QString::number((uint)header->flags, 16);

                while (columnData.length() < 8) {
                    columnData.insert(0, "0");
                }

                //TODO: Refactor into own record
                for (int i = 7; i >= 0; i--) {
                    switch (i) {
                        case 1:
                            if (columnData[i] == '4') {
                                item->insertChildren(item->childCount(), 1, 2);
                                FormModelItem* newItem = item->child(item->childCount() - 1);
                                newItem->setData(0, "NavMesh Gen — Filter");
                            } else if (columnData[i] == '8') {
                                item->insertChildren(item->childCount(), 1, 2);
                                FormModelItem* newItem = item->child(item->childCount() - 1);
                                newItem->setData(0, "NavMesh Gen — Bounding Box");
                            }
                            break;
                        case 2:
                            if (columnData[i] == '8') {
                                item->insertChildren(item->childCount(), 1, 2);
                                FormModelItem* newItem = item->child(item->childCount() - 1);
                                newItem->setData(0, "Is Marker");
                            }
                            break;
                        case 3:
                            if (columnData[i] == '4') {
                                item->insertChildren(item->childCount(), 1, 2);
                                FormModelItem* newItem = item->child(item->childCount() - 1);
                                newItem->setData(0, "Compressed Data");
                            } else if (columnData[i] == '8') {
                                item->insertChildren(item->childCount(), 1, 2);
                                FormModelItem* newItem = item->child(item->childCount() - 1);
                                newItem->setData(0, "Cannot Wait");
                            }
                            break;
                        case 4:
                            if (columnData[i] == '1') {
                                item->insertChildren(item->childCount(), 1, 2);
                                FormModelItem* newItem = item->child(item->childCount() - 1);
                                newItem->setData(0, "Ignored");
                            } else if (columnData[i] == '8') {
                                item->insertChildren(item->childCount(), 1, 2);
                                FormModelItem* newItem = item->child(item->childCount() - 1);
                                newItem->setData(0, "Visible When Distant");
                            }
                            break;
                        case 5:
                            if (columnData[i] == '8') {
                                item->insertChildren(item->childCount(), 1, 2);
                                FormModelItem* newItem = item->child(item->childCount() - 1);
                                newItem->setData(0, "Initially Disabled");
                            }
                            break;
                        case 6:
                            if (columnData[i] == '2') {
                                item->insertChildren(item->childCount(), 1, 2);
                                FormModelItem* newItem = item->child(item->childCount() - 1);
                                newItem->setData(0, "Deleted");
                            } else if (columnData[i] == '8') {
                                item->insertChildren(item->childCount(), 1, 2);
                                FormModelItem* newItem = item->child(item->childCount() - 1);
                                newItem->setData(0, "Localized");
                            }
                            break;
                        case 7:
                            if (columnData[i] == '1') {
                                item->insertChildren(item->childCount(), 1, 2);
                                FormModelItem* newItem = item->child(item->childCount() - 1);
                                newItem->setData(0, "Master");
                            }
                            break;
                    }
                }

                columnData.insert(0, "0x");

                break;
            case 2:
                columnData = QString::number((uint)header->id);
                break;
            case 3:
                columnData = QString::number((uint)header->revision);
                break;
            case 4:
                columnData = QString::number((uint)header->version);
                break;
            case 5:
                columnData = QString::number((uint)header->unknown);
                break;
        }

        item->setData(1, columnData);
    }
}

/**
 * Display the data of a TES4 record as entries in the tree model.
 * @brief Display a TES4 record.
 * @param Record to be read.
 */
void FormModel::readTES4(TES4Form* TES4)
{
    FormModelItem* item;
    rootItem->insertChildren(rootItem->childCount(), 1, 2);
    item = rootItem->child(rootItem->childCount() - 1);
    item->setData(0, "HEDR — File Header");

    item->insertChildren(item->childCount(), 3, 2);

    for (quint8 i = 3; i > 0; i--) {
        FormModelItem* newItem = item->child(item->childCount() - i);

        switch (i) {
            case 1:
                newItem->setData(0, "Next Object ID");
                newItem->setData(1, QString::number((ulong)TES4->getNextID()));
                break;
            case 2:
                newItem->setData(0, "Number of Records");
                newItem->setData(1, QString::number((int)TES4->getNumRecords()));
                break;
            case 3:
                newItem->setData(0, "Version");
                newItem->setData(1, QString::number((float)TES4->getTES4Version()));
                break;
        }
    }

    rootItem->insertChildren(rootItem->childCount(), 1, 2);
    item = rootItem->child(rootItem->childCount() - 1);
    item->setData(0, "CNAM — Author");

    if (TES4->getAuthor() != nullptr) {
        item->insertChildren(item->childCount(), 1, 2);
        FormModelItem* newItem = item->child(item->childCount() - 1);
        newItem->setData(0, "Author");
        newItem->setData(1, TES4->getAuthor());
    }

    rootItem->insertChildren(rootItem->childCount(), 1, 2);
    item = rootItem->child(rootItem->childCount() - 1);
    item->setData(0, "SNAM — Description");

    if (TES4->getDesc() != nullptr) {
        item->insertChildren(item->childCount(), 1, 2);
        FormModelItem* newItem = item->child(item->childCount() - 1);
        newItem->setData(0, "Description");
        newItem->setData(1, TES4->getDesc());
    }

    rootItem->insertChildren(rootItem->childCount(), 1, 2);
    item = rootItem->child(rootItem->childCount() - 1);
    item->setData(0, "Master Files");

    QMapIterator<QString, quint64> i(TES4->getMasters());
    while (i.hasNext()) {
        i.next();
        item->insertChildren(item->childCount(), 1, 2);
        FormModelItem* newItem = item->child(item->childCount() - 1);
        newItem->setData(0, i.key());
        newItem->setData(1, QString::number((uint)i.value()));
    }

    rootItem->insertChildren(rootItem->childCount(), 1, 2);
    item = rootItem->child(rootItem->childCount() - 1);
    item->setData(0, "ONAM — Overrides");

    for (int i = 0; i < TES4->getOverrides().length(); i++) {
        item->insertChildren(item->childCount(), 1, 2);
        FormModelItem* newItem = item->child(item->childCount() - 1);
        newItem->setData(0, QString::number((uint)TES4->getOverrides()[i]));
    }

    rootItem->insertChildren(rootItem->childCount(), 1, 2);
    item = rootItem->child(rootItem->childCount() - 1);
    item->setData(0, "INTV — Internal Version");

    if (TES4->getIntv() != 0) {
        item->insertChildren(item->childCount(), 1, 2);
        FormModelItem* newItem = item->child(item->childCount() - 1);
        newItem->setData(0, "Internal Version");
        newItem->setData(1, QString::number((uint)TES4->getIntv()));
    }

    rootItem->insertChildren(rootItem->childCount(), 1, 2);
    item = rootItem->child(rootItem->childCount() - 1);
    item->setData(0, "INTCC — Unknown Integer");

    if (TES4->getIncc() != 0) {
        item->insertChildren(item->childCount(), 1, 2);
        FormModelItem* newItem = item->child(item->childCount() - 1);
        newItem->setData(0, "Unknown Integer");
        newItem->setData(1, QString::number((uint)TES4->getIncc()));
    }
}

/**
 * Reads a game settings form.
 * @brief Reads a game settings form.
 * @param GMST The game settings form to read.
 */
void FormModel::readGMST(GMSTForm* GMST)
{
    FormModelItem* item;
    rootItem->insertChildren(rootItem->childCount(), 2, 2);
    item = rootItem->child(rootItem->childCount() - 2);
    item->setData(0, "EDID — Editor ID");
    item->insertChildren(item->childCount(), 1, 2);

    FormModelItem* newItem = item->child(item->childCount() - 1);
    newItem->setData(0, "Editor ID");
    newItem->setData(1, GMST->getEditorID());

    item = rootItem->child(rootItem->childCount() - 1);
    item->setData(0, "DATA — Value");
    item->insertChildren(item->childCount(), 1, 2);

    newItem = item->child(item->childCount() - 1);
    newItem->setData(0, "Value");

    char prefix = GMST->getEditorID().at(0).toLatin1();

    if (prefix == 'b' && GMST->getValueUInt()) {
        bool result = (GMST->getValueUInt() != 0);

        if (result) {
            newItem->setData(1, "True");
        } else {
            newItem->setData(1, "False");
        }
    } else if (prefix == 'i') {
        newItem->setData(1, QString::number((uint)GMST->getValueUInt()));
    } else if (prefix == 'f') {
        newItem->setData(1, QString::number((float)GMST->getValueFloat()));
    } else if (prefix == 's') {
        //TODO: String table lookup
        newItem->setData(1, "Localised String: ["
            + QString::number((uint)GMST->getValueUInt()) + "]");
    }
}

void FormModel::readKYWD(KYWDForm* KYWD)
{
    FormModelItem* item;
    rootItem->insertChildren(rootItem->childCount(), 2, 2);
    item = rootItem->child(rootItem->childCount() - 2);
    item->setData(0, "EDID — Editor ID");
    item->insertChildren(item->childCount(), 1, 2);

    FormModelItem* newItem = item->child(item->childCount() - 1);
    newItem->setData(0, "Editor ID");
    newItem->setData(1, KYWD->getEditorID());

    item = rootItem->child(rootItem->childCount() - 1);
    item->setData(0, "CNAM — RGB(?)");
    item->insertChildren(item->childCount(), 1, 2);

    newItem = item->child(item->childCount() - 1);
    newItem->setData(0, "Value");
    newItem->setData(1, "0x" + QString::number((quint32)KYWD->getRgb(), 16));
}
