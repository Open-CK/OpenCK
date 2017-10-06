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
struct CombatStyleStandard
{
	ubyte dodgeChance;
	ubyte lrChance;
	float dodgeLrTimerMin;
	float dodgeLrTimerMax;
	float dodgeForTimerMin;
	float dodgeForTimerMax;
	float dodgeBackTimerMin;
	float dodgeBackTimerMax;
	float dodgeIdleTimerMin;
	float dodgeIdleTimerMax;
	ubyte blkChance;
	ubyte atkChance;
	float atkBRecoil;
	float atkBUnc;
	float atkBh2h;
	ubyte pAtkChance;
	float pAtkBRecoil;
	float pAtkBUnc;
	ubyte pAtkNormal;
	ubyte pAtkFor;
	ubyte pAtkBack;
	ubyte pAtkL;
	ubyte pAtkR;
	float holdTimerMin;
	float holdTimerMax;
	ulong flags;
	ubyte acrobaticDodgeChance;
	ubyte rushingAttackChance;
	float rushingAttackDistanceMult;
};
struct CombatStyleSimple
{
	float coverSearchRadius;
	float takeCoverChance;
	float waitTimerMin;
	float waitTimerMax;
	float waitFireTimerMin;
	float waitFireTimerMax;
	float fireTimerMin;
	float fireTimerMax;
	float rangedWeaponMultMin;
	float clusterDist;
	ubyte weaponRess;
	float rangedWeaponMultMax;
	float maxTarFOV;
	float combatRad;
	float sAutFDelayMin;
	float sAutFDelayMax;
};
struct CombatStyleAdvanced
{
	float dodgeFMult;
	float dodgeFBase;
	float encSBase;
	float encSMult;
	float dodgeAtkMult;
	float dodgeNAtkMult;
	float dodgeBAtkMult;
	float dodgeBNAtkMult;
	float dodgeFAtkMult;
	float dodgeFNAtkMult;
	float blockMult;
	float blockBase;
	float blockAtkMult;
	float blockNAtkMult;
	float atkMult;
	float atkBase;
	float atkAtkMult;
	float atkNAtkMult;
	float atkBlockMult;
	float pAtkFBase;
	float pAtkFMult;
};
class CombatStyleForm : public Form
{
protected:
	CombatStyleStandard standard;
	CombatStyleSimple simple;
	CombatStyleAdvanced advanced;
public:
	CombatStyleForm(FormHeader h,ModFile *f) : Form(h,f)
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
			case 'CSTD':
				standard = f->read<CombatStyleStandard>();
				readSize += sizeof(CombatStyleStandard);
				break;
			case 'CSAD':
				advanced = f->read<CombatStyleAdvanced>();
				readSize += sizeof(CombatStyleAdvanced);
				break;
			case 'CSSD':
				simple = f->read<CombatStyleSimple>();
				readSize += sizeof(CombatStyleSimple);
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
		WriteSubrecord('CSTD',sizeof(CombatStyleStandard),f);
		f->write<CombatStyleStandard>(standard);
		WriteSubrecord('CSAD',sizeof(CombatStyleAdvanced),f);
		f->write<CombatStyleAdvanced>(advanced);
		WriteSubrecord('CSSD',sizeof(CombatStyleSimple),f);
		f->write<CombatStyleSimple>(simple);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		size += ComputeSubrecordSize(sizeof(CombatStyleStandard));
		size += ComputeSubrecordSize(sizeof(CombatStyleAdvanced));
		size += ComputeSubrecordSize(sizeof(CombatStyleSimple));
		return size;
	}
};
