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
class ContainerForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Scriptable, public Container, public DestructibleObject
{
protected:
	ubyte flags;
	float weight;
	formid openSound;
	formid closeSound;
	formid sound;
public:
	ContainerForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), openSound(0), closeSound(0), sound(0)
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
			ContainerLoad();
			DestructibleObjectLoad();
			case 'DATA':
				flags = f->read<ubyte>();
				readSize += 1;
				weight = f->read<float>();
				readSize += 4;
				break;
			case 'SNAM':
				openSound = f->read<formid>();
				readSize += 4;
				break;
			case 'QNAM':
				closeSound = f->read<formid>();
				readSize += 4;
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
		FullNameSave();
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		ScriptableSave();
		ContainerSave();
		DestructibleObjectSave();
		WriteSubrecord('DATA',5,f);
		f->write<ubyte>(flags);
		f->write<float>(weight);
		if (openSound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(openSound);
		}
		if (closeSound)
		{
			WriteSubrecord('QNAM',4,f);
			f->write<formid>(closeSound);
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
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		ScriptableGetSaveSize();
		ContainerGetSaveSize();
		DestructibleObjectGetSaveSize();
		size += ComputeSubrecordSize(5);
		if (openSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (closeSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (sound)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
