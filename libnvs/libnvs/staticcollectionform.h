/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "boundobjectform.h"
class StaticCollectionForm : public BoundObjectForm, public ModelTextureSwap
{
protected:
	SimpleDynVecClass<formid> parts;
	SimpleDynVecClass<ulong> partCounts;
	SimpleDynVecClass<Position *> partData;
public:
	StaticCollectionForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f)
	{
	}
	virtual ~StaticCollectionForm()
	{
		for (int i = 0;i < partData.Count();i++)
		{
			delete[] partData[i];
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
			BoundObjectFormLoad();
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
			case 'ONAM':
				parts.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'DATA':
				partCounts.Add(h.size / sizeof(Position));
				partData.Add(f->readarray<Position>(h.size / sizeof(Position)));
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
		BoundObjectFormSave();
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		for (int i = 0;i < parts.Count();i++)
		{
			WriteSubrecord('ONAM',4,f);
			f->write<formid>(parts[i]);
			WriteSubrecord('DATA',partCounts[i] * sizeof(Position),f);
			f->writearray<Position>(partCounts[i],partData[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		for (int i = 0;i < parts.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			size += ComputeSubrecordSize(partCounts[i] * sizeof(Position));
		}
		return size;
	}
};
