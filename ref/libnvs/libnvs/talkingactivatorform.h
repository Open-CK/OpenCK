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
class TalkingActivatorForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Scriptable, public DestructibleObject
{
protected:
	formid loopSound;
	formid voiceType;
	formid radioTemplate;
public:
	TalkingActivatorForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), loopSound(0), voiceType(0), radioTemplate(0)
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
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
			ScriptableLoad();
			DestructibleObjectLoad();
			case 'SNAM':
				loopSound = f->read<formid>();
				readSize += 4;
				break;
			case 'VNAM':
				voiceType = f->read<formid>();
				readSize += 4;
				break;
			case 'INAM':
				radioTemplate = f->read<formid>();
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
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		ScriptableSave();
		DestructibleObjectSave();
		if (loopSound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(loopSound);
		}
		if (voiceType)
		{
			WriteSubrecord('VNAM',4,f);
			f->write<formid>(voiceType);
		}
		if (radioTemplate)
		{
			WriteSubrecord('INAM',4,f);
			f->write<formid>(radioTemplate);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		ScriptableGetSaveSize();
		DestructibleObjectGetSaveSize();
		if (loopSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (voiceType)
		{
			size += ComputeSubrecordSize(4);
		}
		if (radioTemplate)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
