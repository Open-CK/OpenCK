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
struct ArmorData
{
	long value;
	long health;
	float weight;
};
struct ArmorData2
{
	short armorRating;
	float damageThreshold;
	ubyte flags;
	ubyte conditionLevel;
};
struct ArmorData2Old
{
	short armorRating;
	ubyte flags;
};
struct AnimationSound
{
	formid sound;
	ubyte chance;
	ulong type;
};
class ArmorForm : public BoundObjectForm, public FullName, public Scriptable, public Enchantable, public BipedModel, public DestructibleObject, public RepairItem, public BipedModelList, public EquipType, public PickupPutdownSounds
{
protected:
	ArmorData data;
	ArmorData2 data2;
	ArmorData2Old data2old;
	bool armorData2Old;
	ulong overridesAnimationSounds;
	bool hasOverridesAnimationSounds;
	formid animationSoundsTemplate;
	SimpleDynVecClass<AnimationSound> animationSounds;
public:
	ArmorForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), animationSoundsTemplate(0), armorData2Old(false), hasOverridesAnimationSounds(false)
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
			ScriptableLoad();
			EnchantableLoad();
			BipedModelLoad();
			DestructibleObjectLoad();
			RepairItemLoad();
			BipedModelListLoad();
			EquipTypeLoad();
			PickupPutdownSoundsLoad();
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
			case 'BNAM':
				overridesAnimationSounds = f->read<ulong>();
				hasOverridesAnimationSounds = true;
				readSize += 4;
				break;
			case 'SNAM':
				animationSounds.Add(f->read<AnimationSound>());
				readSize += sizeof(AnimationSound);
				break;
			case 'TNAM':
				animationSoundsTemplate = f->read<formid>();
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
		ScriptableSave();
		EnchantableSave();
		BipedModelSave();
		DestructibleObjectSave();
		RepairItemSave();
		BipedModelListSave();
		EquipTypeSave();
		PickupPutdownSoundsSave();
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
		if (hasOverridesAnimationSounds)
		{
			WriteSubrecord('BNAM',4,f);
			f->write<ulong>(overridesAnimationSounds);
			if (overridesAnimationSounds)
			{
				for (int i = 0;i < animationSounds.Count();i++)
				{
					WriteSubrecord('SNAM',sizeof(AnimationSound),f);
					f->write<AnimationSound>(animationSounds[i]);
				}
			}
			else
			{
				if (animationSoundsTemplate)
				{
					WriteSubrecord('TNAM',4,f);
					f->write<formid>(animationSoundsTemplate);
				}
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ScriptableGetSaveSize();
		EnchantableGetSaveSize();
		BipedModelGetSaveSize();
		DestructibleObjectGetSaveSize();
		RepairItemGetSaveSize();
		BipedModelListGetSaveSize();
		EquipTypeGetSaveSize();
		PickupPutdownSoundsGetSaveSize();
		size += ComputeSubrecordSize(sizeof(ArmorData));
		if (armorData2Old)
		{
			size += ComputeSubrecordSize(sizeof(ArmorData2Old));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(ArmorData2));
		}
		if (hasOverridesAnimationSounds)
		{
			size += ComputeSubrecordSize(4);
			if (overridesAnimationSounds)
			{
				for (int i = 0;i < animationSounds.Count();i++)
				{
					size += ComputeSubrecordSize(sizeof(AnimationSound));
				}
			}
			else
			{
				if (animationSoundsTemplate)
				{
					size += ComputeSubrecordSize(4);
				}
			}
		}
		return size;
	}
};
