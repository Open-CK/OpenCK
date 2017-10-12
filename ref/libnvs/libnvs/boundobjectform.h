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
struct BoundingBox
{
	ushort xmin;
	ushort ymin;
	ushort zmin;
	ushort xmax;
	ushort ymax;
	ushort zmax;
};
#define BoundObjectFormLoad() \
			FormLoad(); \
			case 'OBND': \
				hasObjectBounds = true; \
				objectBounds = f->read<BoundingBox>(); \
				readSize += sizeof(BoundingBox); \
				break;
#define BoundObjectFormSave() \
		FormSave(); \
		if (hasObjectBounds) \
		{ \
				WriteSubrecord('OBND',sizeof(BoundingBox),f); \
				f->write<BoundingBox>(objectBounds); \
		}
#define BoundObjectFormGetSaveSize() \
		FormGetSaveSize(); \
		if (hasObjectBounds) \
		{ \
			size += ComputeSubrecordSize(sizeof(BoundingBox)); \
		}
class BoundObjectForm : public Form
{
protected:
	BoundingBox objectBounds;
	bool hasObjectBounds;
public:
	BoundObjectForm(FormHeader h,ModFile *f) : Form(h,f), hasObjectBounds(0)
	{
	}
};