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
class FormListForm : public Form
{
protected:
	SimpleDynVecClass<formid> forms;
public:
	FormListForm(FormHeader h,ModFile *f) : Form(h,f)
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
			case 'LNAM':
				forms.Add(f->read<formid>());
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
		for (int i = 0;i < forms.Count();i++)
		{
			WriteSubrecord('LNAM',4,f);
			f->write<formid>(forms[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		for (int i = 0;i < forms.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
