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
class HeadPartForm : public Form, public FullName, public ModelTextureSwap
{
protected:
	ubyte flags;
	SimpleDynVecClass<formid> extraParts;
public:
	HeadPartForm(FormHeader h,ModFile *f) : Form(h,f)
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
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
			case 'DATA':
				flags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'HNAM':
				extraParts.Add(f->read<formid>());
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
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		WriteSubrecord('DATA',1,f);
		f->write<ubyte>(flags);
		for (int i = 0;i < extraParts.Count();i++)
		{
			WriteSubrecord('HNAM',4,f);
			f->write<formid>(extraParts[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		size += ComputeSubrecordSize(1);
		for (int i = 0;i < extraParts.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
