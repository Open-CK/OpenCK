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
class LandscapeTextureForm : public Form
{
protected:
	formid textureSet;
	ubyte materialType;
	ubyte friction;
	ubyte restitution;
	ubyte textureSpecularExponent;
	SimpleDynVecClass<formid> grassTypes;
public:
	LandscapeTextureForm(FormHeader h,ModFile *f) : Form(h,f), textureSet(0), materialType(0), friction(0), restitution(0), textureSpecularExponent(0), grassTypes(0)
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
			case 'TNAM':
				textureSet = f->read<formid>();
				readSize += 4;
				break;
			case 'HNAM':
				materialType = f->read<ubyte>();
				readSize += 1;
				friction = f->read<ubyte>();
				readSize += 1;
				restitution = f->read<ubyte>();
				readSize += 1;
				break;
			case 'SNAM':
				textureSpecularExponent = f->read<ubyte>();
				readSize += 1;
				break;
			case 'GNAM':
				grassTypes.Add(f->read<formid>());
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
		if (header.flags & 0x20)
		{
			return;
		}
		FormSave();
		if (textureSet)
		{
			WriteSubrecord('TNAM',4,f);
			f->write<formid>(textureSet);
		}
		WriteSubrecord('HNAM',3,f);
		f->write<ubyte>(materialType);
		f->write<ubyte>(friction);
		f->write<ubyte>(restitution);
		WriteSubrecord('SNAM',1,f);
		f->write<ubyte>(textureSpecularExponent);
		for (int i = 0;i < grassTypes.Count();i++)
		{
			WriteSubrecord('GNAM',4,f);
			f->write<formid>(grassTypes[i]);
		}
	}
	virtual int GetSaveSize()
	{
		if (header.flags & 0x20)
		{
			return 0;
		}
		int size = 0;
		FormGetSaveSize();
		if (textureSet)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(3);
		size += ComputeSubrecordSize(1);
		for (int i = 0;i < grassTypes.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
