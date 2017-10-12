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
class MoveableStaticForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public DestructibleObject
{
protected:
	ubyte flags;
	formid sound;
	bool hasFlags;
public:
	MoveableStaticForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), sound(0), hasFlags(false)
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
			DestructibleObjectLoad();
			case 'DATA':
				hasFlags = true;
				flags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'SNAM':
				sound = f->read<formid>();
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
		DestructibleObjectSave();
		if (hasFlags)
		{
			WriteSubrecord('DATA',1,f);
			f->write<ubyte>(flags);
		}
		if (sound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(sound);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		DestructibleObjectGetSaveSize();
		if (hasFlags)
		{
			size += ComputeSubrecordSize(1);
		}
		if (sound)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
