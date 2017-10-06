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
struct DialogResponseData
{
	ubyte type;
	ubyte nextSpeaker;
	ubyte flags;
	ubyte pad;
};
#pragma pack(push, 1)
struct DialogResponseDataOld
{
	ubyte type;
	ubyte nextSpeaker;
	ubyte flags;
};
#pragma pack(pop)
struct DialogResponseEntryData
{
	ulong emotionType;
	long emotionValue;
	formid unk;
	ubyte responseNumber;
	formid sound;
	ubyte flags;
};
struct DialogResponseEntryDataSmall
{
	ulong emotionType;
	long emotionValue;
	formid unk;
	ubyte responseNumber;
	formid sound;
};
struct DialogResponseEntryDataTiny
{
	ulong emotionType;
	long emotionValue;
	formid unk;
	ubyte responseNumber;
};
struct DialogResponse
{
	DialogResponseEntryData data;
	DialogResponseEntryDataSmall smallData;
	DialogResponseEntryDataTiny tinyData;
	bool hasSmallData;
	bool hasTinyData;
	char *responseText;
	char *scriptNotes;
	char *edits;
	formid speakerAnimation;
	formid listenerAnimation;
	DialogResponse() : responseText(0), scriptNotes(0), edits(0), speakerAnimation(0), listenerAnimation(0), hasSmallData(false), hasTinyData(false)
	{
	}
	virtual ~DialogResponse()
	{
		if (responseText)
		{
			delete[] responseText;
		}
		if (scriptNotes)
		{
			delete[] scriptNotes;
		}
		if (edits)
		{
			delete[] edits;
		}
	}
};
struct Conditions
{
	Condition condition;
	ConditionOld conditionOld;
	ConditionOld2 conditionOld2;
	bool hasConditionOld;
	bool hasConditionOld2;
	Conditions() : hasConditionOld(false), hasConditionOld2(false)
	{
	}
};
class DialogResponseForm : public Form
{
protected:
	DialogResponseData data;
	DialogResponseDataOld oldData;
	bool hasOldData;
	formid quest;
	formid topic;
	formid previousInfo;
	SimpleDynVecClass<formid> names;
	SimpleDynVecClass<DialogResponse *> responses;
	SimpleDynVecClass<Conditions> conditions;
	SimpleDynVecClass<formid> choices;
	SimpleDynVecClass<formid> linkFromTopics;
	SimpleDynVecClass<formid> nextInfos;
	Script beginScript;
	Script endScript;
	formid sound;
	char *prompt;
	formid speaker;
	formid actorValue;
	ulong challenge;
	bool hasChallenge;
	bool hasPreviousInfo;
	bool hasEndScript;
public:
	DialogResponseForm(FormHeader h,ModFile *f) : Form(h,f), quest(0), topic(0), previousInfo(0), sound(0), prompt(0), speaker(0), actorValue(0), hasPreviousInfo(false), hasOldData(false), hasEndScript(false), hasChallenge(false)
	{
	}
	virtual ~DialogResponseForm()
	{
		if (prompt)
		{
			delete[] prompt;
		}
		for (int i = 0;i < responses.Count();i++)
		{
			delete responses[i];
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentResponse = -1;
		Script *script = &beginScript;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			case 'DATA':
				if (h.size == sizeof(DialogResponseData))
				{
					data = f->read<DialogResponseData>();
					readSize += sizeof(DialogResponseData);
				}
				else
				{
					hasOldData = true;
					oldData = f->read<DialogResponseDataOld>();
					readSize += sizeof(DialogResponseDataOld);
				}
				break;
			case 'QSTI':
				quest = f->read<formid>();
				readSize += 4;
				break;
			case 'TPIC':
				topic = f->read<formid>();
				readSize += 4;
				break;
			case 'PNAM':
				hasPreviousInfo = true;
				previousInfo = f->read<formid>();
				readSize += 4;
				break;
			case 'NAME':
				names.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'TRDT':
				currentResponse++;
				responses.Add(new DialogResponse());
				if (h.size == sizeof(DialogResponseEntryData))
				{
					responses[currentResponse]->data = f->read<DialogResponseEntryData>();
					readSize += sizeof(DialogResponseEntryData);
				}
				else if (h.size == sizeof(DialogResponseEntryDataSmall))
				{
					responses[currentResponse]->hasSmallData = true;
					responses[currentResponse]->smallData = f->read<DialogResponseEntryDataSmall>();
					readSize += sizeof(DialogResponseEntryDataSmall);
				}
				else
				{
					responses[currentResponse]->hasTinyData = true;
					responses[currentResponse]->tinyData = f->read<DialogResponseEntryDataTiny>();
					readSize += sizeof(DialogResponseEntryDataTiny);
				}
				break;
			case 'NAM1':
				responses[currentResponse]->responseText = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'NAM2':
				responses[currentResponse]->scriptNotes = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'NAM3':
				responses[currentResponse]->edits = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SNAM':
				responses[currentResponse]->speakerAnimation = f->read<formid>();
				readSize += 4;
				break;
			case 'LNAM':
				responses[currentResponse]->listenerAnimation = f->read<formid>();
				readSize += 4;
				break;
			case 'CTDA':
				if (h.size == sizeof(Condition))
				{
					Conditions c;
					c.condition = f->read<Condition>();
					conditions.Add(c);
					readSize += sizeof(Condition);
				}
				else if (h.size == sizeof(ConditionOld))
				{
					Conditions c;
					c.conditionOld = f->read<ConditionOld>();
					c.hasConditionOld = true;
					conditions.Add(c);
					readSize += sizeof(ConditionOld);
				}
				else if (h.size == sizeof(ConditionOld2))
				{
					Conditions c;
					c.conditionOld2 = f->read<ConditionOld2>();
					c.hasConditionOld2 = true;
					conditions.Add(c);
					readSize += sizeof(ConditionOld2);
				}
				break;
			case 'TCLT':
				choices.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'TCLF':
				linkFromTopics.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'TCFU':
				nextInfos.Add(f->read<formid>());
				readSize += 4;
				break;
			ScriptLoad(script);
			case 'NEXT':
				hasEndScript = true;
				script = &endScript;
				break;
			case 'SNDD':
				sound = f->read<formid>();
				readSize += 4;
				break;
			case 'RNAM':
				prompt = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'ANAM':
				speaker = f->read<formid>();
				readSize += 4;
				break;
			case 'KNAM':
				actorValue = f->read<formid>();
				readSize += 4;
				break;
			case 'DNAM':
				hasChallenge = true;
				challenge = f->read<ulong>();
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
		if (hasOldData)
		{
			WriteSubrecord('DATA',sizeof(DialogResponseDataOld),f);
			f->write<DialogResponseDataOld>(oldData);
		}
		else
		{
			WriteSubrecord('DATA',sizeof(DialogResponseData),f);
			f->write<DialogResponseData>(data);
		}
		if (quest)
		{
			WriteSubrecord('QSTI',4,f);
			f->write<formid>(quest);
		}
		if (topic)
		{
			WriteSubrecord('TPIC',4,f);
			f->write<formid>(topic);
		}
		if (hasPreviousInfo)
		{
			WriteSubrecord('PNAM',4,f);
			f->write<formid>(previousInfo);
		}
		if (header.flags & 0x20)
		{
			return;
		}
		for (int i = 0;i < names.Count();i++)
		{
			WriteSubrecord('NAME',4,f);
			f->write<formid>(names[i]);
		}
		for (int i = 0;i < responses.Count();i++)
		{
			if (responses[i]->hasSmallData)
			{
				WriteSubrecord('TRDT',sizeof(DialogResponseEntryDataSmall),f);
				f->write<DialogResponseEntryDataSmall>(responses[i]->smallData);
			}
			else if (responses[i]->hasTinyData)
			{
				WriteSubrecord('TRDT',sizeof(DialogResponseEntryDataTiny),f);
				f->write<DialogResponseEntryDataTiny>(responses[i]->tinyData);
			}
			else
			{
				WriteSubrecord('TRDT',sizeof(DialogResponseEntryData),f);
				f->write<DialogResponseEntryData>(responses[i]->data);
			}
			WriteZStringSubrecord('NAM1',responses[i]->responseText,f);
			WriteZStringSubrecord('NAM2',responses[i]->scriptNotes,f);
			WriteZStringSubrecord('NAM3',responses[i]->edits,f);
			if (responses[i]->speakerAnimation)
			{
				WriteSubrecord('SNAM',4,f);
				f->write<formid>(responses[i]->speakerAnimation);
			}
			if (responses[i]->listenerAnimation)
			{
				WriteSubrecord('LNAM',4,f);
				f->write<formid>(responses[i]->listenerAnimation);
			}
		}
		for (int conditioncount = 0;conditioncount < conditions.Count();conditioncount++)
		{
			if (conditions[conditioncount].hasConditionOld)
			{
				WriteSubrecord('CTDA',sizeof(ConditionOld),f);
				f->write<ConditionOld>(conditions[conditioncount].conditionOld);
			}
			else if (conditions[conditioncount].hasConditionOld2)
			{
				WriteSubrecord('CTDA',sizeof(ConditionOld2),f);
				f->write<ConditionOld2>(conditions[conditioncount].conditionOld2);
			}
			else
			{
				WriteSubrecord('CTDA',sizeof(Condition),f);
				f->write<Condition>(conditions[conditioncount].condition);
			}
		}
		for (int i = 0;i < choices.Count();i++)
		{
			WriteSubrecord('TCLT',4,f);
			f->write<formid>(choices[i]);
		}
		for (int i = 0;i < linkFromTopics.Count();i++)
		{
			WriteSubrecord('TCLF',4,f);
			f->write<formid>(linkFromTopics[i]);
		}
		for (int i = 0;i < nextInfos.Count();i++)
		{
			WriteSubrecord('TCFU',4,f);
			f->write<formid>(nextInfos[i]);
		}
		ScriptSave((&beginScript),this);
		if (hasEndScript)
		{
			WriteSubrecord('NEXT',0,f);
			ScriptSave((&endScript),this);
		}
		WriteZStringSubrecord('RNAM',prompt,f);
		if (speaker)
		{
			WriteSubrecord('ANAM',4,f);
			f->write<formid>(speaker);
		}
		if (actorValue)
		{
			WriteSubrecord('KNAM',4,f);
			f->write<formid>(actorValue);
		}
		if (hasChallenge)
		{
			WriteSubrecord('DNAM',4,f);
			f->write<ulong>(challenge);
		}
		if (sound)
		{
			WriteSubrecord('SNDD',4,f);
			f->write<formid>(sound);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		if (hasOldData)
		{
			size += ComputeSubrecordSize(sizeof(DialogResponseDataOld));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(DialogResponseData));
		}
		if (quest)
		{
			size += ComputeSubrecordSize(4);
		}
		if (topic)
		{
			size += ComputeSubrecordSize(4);
		}
		if (hasPreviousInfo)
		{
			size += ComputeSubrecordSize(4);
		}
		if (header.flags & 0x20)
		{
			return size;
		}
		for (int i = 0;i < names.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < responses.Count();i++)
		{
			if (responses[i]->hasSmallData)
			{
				size += ComputeSubrecordSize(sizeof(DialogResponseEntryDataSmall));
			}
			else if (responses[i]->hasTinyData)
			{
				size += ComputeSubrecordSize(sizeof(DialogResponseEntryDataTiny));
			}
			else
			{
				size += ComputeSubrecordSize(sizeof(DialogResponseEntryData));
			}
			size += ZStringSubrecordSize(responses[i]->responseText);
			size += ZStringSubrecordSize(responses[i]->scriptNotes);
			size += ZStringSubrecordSize(responses[i]->edits);
			if (responses[i]->speakerAnimation)
			{
				size += ComputeSubrecordSize(4);
			}
			if (responses[i]->listenerAnimation)
			{
				size += ComputeSubrecordSize(4);
			}
		}
		for (int conditioncount = 0;conditioncount < conditions.Count();conditioncount++)
		{
			if (conditions[conditioncount].hasConditionOld)
			{
				size += ComputeSubrecordSize(sizeof(ConditionOld));
			}
			else if (conditions[conditioncount].hasConditionOld2)
			{
				size += ComputeSubrecordSize(sizeof(ConditionOld2));
			}
			else
			{
				size += ComputeSubrecordSize(sizeof(Condition));
			}
		}
		for (int i = 0;i < choices.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < linkFromTopics.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < nextInfos.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		ScriptGetSaveSize((&beginScript),this);
		if (hasEndScript)
		{
			size += ComputeSubrecordSize(0);
			ScriptGetSaveSize((&endScript),this);
		}
		size += ZStringSubrecordSize(prompt);
		if (speaker)
		{
			size += ComputeSubrecordSize(4);
		}
		if (actorValue)
		{
			size += ComputeSubrecordSize(4);
		}
		if (hasChallenge)
		{
			size += ComputeSubrecordSize(4);
		}
		if (sound)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
