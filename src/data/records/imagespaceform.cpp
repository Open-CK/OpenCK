/*
** imagespaceform.cpp
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
** Created Date: 02-May-2018
*/

#include <data/records/imagespaceform.h>
#include <io/parser.h>

namespace esx
{
    ImagespaceForm::ImagespaceForm(const Form& form)
        : ImagespaceForm()
    {
        this->header = form.getHeader();
        this->header.setName(FormName::Imagespace);
    }

    void ImagespaceForm::load(io::Reader& r)
    {
        quint32 read{ 0 };
        this->setUsesENAM(false);
        while (read < header.getDataSize()) {
            SubrecordHeader h = readSubrecord(r, &read);

            switch (h.type) {
            case 'EDID': // Editor ID
                this->setEditorID(r.readZstring());
                read += this->getEditorID().length();
                break;
            case 'ENAM': { // All encompassing field for HDR, Cinematic and Tint params.
                
                ENAMField enam;

                this->setUsesENAM(true);

                // HDR
                enam.eyeAdaptSpeed = r.read<float>();
                enam.bloomBlurRadius = r.read<float>();
                enam.bloomThreshold = r.read<float>();
                enam.bloomScale = r.read<float>();
                enam.receiveBloomThreshold = r.read<float>();
                enam.sunlightScale = r.read<float>();
                enam.skyScale = r.read<float>();

                // Cinematic
                enam.saturation = r.read<float>();
                enam.brightness = r.read<float>();
                enam.contrast = r.read<float>();

                // Tint
                enam.tint = r.read<float>();
                enam.red = r.read<float>();
                enam.green = r.read<float>();
                enam.blue = r.read<float>();

                this->setENAMParams(enam);
                read += sizeof(float) * 14;

                break;
            }
            case 'HNAM': { // HDR params

                HDRParamsField hdr;
                hdr.eyeAdaptSpeed = r.read<float>();
                hdr.bloomBlurRadius = r.read<float>();
                hdr.bloomThreshold = r.read<float>();
                hdr.bloomScale = r.read<float>();
                hdr.receiveBloomThreshold = r.read<float>();
                hdr.white = r.read<float>();
                hdr.sunlightScale = r.read<float>();
                hdr.skyScale = r.read<float>();
                hdr.eyeAdaptStrength = r.read<float>();

                this->setHDRParams(hdr);
                read += sizeof(float) * 9;

                break;
            }
            case 'CNAM': {// Cinematic params

                CinematicParamsField cparams;
                cparams.saturation = r.read<float>();
                cparams.brightness = r.read<float>();
                cparams.contrast = r.read<float>();

                this->setCinematicParams(cparams);
                read += sizeof(float) * 3;

                break;
            }
            case 'TNAM': { // Tint params

                TintParamsField tparams;
                tparams.tint = r.read<float>();
                tparams.red = r.read<float>();
                tparams.green = r.read<float>();
                tparams.blue = r.read<float>();

                this->setTintParams(tparams);
                read += sizeof(float) * 4;

                break;
            }
            case 'DNAM': { // Depth of Field params

                DOFParamsField dof;
                
                dof.strength = r.read<float>();
                dof.distance = r.read<float>();
                dof.range = r.read<float>();

                read += sizeof(float) * 3;

                // TODO: Check where/when this field is read.
                if (read < header.getDataSize()) {
                    dof.unk = r.read<float>();
                    read += sizeof(float);
                }

                this->setDOFParams(dof);

                break;
            }
            }
        }
    }

    void ImagespaceForm::addForm()
    {
        connect(this, &ImagespaceForm::addIMGS,
            &io::Parser::getParser().getFileModel(), &models::FileModel::insertIMGS);
        emit addIMGS(*this);
    }

    void ImagespaceForm::readForm()
    {
        connect(this, &ImagespaceForm::readIMGS,
            &io::Parser::getParser().getFormModel(), &models::FormModel::readIMGS);
        emit readIMGS(*this);
    }
}