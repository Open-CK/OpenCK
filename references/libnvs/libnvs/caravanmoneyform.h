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
class CaravanMoneyForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Texture, public MessageTexture, public PickupPutdownSounds
{
protected:
	float value;
	ModelTextureSwap anteModel1;
	ModelTextureSwap anteModel2;
public:
	CaravanMoneyForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f)
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
			PickupPutdownSoundsLoad();
			case 'DATA':
				value = f->read<float>();
				readSize += 4;
				break;
			ModelTextureSwapBRLoad((&anteModel1),'MOD2','MO2B','MO2T','MO2S');
			ModelTextureSwapBRLoad((&anteModel2),'MOD3','MO3B','MO3T','MO3S');
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
		PickupPutdownSoundsSave();
		WriteSubrecord('DATA',4,f);
		f->write<float>(value);
		ModelTextureSwapBRSave((&anteModel1),'MOD2','MO2B','MO2T','MO2S');
		ModelTextureSwapBRSave((&anteModel2),'MOD3','MO3B','MO3T','MO3S');
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		TextureGetSaveSize(this);
		MessageTextureGetSaveSize(this);
		PickupPutdownSoundsGetSaveSize();
		size += ComputeSubrecordSize(4);
		ModelTextureSwapBRGetSaveSize((&anteModel1));
		ModelTextureSwapBRGetSaveSize((&anteModel2));
		return size;
	}
};
