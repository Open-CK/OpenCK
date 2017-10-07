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
struct ObjectEffectSubData
{
	ulong magnitude;
	ulong area;
	ulong duration;
	ulong type;
	long actorValue;
};
class ObjectEffectItemList
{
protected:
	int currentEffect;
	SimpleDynVecClass<formid> baseEffects;
	SimpleDynVecClass<ObjectEffectSubData> effectSubData;
	SimpleDynVecClass<SimpleDynVecClass<Condition>> conditions;
public:
	ObjectEffectItemList() : currentEffect(-1)
	{
	}
};

class MagicObject : public BoundObjectForm, public FullName, public ObjectEffectItemList
{
public:
	MagicObject(FormHeader h,ModFile *f) : BoundObjectForm(h,f)
	{
	}
};
#define MagicObjectLoad() \
	BoundObjectFormLoad(); \
	FullNameLoad();
#define MagicObjectSave() \
	BoundObjectFormSave(); \
	FullNameSave();
#define MagicObjectGetSaveSize() \
	BoundObjectFormGetSaveSize(); \
	FullNameGetSaveSize();

#define ObjectEffectItemListLoad() \
			case 'EFID': \
				currentEffect++; \
				baseEffects.Add(f->read<formid>()); \
				conditions.Add(SimpleDynVecClass<Condition>()); \
				readSize += 4; \
				break; \
			case 'EFIT': \
				effectSubData.Add(f->read<ObjectEffectSubData>()); \
				readSize += sizeof(ObjectEffectSubData); \
				break; \
			case 'CTDA': \
				conditions[currentEffect].Add(f->read<Condition>()); \
				readSize += sizeof(Condition); \
				break;
#define ObjectEffectItemListSave() \
		for (int effectcount = 0;effectcount < baseEffects.Count();effectcount++) \
		{ \
			WriteSubrecord('EFID',4,f); \
			f->write<formid>(baseEffects[effectcount]); \
			WriteSubrecord('EFIT',sizeof(ObjectEffectSubData),f); \
			f->write<ObjectEffectSubData>(effectSubData[effectcount]); \
			for (int conditioncount = 0;conditioncount < conditions[effectcount].Count();conditioncount++) \
			{ \
				WriteSubrecord('CTDA',sizeof(Condition),f); \
				f->write<Condition>(conditions[effectcount][conditioncount]); \
			} \
		}
#define ObjectEffectItemListGetSaveSize() \
		for (int effectcount = 0;effectcount < baseEffects.Count();effectcount++) \
		{ \
			size += ComputeSubrecordSize(4); \
			size += ComputeSubrecordSize(sizeof(ObjectEffectSubData)); \
			for (int conditioncount = 0;conditioncount < conditions[effectcount].Count();conditioncount++) \
			{ \
				size += ComputeSubrecordSize(sizeof(Condition)); \
			} \
		}
