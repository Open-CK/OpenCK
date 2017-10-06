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
struct BookData
{
	ubyte flags;
	byte skill;
	long value;
	float weight;
};
#pragma pack(pop)
class BookForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Texture, public Scriptable, public Enchantable, public Description, public DestructibleObject, public MessageTexture, public PickupPutdownSounds
{
protected:
	BookData data;
public:
	BookForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f)
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
			EnchantableLoad();
			DescriptionLoad();
			DestructibleObjectLoad();
			PickupPutdownSoundsLoad();
			case 'DATA':
				data = f->read<BookData>();
				readSize += sizeof(BookData);
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
		EnchantableSave();
		DescriptionSave();
		DestructibleObjectSave();
		PickupPutdownSoundsSave();
		WriteSubrecord('DATA',sizeof(BookData),f);
		f->write<BookData>(data);
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
		EnchantableGetSaveSize();
		DescriptionGetSaveSize();
		DestructibleObjectGetSaveSize();
		PickupPutdownSoundsGetSaveSize();
		size += ComputeSubrecordSize(sizeof(BookData));
		return size;
	}
};
