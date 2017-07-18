/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "boundobjectform.h"
struct TerminalData
{
	ubyte difficulty;
	ubyte flags;
	ubyte server;
	ubyte pad;
};
#pragma pack(push, 1)
struct TerminalDataSmall
{
	ubyte difficulty;
	ubyte flags;
	ubyte server;
};
#pragma pack(pop)
class MenuItem : public Script
{
public:
	char *itemText;
	char *resultText;
	ubyte flags;
	formid displayNote;
	formid subMenu;
	SimpleDynVecClass<Condition> conditions;
	MenuItem() : itemText(0), resultText(0), displayNote(0), subMenu(0)
	{
	}
	virtual ~MenuItem()
	{
		if (itemText)
		{
			delete[] itemText;
		}
		if (resultText)
		{
			delete[] resultText;
		}
	}
	MenuItem & MenuItem::operator = (const MenuItem & that)
	{
		if (that.itemText)
		{
			itemText = newstr(that.itemText);
		}
		if (that.resultText)
		{
			resultText = newstr(that.resultText);
		}
		flags = that.flags;
		displayNote = that.displayNote;
		subMenu = that.subMenu;
		conditions = that.conditions;
		return *this;
	}
};
class TerminalForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Scriptable, public DestructibleObject, public Description
{
protected:
	formid loopSound;
	formid passwordNote;
	bool hasTerminalData;
	TerminalData data;
	TerminalDataSmall smallData;
	bool smallDataFound;
	SimpleDynVecClass<MenuItem *> menuItems;
public:
	TerminalForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), loopSound(0), passwordNote(0), hasTerminalData(false), smallDataFound(false)
	{
	}
	virtual ~TerminalForm()
	{
		for (int i = 0;i < menuItems.Count();i++)
		{
			delete menuItems[i];
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentItem = -1;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			BoundObjectFormLoad();
			FullNameLoad();
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
			ScriptableLoad();
			DestructibleObjectLoad();
			DescriptionLoad();
			case 'SNAM':
				loopSound = f->read<formid>();
				readSize += 4;
				break;
			case 'PNAM':
				passwordNote = f->read<formid>();
				readSize += 4;
				break;
			case 'DNAM':
				hasTerminalData = true;
				if (h.size == 3)
				{
					smallDataFound = true;
					smallData = f->read<TerminalDataSmall>();
					readSize += sizeof(TerminalDataSmall);
				}
				else
				{
					data = f->read<TerminalData>();
					readSize += sizeof(TerminalData);
				}
				break;
			case 'ITXT':
				currentItem++;
				menuItems.Add(new MenuItem());
				menuItems[currentItem]->itemText = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'RNAM':
				menuItems[currentItem]->resultText = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'ANAM':
				menuItems[currentItem]->flags = f->read<ubyte>();
				readSize += h.size;
				break;
			case 'INAM':
				menuItems[currentItem]->displayNote = f->read<formid>();
				readSize += h.size;
				break;
			case 'TNAM':
				menuItems[currentItem]->subMenu = f->read<formid>();
				readSize += h.size;
				break;
			ScriptLoad((menuItems[currentItem]));
			case 'CTDA':
				menuItems[currentItem]->conditions.Add(f->read<Condition>());
				readSize += sizeof(Condition);
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
		BoundObjectFormSave();
		FullNameSave();
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		ScriptableSave();
		DestructibleObjectSave();
		DescriptionSave();
		if (loopSound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(loopSound);
		}
		if (passwordNote)
		{
			WriteSubrecord('PNAM',4,f);
			f->write<formid>(passwordNote);
		}
		if (hasTerminalData)
		{
			if (smallDataFound)
			{
				WriteSubrecord('DNAM',sizeof(TerminalDataSmall),f);
				f->write<TerminalDataSmall>(smallData);
			}
			else
			{
				WriteSubrecord('DNAM',sizeof(TerminalData),f);
				f->write<TerminalData>(data);
			}
		}
		for (int i = 0;i < menuItems.Count();i++)
		{
			WriteZStringSubrecord('ITXT',menuItems[i]->itemText,f,true);
			WriteZStringSubrecord('RNAM',menuItems[i]->resultText,f,true);
			WriteSubrecord('ANAM',1,f);
			f->write<ubyte>(menuItems[i]->flags);
			if (menuItems[i]->displayNote)
			{
				WriteSubrecord('INAM',4,f);
				f->write<formid>(menuItems[i]->displayNote);
			}
			if (menuItems[i]->subMenu)
			{
				WriteSubrecord('TNAM',4,f);
				f->write<formid>(menuItems[i]->subMenu);
			}
			ScriptSave(menuItems[i],this);
			for (int j = 0;j < menuItems[i]->conditions.Count();j++)
			{
				WriteSubrecord('CTDA',sizeof(Condition),f);
				f->write<Condition>(menuItems[i]->conditions[j]);
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		ScriptableGetSaveSize();
		DestructibleObjectGetSaveSize();
		DescriptionGetSaveSize();
		if (loopSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (passwordNote)
		{
			size += ComputeSubrecordSize(4);
		}
		if (hasTerminalData)
		{
			if (smallDataFound)
			{
				size += ComputeSubrecordSize(sizeof(TerminalDataSmall));
			}
			else
			{
				size += ComputeSubrecordSize(sizeof(TerminalData));
			}
		}
		for (int i = 0;i < menuItems.Count();i++)
		{
			size += ZStringSubrecordSize(menuItems[i]->itemText,true);
			size += ZStringSubrecordSize(menuItems[i]->resultText,true);
			size += ComputeSubrecordSize(1);
			if (menuItems[i]->displayNote)
			{
				size += ComputeSubrecordSize(4);
			}
			if (menuItems[i]->subMenu)
			{
				size += ComputeSubrecordSize(4);
			}
			ScriptGetSaveSize(menuItems[i],this);
			for (int j = 0;j < menuItems[i]->conditions.Count();j++)
			{
				size += ComputeSubrecordSize(sizeof(Condition));
			}
		}
		return size;
	}
};
