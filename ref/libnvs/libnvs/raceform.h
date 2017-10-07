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
struct RaceSkill
{
	ubyte value;
	ubyte boost;
};
struct RaceData
{
	RaceSkill skills[7];
	float maleScale;
	float femaleScale;
	float maleWeight;
	float femaleWeight;
	ulong flags;
};
struct RaceBodyPart
{
	ulong index;
	Model model;
	ModelFaceGenFlags faceGenFlags;
	Texture icon;
};
class RaceForm : public Form, public FullName, public Description, public SpellList, public Reaction
{
protected:
	RaceData data;
	formid olderRace;
	formid youngerRace;
	formid voiceType[2];
	formid defaultHair[2];
	ubyte defaultHairColor[2];
	float mainClamp;
	float faceClamp;
	ulong attributesSize;
	ubyte *attributes;
	RaceBodyPart headParts[16];
	RaceBodyPart bodyParts[8];
	ulong hairCount;
	formid *hairs;
	ulong eyeCount;
	formid *eyes;
	ulong fggsSize[2];
	byte *fggs[2];
	ulong fggaSize[2];
	byte *fgga[2];
	ulong fgtsSize[2];
	byte *fgts[2];
	ushort snam[2];
public:
	RaceForm(FormHeader h,ModFile *f) : Form(h,f), olderRace(0), youngerRace(0), attributesSize(0), attributes(0), hairCount(0), hairs(0), eyeCount(0), eyes(0)
	{
		voiceType[0] = 0;
		voiceType[1] = 0;
		defaultHair[0] = 0;
		defaultHair[1] = 0;
		fggsSize[0] = 0;
		fggsSize[1] = 0;
		fggs[0] = 0;
		fggs[1] = 0;
		fggaSize[0] = 0;
		fggaSize[1] = 0;
		fgga[0] = 0;
		fgga[1] = 0;
		fgtsSize[0] = 0;
		fgtsSize[1] = 0;
		fgts[0] = 0;
		fgts[1] = 0;
	}
	virtual ~RaceForm()
	{
		if (hairs)
		{
			delete[] hairs;
		}
		if (eyes)
		{
			delete[] eyes;
		}
		if (fggs[0])
		{
			delete[] fggs[0];
		}
		if (fgga[0])
		{
			delete[] fgga[0];
		}
		if (fgts[0])
		{
			delete[] fgts[0];
		}
		if (fggs[1])
		{
			delete[] fggs[1];
		}
		if (fgga[1])
		{
			delete[] fgga[1];
		}
		if (fgts[1])
		{
			delete[] fgts[1];
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		RaceBodyPart *currentParts = headParts;
		int partCount = 0;
		int currentSex = 0;
		int currentPart = -1;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			FullNameLoad();
			DescriptionLoad();
			SpellListLoad();
			ReactionLoad();
			case 'DATA':
				data = f->read<RaceData>();
				readSize += sizeof(RaceData);
				break;
			case 'ONAM':
				olderRace = f->read<formid>();
				readSize += 4;
				break;
			case 'YNAM':
				youngerRace = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM2':
				break;
			case 'VTCK':
				voiceType[0] = f->read<formid>();
				voiceType[1] = f->read<formid>();
				readSize += 8;
				break;
			case 'DNAM':
				defaultHair[0] = f->read<formid>();
				defaultHair[1] = f->read<formid>();
				readSize += 8;
				break;
			case 'CNAM':
				defaultHairColor[0] = f->read<ubyte>();
				defaultHairColor[1] = f->read<ubyte>();
				readSize += 2;
				break;
			case 'PNAM':
				mainClamp = f->read<float>();
				readSize += 4;
				break;
			case 'UNAM':
				faceClamp = f->read<float>();
				readSize += 4;
				break;
			case 'ATTR':
				attributesSize = h.size;
				attributes = f->readarray<ubyte>(h.size);;
				readSize += h.size;;
				break;
			case 'NAM0':
				currentParts = headParts;
				partCount = 8;
				break;
			case 'MNAM':
				currentSex = 0;
				currentPart = -1;
				break;
			case 'FNAM':
				currentSex = 1;
				currentPart = -1;
				break;
			case 'INDX':
				currentPart++;
				currentParts[(partCount * currentSex) + currentPart].index = f->read<ulong>();
				readSize += 4;
				break;
			ModelBRLoad((&currentParts[(partCount * currentSex) + currentPart].model),'MODL','MODB','MODT');
			ModelFaceGenFlagsLoad((&currentParts[(partCount * currentSex) + currentPart].faceGenFlags),'MODD');
			TextureLoad((&currentParts[(partCount * currentSex) + currentPart].icon),'ICON');
			case 'NAM1':
				currentParts = bodyParts;
				partCount = 4;
				break;
			case 'HNAM':
				hairCount = h.size / 4;
				hairs = f->readarray<formid>(hairCount);
				readSize += h.size;
				break;
			case 'ENAM':
				eyeCount = h.size / 4;
				eyes = f->readarray<formid>(eyeCount);
				readSize += h.size;
				break;
			case 'FGGS':
				fggsSize[currentSex] = h.size;
				fggs[currentSex] = f->readarray<byte>(fggsSize[currentSex]);
				readSize += h.size;
				break;
			case 'FGGA':
				fggaSize[currentSex] = h.size;
				fgga[currentSex] = f->readarray<byte>(fggaSize[currentSex]);
				readSize += h.size;
				break;
			case 'FGTS':
				fgtsSize[currentSex] = h.size;
				fgts[currentSex] = f->readarray<byte>(fgtsSize[currentSex]);
				readSize += h.size;
				break;
			case 'SNAM':
				snam[currentSex] = f->read<ushort>();
				readSize += 2;
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
		DescriptionSave();
		SpellListSave();
		ReactionSave();
		WriteSubrecord('DATA',sizeof(RaceData),f);
		f->write<RaceData>(data);
		if (olderRace)
		{
			WriteSubrecord('ONAM',4,f);
			f->write<formid>(olderRace);
		}
		if (youngerRace)
		{
			WriteSubrecord('YNAM',4,f);
			f->write<formid>(youngerRace);
		}
		WriteSubrecord('NAM2',0,f);
		if (voiceType[0] || voiceType[1])
		{
			WriteSubrecord('VTCK',8,f);
			f->write<formid>(voiceType[0]);
			f->write<formid>(voiceType[1]);
		}
		if (defaultHair[0] || defaultHair[1])
		{
			WriteSubrecord('DNAM',8,f);
			f->write<formid>(defaultHair[0]);
			f->write<formid>(defaultHair[1]);
		}
		WriteSubrecord('CNAM',2,f);
		f->write<ubyte>(defaultHairColor[0]);
		f->write<ubyte>(defaultHairColor[1]);
		WriteSubrecord('PNAM',4,f);
		f->write<float>(mainClamp);
		WriteSubrecord('UNAM',4,f);
		f->write<float>(faceClamp);
		if (attributes)
		{
			WriteSubrecord('ATTR',attributesSize,f);
			f->writearray<ubyte>(attributesSize,attributes);
		}
		WriteSubrecord('NAM0',0,f);
		WriteSubrecord('MNAM',0,f);
		for (int i = 0;i < 8;i++)
		{
			WriteSubrecord('INDX',4,f);
			f->write<ulong>(headParts[i].index);
			ModelBRSave((&headParts[i].model),'MODL','MODB','MODT');
			ModelFaceGenFlagsSave((&headParts[i].faceGenFlags),'MODD');
			TextureSave((&headParts[i].icon),'ICON');
		}
		WriteSubrecord('FNAM',0,f);
		for (int i = 0;i < 8;i++)
		{
			WriteSubrecord('INDX',4,f);
			f->write<ulong>(headParts[i+8].index);
			ModelBRSave((&headParts[i+8].model),'MODL','MODB','MODT');
			ModelFaceGenFlagsSave((&headParts[i+8].faceGenFlags),'MODD');
			TextureSave((&headParts[i+8].icon),'ICON');
		}
		WriteSubrecord('NAM1',0,f);
		WriteSubrecord('MNAM',0,f);
		for (int i = 0;i < 4;i++)
		{
			WriteSubrecord('INDX',4,f);
			f->write<ulong>(bodyParts[i].index);
			TextureSave((&bodyParts[i].icon),'ICON');
			ModelBRSave((&bodyParts[i].model),'MODL','MODB','MODT');
			ModelFaceGenFlagsSave((&bodyParts[i].faceGenFlags),'MODD');
		}
		WriteSubrecord('FNAM',0,f);
		for (int i = 0;i < 4;i++)
		{
			WriteSubrecord('INDX',4,f);
			f->write<ulong>(bodyParts[i+4].index);
			TextureSave((&bodyParts[i+4].icon),'ICON');
			ModelBRSave((&bodyParts[i+4].model),'MODL','MODB','MODT');
			ModelFaceGenFlagsSave((&bodyParts[i+4].faceGenFlags),'MODD');
		}
		WriteSubrecord('HNAM',hairCount * 4,f);
		if (hairs)
		{
			f->writearray<formid>(hairCount,hairs);
		}
		WriteSubrecord('ENAM',eyeCount * 4,f);
		if (eyes)
		{
			f->writearray<formid>(eyeCount,eyes);
		}
		WriteSubrecord('MNAM',0,f);
		if (fggsSize[0])
		{
			WriteSubrecord('FGGS',fggsSize[0],f);
			f->writearray<byte>(fggsSize[0],fggs[0]);
		}
		if (fggaSize[0])
		{
			WriteSubrecord('FGGA',fggaSize[0],f);
			f->writearray<byte>(fggaSize[0],fgga[0]);
		}
		if (fgtsSize[0])
		{
			WriteSubrecord('FGTS',fgtsSize[0],f);
			f->writearray<byte>(fgtsSize[0],fgts[0]);
		}
		WriteSubrecord('SNAM',2,f);
		f->write<ushort>(snam[0]);
		WriteSubrecord('FNAM',0,f);
		if (fggsSize[1])
		{
			WriteSubrecord('FGGS',fggsSize[1],f);
			f->writearray<byte>(fggsSize[1],fggs[1]);
		}
		if (fggaSize[1])
		{
			WriteSubrecord('FGGA',fggaSize[1],f);
			f->writearray<byte>(fggaSize[1],fgga[1]);
		}
		if (fgtsSize[1])
		{
			WriteSubrecord('FGTS',fgtsSize[1],f);
			f->writearray<byte>(fgtsSize[1],fgts[1]);
		}
		WriteSubrecord('SNAM',2,f);
		f->write<ushort>(snam[1]);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		DescriptionGetSaveSize();
		SpellListGetSaveSize();
		ReactionGetSaveSize();
		size += ComputeSubrecordSize(sizeof(RaceData));
		if (olderRace)
		{
			size += ComputeSubrecordSize(4);
		}
		if (youngerRace)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(0);
		if (voiceType[0] || voiceType[1])
		{
			size += ComputeSubrecordSize(8);
		}
		if (defaultHair[0] || defaultHair[1])
		{
			size += ComputeSubrecordSize(8);
		}
		size += ComputeSubrecordSize(2);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		if (attributes)
		{
			size += ComputeSubrecordSize(attributesSize);
		}
		size += ComputeSubrecordSize(0);
		size += ComputeSubrecordSize(0);
		for (int i = 0;i < 8;i++)
		{
			size += ComputeSubrecordSize(4);
			ModelBRGetSaveSize((&headParts[i].model));
			ModelFaceGenFlagsGetSaveSize((&headParts[i].faceGenFlags));
			TextureGetSaveSize((&headParts[i].icon));
		}
		size += ComputeSubrecordSize(0);
		for (int i = 0;i < 8;i++)
		{
			size += ComputeSubrecordSize(4);
			ModelBRGetSaveSize((&headParts[i+8].model));
			ModelFaceGenFlagsGetSaveSize((&headParts[i+8].faceGenFlags));
			TextureGetSaveSize((&headParts[i+8].icon));
		}
		size += ComputeSubrecordSize(0);
		size += ComputeSubrecordSize(0);
		for (int i = 0;i < 4;i++)
		{
			size += ComputeSubrecordSize(4);
			ModelBRGetSaveSize((&bodyParts[i].model));
			ModelFaceGenFlagsGetSaveSize((&bodyParts[i].faceGenFlags));
			TextureGetSaveSize((&bodyParts[i].icon));
		}
		size += ComputeSubrecordSize(0);
		for (int i = 0;i < 4;i++)
		{
			size += ComputeSubrecordSize(4);
			TextureGetSaveSize((&bodyParts[i+4].icon));
			ModelBRGetSaveSize((&bodyParts[i+4].model));
			ModelFaceGenFlagsGetSaveSize((&bodyParts[i+4].faceGenFlags));
		}
		size += ComputeSubrecordSize(hairCount * 4);
		size += ComputeSubrecordSize(eyeCount * 4);
		size += ComputeSubrecordSize(0);
		if (fggsSize[0])
		{
			size += ComputeSubrecordSize(fggsSize[0]);
		}
		if (fggaSize[0])
		{
			size += ComputeSubrecordSize(fggaSize[0]);
		}
		if (fgtsSize[0])
		{
			size += ComputeSubrecordSize(fgtsSize[0]);
		}
		size += ComputeSubrecordSize(2);
		size += ComputeSubrecordSize(0);
		if (fggsSize[1])
		{
			size += ComputeSubrecordSize(fggsSize[1]);
		}
		if (fggaSize[1])
		{
			size += ComputeSubrecordSize(fggaSize[1]);
		}
		if (fgtsSize[1])
		{
			size += ComputeSubrecordSize(fgtsSize[1]);
		}
		size += ComputeSubrecordSize(2);
		return size;
	}
};
