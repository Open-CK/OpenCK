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
class HairForm : public Form, public FullName, public Model, public Texture
{
protected:
	ubyte flags;
public:
	HairForm(FormHeader h,ModFile *f) : Form(h,f)
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
			ModelBRLoad(this,'MODL','MODB','MODT');
			TextureLoad(this,'ICON');
			case 'DATA':
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
		FullNameSave();
		ModelBRSave(this,'MODL','MODB','MODT');
		TextureSave(this,'ICON');
		WriteSubrecord('DATA',1,f);
		f->write<ubyte>(flags);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		ModelBRGetSaveSize(this);
		TextureGetSaveSize(this);
		size += ComputeSubrecordSize(1);
		return size;
	}
};
