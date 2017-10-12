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
struct ActorBaseData
{
	ulong flags;
	ushort fatigue;
	ushort barterGold;
	short level;
	ushort calcMin;
	ushort calcMax;
	ushort speedMult;
	float karma;
	short disposition;
	ushort templateFlags;
};
struct Faction
{
	formid faction;
	ubyte rank;
};
struct AIData
{
	ubyte aggression;
	ubyte confidence;
	ubyte energyLevel;
	ubyte responsibility;
	ubyte mood;
	ulong services;
	byte teaches;
	ubyte maxTrainingLevel;
	byte assistance;
	ubyte aggroBehaviour;
	long aggroRadius;
};
#define ActorBaseDataLoad(); \
			case 'ACBS': \
				actorBaseData = f->read<ActorBaseData>(); \
				readSize += sizeof(ActorBaseData); \
				break; \
			case 'SNAM': \
				factions.Add(f->read<Faction>()); \
				readSize += sizeof(Faction); \
				break; \
			case 'INAM': \
				deathItem = f->read<formid>(); \
				readSize += 4; \
				break; \
			case 'VTCK': \
				voice = f->read<formid>(); \
				readSize += 4; \
				break; \
			case 'TPLT': \
				actorTemplate = f->read<formid>(); \
				readSize += 4; \
				break;
#define ActorBaseDataSave(); \
		WriteSubrecord('ACBS',sizeof(ActorBaseData),f); \
		f->write<ActorBaseData>(actorBaseData); \
		for (int factionCount = 0;factionCount < factions.Count();factionCount++) \
		{ \
			WriteSubrecord('SNAM',sizeof(Faction),f); \
			f->write<Faction>(factions[factionCount]); \
		} \
		if (deathItem) \
		{ \
			WriteSubrecord('INAM',4,f); \
			f->write<formid>(deathItem); \
		} \
		if (voice) \
		{ \
			WriteSubrecord('VTCK',4,f); \
			f->write<formid>(voice); \
		} \
		if (actorTemplate) \
		{ \
			WriteSubrecord('TPLT',4,f); \
			f->write<formid>(actorTemplate); \
		}
#define ActorBaseDataGetSaveSize(); \
		size += ComputeSubrecordSize(sizeof(ActorBaseData)); \
		for (int factionCount = 0;factionCount < factions.Count();factionCount++) \
		{ \
			size += ComputeSubrecordSize(sizeof(Faction)); \
		} \
		if (deathItem) \
		{ \
			size += ComputeSubrecordSize(4); \
		} \
		if (voice) \
		{ \
			size += ComputeSubrecordSize(4); \
		} \
		if (actorTemplate) \
		{ \
			size += ComputeSubrecordSize(4); \
		}
#define AILoad(); \
			case 'AIDT': \
				aiData = f->read<AIData>(); \
				readSize += sizeof(AIData); \
				break; \
			case 'PKID': \
				packages.Add(f->read<formid>()); \
				readSize += 4; \
				break;
#define AISave(); \
		WriteSubrecord('AIDT',sizeof(AIData),f); \
		f->write<AIData>(aiData); \
		for (int packageCount = 0;packageCount < packages.Count();packageCount++) \
		{ \
			WriteSubrecord('PKID',4,f); \
			f->write<formid>(packages[packageCount]); \
		}
#define AIGetSaveSize() \
		size += ComputeSubrecordSize(sizeof(AIData)); \
		for (int packageCount = 0;packageCount < packages.Count();packageCount++) \
		{ \
			size += ComputeSubrecordSize(4); \
		}
#define AnimationLoad() \
			case 'KFFZ': \
				animationsSize = h.size; \
				animations = f->readarray<char>(animationsSize); \
				readSize += h.size; \
				break;
#define AnimationSave() \
		if (animationsSize) \
		{ \
			WriteSubrecord('KFFZ',animationsSize,f); \
			f->writearray<char>(animationsSize,animations); \
		}
#define AnimationGetSaveSize() \
		if (animationsSize) \
		{ \
			size += ComputeSubrecordSize(animationsSize); \
		}

class ActorBaseForm : public BoundObjectForm, public Container, public Enchantable, public SpellList, public FullName, public Model, public Scriptable, public DestructibleObject
{
protected:
	ActorBaseData actorBaseData;
	SimpleDynVecClass<Faction> factions;
	formid deathItem;
	formid voice;
	formid actorTemplate;
	AIData aiData;
	SimpleDynVecClass<formid> packages;
	int animationsSize;
	char *animations;
public:
	ActorBaseForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), deathItem(0), voice(0), actorTemplate(0), animationsSize(0), animations(0)
	{
	}
	virtual ~ActorBaseForm()
	{
		if (animations)
		{
			delete[] animations;
		}
	}
};
