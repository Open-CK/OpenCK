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
class CaravanCardForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Texture, public MessageTexture, public Scriptable, public PickupPutdownSounds
{
protected:
	Texture face;
	Texture back;
	ulong cardSuit;
	ulong cardValue;
	float value;
public:
	CaravanCardForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), cardSuit(0), cardValue(0)
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
			PickupPutdownSoundsLoad();
			TextureLoad((&face),'TX00');
			TextureLoad((&back),'TX01');
			case 'INTV':
				if (!cardSuit)
				{
					cardSuit = f->read<ulong>();
				}
				else
				{
					cardValue = f->read<ulong>();
				}
				readSize += 4;
				break;
			case 'DATA':
				value = f->read<float>();
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
		PickupPutdownSoundsSave();
		TextureSave((&face),'TX00');
		TextureSave((&back),'TX01');
		WriteSubrecord('INTV',4,f);
		f->write<ulong>(cardSuit);
		WriteSubrecord('INTV',4,f);
		f->write<ulong>(cardValue);
		WriteSubrecord('DATA',4,f);
		f->write<float>(value);
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
		PickupPutdownSoundsGetSaveSize();
		TextureGetSaveSize((&face));
		TextureGetSaveSize((&back));
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		return size;
	}
};
