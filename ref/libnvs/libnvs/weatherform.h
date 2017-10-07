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
struct WeatherColor
{
	ulong sunrise;
	ulong day;
	ulong sunset;
	ulong night;
	ulong highNoon;
	ulong midnight;
};
struct WeatherColorOld
{
	ulong sunrise;
	ulong day;
	ulong sunset;
	ulong night;
};
struct CloudSpeed
{
	ubyte layer0Speed;
	ubyte layer1Speed;
	ubyte layer2Speed;
	ubyte layer3Speed;
};
struct CloudColors
{
	WeatherColor layer0Color;
	WeatherColor layer1Color;
	WeatherColor layer2Color;
	WeatherColor layer3Color;
};
struct CloudColorsOld
{
	WeatherColorOld layer0Color;
	WeatherColorOld layer1Color;
	WeatherColorOld layer2Color;
	WeatherColorOld layer3Color;
};
struct WeatherColors
{
	WeatherColor upperSky;
	WeatherColor fog;
	WeatherColor lowerClouds;
	WeatherColor ambient;
	WeatherColor sunlight;
	WeatherColor sun;
	WeatherColor stars;
	WeatherColor lowerSky;
	WeatherColor horizon;
	WeatherColor upperClouds;
};
struct WeatherColorsOld
{
	WeatherColorOld upperSky;
	WeatherColorOld fog;
	WeatherColorOld lowerClouds;
	WeatherColorOld ambient;
	WeatherColorOld sunlight;
	WeatherColorOld sun;
	WeatherColorOld stars;
	WeatherColorOld lowerSky;
	WeatherColorOld horizon;
	WeatherColorOld upperClouds;
};
struct WeatherFog
{
	float dayNear;
	float dayFar;
	float nightNear;
	float nightFar;
	float dayPower;
	float nightPower;
};
#pragma pack(push, 1)
struct WeatherData
{
	ubyte windSpeed;
	ubyte cloudSpeedLower;
	ubyte cloudSpeedUpper;
	ubyte transitionDelta;
	ubyte sunGlare;
	ubyte sunDamage;
	ubyte precipitationFadeIn;
	ubyte precipitationFadeOut;
	ubyte lightningFadeIn;
	ubyte lightningFadeOut;
	ubyte lightningFrequency;
	ubyte weatherType;
	ubyte lightningColorRed;
	ubyte lightningColorGreen;
	ubyte lightningColorBlue;
};
#pragma pack(pop)
struct WeatherSound
{
	formid sound;
	ulong type;
};
class WeatherForm : public Form
{
protected:
	formid imageSpaceModifiers[6];
	ulong cloudTextureCount;
	char *cloudTextures[4];
	CloudSpeed cloudSpeed;
	CloudColors cloudColors;
	CloudColorsOld cloudColorsOld;
	bool hasCloudColorsOld;
	Model preciptationModel;
	WeatherData data;
	WeatherFog fog;
	WeatherColors colors;
	WeatherColorsOld colorsOld;
	bool hasColorsOld;
	SimpleDynVecClass<WeatherSound> sounds;
	float *HDRData;
public:
	WeatherForm(FormHeader h,ModFile *f) : Form(h,f), cloudTextureCount(0), HDRData(0), hasCloudColorsOld(false), hasColorsOld(false)
	{
		imageSpaceModifiers[0] = 0;
		imageSpaceModifiers[1] = 0;
		imageSpaceModifiers[2] = 0;
		imageSpaceModifiers[3] = 0;
		imageSpaceModifiers[4] = 0;
		imageSpaceModifiers[5] = 0;
		cloudTextures[0] = 0;
		cloudTextures[1] = 0;
		cloudTextures[2] = 0;
		cloudTextures[3] = 0;
	}
	virtual ~WeatherForm()
	{
		if (cloudTextures[0])
		{
			delete[] cloudTextures[0];
		}
		if (cloudTextures[1])
		{
			delete[] cloudTextures[1];
		}
		if (cloudTextures[2])
		{
			delete[] cloudTextures[2];
		}
		if (cloudTextures[3])
		{
			delete[] cloudTextures[3];
		}
		if (HDRData)
		{
			delete[] HDRData;
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
			case 0x00494144:
				imageSpaceModifiers[0] = f->read<formid>();
				readSize += 4;
				break;
			case 0x01494144:
				imageSpaceModifiers[1] = f->read<formid>();
				readSize += 4;
				break;
			case 0x02494144:
				imageSpaceModifiers[2] = f->read<formid>();
				readSize += 4;
				break;
			case 0x03494144:
				imageSpaceModifiers[3] = f->read<formid>();
				readSize += 4;
				break;
			case 0x04494144:
				imageSpaceModifiers[4] = f->read<formid>();
				readSize += 4;
				break;
			case 0x05494144:
				imageSpaceModifiers[5] = f->read<formid>();
				readSize += 4;
				break;
			case 'DNAM':
				cloudTextures[0] = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'CNAM':
				cloudTextures[1] = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'ANAM':
				cloudTextures[2] = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'BNAM':
				cloudTextures[3] = f->readzstring(h.size);
				readSize += h.size;
				break;
			ModelBRLoad((&preciptationModel),'MODL','MODB','MODT');
			case 'LNAM':
				cloudTextureCount = f->read<ulong>();
				readSize += 4;
				break;
			case 'ONAM':
				cloudSpeed = f->read<CloudSpeed>();
				readSize += sizeof(CloudSpeed);
				break;
			case 'PNAM':
				if (h.size == sizeof(CloudColorsOld))
				{
					cloudColorsOld = f->read<CloudColorsOld>();
					readSize += sizeof(CloudColorsOld);
					hasCloudColorsOld = true;
				}
				else
				{
					cloudColors = f->read<CloudColors>();
					readSize += sizeof(CloudColors);
				}
				break;
			case 'NAM0':
				if (h.size == sizeof(WeatherColorsOld))
				{
					colorsOld = f->read<WeatherColorsOld>();
					readSize += sizeof(WeatherColorsOld);
					hasColorsOld = true;
				}
				else
				{
					colors = f->read<WeatherColors>();
					readSize += sizeof(WeatherColors);
				}
				break;
			case 'FNAM':
				fog = f->read<WeatherFog>();
				readSize += sizeof(WeatherFog);
				break;
			case 'INAM':
				HDRData = f->readarray<float>(0x130 / 4);
				readSize += 0x130;
				break;
			case 'DATA':
				data = f->read<WeatherData>();
				readSize += sizeof(WeatherData);
				break;
			case 'SNAM':
				sounds.Add(f->read<WeatherSound>());
				readSize += sizeof(WeatherSound);
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
		for (int i = 0;i < 6;i++)
		{
			if (imageSpaceModifiers[i])
			{
				WriteSubrecord(SwapBytes(0x44414900 + i),4,f);
				f->write<formid>(imageSpaceModifiers[i]);
			}
		}
		WriteZStringSubrecord('DNAM',cloudTextures[0],f);
		WriteZStringSubrecord('CNAM',cloudTextures[1],f);
		WriteZStringSubrecord('ANAM',cloudTextures[2],f);
		WriteZStringSubrecord('BNAM',cloudTextures[3],f);
		ModelBRSave((&preciptationModel),'MODL','MODB','MODT');
		WriteSubrecord('LNAM',4,f);
		f->write<ulong>(cloudTextureCount);
		WriteSubrecord('ONAM',sizeof(CloudSpeed),f);
		f->write<CloudSpeed>(cloudSpeed);
		if (hasCloudColorsOld)
		{
			WriteSubrecord('PNAM',sizeof(CloudColorsOld),f);
			f->write<CloudColorsOld>(cloudColorsOld);
		}
		else
		{
			WriteSubrecord('PNAM',sizeof(CloudColors),f);
			f->write<CloudColors>(cloudColors);
		}
		if (hasColorsOld)
		{
			WriteSubrecord('NAM0',sizeof(WeatherColorsOld),f);
			f->write<WeatherColorsOld>(colorsOld);
		}
		else
		{
			WriteSubrecord('NAM0',sizeof(WeatherColors),f);
			f->write<WeatherColors>(colors);
		}
		WriteSubrecord('FNAM',sizeof(WeatherFog),f);
		f->write<WeatherFog>(fog);
		WriteSubrecord('INAM',0x130,f);
		f->writearray<float>(0x130 / 4,HDRData);
		WriteSubrecord('DATA',sizeof(WeatherData),f);
		f->write<WeatherData>(data);
		for (int i = 0;i < sounds.Count();i++)
		{
			WriteSubrecord('SNAM',sizeof(WeatherSound),f);
			f->write<WeatherSound>(sounds[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		for (int i = 0;i < 6;i++)
		{
			if (imageSpaceModifiers[i])
			{
				size += ComputeSubrecordSize(4);
			}
		}
		size += ZStringSubrecordSize(cloudTextures[0]);
		size += ZStringSubrecordSize(cloudTextures[1]);
		size += ZStringSubrecordSize(cloudTextures[2]);
		size += ZStringSubrecordSize(cloudTextures[3]);
		ModelBRGetSaveSize((&preciptationModel));
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(sizeof(CloudSpeed));
		if (hasCloudColorsOld)
		{
			size += ComputeSubrecordSize(sizeof(CloudColorsOld));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(CloudColors));
		}
		if (hasColorsOld)
		{
			size += ComputeSubrecordSize(sizeof(WeatherColorsOld));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(WeatherColors));
		}
		size += ComputeSubrecordSize(sizeof(WeatherFog));
		size += ComputeSubrecordSize(0x130);
		size += ComputeSubrecordSize(sizeof(WeatherData));
		for (int i = 0;i < sounds.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(WeatherSound));
		}
		return size;
	}
};
