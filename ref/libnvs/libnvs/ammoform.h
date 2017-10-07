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
struct AmmoData
{
	float speed;
	ubyte flags;
	ubyte pad[3];
	long value;
	ubyte clipRounds;
};
#pragma pack(pop)
struct AmmoData2
{
	ulong projectilesPerShot;
	formid projectile;
	float weight;
	formid consumedAmmo;
	float consumedPerc;
};
struct AmmoData2Old
{
	ulong projectilesPerShot;
	formid projectile;
	float weight;
};
class AmmoForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Texture, public MessageTexture, public Scriptable, public DestructibleObject, public PickupPutdownSounds
{
protected:
	AmmoData data;
	AmmoData2 data2;
	AmmoData2Old data2Old;
	bool hasData2Old;
	bool hasData2;
	char *shortName;
	char *abbreviation;
	SimpleDynVecClass<formid> effects;
public:
	AmmoForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), shortName(0), abbreviation(0), hasData2(false), hasData2Old(false)
	{
	}
	virtual ~AmmoForm()
	{
		if (shortName)
		{
			delete[] shortName;
		}
		if (abbreviation)
		{
			delete[] abbreviation;
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
			TextureLoad(this,'ICON');
			MessageTextureLoad(this,'MICO');
			ScriptableLoad();
			DestructibleObjectLoad();
			PickupPutdownSoundsLoad();
			case 'DATA':
				data = f->read<AmmoData>();
				readSize += sizeof(AmmoData);
				break;
			case 'DAT2':
				if (h.size == sizeof(AmmoData2))
				{
					data2 = f->read<AmmoData2>();
					readSize += sizeof(AmmoData2);
				}
				else
				{
					data2Old = f->read<AmmoData2Old>();
					readSize += sizeof(AmmoData2Old);
					hasData2Old = true;
				}
				hasData2 = true;
				break;
			case 'ONAM':
				shortName = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'QNAM':
				abbreviation = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'RCIL':
				effects.Add(f->read<formid>());
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
		TextureSave(this,'ICON');
		MessageTextureSave(this,'MICO');
		ScriptableSave();
		DestructibleObjectSave();
		PickupPutdownSoundsSave();
		WriteSubrecord('DATA',sizeof(AmmoData),f);
		f->write<AmmoData>(data);
		if (hasData2)
		{
			if (hasData2Old)
			{
				WriteSubrecord('DAT2',sizeof(AmmoData2Old),f);
				f->write<AmmoData2Old>(data2Old);
			}
			else
			{
				WriteSubrecord('DAT2',sizeof(AmmoData2),f);
				f->write<AmmoData2>(data2);
			}
		}
		WriteZStringSubrecord('ONAM',shortName,f);
		WriteZStringSubrecord('QNAM',abbreviation,f);
		for (int i = 0;i < effects.Count();i++)
		{
			WriteSubrecord('RCIL',4,f);
			f->write<formid>(effects[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		TextureGetSaveSize(this);
		MessageTextureGetSaveSize(this);
		ScriptableGetSaveSize();
		DestructibleObjectGetSaveSize();
		PickupPutdownSoundsGetSaveSize();
		size += ComputeSubrecordSize(sizeof(AmmoData));
		if (hasData2)
		{
			if (hasData2Old)
			{
				size += ComputeSubrecordSize(sizeof(AmmoData2Old));
			}
			else
			{
				size += ComputeSubrecordSize(sizeof(AmmoData2));
			}
		}
		size += ZStringSubrecordSize(shortName);
		size += ZStringSubrecordSize(abbreviation);
		for (int i = 0;i < effects.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
