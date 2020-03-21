#include "variant.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

Variant::Variant()
    : type(Var_None)
{
}

Variant::Variant(quint16 val)
    : type(Var_Short)
{
    data = val;
}

Variant::Variant(quint32 val)
    : type(Var_Int)
{
    data = val;
}

Variant::Variant(float val)
    : type(Var_Float)
{
    data = val;
}

Variant::Variant(QString val)
    : type(Var_String)
{
    data = val;
}

Variant::Variant(LString val)
    : type(Var_LString)
{
    lstring = val;
}

Variant::Variant(bool val)
    : type(Var_Bool)
{
    data = val;
}

VariantType Variant::getType() const
{
    return type;
}

quint16 Variant::getShort()
{
    data.convert(QMetaType::Short);
    return static_cast<quint16>(data.toUInt());
}

quint32 Variant::getInt() const
{
    return data.toUInt();
}

float Variant::getFloat() const
{
    return data.toFloat();
}

QString Variant::getString() const
{
    return data.toString();
}

LString Variant::getLString() const
{
    return lstring;
}

bool Variant::getBool() const
{
    return data.toBool();
}

void Variant::setType(VariantType inType)
{
    type = inType;
}

void Variant::setShort(quint16 val)
{
    type = VariantType::Var_Short;
    data = data.fromValue(val);
}

void Variant::setInt(quint32 val)
{
    type = VariantType::Var_Int;
    data = data.fromValue(val);
}

void Variant::setFloat(float val)
{
    type = VariantType::Var_Float;
    data = data.fromValue(val);
}

void Variant::setString(QString val)
{
    type = VariantType::Var_String;
    data = data.fromValue(val);
}

void Variant::setLString(LString val)
{
    type = VariantType::Var_LString;
    lstring = val;
}

void Variant::setBool(bool val)
{
    type = VariantType::Var_Bool;
    data = data.fromValue(val);
}

void Variant::load(ESMReader& esm, Format format, const QString& editorId)
{
    switch (format)
    {
    case (Format_GMST):
    {
        esm.readNSubHeader();

        if (editorId.size() > 0)
        {
            if (editorId.front() == "b")
            {
                setType(Var_Bool);
                setBool(esm.readType<quint32>());
            }
            else if (editorId.front() == "i")
            {
                setType(Var_Int);
                setFloat(esm.readType<quint32>());
            }
            else if (editorId.front() == "f")
            {
                setType(Var_Float);
                setFloat(esm.readType<float>());
            }
            else if (editorId.front() == "s")
            {
                if (esm.localised())
                {
                    setType(Var_LString);

                    LString lstr;
                    lstr.index = esm.readType<quint32>();
                    lstr.string = esm.getStrings().get(Strings::LString, lstr.index);

                    setLString(lstr);
                }
                else
                {
                    setType(Var_String);
                    setString(esm.readZString());
                }
            }
            else
            {
                throw std::runtime_error("Invalid format in GMST record.");
            }
        }
        else
        {
            throw std::runtime_error("No EditorID provided for GMST record.");
        }

        break;
    }
    case (Format_GLOB):
    {
        unsigned char c{ esm.readSubData<quint8>('FNAM') };

        if (c == 's')
        {
            setType(Var_Short);
            setShort(static_cast<quint16>(esm.readSubData<float>('FLTV')));
        }
        else if (c == 'l')
        {
            setType(Var_Int);
            setInt(static_cast<quint32>(esm.readSubData<float>('FLTV')));
        }
        else if (c == 'f')
        {
            setType(Var_Float);
            setFloat(static_cast<float>(esm.readSubData<float>('FLTV')));
        }
        else
        {
            throw std::runtime_error("Invalid format in GLOB record.");
        }

        break;
    }
    }
}

void Variant::write(ESMWriter& esm, Format format) const
{
    switch (format)
    {
    case (Format_GMST):
    {
        if (type == Var_Bool)
        {
            esm.writeType<quint32>(data.toBool());
        }
        else if (type == Var_Int)
        {
            esm.writeType<quint32>(data.toUInt());
        }
        else if (type == Var_Float)
        {
            esm.writeType<float>(data.toFloat());
        }
        else if (type == Var_String)
        {
            esm.writeZString(data.toString().toUtf8());
        }
        else
        {
            throw std::runtime_error("Invalid format in GMST record.");
        }

        break;
    }
    case (Format_GLOB):
    {
        if (type == Var_Short)
        {
            esm.writeSubData<quint8>('FNAM', 's');
        }
        else if (type == Var_Int)
        {
            esm.writeSubData<quint8>('FNAM', 'l');
        }
        else if (type == Var_Float)
        {
            esm.writeSubData<quint8>('FNAM', 'f');
        }
        else
        {
            throw std::runtime_error("Invalid format in GLOB record.");
        }

        esm.writeSubData<float>('FLTV', data.toFloat());
        break;
    }
    }
}

const QVariant& Variant::getData() const
{
    return data;
}

bool operator==(const Variant& l, const Variant& r)
{
    return l.getData() == r.getData();
}

bool operator!=(const Variant& l, const Variant& r)
{
    return l.getData() != r.getData();
}
