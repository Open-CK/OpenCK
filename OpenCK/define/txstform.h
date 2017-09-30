/*
** txstrecord.h
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
** Created Date: 15-Aug-2017
*/

#ifndef TXSTFORM_H
#define TXSTFORM_H

#include "form.h"

namespace Define
{
    class TXSTForm;
}

struct DecalData {
    float minWidth;
    float maxWidth;
    float minHeight;
    float maxHeight;
    float depth;
    float shininess;
    float parallaxScale;
    quint8 parallaxPasses;
    quint8 decalFlags;
    quint8 unknown00;
    quint8 unknown01;
    quint32 rgb;
};

typedef struct DecalData DecalData;

class TXSTForm : public Form
{
public:
    TXSTForm() {}
    ~TXSTForm() {}
    void load(QDataStream *in, int fileNumber);

    QString getEditorID() const;
    quint8* getUnknownArray() const;
    QString getMap00() const;
    QString getMap01() const;
    QString getMask02() const;
    QString getMap03() const;
    QString getMap04() const;
    QString getMap05() const;
    QString getMap06() const;
    QString getMap07() const;
    DecalData getDecalData() const;
    quint16 getTextureFlags() const;

    void setEditorID(const QString in);
    void setUnknownArray(const quint8* start);
    void setMap00(const QString path);
    void setMap01(const QString path);
    void setMap02(const QString path);
    void setMap03(const QString path);
    void setMap04(const QString path);
    void setMap05(const QString path);
    void setMap06(const QString path);
    void setMap07(const QString path);
    void setDecalData(const DecalData in);
    void setTextureFlags(const quint16 in);

private:
    void readDecalData(QDataStream *in, QByteArray *buffer);

    QString editorID = nullptr;
    quint8 unknownArray[12];
    QString map00 = nullptr;
    QString map01 = nullptr;
    QString map02 = nullptr;
    QString map03 = nullptr;
    QString map04 = nullptr;
    QString map05 = nullptr;
    QString map06 = nullptr;
    QString map07 = nullptr;
    DecalData decalData;
    quint16 textureFlags = 0;
};

#endif // TXSTFORM_H
