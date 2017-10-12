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
class ActorValueInfoForm : public Form, public FullName, public Description, public Texture
{
protected:
	char *shortName;
public:
	ActorValueInfoForm(FormHeader h,ModFile *f) : Form(h,f), shortName(0)
	{
	}
	virtual ~ActorValueInfoForm()
	{
		if (shortName)
		{
			delete[] shortName;
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
			DescriptionLoad();
			TextureLoad(this,'ICON');
			case 'ANAM':
				shortName = f->readzstring(h.size);
				readSize += h.size;
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
		DescriptionSave();
		TextureSave(this,'ICON');
		WriteZStringSubrecord('ANAM',shortName,f);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		DescriptionGetSaveSize();
		TextureGetSaveSize(this);
		size += ZStringSubrecordSize(shortName);
		return size;
	}
};
