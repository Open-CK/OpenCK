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
struct SpellData
{
	ulong spellType;
	ulong spellCost;
	ulong level;
	ubyte flags;
};
class SpellForm : public MagicForm
{
protected:
	SpellData spellData;
public:
	SpellForm(FormHeader h,ModFile *f) : MagicForm(h,f)
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
			case 'SPIT':
				spellData = f->read<SpellData>();
				readSize += sizeof(SpellData);
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
		WriteSubrecord('SPIT',sizeof(SpellData),f);
		f->write<SpellData>(spellData);
		EffectItemListSave();
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		MagicFormGetSaveSize();
		size += ComputeSubrecordSize(sizeof(SpellData));
		EffectItemListGetSaveSize();
		return size;
	}
};
