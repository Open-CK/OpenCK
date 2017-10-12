/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "boundobjectform.h"
struct GrassData
{
	ubyte density;
	ubyte minSlope;
	ubyte maxSlope;
	ushort unitFromWaterAmount;
	ulong unitFromWaterType;
	float positionRange;
	float heightRange;
	float colorRange;
	float wavePeriod;
	ubyte flags;
};
class GrassForm : public BoundObjectForm, public Model
{
protected:
	GrassData data;
public:
	GrassForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f)
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
			BoundObjectFormLoad();
			ModelBRLoad(this,'MODL','MODB','MODT');
			case 'DATA':
				data = f->read<GrassData>();
				readSize += sizeof(GrassData);
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
		BoundObjectFormSave();
		ModelBRSave(this,'MODL','MODB','MODT');
		WriteSubrecord('DATA',sizeof(GrassData),f);
		f->write<GrassData>(data);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		ModelBRGetSaveSize(this);
		size += ComputeSubrecordSize(sizeof(GrassData));
		return size;
	}
};
