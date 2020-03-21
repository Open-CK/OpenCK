#ifndef GENERIC_DELEGATE_H
#define GENERIC_DELEGATE_H

#include "../../model/doc/document.hpp"
#include "../../model/world/basecolumn.hpp"

#include <QStyledItemDelegate>

class TableModelHelper : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModelHelper(QAbstractItemModel& model);
    
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex& index, int role) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    virtual QVariant getData() const;

private:
    QAbstractItemModel& model;
    QVariant modelData;
};

class GenericDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    GenericDelegate(Document& document, QObject* parent);

    virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index, BaseColumn::Display display) const;

    void setEditLock(bool locked);
    bool isEditLocked() const;

    virtual void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    virtual void setEditorData(QWidget* editor, const QModelIndex& index, bool tryDisplay) const;

protected:
    Document& getDocument() const;
    BaseColumn::Display getDisplayTypeFromIndex(const QModelIndex& index) const;

    virtual void setModelDataImp(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;


private:
    Document& document;
    bool isLocked;
};

#endif // GENERIC_DELEGATE_H