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
#pragma pack(push,1)
struct WeaponData
{
	long value;
	long health;
	float weight;
	ushort baseDamage;
	ubyte clipSize;
};
#pragma pack(pop)
struct WeaponStatsData
{
	 ubyte weaponAnimType;
	 float animMult;
	 float reach;
	 ubyte flags1;
	 ubyte handGrip;
	 ubyte ammoUse;
	 ubyte reloadAnim;
	 float minSpread;
	 float spread;
	 float unk1;
	 float sightFOV;
	 ubyte conditionLevel;
	 formid projectile;
	 ubyte baseVATSChance;
	 ubyte attackAnim;
	 ubyte numProjectiles;
	 ubyte embedWeaponAV;
	 float minRange;
	 float maxRange;
	 ulong onHit;
	 ulong flags2;
	 float animAttackMult;
	 float fireRate;
	 float actionPointsOverride;
	 float rumbleLeftMotor;
	 float rumbleRightMotor;
	 float rumbleDuration;
	 float damageToWeaponMult;
	 float attackShotsPerSec;
	 float reloadTime;
	 float jamTime;
	 float aimArc;
	 long skill;
	 ulong rumblePattern;
	 float rumbleWaveLength;
	 float limbDamageMult;
	 long resistType;
	 ulong sightUsage;
	 float semiAutoFireDelayMin;
	 float semiAutoFireDelayMax;
	 float semiAutoFireDelay;
	 ulong effectMod1;
	 ulong effectMod2;
	 ulong effectMod3;
	 float valueAMod1;
	 float valueAMod2;
	 float valueAMod3;
	 ubyte powerAttackAnimOverride;
	 ulong strReq;
	 ubyte unk2;
	 ubyte reloadAnimMod;
	 float regenRate;
	 float killImpulse;
	 float valueBMod1;
	 float valueBMod2;
	 float valueBMod3;
	 float impulseDist;
	 ulong skillReq;
};
struct WeaponStatsData2
{
	 ubyte weaponAnimType;
	 float animMult;
	 float reach;
	 ubyte flags1;
	 ubyte handGrip;
	 ubyte ammoUse;
	 ubyte reloadAnim;
	 float minSpread;
	 float spread;
	 float unk1;
	 float sightFOV;
	 ubyte conditionLevel;
	 formid projectile;
	 ubyte baseVATSChance;
	 ubyte attackAnim;
	 ubyte numProjectiles;
	 ubyte embedWeaponAV;
	 float minRange;
	 float maxRange;
	 ulong onHit;
	 ulong flags2;
	 float animAttackMult;
	 float fireRate;
	 float actionPointsOverride;
	 float rumbleLeftMotor;
	 float rumbleRightMotor;
	 float rumbleDuration;
	 float damageToWeaponMult;
	 float attackShotsPerSec;
	 float reloadTime;
	 float jamTime;
	 float aimArc;
	 long skill;
	 ulong rumblePattern;
	 float rumbleWaveLength;
	 float limbDamageMult;
	 long resistType;
	 ulong sightUsage;
	 float semiAutoFireDelayMin;
	 float semiAutoFireDelayMax;
	 float semiAutoFireDelay;
	 ulong effectMod1;
	 ulong effectMod2;
	 ulong effectMod3;
	 float valueAMod1;
	 float valueAMod2;
	 float valueAMod3;
	 ubyte powerAttackAnimOverride;
	 ulong strReq;
	 ubyte unk2;
	 ubyte reloadAnimMod;
	 float regenRate;
	 float killImpulse;
	 float valueBMod1;
	 float valueBMod2;
	 float valueBMod3;
	 float impulseDist;
};
struct WeaponStatsData3
{
	 ubyte weaponAnimType;
	 float animMult;
	 float reach;
	 ubyte flags1;
	 ubyte handGrip;
	 ubyte ammoUse;
	 ubyte reloadAnim;
	 float minSpread;
	 float spread;
	 float unk1;
	 float sightFOV;
	 ubyte conditionLevel;
	 formid projectile;
	 ubyte baseVATSChance;
	 ubyte attackAnim;
	 ubyte numProjectiles;
	 ubyte embedWeaponAV;
	 float minRange;
	 float maxRange;
	 ulong onHit;
	 ulong flags2;
	 float animAttackMult;
	 float fireRate;
	 float actionPointsOverride;
	 float rumbleLeftMotor;
	 float rumbleRightMotor;
	 float rumbleDuration;
	 float damageToWeaponMult;
	 float attackShotsPerSec;
	 float reloadTime;
	 float jamTime;
	 float aimArc;
	 long skill;
	 ulong rumblePattern;
	 float rumbleWaveLength;
	 float limbDamageMult;
	 long resistType;
	 ulong sightUsage;
	 float semiAutoFireDelayMin;
	 float semiAutoFireDelayMax;
	 float semiAutoFireDelay;
	 ulong effectMod1;
	 ulong effectMod2;
	 ulong effectMod3;
	 float valueAMod1;
	 float valueAMod2;
	 float valueAMod3;
	 ubyte powerAttackAnimOverride;
	 ulong strReq;
	 ubyte unk2;
	 ubyte reloadAnimMod;
	 float regenRate;
	 float killImpulse;
	 float valueBMod1;
	 float valueBMod2;
	 float valueBMod3;
};
struct WeaponStatsData4
{
	 ubyte weaponAnimType;
	 float animMult;
	 float reach;
	 ubyte flags1;
	 ubyte handGrip;
	 ubyte ammoUse;
	 ubyte reloadAnim;
	 float minSpread;
	 float spread;
	 float unk1;
	 float sightFOV;
	 ubyte conditionLevel;
	 formid projectile;
	 ubyte baseVATSChance;
	 ubyte attackAnim;
	 ubyte numProjectiles;
	 ubyte embedWeaponAV;
	 float minRange;
	 float maxRange;
	 ulong onHit;
	 ulong flags2;
	 float animAttackMult;
	 float fireRate;
	 float actionPointsOverride;
	 float rumbleLeftMotor;
	 float rumbleRightMotor;
	 float rumbleDuration;
	 float damageToWeaponMult;
	 float attackShotsPerSec;
	 float reloadTime;
	 float jamTime;
	 float aimArc;
	 long skill;
	 ulong rumblePattern;
	 float rumbleWaveLength;
	 float limbDamageMult;
	 long resistType;
	 ulong sightUsage;
	 float semiAutoFireDelayMin;
	 float semiAutoFireDelayMax;
	 float semiAutoFireDelay;
	 ulong effectMod1;
	 ulong effectMod2;
	 ulong effectMod3;
	 float valueAMod1;
	 float valueAMod2;
	 float valueAMod3;
	 ubyte powerAttackAnimOverride;
	 ulong strReq;
	 ubyte unk2;
	 ubyte reloadAnimMod;
	 float regenRate;
};
struct WeaponStatsData5
{
	 ubyte weaponAnimType;
	 float animMult;
	 float reach;
	 ubyte flags1;
	 ubyte handGrip;
	 ubyte ammoUse;
	 ubyte reloadAnim;
	 float minSpread;
	 float spread;
	 float unk1;
	 float sightFOV;
	 ubyte conditionLevel;
	 formid projectile;
	 ubyte baseVATSChance;
	 ubyte attackAnim;
	 ubyte numProjectiles;
	 ubyte embedWeaponAV;
	 float minRange;
	 float maxRange;
	 ulong onHit;
	 ulong flags2;
	 float animAttackMult;
	 float fireRate;
	 float actionPointsOverride;
	 float rumbleLeftMotor;
	 float rumbleRightMotor;
	 float rumbleDuration;
	 float damageToWeaponMult;
	 float attackShotsPerSec;
	 float reloadTime;
	 float jamTime;
	 float aimArc;
	 long skill;
	 ulong rumblePattern;
	 float rumbleWaveLength;
	 float limbDamageMult;
	 long resistType;
	 ulong sightUsage;
	 float semiAutoFireDelayMin;
	 float semiAutoFireDelayMax;
	 float semiAutoFireDelay;
	 ulong effectMod1;
	 ulong effectMod2;
	 ulong effectMod3;
	 float valueAMod1;
	 float valueAMod2;
	 float valueAMod3;
	 ubyte powerAttackAnimOverride;
	 ulong strReq;
};
struct WeaponStatsData6
{
	 ubyte weaponAnimType;
	 float animMult;
	 float reach;
	 ubyte flags1;
	 ubyte handGrip;
	 ubyte ammoUse;
	 ubyte reloadAnim;
	 float minSpread;
	 float spread;
	 float unk1;
	 float sightFOV;
	 ubyte conditionLevel;
	 formid projectile;
	 ubyte baseVATSChance;
	 ubyte attackAnim;
	 ubyte numProjectiles;
	 ubyte embedWeaponAV;
	 float minRange;
	 float maxRange;
	 ulong onHit;
	 ulong flags2;
	 float animAttackMult;
	 float fireRate;
	 float actionPointsOverride;
	 float rumbleLeftMotor;
	 float rumbleRightMotor;
	 float rumbleDuration;
	 float damageToWeaponMult;
	 float attackShotsPerSec;
	 float reloadTime;
	 float jamTime;
	 float aimArc;
	 long skill;
	 ulong rumblePattern;
	 float rumbleWaveLength;
	 float limbDamageMult;
	 long resistType;
	 ulong sightUsage;
	 float semiAutoFireDelayMin;
	 float semiAutoFireDelayMax;
	 float semiAutoFireDelay;
	 ulong effectMod1;
	 ulong effectMod2;
	 ulong effectMod3;
	 float valueAMod1;
	 float valueAMod2;
	 float valueAMod3;
};
struct WeaponStatsData7
{
	 ubyte weaponAnimType;
	 float animMult;
	 float reach;
	 ubyte flags1;
	 ubyte handGrip;
	 ubyte ammoUse;
	 ubyte reloadAnim;
	 float minSpread;
	 float spread;
	 ulong unk;
	 float sightFOV;
	 ubyte conditionLevel;
	 formid projectile;
	 ubyte baseVATSChance;
	 ubyte attackAnim;
	 ubyte numProjectiles;
	 ubyte embedWeaponActorValue;
	 float minRange;
	 float maxRange;
	 ulong onHit;
	 ulong flags2;
	 float animAttackMult;
	 float fireRate;
	 float actionPoints;
	 float rumbleLeftMotor;
	 float rumbleRightMotor;
	 float rumbleDuration;
	 float damageToWeaponMult;
	 float animShotsPerSec;
	 float reloadTime;
	 float jamTime;
	 float aimArc;
	 long weaponSkill;
	 ulong rumblePattern;
	 float rumbleWaveLength;
	 float limbDamageMult;
	 long resistType;
	 ulong sightUsage;
	 float semiAutoFireDelayMin;
	 float semiAutoFireDelayMax;
};
struct WeaponStatsData8
{
	 ubyte weaponAnimType;
	 float animMult;
	 float reach;
	 ubyte flags1;
	 ubyte handGrip;
	 ubyte ammoUse;
	 ubyte reloadAnim;
	 float minSpread;
	 float spread;
	 ulong unk;
	 float sightFOV;
	 ubyte conditionLevel;
	 formid projectile;
	 ubyte baseVATSChance;
	 ubyte attackAnim;
	 ubyte numProjectiles;
	 ubyte embedWeaponActorValue;
	 float minRange;
	 float maxRange;
	 ulong onHit;
	 ulong flags2;
	 float animAttackMult;
	 float fireRate;
	 float actionPoints;
	 float rumbleLeftMotor;
	 float rumbleRightMotor;
	 float rumbleDuration;
	 float damageToWeaponMult;
	 float animShotsPerSec;
	 float reloadTime;
	 float jamTime;
	 float aimArc;
	 long weaponSkill;
	 ulong rumblePattern;
	 float rumbleWaveLength;
	 float limbDamageMult;
	 long resistType;
};
struct WeaponStatsData9
{
	 ubyte weaponAnimType;
	 float animMult;
	 float reach;
	 ubyte flags1;
	 ubyte handGrip;
	 ubyte ammoUse;
	 ubyte reloadAnim;
	 float minSpread;
	 float spread;
	 ulong unk;
	 float sightFOV;
	 ubyte conditionLevel;
	 formid projectile;
	 ubyte baseVATSChance;
	 ubyte attackAnim;
	 ubyte numProjectiles;
	 ubyte embedWeaponActorValue;
	 float minRange;
	 float maxRange;
	 ulong onHit;
	 ulong flags2;
	 float animAttackMult;
	 float fireRate;
	 float actionPoints;
	 float rumbleLeftMotor;
	 float rumbleRightMotor;
	 float rumbleDuration;
	 float damageToWeaponMult;
	 float animShotsPerSec;
	 float reloadTime;
	 float jamTime;
	 float aimArc;
	 long weaponSkill;
	 ulong rumblePattern;
	 float rumbleWaveLength;
	 float limbDamageMult;
};
struct WeaponCritData
{
	ushort damage;
	float percent;
	ubyte onDeath;
	formid effect;
};
struct WeaponVatsData
{
	formid effect;
	float skill;
	float damageMult;
	float AP;
	ubyte silent;
	ubyte modRequired;
};
struct WeaponVatsData2
{
	formid effect;
	float skill;
	float damageMult;
	float AP;
};
class WeaponForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public ModelFaceGenFlags, public Texture, public Scriptable, public Enchantable, public Ammo, public DestructibleObject, public RepairItem, public EquipType, public MessageTexture, public BipedModelList, public PickupPutdownSounds
{
protected:
	Model shellCasingModel;
	Model scopeTargetModel;
	formid scopeEffect;
	Model worldModel;
	Model textureMod1;
	Model textureMod2;
	Model textureMod12;
	Model textureMod3;
	Model textureMod13;
	Model textureMod23;
	Model textureMod123;
	char *embeddedWeaponNode;
	char *vatsAttackName;
	formid impactDataSet;
	formid firstPersonModel;
	formid mod1FirstPerson;
	formid mod2FirstPerson;
	formid mod12FirstPerson;
	formid mod3FirstPerson;
	formid mod23FirstPerson;
	formid mod13FirstPerson;
	formid mod123FirstPerson;
	formid itemMod1;
	formid itemMod2;
	formid itemMod3;
	formid soundAttack;
	formid soundAttackDist;
	formid soundAttack2D;
	formid soundAttackLooping;
	formid soundAttackFail;
	formid soundBlock;
	formid soundIdle;
	formid soundEquip;
	formid soundUnequip;
	formid modAttackSound1;
	formid modAttackSound2;
	formid modAttackSound2D;
	WeaponData data;
	WeaponStatsData statsData;
	WeaponStatsData2 statsData2;
	WeaponStatsData3 statsData3;
	WeaponStatsData4 statsData4;
	WeaponStatsData5 statsData5;
	WeaponStatsData6 statsData6;
	WeaponStatsData7 statsData7;
	WeaponStatsData8 statsData8;
	WeaponStatsData9 statsData9;
	WeaponCritData critData;
	WeaponVatsData vatsData;
	WeaponVatsData2 vatsData2;
	bool hasVatsData;
	bool hasVatsData2;
	ulong soundLevel;
	int stats;
public:
	WeaponForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), scopeEffect(0), embeddedWeaponNode(0), vatsAttackName(0), impactDataSet(0), firstPersonModel(0), mod1FirstPerson(0), mod2FirstPerson(0), mod12FirstPerson(0), mod3FirstPerson(0), mod23FirstPerson(0), mod13FirstPerson(0), mod123FirstPerson(0), itemMod1(0), itemMod2(0), itemMod3(0), soundAttack(0), soundAttackDist(0), soundAttack2D(0), soundAttackLooping(0), soundAttackFail(0), soundBlock(0), soundIdle(0), soundEquip(0), soundUnequip(0), modAttackSound1(0), modAttackSound2(0), modAttackSound2D(0), hasVatsData(false), hasVatsData2(false)
	{
	}
	virtual ~WeaponForm()
	{
		if (embeddedWeaponNode)
		{
			delete[] embeddedWeaponNode;
		}
		if (vatsAttackName)
		{
			delete[] vatsAttackName;
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
			ModelFaceGenFlagsLoad(this,'MODD');
			TextureLoad(this,'ICON');
			MessageTextureLoad(this,'MICO');
			ScriptableLoad();
			EnchantableLoad();
			AmmoLoad();
			DestructibleObjectLoad();
			RepairItemLoad();
			EquipTypeLoad();
			BipedModelListLoad();
			PickupPutdownSoundsLoad();
			ModelBRLoad((&shellCasingModel),'MOD2','MO2B','MO2T');
			ModelBRLoad((&scopeTargetModel),'MOD3','MO3B','MO3T');
			case 'EFSD':
				scopeEffect = f->read<formid>();
				readSize += 4;
				break;
			ModelBRLoad((&worldModel),'MOD4','MO4B','MO4T');
			ModelBRLoad((&textureMod1),'MWD1','MWB1','MWT1');
			ModelBRLoad((&textureMod2),'MWD2','MWB2','MWT2');
			ModelBRLoad((&textureMod12),'MWD4','MWB4','MWT4');
			ModelBRLoad((&textureMod3),'MWD3','MWB3','MWT3');
			ModelBRLoad((&textureMod13),'MWD5','MWB5','MWT5');
			ModelBRLoad((&textureMod23),'MWD6','MWB6','MWT6');
			ModelBRLoad((&textureMod123),'MWD7','MWB7','MWT7');
			case 'NNAM':
				embeddedWeaponNode = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'VANM':
				vatsAttackName = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'INAM':
				impactDataSet = f->read<formid>();
				readSize += 4;
				break;
			case 'WNAM':
				firstPersonModel = f->read<formid>();
				readSize += 4;
				break;
			case 'WNM1':
				mod1FirstPerson = f->read<formid>();
				readSize += 4;
				break;
			case 'WNM2':
				mod2FirstPerson = f->read<formid>();
				readSize += 4;
				break;
			case 'WNM4':
				mod12FirstPerson = f->read<formid>();
				readSize += 4;
				break;
			case 'WNM3':
				mod3FirstPerson = f->read<formid>();
				readSize += 4;
				break;
			case 'WNM6':
				mod23FirstPerson = f->read<formid>();
				readSize += 4;
				break;
			case 'WNM5':
				mod13FirstPerson = f->read<formid>();
				readSize += 4;
				break;
			case 'WNM7':
				mod123FirstPerson = f->read<formid>();
				readSize += 4;
				break;
			case 'WMI1':
				itemMod1 = f->read<formid>();
				readSize += 4;
				break;
			case 'WMI2':
				itemMod2 = f->read<formid>();
				readSize += 4;
				break;
			case 'WMI3':
				itemMod3 = f->read<formid>();
				readSize += 4;
				break;
			case 'SNAM':
				if (!soundAttack)
				{
					soundAttack = f->read<formid>();
				}
				else
				{
					soundAttackDist = f->read<formid>();
				}
				readSize += 4;
				break;
			case 'XNAM':
				soundAttack2D = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM7':
				soundAttackLooping = f->read<formid>();
				readSize += 4;
				break;
			case 'TNAM':
				soundAttackFail = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM6':
				soundBlock = f->read<formid>();
				readSize += 4;
				break;
			case 'UNAM':
				soundIdle = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM9':
				soundEquip = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM8':
				soundUnequip = f->read<formid>();
				readSize += 4;
				break;
			case 'WMS1':
				if (!modAttackSound1)
				{
					modAttackSound1 = f->read<formid>();
				}
				else
				{
					modAttackSound2 = f->read<formid>();
				}
				readSize += 4;
				break;
			case 'WMS2':
				modAttackSound2D = f->read<formid>();
				readSize += 4;
				break;
			case 'DATA':
				data = f->read<WeaponData>();
				readSize += sizeof(WeaponData);
				break;
			case 'DNAM':
				if (h.size == sizeof(WeaponStatsData))
				{
					statsData = f->read<WeaponStatsData>();
					readSize += sizeof(WeaponStatsData);
					stats = 1;
				}
				else if (h.size == sizeof(WeaponStatsData2))
				{
					statsData2 = f->read<WeaponStatsData2>();
					memcpy(&statsData,&statsData2,sizeof(statsData2));
					readSize += sizeof(WeaponStatsData2);
					stats = 2;
				}
				else if (h.size == sizeof(WeaponStatsData3))
				{
					statsData3 = f->read<WeaponStatsData3>();
					memcpy(&statsData,&statsData3,sizeof(statsData3));
					readSize += sizeof(WeaponStatsData3);
					stats = 3;
				}
				else if (h.size == sizeof(WeaponStatsData4))
				{
					statsData4 = f->read<WeaponStatsData4>();
					memcpy(&statsData,&statsData4,sizeof(statsData4));
					readSize += sizeof(WeaponStatsData4);
					stats = 4;
				}
				else if (h.size == sizeof(WeaponStatsData5))
				{
					statsData5 = f->read<WeaponStatsData5>();
					memcpy(&statsData,&statsData5,sizeof(statsData5));
					readSize += sizeof(WeaponStatsData5);
					stats = 5;
				}
				else if (h.size == sizeof(WeaponStatsData6))
				{
					statsData6 = f->read<WeaponStatsData6>();
					memcpy(&statsData,&statsData6,sizeof(statsData6));
					readSize += sizeof(WeaponStatsData6);
					stats = 6;
				}
				else if (h.size == sizeof(WeaponStatsData7))
				{
					statsData7 = f->read<WeaponStatsData7>();
					memcpy(&statsData,&statsData7,sizeof(statsData7));
					readSize += sizeof(WeaponStatsData7);
					stats = 7;
				}
				else if (h.size == sizeof(WeaponStatsData8))
				{
					statsData8 = f->read<WeaponStatsData8>();
					memcpy(&statsData,&statsData8,sizeof(statsData8));
					readSize += sizeof(WeaponStatsData8);
					stats = 8;
				}
				else if (h.size == sizeof(WeaponStatsData9))
				{
					statsData9 = f->read<WeaponStatsData9>();
					memcpy(&statsData,&statsData9,sizeof(statsData9));
					readSize += sizeof(WeaponStatsData9);
					stats = 9;
				}
				break;
			case 'CRDT':
				critData = f->read<WeaponCritData>();
				readSize += sizeof(WeaponCritData);
				break;
			case 'VATS':
				if (h.size == sizeof(WeaponVatsData))
				{
					vatsData = f->read<WeaponVatsData>();
					readSize += sizeof(WeaponVatsData);
				}
				else
				{
					vatsData2 = f->read<WeaponVatsData2>();
					readSize += sizeof(WeaponVatsData2);
					hasVatsData2 = true;
				}
				hasVatsData = true;
				break;
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
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		ModelFaceGenFlagsSave(this,'MODD');
		TextureSave(this,'ICON');
		MessageTextureSave(this,'MICO');
		ScriptableSave();
		EnchantableSave();
		AmmoSave();
		DestructibleObjectSave();
		RepairItemSave();
		EquipTypeSave();
		BipedModelListSave();
		PickupPutdownSoundsSave();
		ModelBRSave((&shellCasingModel),'MOD2','MO2B','MO2T');
		if (statsData.flags1 & 4)
		{
			ModelBRSave((&scopeTargetModel),'MOD3','MO3B','MO3T');
			if (scopeEffect)
			{
				WriteSubrecord('EFSD',4,f);
				f->write<formid>(scopeEffect);
			}
		}
		ModelBRSave((&worldModel),'MOD4','MO4B','MO4T');
		ModelBRSave((&textureMod1),'MWD1','MWB1','MWT1');
		ModelBRSave((&textureMod2),'MWD2','MWB2','MWT2');
		ModelBRSave((&textureMod12),'MWD4','MWB4','MWT4');
		ModelBRSave((&textureMod3),'MWD3','MWB3','MWT3');
		ModelBRSave((&textureMod13),'MWD5','MWB5','MWT5');
		ModelBRSave((&textureMod23),'MWD6','MWB6','MWT6');
		ModelBRSave((&textureMod123),'MWD7','MWB7','MWT7');
		WriteZStringSubrecord('NNAM',embeddedWeaponNode,f);
		WriteZStringSubrecord('VANM',vatsAttackName,f);
		if (impactDataSet)
		{
			WriteSubrecord('INAM',4,f);
			f->write<formid>(impactDataSet);
		}
		if (firstPersonModel)
		{
			WriteSubrecord('WNAM',4,f);
			f->write<formid>(firstPersonModel);
		}
		if (mod1FirstPerson)
		{
			WriteSubrecord('WNM1',4,f);
			f->write<formid>(mod1FirstPerson);
		}
		if (mod2FirstPerson)
		{
			WriteSubrecord('WNM2',4,f);
			f->write<formid>(mod2FirstPerson);
		}
		if (mod12FirstPerson)
		{
			WriteSubrecord('WNM4',4,f);
			f->write<formid>(mod12FirstPerson);
		}
		if (mod3FirstPerson)
		{
			WriteSubrecord('WNM3',4,f);
			f->write<formid>(mod3FirstPerson);
		}
		if (mod23FirstPerson)
		{
			WriteSubrecord('WNM6',4,f);
			f->write<formid>(mod23FirstPerson);
		}
		if (mod13FirstPerson)
		{
			WriteSubrecord('WNM5',4,f);
			f->write<formid>(mod13FirstPerson);
		}
		if (mod123FirstPerson)
		{
			WriteSubrecord('WNM7',4,f);
			f->write<formid>(mod123FirstPerson);
		}
		if (itemMod1)
		{
			WriteSubrecord('WMI1',4,f);
			f->write<formid>(itemMod1);
		}
		if (itemMod2)
		{
			WriteSubrecord('WMI2',4,f);
			f->write<formid>(itemMod2);
		}
		if (itemMod3)
		{
			WriteSubrecord('WMI3',4,f);
			f->write<formid>(itemMod3);
		}
		if (soundAttack)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(soundAttack);
		}
		if (soundAttackDist)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(soundAttackDist);
		}
		if (soundAttack2D)
		{
			WriteSubrecord('XNAM',4,f);
			f->write<formid>(soundAttack2D);
		}
		if (soundAttackLooping)
		{
			WriteSubrecord('NAM7',4,f);
			f->write<formid>(soundAttackLooping);
		}
		if (soundAttackFail)
		{
			WriteSubrecord('TNAM',4,f);
			f->write<formid>(soundAttackFail);
		}
		if (soundBlock)
		{
			WriteSubrecord('NAM6',4,f);
			f->write<formid>(soundBlock);
		}
		if (soundIdle)
		{
			WriteSubrecord('UNAM',4,f);
			f->write<formid>(soundIdle);
		}
		if (soundEquip)
		{
			WriteSubrecord('NAM9',4,f);
			f->write<formid>(soundEquip);
		}
		if (soundUnequip)
		{
			WriteSubrecord('NAM8',4,f);
			f->write<formid>(soundUnequip);
		}
		if (modAttackSound1)
		{
			WriteSubrecord('WMS1',4,f);
			f->write<formid>(modAttackSound1);
		}
		if (modAttackSound2)
		{
			WriteSubrecord('WMS1',4,f);
			f->write<formid>(modAttackSound2);
		}
		if (modAttackSound2D)
		{
			WriteSubrecord('WMS2',4,f);
			f->write<formid>(modAttackSound2D);
		}
		WriteSubrecord('DATA',sizeof(WeaponData),f);
		f->write<WeaponData>(data);
		if (stats == 1)
		{
			WriteSubrecord('DNAM',sizeof(WeaponStatsData),f);
			f->write<WeaponStatsData>(statsData);
		}
		else if (stats == 2)
		{
			WriteSubrecord('DNAM',sizeof(WeaponStatsData2),f);
			f->write<WeaponStatsData2>(statsData2);
		}
		else if (stats == 3)
		{
			WriteSubrecord('DNAM',sizeof(WeaponStatsData3),f);
			f->write<WeaponStatsData3>(statsData3);
		}
		else if (stats == 4)
		{
			WriteSubrecord('DNAM',sizeof(WeaponStatsData4),f);
			f->write<WeaponStatsData4>(statsData4);
		}
		else if (stats == 5)
		{
			WriteSubrecord('DNAM',sizeof(WeaponStatsData5),f);
			f->write<WeaponStatsData5>(statsData5);
		}
		else if (stats == 6)
		{
			WriteSubrecord('DNAM',sizeof(WeaponStatsData6),f);
			f->write<WeaponStatsData6>(statsData6);
		}
		else if (stats == 7)
		{
			WriteSubrecord('DNAM',sizeof(WeaponStatsData7),f);
			f->write<WeaponStatsData7>(statsData7);
		}
		else if (stats == 8)
		{
			WriteSubrecord('DNAM',sizeof(WeaponStatsData8),f);
			f->write<WeaponStatsData8>(statsData8);
		}
		else if (stats == 9)
		{
			WriteSubrecord('DNAM',sizeof(WeaponStatsData9),f);
			f->write<WeaponStatsData9>(statsData9);
		}
		WriteSubrecord('CRDT',sizeof(WeaponCritData),f);
		f->write<WeaponCritData>(critData);
		if (hasVatsData)
		{
			if (hasVatsData2)
			{
				WriteSubrecord('VATS',sizeof(WeaponVatsData2),f);
				f->write<WeaponVatsData2>(vatsData2);
			}
			else
			{
				WriteSubrecord('VATS',sizeof(WeaponVatsData),f);
				f->write<WeaponVatsData>(vatsData);
			}
		}
		WriteSubrecord('VNAM',4,f);
		f->write<formid>(soundLevel);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		ModelFaceGenFlagsGetSaveSize(this);
		TextureGetSaveSize(this);
		MessageTextureGetSaveSize(this);
		ScriptableGetSaveSize();
		EnchantableGetSaveSize();
		AmmoGetSaveSize();
		DestructibleObjectGetSaveSize();
		RepairItemGetSaveSize();
		EquipTypeGetSaveSize();
		BipedModelListGetSaveSize();
		PickupPutdownSoundsGetSaveSize();
		ModelBRGetSaveSize((&shellCasingModel));
		if (statsData.flags1 & 4)
		{
			ModelBRGetSaveSize((&scopeTargetModel));
			if (scopeEffect)
			{
				size += ComputeSubrecordSize(4);
			}
		}
		ModelBRGetSaveSize((&worldModel));
		ModelBRGetSaveSize((&textureMod1));
		ModelBRGetSaveSize((&textureMod2));
		ModelBRGetSaveSize((&textureMod12));
		ModelBRGetSaveSize((&textureMod3));
		ModelBRGetSaveSize((&textureMod13));
		ModelBRGetSaveSize((&textureMod23));
		ModelBRGetSaveSize((&textureMod123));
		size += ZStringSubrecordSize(embeddedWeaponNode);
		size += ZStringSubrecordSize(vatsAttackName);
		if (impactDataSet)
		{
			size += ComputeSubrecordSize(4);
		}
		if (firstPersonModel)
		{
			size += ComputeSubrecordSize(4);
		}
		if (mod1FirstPerson)
		{
			size += ComputeSubrecordSize(4);
		}
		if (mod2FirstPerson)
		{
			size += ComputeSubrecordSize(4);
		}
		if (mod12FirstPerson)
		{
			size += ComputeSubrecordSize(4);
		}
		if (mod3FirstPerson)
		{
			size += ComputeSubrecordSize(4);
		}
		if (mod23FirstPerson)
		{
			size += ComputeSubrecordSize(4);
		}
		if (mod13FirstPerson)
		{
			size += ComputeSubrecordSize(4);
		}
		if (mod123FirstPerson)
		{
			size += ComputeSubrecordSize(4);
		}
		if (itemMod1)
		{
			size += ComputeSubrecordSize(4);
		}
		if (itemMod2)
		{
			size += ComputeSubrecordSize(4);
		}
		if (itemMod3)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundAttack)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundAttackDist)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundAttack2D)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundAttackLooping)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundAttackFail)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundBlock)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundIdle)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundEquip)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundUnequip)
		{
			size += ComputeSubrecordSize(4);
		}
		if (modAttackSound1)
		{
			size += ComputeSubrecordSize(4);
		}
		if (modAttackSound2)
		{
			size += ComputeSubrecordSize(4);
		}
		if (modAttackSound2D)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(sizeof(WeaponData));
		if (stats == 1)
		{
			size += ComputeSubrecordSize(sizeof(WeaponStatsData));
		}
		else if (stats == 2)
		{
			size += ComputeSubrecordSize(sizeof(WeaponStatsData2));
		}
		else if (stats == 3)
		{
			size += ComputeSubrecordSize(sizeof(WeaponStatsData3));
		}
		else if (stats == 4)
		{
			size += ComputeSubrecordSize(sizeof(WeaponStatsData4));
		}
		else if (stats == 5)
		{
			size += ComputeSubrecordSize(sizeof(WeaponStatsData5));
		}
		else if (stats == 6)
		{
			size += ComputeSubrecordSize(sizeof(WeaponStatsData6));
		}
		else if (stats == 7)
		{
			size += ComputeSubrecordSize(sizeof(WeaponStatsData7));
		}
		else if (stats == 8)
		{
			size += ComputeSubrecordSize(sizeof(WeaponStatsData8));
		}
		else if (stats == 9)
		{
			size += ComputeSubrecordSize(sizeof(WeaponStatsData9));
		}
		size += ComputeSubrecordSize(sizeof(WeaponCritData));
		if (hasVatsData)
		{
			if (hasVatsData2)
			{
				size += ComputeSubrecordSize(sizeof(WeaponVatsData2));
			}
			else
			{
				size += ComputeSubrecordSize(sizeof(WeaponVatsData));
			}
		}
		size += ComputeSubrecordSize(4);
		return size;
	}
};
