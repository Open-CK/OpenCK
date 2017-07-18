/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "extradataform.h"
struct CellLighting
{
	ulong ambient;
	ulong directional;
	ulong fog;
	float fogNear;
	float fogFar;
	long rotXY;
	long rotZ;
	float directionalFade;
	float fogClipDistance;
	float fogPower;
};
struct CellLightingSmall
{
	ulong ambient;
	ulong directional;
	ulong fog;
	float fogNear;
	float fogFar;
	long rotXY;
	long rotZ;
	float directionalFade;
	float fogClipDistance;
};
struct CellCoordinates
{
	long x;
	long y;
	ubyte flags;
};
struct CellCoordinatesSmall
{
	long x;
	long y;
};
class CellForm : public ExtraDataForm, public FullName
{
protected:
	ubyte flags;
	CellLighting lighting;
	CellLightingSmall smallLighting;
	bool hasSmallLighting;
	CellCoordinates coordinates;
	CellCoordinatesSmall smallCoordinates;
	bool hasSmallCoordinates;
	SimpleDynVecClass<ImpactSwap> impactSwap;
	char *footstepMaterials;
	formid lightingTemplate;
	ulong lightingTemplateFlags;
	float waterHeight;
	char *waterNoiseTexture;
	bool lightingTemplateFound;
	bool lightingTemplateFlagsFound;
	bool hasWaterHeight;
public:
	CellForm(FormHeader h,ModFile *f) : ExtraDataForm(h,f), waterNoiseTexture(0), footstepMaterials(0), hasSmallLighting(false), hasSmallCoordinates(false), lightingTemplateFound(false), lightingTemplateFlagsFound(false), hasWaterHeight(false)
	{
	}
	virtual ~CellForm()
	{
		if (waterNoiseTexture)
		{
			delete[] waterNoiseTexture;
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
			case 'DATA':
				flags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'XCLL':
				if (h.size == sizeof(CellLighting))
				{
					lighting = f->read<CellLighting>();
					readSize += sizeof(CellLighting);
				}
				else
				{
					hasSmallLighting = true;
					smallLighting = f->read<CellLightingSmall>();
					readSize += sizeof(CellLightingSmall);
				}
				break;
			case 'XCLC':
				if (h.size == sizeof(CellCoordinates))
				{
					coordinates = f->read<CellCoordinates>();
					readSize += sizeof(CellCoordinates);
				}
				else
				{
					hasSmallCoordinates = true;
					smallCoordinates = f->read<CellCoordinatesSmall>();
					readSize += sizeof(CellCoordinatesSmall);
				}
				break;
			case 'IMPS':
				impactSwap.Add(f->read<ImpactSwap>());
				readSize += sizeof(ImpactSwap);
				break;
			case 'IMPF':
				footstepMaterials = f->readarray<char>(0x12C);
				readSize += 0x12C;
				break;
			case 'LTMP':
				lightingTemplateFound = true;
				lightingTemplate = f->read<formid>();
				readSize += 4;
				break;
			case 'LNAM':
				lightingTemplateFlagsFound = true;
				lightingTemplateFlags = f->read<ulong>();
				readSize += 4;
				break;
			case 'XCLW':
				hasWaterHeight = true;
				waterHeight = f->read<float>();
				readSize += 4;
				break;
			case 'XNAM':
				waterNoiseTexture = f->readzstring(h.size);
				readSize += h.size;
				break;
			default:
				LoadExtraData(f,h);
				break;
			}
		}
	}
	virtual void Save(FileWrite *f)
	{
		FormSave();
		FullNameSave();
		WriteSubrecord('DATA',1,f);
		f->write<ubyte>(flags);
		if (flags & 1)
		{
			if (hasSmallLighting)
			{
				WriteSubrecord('XCLL',sizeof(CellLightingSmall),f);
				f->write<CellLightingSmall>(smallLighting);
			}
			else
			{
				WriteSubrecord('XCLL',sizeof(CellLighting),f);
				f->write<CellLighting>(lighting);
			}
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
		}
		else
		{
			if (hasSmallCoordinates)
			{
				WriteSubrecord('XCLC',sizeof(CellCoordinatesSmall),f);
				f->write<CellCoordinatesSmall>(smallCoordinates);
			}
			else
			{
				WriteSubrecord('XCLC',sizeof(CellCoordinates),f);
				f->write<CellCoordinates>(coordinates);
			}
		}
		if (lightingTemplateFound)
		{
			WriteSubrecord('LTMP',4,f);
			f->write<formid>(lightingTemplate);
		}
		if (lightingTemplateFlagsFound)
		{
			WriteSubrecord('LNAM',4,f);
			f->write<ulong>(lightingTemplateFlags);
		}
		if (hasWaterHeight)
		{
			WriteSubrecord('XCLW',4,f);
			f->write<float>(waterHeight);
		}
		WriteZStringSubrecord('XNAM',waterNoiseTexture,f);
		SaveExtraData(f);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		size += ComputeSubrecordSize(1);
		if (flags & 1)
		{
			if (hasSmallLighting)
			{
				size += ComputeSubrecordSize(sizeof(CellLightingSmall));
			}
			else
			{
				size += ComputeSubrecordSize(sizeof(CellLighting));
			}
			for (int i = 0;i < impactSwap.Count();i++)
			{
				size += ComputeSubrecordSize(sizeof(ImpactSwap));
			}
			if (footstepMaterials)
			{
				size += ComputeSubrecordSize(0x12C);
			}
		}
		else
		{
			if (hasSmallCoordinates)
			{
				size += ComputeSubrecordSize(sizeof(CellCoordinatesSmall));
			}
			else
			{
				size += ComputeSubrecordSize(sizeof(CellCoordinates));
			}
		}
		if (lightingTemplateFound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (lightingTemplateFlagsFound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (hasWaterHeight)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ZStringSubrecordSize(waterNoiseTexture);
		size += GetExtraDataSaveSize();
		return size;
	}
};
