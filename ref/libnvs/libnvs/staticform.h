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
class StaticForm : public BoundObjectForm, public ModelTextureSwap
{
protected:
	byte passthroughSound;
	bool hasPassthroughSound;
	formid sound;
public:
	StaticForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), sound(0), hasPassthroughSound(false)
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
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
			case 'BRUS':
				passthroughSound = f->read<byte>();
				hasPassthroughSound = true;
				readSize += 1;
				break;
			case 'RNAM':
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
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		if (hasPassthroughSound)
		{
			WriteSubrecord('BRUS',1,f);
			f->write<byte>(passthroughSound);
		}
		if (sound)
		{
			WriteSubrecord('RNAM',4,f);
			f->write<formid>(sound);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		if (hasPassthroughSound)
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
