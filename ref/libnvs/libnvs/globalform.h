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
class GlobalForm : public Form
{
protected:
	ubyte type;
	float value;
public:
	GlobalForm(FormHeader h,ModFile *f) : Form(h,f), type(0), value(0)
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
			case 'FNAM':
				type = f->read<ubyte>();
				readSize += 1;
				break;
			case 'FLTV':
				value = f->read<float>();
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
		WriteSubrecord('FNAM',1,f);
		f->write<ubyte>(type);
		WriteSubrecord('FLTV',4,f);
		f->write<float>(value);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		size += ComputeSubrecordSize(1);
		size += ComputeSubrecordSize(4);
		return size;
	}
};