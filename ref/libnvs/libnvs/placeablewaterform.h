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
struct PlaceableWaterData
{
	ulong flags;
	formid water;
};
class PlaceableWaterForm : public BoundObjectForm, public Model
{
protected:
	PlaceableWaterData data;
public:
	PlaceableWaterForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f)
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
			case 'DNAM':
				data = f->read<PlaceableWaterData>();
				readSize += sizeof(PlaceableWaterData);
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
		WriteSubrecord('DNAM',sizeof(PlaceableWaterData),f);
		f->write<PlaceableWaterData>(data);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		ModelBRGetSaveSize(this);
		size += ComputeSubrecordSize(sizeof(PlaceableWaterData));
		return size;
	}
};
