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
class TypeGroup
{
protected:
	TypeGroupHeader header;
	SimpleDynVecClass<FormHeader> formHeaders;
	SimpleDynVecClass<Form *> forms;
	ModFile *file;
public:
	TypeGroup(TypeGroupHeader h,ModFile *f) : header(h), file(f)
	{
	}
	virtual ~TypeGroup()
	{
		for (int i = 0;i < forms.Count();i++)
		{
			delete forms[i];
		}
		forms.Delete_All();
		formHeaders.Delete_All();
	}
	virtual void Load(FileRead *f)
	{
		int size = header.groupSize - sizeof(header);
		while (size > 0)
		{
			FormHeader h = f->read<FormHeader>();
			formHeaders.Add(h);
			Form *fo = CreateForm(h,file);
			fo->LoadCompressed(f);
			forms.Add(fo);
			size -= h.dataSize;
			size -= sizeof(FormHeader);
		}
	}
	virtual void Save(FileWrite *f)
	{
		for (int i = 0;i < forms.Count();i++)
		{
			forms[i]->SaveCompressed(f);
		}
	}
};