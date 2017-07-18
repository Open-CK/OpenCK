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
struct AmmoEffectData
{
	ulong type;
	ulong operation;
	float value;
};
class AmmoEffectForm : public Form, public FullName
{
protected:
	AmmoEffectData data;
public:
	AmmoEffectForm(FormHeader h,ModFile *f) : Form(h,f)
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
			FullNameLoad();
			case 'DATA':
				data = f->read<AmmoEffectData>();
				readSize += sizeof(AmmoEffectData);
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
		FullNameSave();
		WriteSubrecord('DATA',sizeof(AmmoEffectData),f);
		f->write<AmmoEffectData>(data);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		size += ComputeSubrecordSize(sizeof(AmmoEffectData));
		return size;
	}
};
