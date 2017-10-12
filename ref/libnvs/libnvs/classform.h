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
struct ClassData
{
	ulong tagSkills[4];
	ulong classFlags;
	ulong services;
	ubyte teaches;
	ubyte trainingLevel;
};
class ClassForm : public Form, public FullName, public Description, public Texture
{
protected:
	ClassData data;
	ubyte attributes[7];
public:
	ClassForm(FormHeader h,ModFile *f) : Form(h,f)
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
			DescriptionLoad();
			TextureLoad(this,'ICON');
			case 'DATA':
				data = f->read<ClassData>();
				readSize += sizeof(ClassData);
				break;
			case 'ATTR':
				f->readarray<ubyte>(7,attributes);
				readSize += 7;
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
		WriteSubrecord('DATA',sizeof(ClassData),f);
		f->write<ClassData>(data);
		WriteSubrecord('ATTR',7,f);
		f->writearray<ubyte>(7,attributes);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		DescriptionGetSaveSize();
		TextureGetSaveSize(this);
		size += ComputeSubrecordSize(sizeof(ClassData));
		size += ComputeSubrecordSize(7);
		return size;
	}
};
