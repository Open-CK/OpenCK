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
struct FactionRank
{
	long rank;
	char *male;
	char *female;
	char *insignia;
	FactionRank() : rank(0), male(0), female(0), insignia(0)
	{
	}
	virtual ~FactionRank()
	{
		if (male)
		{
			delete[] male;
		}
		if (female)
		{
			delete[] female;
		}
		if (insignia)
		{
			delete[] insignia;
		}
	}
	FactionRank & operator = (const FactionRank & that)
	{
		rank = that.rank;
		male = newstr(that.male);
		female = newstr(that.female);
		insignia = newstr(that.insignia);
		return *this;
	}
};
class FactionForm : public Form, public FullName, public Reaction
{
protected:
	bool smallFlagsFound;
	ubyte smallFlags;
	ulong flags;
	SimpleDynVecClass<FactionRank> ranks;
	float crimeGoldMultiplier;
	bool cnamFound;
	formid reputation;
public:
	FactionForm(FormHeader h,ModFile *f) : Form(h,f), smallFlagsFound(false), cnamFound(false), reputation(0)
	{
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentRank = -1;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			FullNameLoad();
			ReactionLoad();
			case 'DATA':
				if (h.size == 1)
				{
					smallFlagsFound = true;
					smallFlags = f->read<ubyte>();
					readSize += 1;
				}
				else
				{
					flags = f->read<ulong>();
					readSize += 4;
				}
				break;
			case 'RNAM':
				currentRank++;
				ranks.Add(FactionRank());
				ranks[currentRank].rank = f->read<long>();
				readSize += 4;
				break;
			case 'MNAM':
				ranks[currentRank].male = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'FNAM':
				ranks[currentRank].female = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'INAM':
				ranks[currentRank].insignia = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'CNAM':
				cnamFound = true;
				crimeGoldMultiplier = f->read<float>();
				readSize += 4;
				break;
			case 'WMI1':
				reputation = f->read<formid>();
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
		FullNameSave();
		ReactionSave();
		if (smallFlagsFound)
		{
			WriteSubrecord('DATA',1,f);
			f->write<ubyte>(smallFlags);
		}
		else
		{
			WriteSubrecord('DATA',4,f);
			f->write<ulong>(flags);
		}
		if (cnamFound)
		{
			WriteSubrecord('CNAM',4,f);
			f->write<float>(crimeGoldMultiplier);
		}
		for (int i = 0;i < ranks.Count();i++)
		{
			WriteSubrecord('RNAM',4,f);
			f->write<long>(ranks[i].rank);
			WriteZStringSubrecord('MNAM',ranks[i].male,f);
			WriteZStringSubrecord('FNAM',ranks[i].female,f);
			WriteZStringSubrecord('INAM',ranks[i].insignia,f);
		}
		if (reputation)
		{
			WriteSubrecord('WMI1',4,f);
			f->write<formid>(reputation);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		ReactionGetSaveSize();
		if (smallFlagsFound)
		{
			size += ComputeSubrecordSize(1);
		}
		else
		{
			size += ComputeSubrecordSize(4);
		}
		if (cnamFound)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < ranks.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			size += ZStringSubrecordSize(ranks[i].male);
			size += ZStringSubrecordSize(ranks[i].female);
			size += ZStringSubrecordSize(ranks[i].insignia);
		}
		if (reputation)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
