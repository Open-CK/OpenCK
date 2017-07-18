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
struct CasinoData
{
	float deckPerc;
	float blackjackPayout;
	ulong slotStopSymbol1;
	ulong slotStopSymbol2;
	ulong slotStopSymbol3;
	ulong slotStopSymbol4;
	ulong slotStopSymbol5;
	ulong slotStopSymbol6;
	ulong slotStopSymbolW;
	ulong deckCount;
	ulong maxWinnings;
	formid currency;
	formid winningsQuest;
	ulong flags;
};
class CasinoForm : public Form, public FullName
{
protected:
	CasinoData data;
	SimpleDynVecClass<char *> models;
	char *slotMachine;
	char *blackjackTable;
	char *rouletteTable;
	SimpleDynVecClass<char *> reelTextures;
	SimpleDynVecClass<char *> deckTextures;
public:
	CasinoForm(FormHeader h,ModFile *f) : Form(h,f), slotMachine(0), blackjackTable(0), rouletteTable(0)
	{
	}
	~CasinoForm()
	{
		for (int i = 0;i < models.Count();i++)
		{
			delete[] models[i];
		}
		if (slotMachine)
		{
			delete[] slotMachine;
		}
		if (blackjackTable)
		{
			delete[] blackjackTable;
		}
		for (int i = 0;i < reelTextures.Count();i++)
		{
			delete[] reelTextures[i];
		}
		for (int i = 0;i < deckTextures.Count();i++)
		{
			delete[] deckTextures[i];
		}
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
			FullNameLoad();
			case 'DATA':
				data = f->read<CasinoData>();
				readSize += sizeof(CasinoData);
				break;
			case 'MODL':
				models.Add(f->readzstring(h.size));
				readSize += h.size;
				break;
			case 'MOD2':
				slotMachine = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MOD3':
				blackjackTable = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MOD4':
				rouletteTable = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'ICON':
				reelTextures.Add(f->readzstring(h.size));
				readSize += h.size;
				break;
			case 'ICO2':
				deckTextures.Add(f->readzstring(h.size));
				readSize += h.size;
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
		WriteSubrecord('DATA',sizeof(CasinoData),f);
		f->write<CasinoData>(data);
		for (int i = 0;i < models.Count();i++)
		{
			WriteZStringSubrecord('MODL',models[i],f);
		}
		WriteZStringSubrecord('MOD2',slotMachine,f);
		WriteZStringSubrecord('MOD3',blackjackTable,f);
		WriteZStringSubrecord('MOD4',rouletteTable,f);
		for (int i = 0;i < reelTextures.Count();i++)
		{
			WriteZStringSubrecord('ICON',reelTextures[i],f);
		}
		for (int i = 0;i < deckTextures.Count();i++)
		{
			WriteZStringSubrecord('ICO2',deckTextures[i],f);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		size += ComputeSubrecordSize(sizeof(CasinoData));
		for (int i = 0;i < models.Count();i++)
		{
			size += ZStringSubrecordSize(models[i]);
		}
		size += ZStringSubrecordSize(slotMachine);
		size += ZStringSubrecordSize(blackjackTable);
		size += ZStringSubrecordSize(rouletteTable);
		for (int i = 0;i < reelTextures.Count();i++)
		{
			size += ZStringSubrecordSize(reelTextures[i]);
		}
		for (int i = 0;i < deckTextures.Count();i++)
		{
			size += ZStringSubrecordSize(deckTextures[i]);
		}
		return size;
	}
};
