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
class AcousticSpaceForm : public BoundObjectForm
{
protected:
	SimpleDynVecClass<formid> sounds;
	ulong wallaTriggerCount;
	formid region;
	ulong environmentType;
	ulong isInterior;
public:
	AcousticSpaceForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), region(0)
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
			case 'SNAM':
				sounds.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'WNAM':
				wallaTriggerCount = f->read<ulong>();
				readSize += 4;
				break;
			case 'RDAT':
				region = f->read<formid>();
				readSize += 4;
				break;
			case 'ANAM':
				environmentType = f->read<ulong>();
				readSize += 4;
				break;
			case 'INAM':
				isInterior = f->read<ulong>();
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
		BoundObjectFormSave();
		for (int i = 0;i < sounds.Count();i++)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(sounds[i]);
		}
		WriteSubrecord('WNAM',4,f);
		f->write<ulong>(wallaTriggerCount);
		if (region)
		{
			WriteSubrecord('RDAT',4,f);
			f->write<formid>(region);
		}
		WriteSubrecord('ANAM',4,f);
		f->write<ulong>(environmentType);
		WriteSubrecord('INAM',4,f);
		f->write<ulong>(isInterior);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		for (int i = 0;i < sounds.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(4);
		if (region)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		return size;
	}
};
