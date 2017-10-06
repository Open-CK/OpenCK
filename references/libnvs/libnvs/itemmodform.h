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
#pragma pack(push,1)
struct ItemModData
{
	long value;
	float weight;
};
#pragma pack(pop)
class ItemModForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Texture, public Scriptable, public Description, public DestructibleObject, public MessageTexture, public PickupPutdownSounds
{
protected:
	ItemModData data;
public:
	ItemModForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f)
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
			DescriptionLoad();
			DestructibleObjectLoad();
			PickupPutdownSoundsLoad();
			case 'DATA':
				data = f->read<ItemModData>();
				readSize += sizeof(ItemModData);
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
		DescriptionSave();
		DestructibleObjectSave();
		PickupPutdownSoundsSave();
		WriteSubrecord('DATA',sizeof(ItemModData),f);
		f->write<ItemModData>(data);
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
		DescriptionGetSaveSize();
		DestructibleObjectGetSaveSize();
		PickupPutdownSoundsGetSaveSize();
		size += ComputeSubrecordSize(sizeof(ItemModData));
		return size;
	}
};
