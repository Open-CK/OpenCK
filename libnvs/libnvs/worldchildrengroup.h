/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "exteriorblockgroup.h"
class WorldChildrenGroup
{
protected:
	ParentGroupHeader header;
	FormHeader cellHeader;
	Form *cell;
	ParentGroupHeader cellGroupHeader;
	CellChildGroup *cellGroup;
	SimpleDynVecClass<ExteriorCellHeader> groupHeaders;
	SimpleDynVecClass<ExteriorBlockGroup *> groups;
	ModFile *file;
	int cellPos;
	int curGroup;
public:
	WorldChildrenGroup(ParentGroupHeader h,ModFile *f) : header(h), file(f), groupHeaders(0), groups(0), cell(0), cellGroup(0), cellPos(0), curGroup(0)
	{
	}
	virtual ~WorldChildrenGroup()
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
			FormHeader h2 = f->read<FormHeader>();
			if (SwapBytes(h2.type) == 'CELL')
			{
				cellPos = curGroup;
				cellHeader = h2;
				cell = CreateForm(h2,file);
				cell->LoadCompressed(f);
				size -= sizeof(FormHeader);
				size -= h2.dataSize;
				cellGroupHeader = f->read<ParentGroupHeader>();
				if (cellGroupHeader.groupType == 6)
				{
					cellGroup = new CellChildGroup(cellGroupHeader,file);
					cellGroup->Load(f);
					size -= cellGroupHeader.groupSize;
				}
				else
				{
					f->unread(sizeof(ParentGroupHeader));
				}
			}
			else
			{
				curGroup++;
				f->unread(sizeof(FormHeader));
				ExteriorCellHeader h3 = f->read<ExteriorCellHeader>();
				ExteriorBlockGroup *gr = new ExteriorBlockGroup(h3,file);
				gr->Load(f);
				groupHeaders.Add(h3);
				groups.Add(gr);
				size -= h3.groupSize;
			}
		}
	}
	void Save(FileWrite *f)
	{
		if (!groups.Count())
		{
			if (cell)
			{
				cell->SaveCompressed(f);
				if (cellGroup)
				{
					f->write<ParentGroupHeader>(cellGroupHeader);
					cellGroup->Save(f);
				}
			}
		}
		for (int i = 0;i < groups.Count();i++)
		{
			if (i == cellPos)
			{
				if (cell)
				{
					cell->SaveCompressed(f);
					if (cellGroup)
					{
						f->write<ParentGroupHeader>(cellGroupHeader);
						cellGroup->Save(f);
					}
				}
			}
			f->write<ExteriorCellHeader>(groupHeaders[i]);
			groups[i]->Save(f);
		}
	}
};