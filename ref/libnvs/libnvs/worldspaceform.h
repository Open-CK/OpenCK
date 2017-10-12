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
struct MapData
{
	long xSize;
	long ySize;
	short nwCellX;
	short nwCellY;
	short seCellX;
	short seCellY;
};
struct LandData
{
	float defaultLandHeight;
	float defaultWaterHeight;
};
struct MapOffsetData
{
	float mapScale;
	float cellXOffset;
	float cellYOffset;
};
class WorldspaceForm : public Form, public FullName, public Texture
{
protected:
	formid encounterZone;
	formid parent;
	ushort parentFlags;
	bool hasLandData;
	bool hasLodData;
	bool hasMapData;
	bool hasWaterData;
	bool hasClimateData;
	bool hasImageSpaceData;
	formid climate;
	formid water;
	formid lodWater;
	float lodWaterHeight;
	LandData landData;
	MapData mapData;
	MapOffsetData mapOffsetData;
	formid imageSpace;
	ubyte flags;
	NiPoint2 minBounds;
	NiPoint2 maxBounds;
	formid musicType;
	Texture canopyShadowTexture;
	Texture waterNoiseTexture;
	SimpleDynVecClass<ImpactSwap> impactSwap;
	char *footstepMaterials;
	ulong *offset;
	ulong offsetCount;
public:
	WorldspaceForm(FormHeader h,ModFile *f) : Form(h,f), encounterZone(0), parent(0), climate(0), water(0), lodWater(0), imageSpace(0), musicType(0), footstepMaterials(0), hasLandData(false), hasLodData(false), hasMapData(false), hasWaterData(false), hasClimateData(false), hasImageSpaceData(false), offset(0), offsetCount(0)
	{
	}
	virtual ~WorldspaceForm()
	{
		if (offset)
		{
			delete[] offset;
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
			case 'XEZN':
				encounterZone = f->read<formid>();
				readSize += 4;
				break;
			case 'WNAM':
				parent = f->read<formid>();
				readSize += 4;
				break;
			case 'PNAM':
				parentFlags = f->read<ushort>();
				readSize += 2;
				break;
			case 'CNAM':
				hasClimateData = true;
				climate = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM2':
				hasWaterData = true;
				water = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM3':
				hasLodData = true;
				lodWater = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM4':
				lodWaterHeight = f->read<float>();
				readSize += 4;
				break;
			case 'DNAM':
				hasLandData = true;
				landData = f->read<LandData>();
				readSize += sizeof(LandData);
				break;
			TextureLoad(this,'ICON');
			case 'MNAM':
				hasMapData = true;
				mapData = f->read<MapData>();
				readSize += sizeof(MapData);
				break;
			case 'ONAM':
				mapOffsetData = f->read<MapOffsetData>();
				readSize += sizeof(MapOffsetData);
				break;
			case 'INAM':
				hasImageSpaceData = true;
				imageSpace = f->read<formid>();
				readSize += 4;
				break;
			case 'DATA':
				flags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'NAM0':
				minBounds = f->read<NiPoint2>();
				readSize += sizeof(NiPoint2);
				break;
			case 'NAM9':
				maxBounds = f->read<NiPoint2>();
				readSize += sizeof(NiPoint2);
				break;
			case 'ZNAM':
				musicType = f->read<formid>();
				readSize += 4;
				break;
			TextureLoad((&canopyShadowTexture),'NNAM');
			TextureLoad((&waterNoiseTexture),'XNAM');
			case 'IMPS':
				impactSwap.Add(f->read<ImpactSwap>());
				readSize += sizeof(ImpactSwap);
				break;
			case 'IMPF':
				footstepMaterials = f->readarray<char>(0x12C);
				readSize += 0x12C;
				break;
			case 'OFST':
				offsetCount = h.size / 4;
				offset = f->readarray<ulong>(offsetCount);
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
		FormSave();
		if (header.flags & 1)
		{
			WriteSubrecord('NAM0',sizeof(NiPoint2),f);
			f->write<NiPoint2>(minBounds);
			WriteSubrecord('NAM9',sizeof(NiPoint2),f);
			f->write<NiPoint2>(maxBounds);
			return;
		}
		FullNameSave();
		if (encounterZone)
		{
			WriteSubrecord('XEZN',4,f);
			f->write<formid>(encounterZone);
		}
		if (parent)
		{
			WriteSubrecord('WNAM',4,f);
			f->write<formid>(parent);
			WriteSubrecord('PNAM',2,f);
			f->write<ushort>(parentFlags);
		}
		if (hasClimateData)
		{
			WriteSubrecord('CNAM',4,f);
			f->write<formid>(climate);
		}
		if (hasWaterData)
		{
			WriteSubrecord('NAM2',4,f);
			f->write<formid>(water);
		}
		if (hasLodData)
		{
			WriteSubrecord('NAM3',4,f);
			f->write<formid>(lodWater);
			WriteSubrecord('NAM4',4,f);
			f->write<float>(lodWaterHeight);
		}
		if (hasLandData)
		{
			WriteSubrecord('DNAM',sizeof(LandData),f);
			f->write<LandData>(landData);
		}
		if (hasMapData)
		{
			TextureSave(this,'ICON');
			WriteSubrecord('MNAM',sizeof(MapData),f);
			f->write<MapData>(mapData);
		}
		WriteSubrecord('ONAM',sizeof(MapOffsetData),f);
		f->write<MapOffsetData>(mapOffsetData);
		if (hasImageSpaceData)
		{
			WriteSubrecord('INAM',4,f);
			f->write<formid>(imageSpace);
		}
		WriteSubrecord('DATA',1,f);
		f->write<ubyte>(flags);
		WriteSubrecord('NAM0',sizeof(NiPoint2),f);
		f->write<NiPoint2>(minBounds);
		WriteSubrecord('NAM9',sizeof(NiPoint2),f);
		f->write<NiPoint2>(maxBounds);
		if (musicType)
		{
			WriteSubrecord('ZNAM',4,f);
			f->write<formid>(musicType);
		}
		TextureSave((&canopyShadowTexture),'NNAM');
		TextureSave((&waterNoiseTexture),'XNAM');
		for (int i = 0;i < impactSwap.Count();i++)
		{
			WriteSubrecord('IMPS',sizeof(ImpactSwap),f);
			f->write<ImpactSwap>(impactSwap[i]);
		}
		if (footstepMaterials)
		{
			WriteSubrecord('IMPF',0x12C,f);
			f->writearray<char>(0x12C,footstepMaterials);
		}
		if (offset)
		{
			WriteSubrecord('OFST',offsetCount * 4,f);
			f->writearray<ulong>(offsetCount,offset);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		if (header.flags & 1)
		{
			size += ComputeSubrecordSize(sizeof(NiPoint2));
			size += ComputeSubrecordSize(sizeof(NiPoint2));
			return size;
		}
		FullNameGetSaveSize();
		if (encounterZone)
		{
			size += ComputeSubrecordSize(4);
		}
		if (parent)
		{
			size += ComputeSubrecordSize(4);
			size += ComputeSubrecordSize(2);
		}
		if (hasClimateData)
		{
			size += ComputeSubrecordSize(4);
		}
		if (hasWaterData)
		{
			size += ComputeSubrecordSize(4);
		}
		if (hasLodData)
		{
			size += ComputeSubrecordSize(4);
			size += ComputeSubrecordSize(4);
		}
		if (hasLandData)
		{
			size += ComputeSubrecordSize(sizeof(LandData));
		}
		if (hasMapData)
		{
			TextureGetSaveSize(this);
			size += ComputeSubrecordSize(sizeof(MapData));
		}
		size += ComputeSubrecordSize(sizeof(MapOffsetData));
		if (hasImageSpaceData)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(1);
		size += ComputeSubrecordSize(sizeof(NiPoint2));
		size += ComputeSubrecordSize(sizeof(NiPoint2));
		if (musicType)
		{
			size += ComputeSubrecordSize(4);
		}
		TextureGetSaveSize((&canopyShadowTexture));
		TextureGetSaveSize((&waterNoiseTexture));
		for (int i = 0;i < impactSwap.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(ImpactSwap));
		}
		if (footstepMaterials)
		{
			size += ComputeSubrecordSize(0x12C);
		}
		if (offset)
		{
			size += ComputeSubrecordSize(offsetCount * 4);
		}
		return size;
	}
};
