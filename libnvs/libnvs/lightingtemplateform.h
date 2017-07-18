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
struct LightingTemplateData
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
class LightingTemplateForm : public Form
{
protected:
	LightingTemplateData data;
public:
	LightingTemplateForm(FormHeader h,ModFile *f) : Form(h,f)
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
				data = f->read<LightingTemplateData>();
				readSize += sizeof(LightingTemplateData);
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
		WriteSubrecord('DATA',sizeof(LightingTemplateData),f);
		f->write<LightingTemplateData>(data);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		size += ComputeSubrecordSize(sizeof(LightingTemplateData));
		return size;
	}
};
