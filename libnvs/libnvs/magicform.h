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
struct EffectSubData
{
	ulong magnitude;
	ulong area;
	ulong duration;
	ulong type;
	long actorValue;
};
class EffectItemList
{
protected:
	int currentEffect;
	SimpleDynVecClass<formid> baseEffects;
	SimpleDynVecClass<EffectSubData> effectSubData;
	SimpleDynVecClass<SimpleDynVecClass<Condition>> conditions;
public:
	EffectItemList() : currentEffect(-1)
	{
	}
};

class MagicForm : public Form, public FullName, public EffectItemList
{
public:
	MagicForm(FormHeader h,ModFile *f) : Form(h,f)
	{
	}
};
#define MagicFormLoad() \
	FormLoad(); \
	FullNameLoad();
#define MagicFormSave() \
	FormSave(); \
	FullNameSave();
#define MagicFormGetSaveSize() \
	FormGetSaveSize(); \
	FullNameGetSaveSize();

#define EffectItemListLoad() \
			case 'EFID': \
				currentEffect++; \
				baseEffects.Add(f->read<formid>()); \
				conditions.Add(SimpleDynVecClass<Condition>()); \
				readSize += 4; \
				break; \
			case 'EFIT': \
				effectSubData.Add(f->read<EffectSubData>()); \
				readSize += sizeof(EffectSubData); \
				break; \
			case 'CTDA': \
				conditions[currentEffect].Add(f->read<Condition>()); \
				readSize += sizeof(Condition); \
				break;
#define EffectItemListSave() \
		for (int effectcount = 0;effectcount < baseEffects.Count();effectcount++) \
		{ \
			WriteSubrecord('EFID',4,f); \
			f->write<formid>(baseEffects[effectcount]); \
			WriteSubrecord('EFIT',sizeof(EffectSubData),f); \
			f->write<EffectSubData>(effectSubData[effectcount]); \
			for (int conditioncount = 0;conditioncount < conditions[effectcount].Count();conditioncount++) \
			{ \
				WriteSubrecord('CTDA',sizeof(Condition),f); \
				f->write<Condition>(conditions[effectcount][conditioncount]); \
			} \
		}
#define EffectItemListGetSaveSize() \
		for (int effectcount = 0;effectcount < baseEffects.Count();effectcount++) \
		{ \
			size += ComputeSubrecordSize(4); \
			size += ComputeSubrecordSize(sizeof(EffectSubData)); \
			for (int conditioncount = 0;conditioncount < conditions[effectcount].Count();conditioncount++) \
			{ \
				size += ComputeSubrecordSize(sizeof(Condition)); \
			} \
		}
