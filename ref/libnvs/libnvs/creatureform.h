/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "actorbaseform.h"
struct Sound
{
	formid sound;
	ubyte chance;
};
struct SoundType
{
	ulong type;
	SimpleDynVecClass<Sound> sounds;
	SoundType() : sounds(0)
	{
	};
};
#pragma pack(push,1)
struct CreatureData
{
	ubyte type;
	ubyte combatSkill;
	ubyte magicSkill;
	ubyte stealthSkill;
	ulong health;
	ushort damage;
	ubyte strength;
	ubyte perception;
	ubyte endurance;
	ubyte charisma;
	ubyte intellegence;
	ubyte agillity;
	ubyte luck;
};
#pragma pack(pop)
class CreatureForm : public ActorBaseForm, public ModelList
{
protected:
	CreatureData data;
	ubyte attackReach;
	formid combatStyle;
	formid bodyPartData;
	float turningSpeed;
	float baseScale;
	float footWeight;
	ulong impactMaterialType;
	ulong soundLevel;
	formid inheritsSoundsFrom;
	SimpleDynVecClass<SoundType *> sounds;
	formid impactDataSet;
	formid meleeWeaponList;
public:
	CreatureForm(FormHeader h,ModFile *f) : ActorBaseForm(h,f), combatStyle(0), bodyPartData(0), inheritsSoundsFrom(0), impactDataSet(0), meleeWeaponList(0)
	{
	}
	virtual ~CreatureForm()
	{
		for (int i = 0;i < sounds.Count();i++)
		{
			delete sounds[i];
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentSound = -1;
		int currentSound2 = -1;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			BoundObjectFormLoad();
			FullNameLoad();
			ModelBRLoad(this,'MODL','MODB','MODT');
			SpellListLoad();
			EnchantableLoad();
			ModelListLoad();
			ActorBaseDataLoad();
			DestructibleObjectLoad();
			ScriptableLoad();
			ContainerLoad();
			AILoad();
			AnimationLoad();
			case 'DATA':
				data = f->read<CreatureData>();
				readSize += sizeof(CreatureData);
				break;
			case 'RNAM':
				attackReach = f->read<ubyte>();
				readSize += 1;
				break;
			case 'ZNAM':
				combatStyle = f->read<formid>();
				readSize += 4;
				break;
			case 'PNAM':
				bodyPartData = f->read<formid>();
				readSize += 4;
				break;
			case 'TNAM':
				turningSpeed = f->read<float>();
				readSize += 4;
				break;
			case 'BNAM':
				baseScale = f->read<float>();
				readSize += 4;
				break;
			case 'WNAM':
				footWeight = f->read<float>();
				readSize += 4;
				break;
			case 'NAM4':
				impactMaterialType = f->read<ulong>();
				readSize += 4;
				break;
			case 'NAM5':
				soundLevel = f->read<ulong>();
				readSize += 4;
				break;
			case 'CSCR':
				inheritsSoundsFrom = f->read<formid>();
				readSize += 4;
				break;
			case 'CSDT':
				{
					currentSound++;
					currentSound2 = -1;
					SoundType *t = new SoundType;
					t->type = f->read<ulong>();
					readSize += 4;
					sounds.Add(t);
				}
				break;
			case 'CSDI':
				{
					currentSound2++;
					Sound s;
					s.sound = f->read<formid>();
					readSize += 4;
					sounds[currentSound]->sounds.Add(s);
				}
				break;
			case 'CSDC':
				sounds[currentSound]->sounds[currentSound2].chance = f->read<ubyte>();
				readSize += 1;
				break;
			case 'CNAM':
				impactDataSet = f->read<formid>();
				readSize += 4;
				break;
			case 'LNAM':
				meleeWeaponList = f->read<formid>();
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
		ModelBRSave(this,'MODL','MODB','MODT');
		SpellListSave();
		EnchantableSave();
		ModelListSave();
		ActorBaseDataSave();
		DestructibleObjectSave();
		ScriptableSave();
		ContainerSave();
		AISave();
		AnimationSave();
		WriteSubrecord('DATA',sizeof(CreatureData),f);
		f->write<CreatureData>(data);
		WriteSubrecord('RNAM',1,f);
		f->write<ubyte>(attackReach);
		if (combatStyle)
		{
			WriteSubrecord('ZNAM',4,f);
			f->write<formid>(combatStyle);
		}
		if (bodyPartData)
		{
			WriteSubrecord('PNAM',4,f);
			f->write<formid>(bodyPartData);
		}
		WriteSubrecord('TNAM',4,f);
		f->write<float>(turningSpeed);
		WriteSubrecord('BNAM',4,f);
		f->write<float>(baseScale);
		WriteSubrecord('WNAM',4,f);
		f->write<float>(footWeight);
		WriteSubrecord('NAM4',4,f);
		f->write<ulong>(impactMaterialType);
		WriteSubrecord('NAM5',4,f);
		f->write<ulong>(soundLevel);
		if (actorBaseData.flags & 0x100)
		{
			for (int i = 0;i < sounds.Count();i++)
			{
				WriteSubrecord('CSDT',4,f);
				f->write<ulong>(sounds[i]->type);
				for (int j = 0;j < sounds[i]->sounds.Count();j++)
				{
					WriteSubrecord('CSDI',4,f);
					f->write<formid>(sounds[i]->sounds[j].sound);
					WriteSubrecord('CSDC',1,f);
					f->write<ubyte>(sounds[i]->sounds[j].chance);
				}
			}
		}
		else
		{
			if (inheritsSoundsFrom)
			{
				WriteSubrecord('CSCR',4,f);
				f->write<formid>(inheritsSoundsFrom);
			}
		}
		if (impactDataSet)
		{
			WriteSubrecord('CNAM',4,f);
			f->write<formid>(impactDataSet);
		}
		if (meleeWeaponList)
		{
			WriteSubrecord('LNAM',4,f);
			f->write<formid>(meleeWeaponList);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelBRGetSaveSize(this);
		SpellListGetSaveSize();
		EnchantableGetSaveSize();
		ModelListGetSaveSize();
		ActorBaseDataGetSaveSize();
		DestructibleObjectGetSaveSize();
		ScriptableGetSaveSize();
		ContainerGetSaveSize();
		AIGetSaveSize();
		AnimationGetSaveSize();
		size += ComputeSubrecordSize(sizeof(CreatureData));
		size += ComputeSubrecordSize(1);
		if (combatStyle)
		{
			size += ComputeSubrecordSize(4);
		}
		if (bodyPartData)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		if (actorBaseData.flags & 0x100)
		{
			for (int i = 0;i < sounds.Count();i++)
			{
				size += ComputeSubrecordSize(4);
				for (int j = 0;j < sounds[i]->sounds.Count();j++)
				{
					size += ComputeSubrecordSize(4);
					size += ComputeSubrecordSize(1);
				}
			}
		}
		else
		{
			if (inheritsSoundsFrom)
			{
				size += ComputeSubrecordSize(4);
			}
		}
		if (impactDataSet)
		{
			size += ComputeSubrecordSize(4);
		}
		if (meleeWeaponList)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
