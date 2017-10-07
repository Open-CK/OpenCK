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
class ReputationForm : public Form, public FullName, public Texture, public MessageTexture
{
protected:
	float value;
public:
	ReputationForm(FormHeader h,ModFile *f) : Form(h,f)
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
			TextureLoad(this,'ICON');
			MessageTextureLoad(this,'MICO');
			case 'DATA':
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
		FullNameSave();
		TextureSave(this,'ICON');
		MessageTextureSave(this,'MICO');
		WriteSubrecord('DATA',4,f);
		f->write<float>(value);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		TextureGetSaveSize(this);
		MessageTextureGetSaveSize(this);
		size += ComputeSubrecordSize(4);
		return size;
	}
};
