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
struct ProjectileData
{
	ulong flags;
	float gravity;
	float speed;
	float range;
	formid light;
	formid muzzleFlashLight;
	float tracerChance;
	float explosionProximity;
	float explosionTimer;
	formid explosion;
	formid sound;
	float muzzleFlashDuration;
	float fadeDuration;
	float impactForce;
	formid countdownSound;
	formid disableSound;
	formid defaultWeaponSource;
	NiPoint3 rotation;
	float bouncyMultiplier;
};
struct ProjectileDataOld
{
	ulong flags;
	float gravity;
	float speed;
	float range;
	formid light;
	formid muzzleFlashLight;
	float tracerChance;
	float explosionProximity;
	float explosionTimer;
	formid explosion;
	formid sound;
	float muzzleFlashDuration;
	float fadeDuration;
	float impactForce;
	formid countdownSound;
	formid disableSound;
	formid defaultWeaponSource;
};
class ProjectileForm : public BoundObjectForm, public FullName, public Model, public DestructibleObject
{
protected:
	ProjectileData data;
	ProjectileDataOld dataOld;
	bool old;
	Model muzzleFlash;
	ulong soundLevel;
public:
	ProjectileForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), old(false)
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
			ModelBRLoad(this,'MODL','MODB','MODT');
			DestructibleObjectLoad();
			case 'DATA':
				if (h.size == sizeof(ProjectileData))
				{
					data = f->read<ProjectileData>();
					readSize += sizeof(ProjectileData);
				}
				else
				{
					dataOld = f->read<ProjectileDataOld>();
					readSize += sizeof(ProjectileDataOld);
					old = true;
				}
				break;
			ModelBRLoad((&muzzleFlash),'NAM1','NAMA','NAM2');
			case 'VNAM':
				soundLevel = f->read<ulong>();
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
		DestructibleObjectSave();
		if (old)
		{
			WriteSubrecord('DATA',sizeof(ProjectileDataOld),f);
			f->write<ProjectileDataOld>(dataOld);
		}
		else
		{
			WriteSubrecord('DATA',sizeof(ProjectileData),f);
			f->write<ProjectileData>(data);
		}
		ModelBRSave((&muzzleFlash),'NAM1','NAMA','NAM2');
		WriteSubrecord('VNAM',4,f);
		f->write<ulong>(soundLevel);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelBRGetSaveSize(this);
		DestructibleObjectGetSaveSize();
		if (old)
		{
			size += ComputeSubrecordSize(sizeof(ProjectileDataOld));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(ProjectileData));
		}
		ModelBRGetSaveSize((&muzzleFlash));
		size += ComputeSubrecordSize(4);
		return size;
	}
};
