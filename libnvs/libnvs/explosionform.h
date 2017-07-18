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
struct ExplosionData
{
	float force;
	float damage;
	float radius;
	formid light;
	formid sound1;
	ulong flags;
	float isRadius;
	formid impactDataset;
	formid sound2;
	float radiationLevel;
	float radiationDissipationTime;
	float radiationRadius;
	ulong soundLevel;
};
class ExplosionForm : public BoundObjectForm, public FullName, public Model, public Enchantable, public ImageSpaceModifiable
{
protected:
	ExplosionData data;
	formid impactObject;
public:
	ExplosionForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), impactObject(0)
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
			ModelBRLoad(this,'MODL','MODB','MODT');
			EnchantableLoad();
			ImageSpaceModifiableLoad();
			case 'DATA':
				data = f->read<ExplosionData>();
				readSize += h.size;
				break;
			case 'INAM':
				impactObject = f->read<formid>();
				readSize += h.size;
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
		ModelBRSave(this,'MODL','MODB','MODT');
		EnchantableSave();
		ImageSpaceModifiableSave();
		WriteSubrecord('DATA',sizeof(ExplosionData),f);
		f->write<ExplosionData>(data);
		if (impactObject)
		{
			WriteSubrecord('INAM',4,f);
			f->write<formid>(impactObject);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelBRGetSaveSize(this);
		EnchantableGetSaveSize();
		ImageSpaceModifiableGetSaveSize();
		size += ComputeSubrecordSize(sizeof(ExplosionData));
		if (impactObject)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
