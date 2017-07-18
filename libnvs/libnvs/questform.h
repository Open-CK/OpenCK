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
struct QuestLogEntry
{
	ubyte flags;
	SimpleDynVecClass<Condition> conditions;
	SimpleDynVecClass<ConditionOld> oldConditions;
	SimpleDynVecClass<ConditionOld2> oldConditions2;
	char *logEntry;
	Script script;
	formid nextQuest;
	QuestLogEntry() : logEntry(0), nextQuest(0)
	{
	}
	virtual ~QuestLogEntry()
	{
		if (logEntry)
		{
			delete[] logEntry;
		}
	}
};
struct QuestStage
{
	short index;
	SimpleDynVecClass<QuestLogEntry *> logEntries;
};
struct Target
{
	formid target;
	ubyte flags;
	Target() : target(0)
	{
	}
};
struct QuestTarget
{
	Target target;
	SimpleDynVecClass<Condition> conditions;
	SimpleDynVecClass<ConditionOld> oldConditions;
	SimpleDynVecClass<ConditionOld2> oldConditions2;
};
struct QuestObjective
{
	long index;
	char *description;
	SimpleDynVecClass<QuestTarget> targets;
	QuestObjective() : description(0)
	{
	}
	virtual ~QuestObjective()
	{
		if (description)
		{
			delete[] description;
		}
	}
};
struct QuestData
{
	ubyte flags;
	ubyte priority;
	float questDelay;
};
#pragma pack (push, 1)
struct QuestDataOld
{
	ubyte flags;
	ubyte priority;
};
#pragma pack (pop)
class QuestForm : public Form, public Scriptable, public Texture, public FullName
{
protected:
	QuestData data;
	QuestDataOld oldData;
	bool hasOldData;
	SimpleDynVecClass<Condition> conditions;
	SimpleDynVecClass<ConditionOld> oldConditions;
	SimpleDynVecClass<ConditionOld2> oldConditions2;
	SimpleDynVecClass<QuestStage *> stages;
	SimpleDynVecClass<QuestObjective *> objectives;
public:
	QuestForm(FormHeader h,ModFile *f) : Form(h,f), hasOldData(false)
	{
	}
	virtual ~QuestForm()
	{
		for (int i = 0;i < stages.Count();i++)
		{
			for (int j = 0;j < stages[i]->logEntries.Count();j++)
			{
				delete stages[i]->logEntries[j];
			}
			delete stages[i];
		}
		for (int i = 0;i < objectives.Count();i++)
		{
			delete objectives[i];
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentStage = -1;
		int currentLogEntry = -1;
		int currentObjective = -1;
		int currentTarget = -1;
		SimpleDynVecClass<Condition> *cond = &conditions;
		SimpleDynVecClass<ConditionOld> *condOld = &oldConditions;
		SimpleDynVecClass<ConditionOld2> *condOld2 = &oldConditions2;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			ScriptableLoad();
			FullNameLoad();
			TextureLoad(this,'ICON');
			case 'DATA':
				if (h.size == sizeof(QuestData))
				{
					data = f->read<QuestData>();
					readSize += sizeof(QuestData);
				}
				else if (h.size == sizeof(QuestDataOld))
				{
					hasOldData = true;
					oldData = f->read<QuestDataOld>();
					readSize += sizeof(QuestDataOld);
				}
				break;
			case 'CTDA':
				if (h.size == sizeof(Condition))
				{
					cond->Add(f->read<Condition>());
					readSize += sizeof(Condition);
				}
				else if (h.size == sizeof(ConditionOld))
				{
					condOld->Add(f->read<ConditionOld>());
					readSize += sizeof(ConditionOld);
				}
				else if (h.size == sizeof(ConditionOld2))
				{
					condOld2->Add(f->read<ConditionOld2>());
					readSize += sizeof(ConditionOld2);
				}
				break;
			case 'INDX':
				currentStage++;
				currentLogEntry = -1;
				stages.Add(new QuestStage());
				stages[currentStage]->index = f->read<short>();
				readSize += 2;
				break;
			case 'QSDT':
				currentLogEntry++;
				stages[currentStage]->logEntries.Add(new QuestLogEntry());
				stages[currentStage]->logEntries[currentLogEntry]->flags = f->read<ubyte>();
				readSize += 1;
				cond = &stages[currentStage]->logEntries[currentLogEntry]->conditions;
				condOld = &stages[currentStage]->logEntries[currentLogEntry]->oldConditions;
				condOld2 = &stages[currentStage]->logEntries[currentLogEntry]->oldConditions2;
				break;
			case 'CNAM':
				stages[currentStage]->logEntries[currentLogEntry]->logEntry = f->readzstring(h.size);
				readSize += h.size;
				break;
			ScriptLoad((&stages[currentStage]->logEntries[currentLogEntry]->script));
			case 'NAM0':
				stages[currentStage]->logEntries[currentLogEntry]->nextQuest = f->read<formid>();
				readSize += 4;
				break;
			case 'QOBJ':
				currentObjective++;
				currentTarget = -1;
				objectives.Add(new QuestObjective());
				objectives[currentObjective]->index = f->read<long>();
				readSize += 4;
				break;
			case 'NNAM':
				objectives[currentObjective]->description = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'QSTA':
				currentTarget++;
				objectives[currentObjective]->targets.Add(QuestTarget());
				objectives[currentObjective]->targets[currentTarget].target = f->read<Target>();
				readSize += sizeof(Target);
				cond = &objectives[currentObjective]->targets[currentTarget].conditions;
				condOld = &objectives[currentObjective]->targets[currentTarget].oldConditions;
				condOld2 = &objectives[currentObjective]->targets[currentTarget].oldConditions2;
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
		ScriptableSave();
		FullNameSave();
		TextureSave(this,'ICON');
		if (hasOldData)
		{
			WriteSubrecord('DATA',sizeof(QuestDataOld),f);
			f->write<QuestDataOld>(oldData);
		}
		else
		{
			WriteSubrecord('DATA',sizeof(QuestData),f);
			f->write<QuestData>(data);
		}
		for (int i = 0;i < conditions.Count();i++)
		{
			WriteSubrecord('CTDA',sizeof(Condition),f);
			f->write<Condition>(conditions[i]);
		}
		for (int i = 0;i < oldConditions.Count();i++)
		{
			WriteSubrecord('CTDA',sizeof(ConditionOld),f);
			f->write<ConditionOld>(oldConditions[i]);
		}
		for (int i = 0;i < oldConditions2.Count();i++)
		{
			WriteSubrecord('CTDA',sizeof(ConditionOld2),f);
			f->write<ConditionOld2>(oldConditions2[i]);
		}
		for (int i = 0;i < stages.Count();i++)
		{
			WriteSubrecord('INDX',2,f);
			f->write<short>(stages[i]->index);
			for (int j = 0;j < stages[i]->logEntries.Count();j++)
			{
				WriteSubrecord('QSDT',1,f);
				f->write<ubyte>(stages[i]->logEntries[j]->flags);
				for (int k = 0;k < stages[i]->logEntries[j]->conditions.Count();k++)
				{
					WriteSubrecord('CTDA',sizeof(Condition),f);
					f->write<Condition>(stages[i]->logEntries[j]->conditions[k]);
				}
				for (int k = 0;k < stages[i]->logEntries[j]->oldConditions.Count();k++)
				{
					WriteSubrecord('CTDA',sizeof(ConditionOld),f);
					f->write<ConditionOld>(stages[i]->logEntries[j]->oldConditions[k]);
				}
				for (int k = 0;k < stages[i]->logEntries[j]->oldConditions2.Count();k++)
				{
					WriteSubrecord('CTDA',sizeof(ConditionOld2),f);
					f->write<ConditionOld2>(stages[i]->logEntries[j]->oldConditions2[k]);
				}
				WriteZStringSubrecord('CNAM',stages[i]->logEntries[j]->logEntry,f);
				ScriptSave((&stages[i]->logEntries[j]->script),this);
				if (stages[i]->logEntries[j]->nextQuest)
				{
					WriteSubrecord('NAM0',4,f);
					f->write<formid>(stages[i]->logEntries[j]->nextQuest);
				}
			}
		}
		for (int i = 0;i < objectives.Count();i++)
		{
			WriteSubrecord('QOBJ',4,f);
			f->write<long>(objectives[i]->index);
			WriteZStringSubrecord('NNAM',objectives[i]->description,f);
			for (int j = 0;j < objectives[i]->targets.Count();j++)
			{
				WriteSubrecord('QSTA',sizeof(Target),f);
				f->write<Target>(objectives[i]->targets[j].target);
				for (int k = 0;k < objectives[i]->targets[j].conditions.Count();k++)
				{
					WriteSubrecord('CTDA',sizeof(Condition),f);
					f->write<Condition>(objectives[i]->targets[j].conditions[k]);
				}
				for (int k = 0;k < objectives[i]->targets[j].oldConditions.Count();k++)
				{
					WriteSubrecord('CTDA',sizeof(ConditionOld),f);
					f->write<ConditionOld>(objectives[i]->targets[j].oldConditions[k]);
				}
				for (int k = 0;k < objectives[i]->targets[j].oldConditions2.Count();k++)
				{
					WriteSubrecord('CTDA',sizeof(ConditionOld2),f);
					f->write<ConditionOld2>(objectives[i]->targets[j].oldConditions2[k]);
				}
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		ScriptableGetSaveSize();
		FullNameGetSaveSize();
		TextureGetSaveSize(this);
		if (hasOldData)
		{
			size += ComputeSubrecordSize(sizeof(QuestDataOld));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(QuestData));
		}
		for (int i = 0;i < conditions.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(Condition));
		}
		for (int i = 0;i < oldConditions.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(ConditionOld));
		}
		for (int i = 0;i < oldConditions2.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(ConditionOld2));
		}
		for (int i = 0;i < stages.Count();i++)
		{
			size += ComputeSubrecordSize(2);
			for (int j = 0;j < stages[i]->logEntries.Count();j++)
			{
				size += ComputeSubrecordSize(1);
				for (int k = 0;k < stages[i]->logEntries[j]->conditions.Count();k++)
				{
					size += ComputeSubrecordSize(sizeof(Condition));
				}
				for (int k = 0;k < stages[i]->logEntries[j]->oldConditions.Count();k++)
				{
					size += ComputeSubrecordSize(sizeof(ConditionOld));
				}
				for (int k = 0;k < stages[i]->logEntries[j]->oldConditions2.Count();k++)
				{
					size += ComputeSubrecordSize(sizeof(ConditionOld2));
				}
				size += ZStringSubrecordSize(stages[i]->logEntries[j]->logEntry);
				ScriptGetSaveSize((&stages[i]->logEntries[j]->script),this);
				if (stages[i]->logEntries[j]->nextQuest)
				{
					size += ComputeSubrecordSize(4);
				}
			}
		}
		for (int i = 0;i < objectives.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			size += ZStringSubrecordSize(objectives[i]->description);
			for (int j = 0;j < objectives[i]->targets.Count();j++)
			{
				size += ComputeSubrecordSize(sizeof(Target));
				for (int k = 0;k < objectives[i]->targets[j].conditions.Count();k++)
				{
					size += ComputeSubrecordSize(sizeof(Condition));
				}
				for (int k = 0;k < objectives[i]->targets[j].oldConditions.Count();k++)
				{
					size += ComputeSubrecordSize(sizeof(ConditionOld));
				}
				for (int k = 0;k < objectives[i]->targets[j].oldConditions2.Count();k++)
				{
					size += ComputeSubrecordSize(sizeof(ConditionOld2));
				}
			}
		}
		return size;
	}
};
