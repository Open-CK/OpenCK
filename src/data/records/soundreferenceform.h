/*
** soundreferenceform.h
**
** Copyright © Beyond Skyrim Development Team, 2018.
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
** Created Date: 19-Mar-2018
*/

//!@file soundreferenceform.h Header for the SNDR record class.

#ifndef SOUNDREFERENCEFORM_H
#define SOUNDREFERENCEFORM_H

#define FORM_MEMBER(type, name) \
private: \
    type name; \
public: \
    const type& get##name##() const { return name; } \
    void set##name##(const type& newval) { name = newval; }

#include <QVector>
#include <data/form.h>
#include <data/subrecords/conditionfield.h>

namespace esx
{
    struct LoopDataField
    {
        quint16 flags;
        quint8 unused;
        quint8 rumbleSend;
    };

    struct SoundDataField
    {
        qint8 freqShift;
        quint8 freqVariance;
        quint8 priority;
        quint8 variance;
        quint16 attenuation;
    };

    typedef LoopDataField LoopDataField;
    typedef SoundDataField SoundDataField;

    /**
     * The SNDR Form.
     * @brief The SNDR Form.
     */
    class SoundReferenceForm : public Form
    {
        Q_OBJECT

        FORM_MEMBER(QString, EditorID)
        FORM_MEMBER(quint32, UnknownBytes)
        FORM_MEMBER(quint32, SoundCategoryID)
        FORM_MEMBER(quint32, AssocSoundID)
        FORM_MEMBER(QVector<QString>, TrackPaths)
        FORM_MEMBER(quint32, OutputModelID)
        FORM_MEMBER(QVector<ConditionField>, ConditionData)
        FORM_MEMBER(LoopDataField, LoopData)
        FORM_MEMBER(SoundDataField, SoundData)

    public:
        SoundReferenceForm() {}
        SoundReferenceForm(const Form& f) {}
        ~SoundReferenceForm() {}

        void load(io::Reader& r) override {}
        void addForm() override {}
        void readForm() override {}

    signals:
        void addSNDR(SoundReferenceForm& form);
        void readSNDR(SoundReferenceForm& form);
    };
}

#endif // SOUNDREFERENCEFORM_H
