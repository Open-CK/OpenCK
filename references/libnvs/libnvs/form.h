/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "nvsfile.h"
#include "modfile.h"
#include "formcomponents.h"
struct SubrecordHeader
{
	ulong type;
	ulong size;
};
#define FormLoad() \
			case 'EDID': \
				editorID = f->readzstring(h.size); \
				readSize += h.size; \
				break;
#define FormSave() \
		WriteZStringSubrecord('EDID',editorID,f);
#define FormGetSaveSize() \
		size += ZStringSubrecordSize(editorID);
class Form
{
protected:
	FormHeader header;
	ulong readSize;
	ModFile *file;
	ulong uncompsize;
	char *editorID;
	bool deleted;
public:
	Form(FormHeader h,ModFile *f) : header(h), file(f), readSize(0), uncompsize(h.dataSize), editorID(0), deleted(0)
	{
		AddForm(this);
	}
	virtual ~Form()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		RemoveForm(this);
	}
	void LoadCompressed(FileRead *f);
	void SaveCompressed(FileWrite *f);
	FormHeader Get_Header()
	{
		return header;
	}
	formid RemapFormID(formid id)
	{
		if (!id)
		{
			return 0;
		}
		if (file)
		{
			return id |= (file->GetLoadID((ubyte)(id >> 24)) << 24);
		}
		else
		{
			return id;
		}
	}
protected:
	virtual void Load(FileRead *f) = 0;
	virtual void Save(FileWrite *f) = 0;
	virtual int GetSaveSize() = 0;
	public:
	SubrecordHeader ReadSubrecord(FileRead *f)
	{
		SubrecordHeader h;
		h.type = SwapBytes(f->read<ulong>());
		readSize += 4;
		h.size = f->read<ushort>();
		readSize += 2;
		if (h.type == 'XXXX')
		{
			h.size = f->read<ulong>();
			readSize += 4;
			h.type = SwapBytes(f->read<ulong>());
			readSize += 4;
			f->read<ushort>();
			readSize += 2;
		}
		return h;
	}
	void AddReadSize(int size)
	{
		readSize += size;
	}
	void WriteSubrecord(ulong type, ulong size, FileWrite *f)
	{
		if (size > 0xFFFF)
		{
			WriteSubrecord('XXXX',4,f);
			f->write<ulong>(size);
			size = 0;
		}
		f->write<ulong>(SwapBytes(type));
		f->write<ushort>((ushort)size);
	}
	int ComputeSubrecordSize(ulong size)
	{
		int sz = 6;
		if (size > 0xFFFF)
		{
			sz += 6;
			sz += 4;
		}
		sz += size;
		return sz;
	}
	void WriteZStringSubrecord(ulong type,char *string,FileWrite *f, bool special = false)
	{
		if (string)
		{
			ulong size = strlen(string) + 1;
			if (size == 1 && special)
			{
				WriteSubrecord(type,4,f);
				f->writezstring(1,string);
				f->writezstring(1,string);
				f->writezstring(1,string);
				f->writezstring(1,string);
			}
			else
			{
				WriteSubrecord(type,size,f);
				f->writezstring(size,string);
			}
		}
	}
	int ZStringSubrecordSize(char *string, bool special = false)
	{
		if (string)
		{
			ulong size = strlen(string) + 1;
			if (size == 1 && special)
			{
				return ComputeSubrecordSize(4);
			}
			else
			{
				return ComputeSubrecordSize(size);
			}
		}
		return 0;
	}
	void WriteZStringSubrecord2(ulong type,char *string,int count,FileWrite *f, bool special = false)
	{
		if (string)
		{
			ulong size = count;
			if (size == 1 && special)
			{
				WriteSubrecord(type,4,f);
				f->writezstring(1,string);
				f->writezstring(1,string);
				f->writezstring(1,string);
				f->writezstring(1,string);
			}
			else
			{
				WriteSubrecord(type,size,f);
				f->writezstring(size,string);
			}
		}
	}
	int ZStringSubrecordSize2(char *string,int count,bool special = false)
	{
		if (string)
		{
			ulong size = count;
			if (size == 1 && special)
			{
				return ComputeSubrecordSize(4);
			}
			else
			{
				return ComputeSubrecordSize(size);
			}
		}
		return 0;
	}
	friend class NVSFile;
};
Form *CreateForm(FormHeader header,ModFile *f);
