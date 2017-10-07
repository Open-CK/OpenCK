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
struct TreeData
{
	float curvature;
	float minAngle;
	float maxAngle;
	float branchDim;
	float leafDim;
	long shadowRadius;
	float rockSpeed;
	float rustleSpeed;
};
class TreeForm : public BoundObjectForm, public Model, public Texture, public DestructibleObject
{
protected:
	ulong seedCount;
	ulong *seeds;
	TreeData data;
	NiPoint2 billboardDimentions;
public:
	TreeForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), seedCount(0), seeds(0)
	{
	}
	virtual ~TreeForm()
	{
		if (seeds)
		{
			delete[] seeds;
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
			ModelBRLoad(this,'MODL','MODB','MODT');
			TextureLoad(this,'ICON');
			DestructibleObjectLoad();
			case 'SNAM':
				seedCount = h.size / 4;
				seeds = f->readarray<ulong>(seedCount);
				readSize += h.size;
				break;
			case 'CNAM':
				data = f->read<TreeData>();
				readSize += sizeof(TreeData);
				break;
			case 'BNAM':
				billboardDimentions = f->read<NiPoint2>();
				readSize += sizeof(NiPoint2);
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
		ModelBRSave(this,'MODL','MODB','MODT');
		TextureSave(this,'ICON');
		DestructibleObjectSave();
		if (seeds)
		{
			WriteSubrecord('SNAM',seedCount * 4,f);
			f->writearray<ulong>(seedCount,seeds);
		}
		WriteSubrecord('CNAM',sizeof(TreeData),f);
		f->write<TreeData>(data);
		WriteSubrecord('BNAM',sizeof(NiPoint2),f);
		f->write<NiPoint2>(billboardDimentions);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		ModelBRGetSaveSize(this);
		TextureGetSaveSize(this);
		DestructibleObjectGetSaveSize();
		if (seeds)
		{
			size += ComputeSubrecordSize(seedCount * 4);
		}
		size += ComputeSubrecordSize(sizeof(TreeData));
		size += ComputeSubrecordSize(sizeof(NiPoint2));
		return size;
	}
};
