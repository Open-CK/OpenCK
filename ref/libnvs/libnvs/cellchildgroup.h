/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "formgroup.h"
class CellChildGroup
{
protected:
	ParentGroupHeader header;
	SimpleDynVecClass<ParentGroupHeader> groupHeaders;
	SimpleDynVecClass<FormGroup *> groups;
	ModFile *file;
public:
	CellChildGroup(ParentGroupHeader h, ModFile *f) : header(h), file(f), groupHeaders(0), groups(0)
	{
	}
	virtual ~CellChildGroup()
	{
		for (int i = 0;i < groups.Count();i++)
		{
			delete groups[i];
		}
		groupHeaders.Delete_All();
		groups.Delete_All();
	}
	virtual void Load(FileRead *f)
	{
		int size = header.groupSize - sizeof(header);
		while (size > 0)
		{
			ParentGroupHeader h = f->read<ParentGroupHeader>();
			groupHeaders.Add(h);
			FormGroup *gr = new FormGroup(h,file);
			gr->Load(f);
			groups.Add(gr);
			size -= h.groupSize;
		}
	}
	virtual void Save(FileWrite *f)
	{
		for (int i = 0;i < groups.Count();i++)
		{
			f->write<ParentGroupHeader>(groupHeaders[i]);
			groups[i]->Save(f);
		}
	}
};
