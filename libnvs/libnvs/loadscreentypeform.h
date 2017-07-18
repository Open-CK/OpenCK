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
struct LoadScreenTypeData
{
	ulong type;
	ulong x;
	ulong y;
	ulong width;
	ulong height;
	float orientation;
	ulong font1;
	NiPoint3 font1Color;
	ulong font1Justification;
	ulong unk1;
	ulong unk2;
	ulong unk3;
	ulong unk4;
	float unk5;
	ulong font2;
	NiPoint3 font2Color;
	ulong unk6;
	ulong stats;
};
class LoadScreenTypeForm : public Form
{
protected:
	LoadScreenTypeData data;
public:
	LoadScreenTypeForm(FormHeader h,ModFile *f) : Form(h,f)
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
			case 'DATA':
				data = f->read<LoadScreenTypeData>();
				readSize += sizeof(LoadScreenTypeData);
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
		WriteSubrecord('DATA',sizeof(LoadScreenTypeData),f);
		f->write<LoadScreenTypeData>(data);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		size += ComputeSubrecordSize(sizeof(LoadScreenTypeData));
		return size;
	}
};
