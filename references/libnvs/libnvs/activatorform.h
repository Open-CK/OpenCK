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
class ActivatorForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Scriptable, public DestructibleObject
{
protected:
	formid loopSound;
	formid activationSound;
	formid waterType;
	formid radioStation;
	formid radioTemplate;
	char *activationPrompt;
public:
	ActivatorForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), loopSound(0), activationSound(0), waterType(0), radioStation(0), radioTemplate(0), activationPrompt(0)
	{
	}
	~ActivatorForm()
	{
		if (activationPrompt)
		{
			delete[] activationPrompt;
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
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
			ScriptableLoad();
			DestructibleObjectLoad();
			case 'SNAM':
				loopSound = f->read<formid>();
				readSize += 4;
				break;
			case 'VNAM':
				activationSound = f->read<formid>();
				readSize += 4;
				break;
			case 'INAM':
				radioTemplate = f->read<formid>();
				readSize += 4;
				break;
			case 'WNAM':
				waterType = f->read<formid>();
				readSize += 4;
				break;
			case 'RNAM':
				radioStation = f->read<formid>();
				readSize += 4;
				break;
			case 'XATO':
				activationPrompt = f->readzstring(h.size);
				readSize += h.size;
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
		if (activationSound)
		{
			WriteSubrecord('VNAM',4,f);
			f->write<formid>(activationSound);
		}
		if (radioTemplate)
		{
			WriteSubrecord('INAM',4,f);
			f->write<formid>(radioTemplate);
		}
		if (waterType)
		{
			WriteSubrecord('WNAM',4,f);
			f->write<formid>(waterType);
		}
		if (radioStation)
		{
			WriteSubrecord('RNAM',4,f);
			f->write<formid>(radioStation);
		}
		WriteZStringSubrecord('XATO',activationPrompt,f);
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
		if (activationSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (radioTemplate)
		{
			size += ComputeSubrecordSize(4);
		}
		if (waterType)
		{
			size += ComputeSubrecordSize(4);
		}
		if (radioStation)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ZStringSubrecordSize(activationPrompt);
		return size;
	}
};
