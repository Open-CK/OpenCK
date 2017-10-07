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
struct MenuButton
{
	char *buttonText;
	SimpleDynVecClass<Condition> conditions;
};
class MessageForm : public Form, public Description, public FullName
{
protected:
	formid icon;
	ulong flags;
	bool hasFlags;
	ulong time;
	SimpleDynVecClass<MenuButton> buttons;
	ubyte nam0;
	ubyte nam1;
	ubyte nam2;
	ubyte nam3;
	ubyte nam4;
	ubyte nam5;
	ubyte nam6;
	ubyte nam7;
	ubyte nam8;
	ubyte nam9;
	bool hasnam;
public:
	MessageForm(FormHeader h,ModFile *f) : Form(h,f), hasnam(false), hasFlags(false)
	{
	}
	virtual ~MessageForm()
	{
		for (int i = 0;i < buttons.Count();i++)
		{
			delete[] buttons[i].buttonText;
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentMenuItem = -1;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			DescriptionLoad();
			FullNameLoad();
			case 'INAM':
				icon = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM0':
				hasnam = true;
				nam0 = f->read<ubyte>();
				readSize += 1;
				break;
			case 'NAM1':
				hasnam = true;
				nam1 = f->read<ubyte>();
				readSize += 1;
				break;
			case 'NAM2':
				hasnam = true;
				nam2 = f->read<ubyte>();
				readSize += 1;
				break;
			case 'NAM3':
				hasnam = true;
				nam3 = f->read<ubyte>();
				readSize += 1;
				break;
			case 'NAM4':
				hasnam = true;
				nam4 = f->read<ubyte>();
				readSize += 1;
				break;
			case 'NAM5':
				hasnam = true;
				nam5 = f->read<ubyte>();
				readSize += 1;
				break;
			case 'NAM6':
				hasnam = true;
				nam6 = f->read<ubyte>();
				readSize += 1;
				break;
			case 'NAM7':
				hasnam = true;
				nam7 = f->read<ubyte>();
				readSize += 1;
				break;
			case 'NAM8':
				hasnam = true;
				nam8 = f->read<ubyte>();
				readSize += 1;
				break;
			case 'NAM9':
				hasnam = true;
				nam9 = f->read<ubyte>();
				readSize += 1;
				break;
			case 'DNAM':
				hasFlags = true;
				flags = f->read<ulong>();
				readSize += 4;
				break;
			case 'TNAM':
				time = f->read<ulong>();
				readSize += 4;
				break;
			case 'ITXT':
				currentMenuItem++;
				buttons.Add(MenuButton());
				buttons[currentMenuItem].buttonText = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'CTDA':
				buttons[currentMenuItem].conditions.Add(f->read<Condition>());
				readSize += sizeof(Condition);
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
		DescriptionSave();
		FullNameSave();
		WriteSubrecord('INAM',4,f);
		f->write<formid>(icon);
		if (hasnam)
		{
			WriteSubrecord('NAM0',1,f);
			f->write<ubyte>(nam0);
			WriteSubrecord('NAM1',1,f);
			f->write<ubyte>(nam1);
			WriteSubrecord('NAM2',1,f);
			f->write<ubyte>(nam2);
			WriteSubrecord('NAM3',1,f);
			f->write<ubyte>(nam3);
			WriteSubrecord('NAM4',1,f);
			f->write<ubyte>(nam4);
			WriteSubrecord('NAM5',1,f);
			f->write<ubyte>(nam5);
			WriteSubrecord('NAM6',1,f);
			f->write<ubyte>(nam6);
			WriteSubrecord('NAM7',1,f);
			f->write<ubyte>(nam7);
			WriteSubrecord('NAM8',1,f);
			f->write<ubyte>(nam8);
			WriteSubrecord('NAM9',1,f);
			f->write<ubyte>(nam9);
		}
		if (hasFlags)
		{
			WriteSubrecord('DNAM',4,f);
			f->write<ulong>(flags);
			if (!(flags & 1))
			{
				WriteSubrecord('TNAM',4,f);
				f->write<ulong>(time);
			}
		}
		for (int i = 0;i < buttons.Count();i++)
		{
			WriteZStringSubrecord('ITXT',buttons[i].buttonText,f);
			for (int j = 0;j < buttons[i].conditions.Count();j++)
			{
				WriteSubrecord('CTDA',sizeof(Condition),f);
				f->write<Condition>(buttons[i].conditions[j]);
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		DescriptionGetSaveSize();
		FullNameGetSaveSize();
		size += ComputeSubrecordSize(4);
		if (hasnam)
		{
			size += ComputeSubrecordSize(1);
			size += ComputeSubrecordSize(1);
			size += ComputeSubrecordSize(1);
			size += ComputeSubrecordSize(1);
			size += ComputeSubrecordSize(1);
			size += ComputeSubrecordSize(1);
			size += ComputeSubrecordSize(1);
			size += ComputeSubrecordSize(1);
			size += ComputeSubrecordSize(1);
			size += ComputeSubrecordSize(1);
		}
		if (hasFlags)
		{
			size += ComputeSubrecordSize(4);
			if (!(flags & 1))
			{
				size += ComputeSubrecordSize(4);
			}
		}
		for (int i = 0;i < buttons.Count();i++)
		{
			size += ZStringSubrecordSize(buttons[i].buttonText);
			for (int j = 0;j < buttons[i].conditions.Count();j++)
			{
				size += ComputeSubrecordSize(sizeof(Condition));
			}
		}
		return size;
	}
};
