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
#include "interiorblockgroup.h"
class CellTypeGroup : public TypeGroup
{
protected:
	SimpleDynVecClass<InteriorCellHeader> groupHeaders;
	SimpleDynVecClass<InteriorBlockGroup *> groups;
public:
	CellTypeGroup(TypeGroupHeader h,ModFile *f) : TypeGroup(h,f), groupHeaders(0), groups(0)
	{
	}
	virtual ~CellTypeGroup()
	{
		for (int i = 0;i < groups.Count();i++)
		{
			delete groups[i];
		}
		groups.Delete_All();
	}
	void Load(FileRead *f)
	{
		int size = header.groupSize - sizeof(header);
		while (size > 0)
		{
			InteriorCellHeader h = f->read<InteriorCellHeader>();
			InteriorBlockGroup *gr = new InteriorBlockGroup(h,file);
			gr->Load(f);
			groupHeaders.Add(h);
			groups.Add(gr);
			size -= h.groupSize;
		}
	}
	void Save(FileWrite *f)
	{
		for (int i = 0;i < groups.Count();i++)
		{
			f->write<InteriorCellHeader>(groupHeaders[i]);
			groups[i]->Save(f);
		}
	}
};