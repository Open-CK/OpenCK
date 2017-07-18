/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "form.h"
struct ImageSpaceData
{
	float hdrData[15];
	float blurData[3];
	float getHitData[3];
	float nightEyeTintRed;
	float nightEyeTintGreen;
	float nightEyeTintBlue;
	float nightEyeBrightness;
	float cinematicData[4];
	float cinematicBrightnessRed;
	float cinematicBrightnessGreen;
	float cinematicBrightnessBlue;
	float cinematicBrightnessTintValue;
	float unk1;
	float unk2;
	float unk3;
	float unk4;
	ulong flags;
};
struct ImageSpaceData2
{
	float hdrData[15];
	float blurData[3];
	float getHitData[3];
	float nightEyeTintRed;
	float nightEyeTintGreen;
	float nightEyeTintBlue;
	float nightEyeBrightness;
	float cinematicData[4];
	float cinematicBrightnessRed;
	float cinematicBrightnessGreen;
	float cinematicBrightnessBlue;
	float cinematicBrightnessTintValue;
	float unk1;
	float unk2;
	float unk3;
	float unk4;
};
struct ImageSpaceData3
{
	float hdrData[15];
	float blurData[3];
	float getHitData[3];
	float nightEyeTintRed;
	float nightEyeTintGreen;
	float nightEyeTintBlue;
	float nightEyeBrightness;
	float cinematicData[4];
	float cinematicBrightnessRed;
	float cinematicBrightnessGreen;
	float cinematicBrightnessBlue;
	float cinematicBrightnessTintValue;
};
class ImageSpaceForm : public Form
{
protected:
	ImageSpaceData data;
	ImageSpaceData2 data2;
	ImageSpaceData3 data3;
	bool hasImageSpaceData2;
	bool hasImageSpaceData3;
public:
	ImageSpaceForm(FormHeader h,ModFile *f) : Form(h,f), hasImageSpaceData2(false), hasImageSpaceData3(false)
	{
	}
protected:
	virtual void Load(FileRead *f)
	{
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			case 'DNAM':
				if (h.size == sizeof(ImageSpaceData))
				{
					data = f->read<ImageSpaceData>();
					readSize += sizeof(ImageSpaceData);
				}
				else if (h.size == sizeof(ImageSpaceData2))
				{
					hasImageSpaceData2 = true;
					data2 = f->read<ImageSpaceData2>();
					readSize += sizeof(ImageSpaceData2);
				}
				else if (h.size == sizeof(ImageSpaceData3))
				{
					hasImageSpaceData3 = true;
					data3 = f->read<ImageSpaceData3>();
					readSize += sizeof(ImageSpaceData3);
				}
				break;
			default:
				printf("Unknown subrecord found");
				__debugbreak();
				break;
			}
		}
	}
	virtual void Save(FileWrite *f)
	{
		FormSave();
		if (hasImageSpaceData2)
		{
			WriteSubrecord('DNAM',sizeof(ImageSpaceData2),f);
			f->write<ImageSpaceData2>(data2);
		}
		else if (hasImageSpaceData3)
		{
			WriteSubrecord('DNAM',sizeof(ImageSpaceData3),f);
			f->write<ImageSpaceData3>(data3);
		}
		else
		{
			WriteSubrecord('DNAM',sizeof(ImageSpaceData),f);
			f->write<ImageSpaceData>(data);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		if (hasImageSpaceData2)
		{
			size += ComputeSubrecordSize(sizeof(ImageSpaceData2));
		}
		else if (hasImageSpaceData3)
		{
			size += ComputeSubrecordSize(sizeof(ImageSpaceData3));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(ImageSpaceData));
		}
		return size;
	}
};
