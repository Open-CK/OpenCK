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
struct PackageData
{
	ulong flags;
	ubyte type;
	ushort behaviourFlags;
	ushort typeFlags;
};
struct PackageDataOld
{
	ulong flags;
	ubyte type;
	ushort behaviourFlags;
};
struct PackageLocation
{
	ulong type;
	formid location;
	long radius;
};
struct PackageSchedule
{
	byte month;
	byte dayOfWeek;
	ubyte date;
	byte time;
	long duration;
};
struct PackageTarget
{
	long type;
	formid target;
	long count;
	float unk;
};
struct PackageTargetOld
{
	long type;
	formid target;
	long count;
};
struct UseWeaponData
{
	ubyte alwaysHit;
	ubyte doNoDamage;
	ubyte crouchToReload;
	ubyte holdFireWhenBlocked;
	ubyte fireRate;
	ubyte fireCount;
	ushort numBursts;
	ushort shotsPerVolleyMin;
	ushort shotsPerVolleyMax;
	float pauseBetweenVolleysMin;
	float pauseBetweenVolleysMax;
	formid unk;
};
struct DialogueData
{
	float fov;
	formid topic;
	ubyte noHeadTracking;
	ubyte dontControlTargetMovement;
	ulong unk1;
	ulong dialogueType;
	ulong unk2;
};
struct DialogueDataOld
{
	float fov;
	formid topic;
	ubyte noHeadTracking;
	ubyte dontControlTargetMovement;
	ulong unk1;
	ulong dialogueType;
};
struct DialogueDataOld2
{
	float fov;
	formid topic;
	ubyte noHeadTracking;
	ubyte dontControlTargetMovement;
	ulong unk1;
};
struct DialogueDataOld3
{
	float fov;
	formid topic;
	ubyte noHeadTracking;
	ubyte dontControlTargetMovement;
};
struct ScriptData
{
	formid idle;
	Script script;
	formid topic;
	ScriptData() : idle(0), topic(0)
	{
	}
};
enum PackageTypes
{
	find = 0,
	follow = 1,
	escort = 2,
	eat = 3,
	sleep = 4,
	wander = 5,
	travel = 6,
	accompany = 7,
	useItemAt = 8,
	ambush = 9,
	fleeNotCombat = 10,
	unk = 11,
	sandbox = 12,
	patrol = 13,
	guard = 14,
	dialogue = 15,
	useWeapon = 16
};
class PackageForm : public Form, public IdleCollection
{
protected:
	PackageData data;
	PackageDataOld oldData;
	bool hasOldData;
	PackageLocation location1;
	bool location1Present;
	PackageLocation location2;
	bool location2Present;
	PackageSchedule schedule;
	PackageTarget target1;
	PackageTargetOld target1Old;
	bool hasTarget1Old;
	bool target1Present;
	SimpleDynVecClass<Condition> conditions;
	SimpleDynVecClass<ConditionOld> oldConditions;
	SimpleDynVecClass<ConditionOld2> oldConditions2;
	formid combatStyle;
	bool loadingPackage;
	ulong escortDistance;
	float followRadius;
	ushort patrolFlags;
	ubyte patrolFlagsOld;
	bool hasPatrolFlagsOld;
	UseWeaponData useWeaponData;
	PackageTarget target2;
	PackageTargetOld target2Old;
	bool target2Present;
	bool hasTarget2Old;
	DialogueData dialogueData;
	DialogueDataOld oldDialogueData;
	DialogueDataOld2 oldDialogueData2;
	DialogueDataOld3 oldDialogueData3;
	bool hasOldDialogueData;
	bool hasOldDialogueData2;
	bool hasOldDialogueData3;
	PackageLocation location3;
	bool location3Present;
	ScriptData onBegin;
	ScriptData onEnd;
	ScriptData onChange;
	bool hasOnBegin;
	bool hasOnEnd;
	bool hasOnChange;
	bool dialogDataPresent;
	bool hasFollowRadius;
	bool hasUseWeaponData;
	bool hasPatrolFlags;
	bool hasEatMarker;
public:
	PackageForm(FormHeader h,ModFile *f) : Form(h,f), location1Present(false), location2Present(false), target1Present(false), combatStyle(0), loadingPackage(false), target2Present(false), location3Present(false), dialogDataPresent(false), hasOldData(false), hasPatrolFlagsOld(false), hasOldDialogueData(false), hasOldDialogueData2(false), hasTarget1Old(false), hasTarget2Old(false), hasOldDialogueData3(false), hasFollowRadius(false), hasOnBegin(false), hasOnEnd(false), hasOnChange(false), hasUseWeaponData(false), hasPatrolFlags(false), hasEatMarker(false)
	{
	}
protected:
	virtual void Load(FileRead *f)
	{
		ScriptData *scr = &onBegin;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			case 'PKDT':
				if (h.size == sizeof(PackageData))
				{
					data = f->read<PackageData>();
					readSize += sizeof(PackageData);
				}
				else if (h.size == sizeof(PackageDataOld))
				{
					hasOldData = true;
					oldData = f->read<PackageDataOld>();
					memcpy(&data,&oldData,sizeof(PackageDataOld));
					readSize += sizeof(PackageDataOld);
				}
				break;
			case 'PLDT':
				location1Present = true;
				location1 = f->read<PackageLocation>();
				readSize += sizeof(PackageLocation);
				break;
			case 'PLD2':
				if (!loadingPackage)
				{
					location2Present = true;
					location2 = f->read<PackageLocation>();
				}
				else
				{
					location3Present = true;
					location3 = f->read<PackageLocation>();
				}
				readSize += sizeof(PackageLocation);
				break;
			case 'PSDT':
				schedule = f->read<PackageSchedule>();
				readSize += sizeof(PackageSchedule);
				break;
			case 'PTDT':
				target1Present = true;
				if (h.size == sizeof(PackageTarget))
				{
					target1 = f->read<PackageTarget>();
					readSize += sizeof(PackageTarget);
				}
				else if (h.size == sizeof(PackageTargetOld))
				{
					hasTarget1Old = true;
					target1Old = f->read<PackageTargetOld>();
					readSize += sizeof(PackageTargetOld);
				}
				break;
			case 'CTDA':
				if (h.size == sizeof(Condition))
				{
					conditions.Add(f->read<Condition>());
					readSize += sizeof(Condition);
				}
				else if (h.size == sizeof(ConditionOld))
				{
					oldConditions.Add(f->read<ConditionOld>());
					readSize += sizeof(ConditionOld);
				}
				else if (h.size == sizeof(ConditionOld2))
				{
					oldConditions2.Add(f->read<ConditionOld2>());
					readSize += sizeof(ConditionOld2);
				}
				break;
			IdleCollectionLoad();
			case 'CNAM':
				combatStyle = f->read<formid>();
				readSize += 4;
				break;
			case 'PKED':
				hasEatMarker = true;
				loadingPackage = true;
				break;
			case 'PKE2':
				loadingPackage = true;
				escortDistance = f->read<ulong>();
				readSize += 4;
				break;
			case 'PKFD':
				loadingPackage = true;
				hasFollowRadius = true;
				followRadius = f->read<float>();
				readSize += 4;
				break;
			case 'PKPT':
				hasPatrolFlags = true;
				loadingPackage = true;
				if (h.size == 2)
				{
					patrolFlags = f->read<ushort>();
					readSize += 2;
				}
				else
				{
					hasPatrolFlagsOld = true;
					patrolFlagsOld = f->read<ubyte>();
					readSize += 1;
				}
				break;
			case 'PKW3':
				hasUseWeaponData = true;
				loadingPackage = true;
				useWeaponData = f->read<UseWeaponData>();
				readSize += sizeof(UseWeaponData);
				break;
			case 'PTD2':
				target2Present = true;
				if (h.size == sizeof(PackageTarget))
				{
					target2 = f->read<PackageTarget>();
					readSize += sizeof(PackageTarget);
				}
				else if (h.size == sizeof(PackageTargetOld))
				{
					hasTarget2Old = true;
					target2Old = f->read<PackageTargetOld>();
					readSize += sizeof(PackageTargetOld);
				}
				break;
			case 'PUID':
				loadingPackage = true;
				break;
			case 'PKAM':
				loadingPackage = true;
				break;
			case 'PKDD':
				dialogDataPresent = true;
				loadingPackage = true;
				if (h.size == sizeof(DialogueData))
				{
					dialogueData = f->read<DialogueData>();
					readSize += sizeof(DialogueData);
				}
				else if (h.size == sizeof(DialogueDataOld))
				{
					hasOldDialogueData = true;
					oldDialogueData = f->read<DialogueDataOld>();
					readSize += sizeof(DialogueDataOld);
				}
				else if (h.size == sizeof(DialogueDataOld2))
				{
					hasOldDialogueData2 = true;
					oldDialogueData2 = f->read<DialogueDataOld2>();
					readSize += sizeof(DialogueDataOld2);
				}
				else if (h.size == sizeof(DialogueDataOld3))
				{
					hasOldDialogueData3 = true;
					oldDialogueData3 = f->read<DialogueDataOld3>();
					readSize += sizeof(DialogueDataOld3);
				}
				break;
			case 'POBA':
				hasOnBegin = true;
				scr = &onBegin;
				break;
			case 'INAM':
				scr->idle = f->read<formid>();
				readSize += 4;
				break;
			ScriptLoad((&scr->script));
			case 'TNAM':
				scr->topic = f->read<formid>();
				readSize += 4;
				break;
			case 'POEA':
				hasOnEnd = true;
				scr = &onEnd;
				break;
			case 'POCA':
				hasOnChange = true;
				scr = &onChange;
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
		if (hasOldData)
		{
			WriteSubrecord('PKDT',sizeof(PackageDataOld),f);
			f->write<PackageDataOld>(oldData);
		}
		else
		{
			WriteSubrecord('PKDT',sizeof(PackageData),f);
			f->write<PackageData>(data);
		}
		if (location1Present)
		{
			WriteSubrecord('PLDT',sizeof(PackageLocation),f);
			f->write<PackageLocation>(location1);
		}
		if (location2Present)
		{
			WriteSubrecord('PLD2',sizeof(PackageLocation),f);
			f->write<PackageLocation>(location2);
		}
		WriteSubrecord('PSDT',sizeof(PackageSchedule),f);
		f->write<PackageSchedule>(schedule);
		if (target1Present)
		{
			if (hasTarget1Old)
			{
				WriteSubrecord('PTDT',sizeof(PackageTargetOld),f);
				f->write<PackageTargetOld>(target1Old);
			}
			else
			{
				WriteSubrecord('PTDT',sizeof(PackageTarget),f);
				f->write<PackageTarget>(target1);
			}
		}
		for (int conditioncount = 0;conditioncount < conditions.Count();conditioncount++)
		{
			WriteSubrecord('CTDA',sizeof(Condition),f);
			f->write<Condition>(conditions[conditioncount]);
		}
		for (int conditioncount = 0;conditioncount < oldConditions.Count();conditioncount++)
		{
			WriteSubrecord('CTDA',sizeof(ConditionOld),f);
			f->write<ConditionOld>(oldConditions[conditioncount]);
		}
		for (int conditioncount = 0;conditioncount < oldConditions2.Count();conditioncount++)
		{
			WriteSubrecord('CTDA',sizeof(ConditionOld2),f);
			f->write<ConditionOld2>(oldConditions2[conditioncount]);
		}
		IdleCollectionSave()
		if (combatStyle)
		{
			WriteSubrecord('CNAM',4,f);
			f->write<formid>(combatStyle);
		}
		if (dialogDataPresent)
		{
			if (hasOldDialogueData)
			{
				WriteSubrecord('PKDD',sizeof(DialogueDataOld),f);
				f->write<DialogueDataOld>(oldDialogueData);
			}
			else if (hasOldDialogueData2)
			{
				WriteSubrecord('PKDD',sizeof(DialogueDataOld2),f);
				f->write<DialogueDataOld2>(oldDialogueData2);
			}
			else if (hasOldDialogueData3)
			{
				WriteSubrecord('PKDD',sizeof(DialogueDataOld3),f);
				f->write<DialogueDataOld3>(oldDialogueData3);
			}
			else
			{
				WriteSubrecord('PKDD',sizeof(DialogueData),f);
				f->write<DialogueData>(dialogueData);
			}
		}
		if (hasFollowRadius)
		{
			WriteSubrecord('PKFD',4,f);
			f->write<float>(followRadius);
		}
		if (hasUseWeaponData)
		{
			WriteSubrecord('PKW3',sizeof(UseWeaponData),f);
			f->write<UseWeaponData>(useWeaponData);
		}
		switch (data.type)
		{
		case follow:
			if (location3Present)
			{
				WriteSubrecord('PLD2',sizeof(PackageLocation),f);
				f->write<PackageLocation>(location3);
			}
			break;
		case escort:
			WriteSubrecord('PKE2',4,f);
			f->write<ulong>(escortDistance);
			if (location3Present)
			{
				WriteSubrecord('PLD2',sizeof(PackageLocation),f);
				f->write<PackageLocation>(location3);
			}
			break;
		case eat:
			if (hasEatMarker)
			{
				WriteSubrecord('PKED',0,f);
			}
			if (location3Present)
			{
				WriteSubrecord('PLD2',sizeof(PackageLocation),f);
				f->write<PackageLocation>(location3);
			}
			break;
		case useItemAt:
			WriteSubrecord('PUID',0,f);
			if (location3Present)
			{
				WriteSubrecord('PLD2',sizeof(PackageLocation),f);
				f->write<PackageLocation>(location3);
			}
			break;
		case ambush:
			WriteSubrecord('PKAM',0,f);
			if (location3Present)
			{
				WriteSubrecord('PLD2',sizeof(PackageLocation),f);
				f->write<PackageLocation>(location3);
			}
			break;
		case patrol:
			if (hasPatrolFlags)
			{
				if (hasPatrolFlagsOld)
				{
					WriteSubrecord('PKPT',1,f);
					f->write<ubyte>(patrolFlagsOld);
				}
				else
				{
					WriteSubrecord('PKPT',2,f);
					f->write<ushort>(patrolFlags);
				}
			}
			break;
		case dialogue:
			if (location3Present)
			{
				WriteSubrecord('PLD2',sizeof(PackageLocation),f);
				f->write<PackageLocation>(location3);
			}
			break;
		case useWeapon:
			if (target2Present)
			{
				if (hasTarget2Old)
				{
					WriteSubrecord('PTD2',sizeof(PackageTargetOld),f);
					f->write<PackageTargetOld>(target2Old);
				}
				else
				{
					WriteSubrecord('PTD2',sizeof(PackageTarget),f);
					f->write<PackageTarget>(target2);
				}
			}
			if (location3Present)
			{
				WriteSubrecord('PLD2',sizeof(PackageLocation),f);
				f->write<PackageLocation>(location3);
			}
		}
		if (hasOnBegin)
		{
			WriteSubrecord('POBA',0,f);
			WriteSubrecord('INAM',4,f);
			f->write<formid>(onBegin.idle);
			ScriptSave((&onBegin.script),this);
			WriteSubrecord('TNAM',4,f);
			f->write<formid>(onBegin.topic);
		}
		if (hasOnEnd)
		{
			WriteSubrecord('POEA',0,f);
			WriteSubrecord('INAM',4,f);
			f->write<formid>(onEnd.idle);
			ScriptSave((&onEnd.script),this);
			WriteSubrecord('TNAM',4,f);
			f->write<formid>(onEnd.topic);
		}
		if (hasOnChange)
		{
			WriteSubrecord('POCA',0,f);
			WriteSubrecord('INAM',4,f);
			f->write<formid>(onChange.idle);
			ScriptSave((&onChange.script),this);
			WriteSubrecord('TNAM',4,f);
			f->write<formid>(onChange.topic);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		if (hasOldData)
		{
			size += ComputeSubrecordSize(sizeof(PackageDataOld));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(PackageData));
		}
		if (location1Present)
		{
			size += ComputeSubrecordSize(sizeof(PackageLocation));
		}
		if (location2Present)
		{
			size += ComputeSubrecordSize(sizeof(PackageLocation));
		}
		size += ComputeSubrecordSize(sizeof(PackageSchedule));
		if (target1Present)
		{
			if (hasTarget1Old)
			{
				size += ComputeSubrecordSize(sizeof(PackageTargetOld));
			}
			else
			{
				size += ComputeSubrecordSize(sizeof(PackageTarget));
			}
		}
		for (int conditioncount = 0;conditioncount < conditions.Count();conditioncount++)
		{
			size += ComputeSubrecordSize(sizeof(Condition));
		}
		for (int conditioncount = 0;conditioncount < oldConditions.Count();conditioncount++)
		{
			size += ComputeSubrecordSize(sizeof(ConditionOld));
		}
		for (int conditioncount = 0;conditioncount < oldConditions2.Count();conditioncount++)
		{
			size += ComputeSubrecordSize(sizeof(ConditionOld2));
		}
		IdleCollectionGetSaveSize();
		if (combatStyle)
		{
			size += ComputeSubrecordSize(4);
		}
		if (dialogDataPresent)
		{
			if (hasOldDialogueData)
			{
				size += ComputeSubrecordSize(sizeof(DialogueDataOld));
			}
			else if (hasOldDialogueData2)
			{
				size += ComputeSubrecordSize(sizeof(DialogueDataOld2));
			}
			else if (hasOldDialogueData3)
			{
				size += ComputeSubrecordSize(sizeof(DialogueDataOld3));
			}
			else
			{
				size += ComputeSubrecordSize(sizeof(DialogueData));
			}
		}
		if (hasFollowRadius)
		{
			size += ComputeSubrecordSize(4);
		}
		if (hasUseWeaponData)
		{
			size += ComputeSubrecordSize(sizeof(UseWeaponData));
		}
		switch (data.type)
		{
		case follow:
			if (location3Present)
			{
				size += ComputeSubrecordSize(sizeof(PackageLocation));
			}
			break;
		case escort:
			size += ComputeSubrecordSize(4);
			if (location3Present)
			{
				size += ComputeSubrecordSize(sizeof(PackageLocation));
			}
			break;
		case eat:
			if (hasEatMarker)
			{
				size += ComputeSubrecordSize(0);
			}
			if (location3Present)
			{
				size += ComputeSubrecordSize(sizeof(PackageLocation));
			}
			break;
		case useItemAt:
			size += ComputeSubrecordSize(0);
			if (location3Present)
			{
				size += ComputeSubrecordSize(sizeof(PackageLocation));
			}
			break;
		case ambush:
			size += ComputeSubrecordSize(0);
			if (location3Present)
			{
				size += ComputeSubrecordSize(sizeof(PackageLocation));
			}
			break;
		case patrol:
			if (hasPatrolFlags)
			{
				if (hasPatrolFlagsOld)
				{
					size += ComputeSubrecordSize(1);
				}
				else
				{
					size += ComputeSubrecordSize(2);
				}
			}
			break;
		case dialogue:
			if (location3Present)
			{
				size += ComputeSubrecordSize(sizeof(PackageLocation));
			}
			break;
		case useWeapon:
			if (target2Present)
			{
				if (hasTarget2Old)
				{
					size += ComputeSubrecordSize(sizeof(PackageTargetOld));
				}
				else
				{
					size += ComputeSubrecordSize(sizeof(PackageTarget));
				}
			}
			if (location3Present)
			{
				size += ComputeSubrecordSize(sizeof(PackageLocation));
			}
		}
		if (hasOnBegin)
		{
			size += ComputeSubrecordSize(0);
			size += ComputeSubrecordSize(4);
			ScriptGetSaveSize((&onBegin.script),this);
			size += ComputeSubrecordSize(4);
		}
		if (hasOnEnd)
		{
			size += ComputeSubrecordSize(0);
			size += ComputeSubrecordSize(4);
			ScriptGetSaveSize((&onEnd.script),this);
			size += ComputeSubrecordSize(4);
		}
		if (hasOnChange)
		{
			size += ComputeSubrecordSize(0);
			size += ComputeSubrecordSize(4);
			ScriptGetSaveSize((&onChange.script),this);
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
