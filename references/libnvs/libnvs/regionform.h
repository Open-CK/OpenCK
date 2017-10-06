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
struct RegionArea
{
	ulong edgeFallOff;
	ulong pointCount;
	NiPoint2 *points;
	RegionArea() : edgeFallOff(0), pointCount(0), points(0)
	{
	}
	virtual ~RegionArea()
	{
		if (points)
		{
			delete[] points;
		}
	}
};
struct RegionObject
{
	formid object;
	ushort parentIndex;
	float density;
	ubyte clustering;
	ubyte minSlope;
	ubyte maxSlope;
	ubyte flags;
	ushort radiusParented;
	ushort radius;
	ulong minHeight;
	float maxHeight;
	float sink;
	float sinkVariance;
	float sizeVariance;
	ushort angleVarianceX;
	ushort angleVarianceY;
	ushort angleVarianceZ;
	ulong paintVerticesColor;
};
struct RegionGrass
{
	formid grass;
	formid landTexture;
};
struct RegionSound
{
	formid sound;
	ulong flags;
	ulong chance;
};
struct RegionWeather
{
	formid weather;
	ulong chance;
	formid global;
};
struct RegionData
{
	ulong type;
	ubyte flags;
};
struct RegionDataEntry
{
	RegionData data;
	ulong objectCount;
	RegionObject *objects;
	char *mapName;
	char *icon;
	ulong grassCount;
	RegionGrass *grasses;
	ulong musicType;
	bool hasMusicType;
	formid music;
	formid mediaSet;
	bool hasMediaSet;
	SimpleDynVecClass<formid> battleMediaSets;
	ulong soundCount;
	RegionSound *sounds;
	ulong weatherCount;
	RegionWeather *weatherTypes;
	ulong imposterCount;
	formid *imposters;
	RegionDataEntry() : objectCount(0), objects(0), mapName(0), icon(0), grassCount(0), grasses(0), music(0), soundCount(0), sounds(0), weatherCount(0), weatherTypes(0), hasMusicType(false), imposterCount(0), imposters(0), hasMediaSet(false)
	{
	}
	virtual ~RegionDataEntry()
	{
		if (objects)
		{
			delete[] objects;
		}
		if (mapName)
		{
			delete[] mapName;
		}
		if (icon)
		{
			delete[] icon;
		}
		if (grasses)
		{
			delete[] grasses;
		}
		if (sounds)
		{
			delete[] sounds;
		}
		if (imposters)
		{
			delete[] imposters;
		}
	}
};
class RegionForm : public Form
{
protected:
	char *editorID;
	char *icon;
	ulong mapColor;
	formid worldspace;
	SimpleDynVecClass<RegionArea *> areas;
	SimpleDynVecClass<RegionDataEntry *> dataEntries;
public:
	RegionForm(FormHeader h,ModFile *f) : Form(h,f), icon(0), worldspace(0), areas(0), dataEntries(0)
	{
	}
	virtual ~RegionForm()
	{
		if (icon)
		{
			delete[] icon;
		}
		for (int i = 0;i < areas.Count();i++)
		{
			delete areas[i];
		}
		for (int i = 0;i < dataEntries.Count();i++)
		{
			delete dataEntries[i];
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentArea = -1;
		int currentEntry = -1;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			case 'ICON':
				if (!dataEntries.Count())
				{
					icon = f->readzstring(h.size);
					readSize += h.size;
				}
				else
				{
					dataEntries[currentEntry]->icon = f->readzstring(h.size);
					readSize += h.size;
				}
				break;
			case 'RCLR':
				mapColor = f->read<ulong>();
				readSize += 4;
				break;
			case 'WNAM':
				worldspace = f->read<formid>();
				readSize += 4;
				break;
			case 'RPLI':
				currentArea++;
				areas.Add(new RegionArea());
				areas[currentArea]->edgeFallOff = f->read<ulong>();
				readSize += 4;
				break;
			case 'RPLD':
				areas[currentArea]->pointCount = h.size / 8;
				areas[currentArea]->points = f->readarray<NiPoint2>(h.size / 8);
				readSize += h.size;
				break;
			case 'RDAT':
				currentEntry++;
				dataEntries.Add(new RegionDataEntry());
				dataEntries[currentEntry]->data = f->read<RegionData>();
				readSize += sizeof(RegionData);
				break;
			case 'RDOT':
				dataEntries[currentEntry]->objectCount = h.size / sizeof(RegionObject);
				dataEntries[currentEntry]->objects = f->readarray<RegionObject>(h.size / sizeof(RegionObject));
				readSize += h.size;
				break;
			case 'RDMP':
				dataEntries[currentEntry]->mapName = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'RDGS':
				dataEntries[currentEntry]->grassCount = h.size / sizeof(RegionGrass);
				dataEntries[currentEntry]->grasses = f->readarray<RegionGrass>(h.size / sizeof(RegionGrass));
				readSize += h.size;
				break;
			case 'RDMD':
				dataEntries[currentEntry]->hasMusicType = true;
				dataEntries[currentEntry]->musicType = f->read<ulong>();
				readSize += 4;
				break;
			case 'RDMO':
				dataEntries[currentEntry]->music = f->read<formid>();
				readSize += 4;
				break;
			case 'RDSI':
				dataEntries[currentEntry]->mediaSet = f->read<formid>();
				dataEntries[currentEntry]->hasMediaSet = true;
				readSize += 4;
				break;
			case 'RDSB':
				dataEntries[currentEntry]->battleMediaSets.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'RDSD':
				dataEntries[currentEntry]->soundCount = h.size / sizeof(RegionSound);
				dataEntries[currentEntry]->sounds = f->readarray<RegionSound>(h.size / sizeof(RegionSound));
				readSize += h.size;
				break;
			case 'RDWT':
				dataEntries[currentEntry]->weatherCount = h.size / sizeof(RegionWeather);
				dataEntries[currentEntry]->weatherTypes = f->readarray<RegionWeather>(h.size / sizeof(RegionWeather));
				readSize += h.size;
				break;
			case 'RDID':
				dataEntries[currentEntry]->imposterCount = h.size / 4;
				dataEntries[currentEntry]->imposters = f->readarray<formid>(h.size / 4);
				readSize += h.size;
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
		WriteZStringSubrecord('EDID',editorID,f);
		WriteZStringSubrecord('ICON',icon,f);
		WriteSubrecord('RCLR',4,f);
		f->write<ulong>(mapColor);
		if (worldspace)
		{
			WriteSubrecord('WNAM',4,f);
			f->write<formid>(worldspace);
		}
		for (int i = 0;i < areas.Count();i++)
		{
			WriteSubrecord('RPLI',4,f);
			f->write<ulong>(areas[i]->edgeFallOff);
			WriteSubrecord('RPLD',areas[i]->pointCount * 8,f);
			f->writearray<NiPoint2>(areas[i]->pointCount,areas[i]->points);
		}
		for (int i = 0;i < dataEntries.Count();i++)
		{
			WriteSubrecord('RDAT',sizeof(RegionData),f);
			f->write<RegionData>(dataEntries[i]->data);
			switch (dataEntries[i]->data.type)
			{
			case 2:
				WriteSubrecord('RDOT',dataEntries[i]->objectCount * sizeof(RegionObject),f);
				f->writearray<RegionObject>(dataEntries[i]->objectCount,dataEntries[i]->objects);
				break;
			case 3:
				if (dataEntries[i]->weatherCount)
				{
					WriteSubrecord('RDWT',dataEntries[i]->weatherCount * sizeof(RegionWeather),f);
					f->writearray<RegionWeather>(dataEntries[i]->weatherCount,dataEntries[i]->weatherTypes);
				}
				break;
			case 4:
				WriteZStringSubrecord('RDMP',dataEntries[i]->mapName,f);
				break;
			case 5:
				WriteZStringSubrecord('ICON',dataEntries[i]->icon,f);
				break;
			case 6:
				if (dataEntries[i]->grassCount)
				{
					WriteSubrecord('RDGS',dataEntries[i]->grassCount * sizeof(RegionGrass),f);
					f->writearray<RegionGrass>(dataEntries[i]->grassCount,dataEntries[i]->grasses);
				}
				break;
			case 7:
				if (dataEntries[i]->hasMusicType)
				{
					WriteSubrecord('RDMD',4,f);
					f->write<ulong>(dataEntries[i]->musicType);
				}
				if (dataEntries[i]->music)
				{
					WriteSubrecord('RDMO',4,f);
					f->write<formid>(dataEntries[i]->music);
				}
				if (dataEntries[i]->hasMediaSet)
				{
					WriteSubrecord('RDSI',4,f);
					f->write<formid>(dataEntries[i]->mediaSet);
				}
				for (int j = 0;j < dataEntries[i]->battleMediaSets.Count();j++)
				{
					WriteSubrecord('RDSB',4,f);
					f->write<formid>(dataEntries[i]->battleMediaSets[j]);
				}
				if (dataEntries[i]->soundCount)
				{
					WriteSubrecord('RDSD',dataEntries[i]->soundCount * sizeof(RegionSound),f);
					f->writearray<RegionSound>(dataEntries[i]->soundCount,dataEntries[i]->sounds);
				}
				break;
			case 8:
				if (dataEntries[i]->imposterCount)
				{
					WriteSubrecord('RDID',dataEntries[i]->imposterCount * 4,f);
					f->writearray<formid>(dataEntries[i]->imposterCount,dataEntries[i]->imposters);
				}
				break;
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(icon);
		size += ComputeSubrecordSize(4);
		if (worldspace)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < areas.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			size += ComputeSubrecordSize(areas[i]->pointCount * 8);
		}
		for (int i = 0;i < dataEntries.Count();i++)
		{
			size += ComputeSubrecordSize(8);
			switch (dataEntries[i]->data.type)
			{
			case 2:
				size += ComputeSubrecordSize(dataEntries[i]->objectCount * sizeof(RegionObject));
				break;
			case 3:
				if (dataEntries[i]->weatherCount)
				{
					size += ComputeSubrecordSize(dataEntries[i]->weatherCount * sizeof(RegionWeather));
				}
				break;
			case 4:
				size += ZStringSubrecordSize(dataEntries[i]->mapName);
				break;
			case 5:
				size += ZStringSubrecordSize(dataEntries[i]->icon);
				break;
			case 6:
				if (dataEntries[i]->grassCount)
				{
					size += ComputeSubrecordSize(dataEntries[i]->grassCount * sizeof(RegionGrass));
				}
				break;
			case 7:
				if (dataEntries[i]->hasMusicType)
				{
					size += ComputeSubrecordSize(4);
				}
				if (dataEntries[i]->music)
				{
					size += ComputeSubrecordSize(4);
				}
				if (dataEntries[i]->hasMediaSet)
				{
					size += ComputeSubrecordSize(4);
				}
				for (int j = 0;j < dataEntries[i]->battleMediaSets.Count();j++)
				{
					size += ComputeSubrecordSize(4);
				}
				if (dataEntries[i]->soundCount)
				{
					size += ComputeSubrecordSize(dataEntries[i]->soundCount * sizeof(RegionSound));
				}
				break;
			case 8:
				if (dataEntries[i]->imposterCount)
				{
					size += ComputeSubrecordSize(dataEntries[i]->imposterCount * 4);
				}
				break;
			}
		}
		return size;
	}
};
