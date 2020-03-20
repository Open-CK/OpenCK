#ifndef ENUM_DELEGATE_H
#define ENUM_DELEGATE_H

#include "delegatefactory.hpp"
#include "genericdelegate.hpp"

#include <QSize>

class Document;

class EnumDelegateFactory : public DelegateFactory
{
public:
    EnumDelegateFactory();
    EnumDelegateFactory(ColumnId column);
    ~EnumDelegateFactory();

    virtual GenericDelegate* makeDelegate(Document& document, QObject* parent) const override;

private:
    QVector<QPair<int, QString>> values;
};

class EnumDelegate : public GenericDelegate
{
public:
    EnumDelegate(const QVector<QPair<int, QString>>& values, Document& document, QObject* parent);

    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index, BaseColumn::Display display = BaseColumn::Display_None) const override;
    virtual void setEditorData(QWidget* editor, const QModelIndex& index, bool tryDisplay = false) const override;
    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

protected:
    virtual void setModelDataImp(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
    
private:
    int getValueIndex(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QVector<QPair<int, QString>> values;
};

#endif // ENUM_DELEGATE_H