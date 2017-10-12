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
class TES4Form : public Form
{
protected:
	float version;
	ulong formCount;
	ulong nextFormId;
	char *author;
	char *description;
	SimpleDynVecClass<char *> masters;
	SimpleDynVecClass<uint64> sizes;
	SimpleDynVecClass<bool> sizesPresent;
	ulong formOverrideCount;
	formid *formOverrides;
	long formOverridePos;
public:
	TES4Form(FormHeader h,ModFile *f) : Form(h,f), version(0), formCount(0), nextFormId(0), author(0), description(0), masters(0), sizes(0), formOverrideCount(0), formOverrides(0), formOverridePos(0)
	{
	}
	virtual ~TES4Form()
	{
		if (author)
		{
			delete[] author;
		}
		if (description)
		{
			delete[] description;
		}
		for (int i = 0;i < masters.Count();i++)
		{
			delete[] masters[i];
		}
		masters.Delete_All();
		sizes.Delete_All();
		if (formOverrides)
		{
			delete[] formOverrides;
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentMaster = -1;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			case 'HEDR':
				version = f->read<float>();
				formCount = f->read<ulong>();
				nextFormId = f->read<ulong>();
				readSize += 12;
				break;
			case 'CNAM':
				author = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SNAM':
				description = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MAST':
				currentMaster++;
				masters.Add(f->readzstring(h.size));
				sizes.Add(0);
				sizesPresent.Add(false);
				readSize += h.size;
				break;
			case 'DATA':
				sizes[currentMaster] = f->read<uint64>();
				sizesPresent[currentMaster] = true;
				readSize += 8;
				break;
			case 'ONAM':
				formOverridePos = currentMaster;
				formOverrideCount = h.size / sizeof(formid);
				formOverrides = f->readarray<formid>(h.size / sizeof(formid));
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
		WriteSubrecord('HEDR',12,f);
		f->write<float>(version);
		f->write<ulong>(formCount);
		f->write<ulong>(nextFormId);
		WriteZStringSubrecord('CNAM',author,f);
		WriteZStringSubrecord('SNAM',description,f);
		for (int i = 0;i < masters.Count();i++)
		{
			WriteZStringSubrecord('MAST',masters[i],f);
			if (sizesPresent[i])
			{
				WriteSubrecord('DATA',8,f);
				f->write<uint64>(sizes[i]);
			}
			if (i == formOverridePos)
			{
				if (formOverrides)
				{
					WriteSubrecord('ONAM',formOverrideCount * sizeof(formid),f);
					f->writearray<formid>(formOverrideCount,formOverrides);
				}
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ComputeSubrecordSize(12);
		size += ZStringSubrecordSize(author);
		size += ZStringSubrecordSize(description);
		for (int i = 0;i < masters.Count();i++)
		{
			size += ZStringSubrecordSize(masters[i]);
			if (sizesPresent[i])
			{
				size += ComputeSubrecordSize(8);
			}
		}
		if (formOverrides)
		{
			size += ComputeSubrecordSize(formOverrideCount * sizeof(formid));
		}
		return size;
	}
	friend class ModFile;
};
