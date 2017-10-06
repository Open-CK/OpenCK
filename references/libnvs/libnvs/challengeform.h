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
struct ChallengeData
{
	ulong type;
	ulong threshold;
	ushort flags;
	ulong interval;
	ushort value1;
	ushort value2;
	ushort value3;
};
class ChallengeForm : public Form, public FullName, public Texture, public MessageTexture, public Scriptable, public Description
{
protected:
	ChallengeData data;
	formid value3;
	formid value4;
public:
	ChallengeForm(FormHeader h,ModFile *f) : Form(h,f), value3(0), value4(0)
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
			ScriptableLoad();
			DescriptionLoad();
			case 'DATA':
				data = f->read<ChallengeData>();
				readSize += sizeof(ChallengeData);
				break;
			case 'SNAM':
				value3 = f->read<formid>();
				readSize += 4;
				break;
			case 'XNAM':
				value4 = f->read<formid>();
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
		ScriptableSave();
		DescriptionSave();
		WriteSubrecord('DATA',sizeof(ChallengeData),f);
		f->write<ChallengeData>(data);
		if (value3)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(value3);
		}
		if (value4)
		{
			WriteSubrecord('XNAM',4,f);
			f->write<formid>(value4);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		TextureGetSaveSize(this);
		MessageTextureGetSaveSize(this);
		ScriptableGetSaveSize();
		DescriptionGetSaveSize();
		size += ComputeSubrecordSize(sizeof(ChallengeData));
		if (value3)
		{
			size += ComputeSubrecordSize(4);
		}
		if (value4)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
