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
enum ExtraDataProperties
{
	ExtraHavok = 0x01,
	ExtraCell3D = 0x02,
	ExtraCellWaterType = 0x03,
	ExtraRegionList = 0x04,
	ExtraSeenData = 0x05,
	ExtraCellMusicType = 0x07,
	ExtraCellClimate = 0x08,
	ExtraProcessMiddleLow = 0x09,
	ExtraCellCanopyShadowMask = 0x0A,
	ExtraDetachTime = 0x0B,
	ExtraPersistentCell = 0x0C,
	ExtraScript = 0x0D,
	ExtraAction = 0x0E,
	ExtraStartingPosition = 0x0F,
	ExtraAnim = 0x10,
	ExtraExtraBiped = 0x11,
	ExtraUsedMarkers = 0x12,
	ExtraDistantData = 0x13,
	ExtraRagdollData = 0x14,
	ExtraContainerChanges = 0x15,
	ExtraWorn = 0x16,
	ExtraWornLeft = 0x17,
	ExtraPackageStartLocation = 0x18,
	ExtraPackage = 0x19,
	ExtraTrespassPackage = 0x1A,
	ExtraRunOncePacks = 0x1B,
	ExtraReferencePointer = 0x1C,
	ExtraFollower = 0x1D,
	ExtraLevCreaModifier = 0x1E,
	ExtraGhost = 0x1F,
	ExtraOriginalReference = 0x20,
	ExtraOwnership = 0x21,
	ExtraGlobal = 0x22,
	ExtraRank = 0x23,
	ExtraCount = 0x24,
	ExtraHealth = 0x25,
	ExtraUses = 0x26,
	ExtraTimeLeft = 0x27,
	ExtraCharge = 0x28,
	ExtraLight = 0x29,
	ExtraLock = 0x2A,
	ExtraTeleport = 0x2B,
	ExtraMapMarker = 0x2C,
	ExtraLeveledCreature = 0x2E,
	ExtraLeveledItem = 0x2F,
	ExtraScale = 0x30,
	ExtraSeed = 0x31,
	ExtraMasterFileCell = 0x34,
	ExtraPlayerCrimeList = 0x35,
	ExtraEnableStateParent = 0x37,
	ExtraEnableStateChildren = 0x38,
	ExtraItemDropper = 0x39,
	ExtraDroppedItemList = 0x3A,
	ExtraRandomTeleportMarker = 0x3B,
	ExtraMerchantContainer = 0x3C,
	ExtraSavedHavokData = 0x3D,
	ExtraCannotWear = 0x3E,
	ExtraPoison = 0x3F,
	ExtraLastFinishedSequence = 0x41,
	ExtraSavedAnimation = 0x42,
	ExtraNorthRotation = 0x43,
	ExtraXTarget = 0x44,
	ExtraFriendHits = 0x45,
	ExtraHeadingTarget = 0x46,
	ExtraRefractionProperty = 0x48,
	ExtraStartingWorldOrCell = 0x49,
	ExtraHotkey = 0x4A,
	ExtraEditorRef3DData = 0x4B,
	ExtraEditorRefMovedData = 0x4C,
	ExtraInfoGeneralTopic = 0x4D,
	ExtraHasNoRumors = 0x4E,
	ExtraSound = 0x4F,
	ExtraTerminalState = 0x50,
	ExtraLinkedRef = 0x51,
	ExtraLinkedRefChildren = 0x52,
	ExtraActivateRef = 0x53,
	ExtraActivateRefChildren = 0x54,
	ExtraTalkingActor = 0x55,
	ExtraObjectHealth = 0x56,
	ExtraDecalRefs = 0x57,
	ExtraDecalTargets = 0x58,
	ExtraCellImageSpace = 0x59,
	ExtraNavMeshPortal = 0x5A,
	ExtraModelSwap = 0x5B,
	ExtraRadius = 0x5C,
	ExtraRadiation = 0x5D,
	ExtraFactionChanges = 0x5E,
	ExtraDismemberedLimbs = 0x5F,
	ExtraActorCause = 0x60,
	ExtraMultiBound = 0x61,
	ExtraMultiBoundData = 0x62,
	ExtraMultiBoundRef = 0x63,
	ExtraReflectedRefs = 0x65,
	ExtraReflectorRefs = 0x66,
	ExtraEmittanceSource = 0x67,
	ExtraRadioData = 0x68,
	ExtraCombatStyle = 0x69,
	ExtraExtraLinkColorPair = 0x6A,
	ExtraPrimitive = 0x6B,
	ExtraOpenCloseActivateRef = 0x6C,
	ExtraAmmo = 0x6E,
	ExtraPatrolRef = 0x6F,
	ExtraPackageData = 0x70,
	ExtraOcclusionPlane = 0x71,
	ExtraCollisionData = 0x72,
	ExtraSayTopicInfoOnceADay = 0x73,
	ExtraEncounterZone = 0x74,
	ExtraSayToTopicInfo = 0x75,
	ExtraOcclusionPlaneRefData = 0x76,
	ExtraPortalRefData = 0x77,
	ExtraPortal = 0x78,
	ExtraRoom = 0x79,
	ExtraHealthPerc = 0x7A,
	ExtraRoomRefData = 0x7B,
	ExtraGuardedRefData = 0x7C,
	ExtraCreatureAwakeSound = 0x7D,
	ExtraWaterZoneMap = 0x7E,
	ExtraIgnoredBySandbox = 0x80,
	ExtraCellAcousticSpace = 0x81,
	ExtraReservedMarkers = 0x82,
	ExtraWeaponIdleSound = 0x83,
	ExtraWaterLightRefs = 0x84,
	ExtraLitWaterRefs = 0x85,
	ExtraWeaponAttackSound = 0x86,
	ExtraActivateLoopSound = 0x87,
	ExtraPatrolRefInUseData = 0x88,
	ExtraAshPileRef = 0x89,
	ExtraCreatureMovementSound = 0x8A,
	ExtraFollowerSwimBreadcrumbs = 0x8B,
	ExtraCellImpactSwap = 0x8C,
	ExtraWeaponModFlags = 0x8D
};
class ExtraDataForm;
class ExtraData
{
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h) = 0;
	virtual void Save(ExtraDataForm *form, FileWrite *f) = 0;
	virtual int GetSaveSize(ExtraDataForm *form) = 0;
	virtual ~ExtraData()
	{
	}
};
class ExtraDataForm : public Form
{
protected:
	SimpleDynVecClass<ExtraData *> extraData;
public:
	ExtraDataForm(FormHeader h,ModFile *f) : Form(h,f)
	{
	}
	virtual ~ExtraDataForm()
	{
		for (int i = 0;i < extraData.Count();i++)
		{
			delete extraData[i];
		}
	}
protected:
	void LoadExtraData(FileRead *f, SubrecordHeader h);
	void SaveExtraData(FileWrite *f)
	{
		for (int i = 0;i < extraData.Count();i++)
		{
			extraData[i]->Save(this,f);
		}
	}
	int GetExtraDataSaveSize()
	{
		int size = 0;
		for (int i = 0;i < extraData.Count();i++)
		{
			size += extraData[i]->GetSaveSize(this);
		}
		return size;
	}
};
class ExtraEncounterZoneData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XEZN',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraImageSpaceData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XCIM',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraCellMusicTypeData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XCMO',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraCellAcousticSpaceData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XCAS',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraLinkedRefData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XLKR',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraLevCreaModifierData : public ExtraData
{
protected:
	long level;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		level = f->read<long>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XLCM',4,f);
		f->write<long>(level);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraRegionListData : public ExtraData
{
protected:
	ulong regionCount;
	formid *regions;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		regionCount = h.size / 4;
		regions = f->readarray<formid>(regionCount);
		form->AddReadSize(h.size);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XCLR',regionCount * 4,f);
		f->writearray<formid>(regionCount,regions);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(regionCount * 4);
	}
};
class ExtraOwnershipData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XOWN',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraEmittanceSourceData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XEMI',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraCellWaterTypeData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XCWT',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
struct TeleportData
{
	formid door;
	NiPoint3 position;
	NiPoint3 rotation;
	ulong flags;
};
class ExtraTeleportData : public ExtraData
{
protected:
	TeleportData data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<TeleportData>();
		form->AddReadSize(sizeof(TeleportData));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XTEL',sizeof(TeleportData),f);
		f->write<TeleportData>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(TeleportData));
	}
};
class ExtraPatrolRefData : public ExtraData
{
protected:
	float idleTime;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		idleTime = f->read<float>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XPRD',4,f);
		f->write<float>(idleTime);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraPatrolRefScriptMarkerData : public ExtraData, public Script
{
protected:
	formid idle;
	formid topic;
public:
	ExtraPatrolRefScriptMarkerData() : idle(0), topic(0)
	{
	}
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader hx)
	{
		ulong readSize = 0;
		for (;;)
		{
			SubrecordHeader h = form->ReadSubrecord(f);
			switch(h.type)
			{
			case 'INAM':
				idle = f->read<formid>();
				readSize += 4;
				break;
			ScriptLoad(this);
			case 'TNAM':
				topic = f->read<formid>();
				readSize += 4;
				break;
			default:
				f->unread(6);
				readSize -= 6;
				form->AddReadSize(readSize);
				return;
			}
		}
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XPPA',0,f);
		form->WriteSubrecord('INAM',4,f);
		f->write<formid>(idle);
		ScriptSave(this,form);
		form->WriteSubrecord('TNAM',4,f);
		f->write<formid>(topic);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		int size = 0;
		size += form->ComputeSubrecordSize(0);
		size += form->ComputeSubrecordSize(4);
		ScriptGetSaveSize(this,form);
		size += form->ComputeSubrecordSize(4);
		return size;
	}
};
class ExtraRadiusData : public ExtraData
{
protected:
	float radius;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		radius = f->read<float>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XRDS',4,f);
		f->write<float>(radius);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
struct Primitive
{
	NiPoint3 bound;
	float red;
	float green;
	float blue;
	float alpha;
	ulong type;
};
class ExtraPrimitiveData : public ExtraData
{
protected:
	Primitive data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<Primitive>();
		form->AddReadSize(sizeof(Primitive));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XPRM',sizeof(Primitive),f);
		f->write<Primitive>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(Primitive));
	}
};
class ExtraActivateRefData : public ExtraData
{
protected:
	ubyte flags;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		flags = f->read<ubyte>();
		form->AddReadSize(1);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XAPD',1,f);
		f->write<ubyte>(flags);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(1);
	}
};
struct ActivateRef
{
	formid reference;
	float delay;
};
class ExtraActivateRefDataData : public ExtraData
{
protected:
	ActivateRef data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<ActivateRef>();
		form->AddReadSize(sizeof(ActivateRef));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XAPR',sizeof(ActivateRef),f);
		f->write<ActivateRef>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(ActivateRef));
	}
};
class ExtraActivateRefPromptData : public ExtraData
{
protected:
	char *prompt;
public:
	ExtraActivateRefPromptData() : prompt(0)
	{
	}
	~ExtraActivateRefPromptData()
	{
		if (prompt)
		{
			delete[] prompt;
		}
	}
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		prompt = f->readzstring(h.size);
		form->AddReadSize(h.size);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteZStringSubrecord('XATO',prompt,f);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ZStringSubrecordSize(prompt);
	}
};
class ExtraMapMarkerData : public ExtraData
{
protected:
	ubyte flags;
	char *name;
	ushort type;
	formid reputation;
public:
	ExtraMapMarkerData() : name(0), reputation(0)
	{
	}
	virtual ~ExtraMapMarkerData()
	{
		if (name)
		{
			delete[] name;
		}
	}
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader hx)
	{
		ulong readSize = 0;
		for (;;)
		{
			SubrecordHeader h = form->ReadSubrecord(f);
			switch(h.type)
			{
			case 'FNAM':
				flags = f->read<ubyte>();
				form->AddReadSize(1);
				break;
			case 'FULL':
				name = f->readzstring(h.size);
				form->AddReadSize(h.size);
				break;
			case 'TNAM':
				type = f->read<ushort>();
				form->AddReadSize(2);
				break;
			case 'WMI1':
				reputation = f->read<formid>();
				form->AddReadSize(4);
				break;
			default:
				f->unread(6);
				readSize -= 6;
				form->AddReadSize(readSize);
				return;
			}
		}
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XMRK',0,f);
		form->WriteSubrecord('FNAM',1,f);
		f->write<ubyte>(flags);
		form->WriteZStringSubrecord('FULL',name,f);
		form->WriteSubrecord('TNAM',2,f);
		f->write<ushort>(type);
		if (reputation)
		{
			form->WriteSubrecord('WMI1',4,f);
			f->write<formid>(reputation);
		}
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		int size = 0;
		size += form->ComputeSubrecordSize(0);
		size += form->ComputeSubrecordSize(1);
		size += form->ZStringSubrecordSize(name);
		size += form->ComputeSubrecordSize(2);
		if (reputation)
		{
			size += form->ComputeSubrecordSize(4);
		}
		return size;
	}
};
struct NavMeshPortal
{
	formid navMesh;
	ushort unk;
};
class ExtraNavMeshPortalData : public ExtraData
{
protected:
	NavMeshPortal data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<NavMeshPortal>();
		form->AddReadSize(sizeof(NavMeshPortal));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XNDP',sizeof(NavMeshPortal),f);
		f->write<NavMeshPortal>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(NavMeshPortal));
	}
};
class ExtraMultiBoundOffsetData : public ExtraData
{
protected:
	NiPoint3 data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<NiPoint3>();
		form->AddReadSize(sizeof(NiPoint3));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XMBO',sizeof(NiPoint3),f);
		f->write<NiPoint3>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(NiPoint3));
	}
};
struct EnableStateParent
{
	formid reference;
	ubyte flags;
};
class ExtraEnableStateParentData : public ExtraData
{
protected:
	EnableStateParent data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<EnableStateParent>();
		form->AddReadSize(sizeof(EnableStateParent));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XESP',sizeof(EnableStateParent),f);
		f->write<EnableStateParent>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(EnableStateParent));
	}
};
class ExtraPortalRoomData : public ExtraData
{
protected:
	formid *formIds;
	ulong formIdCount;
public:
	ExtraPortalRoomData() : formIds(0), formIdCount(0)
	{
	}
	virtual ~ExtraPortalRoomData()
	{
		if (formIds)
		{
			delete[] formIds;
		}
	}
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formIdCount = h.size / 4;
		formIds = f->readarray<formid>(formIdCount);
		form->AddReadSize(h.size);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XPOD',formIdCount * 4,f);
		f->writearray<formid>(formIdCount,formIds);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(formIdCount * 4);
	}
};
class ExtraRagDollData : public ExtraData
{
protected:
	ubyte *ragdollData;
	ulong ragdollDataCount;
public:
	ExtraRagDollData() : ragdollData(0), ragdollDataCount(0)
	{
	}
	virtual ~ExtraRagDollData()
	{
		if (ragdollData)
		{
			delete[] ragdollData;
		}
	}
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		ragdollDataCount = h.size;
		ragdollData = f->readarray<ubyte>(ragdollDataCount);
		form->AddReadSize(h.size);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XRGD',ragdollDataCount,f);
		f->writearray<ubyte>(ragdollDataCount,ragdollData);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(ragdollDataCount);
	}
};
class ExtraActionData : public ExtraData
{
protected:
	ulong actionFlag;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		actionFlag = f->read<ulong>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XACT',4,f);
		f->write<ulong>(actionFlag);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraCountData : public ExtraData
{
protected:
	ulong count;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		count = f->read<ulong>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XCNT',4,f);
		f->write<ulong>(count);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraFactionRankData : public ExtraData
{
protected:
	long rank;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		rank = f->read<long>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XRNK',4,f);
		f->write<long>(rank);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
struct LockData
{
	ubyte level;
	formid key;
	ubyte flags;
	ulong unk;
	ulong unk2;
};
struct LockDataSmall
{
	ubyte level;
	formid key;
	ubyte flags;
};
class ExtraLockData : public ExtraData
{
protected:
	LockData data;
	LockDataSmall smallData;
	bool hasSmallData;
public:
	ExtraLockData() : hasSmallData(false)
	{
	}
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		if (h.size == sizeof(LockData))
		{
			data = f->read<LockData>();
			form->AddReadSize(sizeof(LockData));
		}
		else
		{
			hasSmallData = true;
			smallData = f->read<LockDataSmall>();
			form->AddReadSize(sizeof(LockDataSmall));
		}
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		if (hasSmallData)
		{
			form->WriteSubrecord('XLOC',sizeof(LockDataSmall),f);
			f->write<LockDataSmall>(smallData);
		}
		else
		{
			form->WriteSubrecord('XLOC',sizeof(LockData),f);
			f->write<LockData>(data);
		}
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		if (hasSmallData)
		{
			return form->ComputeSubrecordSize(sizeof(LockDataSmall));
		}
		else
		{
			return form->ComputeSubrecordSize(sizeof(LockData));
		}
	}
};
class ExtraMerchantContainerData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XMRC',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraRoomHeaderData : public ExtraData
{
protected:
	ulong count;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		count = f->read<ulong>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XRMR',4,f);
		f->write<ulong>(count);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraLinkedRoomData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XLRM',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraHealthData : public ExtraData
{
protected:
	float health;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		health = f->read<float>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XHLT',4,f);
		f->write<float>(health);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraHealthPercData : public ExtraData
{
protected:
	float health;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		health = f->read<float>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XHLP',4,f);
		f->write<float>(health);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraCETData : public ExtraData
{
protected:
	ubyte unk;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		unk = f->read<ubyte>();
		form->AddReadSize(1);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XCET',1,f);
		f->write<ubyte>(unk);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(1);
	}
};
class ExtraCMTData : public ExtraData
{
protected:
	ubyte unk;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		unk = f->read<ubyte>();
		form->AddReadSize(1);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XCMT',1,f);
		f->write<ubyte>(unk);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(1);
	}
};
class ExtraCellClimateData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XCCM',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraAmmoData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XAMT',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraAmmoCountData : public ExtraData
{
protected:
	ulong ammo;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		ammo = f->read<ulong>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XAMC',4,f);
		f->write<ulong>(ammo);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
struct Portal
{
	float width;
	float height;
	NiPoint3 position;
	float quat1;
	float quat2;
	float quat3;
	float quat4;
};
class ExtraPortalData : public ExtraData
{
protected:
	Portal data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<Portal>();
		form->AddReadSize(sizeof(Portal));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XPTL',sizeof(Portal),f);
		f->write<Portal>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(Portal));
	}
};
class ExtraRadiationData : public ExtraData
{
protected:
	float radiation;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		radiation = f->read<float>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XRAD',4,f);
		f->write<float>(radiation);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraCollisionLayerData : public ExtraData
{
protected:
	ulong collision;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		collision = f->read<ulong>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XTRI',4,f);
		f->write<ulong>(collision);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraRagDollBipedData : public ExtraData
{
protected:
	ubyte *ragdollData;
	ulong ragdollDataCount;
public:
	ExtraRagDollBipedData() : ragdollData(0), ragdollDataCount(0)
	{
	}
	virtual ~ExtraRagDollBipedData()
	{
		if (ragdollData)
		{
			delete[] ragdollData;
		}
	}
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		ragdollDataCount = h.size;
		ragdollData = f->readarray<ubyte>(ragdollDataCount);
		form->AddReadSize(h.size);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XRGB',ragdollDataCount,f);
		f->writearray<ubyte>(ragdollDataCount,ragdollData);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(ragdollDataCount);
	}
};
class ExtraXTargetData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XTRG',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
struct ReflectorData
{
	formid reference;
	ulong type;
};
class ExtraReflectorData : public ExtraData
{
protected:
	ReflectorData data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<ReflectorData>();
		form->AddReadSize(sizeof(ReflectorData));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XPWR',sizeof(ReflectorData),f);
		f->write<ReflectorData>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(ReflectorData));
	}
};
class ExtraOcclusionPlaneData : public ExtraData
{
protected:
	Portal data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<Portal>();
		form->AddReadSize(sizeof(Portal));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XOCP',sizeof(Portal),f);
		f->write<Portal>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(Portal));
	}
};
class ExtraMultiBoundPrimitiveData : public ExtraData
{
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XMBP',0,f);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(0);
	}
};
class ExtraIgnoredBySandboxData : public ExtraData
{
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XIBS',0,f);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(0);
	}
};
struct RadioData
{
	float radius;
	ulong broadcastType;
	float staticPercentage;
	formid position;
};
class ExtraRadioDataData : public ExtraData
{
protected:
	RadioData data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<RadioData>();
		form->AddReadSize(sizeof(RadioData));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XRDO',sizeof(RadioData),f);
		f->write<RadioData>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(RadioData));
	}
};
class ExtraSpeedTreeSeedData : public ExtraData
{
protected:
	ubyte seed;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		if (h.size != 1)
		{
			__debugbreak();
		}
		seed = f->read<ubyte>();
		form->AddReadSize(1);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XSED',1,f);
		f->write<ubyte>(seed);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(1);
	}
};
struct DistantData
{
	float unk1;
	float unk2;
	float unk3;
};
class ExtraDistantDataData : public ExtraData
{
protected:
	DistantData data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<DistantData>();
		form->AddReadSize(sizeof(DistantData));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XLOD',sizeof(DistantData),f);
		f->write<DistantData>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(DistantData));
	}
};
class ExtraLitWaterData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XLTW',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraOcclusionPlaneRefDataData : public ExtraData
{
protected:
	formid formId1;
	formid formId2;
	formid formId3;
	formid formId4;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId1 = f->read<formid>();
		formId2 = f->read<formid>();
		formId3 = f->read<formid>();
		formId4 = f->read<formid>();
		form->AddReadSize(16);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XORD',16,f);
		f->write<formid>(formId1);
		f->write<formid>(formId2);
		f->write<formid>(formId3);
		f->write<formid>(formId4);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(16);
	}
};
class ExtraMultiBoundDataData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XMBR',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraParentObjectData : public ExtraData
{
protected:
	formid formId;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		formId = f->read<formid>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('NAME',4,f);
		f->write<formid>(formId);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
struct LinkedReferenceColor
{
	ulong linkStartColor;
	ulong linkEndColor;
};
class ExtraLinkColorData : public ExtraData
{
protected:
	LinkedReferenceColor data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<LinkedReferenceColor>();
		form->AddReadSize(sizeof(LinkedReferenceColor));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XCLP',sizeof(LinkedReferenceColor),f);
		f->write<LinkedReferenceColor>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(LinkedReferenceColor));
	}
};
class ExtraLinkColorData2 : public ExtraData
{
protected:
	LinkedReferenceColor data;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		data = f->read<LinkedReferenceColor>();
		form->AddReadSize(sizeof(LinkedReferenceColor));
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('RCLR',sizeof(LinkedReferenceColor),f);
		f->write<LinkedReferenceColor>(data);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(sizeof(LinkedReferenceColor));
	}
};
class ExtraScaleData : public ExtraData
{
protected:
	float scale;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		scale = f->read<float>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XSCL',4,f);
		f->write<float>(scale);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraOpenByDefaultData : public ExtraData
{
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('ONAM',0,f);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(0);
	}
};
class ExtraAudioMarkerData : public ExtraData
{
protected:
	char *name;
	formid mediaLocationController;
	ulong useControllerValues;
	float layer2Trigger;
	float layer3Trigger;
public:
	ExtraAudioMarkerData() : name(0), mediaLocationController(0)
	{
	}
	virtual ~ExtraAudioMarkerData()
	{
		if (name)
		{
			delete[] name;
		}
	}
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader hx)
	{
		ulong readSize = 0;
		for (;;)
		{
			SubrecordHeader h = form->ReadSubrecord(f);
			switch(h.type)
			{
			case 'FULL':
				name = f->readzstring(h.size);
				form->AddReadSize(h.size);
				break;
			case 'CNAM':
				mediaLocationController = f->read<formid>();
				form->AddReadSize(4);
				break;
			case 'BNAM':
				useControllerValues = f->read<ulong>();
				form->AddReadSize(4);
				break;
			case 'MNAM':
				layer2Trigger = f->read<float>();
				form->AddReadSize(4);
				break;
			case 'NNAM':
				layer3Trigger = f->read<float>();
				form->AddReadSize(4);
				break;
			default:
				f->unread(6);
				readSize -= 6;
				form->AddReadSize(readSize);
				return;
			}
		}
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('MMRK',0,f);
		form->WriteZStringSubrecord('FULL',name,f);
		if (mediaLocationController)
		{
			form->WriteSubrecord('CNAM',4,f);
			f->write<formid>(mediaLocationController);
		}
		form->WriteSubrecord('BNAM',4,f);
		f->write<formid>(useControllerValues);
		form->WriteSubrecord('MNAM',4,f);
		f->write<float>(layer2Trigger);
		form->WriteSubrecord('NNAM',4,f);
		f->write<float>(layer3Trigger);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		int size = 0;
		size += form->ComputeSubrecordSize(0);
		size += form->ZStringSubrecordSize(name);
		if (mediaLocationController)
		{
			size += form->ComputeSubrecordSize(4);
		}
		size += form->ComputeSubrecordSize(4);
		size += form->ComputeSubrecordSize(4);
		size += form->ComputeSubrecordSize(4);
		return size;
	}
};
class ExtraSpecialRenderFlagsData : public ExtraData
{
protected:
	ulong flags;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		flags = f->read<ulong>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XSRF',4,f);
		f->write<ulong>(flags);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraSpecialRenderFlagsDistanceData : public ExtraData
{
protected:
	float scale;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		scale = f->read<float>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XSRD',4,f);
		f->write<float>(scale);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
class ExtraChargeData : public ExtraData
{
protected:
	float scale;
public:
	virtual void Load(ExtraDataForm *form, FileRead *f, SubrecordHeader h)
	{
		scale = f->read<float>();
		form->AddReadSize(4);
	}
	virtual void Save(ExtraDataForm *form, FileWrite *f)
	{
		form->WriteSubrecord('XCHG',4,f);
		f->write<float>(scale);
	}
	virtual int GetSaveSize(ExtraDataForm *form)
	{
		return form->ComputeSubrecordSize(4);
	}
};
#define LoadExtraDataType(srid,edtype) \
		case srid: \
			{ \
				edtype *z = new edtype(); \
				z->Load(this,f,h); \
				extraData.Add(z); \
			} \
			break;
void ExtraDataForm::LoadExtraData(FileRead *f, SubrecordHeader h)
{
		switch(h.type)
		{
		LoadExtraDataType('XACT',ExtraActionData);
		LoadExtraDataType('XLOC',ExtraLockData);
		LoadExtraDataType('XRDO',ExtraRadioDataData);
		LoadExtraDataType('XTEL',ExtraTeleportData);
		LoadExtraDataType('XMRK',ExtraMapMarkerData);
		LoadExtraDataType('MMRK',ExtraAudioMarkerData);
		//AMRK AudioBuoyMarker
		LoadExtraDataType('XOWN',ExtraOwnershipData);
		//XGLB Global
		LoadExtraDataType('XRNK',ExtraFactionRankData);
		LoadExtraDataType('XCNT',ExtraCountData);
		LoadExtraDataType('XAMT',ExtraAmmoData);
		LoadExtraDataType('XAMC',ExtraAmmoCountData);
		LoadExtraDataType('XHLT',ExtraHealthData);
		LoadExtraDataType('XHLP',ExtraHealthPercData);
		//XHLP HealthPerc
		//XUSE Uses
		//XTIM TimeLeft
		LoadExtraDataType('XCHG',ExtraChargeData);
		//XPSN Poision
		LoadExtraDataType('XSED',ExtraSpeedTreeSeedData);
		LoadExtraDataType('XCLR',ExtraRegionListData);
		LoadExtraDataType('XCCM',ExtraCellClimateData);
		LoadExtraDataType('XCIM',ExtraImageSpaceData);
		LoadExtraDataType('XCWT',ExtraCellWaterTypeData);
		LoadExtraDataType('XCMO',ExtraCellMusicTypeData);
		LoadExtraDataType('XCAS',ExtraCellAcousticSpaceData);
		//XPSL PackageStartLocation
		LoadExtraDataType('XRGD',ExtraRagDollData);
		LoadExtraDataType('XRGB',ExtraRagDollBipedData);
		LoadExtraDataType('XLOD',ExtraDistantDataData);
		LoadExtraDataType('XESP',ExtraEnableStateParentData);
		//XRTM RandomTeleportMarker
		LoadExtraDataType('XLKR',ExtraLinkedRefData);
		LoadExtraDataType('XAPD',ExtraActivateRefData);
		LoadExtraDataType('XAPR',ExtraActivateRefDataData);
		LoadExtraDataType('XATO',ExtraActivateRefPromptData);
		LoadExtraDataType('XPWR',ExtraReflectorData);
		LoadExtraDataType('XLTW',ExtraLitWaterData);
		//XDCR DecalRefs
		LoadExtraDataType('XMRC',ExtraMerchantContainerData);
		LoadExtraDataType('XTRG',ExtraXTargetData);
		LoadExtraDataType('XEZN',ExtraEncounterZoneData);
		LoadExtraDataType('XEMI',ExtraEmittanceSourceData);
		LoadExtraDataType('XMBR',ExtraMultiBoundDataData);
		LoadExtraDataType('XMBO',ExtraMultiBoundOffsetData);
		LoadExtraDataType('XLCM',ExtraLevCreaModifierData);
		LoadExtraDataType('XNDP',ExtraNavMeshPortalData);
		LoadExtraDataType('XRDS',ExtraRadiusData);
		LoadExtraDataType('XRAD',ExtraRadiationData);
		LoadExtraDataType('XCLP',ExtraLinkColorData);
		LoadExtraDataType('XPRM',ExtraPrimitiveData);
		LoadExtraDataType('XPRD',ExtraPatrolRefData);
		LoadExtraDataType('XPPA',ExtraPatrolRefScriptMarkerData);
		LoadExtraDataType('XOCP',ExtraOcclusionPlaneData);
		LoadExtraDataType('XORD',ExtraOcclusionPlaneRefDataData);
		LoadExtraDataType('XPTL',ExtraPortalData);
		LoadExtraDataType('XPOD',ExtraPortalRoomData);
		LoadExtraDataType('XRMR',ExtraRoomHeaderData);
		LoadExtraDataType('XLRM',ExtraLinkedRoomData);
		LoadExtraDataType('XMBP',ExtraMultiBoundPrimitiveData);
		LoadExtraDataType('XTRI',ExtraCollisionLayerData);
		LoadExtraDataType('XIBS',ExtraIgnoredBySandboxData);
		//XHLT WeaponModFlags
		LoadExtraDataType('XSRF',ExtraSpecialRenderFlagsData);
		LoadExtraDataType('XSRD',ExtraSpecialRenderFlagsDistanceData);
		LoadExtraDataType('NAME',ExtraParentObjectData);
		LoadExtraDataType('XSCL',ExtraScaleData);
		LoadExtraDataType('ONAM',ExtraOpenByDefaultData);
		LoadExtraDataType('XCET',ExtraCETData);
		LoadExtraDataType('XCMT',ExtraCMTData);

		/*
		LoadExtraDataType('RCLR',ExtraLinkColorData2);
		*/
		default:
			printf("Unknown subrecord found");
			__debugbreak();
			break;
		}
}
