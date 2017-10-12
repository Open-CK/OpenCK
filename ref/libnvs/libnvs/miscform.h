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
struct MiscData
{
	long value;
	float weight;
};
class MiscForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Texture, public MessageTexture, public Scriptable, public DestructibleObject, public PickupPutdownSounds
{
protected:
	MiscData data;
	formid sound;
public:
	MiscForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), sound(0)
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
			TextureLoad(this,'ICON');
			MessageTextureLoad(this,'MICO');
			ScriptableLoad();
			DestructibleObjectLoad();
			PickupPutdownSoundsLoad();
			case 'DATA':
				data = f->read<MiscData>();
				readSize += sizeof(MiscData);
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
		TextureSave(this,'ICON');
		MessageTextureSave(this,'MICO');
		ScriptableSave();
		DestructibleObjectSave();
		PickupPutdownSoundsSave();
		WriteSubrecord('DATA',sizeof(MiscData),f);
		f->write<MiscData>(data);
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
		TextureGetSaveSize(this);
		MessageTextureGetSaveSize(this);
		ScriptableGetSaveSize();
		DestructibleObjectGetSaveSize();
		PickupPutdownSoundsGetSaveSize();
		size += ComputeSubrecordSize(sizeof(MiscData));
		if (sound)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
