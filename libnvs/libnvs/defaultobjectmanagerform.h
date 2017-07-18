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
class DefaultObjectManagerData
{
	formid stimpack;
	formid superStimpack;
	formid radx;
	formid radAway;
	formid medx;
	formid perkParalysis;
	formid playerFaction;
	formid mysteriousStrangerNPC;
	formid mysteriousStrangerFaction;
	formid defaultMusic;
	formid battleMusic;
	formid deathMusic;
	formid successMusic;
	formid levelUpMusic;
	formid playerVoiceMale;
	formid playerVoiceMaleChild;
	formid playerVoiceFemale;
	formid playerVoiceFemaleChild;
	formid eatPackageDefaultFood;
	formid everyActorAbility;
	formid drugWearsOffImageSpace;
	formid doctorsBag;
	formid missFortuneNPC;
	formid missFortuneFaction;
	formid meltdownExplosion;
	formid unarmedForwardPA;
	formid unarmedBackwardPA;
	formid unarmedLeftPA;
	formid unarmedRightPA;
	formid unarmedCrouchPA;
	formid unarmedCounterPA;
	formid spotterEffect;
	formid itemDetectedEffect;
	formid cateyeMobileEffect;
};
class DefaultObjectManagerForm : public Form
{
protected:
	DefaultObjectManagerData data;
public:
	DefaultObjectManagerForm(FormHeader h,ModFile *f) : Form(h,f)
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
			case 'DATA':
				data = f->read<DefaultObjectManagerData>();
				readSize += sizeof(DefaultObjectManagerData);
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
		WriteSubrecord('DATA',sizeof(DefaultObjectManagerData),f);
		f->write<DefaultObjectManagerData>(data);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		size += ComputeSubrecordSize(sizeof(DefaultObjectManagerData));
		return size;
	}
};
