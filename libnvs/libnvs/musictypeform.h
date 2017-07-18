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
class MusicTypeForm : public Form, public SoundFile
{
	float db;
	bool hasanam;
public:
	MusicTypeForm(FormHeader h,ModFile *f) : Form(h,f), hasanam(false)
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
			SoundFileLoad();
			case 'ANAM':
				hasanam = true;
				db = f->read<float>();
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
		SoundFileSave();
		if (hasanam)
		{
			WriteSubrecord('ANAM',4,f);
			f->write<float>(db);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		SoundFileGetSaveSize();
		if (hasanam)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
