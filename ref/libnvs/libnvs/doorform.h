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
class DoorForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Scriptable, public DestructibleObject
{
protected:
	formid openSound;
	formid closeSound;
	formid loopSound;
	ubyte flags;
	SimpleDynVecClass<formid> teleports;
public:
	DoorForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), openSound(0), closeSound(0), loopSound(0), flags(0), teleports(0)
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
			case 'SNAM':
				openSound = f->read<formid>();
				readSize += 4;
				break;
			case 'ANAM':
				closeSound = f->read<formid>();
				readSize += 4;
				break;
			case 'BNAM':
				loopSound = f->read<formid>();
				readSize += 4;
				break;
			case 'FNAM':
				flags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'TNAM':
				teleports.Add(f->read<formid>());
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
		if (openSound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(openSound);
		}
		if (closeSound)
		{
			WriteSubrecord('ANAM',4,f);
			f->write<formid>(closeSound);
		}
		if (loopSound)
		{
			WriteSubrecord('BNAM',4,f);
			f->write<formid>(loopSound);
		}
		WriteSubrecord('FNAM',1,f);
		f->write<ubyte>(flags);
		for (int i = 0;i < teleports.Count();i++)
		{
			WriteSubrecord('TNAM',4,f);
			f->write<formid>(teleports[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		ScriptableGetSaveSize();
		DestructibleObjectGetSaveSize();
		if (openSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (closeSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (loopSound)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(1);
		for (int i = 0;i < teleports.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
