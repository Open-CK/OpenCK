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
class VoiceTypeForm : public Form
{
protected:
	ubyte flags;
	bool hasFlags;
public:
	VoiceTypeForm(FormHeader h,ModFile *f) : Form(h,f), hasFlags(false)
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
			case 'DNAM':
				hasFlags = true;
				flags = f->read<ubyte>();
				readSize += 1;
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
		if (hasFlags)
		{
			WriteSubrecord('DNAM',1,f);
			f->write<ubyte>(flags);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		if (hasFlags)
		{
			size += ComputeSubrecordSize(1);
		}
		return size;
	}
};
