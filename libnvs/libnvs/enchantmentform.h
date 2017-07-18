/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "magicform.h"
struct EffectData
{
	ulong enchantmentType;
	ulong chargeAmount;
	ulong enchantCost;
	ubyte flags;
};
class EnchantmentForm : public MagicForm
{
protected:
	EffectData effectData;
public:
	EnchantmentForm(FormHeader h,ModFile *f) : MagicForm(h,f)
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
			MagicFormLoad();
			case 'ENIT':
				effectData = f->read<EffectData>();
				readSize += sizeof(EffectData);
				break;
			EffectItemListLoad();
			default:
				printf("Unknown subrecord found");
				__debugbreak();
				break;
			}
		}
	}
	virtual void Save(FileWrite *f)
	{
		MagicFormSave();
		WriteSubrecord('ENIT',sizeof(EffectData),f);
		f->write<EffectData>(effectData);
		EffectItemListSave();
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		MagicFormGetSaveSize();
		size += ComputeSubrecordSize(sizeof(EffectData));
		EffectItemListGetSaveSize();
		return size;
	}
};
