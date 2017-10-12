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
struct ImpactDataSetData
{
	formid stone;
	formid dirt;
	formid grass;
	formid glass;
	formid metal;
	formid wood;
	formid organic;
	formid cloth;
	formid water;
	formid hollowMetal;
	formid organicBug;
	formid organicGlow;
};
struct ImpactDataSetData2
{
	formid stone;
	formid dirt;
	formid grass;
	formid glass;
	formid metal;
	formid wood;
	formid organic;
	formid cloth;
	formid water;
	formid hollowMetal;
};
struct ImpactDataSetData3
{
	formid stone;
	formid dirt;
	formid grass;
	formid glass;
	formid metal;
	formid wood;
	formid organic;
	formid cloth;
	formid water;
};
class ImpactDataSetForm : public Form
{
protected:
	ImpactDataSetData data;
	ImpactDataSetData2 data2;
	ImpactDataSetData3 data3;
	bool hasImpactDataSetData2;
	bool hasImpactDataSetData3;
public:
	ImpactDataSetForm(FormHeader h,ModFile *f) : Form(h,f), hasImpactDataSetData2(false), hasImpactDataSetData3(false)
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
			FormLoad();
			case 'DATA':
				if (h.size == sizeof(ImpactDataSetData))
				{
					data = f->read<ImpactDataSetData>();
					readSize += sizeof(ImpactDataSetData);
				}
				else if (h.size == sizeof(ImpactDataSetData2))
				{
					hasImpactDataSetData2 = true;
					data2 = f->read<ImpactDataSetData2>();
					readSize += sizeof(ImpactDataSetData2);
				}
				else if (h.size == sizeof(ImpactDataSetData3))
				{
					hasImpactDataSetData3 = true;
					data3 = f->read<ImpactDataSetData3>();
					readSize += sizeof(ImpactDataSetData3);
				}
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
		if (hasImpactDataSetData2)
		{
			WriteSubrecord('DATA',sizeof(ImpactDataSetData2),f);
			f->write<ImpactDataSetData2>(data2);
		}
		else if (hasImpactDataSetData3)
		{
			WriteSubrecord('DATA',sizeof(ImpactDataSetData3),f);
			f->write<ImpactDataSetData3>(data3);
		}
		else
		{
			WriteSubrecord('DATA',sizeof(ImpactDataSetData),f);
			f->write<ImpactDataSetData>(data);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		if (hasImpactDataSetData2)
		{
			size += ComputeSubrecordSize(sizeof(ImpactDataSetData2));
		}
		else if (hasImpactDataSetData3)
		{
			size += ComputeSubrecordSize(sizeof(ImpactDataSetData3));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(ImpactDataSetData));
		}
		return size;
	}
};
