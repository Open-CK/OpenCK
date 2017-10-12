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
#include "armorform.h"
class ArmorAddonForm : public BoundObjectForm, public FullName, public BipedModel, public EquipType
{
protected:
	ArmorData data;
	ArmorData2 data2;
	ArmorData2Old data2old;
	bool armorData2Old;
public:
	ArmorAddonForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), armorData2Old(false)
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
			BipedModelLoad();
			EquipTypeLoad();
			case 'DATA':
				data = f->read<ArmorData>();
				readSize += sizeof(ArmorData);
				break;
			case 'DNAM':
				if (h.size == 4)
				{
					data2old = f->read<ArmorData2Old>();
					readSize += sizeof(ArmorData2Old);
					armorData2Old = true;
				}
				else
				{
					data2 = f->read<ArmorData2>();
					readSize += sizeof(ArmorData2);
				}
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
		BipedModelSave();
		EquipTypeSave();
		WriteSubrecord('DATA',sizeof(ArmorData),f);
		f->write<ArmorData>(data);
		if (armorData2Old)
		{
			WriteSubrecord('DNAM',sizeof(ArmorData2Old),f);
			f->write<ArmorData2Old>(data2old);
		}
		else
		{
			WriteSubrecord('DNAM',sizeof(ArmorData2),f);
			f->write<ArmorData2>(data2);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		BipedModelGetSaveSize();
		EquipTypeGetSaveSize();
		size += ComputeSubrecordSize(sizeof(ArmorData));
		if (armorData2Old)
		{
			size += ComputeSubrecordSize(sizeof(ArmorData2Old));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(ArmorData2));
		}
		return size;
	}
};
