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
#pragma pack(push,1)
struct DialogData
{
	ubyte type;
	ubyte flags;
};
struct DialogDataOld
{
	ubyte type;
};
#pragma pack(pop)
struct DialogSharedInfo
{
	formid infoConnection;
	long infoIndex;
	bool hasInfoIndex;
	DialogSharedInfo() : hasInfoIndex(false)
	{
	}
};
struct DialogQuest
{
	formid quest;
	ulong type;
	SimpleDynVecClass<DialogSharedInfo> sharedInfo;
};
class DialogForm : public Form, public FullName
{
protected:
	DialogData data;
	DialogDataOld oldData;
	bool hasOldData;
	SimpleDynVecClass<DialogQuest> quests;
	float priority;
	bool hasPriority;
	char *dumbString;
	SimpleDynVecClass<DialogSharedInfo> infoConnections;
public:
	DialogForm(FormHeader h,ModFile *f) : Form(h,f), hasOldData(false), hasPriority(false), dumbString(0)
	{
	}
	~DialogForm()
	{
		if (dumbString)
		{
			delete[] dumbString;
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentQuest = -1;
		int currentQuestInfo = -1;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			case 'QSTI':
			case 'QSTR':
				{
					currentQuest++;
					currentQuestInfo = -1;
					DialogQuest q;
					q.quest = f->read<formid>();
					readSize += 4;
					q.type = h.type;
					quests.Add(q);
				}
				break;
			case 'INFC':
				if (currentQuest >= 0)
				{
					quests[currentQuest].sharedInfo.Add(DialogSharedInfo());
					currentQuestInfo++;
					quests[currentQuest].sharedInfo[currentQuestInfo].infoConnection = f->read<formid>();
				}
				else
				{
					currentQuestInfo++;
					infoConnections.Add(DialogSharedInfo());
					infoConnections[currentQuestInfo].infoConnection = f->read<formid>();
				}
				readSize += 4;
				break;
			case 'INFX':
				if (currentQuest >= 0)
				{
					quests[currentQuest].sharedInfo[currentQuestInfo].infoIndex = f->read<long>();
					quests[currentQuest].sharedInfo[currentQuestInfo].hasInfoIndex = true;
				}
				else
				{
					infoConnections[currentQuestInfo].infoIndex = f->read<long>();
					infoConnections[currentQuestInfo].hasInfoIndex = true;
				}
				readSize += 4;
				break;
			FullNameLoad();
			case 'PNAM':
				hasPriority = true;
				priority = f->read<float>();
				readSize += 4;
				break;
			case 'TDUM':
				dumbString = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DATA':
				if (h.size == sizeof(DialogData))
				{
					data = f->read<DialogData>();
					readSize += sizeof(DialogData);
				}
				else
				{
					hasOldData = true;
					oldData = f->read<DialogDataOld>();
					readSize += sizeof(DialogDataOld);
				}
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
		for (int i = 0;i < quests.Count();i++)
		{
			WriteSubrecord(quests[i].type,4,f);
			f->write<formid>(quests[i].quest);
			for (int j = 0;j < quests[i].sharedInfo.Count();j++)
			{
				WriteSubrecord('INFC',4,f);
				f->write<formid>(quests[i].sharedInfo[j].infoConnection);
				if (quests[i].sharedInfo[j].hasInfoIndex)
				{
					WriteSubrecord('INFX',4,f);
					f->write<long>(quests[i].sharedInfo[j].infoIndex);
				}
			}
		}
		for (int i = 0;i < infoConnections.Count();i++)
		{
			WriteSubrecord('INFC',4,f);
			f->write<formid>(infoConnections[i].infoConnection);
			if (infoConnections[i].hasInfoIndex)
			{
				WriteSubrecord('INFX',4,f);
				f->write<long>(infoConnections[i].infoIndex);
			}
		}
		FullNameSave();
		if (hasPriority)
		{
			WriteSubrecord('PNAM',4,f);
			f->write<float>(priority);
		}
		WriteZStringSubrecord('TDUM',dumbString,f);
		if (hasOldData)
		{
			WriteSubrecord('DATA',sizeof(DialogDataOld),f);
			f->write<DialogDataOld>(oldData);
		}
		else
		{
			WriteSubrecord('DATA',sizeof(DialogData),f);
			f->write<DialogData>(data);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		for (int i = 0;i < quests.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			for (int j = 0;j < quests[i].sharedInfo.Count();j++)
			{
				size += ComputeSubrecordSize(4);
				if (quests[i].sharedInfo[j].hasInfoIndex)
				{
					size += ComputeSubrecordSize(4);
				}
			}
		}
		for (int i = 0;i < infoConnections.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			if (infoConnections[i].hasInfoIndex)
			{
				size += ComputeSubrecordSize(4);
			}
		}
		FullNameGetSaveSize();
		if (hasPriority)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ZStringSubrecordSize(dumbString);
		if (hasOldData)
		{
			size += ComputeSubrecordSize(sizeof(DialogDataOld));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(DialogData));
		}
		return size;
	}
};
