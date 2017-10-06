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
struct WaterData
{
	float unk1;
	float unk2;
	float unk3;
	float unk4;
	float sunPower;
	float reflectivity;
	float fresnel;
	float unk5;
	float fogNearPlane;
	float fogFarPlane;
	ulong shadowColor;
	ulong deepColor;
	ulong reflectionColor;
	int unk6;
	float rainForce;
	float rainVelocity;
	float rainFalloff;
	float rainDampner;
	float displacementStartingSize;
	float displacementForce;
	float displacementVelocity;
	float displacementFalloff;
	float displacementDampner;
	float rainStartingSize;
	float noiseNoiseScale;
	float noiseWindDirection;
	float noiseWindDirection2;
	float noiseWindDirection3;
	float noiseWindSpeed;
	float noiseWindSpeed2;
	float noiseWindSpeed3;
	float noiseDepthFalloffStart;
	float noiseDepthFalloffEnd;
	float fogAmount;
	float noiseNormalsUVScale;
	float fogUnderwaterAmount;
	float fogUnderwaterNearPlane;
	float fogUnderwaterFarPlane;
	float distortion;
	float shininess;
	float reflectionHDRMultiplier;
	float lightRadius;
	float lightBrightness;
	float noiseUVScale;
	float noiseUVScale2;
	float noiseUVScale3;
	float noiseAmplitudeScale;
	float noiseAmplitudeScale2;
	float noiseAmplitudeScale3;
};
struct WaterDataOld
{
	float unk1;
	float unk2;
	float unk3;
	float unk4;
	float sunPower;
	float reflectivity;
	float fresnel;
	float unk5;
	float fogNearPlane;
	float fogFarPlane;
	ulong shadowColor;
	ulong deepColor;
	ulong reflectionColor;
	int unk6;
	float rainForce;
	float rainVelocity;
	float rainFalloff;
	float rainDampner;
	float displacementStartingSize;
	float displacementForce;
	float displacementVelocity;
	float displacementFalloff;
	float displacementDampner;
	float rainStartingSize;
	float noiseNoiseScale;
	float noiseWindDirection;
	float noiseWindDirection2;
	float noiseWindDirection3;
	float noiseWindSpeed;
	float noiseWindSpeed2;
	float noiseWindSpeed3;
	float noiseDepthFalloffStart;
	float noiseDepthFalloffEnd;
	float fogAmount;
	float noiseNormalsUVScale;
	float fogUnderwaterAmount;
	float fogUnderwaterNearPlane;
	float fogUnderwaterFarPlane;
	float distortion;
	float shininess;
	float reflectionHDRMultiplier;
	float lightRadius;
	float lightBrightness;
	float noiseUVScale;
	float noiseUVScale2;
	float noiseUVScale3;
};
#pragma pack(push,1)
struct WaterData2
{
	float unk1;
	float unk2;
	float unk3;
	float unk4;
	float sunPower;
	float reflectivity;
	float fresnel;
	float unk5;
	float fogNearPlane;
	float fogFarPlane;
	ulong shadowColor;
	ulong deepColor;
	ulong reflectionColor;
	int unk6;
	float rainForce;
	float rainVelocity;
	float rainFalloff;
	float rainDampner;
	float displacementStartingSize;
	float displacementForce;
	float displacementVelocity;
	float displacementFalloff;
	float displacementDampner;
	float rainStartingSize;
	float noiseNoiseScale;
	float noiseWindDirection;
	float noiseWindDirection2;
	float noiseWindDirection3;
	float noiseWindSpeed;
	float noiseWindSpeed2;
	float noiseWindSpeed3;
	float noiseDepthFalloffStart;
	float noiseDepthFalloffEnd;
	float fogAmount;
	float noiseNormalsUVScale;
	float fogUnderwaterAmount;
	float fogUnderwaterNearPlane;
	float fogUnderwaterFarPlane;
	float distortion;
	float shininess;
	float reflectionHDRMultiplier;
	float lightRadius;
	float lightBrightness;
	float noiseUVScale;
	float noiseUVScale2;
	float noiseUVScale3;
	ushort damage;
};
#pragma pack(pop)
struct RelatedWaters
{
	formid dayTime;
	formid nightTime;
	formid underwater;
};
class WaterForm : public Form, public FullName
{
protected:
	Texture noiseMap;
	ubyte opacity;
	ubyte flags;
	char *materialId;
	formid sound;
	formid actorEffect;
	ushort damage;
	WaterData data;
	WaterDataOld dataOld;
	WaterData2 data2;
	bool hasData;
	bool hasData2;
	bool hasWaterData;
	bool hasWaterDataOld;
	RelatedWaters relatedWaters;
public:
	WaterForm(FormHeader h,ModFile *f) : Form(h,f), materialId(0), sound(0), actorEffect(0), hasData(false), hasData2(false), hasWaterData(false), hasWaterDataOld(false)
	{
	}
	virtual ~WaterForm()
	{
		if (materialId)
		{
			delete[] materialId;
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
			FormLoad();
			FullNameLoad();
			TextureLoad((&noiseMap),'NNAM');
			case 'ANAM':
				opacity = f->read<ubyte>();
				readSize += 1;
				break;
			case 'FNAM':
				flags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'MNAM':
				materialId = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SNAM':
				sound = f->read<formid>();
				readSize += 4;
				break;
			case 'XNAM':
				actorEffect = f->read<formid>();
				readSize += 4;
				break;
			case 'DATA':
				if (h.size == 2)
				{
					hasData = true;
					damage = f->read<ushort>();
					readSize += 2;
				}
				else
				{
					hasData2 = true;
					data2 = f->read<WaterData2>();
					readSize += sizeof(WaterData2);
				}
				break;
			case 'DNAM':
				hasWaterData = true;
				if (h.size == sizeof(WaterData))
				{
					data = f->read<WaterData>();
					readSize += sizeof(WaterData);
				}
				else if (h.size == sizeof(WaterDataOld))
				{
					hasWaterDataOld = true;
					dataOld = f->read<WaterDataOld>();
					readSize += sizeof(WaterDataOld);
				}
				break;
			case 'GNAM':
				relatedWaters = f->read<RelatedWaters>();
				readSize += sizeof(RelatedWaters);
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
		FullNameSave();
		TextureSave((&noiseMap),'NNAM');
		WriteSubrecord('ANAM',1,f);
		f->write<ubyte>(opacity);
		WriteSubrecord('FNAM',1,f);
		f->write<ubyte>(flags);
		WriteZStringSubrecord('MNAM',materialId,f);
		if (sound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(sound);
		}
		if (actorEffect)
		{
			WriteSubrecord('XNAM',4,f);
			f->write<formid>(actorEffect);
		}
		if (hasData)
		{
			WriteSubrecord('DATA',2,f);
			f->write<ushort>(damage);
		}
		if (hasData2)
		{
			WriteSubrecord('DATA',sizeof(WaterData2),f);
			f->write<WaterData2>(data2);
		}
		if (hasWaterData)
		{
			if (hasWaterDataOld)
			{
				WriteSubrecord('DNAM',sizeof(WaterDataOld),f);
				f->write<WaterDataOld>(dataOld);
			}
			else
			{
				WriteSubrecord('DNAM',sizeof(WaterData),f);
				f->write<WaterData>(data);
			}
		}
		WriteSubrecord('GNAM',sizeof(RelatedWaters),f);
		f->write<RelatedWaters>(relatedWaters);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		TextureGetSaveSize((&noiseMap));
		size += ComputeSubrecordSize(1);
		size += ComputeSubrecordSize(1);
		size += ZStringSubrecordSize(materialId);
		if (sound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (actorEffect)
		{
			size += ComputeSubrecordSize(4);
		}
		if (hasData)
		{
			size += ComputeSubrecordSize(2);
		}
		if (hasData2)
		{
			size += ComputeSubrecordSize(sizeof(WaterData2));
		}
		if (hasWaterData)
		{
			if (hasWaterDataOld)
			{
				size += ComputeSubrecordSize(sizeof(WaterDataOld));
			}
			else
			{
				size += ComputeSubrecordSize(sizeof(WaterData));
			}
		}
		size += ComputeSubrecordSize(sizeof(RelatedWaters));
		return size;
	}
};
