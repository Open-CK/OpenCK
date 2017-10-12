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
struct BodyPartData
{
	float damageMultiplier;
	ubyte flags;
	ubyte partType;
	ubyte heapthPercent;
	ubyte actorValue;
	ubyte toHitChance;
	ubyte explosionChance;
	ubyte explosionDebrisCount;
	formid explosionDebris;
	formid explosion;
	float trackingMaxAngle;
	float explosionDebrisScale;
	ubyte severableDebrisCount;
	formid severableDebris;
	formid severableDebrisExplosion;
	float severableDebrisScale;
	NiPoint3 goreEffectsTranslation;
	NiPoint3 goreEffectsRotation;
	formid severableImpactDataset;
	formid explodableImpactDataset;
	ubyte severableDecalCount;
	ubyte explodableDecalCount;
	float limbReplacementScale;
};
struct BodyPart
{
	char *partNode;
	char *vatsTarget;
	char *ikStartNode;
	char *partName;
	char *goreEffectsTargetBone;
	char *limbReplacementModel;
	char *poseMatchingModel;
	BodyPartData data;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	BodyPart() : partNode(0), vatsTarget(0), ikStartNode(0), partName(0), goreEffectsTargetBone(0), limbReplacementModel(0), poseMatchingModel(0), textureHashesCount(0), textureHashes(0)
	{
	}
	virtual ~BodyPart()
	{
		if (partNode)
		{
			delete[] partNode;
		}
		if (vatsTarget)
		{
			delete[] vatsTarget;
		}
		if (ikStartNode)
		{
			delete[] ikStartNode;
		}
		if (partName)
		{
			delete[] partName;
		}
		if (goreEffectsTargetBone)
		{
			delete[] goreEffectsTargetBone;
		}
		if (limbReplacementModel)
		{
			delete[] limbReplacementModel;
		}
		if (poseMatchingModel)
		{
			delete[] poseMatchingModel;
		}
		if (textureHashes)
		{
			delete[] textureHashes;
		}
	}
};
class BodyPartDataForm : public Form, public Model
{
protected:
	SimpleDynVecClass<BodyPart *> bodyParts;
	formid ragDoll;
public:
	BodyPartDataForm(FormHeader h,ModFile *f) : Form(h,f), ragDoll(0)
	{
	}
	~BodyPartDataForm()
	{
		for (int i = 0;i < bodyParts.Count();i++)
		{
			delete bodyParts[i];
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentPart = -1;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			ModelBRLoad(this,'MODL','MODB','MODT');
			case 'BPTN':
				currentPart++;
				bodyParts.Add(new BodyPart());
				bodyParts[currentPart]->partName = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'PNAM':
				bodyParts[currentPart]->poseMatchingModel = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'BPNN':
				if (currentPart == -1)
				{
					currentPart++;
					bodyParts.Add(new BodyPart());
				}
				bodyParts[currentPart]->partNode = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'BPNT':
				bodyParts[currentPart]->vatsTarget = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'BPNI':
				bodyParts[currentPart]->ikStartNode = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'BPND':
				bodyParts[currentPart]->data = f->read<BodyPartData>();
				readSize += sizeof(BodyPartData);
				break;
			case 'NAM1':
				bodyParts[currentPart]->limbReplacementModel = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'NAM4':
				bodyParts[currentPart]->goreEffectsTargetBone = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'NAM5':
				bodyParts[currentPart]->textureHashesCount = h.size / sizeof(TextureHash);
				bodyParts[currentPart]->textureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
				readSize += h.size;
				break;
			case 'RAGA':
				ragDoll = f->read<formid>();
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
		ModelBRSave(this,'MODL','MODB','MODT');
		for (int currentPart = 0;currentPart < bodyParts.Count();currentPart++)
		{
			WriteZStringSubrecord('BPTN',bodyParts[currentPart]->partName,f);
			WriteZStringSubrecord('PNAM',bodyParts[currentPart]->poseMatchingModel,f);
			WriteZStringSubrecord('BPNN',bodyParts[currentPart]->partNode,f);
			WriteZStringSubrecord('BPNT',bodyParts[currentPart]->vatsTarget,f);
			WriteZStringSubrecord('BPNI',bodyParts[currentPart]->ikStartNode,f);
			WriteSubrecord('BPND',sizeof(BodyPartData),f);
			f->write<BodyPartData>(bodyParts[currentPart]->data);
			WriteZStringSubrecord('NAM1',bodyParts[currentPart]->limbReplacementModel,f);
			WriteZStringSubrecord('NAM4',bodyParts[currentPart]->goreEffectsTargetBone,f);
			WriteSubrecord('NAM5',bodyParts[currentPart]->textureHashesCount * sizeof(TextureHash),f);
			if (bodyParts[currentPart]->textureHashesCount)
			{
				f->writearray<TextureHash>(bodyParts[currentPart]->textureHashesCount,bodyParts[currentPart]->textureHashes);
			}
		}
		if (ragDoll)
		{
			WriteSubrecord('RAGA',4,f);
			f->write<formid>(ragDoll);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		ModelBRGetSaveSize(this);
		for (int currentPart = 0;currentPart < bodyParts.Count();currentPart++)
		{
			size += ZStringSubrecordSize(bodyParts[currentPart]->partName);
			size += ZStringSubrecordSize(bodyParts[currentPart]->poseMatchingModel);
			size += ZStringSubrecordSize(bodyParts[currentPart]->partNode);
			size += ZStringSubrecordSize(bodyParts[currentPart]->vatsTarget);
			size += ZStringSubrecordSize(bodyParts[currentPart]->ikStartNode);
			size += ComputeSubrecordSize(sizeof(BodyPartData));
			size += ZStringSubrecordSize(bodyParts[currentPart]->limbReplacementModel);
			size += ZStringSubrecordSize(bodyParts[currentPart]->goreEffectsTargetBone);
			size += ComputeSubrecordSize(bodyParts[currentPart]->textureHashesCount * sizeof(TextureHash));
		}
		if (ragDoll)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
