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
class MediaLocationControllerForm : public Form, public FullName
{
protected:
	ulong flags;
	float unk1;
	float unk2;
	float locationDelay;
	ulong dayStart;
	ulong nightStart;
	float loopRetriggerDelay;
	SimpleDynVecClass<formid> neutralSets;
	SimpleDynVecClass<formid> allySets;
	SimpleDynVecClass<formid> friendSets;
	SimpleDynVecClass<formid> enemySets;
	SimpleDynVecClass<formid> locationSets;
	SimpleDynVecClass<formid> battleSets;
	formid conditionalFaction;
	ulong unk3;
public:
	MediaLocationControllerForm(FormHeader h,ModFile *f) : Form(h,f), conditionalFaction(0)
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
			case 'NAM1':
				flags = f->read<ulong>();
				readSize += 4;
				break;
			case 'NAM2':
				unk1 = f->read<float>();
				readSize += 4;
				break;
			case 'NAM3':
				unk2 = f->read<float>();
				readSize += 4;
				break;
			case 'NAM4':
				locationDelay = f->read<float>();
				readSize += 4;
				break;
			case 'NAM5':
				dayStart = f->read<ulong>();
				readSize += 4;
				break;
			case 'NAM6':
				nightStart = f->read<ulong>();
				readSize += 4;
				break;
			case 'NAM7':
				loopRetriggerDelay = f->read<float>();
				readSize += 4;
				break;
			case 'HNAM':
				neutralSets.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'ZNAM':
				allySets.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'XNAM':
				friendSets.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'YNAM':
				enemySets.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'LNAM':
				locationSets.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'GNAM':
				battleSets.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'RNAM':
				conditionalFaction = f->read<formid>();
				readSize += 4;
				break;
			case 'FNAM':
				unk3 = f->read<formid>();
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
		FullNameSave();
		WriteSubrecord('NAM1',4,f);
		f->write<ulong>(flags);
		WriteSubrecord('NAM2',4,f);
		f->write<float>(unk1);
		WriteSubrecord('NAM3',4,f);
		f->write<float>(unk2);
		WriteSubrecord('NAM4',4,f);
		f->write<float>(locationDelay);
		WriteSubrecord('NAM5',4,f);
		f->write<ulong>(dayStart);
		WriteSubrecord('NAM6',4,f);
		f->write<ulong>(nightStart);
		WriteSubrecord('NAM7',4,f);
		f->write<float>(loopRetriggerDelay);
		for (int i = 0;i < neutralSets.Count();i++)
		{
			WriteSubrecord('HNAM',4,f);
			f->write<formid>(neutralSets[i]);
		}
		for (int i = 0;i < allySets.Count();i++)
		{
			WriteSubrecord('ZNAM',4,f);
			f->write<formid>(allySets[i]);
		}
		for (int i = 0;i < friendSets.Count();i++)
		{
			WriteSubrecord('XNAM',4,f);
			f->write<formid>(friendSets[i]);
		}
		for (int i = 0;i < enemySets.Count();i++)
		{
			WriteSubrecord('YNAM',4,f);
			f->write<formid>(enemySets[i]);
		}
		for (int i = 0;i < locationSets.Count();i++)
		{
			WriteSubrecord('LNAM',4,f);
			f->write<formid>(locationSets[i]);
		}
		for (int i = 0;i < battleSets.Count();i++)
		{
			WriteSubrecord('GNAM',4,f);
			f->write<formid>(battleSets[i]);
		}
		if (conditionalFaction)
		{
			WriteSubrecord('RNAM',4,f);
			f->write<formid>(conditionalFaction);
		}
		WriteSubrecord('FNAM',4,f);
		f->write(unk3);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		for (int i = 0;i < neutralSets.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < allySets.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < friendSets.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < enemySets.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < locationSets.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < battleSets.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		if (conditionalFaction)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(4);
		return size;
	}
};
