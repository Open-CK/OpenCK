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
class FurnitureForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Scriptable, public DestructibleObject
{
protected:
	ulong markers;
public:
	FurnitureForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f)
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
			BoundObjectFormLoad();
			FullNameLoad();
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
			ScriptableLoad();
			DestructibleObjectLoad();
			case 'MNAM':
				markers = f->read<ulong>();
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
		BoundObjectFormSave();
		FullNameSave();
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		ScriptableSave();
		DestructibleObjectSave();
		WriteSubrecord('MNAM',4,f);
		f->write<ulong>(markers);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		ScriptableGetSaveSize();
		DestructibleObjectGetSaveSize();
		size += ComputeSubrecordSize(4);
		return size;
	}
};
