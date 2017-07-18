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
class LeveledActorForm : public BoundObjectForm, public LeveledList, public ModelTextureSwap
{
public:
	LeveledActorForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f)
	{
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentItem = -1;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			BoundObjectFormLoad();
			LeveledListLoad();
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
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
		LeveledListSave();
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		LeveledListGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		return size;
	}
};
