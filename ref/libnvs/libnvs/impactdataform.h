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
struct ImpactDataData
{
	float effectDuration;
	ulong effectOrientation;
	float effectAngle;
	float placementRadius;
	ulong soundLevel;
	ubyte flags;
};
struct ImpactDecalInfo
{
	float minWidth;
	float maxWidth;
	float minHeight;
	float maxHeight;
	float depth;
	float shininess;
	float parallaxScale;
	ubyte parallaxPasses;
	ubyte flags;
	ulong color;
};
class ImpactDataForm : public Form, public Model
{
protected:
	ImpactDataData data;
	ImpactDecalInfo info;
	formid textureSet;
	formid sound1;
	formid sound2;
public:
	ImpactDataForm(FormHeader h,ModFile *f) : Form(h,f), textureSet(0), sound1(0), sound2(0)
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
			ModelBRLoad(this,'MODL','MODB','MODT');
			case 'DATA':
				data = f->read<ImpactDataData>();
				readSize += sizeof(ImpactDataData);
				break;
			case 'DODT':
				info = f->read<ImpactDecalInfo>();
				readSize += sizeof(ImpactDecalInfo);
				break;
			case 'DNAM':
				textureSet = f->read<formid>();
				readSize += 4;
				break;
			case 'SNAM':
				sound1 = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM1':
				sound2 = f->read<formid>();
				readSize += 4;
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
		ModelBRSave(this,'MODL','MODB','MODT');
		WriteSubrecord('DATA',sizeof(ImpactDataData),f);
		f->write<ImpactDataData>(data);
		if (!(data.flags & 1))
		{
			WriteSubrecord('DODT',sizeof(ImpactDecalInfo),f);
			f->write<ImpactDecalInfo>(info);
		}
		if (textureSet)
		{
			WriteSubrecord('DNAM',4,f);
			f->write<formid>(textureSet);
		}
		if (sound1)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(sound1);
		}
		if (sound2)
		{
			WriteSubrecord('NAM1',4,f);
			f->write<formid>(sound2);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		ModelBRGetSaveSize(this);
		size += ComputeSubrecordSize(sizeof(ImpactDataData));
		if (!(data.flags & 1))
		{
			size += ComputeSubrecordSize(sizeof(ImpactDecalInfo));
		}
		if (textureSet)
		{
			size += ComputeSubrecordSize(4);
		}
		if (sound1)
		{
			size += ComputeSubrecordSize(4);
		}
		if (sound2)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
