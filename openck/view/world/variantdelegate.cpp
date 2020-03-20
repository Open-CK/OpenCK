#include "variantdelegate.hpp"

#include <QComboBox>

VariantDelegateFactory::VariantDelegateFactory()
{

}

VariantDelegateFactory::~VariantDelegateFactory()
{

}

GenericDelegate* VariantDelegateFactory::makeDelegate(Document& document, QObject* parent) const
{
    return new VariantDelegate(values, document, parent);
}

VariantDelegate::VariantDelegate(const QVector<QPair<int, QString>>& values, Document& document, QObject* parent) :
    EnumDelegate(values, document, parent)
{
    
}
