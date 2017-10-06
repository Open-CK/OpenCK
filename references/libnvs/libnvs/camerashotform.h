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
struct CameraShotData
{
	ulong action;
	ulong location;
	ulong target;
	ulong flags;
	float playerTime;
	float targetTime;
	float globalTime;
	float maxTime;
	float minTime;
	float targetPercentage;
};
struct CameraShotData2
{
	ulong action;
	ulong location;
	ulong target;
	ulong flags;
	float playerTime;
	float targetTime;
	float globalTime;
	float maxTime;
	float minTime;
};
class CameraShotForm : public Form, public Model
{
protected:
	CameraShotData data;
	CameraShotData2 data2;
	bool hasCameraShotData2;
	formid imageSpaceModifier;
public:
	CameraShotForm(FormHeader h,ModFile *f) : Form(h,f), imageSpaceModifier(0), hasCameraShotData2(false)
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
				if (h.size == sizeof(CameraShotData))
				{
					data = f->read<CameraShotData>();
					readSize += sizeof(CameraShotData);
				} else if (h.size == sizeof(CameraShotData2))
				{
					hasCameraShotData2 = true;
					data2 = f->read<CameraShotData2>();
					readSize += sizeof(CameraShotData2);
				}
				break;
			case 'MNAM':
				imageSpaceModifier = f->read<formid>();
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
		if (hasCameraShotData2)
		{
			WriteSubrecord('DATA',sizeof(CameraShotData2),f);
			f->write<CameraShotData2>(data2);
		}
		else
		{
			WriteSubrecord('DATA',sizeof(CameraShotData),f);
			f->write<CameraShotData>(data);
		}
		if (imageSpaceModifier)
		{
			WriteSubrecord('MNAM',4,f);
			f->write<formid>(imageSpaceModifier);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		ModelBRGetSaveSize(this);
		if (hasCameraShotData2)
		{
			size += ComputeSubrecordSize(sizeof(CameraShotData2));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(CameraShotData));
		}
		if (imageSpaceModifier)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
