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
struct IngredientData
{
	long value;
	ubyte flags;
};
class IngredientItemForm : public MagicObject, public ModelTextureSwap, public Texture, public Scriptable, public EquipType, public DestructibleObject
{
protected:
	float weight;
	IngredientData data;
public:
	IngredientItemForm(FormHeader h,ModFile *f) : MagicObject(h,f)
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
			ScriptableLoad();
			DestructibleObjectLoad();
			EquipTypeLoad();
			case 'DATA':
				weight = f->read<float>();
				readSize += 4;
				break;
			case 'ENIT':
				data = f->read<IngredientData>();
				readSize += sizeof(IngredientData);
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
		ScriptableSave();
		DestructibleObjectSave();
		EquipTypeSave();
		WriteSubrecord('DATA',4,f);
		f->write<float>(weight);
		WriteSubrecord('ENIT',sizeof(IngredientData),f);
		f->write<IngredientData>(data);
		ObjectEffectItemListSave();
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		TextureGetSaveSize(this);
		ScriptableGetSaveSize();
		DestructibleObjectGetSaveSize();
		EquipTypeGetSaveSize();
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(sizeof(IngredientData));
		ObjectEffectItemListGetSaveSize();
		return size;
	}
};
