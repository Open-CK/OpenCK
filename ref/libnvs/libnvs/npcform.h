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
#pragma pack(push,1)
struct NPCData
{
	long baseHealth;
	ubyte strength;
	ubyte perception;
	ubyte endurance;
	ubyte charisma;
	ubyte intellegence;
	ubyte agility;
	ubyte luck;
};
#pragma pack(pop)
struct NPCSkill
{
	ubyte barter;
	ubyte bigGuns;
	ubyte energy;
	ubyte explosives;
	ubyte lockPick;
	ubyte medicine;
	ubyte melee;
	ubyte repair;
	ubyte science;
	ubyte smallGuns;
	ubyte sneak;
	ubyte speech;
	ubyte throwing;
	ubyte unarmed;
	ubyte barterOffset;
	ubyte bigGunsOffset;
	ubyte energyOffset;
	ubyte explosivesOffset;
	ubyte lockPickOffset;
	ubyte medicineOffset;
	ubyte meleeOffset;
	ubyte repairOffset;
	ubyte scienceOffset;
	ubyte smallGunsOffset;
	ubyte sneakOffset;
	ubyte speechOffset;
	ubyte throwingOffset;
	ubyte unarmedOffset;
};
class NPCForm : public ActorBaseForm
{
protected:
	formid race;
	formid classType;
	NPCData data;
	NPCSkill skills;
	bool hasSkills;
	SimpleDynVecClass<formid> headParts;
	formid hair;
	float hairLength;
	formid eyes;
	ulong hairColor;
	formid combatStyle;
	ulong impactMaterialType;
	bool fggsSeen;
	ulong fggsSize;
	ubyte *fggs;
	bool fggaSeen;
	ulong fggaSize;
	ubyte *fgga;
	bool fgtsSeen;
	ulong fgtsSize;
	ubyte *fgts;
	ushort faceRace;
	float height;
	float weight;
	ubyte *npcDataExtra;
	ulong npcDataExtraCount;
public:
	NPCForm(FormHeader h,ModFile *f) : ActorBaseForm(h,f), race(0), classType(0), hair(0), hairLength(0), eyes(0), combatStyle(0), impactMaterialType(0), fggsSize(0), fggs(0), fggaSize(0), fgga(0), fgtsSize(0), fgts(0), faceRace(0), height(0), weight(0), hasSkills(false), fggsSeen(false), fggaSeen(false), fgtsSeen(false), npcDataExtra(0), npcDataExtraCount(0)
	{
	}
	virtual ~NPCForm()
	{
		if (fggs)
		{
			delete[] fggs;
		}
		if (fgga)
		{
			delete[] fgga;
		}
		if (fgts)
		{
			delete[] fgts;
		}
		if (npcDataExtra)
		{
			delete[] npcDataExtra;
		}
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
			ActorBaseDataLoad();
			case 'RNAM':
				race = f->read<formid>();
				readSize += 4;
				break;
			SpellListLoad();
			EnchantableLoad();
			DestructibleObjectLoad();
			ScriptableLoad();
			ContainerLoad();
			AILoad();
			AnimationLoad();
			case 'CNAM':
				classType = f->read<formid>();
				readSize += 4;
				break;
			case 'DATA':
				data = f->read<NPCData>();
				readSize += sizeof(NPCData);
				if (h.size > sizeof(NPCData))
				{
					npcDataExtraCount = h.size - sizeof(NPCData);
					npcDataExtra = f->readarray<ubyte>(npcDataExtraCount);
					readSize += npcDataExtraCount;
				}
				break;
			case 'DNAM':
				hasSkills = true;
				skills = f->read<NPCSkill>();
				readSize += sizeof(NPCSkill);
				break;
			case 'PNAM':
				headParts.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'HNAM':
				hair = f->read<formid>();
				readSize += 4;
				break;
			case 'LNAM':
				hairLength = f->read<float>();
				readSize += 4;
				break;
			case 'ENAM':
				eyes = f->read<formid>();
				readSize += 4;
				break;
			case 'HCLR':
				hairColor = f->read<ulong>();
				readSize += 4;
				break;
			case 'ZNAM':
				combatStyle = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM4':
				impactMaterialType = f->read<ulong>();
				readSize += 4;
				break;
			case 'FGGS':
				fggsSeen = true;
				fggsSize = h.size;
				fggs = f->readarray<ubyte>(fggsSize);
				readSize += h.size;
				break;
			case 'FGGA':
				fggaSeen = true;
				fggaSize = h.size;
				fgga = f->readarray<ubyte>(fggaSize);
				readSize += h.size;
				break;
			case 'FGTS':
				fgtsSeen = true;
				fgtsSize = h.size;
				fgts = f->readarray<ubyte>(fgtsSize);
				readSize += h.size;
				break;
			case 'NAM5':
				faceRace = f->read<ushort>();
				readSize += 2;
				break;
			case 'NAM6':
				height = f->read<float>();
				readSize += 4;
				break;
			case 'NAM7':
				weight = f->read<float>();
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
		ActorBaseDataSave();
		if (race)
		{
			WriteSubrecord('RNAM',4,f);
			f->write<formid>(race);
		}
		SpellListSave();
		EnchantableSave();
		DestructibleObjectSave();
		ScriptableSave();
		ContainerSave();
		AISave();
		AnimationSave();
		if (classType)
		{
			WriteSubrecord('CNAM',4,f);
			f->write<formid>(classType);
		}
		WriteSubrecord('DATA',sizeof(NPCData) + npcDataExtraCount,f);
		f->write<NPCData>(data);
		if (npcDataExtraCount)
		{
			f->writearray<ubyte>(npcDataExtraCount,npcDataExtra);
		}
		if (hasSkills)
		{
			WriteSubrecord('DNAM',sizeof(NPCSkill),f);
			f->write<NPCSkill>(skills);
		}
		for (int i = 0;i < headParts.Count();i++)
		{
			WriteSubrecord('PNAM',4,f);
			f->write<formid>(headParts[i]);
		}
		if (hair)
		{
			WriteSubrecord('HNAM',4,f);
			f->write<formid>(hair);
			WriteSubrecord('LNAM',4,f);
			f->write<float>(hairLength);
		}
		if (eyes)
		{
			WriteSubrecord('ENAM',4,f);
			f->write<formid>(eyes);
		}
		WriteSubrecord('HCLR',4,f);
		f->write<ulong>(hairColor);
		if (combatStyle)
		{
			WriteSubrecord('ZNAM',4,f);
			f->write<formid>(combatStyle);
		}
		WriteSubrecord('NAM4',4,f);
		f->write<ulong>(impactMaterialType);
		if (fggsSeen)
		{
			WriteSubrecord('FGGS',fggsSize,f);
			if (fggsSize)
			{
				f->writearray<ubyte>(fggsSize,fggs);
			}
		}
		if (fggaSeen)
		{
			WriteSubrecord('FGGA',fggaSize,f);
			if (fggaSize)
			{
				f->writearray<ubyte>(fggaSize,fgga);
			}
		}
		if (fgtsSeen)
		{
			WriteSubrecord('FGTS',fgtsSize,f);
			if (fgtsSize)
			{
				f->writearray<ubyte>(fgtsSize,fgts);
			}
		}
		WriteSubrecord('NAM5',2,f);
		f->write<ushort>(faceRace);
		WriteSubrecord('NAM6',4,f);
		f->write<float>(height);
		WriteSubrecord('NAM7',4,f);
		f->write<float>(weight);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelBRGetSaveSize(this);
		ActorBaseDataGetSaveSize();
		if (race)
		{
			size += ComputeSubrecordSize(4);
		}
		SpellListGetSaveSize();
		EnchantableGetSaveSize();
		DestructibleObjectGetSaveSize();
		ScriptableGetSaveSize();
		ContainerGetSaveSize();
		AIGetSaveSize();
		AnimationGetSaveSize();
		if (classType)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(sizeof(NPCData) + npcDataExtraCount);
		if (hasSkills)
		{
			size += ComputeSubrecordSize(sizeof(NPCSkill));
		}
		for (int i = 0;i < headParts.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		if (hair)
		{
			size += ComputeSubrecordSize(4);
			size += ComputeSubrecordSize(4);
		}
		if (eyes)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(4);
		if (combatStyle)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(4);
		if (fggsSeen)
		{
			size += ComputeSubrecordSize(fggsSize);
		}
		if (fggaSeen)
		{
			size += ComputeSubrecordSize(fggaSize);
		}
		if (fgtsSeen)
		{
			size += ComputeSubrecordSize(fgtsSize);
		}
		size += ComputeSubrecordSize(2);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		return size;
	}
};
