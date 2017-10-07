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
struct CameraPathData
{
	formid parent;
	formid previousSibling;
};
class CameraPathForm : public Form, public Model
{
protected:
	SimpleDynVecClass<Condition> conditions;
	CameraPathData data;
	ubyte zoom;
	SimpleDynVecClass<formid> cameraShots;
public:
	CameraPathForm(FormHeader h,ModFile *f) : Form(h,f)
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
			ModelBRLoad(this,'MODL','MODB','MODT');
			case 'CTDA':
				conditions.Add(f->read<Condition>());
				readSize += sizeof(Condition);
				break;
			case 'ANAM':
				data = f->read<CameraPathData>();
				readSize += sizeof(CameraPathData);
				break;
			case 'DATA':
				zoom = f->read<ubyte>();
				readSize += 1;
				break;
			case 'SNAM':
				cameraShots.Add(f->read<formid>());
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
		FormSave();
		ModelBRSave(this,'MODL','MODB','MODT');
		for (int i = 0;i < conditions.Count();i++)
		{
			WriteSubrecord('CTDA',sizeof(Condition),f);
			f->write<Condition>(conditions[i]);
		}
		WriteSubrecord('ANAM',sizeof(CameraPathData),f);
		f->write<CameraPathData>(data);
		WriteSubrecord('DATA',1,f);
		f->write<ubyte>(zoom);
		for (int i = 0;i < cameraShots.Count();i++)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(cameraShots[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		ModelBRGetSaveSize(this);
		for (int i = 0;i < conditions.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(Condition));
		}
		size += ComputeSubrecordSize(sizeof(CameraPathData));
		size += ComputeSubrecordSize(1);
		for (int i = 0;i < cameraShots.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
