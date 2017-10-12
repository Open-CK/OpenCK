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
class AnimatedObjectForm : public Form, public ModelTextureSwap
{
protected:
	formid idleAnimation;
public:
	AnimatedObjectForm(FormHeader h,ModFile *f) : Form(h,f), idleAnimation(0)
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
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
			case 'DATA':
				idleAnimation = f->read<formid>();
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
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		if (idleAnimation)
		{
			WriteSubrecord('DATA',4,f);
			f->write<formid>(idleAnimation);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		if (idleAnimation)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
