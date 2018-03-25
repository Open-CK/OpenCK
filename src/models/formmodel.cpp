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

#include <models/formmodel.h>
#include <io/parser.h>
#include <data/formcomponents.h>

//!@file filemodel.cpp Source for the File Model and its respective items.

namespace models
{
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
     * Clear the model to display contents of another form.
     * @brief Clear and reformat the model.
     * @param form Form to be displayed.
     * @param name Form description.
     */
    void FormModel::formatModel(const esx::Form& form, const QString name)
    {
        if (rowCount() > 0) {
            this->removeRows(0, rowCount());
        }

        rootItem->setData(0, "Record");
        rootItem->setData(1, name);

        if (form.getHeader().getName() != esx::FormName::TES4) {
            this->readFormHeader(&form.getHeader());
        }
    }

    /**
     * Display the data of a form header as entries in the tree model.
     * @brief Display a form header in the model.
     * @param header Form header.
     */
    void FormModel::readFormHeader(const esx::FormHeader* header)
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
                    columnData = QString::number((uint)header->getDataSize());
                    break;
                case 1:
                    columnData = QString::number((uint)header->getFlags(), 16);

                    while (columnData.length() < 8) {
                        columnData.insert(0, "0");
                    }

                    //TODO: Refactor into own method
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
                    columnData = QString::number((uint)header->getID());
                    break;
                case 3:
                    columnData = QString::number((uint)header->getRevision());
                    break;
                case 4:
                    columnData = QString::number((uint)header->getVersion());
                    break;
                case 5:
                    columnData = QString::number((uint)header->getUnknown());
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
    void FormModel::readTES4(esx::TES4Form& TES4)
    {
        this->formatModel(TES4, "File Header");

        FormModelItem* item;
        rootItem->insertChildren(0, 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "HEDR — File Header");

        item->insertChildren(item->childCount(), 3, 2);

        for (quint8 i = 3; i > 0; i--) {
            FormModelItem* newItem = item->child(item->childCount() - i);

            switch (i) {
                case 1:
                    newItem->setData(0, "Next Object ID");
                    newItem->setData(1, QString::number((ulong)TES4.getNextID()));
                    break;
                case 2:
                    newItem->setData(0, "Number of Records");
                    newItem->setData(1, QString::number((int)TES4.getNumRecords()));
                    break;
                case 3:
                    newItem->setData(0, "Version");
                    newItem->setData(1, QString::number((float)TES4.getVersion()));
                    break;
            }
        }

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "CNAM — Author");

        if (TES4.getAuthor() != nullptr) {
            item->insertChildren(item->childCount(), 1, 2);
            FormModelItem* newItem = item->child(item->childCount() - 1);
            newItem->setData(0, "Author");
            newItem->setData(1, TES4.getAuthor());
        }

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "SNAM — Description");

        if (TES4.getDesc() != nullptr) {
            item->insertChildren(item->childCount(), 1, 2);
            FormModelItem* newItem = item->child(item->childCount() - 1);
            newItem->setData(0, "Description");
            newItem->setData(1, TES4.getDesc());
        }

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Master Files");

        QMapIterator<QString, quint64> i(TES4.getMasters());
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

        for (int i = 0; i < TES4.getOverrides().length(); i++) {
            item->insertChildren(item->childCount(), 1, 2);
            FormModelItem* newItem = item->child(item->childCount() - 1);
            newItem->setData(0, QString::number((uint)TES4.getOverrides()[i]));
        }

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "INTV — Internal Version");

        if (TES4.getIntv() != 0) {
            item->insertChildren(item->childCount(), 1, 2);
            FormModelItem* newItem = item->child(item->childCount() - 1);
            newItem->setData(0, "Internal Version");
            newItem->setData(1, QString::number((uint)TES4.getIntv()));
        }

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "INTCC — Unknown Integer");

        if (TES4.getIncc() != 0) {
            item->insertChildren(item->childCount(), 1, 2);
            FormModelItem* newItem = item->child(item->childCount() - 1);
            newItem->setData(0, "Unknown Integer");
            newItem->setData(1, QString::number((uint)TES4.getIncc()));
        }
    }

    /**
     * Reads a game settings form.
     * @brief Reads a game settings form.
     * @param GMST The game settings form to read.
     */
    void FormModel::readGMST(esx::GameSettingForm& GMST)
    {
        this->formatModel(GMST, "Game Setting");

        FormModelItem* item;
        rootItem->insertChildren(rootItem->childCount(), 2, 2);
        item = rootItem->child(rootItem->childCount() - 2);
        item->setData(0, "EDID — Editor ID");
        item->insertChildren(item->childCount(), 1, 2);

        FormModelItem* newItem = item->child(item->childCount() - 1);
        newItem->setData(0, "Editor ID");
        newItem->setData(1, GMST.getEditorID());

        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "DATA — Value");
        item->insertChildren(item->childCount(), 1, 2);

        newItem = item->child(item->childCount() - 1);
        newItem->setData(0, "Value");

        char prefix = GMST.getEditorID().at(0).toLatin1();

        if (prefix == 'b' && GMST.getValueUInt()) {
            bool result = (GMST.getValueUInt() != 0);

            if (result) {
                newItem->setData(1, "True");
            } else {
                newItem->setData(1, "False");
            }
        } else if (prefix == 'i') {
            newItem->setData(1, QString::number((uint)GMST.getValueUInt()));
        } else if (prefix == 'f') {
            newItem->setData(1, QString::number((float)GMST.getValueFloat()));
        } else if (prefix == 's') {
            //TODO: String table lookup
            newItem->setData(1, "Localised String: ["
                + QString::number((uint)GMST.getValueUInt()) + "]");
        }
    }

    /**
     * Display the data of a RGB record as entries in the tree model.
     * @brief Display a RGB record.
     * @param Record to be read.
     */
    void FormModel::readRGB(esx::RgbForm& RGB)
    {
        QString name("");
        using esx::FormName;

        switch (RGB.getHeader().getName()) {
            case FormName::Keyword:
                name = "Keyword";
                break;
            case FormName::Action:
                name = "Action";
                break;
            case FormName::LocationReferenceType:
                name = "Location Reference Type";
                break;
        }

        this->formatModel(RGB, name);

        FormModelItem* item;
        rootItem->insertChildren(rootItem->childCount(), 2, 2);
        item = rootItem->child(rootItem->childCount() - 2);
        item->setData(0, "EDID — Editor ID");
        item->insertChildren(item->childCount(), 1, 2);

        FormModelItem* newItem = item->child(item->childCount() - 1);
        newItem->setData(0, "Editor ID");
        newItem->setData(1, RGB.getEditorID());

        if (quint32(RGB.getEditorID().length() + 1) + 6 < RGB.getHeader().getDataSize()){
            item = rootItem->child(rootItem->childCount() - 1);
            item->setData(0, "CNAM — RGBA");
            item->insertChildren(item->childCount(), 1, 2);

            QString rgb = QString::number(RGB.getRgb(), 16).toUpper().prepend("0x");
            while (rgb.length() < 10) {
                rgb.insert(2, "0");
            }
            item->child(0)->setData(0, "RGBA");
            item->child(0)->setData(1, rgb);
        }
    }

    /**
     * Display the data of a TXST record as entries in the tree model.
     * @brief Display a TXST record.
     * @param Record to be read.
     */
    void FormModel::readTXST(esx::TextureSetForm& TXST)
    {
        this->formatModel(TXST, "Texture Set");

        FormModelItem* item;
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "EDID — Editor ID");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Editor ID");
        item->setData(1, TXST.getEditorID());

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "OBND — Object Bounds");
        item->insertChildren(item->childCount(), 6, 2);

        FormModelItem* newItem = item->child(item->childCount() - 6);
        newItem->setData(0, "Min X");
        newItem->setData(1, TXST.getObjectBounds().xmin);
        newItem = item->child(item->childCount() - 5);
        newItem->setData(0, "Min Y");
        newItem->setData(1, TXST.getObjectBounds().ymin);
        newItem = item->child(item->childCount() - 4);
        newItem->setData(0, "Min Z");
        newItem->setData(1, TXST.getObjectBounds().zmin);
        newItem = item->child(item->childCount() - 3);
        newItem->setData(0, "Max X");
        newItem->setData(1, TXST.getObjectBounds().xmax);
        newItem = item->child(item->childCount() - 2);
        newItem->setData(0, "Max Y");
        newItem->setData(1, TXST.getObjectBounds().ymax);
        newItem = item->child(item->childCount() - 1);
        newItem->setData(0, "Max Z");
        newItem->setData(1, TXST.getObjectBounds().zmax);

        quint8 childNum = 0;
        quint8 childIndices[8];

        for (int i = 0; i < 8; i++) {
            if (TXST.getPath(i) != 0) {
                childIndices[childNum] = i;
                childNum++;
            }
        }

        rootItem->insertChildren(rootItem->childCount(), childNum, 2);
        QString pathName;

        for (int i = 0; i < childNum; i++) {
            switch(childIndices[i]) {
                case 0:
                    pathName = "TX00 — Color Map";
                    break;
                case 1:
                    pathName = "TX01 — Normal Map";
                    break;
                case 2:
                    pathName = "TX02 — Environment/Glow Mask";
                    break;
                case 3:
                    pathName = "TX03 — Glow/Skin Map";
                    break;
                case 4:
                    pathName = "TX04 — Detail Map";
                    break;
                case 5:
                    pathName = "TX05 — Environment Map";
                    break;
                case 6:
                    pathName = "TX06 — Unknown Texture Map";
                    break;
                case 7:
                    pathName = "TX07 — Specularity Map";
                    break;
            }

            item = rootItem->child(3 + i);
            item->setData(0, pathName);
            item->insertChildren(0, 1, 2);
            item = item->child(item->childCount() - 1);
            item->setData(0, "File Path");
            item->setData(1, TXST.getPath(childIndices[i]));
        }

        if (TXST.hasDODT()) {
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            item = rootItem->child(rootItem->childCount() - 1);
            item->setData(0, "DODT — Decal Data");

            item->insertChildren(0, 11, 2);

            for (int i = 0; i < 11; i++) {
                newItem = item->child(i);

                QString varName("");
                QVariant varValue = 0;

                switch(i) {
                    case 0:
                        varName = "Min Width";
                        varValue = TXST.getDecalData().minWidth;
                        break;
                    case 1:
                        varName = "Max Width";
                        varValue = TXST.getDecalData().maxWidth;
                        break;
                    case 2:
                        varName = "Min Height";
                        varValue = TXST.getDecalData().minHeight;
                        break;
                    case 3:
                        varName = "Max Height";
                        varValue = TXST.getDecalData().maxHeight;
                        break;
                    case 4:
                        varName = "Depth";
                        varValue = TXST.getDecalData().depth;
                        break;
                    case 5:
                        varName = "Shininess";
                        varValue = TXST.getDecalData().shininess;
                        break;
                    case 6:
                        varName = "Parallax Scale";
                        varValue = TXST.getDecalData().parallaxScale;
                        break;
                    case 7:
                        varName = "Parallax Passes";
                        varValue = TXST.getDecalData().parallaxPasses;
                        break;
                    case 8: {
                        varName = "Flags";
                        QString varString = QString::number(TXST.getDecalData().flags, 16).prepend("0x");
                        while (varString.length() < 6) {
                            varString.insert(2, "0");
                        }
                        varValue = varString;
                        break;
                    }
                    case 9:
                        varName = "Unknown Bytes — [2]";
                        varValue = "";
                        newItem->insertChildren(0, 2, 2);
                        newItem->child(0)->setData(0, "[0]");
                        newItem->child(0)->setData(1, TXST.getDecalData().unknown[0]);
                        newItem->child(1)->setData(0, "[1]");
                        newItem->child(1)->setData(1, TXST.getDecalData().unknown[1]);
                        break;
                    case 10:
                        varName = "RGBA — Color";
                        varValue = "";
                        newItem->insertChildren(0, 1, 2);
                        newItem->child(0)->setData(0, "RGBA");

                        QString rgbHex("");
                        rgbHex = QString::number(TXST.getDecalData().color, 16).toUpper().prepend("0x");
                        while (rgbHex.length() < 10) {
                            rgbHex.insert(2, "0");
                        }
                        newItem->child(0)->setData(1, rgbHex);
                        break;
                }

                newItem->setData(0, varName);
                newItem->setData(1, varValue);
            }
        }

        if (TXST.hasTextureFlags()) {
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            item = rootItem->child(rootItem->childCount() - 1);
            item->setData(0, "DNAM — Texture Flags");

            item->insertChildren(0, 1, 2);
            item->child(0)->setData(0, "Flags");
            QString texFlags(QString::number(TXST.getFlags(), 16).toUpper().prepend("0x"));
            while (texFlags.length() < 6) {
                texFlags.insert(2, "0");
            }
            item->child(0)->setData(1, texFlags);
        }
    }

    /**
     * Display the data of a GLOB record as entries in the tree model.
     * @brief Display a GLOB record.
     * @param Record to be read.
     */
    void FormModel::readGLOB(esx::GlobalVariableForm& GLOB)
    {
        this->formatModel(GLOB, "Global Variable");

        FormModelItem* item;
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "EDID — Editor ID");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Editor ID");
        item->setData(1, GLOB.getEditorID());

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "FNAM — Data Type");
        item->insertChildren(item->childCount(), 1, 2);
        QString type;
        QString value;

        switch(GLOB.getType()) {
            case 's':
                type = "short (int16)";
                value = QString::number((int16_t)GLOB.getValue());
                break;
            case 'l':
                type = "long (int32)";
                value = QString::number((int32_t)GLOB.getValue());
                break;
            case 'f':
                type = "float";
                value = QString::number(GLOB.getValue());
                break;
        }

        item->child(0)->setData(0, QString(GLOB.getType()));
        item->child(0)->setData(1, type);

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "FLTV — Data Value");
        item->insertChildren(item->childCount(), 1, 2);
        item->child(0)->setData(0, "Type");
        item->child(0)->setData(1, value);
    }

    /**
     * Display the data of a CLAS record as entries in the tree model.
     * @brief Display a CLAS record.
     * @param Record to be read.
     */
    void FormModel::readCLAS(esx::ClassForm &CLAS)
    {
        this->formatModel(CLAS, "Class");

        FormModelItem* item;
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "EDID — Editor ID");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Editor ID");
        item->setData(1, CLAS.getEditorID());

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "FULL — Class Name");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Name");
        item->setData(1, "Localised String: [" + CLAS.getFullName() + "]");

        if (CLAS.getDesc() != 0) {
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            item = rootItem->child(rootItem->childCount() - 1);
            item->setData(0, "DESC — Class Description");
            item->insertChildren(item->childCount(), 1, 2);

            item = item->child(item->childCount() - 1);
            item->setData(0, "Description");
            item->setData(1, "Localised String: [" + CLAS.getDesc() + "]");
        }

        if (CLAS.getIcon() != 0) {
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            item = rootItem->child(rootItem->childCount() - 1);
            item->setData(0, "ICON — Menu Image");
            item->insertChildren(item->childCount(), 1, 2);

            item = item->child(item->childCount() - 1);
            item->setData(0, "File Path");
            item->setData(1, CLAS.getIcon());
        }

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "DATA — Class Information");
        item->insertChildren(item->childCount(), 10, 2);

        for (int i = 0; i < 10; i++) {
            QString name("");
            QString value("");

            switch (i) {
                case 0:
                    name = "Unknown";
                    value = QString::number(CLAS.getClassData().unknown);
                    break;
                case 1:
                    name = "Training Skill";
                    value = esx::skillIndexes[CLAS.getClassData().trainingSkill];
                    break;
                case 2:
                    name = "Max Training Level";
                    value = QString::number(CLAS.getClassData().trainingLevel);
                    break;
                case 3:
                    name = "Skill Weights";
                    break;
                case 4:
                    name = "Bleedout Default";
                    value = QString::number(CLAS.getClassData().bleedoutDefault);
                    break;
                case 5:
                    name = "Voice Points";
                    value = QString::number(CLAS.getClassData().voicePoints);
                    break;
                case 6:
                    name = "Health Weight";
                    value = QString::number(CLAS.getClassData().healthWeight);
                    break;
                case 7:
                    name = "Magicka Weight";
                    value = QString::number(CLAS.getClassData().magickaWeight);
                    break;
                case 8:
                    name = "Stamina Weight";
                    value = QString::number(CLAS.getClassData().staminaWeight);
                    break;
                case 9:
                    name = "Flags";
                    value = QString::number(CLAS.getClassData().flags, 16).toUpper();
                    value.prepend("0x");
                    while (value.length() < 4) {
                        value.insert(2, "0");
                    }
                    break;
            }

            FormModelItem* newItem;
            newItem = item->child(i);
            newItem->setData(0, name);
            newItem->setData(1, value);

            if (i == 3) {
                newItem->insertChildren(0, 18, 2);
            }
        }

        for (int i = 0; i < 18; i++) {
            QString name("");
            QString value("");

            name = esx::skillIndexes[i];
            value = QString::number(CLAS.getClassData().skillWeights[i]);

            FormModelItem* newItem;
            newItem = item->child(3)->child(i);
            newItem->setData(0, name);
            newItem->setData(1, value);
        }
    }

    /**
    * Display the data of a CLAS record as entries in the tree model.
    * @brief Display a CLAS record.
    * @param Record to be read.
    */
    void FormModel::readFACT(esx::FactionForm& FACT)
    {
        this->formatModel(FACT, "Faction");

        FormModelItem* item;

        // Editor ID
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "EDID — Editor ID");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Editor ID");
        item->setData(1, FACT.getEditorID());

        // Name
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "FULL — Faction Name");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Name");
        item->setData(1, "Localised String: [" + FACT.getFullName() + "]");

        // Interfaction relations
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Relations");

        auto& rel = FACT.getRelations();
        item->insertChildren(item->childCount(), rel.size(), 2);

        for (size_t i = 0; i < rel.size(); i++) {
            auto* relItem = item->child(i);
            auto& relData = rel[i];

            relItem->setData(0, "XNAM - Relation");
            relItem->insertChildren(0, 3, 2);

            // Faction
            auto* factionItem = relItem->child(0);
            factionItem->setData(0, "Faction");
            factionItem->setData(1, QString::number(relData.factionFormID, 16));

            // Modifier
            auto* modifierItem = relItem->child(1);
            modifierItem->setData(0, "Modifier");
            modifierItem->setData(1, relData.mod);

            // Group combat reaction
            auto* gcrItem = relItem->child(2);
            gcrItem->setData(0, "Group Combat Reaction");
            gcrItem->setData(1, relData.combatFlags);
        }

        // Flags

        // Prison marker
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Prison Marker");
        item->setData(1, QString::number(FACT.getPrisonMarker(), 16));

        // Follower wait marker
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Follower Wait Marker");
        item->setData(1, QString::number(FACT.getFollowerWaitMarker(), 16));

        // Evidence chest
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Evidence Chest");
        item->setData(1, QString::number(FACT.getEvidenceChest(), 16));

        // Player belongings chest
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Player Belongings Chest");
        item->setData(1, QString::number(FACT.getBelongingsChest(), 16));

        // Crime group
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Crime Group");
        item->setData(1, QString::number(FACT.getCrimeGroup(), 16));

        // Jail outfit
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Jail Outfit");
        item->setData(1, QString::number(FACT.getJailOutfit(), 16));

        // Crime values
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "CRVA - Crime Gold");
        
        {
            auto& cv = FACT.getGold();
            static const quint32 NUM_GOLD_ITEMS = 10;
            item->insertChildren(0, NUM_GOLD_ITEMS, 2);

            // Arrest
            auto* arrestItem = item->child(0);
            arrestItem->setData(0, "Arrest");
            arrestItem->setData(1, (cv.gold.arrest) ? true : false);

            // Attack on sight
            auto* aosItem = item->child(1);
            aosItem->setData(0, "Attack On Sight");
            aosItem->setData(1, (cv.gold.attack) ? true : false);

            // Murder
            auto* murderItem = item->child(2);
            murderItem->setData(0, "Murder");
            murderItem->setData(1, cv.gold.murder);

            // Assault
            auto* assaultItem = item->child(3);
            assaultItem->setData(0, "Assault");
            assaultItem->setData(1, cv.gold.assault);

            // Trespass
            auto* trespassItem = item->child(4);
            trespassItem->setData(0, "Trespass");
            trespassItem->setData(1, cv.gold.trespass);

            // Pickpocket
            auto* pickpocketItem = item->child(5);
            pickpocketItem->setData(0, "Pickpocket");
            pickpocketItem->setData(1, cv.gold.pickpocket);

            // Unk
            auto* unkItem = item->child(6);
            unkItem->setData(0, "Unknown");
            unkItem->setData(1, cv.gold.unused);

            // Steal Multiplier
            auto* stealmultItem = item->child(7);
            stealmultItem->setData(0, "Steal Multiplier");
            stealmultItem->setData(1, cv.stealMult);

            // Escape
            auto* escapeItem = item->child(8);
            escapeItem->setData(0, "Escape");
            escapeItem->setData(1, cv.escape);

            // Werewolf
            auto* werewolfItem = item->child(9);
            werewolfItem->setData(0, "Werewolf");
            werewolfItem->setData(1, cv.werewolf);
        }

        // Ranks
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Ranks");

        auto& ranks = FACT.getRanks();
        item->insertChildren(item->childCount(), ranks.size(), 2);
        {
            for (auto i = 0; i < ranks.size(); i++) {
                auto* rankItem = item->child(i);
                auto& rankData = ranks[i];

                rankItem->setData(0, "Rank");
                rankItem->insertChildren(0, 3, 2);

                auto* rnamItem = rankItem->child(0);
                rnamItem->setData(0, "Rank ID");
                rnamItem->setData(1, rankData.rankID);

                auto* mnamItem = rankItem->child(1);
                mnamItem->setData(0, "Male Rank Title");
                mnamItem->setData(1, rankData.maleTitle);

                auto* fnamItem = rankItem->child(2);
                fnamItem->setData(0, "Female Rank Title");
                fnamItem->setData(1, rankData.femaleTitle);
            }
        }

        // Vendor list
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Vendor List");
        item->setData(1, QString::number(FACT.getVendorList(), 16));

        // Vender container
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Vendor Chest");
        item->setData(1, QString::number(FACT.getVendorChest(), 16));

        // Vendor Data
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Vendor Data");

        {
            auto& vd = FACT.getVendorData();

            static const quint32 NUM_VENDOR_DATA = 6;
            item->insertChildren(0, NUM_VENDOR_DATA, 2);

            // Start hour
            auto* startHourItem = item->child(0);
            startHourItem->setData(0, "Start Hour");
            startHourItem->setData(1, vd.startHour);

            // End hour
            auto* endHourItem = item->child(1);
            endHourItem->setData(0, "End Hour");
            endHourItem->setData(1, vd.endHour);

            // Radius
            auto* radiusItem = item->child(2);
            radiusItem->setData(0, "Radius");
            radiusItem->setData(1, vd.radius);

            // Only Buys Stolen flag
            auto* buysStolenItem = item->child(3);
            buysStolenItem->setData(0, "Only Buys Stolen");
            buysStolenItem->setData(1, vd.stolenFlag);

            // No buy/sell flag
            auto* nbItem = item->child(4);
            nbItem->setData(0, "NOT Sell/Buy");
            nbItem->setData(1, vd.notSellFlag);

            // Unk
            auto* unkItem = item->child(5);
            unkItem->setData(0, "Unknown");
            unkItem->setData(1, vd.unused);
        }

        // Vendor Location
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Vendor Location");

        {
            auto& vl = FACT.getPlace();

            static const quint32 NUM_PLVD_DATA = 3;
            item->insertChildren(0, NUM_PLVD_DATA, 2);

            auto* typeItem = item->child(0);
            typeItem->setData(0, "Type");
            typeItem->setData(1, vl.typeFlags);

            auto* cellItem = item->child(1);
            cellItem->setData(0, "Cell");
            cellItem->setData(1, QString::number(vl.form, 16));

            auto* radiusItem = item->child(2);
            radiusItem->setData(0, "Radius");
            radiusItem->setData(1, vl.unused);
        }

        // Conditionals.
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "CTDA - Conditions");
    }

    /**
     * Display the data of a EYES record as entries in the tree model.
     * @brief Display a EYES record.
     * @param Record to be read.
     */
    void FormModel::readEYES(esx::EyesForm& EYES)
    {
        this->formatModel(EYES, "Eyes");

        FormModelItem* item;
        // EDID
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "EDID — Editor ID");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Editor ID");
        item->setData(1, EYES.getEditorID());

        // FULL
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "FULL — Description");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Description");
        item->setData(1, EYES.getDesc());

        // ICON
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "ICON — Eye texture");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Path:");
        item->setData(1, EYES.getIcon());

        // ICON
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Data — Flags");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Flags:");
        item->setData(1, EYES.getFlags());
        //TODO: present readable flags
    }

    /**
     * Display the data of a SOUN record as entries in the tree model.
     * @brief Display a SOUN record.
     * @param Record to be read.
     */
    void FormModel::readSOUN(esx::SoundForm& SOUN)
    {
        this->formatModel(SOUN, "Sound");

        FormModelItem* item;
        // EDID
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "EDID — Editor ID");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Editor ID");
        item->setData(1, SOUN.getEditorID());

        //OBND
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "OBND — Object Bounds");
        item->insertChildren(item->childCount(), 6, 2);

        auto* newItem = item->child(item->childCount() - 6);
        newItem->setData(0, "Min X");
        newItem->setData(1, SOUN.getObjectBounds().xmin);
        newItem = item->child(item->childCount() - 5);
        newItem->setData(0, "Min Y");
        newItem->setData(1, SOUN.getObjectBounds().ymin);
        newItem = item->child(item->childCount() - 4);
        newItem->setData(0, "Min Z");
        newItem->setData(1, SOUN.getObjectBounds().zmin);
        newItem = item->child(item->childCount() - 3);
        newItem->setData(0, "Max X");
        newItem->setData(1, SOUN.getObjectBounds().xmax);
        newItem = item->child(item->childCount() - 2);
        newItem->setData(0, "Max Y");
        newItem->setData(1, SOUN.getObjectBounds().ymax);
        newItem = item->child(item->childCount() - 1);
        newItem->setData(0, "Max Z");
        newItem->setData(1, SOUN.getObjectBounds().zmax);

        //SDSC
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "SDSC — Sound Data");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Associated SNDR FormID");
        item->setData(1, QString::number(SOUN.getSoundDataID(), 16).toUpper());
    }

    /**
     * Display the data of a ASPC record as entries in the tree model.
     * @brief Display a ASPC record.
     * @param Record to be read.
     */
    void FormModel::readASPC(esx::AcousticSpaceForm& ASPC)
    {
        this->formatModel(ASPC, "Sound");

        FormModelItem* item;
        // EDID
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "EDID — Editor ID");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Editor ID");
        item->setData(1, ASPC.getEditorID());

        //OBND
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "OBND — Object Bounds");
        item->insertChildren(item->childCount(), 6, 2);

        auto* newItem = item->child(item->childCount() - 6);
        newItem->setData(0, "Min X");
        newItem->setData(1, ASPC.getObjectBounds().xmin);
        newItem = item->child(item->childCount() - 5);
        newItem->setData(0, "Min Y");
        newItem->setData(1, ASPC.getObjectBounds().ymin);
        newItem = item->child(item->childCount() - 4);
        newItem->setData(0, "Min Z");
        newItem->setData(1, ASPC.getObjectBounds().zmin);
        newItem = item->child(item->childCount() - 3);
        newItem->setData(0, "Max X");
        newItem->setData(1, ASPC.getObjectBounds().xmax);
        newItem = item->child(item->childCount() - 2);
        newItem->setData(0, "Max Y");
        newItem->setData(1, ASPC.getObjectBounds().ymax);
        newItem = item->child(item->childCount() - 1);
        newItem->setData(0, "Max Z");
        newItem->setData(1, ASPC.getObjectBounds().zmax);

        if (ASPC.getAmbientSoundID() != 0) {
            // SNAM
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            item = rootItem->child(rootItem->childCount() - 1);
            item->setData(0, "SNAM — Ambient Sound Data");
            item->insertChildren(item->childCount(), 1, 2);

            item = item->child(item->childCount() - 1);
            item->setData(0, "Associated SNDR FormID");
            item->setData(1, QString::number(ASPC.getAmbientSoundID(), 16).toUpper());
        }

        if (ASPC.getRegionSoundID() != 0) {
            // RDAT
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            item = rootItem->child(rootItem->childCount() - 1);
            item->setData(0, "RDAT — Region Sound Data");
            item->insertChildren(item->childCount(), 1, 2);

            item = item->child(item->childCount() - 1);
            item->setData(0, "Associated REGN FormID");
            item->setData(1, QString::number(ASPC.getRegionSoundID(), 16).toUpper());
        }

        if (ASPC.getReverbDataID() != 0) {
            // BNAM
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            item = rootItem->child(rootItem->childCount() - 1);
            item->setData(0, "BNAM — Reverb Sound Data");
            item->insertChildren(item->childCount(), 1, 2);

            item = item->child(item->childCount() - 1);
            item->setData(0, "Associated REVB FormID");
            item->setData(1, QString::number(ASPC.getReverbDataID(), 16).toUpper());
        }
    }

    /**
    * Display the data of a MESG record as entries in the tree model.
    * @brief Display a MESG record.
    * @param Record to be read.
    */
    void FormModel::readMESG(esx::MessageForm& MESG)
    {
        this->formatModel(MESG, "Message");

        FormModelItem* item;
        // EDID
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "EDID — Editor ID");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Editor ID");
        item->setData(1, MESG.getEditorID());

        // DESC
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "DESC — Message Text");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Description");
        item->setData(1, "Localised String: [" + MESG.getMessageText() + "]");

        // FULL
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "FULL — Title");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Name");
        item->setData(1, "Localised String: [" + MESG.getTitle() + "]");

        // INAM
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "INAM — Unknown");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Icon (unused)");
        item->setData(1, MESG.getUnknown());

        // QNAM
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "QNAM — QuestID");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Owner QuestID");
        item->setData(1, MESG.getQuestID());

        // DNAM
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "DNAM — Flags");
        item->insertChildren(item->childCount(), 1, 2);

        if (MESG.getFlags() == 0x01) {
            item = item->child(item->childCount() - 1);
            item->setData(0, "Message Box");
            item->setData(1, "Message Box");
        }
        else if(MESG.getFlags() == 0x02) {
            item = item->child(item->childCount() - 1);
            item->setData(0, "Auto-Display");
            item->setData(1, "Auto-Display");
        }

        // TNAM
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "TNAM — Time");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Display Time");
        item->setData(1, MESG.getTime());

        // CDTA
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "CTDA - Conditions");

        // ITXT
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "ITXT — Response Text");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Response Text");
        item->setData(1, MESG.getResponseText());
    }

    /**
    * Display the data of a ASPC record as entries in the tree model.
    * @brief Display a ASPC record.
    * @param Record to be read.
    */
    void FormModel::readRACE(esx::RaceForm& RACE)
    {
        this->formatModel(RACE, "Race");

        FormModelItem* item;
        // EDID
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "EDID — Editor ID");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Editor ID");
        item->setData(1, RACE.getEditorID());

        // Name
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "FULL — Name");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Name");
        item->setData(1, "Localised String: [" + RACE.getFullName() + "]");

        // DESC
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "DESC — Description");
        item->insertChildren(item->childCount(), 1, 2);

        item = item->child(item->childCount() - 1);
        item->setData(0, "Description");
        item->setData(1, "Localised String: [" + RACE.getDesc() + "]");

        // Spells
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "SPCT - Spell Count");

        quint32 spellCount = RACE.getSpellCount();
        item->setData(1, RACE.getSpellCount());

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Actor Spells");

        item->insertChildren(0, spellCount, 2);
        auto spells = RACE.getSpells();
        for (quint32 i = 0; i < spellCount; i++) {
            auto* childItem = item->child(i);

            childItem->setData(0, "SPLO - Spell");
            childItem->setData(1, QString::number(spells[i], 16));
        }

        // WNAM skin
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "WNAM - Skin");
        item->setData(1, QString::number(RACE.getSkin(), 16));

        // BODT/BOD2
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        auto body = RACE.getBodyTemplate();

        if (body.version == esx::BodyTemplateField::BOD2) {
            item->setData(0, "BOD2");

            item->insertChildren(0, 3, 2);

            auto* flagsItem = item->child(0);
            flagsItem->setData(0, "First Person Flags");
            flagsItem->setData(1, body.bodyPartFlags);

            auto* generalFlagsItem = item->child(1);
            generalFlagsItem->setData(0, "General Flags");
            generalFlagsItem->setData(1, body.flags.bytes[0]);

            auto* armorTypeItem = item->child(2);
            armorTypeItem->setData(0, "Armor Type");
            armorTypeItem->setData(1, body.skill);

        } else {
            item->setData(0, "BODT");
        }

        // Keywords
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "KSIZ - Keyword Count");
        quint32 keywordCount = RACE.getKeywordCount();
        item->setData(1, keywordCount);

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "KWDA - Keywords");

        auto keywords = RACE.getKeywords();
        item->insertChildren(0, keywordCount, 2);
        for (quint32 i = 0; i < keywordCount; i++) {
            auto* childItem = item->child(i);
            auto keyword = keywords[i];

            childItem->setData(0, "Keyword");
            childItem->setData(1, QString::number(keyword, 16));
        }

        // DATA
        auto data = RACE.getData();
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "DATA");

        {
            // Skills
            item->insertChildren(0, 1, 2);
            auto* skillsItem = item->child(item->childCount() - 1);
            skillsItem->setData(0, "Skills");

            quint32 numSkills = data.skills.size();
            skillsItem->insertChildren(0, numSkills, 2);
            for (quint32 i = 0; i < numSkills; i++) {
                auto* skillBoostItem = skillsItem->child(i);
                skillBoostItem->insertChildren(0, 2, 2);

                skillBoostItem->setData(0, "Skill Boost");

                auto* skillItem = skillBoostItem->child(0);
                skillItem->setData(0, "Skill");
                skillItem->setData(1, data.skills[i]);

                auto* boostItem = skillBoostItem->child(1);
                boostItem->setData(0, "Boost");
                boostItem->setData(1, data.racialBonus[i]);
            }

            // Heights
            FormModelItem* childItem{ nullptr };
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Male Height");
            childItem->setData(1, data.maleHeight);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Female Height");
            childItem->setData(1, data.femaleHeight);

            // Weights
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Male Weight");
            childItem->setData(1, data.maleWeight);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Female Weight");
            childItem->setData(1, data.femaleWeight);

            // Flags
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Flags");
            childItem->setData(1, data.flags);

            // Starting stats
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Starting Health");
            childItem->setData(1, data.startingHealth);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Starting Magicka");
            childItem->setData(1, data.startingMagicka);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Starting Stamina");
            childItem->setData(1, data.startingStamina);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Base Carry Weight");
            childItem->setData(1, data.baseCarryWeight);

            // Physics data
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Base Mass");
            childItem->setData(1, data.baseMass);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Acceleration Rate");
            childItem->setData(1, data.accelRate);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Deceleration Rate");
            childItem->setData(1, data.decelRate);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Size");
            childItem->setData(1, data.size);

            // Biped
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Head Biped Object");
            childItem->setData(1, data.headBiped);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Hair Biped Object");
            childItem->setData(1, data.headBiped);

            // Injury
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Injured Health Percentage");
            childItem->setData(1, data.injuredHealthPercentage);

            // Shield biped.
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Shield Biped Object");
            childItem->setData(1, data.shieldBiped);

            // Regen values
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Health Regen");
            childItem->setData(1, data.healthRegen);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Magicka Regen");
            childItem->setData(1, data.magickaRegen);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Stamina Regen");
            childItem->setData(1, data.staminaRegen);

            // Unarmed
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Unarmed Damage");
            childItem->setData(1, data.unarmedDamage);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Unarmed Reach");
            childItem->setData(1, data.unarmedReach);

            // Body Biped
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Body Biped Object");
            childItem->setData(1, data.bodyBiped);

            // Tolerances
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Aim Angle Tolerance");
            childItem->setData(1, data.aimAngleTolerence);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Angular Acceleration Rate");
            childItem->setData(1, data.angularAccelRate);

            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Angular Tolerance");
            childItem->setData(1, data.angularTolerance);

            // Flags 2
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Flags 2");
            childItem->setData(1, data.flags2);

            // Mount data.
            item->insertChildren(item->childCount(), 1, 2);
            childItem = item->child(item->childCount() - 1);
            childItem->setData(0, "Mount Data");
            childItem->insertChildren(0, data.mountData.size(), 2);
            for (quint32 i = 0; i < data.mountData.size(); i++) {
                auto mountItem = childItem->child(i);

                mountItem->setData(0, i);
                mountItem->setData(1, data.mountData[i]);
            }
        }

        // Male skeleton
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Male Skeleton Model");
        item->setData(1, RACE.getMaleModelInfo().model);

        // Female skeleton
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Female Skeleton Model");
        item->setData(1, RACE.getFemaleModelInfo().model);

        // Movement Type Names
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Movement Type Names");

        // Voices
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "VTCK - Voices");

        // Decap armor
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Decapitate Armors");

        // Default hair colors
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Default hair colors");

        // Total tints
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Total number of Tints");
        item->setData(1, RACE.getTintIndexTotal());

        // FaceGen - Main clamp
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "PNAM - FaceGen Main Clamp");
        item->setData(1, RACE.getFaceGenMainClamp());

        // FaceGen - Face clamp
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "UNAM - FaceGen Face Clamp");
        item->setData(1, RACE.getFaceGenFaceClamp());

        // Attack Race
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Attack Race");
        item->setData(1, QString::number(RACE.getAttackRace(), 16));

        // Attacks
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Attacks");

        auto attackData = RACE.getAttackData();
        auto attackEvents = RACE.getAttackEvent();
        item->insertChildren(0, attackData.size(), 2);

        for (quint32 i = 0; i < attackData.size(); i++) {
            auto* childItem = item->child(i);
            childItem->setData(0, "Attack");

            childItem->insertChildren(0, 2, 2);
            // DATA
            {
                auto& data = attackData[i];
                auto* dataItem = childItem->child(0);
                dataItem->setData(0, "ATKD - Attack Data");
                dataItem->insertChildren(0, 11, 2);

                auto* damageMultItem = dataItem->child(0);
                damageMultItem->setData(0, "Damage Mult");
                damageMultItem->setData(1, data.damageMultiplier);

                auto* attackChanceItem = dataItem->child(1);
                attackChanceItem->setData(0, "Attack Chance");
                attackChanceItem->setData(1, data.attackChance);

                auto* attackSpellItem = dataItem->child(2);
                attackSpellItem->setData(0, "Attack Spell");
                attackSpellItem->setData(1, QString::number(data.attackSpell, 16));

                auto* flagsItem = dataItem->child(3);
                flagsItem->setData(0, "Flags");
                flagsItem->setData(1, data.flags);

                auto* attackAngleItem = dataItem->child(4);
                attackAngleItem->setData(0, "Attack Angle");
                attackAngleItem->setData(1, data.attackAngle);

                auto* strikeAngleItem = dataItem->child(5);
                strikeAngleItem->setData(0, "Strike Angle");
                strikeAngleItem->setData(1, data.strikeAngle);

                auto* staggerItem = dataItem->child(6);
                staggerItem->setData(0, "Stagger");
                staggerItem->setData(1, data.stagger);

                auto* attackTypeItem = dataItem->child(7);
                attackTypeItem->setData(0, "Attack Type");
                attackTypeItem->setData(1, data.attackType);

                auto* knockdownItem = dataItem->child(8);
                knockdownItem->setData(0, "Knockdown");
                knockdownItem->setData(1, data.knockdown);

                auto* recoveryTimeItem = dataItem->child(9);
                recoveryTimeItem->setData(0, "Recovery Time");
                recoveryTimeItem->setData(1, data.recoveryTime);

                auto* fatigueMultiplierItem = dataItem->child(10);
                fatigueMultiplierItem->setData(0, "Fatigue Multiplier");
                fatigueMultiplierItem->setData(1, data.fatigueMulitplier);

            }
            // EVENT
            auto* eventItem = childItem->child(1);
            eventItem->setData(0, "ATKE - Event");
            eventItem->setData(1, attackEvents[i]);
        }

        // EGT Models
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Body Data");
        item->insertChildren(0, 2, 2);

        auto* maleBodyItem = item->child(0);
        maleBodyItem->setData(0, "Male Body");
        maleBodyItem->insertChildren(0, 2, 2);
        {
            auto maleBody = RACE.getMaleEgtModel();
            // Index
            auto* indexItem = maleBodyItem->child(0);
            indexItem->setData(0, "Index");
            indexItem->setData(1, maleBody.index);

            // Model
            auto* modelItem = maleBodyItem->child(1);
            modelItem->setData(0, "Model");
            modelItem->setData(1, maleBody.model);
        }

        auto* femaleBodyItem = item->child(1);
        femaleBodyItem->setData(0, "Female Body");
        femaleBodyItem->insertChildren(0, 2, 2);
        {
            auto femaleBody = RACE.getFemaleEgtModel();
            // Index
            auto* indexItem = femaleBodyItem->child(0);
            indexItem->setData(0, "Index");
            indexItem->setData(1, femaleBody.index);

            // Model
            auto* modelItem = femaleBodyItem->child(1);
            modelItem->setData(0, "Model");
            modelItem->setData(1, femaleBody.model);
        }

        // GNAM - Body part data
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "GNAM - Body part data");
        item->setData(1, QString::number(RACE.getBodyPartData(), 16));

        // Behavior graphs
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Male Behavior Graph");
        item->insertChildren(0, 1, 2);
        {
            auto* modelItem = item->child(0);
            modelItem->setData(0, "Model");
            modelItem->setData(1, RACE.getMaleHavokModel().model);
        }

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Female Skeleton Model");
        item->insertChildren(0, 1, 2);
        {
            auto* modelItem = item->child(0);
            modelItem->setData(0, "Model");
            modelItem->setData(1, RACE.getFemaleHavokModel().model);
        }

        // NAM4 Material type
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "NAM4 - Material Type");
        item->setData(1, QString::number(RACE.getMaterialType(), 16));

        // NAM5 Impact data set
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "NAM5 - Impact Data Set");
        item->setData(1, QString::number(RACE.getImpactDataSet(), 16));

        // NAM7 Decap FX
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "NAM7 - Decapitation FX");
        item->setData(1, QString::number(RACE.getDecapFX(), 16));

        // ONAM Open loot sound
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "ONAM - Open Loot Sound");
        item->setData(1, QString::number(RACE.getOpenLootSound(), 16));

        // LNAM Close loot sound
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "LNAM - Close Loot Sound");
        item->setData(1, QString::number(RACE.getCloseLootSound(), 16));

        // Biped object names
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Biped Object Names");

        auto bipeds = RACE.getBipedObjectNames();
        item->insertChildren(0, bipeds.size(), 2);

        for (quint32 i = 0; i < bipeds.size(); i++) {

            auto* bipedNameItem = item->child(i);
            bipedNameItem->setData(0, "NAME");
            bipedNameItem->setData(1, bipeds[i]);
        }

        // Movement Types
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Movement Types");

        auto movementTypes = RACE.getMovementTypes();
        item->insertChildren(0, movementTypes.size(), 2);
        for (quint32 i = 0; i < movementTypes.size(); i++) {
            auto* moveItem = item->child(i);
            auto& moveData = movementTypes[i];
            moveItem->setData(0, "Movement Type");//MTYP - Type
            moveItem->insertChildren(0, 2, 2);

            auto* moveTypeItem = moveItem->child(0);
            moveTypeItem->setData(0, "MTYP - Type");
            moveTypeItem->setData(1, QString::number(moveData.type, 16));

            auto* speedTypeItem = moveItem->child(1);
            speedTypeItem->setData(0, "SPED - Override Values");

            // Speed override values.
            if (moveData.hasSpeedData) {
                quint32 numValues = moveData.speedData.unk.size();
                speedTypeItem->insertChildren(0, numValues, 2);

                for (quint32 j = 0; j < numValues; j++) {
                    auto* speedItem = speedTypeItem->child(j);

                    speedItem->setData(0, j);
                    speedItem->setData(1, moveData.speedData.unk[j]);
                }
            }
        }

        // Equipment type flags.
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Equipment Type Flags");
        item->setData(1, RACE.getEquipmentTypeFlags());

        // Equip slots
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Equip Slots");

        auto equipSlots = RACE.getEquipSlots();
        item->insertChildren(0, equipSlots.size(), 2);
        for(quint32 i = 0; i < equipSlots.size(); i++) {
            auto* equipItem = item->child(i);

            equipItem->setData(0, "QNAM - Equip Slot");
            equipItem->setData(1, QString::number(equipSlots[i], 16));
        }

        // Unarmed equip slot
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "UNES - Unarmed Equip Slot");
        item->setData(1, QString::number(RACE.getUnarmedEquipSlot(), 16));

        // Phoneme
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Pheoneme Target Names");

        // Keys
        auto phTargets = RACE.getFacialKeys();
        item->insertChildren(0, phTargets.size(), 2);
        for(quint32 i = 0; i < phTargets.size(); i++) {
            auto* phItem = item->child(i);

            phItem->setData(0, "PHTN - Name");
            phItem->setData(1, phTargets[i]);
        }

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "FaceFX Pheonemes");

        // Weights
        auto phWeights = RACE.getFacialWeights();
        item->insertChildren(0, phWeights.size(), 2);
        for(quint32 i = 0; i < phWeights.size(); i++) {
            auto* weightItem = item->child(i);

            weightItem->setData(0, "PHWT - Phoneme Target Weight");

            auto& weightData = phWeights[i];
            weightItem->insertChildren(0, weightData.weights.size(), 2);

            // TODO: These might be needed elsewhere so maybe move list?
            static const std::array<QString, 16> phtargetsident = {
                "Aah / LipBigAah",
                "BigAah / LipDST",
                "BMP / LipEee",
                "ChJsh / LipFV",
                "DST / LipK",
                "Eee / LipL",
                "Eh / LipR",
                "FV / LipTh",
                "I",
                "K",
                "N",
                "Oh",
                "OohQ",
                "R",
                "TH",
                "W"
            };

            for (quint32 j = 0; j < weightData.weights.size(); j++) {
                auto* weightTargetItem = weightItem->child(j);

                weightTargetItem->setData(0, phtargetsident[j]);
                weightTargetItem->setData(1, weightData.weights[j]);
            }

        }

        // MOVT records
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Movement Default - WALK");
        item->setData(1, QString::number(RACE.getWalkMove(), 16));

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Movement Default - RUN");
        item->setData(1, QString::number(RACE.getRunMove(), 16));

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Movement Default - SWIM");
        item->setData(1, QString::number(RACE.getSwimMove(), 16));

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Movement Default - FLY");
        item->setData(1, QString::number(RACE.getFlyMove(), 16));

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Movement Default - SNEAK");
        item->setData(1, QString::number(RACE.getSneakMove(), 16));

        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Movement Default - SPRINT");
        item->setData(1, QString::number(RACE.getSprintMove(), 16));

        // Head Data
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Head Data");
        item->insertChildren(0, 2, 2);

        auto* maleHeadItem = item->child(0);
        auto maleHeadData = RACE.getMaleHeadData();
        maleHeadItem->setData(0, "Male Head Data");

        auto* femaleHeadItem = item->child(1);
        auto femaleHeadData = RACE.getFemaleHeadData();
        femaleHeadItem->setData(0, "Female Head Data");

        auto headDataReader = [](models::FormModelItem* rootItem, esx::HeadData* data, char suffix) {

            // Head parts
            rootItem->insertChildren(0, 1, 2);
            auto* headPartsItem = rootItem->child(rootItem->childCount() - 1);
            headPartsItem->setData(0, "Head Parts");

            auto& headPartsData = data->headParts;
            headPartsItem->insertChildren(0, headPartsData.size(), 2);
            for (quint32 i = 0; i < headPartsData.size(); i++) {
                auto* headPartItem = headPartsItem->child(i);
                headPartItem->setData(0, "Head Part");
                auto& headPartData = headPartsData[i];

                headPartItem->insertChildren(0, 2, 2);

                auto* indxItem = headPartItem->child(0);
                indxItem->setData(0, "INDX - Head Part Number");
                indxItem->setData(1, headPartData.index);

                auto* headItem = headPartItem->child(1);
                headItem->setData(0, "HEAD - Head");
                headItem->setData(1, QString::number(headPartData.data, 16));
            }

            // Morphs
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            auto* morphsItem = rootItem->child(rootItem->childCount() - 1);
            morphsItem->setData(0, "Available Morphs");

            auto& morphsData = data->morphs;
            morphsItem->insertChildren(0, morphsData.size() * 2, 2);
            for (quint32 i = 0, j = 0; i < morphsData.size(); i++, j += 2) {

                auto* morphIndexItem = morphsItem->child(j);
                morphIndexItem->setData(0, "MPAI - Index");
                morphIndexItem->setData(1, morphsData[i].index);

                auto* morphItem = morphsItem->child(j + 1);
                morphItem->setData(0, "MPAV - Variant");

                // TODO: Implement when fields properly known.
                // Flags

                // Unk
            }

            // Race presets
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            auto* racePresetsItem = rootItem->child(rootItem->childCount() - 1);
            racePresetsItem->setData(0, QString("Race Presets ").append(suffix));

            racePresetsItem->insertChildren(0, data->presets.size(), 2);
            for (quint32 i = 0; i < data->presets.size(); i++) {
                auto* presetItem = racePresetsItem->child(i);

                presetItem->setData(0, QString("RPR%1 - Preset").arg(suffix));
                presetItem->setData(1, QString::number(data->presets[i], 16));
            }

            // Hair colors
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            auto* hairColorsItem = rootItem->child(rootItem->childCount() - 1);
            hairColorsItem->setData(0, QString("Available Hair Colors ").append(suffix));

            hairColorsItem->insertChildren(0, data->hairColors.size(), 2);
            for (quint32 i = 0; i < data->hairColors.size(); i++) {
                auto* hairColorItem = hairColorsItem->child(i);
                auto& hairColorData = data->hairColors[i];
                hairColorItem->setData(0, QString("AHC%1 - Hair Color").arg(suffix));
                hairColorItem->setData(1, QString::number(hairColorData, 16));
            }

            // Face details texture set
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            auto* fdTextureSetItem = rootItem->child(rootItem->childCount() - 1);
            fdTextureSetItem->setData(0, QString("Face Details Texture Set ").append(suffix));

            fdTextureSetItem->insertChildren(0, data->textureSetLists.size(), 2);
            for (quint32 i = 0; i < data->textureSetLists.size(); i++) {
                auto* fdItem = fdTextureSetItem->child(i);

                fdItem->setData(0, QString("FTS%1 - Texture Set").arg(suffix));
                fdItem->setData(1, QString::number(data->textureSetLists[i], 16));
            }

            // Default face texture
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            auto* defaultFaceTextureItem = rootItem->child(rootItem->childCount() - 1);
            defaultFaceTextureItem->setData(0, QString("Default Face Texture ").append(suffix));
            defaultFaceTextureItem->setData(1, QString::number(data->defaultFaceTexture, 16));

            // Tints
            rootItem->insertChildren(rootItem->childCount(), 1, 2);
            auto* tintMasksItem = rootItem->child(rootItem->childCount() - 1);
            tintMasksItem->setData(0, "Tint Masks");

            auto& tintsData = data->tints;
            tintMasksItem->insertChildren(0, tintsData.size(), 2);
            for (quint32 i = 0; i < tintsData.size(); i++) {
                auto* tintItem = tintMasksItem->child(i);
                tintItem->setData(0, "Tint Assets");
                auto& tintData = tintsData[i];

                tintItem->insertChildren(0, 2, 2);

                auto* tintLayerItem = tintItem->child(0);
                tintLayerItem->setData(0, "Tint Layer");

                tintLayerItem->insertChildren(0, 4, 2);
                {
                    // TINI
                    auto* tintIndexItem = tintLayerItem->child(0);
                    tintIndexItem->setData(0, "TINI - Index");
                    tintIndexItem->setData(1, tintData.index);

                    // TINT
                    auto* tintFileItem = tintLayerItem->child(1);
                    tintFileItem->setData(0, "TINT - File Name");
                    tintFileItem->setData(1, tintData.mask);

                    // TINP
                    auto* tintMaskTypeItem = tintLayerItem->child(2);
                    tintMaskTypeItem->setData(0, "TINP - Mask Type");
                    tintMaskTypeItem->setData(1, tintData.maskType);

                    // TIND
                    auto* tintPresetDefaultItem = tintLayerItem->child(3);
                    tintPresetDefaultItem->setData(0, "TINTD - Preset Default");
                    tintPresetDefaultItem->setData(1, QString::number(tintData.presetDefault, 16));

                    // Presets
                    auto* tintPresetsItem = tintItem->child(1);
                    tintPresetsItem->setData(0, "Presets");
                    tintPresetsItem->insertChildren(0, tintData.presets.size(), 2);

                    for (quint32 j = 0; j < tintData.presets.size(); j++) {
                        auto* presetItem = tintPresetsItem->child(j);
                        auto& presetData = tintData.presets[j];

                        presetItem->setData(0, "Preset");

                        presetItem->insertChildren(0, 3, 2);

                        auto* colorItem = presetItem->child(0);
                        colorItem->setData(0, "TINC - Color");
                        colorItem->setData(1, QString::number(presetData.preset, 16));

                        auto* defaultItem = presetItem->child(1);
                        defaultItem->setData(0, "TINV - Default Value");
                        defaultItem->setData(1, presetData.defaultValue);

                        auto* indexItem = presetItem->child(2);
                        indexItem->setData(0, "TIRS - Index");
                        indexItem->setData(1, presetData.tintNumber);
                    }
                }
            }

        };

        // Read Head data.
        headDataReader(maleHeadItem, &maleHeadData, 'M');
        headDataReader(femaleHeadItem, &femaleHeadData, 'F');

        // Morph race
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Morph Race");
        item->setData(1, QString::number(RACE.getMorphRace(), 16));

        // Armor race
        rootItem->insertChildren(rootItem->childCount(), 1, 2);
        item = rootItem->child(rootItem->childCount() - 1);
        item->setData(0, "Armor Race");
        item->setData(1, QString::number(RACE.getArmorRace(), 16));
    }
}
