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
struct AnimationData
{
	formid parent;
	formid previousSibling;
};
struct IdleData
{
	ubyte animationGroupSection;
	ubyte loopingMin;
	ubyte loopingMax;
	ushort replayDelay;
	ubyte flags;
};
#pragma pack(push, 1)
struct IdleDataOld
{
	ubyte animationGroupSection;
	ubyte loopingMin;
	ubyte loopingMax;
	ubyte pad;
	ushort replayDelay;
};
#pragma pack(pop)
class IdleForm : public Form, public Model
{
protected:
	SimpleDynVecClass<Condition> conditions;
	SimpleDynVecClass<ConditionOld> oldConditions;
	SimpleDynVecClass<ConditionOld2> oldConditions2;
	AnimationData animationData;
	IdleData data;
	IdleDataOld oldData;
	bool hasOldData;
public:
	IdleForm(FormHeader h,ModFile *f) : Form(h,f), hasOldData(false)
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
			ModelBRLoad(this,'MODL','MODB','MODT');
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
			case 'ANAM':
				if (h.size == sizeof(AnimationData))
				{
					animationData = f->read<AnimationData>();
					readSize += sizeof(AnimationData);
				}
				break;
			case 'DATA':
				if (h.size == sizeof(IdleData))
				{
					data = f->read<IdleData>();
					readSize += sizeof(IdleData);
				}
				else if (h.size == sizeof(IdleDataOld))
				{
					hasOldData = true;
					oldData = f->read<IdleDataOld>();
					readSize += sizeof(IdleDataOld);
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
		FormSave();
		ModelBRSave(this,'MODL','MODB','MODT');
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
		WriteSubrecord('ANAM',sizeof(AnimationData),f);
		f->write<AnimationData>(animationData);
		if (hasOldData)
		{
			WriteSubrecord('DATA',sizeof(IdleDataOld),f);
			f->write<IdleDataOld>(oldData);
		}
		else
		{
			WriteSubrecord('DATA',sizeof(IdleData),f);
			f->write<IdleData>(data);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		ModelBRGetSaveSize(this);
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
		size += ComputeSubrecordSize(sizeof(AnimationData));
		if (hasOldData)
		{
			size += ComputeSubrecordSize(sizeof(IdleDataOld));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(IdleData));
		}
		return size;
	}
};
