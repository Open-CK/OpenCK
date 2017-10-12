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
class MediaSetForm : public Form, public FullName
{
protected:
	ulong type;
	char *sound1;
	char *sound2;
	char *sound3;
	char *sound4;
	char *sound5;
	char *sound6;
	float sound1db;
	float sound2db;
	float sound3db;
	float sound4db;
	float sound5db;
	float sound6db;
	float dayOuterBoundary;
	float dayMiddleBoundary;
	float dayInnerBoundary;
	float nightOuterBoundary;
	float nightMiddleBoundary;
	float nightInnerBoundary;
	ubyte enableFlags;
	float time1;
	float time2;
	float time3;
	float time4;
	formid intro;
	formid outro;
public:
	MediaSetForm(FormHeader h,ModFile *f) : Form(h,f), sound1(0), sound2(0), sound3(0), sound4(0), sound5(0), sound6(0), intro(0), outro(0)
	{
	}
	~MediaSetForm()
	{
		if (sound1)
		{
			delete[] sound1;
		}
		if (sound2)
		{
			delete[] sound2;
		}
		if (sound3)
		{
			delete[] sound3;
		}
		if (sound4)
		{
			delete[] sound4;
		}
		if (sound5)
		{
			delete[] sound5;
		}
		if (sound6)
		{
			delete[] sound6;
		}
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
				type = f->read<ulong>();
				readSize += 4;
				break;
			case 'NAM2':
				sound1 = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'NAM3':
				sound2 = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'NAM4':
				sound3 = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'NAM5':
				sound4 = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'NAM6':
				sound5 = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'NAM7':
				sound6 = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'NAM8':
				sound1db = f->read<float>();
				readSize += 4;
				break;
			case 'NAM9':
				sound2db = f->read<float>();
				readSize += 4;
				break;
			case 'NAM0':
				sound3db = f->read<float>();
				readSize += 4;
				break;
			case 'ANAM':
				sound4db = f->read<float>();
				readSize += 4;
				break;
			case 'BNAM':
				sound5db = f->read<float>();
				readSize += 4;
				break;
			case 'CNAM':
				sound6db = f->read<float>();
				readSize += 4;
				break;
			case 'JNAM':
				dayOuterBoundary = f->read<float>();
				readSize += 4;
				break;
			case 'KNAM':
				dayMiddleBoundary = f->read<float>();
				readSize += 4;
				break;
			case 'LNAM':
				dayInnerBoundary = f->read<float>();
				readSize += 4;
				break;
			case 'MNAM':
				nightOuterBoundary = f->read<float>();
				readSize += 4;
				break;
			case 'NNAM':
				nightMiddleBoundary = f->read<float>();
				readSize += 4;
				break;
			case 'ONAM':
				nightInnerBoundary = f->read<float>();
				readSize += 4;
				break;
			case 'PNAM':
				enableFlags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'DNAM':
				time1 = f->read<float>();
				readSize += 4;
				break;
			case 'ENAM':
				time2 = f->read<float>();
				readSize += 4;
				break;
			case 'FNAM':
				time3 = f->read<float>();
				readSize += 4;
				break;
			case 'GNAM':
				time4 = f->read<float>();
				readSize += 4;
				break;
			case 'HNAM':
				intro = f->read<formid>();
				readSize += 4;
				break;
			case 'INAM':
				outro = f->read<formid>();
				readSize += 4;
				break;
			case 'DATA':
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
		f->write<ulong>(type);
		WriteZStringSubrecord('NAM2',sound1,f);
		WriteZStringSubrecord('NAM3',sound2,f);
		WriteZStringSubrecord('NAM4',sound3,f);
		WriteZStringSubrecord('NAM5',sound4,f);
		WriteZStringSubrecord('NAM6',sound5,f);
		WriteZStringSubrecord('NAM7',sound6,f);
		WriteSubrecord('NAM8',4,f);
		f->write<float>(sound1db);
		WriteSubrecord('NAM9',4,f);
		f->write<float>(sound2db);
		WriteSubrecord('NAM0',4,f);
		f->write<float>(sound3db);
		WriteSubrecord('ANAM',4,f);
		f->write<float>(sound4db);
		WriteSubrecord('BNAM',4,f);
		f->write<float>(sound5db);
		WriteSubrecord('CNAM',4,f);
		f->write<float>(sound6db);
		WriteSubrecord('JNAM',4,f);
		f->write<float>(dayOuterBoundary);
		WriteSubrecord('KNAM',4,f);
		f->write<float>(dayMiddleBoundary);
		WriteSubrecord('LNAM',4,f);
		f->write<float>(dayInnerBoundary);
		WriteSubrecord('MNAM',4,f);
		f->write<float>(nightOuterBoundary);
		WriteSubrecord('NNAM',4,f);
		f->write<float>(nightMiddleBoundary);
		WriteSubrecord('ONAM',4,f);
		f->write<float>(nightInnerBoundary);
		WriteSubrecord('PNAM',1,f);
		f->write<ubyte>(enableFlags);
		WriteSubrecord('DNAM',4,f);
		f->write<float>(time1);
		WriteSubrecord('ENAM',4,f);
		f->write<float>(time2);
		WriteSubrecord('FNAM',4,f);
		f->write<float>(time3);
		WriteSubrecord('GNAM',4,f);
		f->write<float>(time4);
		if (intro)
		{
			WriteSubrecord('HNAM',4,f);
			f->write<formid>(intro);
		}
		if (outro)
		{
			WriteSubrecord('INAM',4,f);
			f->write<formid>(outro);
		}
		WriteSubrecord('DATA',0,f);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		size += ComputeSubrecordSize(4);
		size += ZStringSubrecordSize(sound1);
		size += ZStringSubrecordSize(sound2);
		size += ZStringSubrecordSize(sound3);
		size += ZStringSubrecordSize(sound4);
		size += ZStringSubrecordSize(sound5);
		size += ZStringSubrecordSize(sound6);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(1);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		if (intro)
		{
			size += ComputeSubrecordSize(4);
		}
		if (outro)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(0);
		return size;
	}
};
