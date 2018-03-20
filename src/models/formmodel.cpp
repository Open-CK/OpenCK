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
}
