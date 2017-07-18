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
struct PerkData
{
	ubyte trait;
	ubyte minLevel;
	ubyte ranks;
	ubyte playable;
	ubyte hidden;
};
struct PerkData2
{
	ubyte trait;
	ubyte minLevel;
	ubyte ranks;
	ubyte playable;
};
struct PerkEntryData
{
	ubyte type;
	ubyte rank;
	ubyte priority;
};
struct EntryPointPerkData
{
	ubyte entryPoint;
	ubyte function;
	ubyte conditionCount;
};
#pragma pack(pop)
struct QuestPerkData
{
	formid quest;
	ubyte questStage;
};
struct PerkCondition
{
	ubyte runOn;
	SimpleDynVecClass<Condition> conditions;
};
struct PerkEntry
{
	PerkEntryData data;
	QuestPerkData questData;
	formid ability;
	EntryPointPerkData entryPointData;
	SimpleDynVecClass<PerkCondition *> perkConditions;
	ubyte entryPointFunctionType;
	float oneValue;
	float twoValue[2];
	formid leveledList;
	char *buttonLabel;
	ushort scriptFlags;
	Script script;
	PerkEntry() : ability(0), leveledList(0), buttonLabel(0)
	{
	}
	virtual ~PerkEntry()
	{
		if (buttonLabel)
		{
			delete[] buttonLabel;
		}
	}
};
class PerkForm : public Form, public FullName, public Description, public Texture
{
protected:
	SimpleDynVecClass<Condition> conditions;
	PerkData data;
	PerkData2 data2;
	bool hasPerkData2;
	SimpleDynVecClass<PerkEntry *> perkEntries;
public:
	PerkForm(FormHeader h,ModFile *f) : Form(h,f), hasPerkData2(false)
	{
	}
	virtual ~PerkForm()
	{
		for (int i = 0;i < perkEntries.Count();i++)
		{
			for (int j = 0;j < perkEntries[i]->perkConditions.Count();j++)
			{
				delete perkEntries[i]->perkConditions[j];
			}
			delete perkEntries[i];
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		SimpleDynVecClass<Condition> *cond = &conditions;
		int currentEntry = -1;
		int currentCondition = -1;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			FullNameLoad();
			DescriptionLoad();
			TextureLoad(this,'ICON');
			case 'CTDA':
				cond->Add(f->read<Condition>());
				readSize += sizeof(Condition);
				break;
			case 'DATA':
				if (currentEntry == -1)
				{
					if (h.size == sizeof(PerkData))
					{
						data = f->read<PerkData>();
						readSize += sizeof(PerkData);
					}
					else
					{
						hasPerkData2 = true;
						data2 = f->read<PerkData2>();
						readSize += sizeof(PerkData2);
					}
				}
				else
				{
					if (perkEntries[currentEntry]->data.type == 0)
					{
						perkEntries[currentEntry]->questData = f->read<QuestPerkData>();
						readSize += sizeof(QuestPerkData);
					}
					else if (perkEntries[currentEntry]->data.type == 1)
					{
						perkEntries[currentEntry]->ability = f->read<formid>();
						readSize += 4;
					}
					else if (perkEntries[currentEntry]->data.type == 2)
					{
						perkEntries[currentEntry]->entryPointData = f->read<EntryPointPerkData>();
						readSize += sizeof(EntryPointPerkData);
					}
				}
				break;
			case 'PRKE':
				currentEntry++;
				currentCondition = -1;
				perkEntries.Add(new PerkEntry());
				perkEntries[currentEntry]->data = f->read<PerkEntryData>();
				readSize += sizeof(PerkEntryData);
				break;
			case 'PRKF':
				break;
			case 'PRKC':
				currentCondition++;
				perkEntries[currentEntry]->perkConditions.Add(new PerkCondition());
				perkEntries[currentEntry]->perkConditions[currentCondition]->runOn = f->read<ubyte>();
				cond = &perkEntries[currentEntry]->perkConditions[currentCondition]->conditions;
				readSize += 1;
				break;
			case 'EPFT':
				perkEntries[currentEntry]->entryPointFunctionType = f->read<ubyte>();
				readSize += 1;
				break;
			case 'EPFD':
				switch (perkEntries[currentEntry]->entryPointFunctionType)
				{
				case 1:
					perkEntries[currentEntry]->oneValue = f->read<float>();
					readSize += 4;
					break;
				case 2:
					perkEntries[currentEntry]->twoValue[0] = f->read<float>();
					perkEntries[currentEntry]->twoValue[1] = f->read<float>();
					readSize += 8;
					break;
				case 3:
					perkEntries[currentEntry]->leveledList = f->read<formid>();
					readSize += 4;
					break;
				}
				break;
			case 'EPF2':
				perkEntries[currentEntry]->buttonLabel = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'EPF3':
				perkEntries[currentEntry]->scriptFlags = f->read<ushort>();
				readSize += 2;
				break;
			ScriptLoad((&perkEntries[currentEntry]->script));
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
		DescriptionSave();
		TextureSave(this,'ICON');
		for (int conditioncount = 0;conditioncount < conditions.Count();conditioncount++)
		{
			WriteSubrecord('CTDA',sizeof(Condition),f);
			f->write<Condition>(conditions[conditioncount]);
		}
		if (hasPerkData2)
		{
			WriteSubrecord('DATA',sizeof(PerkData2),f);
			f->write<PerkData2>(data2);
		}
		else
		{
			WriteSubrecord('DATA',sizeof(PerkData),f);
			f->write<PerkData>(data);
		}
		for (int i = 0;i < perkEntries.Count();i++)
		{
			switch (perkEntries[i]->data.type)
			{
			case 0:
				WriteSubrecord('PRKE',sizeof(PerkEntryData),f);
				f->write<PerkEntryData>(perkEntries[i]->data);
				WriteSubrecord('DATA',sizeof(QuestPerkData),f);
				f->write<QuestPerkData>(perkEntries[i]->questData);
				WriteSubrecord('PRKF',0,f);
				break;
			case 1:
				WriteSubrecord('PRKE',sizeof(PerkEntryData),f);
				f->write<PerkEntryData>(perkEntries[i]->data);
				if (perkEntries[i]->ability)
				{
					WriteSubrecord('DATA',4,f);
					f->write<formid>(perkEntries[i]->ability);
				}
				WriteSubrecord('PRKF',0,f);
				break;
			case 2:
				WriteSubrecord('PRKE',sizeof(PerkEntryData),f);
				f->write<PerkEntryData>(perkEntries[i]->data);
				WriteSubrecord('DATA',sizeof(EntryPointPerkData),f);
				f->write<EntryPointPerkData>(perkEntries[i]->entryPointData);
				for (int j = 0;j < perkEntries[i]->perkConditions.Count();j++)
				{
					WriteSubrecord('PRKC',1,f);
					f->write<ubyte>(perkEntries[i]->perkConditions[j]->runOn);
					for (int conditioncount = 0;conditioncount < perkEntries[i]->perkConditions[j]->conditions.Count();conditioncount++)
					{
						WriteSubrecord('CTDA',sizeof(Condition),f);
						f->write<Condition>(perkEntries[i]->perkConditions[j]->conditions[conditioncount]);
					}
				}
				switch (perkEntries[i]->entryPointFunctionType)
				{
				case 1:
					WriteSubrecord('EPFT',1,f);
					f->write<ubyte>(perkEntries[i]->entryPointFunctionType);
					WriteSubrecord('EPFD',4,f);
					f->write<float>(perkEntries[i]->oneValue);
					break;
				case 2:
					WriteSubrecord('EPFT',1,f);
					f->write<ubyte>(perkEntries[i]->entryPointFunctionType);
					WriteSubrecord('EPFD',8,f);
					f->write<float>(perkEntries[i]->twoValue[0]);
					f->write<float>(perkEntries[i]->twoValue[1]);
					break;
				case 3:
					WriteSubrecord('EPFT',1,f);
					f->write<ubyte>(perkEntries[i]->entryPointFunctionType);
					if (perkEntries[i]->leveledList)
					{
						WriteSubrecord('EPFD',4,f);
						f->write<formid>(perkEntries[i]->leveledList);
					}
					break;
				case 4:
					WriteSubrecord('EPFT',1,f);
					f->write<ubyte>(perkEntries[i]->entryPointFunctionType);
					WriteZStringSubrecord('EPF2',perkEntries[i]->buttonLabel,f);
					WriteSubrecord('EPF3',2,f);
					f->write<ushort>(perkEntries[i]->scriptFlags);
					ScriptSave((&perkEntries[i]->script),this);
					break;
				}
				WriteSubrecord('PRKF',0,f);
				break;
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		DescriptionGetSaveSize();
		TextureGetSaveSize(this);
		for (int conditioncount = 0;conditioncount < conditions.Count();conditioncount++)
		{
			size += ComputeSubrecordSize(sizeof(Condition));
		}
		if (hasPerkData2)
		{
			size += ComputeSubrecordSize(sizeof(PerkData2));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(PerkData));
		}
		for (int i = 0;i < perkEntries.Count();i++)
		{
			switch (perkEntries[i]->data.type)
			{
			case 0:
				size += ComputeSubrecordSize(sizeof(PerkEntryData));
				size += ComputeSubrecordSize(sizeof(QuestPerkData));
				size += ComputeSubrecordSize(0);
				break;
			case 1:
				size += ComputeSubrecordSize(sizeof(PerkEntryData));
				if (perkEntries[i]->ability)
				{
					size += ComputeSubrecordSize(4);
				}
				size += ComputeSubrecordSize(0);
				break;
			case 2:
				size += ComputeSubrecordSize(sizeof(PerkEntryData));
				size += ComputeSubrecordSize(sizeof(EntryPointPerkData));
				for (int j = 0;j < perkEntries[i]->perkConditions.Count();j++)
				{
					size += ComputeSubrecordSize(1);
					for (int conditioncount = 0;conditioncount < perkEntries[i]->perkConditions[j]->conditions.Count();conditioncount++)
					{
						size += ComputeSubrecordSize(sizeof(Condition));
					}
				}
				switch (perkEntries[i]->entryPointFunctionType)
				{
				case 1:
					size += ComputeSubrecordSize(1);
					size += ComputeSubrecordSize(4);
					break;
				case 2:
					size += ComputeSubrecordSize(1);
					size += ComputeSubrecordSize(8);
					break;
				case 3:
					size += ComputeSubrecordSize(1);
					if (perkEntries[i]->leveledList)
					{
						size += ComputeSubrecordSize(4);
					}
					break;
				case 4:
					size += ComputeSubrecordSize(1);
					size += ZStringSubrecordSize(perkEntries[i]->buttonLabel);
					size += ComputeSubrecordSize(2);
					ScriptGetSaveSize((&perkEntries[i]->script),this);
					break;
				}
				size += ComputeSubrecordSize(0);
				break;
			}
		}
		return size;
	}
};
