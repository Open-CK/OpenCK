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
class GameSettingForm : public Form
{
protected:
	char *editorID;
	char *st;
	long in;
	float fl;
public:
	GameSettingForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0)
	{
	}
	virtual ~GameSettingForm()
	{
		if (editorID)
		{
			delete[] editorID;
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
			case 'EDID':
				editorID = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DATA':
				if (editorID[0] == 's')
				{
					st = f->readzstring(h.size);
					readSize += h.size;
				}
				else if (editorID[0] == 'i')
				{
					in = f->read<long>();
					readSize += 4;
				}
				else if (editorID[0] == 'f')
				{
					fl = f->read<float>();
					readSize += 4;
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
		WriteZStringSubrecord('EDID',editorID,f);
		if (editorID[0] == 's')
		{
			WriteZStringSubrecord('DATA',st,f);
		}
		else if (editorID[0] == 'i')
		{
			WriteSubrecord('DATA',4,f);
			f->write<long>(in);
		}
		else if (editorID[0] == 'f')
		{
			WriteSubrecord('DATA',4,f);
			f->write<float>(fl);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		if (editorID[0] == 's')
		{
			size += ZStringSubrecordSize(st);
		}
		else if (editorID[0] == 'i')
		{
			size += ComputeSubrecordSize(4);
		}
		else if (editorID[0] == 'f')
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
