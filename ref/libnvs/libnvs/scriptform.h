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
class ScriptForm : public Form, public Script
{
public:
	ScriptForm(FormHeader h,ModFile *f) : Form(h,f)
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
			ScriptLoad(this);
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
		if (!(header.flags & 0x20))
		{
			ScriptSave(this,this);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		if (!(header.flags & 0x20))
		{
			ScriptGetSaveSize(this,this);
		}
		return size;
	}
};
