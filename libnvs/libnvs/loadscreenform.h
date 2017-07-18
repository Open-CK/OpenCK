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
struct LoadScreenLocation
{
	formid direct;
	formid indirect;
	ulong location;
};
class LoadScreenForm : public Form, public Texture, public Description
{
protected:
	SimpleDynVecClass<LoadScreenLocation> locations;
	formid type;
public:
	LoadScreenForm(FormHeader h,ModFile *f) : Form(h,f), type(0)
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
			TextureLoad(this,'ICON');
			DescriptionLoad();
			case 'LNAM':
				locations.Add(f->read<LoadScreenLocation>());
				readSize += sizeof(LoadScreenLocation);
				break;
			case 'WMI1':
				type = f->read<formid>();
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
		TextureSave(this,'ICON');
		DescriptionSave();
		for (int i = 0;i < locations.Count();i++)
		{
			WriteSubrecord('LNAM',sizeof(LoadScreenLocation),f);
			f->write<LoadScreenLocation>(locations[i]);
		}
		if (type)
		{
			WriteSubrecord('WMI1',4,f);
			f->write<formid>(type);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		TextureGetSaveSize(this);
		DescriptionGetSaveSize();
		for (int i = 0;i < locations.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(LoadScreenLocation));
		}
		if (type)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
