/*
** imagespaceform.h
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

#ifndef IMAGESPACEFORM_H
#define IMAGESPACEFORM_H

#define FORM_MEMBER(type, name) \
private: \
    type name; \
public: \
    const type& get##name##() const { return name; } \
    void set##name##(const type& newval) { name = newval; }

#include <data/form.h>

namespace esx
{
    struct ENAMField
    {
        // HDR
        float eyeAdaptSpeed{ 0.0f };
        float bloomBlurRadius{ 0.0f };
        float bloomThreshold{ 0.0f };
        float bloomScale{ 0.0f };
        float receiveBloomThreshold{ 0.0f };
        float sunlightScale{ 0.0f };
        float skyScale{ 0.0f };
        
        // Cinematic
        float saturation{ 0.0f };
        float brightness{ 0.0f };
        float contrast{ 0.0f };
        
        // Tint
        float tint{ 0.0f };
        float red{ 0.0f };
        float green{ 0.0f };
        float blue{ 0.0f };
    };

    struct HDRParamsField
    {
        float eyeAdaptSpeed{ 0.0f };
        float bloomBlurRadius{ 0.0f };
        float bloomThreshold{ 0.0f };
        float bloomScale{ 0.0f };
        float receiveBloomThreshold{ 0.0f };
        float white{ 0.0f };
        float sunlightScale{ 0.0f };
        float skyScale{ 0.0f };
        float eyeAdaptStrength{ 0.0f };
    };

    struct CinematicParamsField
    {
        float saturation{ 0.0f };
        float brightness{ 0.0f };
        float contrast{ 0.0f };
    };

    struct TintParamsField
    {
        float tint{ 0.0f };
        float red{ 0.0f };
        float green{ 0.0f };
        float blue{ 0.0f };
    };

    struct DOFParamsField
    {
        float strength{0.0f};
        float distance{ 0.0f };
        float range{ 0.0f };
        float unk;
    };

    class ImagespaceForm : public Form 
    {
        Q_OBJECT

        FORM_MEMBER(QString, EditorID)
        FORM_MEMBER(ENAMField, ENAMParams)
        FORM_MEMBER(HDRParamsField, HDRParams)
        FORM_MEMBER(CinematicParamsField, CinematicParams)
        FORM_MEMBER(TintParamsField, TintParams)
        FORM_MEMBER(DOFParamsField, DOFParams)
    public:
        ImagespaceForm();
        ImagespaceForm(const Form& form);
        ~ImagespaceForm() = default;

        void load(io::Reader& r) override;
        void addForm() override;
        void readForm() override;

    signals:
        void addIMGS(ImagespaceForm& IMGS);
        void readIMGS(ImagespaceForm& IMGS);

    private:
    };
}

#endif