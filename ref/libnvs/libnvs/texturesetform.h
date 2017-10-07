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
struct DecalInfo
{
	float minWidth;
	float maxWidth;
	float minHeight;
	float maxHeight;
	float depth;
	float shininess;
	float parallaxScale;
	ubyte parallaxPasses;
	ubyte flags;
	ulong color;
};
class TextureSetForm : public BoundObjectForm
{
protected:
	char *textures[6];
	DecalInfo decalInfo;
	bool hasDecalInfo;
	ushort flags;
	bool hasFlags;
public:
	TextureSetForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), hasDecalInfo(false), hasFlags(false)
	{
		for (int i = 0;i < 6;i++)
		{
			textures[i] = 0;
		}
	}
	virtual ~TextureSetForm()
	{
		for (int i = 0;i < 6;i++)
		{
			if (textures[i])
			{
				delete[] textures[i];
			}
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
			case 'TX00':
				textures[0] = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'TX01':
				textures[1] = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'TX02':
				textures[2] = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'TX03':
				textures[3] = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'TX04':
				textures[4] = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'TX05':
				textures[5] = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DODT':
				decalInfo = f->read<DecalInfo>();
				readSize += sizeof(DecalInfo);
				hasDecalInfo = true;
				break;
			case 'DNAM':
				hasFlags = true;
				flags = f->read<ushort>();
				readSize += 2;
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
		WriteZStringSubrecord('TX00',textures[0],f);
		WriteZStringSubrecord('TX01',textures[1],f);
		WriteZStringSubrecord('TX02',textures[2],f);
		WriteZStringSubrecord('TX03',textures[3],f);
		WriteZStringSubrecord('TX04',textures[4],f);
		WriteZStringSubrecord('TX05',textures[5],f);
		if (hasDecalInfo)
		{
			WriteSubrecord('DODT',sizeof(DecalInfo),f);
			f->write<DecalInfo>(decalInfo);
		}
		if (hasFlags)
		{
			WriteSubrecord('DNAM',2,f);
			f->write<ushort>(flags);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		size += ZStringSubrecordSize(textures[0]);
		size += ZStringSubrecordSize(textures[1]);
		size += ZStringSubrecordSize(textures[2]);
		size += ZStringSubrecordSize(textures[3]);
		size += ZStringSubrecordSize(textures[4]);
		size += ZStringSubrecordSize(textures[5]);
		if (hasDecalInfo)
		{
			size += ComputeSubrecordSize(sizeof(DecalInfo));
		}
		if (hasFlags)
		{
			size += ComputeSubrecordSize(2);
		}
		return size;
	}
};
