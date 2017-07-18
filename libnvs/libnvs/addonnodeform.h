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
struct AddonNodeData
{
	ushort particleSystemCap;
	ubyte unk;
};
class AddonNodeForm : public BoundObjectForm, public ModelTextureSwap
{
protected:
	AddonNodeData data;
	ulong nodeIndex;
	formid sound;
public:
	AddonNodeForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), sound(0)
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
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
			case 'DATA':
				nodeIndex = f->read<ulong>();
				readSize += 4;
				break;
			case 'SNAM':
				sound = f->read<formid>();
				readSize += 4;
				break;
			case 'DNAM':
				data = f->read<AddonNodeData>();
				readSize += sizeof(AddonNodeData);
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
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		WriteSubrecord('DATA',4,f);
		f->write<ulong>(nodeIndex);
		if (sound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(sound);
		}
		WriteSubrecord('DNAM',sizeof(AddonNodeData),f);
		f->write<AddonNodeData>(data);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		size += ComputeSubrecordSize(4);
		if (sound)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(sizeof(AddonNodeData));
		return size;
	}
};
