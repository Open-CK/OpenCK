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
struct RagdollData
{
	ushort dynamicBoneCount;
	ushort legSystemsCount;
	ushort bodySystemsCount;
	ushort headSystemsCount;
	ubyte feedbackEnabled;
	ubyte footIKEanbled;
	ubyte lookIKEnabled;
	ubyte grabIKEnabled;
	ubyte poseMatching;
	ubyte unk;
};
struct RagdollFeedbackData
{
	float dynamicBlendAmount;
	float heirarchyGain;
	float positionGain;
	float velocityGain;
	float accelerationGain;
	float snapGain;
	float velocityDampning;
	float snapMaxLinearVelocity;
	float snapMaxAngularVelocity;
	float snapMaxLinearDistance;
	float snapMaxAngularDistance;
	float positionMaxLinearVelocity;
	float positionMaxAngularVelocity;
	long projectilePositionMaxVelocity;
	ulong meelePositionMaxVelocity;
};
struct RagdollPoseMatchingData
{
	ushort matchBone1;
	ushort matchBone2;
	ushort matchBone3;
	ubyte flags;
	float motorsStrength;
	float poseActivationDelayTime;
	float matchErrorAllowance;
	float displacementToDisable;
};
class RagdollForm : public Form, public Model
{
protected:
	RagdollData data;
	formid actorBase;
	formid bodyPartData;
	RagdollFeedbackData feedbackData;
	ushort *feedbackDynamicBones;
	RagdollPoseMatchingData poseData;
	char *deathPose;
	ulong version;
public:
	RagdollForm(FormHeader h,ModFile *f) : Form(h,f), actorBase(0), bodyPartData(0), feedbackDynamicBones(0), deathPose(0)
	{
	}
	~RagdollForm()
	{
		if (feedbackDynamicBones)
		{
			delete[] feedbackDynamicBones;
		}
		if (deathPose)
		{
			delete[] deathPose;
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
			ModelBRLoad(this,'MODL','MODB','MODT');
			case 'NVER':
				version = f->read<ulong>();
				readSize += 4;
				break;
			case 'DATA':
				data = f->read<RagdollData>();
				readSize += sizeof(RagdollData);
				break;
			case 'XNAM':
				actorBase = f->read<formid>();
				readSize += 4;
				break;
			case 'TNAM':
				bodyPartData = f->read<formid>();
				readSize += 4;
				break;
			case 'RAFD':
				feedbackData = f->read<RagdollFeedbackData>();
				readSize += sizeof(RagdollFeedbackData);
				break;
			case 'RAFB':
				feedbackDynamicBones = f->readarray<ushort>(data.dynamicBoneCount);
				readSize += data.dynamicBoneCount * 2;
				break;
			case 'RAPS':
				poseData = f->read<RagdollPoseMatchingData>();
				readSize += sizeof(RagdollPoseMatchingData);
				break;
			case 'ANAM':
				deathPose = f->readzstring(h.size);
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
		ModelBRSave(this,'MODL','MODB','MODT');
		WriteSubrecord('NVER',4,f);
		f->write<ulong>(version);
		WriteSubrecord('DATA',sizeof(RagdollData),f);
		f->write<RagdollData>(data);
		if (actorBase)
		{
			WriteSubrecord('XNAM',4,f);
			f->write<formid>(actorBase);
		}
		if (bodyPartData)
		{
			WriteSubrecord('TNAM',4,f);
			f->write<formid>(bodyPartData);
		}
		WriteSubrecord('RAFD',sizeof(RagdollFeedbackData),f);
		f->write<RagdollFeedbackData>(feedbackData);
		if (data.dynamicBoneCount)
		{
			WriteSubrecord('RAFB',data.dynamicBoneCount * 2,f);
			f->writearray<ushort>(data.dynamicBoneCount,feedbackDynamicBones);
		}
		WriteSubrecord('RAPS',sizeof(RagdollPoseMatchingData),f);
		f->write<RagdollPoseMatchingData>(poseData);
		WriteZStringSubrecord('ANAM',deathPose,f);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		ModelBRGetSaveSize(this);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(sizeof(RagdollData));
		if (actorBase)
		{
			size += ComputeSubrecordSize(4);
		}
		if (bodyPartData)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(sizeof(RagdollFeedbackData));
		if (data.dynamicBoneCount)
		{
			size += ComputeSubrecordSize(data.dynamicBoneCount * 2);
		}
		size += ComputeSubrecordSize(sizeof(RagdollPoseMatchingData));
		size += ZStringSubrecordSize(deathPose);
		return size;
	}
};
