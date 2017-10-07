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
struct SoundData
{
	ubyte minAttenuation;
	ubyte maxAttenuation;
	byte frequencyAdjustment;
	ulong flags;
	short staticAttenuation;
	ushort time;
	short attenuationPoints[5];
	short reverbAttenuation;
	long priority;
	long x;
	long y;
};
struct SoundDataOld
{
	ubyte minAttenuation;
	ubyte maxAttenuation;
	byte frequencyAdjustment;
	ulong flags;
	short staticAttenuation;
	ushort time;
};
class SoundForm : public BoundObjectForm, public SoundFile
{
protected:
	SoundData soundData;
	bool SNDDSeen;
	SoundDataOld soundDataOld;
	bool SNDXSeen;
	short attenuationPoints[5];
	bool ANAMSeen;
	short reverbAttenuation;
	bool GNAMSeen;
	long priority;
	bool HNAMSeen;
	ubyte random;
	bool RNAMSeen;
public:
	SoundForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), SNDDSeen(false), SNDXSeen(false), ANAMSeen(false), GNAMSeen(false), HNAMSeen(false), RNAMSeen(false)
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
			SoundFileLoad();
			case 'RNAM':
				random = f->read<ubyte>();
				readSize += 1;
				RNAMSeen = true;
				break;
			case 'SNDD':
				soundData = f->read<SoundData>();
				readSize += sizeof(SoundData);
				SNDDSeen = true;
				break;
			case 'SNDX':
				soundDataOld = f->read<SoundDataOld>();
				readSize += sizeof(SoundDataOld);
				SNDXSeen = true;
				break;
			case 'ANAM':
				f->readarray<short>(5,attenuationPoints);
				readSize += h.size;
				ANAMSeen = true;
				break;
			case 'GNAM':
				reverbAttenuation = f->read<short>();
				readSize += 2;
				GNAMSeen = true;
				break;
			case 'HNAM':
				priority = f->read<long>();
				readSize += 4;
				HNAMSeen = true;
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
		if (header.flags & 0x20)
		{
			return;
		}
		BoundObjectFormSave();
		SoundFileSave();
		if (RNAMSeen)
		{
			WriteSubrecord('RNAM',1,f);
			f->write<ubyte>(random);
		}
		if (SNDDSeen)
		{
			WriteSubrecord('SNDD',sizeof(SoundData),f);
			f->write<SoundData>(soundData);
		}
		if (SNDXSeen)
		{
			WriteSubrecord('SNDX',sizeof(SoundDataOld),f);
			f->write<SoundDataOld>(soundDataOld);
		}
		if (ANAMSeen)
		{
			WriteSubrecord('ANAM',10,f);
			f->writearray<short>(5,attenuationPoints);
		}
		if (GNAMSeen)
		{
			WriteSubrecord('GNAM',2,f);
			f->write<short>(reverbAttenuation);
		}
		if (HNAMSeen)
		{
			WriteSubrecord('HNAM',4,f);
			f->write<long>(priority);
		}
	}
	virtual int GetSaveSize()
	{
		if (header.flags & 0x20)
		{
			return 0;
		}
		int size = 0;
		BoundObjectFormGetSaveSize();
		SoundFileGetSaveSize();
		if (RNAMSeen)
		{
			size += ComputeSubrecordSize(1);
		}
		if (SNDDSeen)
		{
			size += ComputeSubrecordSize(sizeof(SoundData));
		}
		if (SNDXSeen)
		{
			size += ComputeSubrecordSize(sizeof(SoundDataOld));
		}
		if (ANAMSeen)
		{
			size += ComputeSubrecordSize(10);
		}
		if (GNAMSeen)
		{
			size += ComputeSubrecordSize(2);
		}
		if (HNAMSeen)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
