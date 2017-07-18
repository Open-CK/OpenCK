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
class NoteForm : public BoundObjectForm, public Model, public FullName, public Texture, public PickupPutdownSounds
{
protected:
	ubyte type;
	SimpleDynVecClass<formid> quests;
	char *noteTexture;
	char *text;
	formid topic;
	formid sound;
public:
	NoteForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), noteTexture(0), text(0), topic(0), sound(0)
	{
	}
	virtual ~NoteForm()
	{
		if (noteTexture)
		{
			delete[] noteTexture;
		}
		if (text)
		{
			delete[] text;
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
			BoundObjectFormLoad();
			FullNameLoad();
			ModelBRLoad(this,'MODL','MODB','MODT');
			TextureLoad(this,'ICON');
			PickupPutdownSoundsLoad();
			case 'DATA':
				type = f->read<ubyte>();
				readSize += 1;
				break;
			case 'ONAM':
				quests.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'SNAM':
				sound = f->read<formid>();
				readSize += 4;
				break;
			case 'TNAM':
				if (type == 1)
				{
					text = f->readzstring(h.size);
					readSize += h.size;
					break;
				}
				else if (type == 3)
				{
					topic = f->read<formid>();
					readSize += 4;
					break;
				}
				break;
			case 'XNAM':
				noteTexture = f->readzstring(h.size);
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
		BoundObjectFormSave();
		FullNameSave();
		ModelBRSave(this,'MODL','MODB','MODT');
		TextureSave(this,'ICON');
		PickupPutdownSoundsSave();
		WriteSubrecord('DATA',1,f);
		f->write<ubyte>(type);
		for (int i = 0;i < quests.Count();i++)
		{
			WriteSubrecord('ONAM',4,f);
			f->write<formid>(quests[i]);
		}
		switch (type)
		{
		case 0:
			if (sound)
			{
				WriteSubrecord('SNAM',4,f);
				f->write<formid>(sound);
			}
			break;
		case 1:
			WriteZStringSubrecord('TNAM',text,f);
			break;
		case 2:
			WriteZStringSubrecord('XNAM',noteTexture,f);
			break;
		case 3:
			if (topic)
			{
				WriteSubrecord('TNAM',4,f);
				f->write<formid>(topic);
			}
			if (sound)
			{
				WriteSubrecord('SNAM',4,f);
				f->write<formid>(sound);
			}
			break;
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelBRGetSaveSize(this);
		TextureGetSaveSize(this);
		PickupPutdownSoundsGetSaveSize();
		size += ComputeSubrecordSize(1);
		for (int i = 0;i < quests.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		switch (type)
		{
		case 0:
			if (sound)
			{
				size += ComputeSubrecordSize(4);
			}
			break;
		case 1:
			size += ZStringSubrecordSize(text);
			break;
		case 2:
			size += ZStringSubrecordSize(noteTexture);
			break;
		case 3:
			if (topic)
			{
				size += ComputeSubrecordSize(4);
			}
			if (sound)
			{
				size += ComputeSubrecordSize(4);
			}
			break;
		}
		return size;
	}
};
