/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#include "modfile.h"
#include "tes4form.h"
#include "form.h"
#include "typegroup.h"
#include "celltypegroup.h"
#include "dialoguetypegroup.h"
#include "worldspacetypegroup.h"
#include "nvsfile.h"
ModFile::ModFile() : header(0), typeGroupHeaders(0), typeGroups(0), masters(0), fname(0)
{
}
void ModFile::Open(const char *path)
{
	fname = new char[260];
	char ext[260];
	_splitpath(path,0,0,fname,ext);
	strcat(fname,ext);
	FileRead *f = new FileRead(path);
	h = f->read<FormHeader>();
	header = new TES4Form(h,this);
	header->LoadCompressed(f);
	for (ubyte i = 0;i < header->masters.Count();i++)
	{
		Master m;
		m.name = header->masters[i];
		m.loadID = GetLoadIndex(m.name,i);
		masters.Add(m);
	}
	Master m2;
	m2.name = fname;
	m2.loadID = GetLoadIndex(m2.name,(ubyte)header->masters.Count());
	masters.Add(m2);
	while (!f->eof())
	{
		TypeGroupHeader gh = f->read<TypeGroupHeader>();
		TypeGroup *g;
		switch(SwapBytes(gh.label))
		{
		case 'DIAL':
			g = new DialogueTypeGroup(gh,this);
			break;
		case 'CELL':
			g = new CellTypeGroup(gh,this);
			break;
		case 'WRLD':
			g = new WorldspaceTypeGroup(gh,this);
			break;
		default:
			g = new TypeGroup(gh,this);
			break;
		}
		g->Load(f);
		typeGroupHeaders.Add(gh);
		typeGroups.Add(g);
	}
}
void ModFile::Save(const char *path)
{
	FileWrite *f = new FileWrite(path);
	header->SaveCompressed(f);
	for (int i = 0;i < typeGroups.Count();i++)
	{
		f->write<TypeGroupHeader>(typeGroupHeaders[i]);
		typeGroups[i]->Save(f);
	}
}
ModFile::~ModFile()
{
	if (header)
	{
		delete header;
	}
	for (int i = 0;i < typeGroups.Count();i++)
	{
		delete typeGroups[i];
	}
	typeGroupHeaders.Delete_All();
	typeGroups.Delete_All();
	if (fname)
	{
		delete[] fname;
	}
}
