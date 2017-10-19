#include "texturesetform.h"
#include "parser.h"

namespace esx
{
    /**
     * Create a new form by copying an existing header.
     * @brief Create a new form from header.
     * @param f Form header read by parser.
     */
    TextureSetForm::TextureSetForm(const Form& f)
    {
        this->header = f.getHeader();
        this->header.setName(FormName::TextureSet);
    }

    /**
     * Loads the GMST header from the data stream.
     * @brief Loads the header.
     * @param r Reader object that performs all parsing functions.
     */
    void TextureSetForm::load(io::Reader &r)
    {
        quint32 read = 0;
        while (read < header.getDataSize()) {
            SubrecordHeader h = readSubrecord(r, &read);

            switch(h.type) {
                case 'EDID':
                    this->setEditorID(r.readZstring());
                    read += this->getEditorID().length() + 1;
                    break;
                case 'OBND':
                    //TEMPORARY: Need to split to subrecord
                    this->ObjectBounds = r.read<ObjectBoundsField>();
                    read += sizeof(ObjectBoundsField);
                    if (this->ObjectBounds.xmax != 0)
                    {
                        qDebug("Check");
                    }
                    break;
                case 'TX00':
                    this->paths[0] = r.readZstring();
                    read += this->paths[0].length() + 1;
                    break;
                case 'TX01':
                    this->paths[1] = r.readZstring();
                    read += this->paths[1].length() + 1;
                    break;
                case 'TX02':
                    this->paths[2] = r.readZstring();
                    read += this->paths[2].length() + 1;
                    break;
                case 'TX03':
                    this->paths[3] = r.readZstring();
                    read += this->paths[3].length() + 1;
                    break;
                case 'TX04':
                    this->paths[4] = r.readZstring();
                    read += this->paths[4].length() + 1;
                    break;
                case 'TX05':
                    this->paths[5] = r.readZstring();
                    read += this->paths[5].length() + 1;
                    break;
                case 'TX06':
                    this->paths[6] = r.readZstring();
                    read += this->paths[6].length() + 1;
                    break;
                case 'TX07':
                    this->paths[7] = r.readZstring();
                    read += this->paths[7].length() + 1;
                    break;
                case 'DODT':
                    this->DecalData = r.read<DecalInf>();
                    read += sizeof(DecalInf);
                    hasDecalData = true;
                    break;
                case 'DNAM':
                    this->setFlags(r.read<quint16>());
                    read += 2;
                    hasFlags = true;
                    break;
            }
        }
    }

    void TextureSetForm::setPath(const quint8 n, const QString& in)
    {
        this->paths[n] = in;
    }

    QString TextureSetForm::getPath(const quint8 n) const
    {
        return this->paths[n];
    }

    bool TextureSetForm::hasDODT() const
    {
        return this->hasDecalData;
    }

    bool TextureSetForm::hasTextureFlags() const
    {
        return this->hasFlags;
    }

    /**
     * Signal. Add the form to the file model.
     * @brief Add form to file model.
     */
    void TextureSetForm::addForm()
    {
        connect(this, &TextureSetForm::addTXST,
                &io::Parser::getParser().getFileModel(), &models::FileModel::insertTXST);
        emit addTXST(*this);
    }

    /**
     * Signal. Display the contents of a form stored in the file model to the form model.
     * @brief Display contents in form model.
     */
    void TextureSetForm::readForm()
    {
        connect(this, &TextureSetForm::readTXST,
                &io::Parser::getParser().getFormModel(), &models::FormModel::readTXST);
        emit readTXST(*this);
    }
}
