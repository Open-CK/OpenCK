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
class NavMeshInfoMapForm : public Form
{
public:
	ulong version;
	SimpleDynVecClass<ubyte *> navMapInfo;
	SimpleDynVecClass<ulong> navMapInfoSize;
	SimpleDynVecClass<ubyte *> navConnectionInfo;
	SimpleDynVecClass<ulong> navConnectionInfoSize;
	NavMeshInfoMapForm(FormHeader h,ModFile *f) : Form(h,f)
	{
	}
	virtual ~NavMeshInfoMapForm()
	{
		for (int i = 0;i < navMapInfo.Count();i++)
		{
			delete[] navMapInfo[i];
		}
		for (int i = 0;i < navConnectionInfo.Count();i++)
		{
			delete[] navConnectionInfo[i];
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
			case 'NVER':
				version = f->read<ulong>();
				readSize += 4;
				break;
			case 'NVMI':
				navMapInfoSize.Add(h.size);
				navMapInfo.Add(f->readarray<ubyte>(h.size));
				readSize += h.size;
				break;
			case 'NVCI':
				navConnectionInfoSize.Add(h.size);
				navConnectionInfo.Add(f->readarray<ubyte>(h.size));
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
		WriteSubrecord('NVER',4,f);
		f->write<ulong>(version);
		for (int i = 0;i < navMapInfo.Count();i++)
		{
			WriteSubrecord('NVMI',navMapInfoSize[i],f);
			f->writearray<ubyte>(navMapInfoSize[i],navMapInfo[i]);
		}
		for (int i = 0;i < navConnectionInfo.Count();i++)
		{
			WriteSubrecord('NVCI',navConnectionInfoSize[i],f);
			f->writearray<ubyte>(navConnectionInfoSize[i],navConnectionInfo[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		size += ComputeSubrecordSize(4);
		for (int i = 0;i < navMapInfo.Count();i++)
		{
			size += ComputeSubrecordSize(navMapInfoSize[i]);
		}
		for (int i = 0;i < navConnectionInfo.Count();i++)
		{
			size += ComputeSubrecordSize(navConnectionInfoSize[i]);
		}
		return size;
	}
};
