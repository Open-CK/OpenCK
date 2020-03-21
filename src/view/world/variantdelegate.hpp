#ifndef VARIANT_DELEGATE_H
#define VARIANT_DELEGATE_H

#include "delegatefactory.hpp"
#include "enumdelegate.hpp"

#include <QStyledItemDelegate>

class Document;

class VariantDelegateFactory : public DelegateFactory
{
public:
    VariantDelegateFactory();
    ~VariantDelegateFactory();

    virtual GenericDelegate* makeDelegate(Document& document, QObject* parent) const override;

private:
    QVector<QPair<int, QString>> values;
};

class VariantDelegate : public EnumDelegate
{
public:
    VariantDelegate(const QVector<QPair<int, QString>>& values, Document& document, QObject* parent = nullptr);
};

#endif // VARIANT_DELEGATE_H