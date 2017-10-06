/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "magicobject.h"
struct AlchemyData
{
	long value;
	ubyte flags;
	formid withdrawalEffect;
	float addictionChance;
	formid consumeSound;
};
class AlchemyForm : public MagicObject, public ModelTextureSwap, public Texture, public MessageTexture, public Scriptable, public EquipType, public DestructibleObject, public PickupPutdownSounds
{
protected:
	float weight;
	AlchemyData data;
public:
	AlchemyForm(FormHeader h,ModFile *f) : MagicObject(h,f)
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
			EquipTypeLoad();
			case 'DATA':
				weight = f->read<float>();
				readSize += 4;
				break;
			case 'ENIT':
				data = f->read<AlchemyData>();
				readSize += sizeof(AlchemyData);
				break;
			ObjectEffectItemListLoad();
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
		EquipTypeSave();
		WriteSubrecord('DATA',4,f);
		f->write<float>(weight);
		WriteSubrecord('ENIT',sizeof(AlchemyData),f);
		f->write<AlchemyData>(data);
		ObjectEffectItemListSave();
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
		EquipTypeGetSaveSize();
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(sizeof(AlchemyData));
		ObjectEffectItemListGetSaveSize();
		return size;
	}
};
