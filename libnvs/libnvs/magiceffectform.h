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
struct MagicEffectData
{
	ulong flags;
	float baseCost;
	formid assocItem;
	long magicSchool;
	long resistanceType;
	ushort numCounters;
	formid light;
	float projectileSpeed;
	formid effectShader;
	formid objectDisplayShader;
	formid effectSound;
	formid boltSound;
	formid hitSound;
	formid areaSound;
	float enchantFactor;
	float barterFactor;
	ulong archType;
	long actorValue;
};
class MagicEffectForm : public Form, public FullName, public Description, public Texture, public Model
{
protected:
	MagicEffectData data;
	SimpleDynVecClass<formid> counters;
public:
	MagicEffectForm(FormHeader h,ModFile *f) : Form(h,f)
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
			FullNameLoad();
			DescriptionLoad();
			TextureLoad(this,'ICON');
			ModelBRLoad(this,'MODL','MODB','MODT');
			case 'DATA':
				data = f->read<MagicEffectData>();
				readSize += sizeof(MagicEffectData);
				break;
			case 'ESCE':
				counters.Add(f->read<formid>());
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
		FullNameSave();
		DescriptionSave();
		TextureSave(this,'ICON');
		ModelBRSave(this,'MODL','MODB','MODT');
		WriteSubrecord('DATA',sizeof(MagicEffectData),f);
		f->write<MagicEffectData>(data);
		for (int i = 0;i < counters.Count();i++)
		{
			WriteSubrecord('ESCE',4,f);
			f->write<formid>(counters[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		DescriptionGetSaveSize();
		TextureGetSaveSize(this);
		ModelBRGetSaveSize(this);
		size += ComputeSubrecordSize(sizeof(MagicEffectData));
		for (int i = 0;i < counters.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
