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
struct LightData
{
	long time;
	ulong radius;
	ulong color;
	ulong flags;
	float falloff;
	float fov;
	ulong value;
	float weight;
};
class LightForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Texture, public MessageTexture, public Scriptable, public DestructibleObject
{
protected:
	LightData data;
	float fade;
	formid sound;
public:
	LightForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), fade(0), sound(0)
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
			ScriptableLoad();
			FullNameLoad();
			TextureLoad(this,'ICON');
			MessageTextureLoad(this,'MICO');
			case 'DATA':
				data = f->read<LightData>();
				readSize += sizeof(LightData);
				break;
			case 'FNAM':
				fade = f->read<float>();
				readSize += 4;
				break;
			case 'SNAM':
				sound = f->read<formid>();
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
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		ScriptableSave();
		if (data.flags & 2)
		{
			FullNameSave();
			TextureSave(this,'ICON');
			MessageTextureSave(this,'MICO');
		}
		WriteSubrecord('DATA',sizeof(LightData),f);
		f->write<LightData>(data);
		WriteSubrecord('FNAM',4,f);
		f->write<float>(fade);
		if (sound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(sound);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		ScriptableGetSaveSize();
		if (data.flags & 2)
		{
			FullNameGetSaveSize();
			TextureGetSaveSize(this);
			MessageTextureGetSaveSize(this);
		}
		size += ComputeSubrecordSize(sizeof(LightData));
		size += ComputeSubrecordSize(4);
		if (sound)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
