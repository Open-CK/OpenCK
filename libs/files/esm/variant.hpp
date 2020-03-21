#ifndef VARIANT_H
#define VARIANT_H

#include <QVariant>

class ESMReader;
class ESMWriter;

enum VariantType
{
    Var_None = 0,
    Var_Short,
    Var_Int,
    Var_Long,
    Var_Float,
    Var_String,
    Var_LString,
    Var_Bool
};

struct LString
{
    quint32 index;
    QString string;
};

class Variant
{
public:
    enum Format
    {
        Format_GLOB = 0,
        Format_GMST
    };

    Variant();
    Variant(quint16 val);
    Variant(quint32 val);
    Variant(float val);
    Variant(QString val);
    Variant(LString val);
    Variant(bool val);

    VariantType getType() const;
    quint16 getShort();
    quint32 getInt() const;
    float getFloat() const;
    QString getString() const;
    LString getLString() const;
    bool getBool() const;

    void setType(VariantType type);
    void setShort(quint16 val);
    void setInt(quint32 val);
    void setFloat(float val);
    void setString(QString val);
    void setLString(LString val);
    void setBool(bool val);

    void load(ESMReader& esm, Format format, const QString& editorId = "");
    void write(ESMWriter& esm, Format format) const;

    const QVariant& getData() const;

private:
    VariantType type;
    QVariant data;
    LString lstring;
};

bool operator==(const Variant& l, const Variant& r);
bool operator!=(const Variant& l, const Variant& r);

#endif // VARIANT_H
