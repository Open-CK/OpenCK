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
struct ClimateWeather
{
	formid weather;
	ulong chance;
	formid global;
};
#pragma pack(push, 1)
struct ClimateTiming
{
	ubyte sunriseBegin;
	ubyte sunriseEnd;
	ubyte sunsetBegin;
	ubyte sunsetEnd;
	ubyte volatility;
	ubyte moonPhaseLength;
};
#pragma pack(pop)
class ClimateForm : public Form
{
protected:
	ulong weatherCount;
	ClimateWeather *weatherTypes;
	Texture sunTexture;
	Texture sunGlareTexture;
	Model nightSkyModel;
	ClimateTiming timing;
public:
	ClimateForm(FormHeader h,ModFile *f) : Form(h,f), weatherCount(0), weatherTypes(0)
	{
	}
	virtual ~ClimateForm()
	{
		if (weatherTypes)
		{
			delete[] weatherTypes;
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
			case 'WLST':
				weatherCount = h.size / sizeof(ClimateWeather);
				weatherTypes = f->readarray<ClimateWeather>(weatherCount);
				readSize += h.size;
				break;
			TextureLoad((&sunTexture),'FNAM');
			TextureLoad((&sunGlareTexture),'GNAM');
			ModelBRLoad((&nightSkyModel),'MODL','MODB','MODT');
			case 'TNAM':
				timing = f->read<ClimateTiming>();
				readSize += sizeof(ClimateTiming);
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
		if (weatherCount)
		{
			WriteSubrecord('WLST',weatherCount * sizeof(ClimateWeather),f);
			f->writearray<ClimateWeather>(weatherCount,weatherTypes);
		}
		TextureSave((&sunTexture),'FNAM');
		TextureSave((&sunGlareTexture),'GNAM');
		ModelBRSave((&nightSkyModel),'MODL','MODB','MODT');
		WriteSubrecord('TNAM',sizeof(ClimateTiming),f);
		f->write<ClimateTiming>(timing);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		if (weatherCount)
		{
			size += ComputeSubrecordSize(weatherCount * sizeof(ClimateWeather));
		}
		TextureGetSaveSize((&sunTexture));
		TextureGetSaveSize((&sunGlareTexture));
		ModelBRGetSaveSize((&nightSkyModel));
		size += ComputeSubrecordSize(sizeof(ClimateTiming));
		return size;
	}
};
