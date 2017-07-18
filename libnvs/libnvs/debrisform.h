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
struct DebrisModel
{
	ubyte percentage;
	char *model;
	ubyte flags;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	DebrisModel() : model(0), textureHashesCount(0), textureHashes(0)
	{
	}
	virtual ~DebrisModel()
	{
		if (model)
		{
			delete[] model;
		}
		if (textureHashes)
		{
			delete[] textureHashes;
		}
	}
};
class DebrisForm : public Form
{
protected:
	SimpleDynVecClass<DebrisModel *> debris;
public:
	DebrisForm(FormHeader h,ModFile *f) : Form(h,f)
	{
	}
	~DebrisForm()
	{
		for (int i = 0;i < debris.Count();i++)
		{
			delete debris[i];
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentDebris = -1;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			case 'DATA':
				currentDebris++;
				debris.Add(new DebrisModel());
				debris[currentDebris]->percentage = f->read<ubyte>();
				debris[currentDebris]->model = f->readzstring(h.size - 2);
				debris[currentDebris]->flags = f->read<ubyte>();
				readSize += h.size;
				break;
			case 'MODT':
				debris[currentDebris]->textureHashesCount = h.size / sizeof(TextureHash);
				debris[currentDebris]->textureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
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
		for (int i = 0;i < debris.Count();i++)
		{
			WriteSubrecord('DATA',strlen(debris[i]->model) + 3,f);
			f->write<ubyte>(debris[i]->percentage);
			f->writezstring(strlen(debris[i]->model) + 1,debris[i]->model);
			f->write<ubyte>(debris[i]->flags);
			if (debris[i]->textureHashesCount)
			{
				WriteSubrecord('MODT',debris[i]->textureHashesCount * sizeof(TextureHash),f);
				f->writearray<TextureHash>(debris[i]->textureHashesCount,debris[i]->textureHashes);
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		for (int i = 0;i < debris.Count();i++)
		{
			size += ComputeSubrecordSize(strlen(debris[i]->model) + 3);
			if (debris[i]->textureHashesCount)
			{
				size += ComputeSubrecordSize(debris[i]->textureHashesCount * sizeof(TextureHash));
			}
		}
		return size;
	}
};
