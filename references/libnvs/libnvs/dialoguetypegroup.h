/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "typegroup.h"
#include "formgroup.h"
struct DialogueGroupStruct
{
	FormHeader formHeader;
	Form *form;
	ParentGroupHeader groupHeader;
	FormGroup *group;
	DialogueGroupStruct() : form(0), group(0)
	{
	}
};
class DialogueTypeGroup : public TypeGroup
{
protected:
	SimpleDynVecClass<DialogueGroupStruct> forms;
public:
	DialogueTypeGroup(TypeGroupHeader h,ModFile *f) : TypeGroup(h,f), forms(0)
	{
	}
	virtual ~DialogueTypeGroup()
	{
		for (int i = 0;i < forms.Count();i++)
		{
			delete forms[i].form;
			if (forms[i].group)
			{
				delete forms[i].group;
			}
		}
		forms.Delete_All();
	}
	void Load(FileRead *f)
	{
		int size = header.groupSize - sizeof(header);
		while (size > 0)
		{
			DialogueGroupStruct gr;
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
				gr.group = new FormGroup(gr.groupHeader,file);
				gr.group->Load(f);
				size -= h2.groupSize;
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