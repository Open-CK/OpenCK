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
class CaravanDeckForm : public Form, public FullName
{
protected:
	SimpleDynVecClass<formid> cards;
	ulong count;
public:
	CaravanDeckForm(FormHeader h,ModFile *f) : Form(h,f)
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
			FullNameLoad();
			case 'CARD':
				cards.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'DATA':
				count = f->read<ulong>();
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
		FullNameSave();
		for (int i = 0;i < cards.Count();i++)
		{
			WriteSubrecord('CARD',4,f);
			f->write<formid>(cards[i]);
		}
		WriteSubrecord('DATA',4,f);
		f->write<ulong>(count);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		for (int i = 0;i < cards.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(4);
		return size;
	}
};
