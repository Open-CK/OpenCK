/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "cellchildgroup.h"
struct ExteriorSubBlockStruct
{
	FormHeader formHeader;
	Form *form;
	ParentGroupHeader groupHeader;
	CellChildGroup *group;
	ExteriorSubBlockStruct() : form(0), group(0)
	{
	}
};
class ExteriorSubBlockGroup
{
protected:
	ExteriorCellHeader header;
	SimpleDynVecClass<ExteriorSubBlockStruct> forms;
	ModFile *file;
public:
	ExteriorSubBlockGroup(ExteriorCellHeader h,ModFile *f) : header(h), file(f), forms(0)
	{
	}
	virtual ~ExteriorSubBlockGroup()
	{
		for (int i = 0;i < forms.Count();i++)
		{
			delete forms[i].form;
			delete forms[i].group;
		}
		forms.Delete_All();
	}
	void Load(FileRead *f)
	{
		int size = header.groupSize - sizeof(header);
		while (size > 0)
		{
			ExteriorSubBlockStruct gr;
			gr.formHeader = f->read<FormHeader>();
			gr.form = CreateForm(gr.formHeader,file);
			gr.form->LoadCompressed(f);
			size -= gr.formHeader.dataSize;
			size -= sizeof(FormHeader);
			if (size <= 0)
			{
				forms.Add(gr);
				break;
			}
			ParentGroupHeader h2 = f->read<ParentGroupHeader>();
			if (SwapBytes(h2.type) == 'GRUP')
			{
				gr.groupHeader = h2;
				gr.group = new CellChildGroup(gr.groupHeader,file);
				gr.group->Load(f);
				size -= gr.groupHeader.groupSize;
			}
			else
			{
				f->unread(sizeof(ParentGroupHeader));
			}
			forms.Add(gr);
		}
	}
	void Save(FileWrite *f)
	{
		for (int i = 0;i < forms.Count();i++)
		{
			forms[i].form->SaveCompressed(f);
			if (forms[i].group)
			{
				f->write<ParentGroupHeader>(forms[i].groupHeader);
				forms[i].group->Save(f);
			}
		}
	}
};
