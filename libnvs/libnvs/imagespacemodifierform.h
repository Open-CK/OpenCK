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
struct ImageSpaceModifierData
{
	ubyte animatable;
	float duration;
	ulong imageModifierDataCount[21][2];
	ulong tintColorCount;
	ulong blurRadiusCount;
	ulong doubleVisionStrengthCount;
	ulong radialBlurStrengthCount;
	ulong radialBlurRampUpCount;
	ulong radialBlurStartCount;
	ubyte useRadialBlurTarget;
	float radialBlurCenterX;
	float radialBlurCenterY;
	ulong depthOfFieldStrengthCount;
	ulong depthOfFieldDistanceCount;
	ulong depthOfFieldRangeCount;
	ubyte useDepthOfFieldTarget;
	ulong radialBlurRampDownCount;
	ulong radialBlurDownStartCount;
	ulong fadeColorCount;
	ulong fullScreenMotionBlurStrengthCount;
	ImageSpaceModifierData() : tintColorCount(0), blurRadiusCount(0), doubleVisionStrengthCount(0), radialBlurStrengthCount(0), radialBlurRampUpCount(0), radialBlurStartCount(0), depthOfFieldStrengthCount(0), depthOfFieldDistanceCount(0), depthOfFieldRangeCount(0), radialBlurRampDownCount(0), radialBlurDownStartCount(0), fadeColorCount(0), fullScreenMotionBlurStrengthCount(0)
	{
	}
};
struct ImageSpaceModifierData2
{
	ubyte animatable;
	float duration;
	ulong imageModifierDataCount[21][2];
	ulong tintColorCount;
	ulong blurRadiusCount;
	ulong doubleVisionStrengthCount;
	ulong radialBlurStrengthCount;
	ulong radialBlurRampUpCount;
	ulong radialBlurStartCount;
	ubyte useRadialBlurTarget;
	float radialBlurCenterX;
	float radialBlurCenterY;
	ulong depthOfFieldStrengthCount;
	ulong depthOfFieldDistanceCount;
	ulong depthOfFieldRangeCount;
	ubyte useDepthOfFieldTarget;
	ulong radialBlurRampDownCount;
	ulong radialBlurDownStartCount;
	ulong fadeColorCount;
};
struct ImageSpaceModifierData3
{
	ubyte animatable;
	float duration;
	ulong imageModifierDataCount[21][2];
	ulong tintColorCount;
	ulong blurRadiusCount;
	ulong doubleVisionStrengthCount;
	ulong radialBlurStrengthCount;
	ulong radialBlurRampUpCount;
	ulong radialBlurStartCount;
	ubyte useRadialBlurTarget;
	float radialBlurCenterX;
	float radialBlurCenterY;
	ulong depthOfFieldStrengthCount;
	ulong depthOfFieldDistanceCount;
	ulong depthOfFieldRangeCount;
	ubyte useDepthOfFieldTarget;
	ulong radialBlurRampDownCount;
	ulong radialBlurDownStartCount;
};

struct ImageSpaceModifierData4
{
	ubyte animatable;
	float duration;
	ulong imageModifierDataCount[21][2];
	ulong tintColorCount;
	ulong blurRadiusCount;
	ulong doubleVisionStrengthCount;
};
struct FloatData
{
	float time;
	float value;
};
struct FloatInterpolator
{
	FloatData *value;
	FloatInterpolator() : value(0)
	{
	}
	virtual ~FloatInterpolator()
	{
		if (value)
		{
			delete[] value;
		}
	}
};
#define FloatInterpolatorLoad(obj,id,count) \
			case id: \
				if (count) \
				{ \
					obj.value = f->readarray<FloatData>(count); \
					readSize += count * sizeof(FloatData); \
				} \
				break;
#define FloatInterpolatorSave(obj,id,count) \
		if (count) \
		{ \
			WriteSubrecord(id,count * sizeof(FloatData),f); \
			f->writearray<FloatData>(count,obj.value); \
		}
#define FloatInterpolatorGetSaveSize(count) \
		if (count) \
		{ \
			size += ComputeSubrecordSize(count * sizeof(FloatData)); \
		}
struct ColorData
{
	float time;
	float red;
	float green;
	float blue;
	float alpha;
};
struct ColorInterpolator
{
	ColorData *value;
	ColorInterpolator() : value(0)
	{
	}
	virtual ~ColorInterpolator()
	{
		if (value)
		{
			delete[] value;
		}
	}
};
#define ColorInterpolatorLoad(obj,id,count) \
			case id: \
				if (count) \
				{ \
					obj.value = f->readarray<ColorData>(count); \
					readSize += count * sizeof(ColorData); \
				} \
				break;
#define ColorInterpolatorSave(obj,id,count) \
		if (count) \
		{ \
			WriteSubrecord(id,count * sizeof(ColorData),f); \
			f->writearray<ColorData>(count,obj.value); \
		}
#define ColorInterpolatorGetSaveSize(count) \
		if (count) \
		{ \
			size += ComputeSubrecordSize(count * sizeof(ColorData)); \
		}

class ImageSpaceModifierForm : public Form
{
protected:
	ImageSpaceModifierData data;
	ImageSpaceModifierData2 data2;
	ImageSpaceModifierData3 data3;
	ImageSpaceModifierData4 data4;
	bool hasImageSpaceModifierData2;
	bool hasImageSpaceModifierData3;
	bool hasImageSpaceModifierData4;
	FloatInterpolator imageModifierData[21][2];
	FloatInterpolator blurRadius;
	FloatInterpolator doubleVisionStrength;
	ColorInterpolator tintColor;
	ColorInterpolator fadeColor;
	FloatInterpolator radialBlurStrength;
	FloatInterpolator radialBlurRampUp;
	FloatInterpolator radialBlurStart;
	FloatInterpolator radialBlurRampDown;
	FloatInterpolator radialBlurDownStart;
	FloatInterpolator depthOfFieldStrength;
	FloatInterpolator depthOfFieldDistance;
	FloatInterpolator depthOfFieldRange;
	FloatInterpolator fullScreenMotionBlurStrength;
	formid introSound;
	formid outroSound;
public:
	ImageSpaceModifierForm(FormHeader h,ModFile *f) : Form(h,f), hasImageSpaceModifierData2(false), hasImageSpaceModifierData3(false), hasImageSpaceModifierData4(false), introSound(0), outroSound(0)
	{
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
			case 'DNAM':
				if (h.size == sizeof(ImageSpaceModifierData))
				{
					data = f->read<ImageSpaceModifierData>();
					readSize += sizeof(ImageSpaceModifierData);
				}
				else if (h.size == sizeof(ImageSpaceModifierData2))
				{
					hasImageSpaceModifierData2 = true;
					data2 = f->read<ImageSpaceModifierData2>();
					memcpy(&data,&data2,sizeof(data2));
					readSize += sizeof(ImageSpaceModifierData2);
				}
				else if (h.size == sizeof(ImageSpaceModifierData3))
				{
					hasImageSpaceModifierData3 = true;
					data3 = f->read<ImageSpaceModifierData3>();
					memcpy(&data,&data3,sizeof(data3));
					readSize += sizeof(ImageSpaceModifierData3);
				}
				else if (h.size == sizeof(ImageSpaceModifierData4))
				{
					hasImageSpaceModifierData4 = true;
					data4 = f->read<ImageSpaceModifierData4>();
					memcpy(&data,&data4,sizeof(data4));
					readSize += sizeof(ImageSpaceModifierData4);
				}
				break;
			FloatInterpolatorLoad(blurRadius,'BNAM',data.blurRadiusCount);
			FloatInterpolatorLoad(doubleVisionStrength,'VNAM',data.doubleVisionStrengthCount);
			ColorInterpolatorLoad(tintColor,'TNAM',data.tintColorCount);
			ColorInterpolatorLoad(fadeColor,'NAM3',data.fadeColorCount);
			FloatInterpolatorLoad(radialBlurStrength,'RNAM',data.radialBlurStrengthCount);
			FloatInterpolatorLoad(radialBlurRampUp,'SNAM',data.radialBlurRampUpCount);
			FloatInterpolatorLoad(radialBlurStart,'UNAM',data.radialBlurStartCount);
			FloatInterpolatorLoad(radialBlurRampDown,'NAM1',data.radialBlurRampDownCount);
			FloatInterpolatorLoad(radialBlurDownStart,'NAM2',data.radialBlurDownStartCount);
			FloatInterpolatorLoad(depthOfFieldStrength,'WNAM',data.depthOfFieldStrengthCount);
			FloatInterpolatorLoad(depthOfFieldDistance,'XNAM',data.depthOfFieldDistanceCount);
			FloatInterpolatorLoad(depthOfFieldRange,'YNAM',data.depthOfFieldRangeCount);
			FloatInterpolatorLoad(fullScreenMotionBlurStrength,'NAM4',data.fullScreenMotionBlurStrengthCount);
			case 'RDSD':
				introSound = f->read<formid>();
				readSize += 4;
				break;
			case 'RDSI':
				outroSound = f->read<formid>();
				readSize += 4;
				break;
			default:
				if (SwapBytes(h.type) - 'DAI\0' <= 0xFF)
				{
					ulong multadd = (SwapBytes(h.type) >> 6) & 3;
					ulong variable = ((char)SwapBytes(h.type)) & 0x3F;
					if (data.imageModifierDataCount[variable][multadd])
					{
						imageModifierData[variable][multadd].value = f->readarray<FloatData>(data.imageModifierDataCount[variable][multadd]);
						readSize += data.imageModifierDataCount[variable][multadd] * sizeof(FloatData);
					}
				}
				else
				{
					printf("Unknown subrecord found");
					__debugbreak();
				}
				break;
			}
		}
	}
	virtual void Save(FileWrite *f)
	{
		FormSave();
		if (hasImageSpaceModifierData2)
		{
			WriteSubrecord('DNAM',sizeof(ImageSpaceModifierData2),f);
			f->write<ImageSpaceModifierData2>(data2);
		}
		else if (hasImageSpaceModifierData3)
		{
			WriteSubrecord('DNAM',sizeof(ImageSpaceModifierData3),f);
			f->write<ImageSpaceModifierData3>(data3);
		}
		else if (hasImageSpaceModifierData4)
		{
			WriteSubrecord('DNAM',sizeof(ImageSpaceModifierData4),f);
			f->write<ImageSpaceModifierData4>(data4);
		}
		else
		{
			WriteSubrecord('DNAM',sizeof(ImageSpaceModifierData),f);
			f->write<ImageSpaceModifierData>(data);
		}
		FloatInterpolatorSave(blurRadius,'BNAM',data.blurRadiusCount);
		FloatInterpolatorSave(doubleVisionStrength,'VNAM',data.doubleVisionStrengthCount);
		ColorInterpolatorSave(tintColor,'TNAM',data.tintColorCount);
		ColorInterpolatorSave(fadeColor,'NAM3',data.fadeColorCount);
		FloatInterpolatorSave(radialBlurStrength,'RNAM',data.radialBlurStrengthCount);
		FloatInterpolatorSave(radialBlurRampUp,'SNAM',data.radialBlurRampUpCount);
		FloatInterpolatorSave(radialBlurStart,'UNAM',data.radialBlurStartCount);
		FloatInterpolatorSave(radialBlurRampDown,'NAM1',data.radialBlurRampDownCount);
		FloatInterpolatorSave(radialBlurDownStart,'NAM2',data.radialBlurDownStartCount);
		FloatInterpolatorSave(depthOfFieldStrength,'WNAM',data.depthOfFieldStrengthCount);
		FloatInterpolatorSave(depthOfFieldDistance,'XNAM',data.depthOfFieldDistanceCount);
		FloatInterpolatorSave(depthOfFieldRange,'YNAM',data.depthOfFieldRangeCount);
		FloatInterpolatorSave(fullScreenMotionBlurStrength,'NAM4',data.fullScreenMotionBlurStrengthCount);
		for (int variable = 0;variable < 21;variable++)
		{
			for (int multadd = 0;multadd < 2;multadd++)
			{
				if (data.imageModifierDataCount[variable][multadd])
				{
					WriteSubrecord(SwapBytes(variable | ((multadd | 0x1110524) << 6)),data.imageModifierDataCount[variable][multadd] * sizeof(FloatData),f);
					f->writearray<FloatData>(data.imageModifierDataCount[variable][multadd],imageModifierData[variable][multadd].value);
				}
			}
		}
		if (introSound)
		{
			WriteSubrecord('RDSD',4,f);
			f->write<formid>(introSound);
		}
		if (outroSound)
		{
			WriteSubrecord('RDSI',4,f);
			f->write<formid>(outroSound);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		if (hasImageSpaceModifierData2)
		{
			size += ComputeSubrecordSize(sizeof(ImageSpaceModifierData2));
		}
		else if (hasImageSpaceModifierData3)
		{
			size += ComputeSubrecordSize(sizeof(ImageSpaceModifierData3));
		}
		else if (hasImageSpaceModifierData4)
		{
			size += ComputeSubrecordSize(sizeof(ImageSpaceModifierData4));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(ImageSpaceModifierData));
		}
		FloatInterpolatorGetSaveSize(data.blurRadiusCount);
		FloatInterpolatorGetSaveSize(data.doubleVisionStrengthCount);
		ColorInterpolatorGetSaveSize(data.tintColorCount);
		ColorInterpolatorGetSaveSize(data.fadeColorCount);
		FloatInterpolatorGetSaveSize(data.radialBlurStrengthCount);
		FloatInterpolatorGetSaveSize(data.radialBlurRampUpCount);
		FloatInterpolatorGetSaveSize(data.radialBlurStartCount);
		FloatInterpolatorGetSaveSize(data.radialBlurRampDownCount);
		FloatInterpolatorGetSaveSize(data.radialBlurDownStartCount);
		FloatInterpolatorGetSaveSize(data.depthOfFieldStrengthCount);
		FloatInterpolatorGetSaveSize(data.depthOfFieldDistanceCount);
		FloatInterpolatorGetSaveSize(data.depthOfFieldRangeCount);
		FloatInterpolatorGetSaveSize(data.fullScreenMotionBlurStrengthCount);
		for (int variable = 0;variable < 21;variable++)
		{
			for (int multadd = 0;multadd < 2;multadd++)
			{
				if (data.imageModifierDataCount[variable][multadd])
				{
					size += ComputeSubrecordSize(data.imageModifierDataCount[variable][multadd] * sizeof(FloatData));
				}
			}
		}
		if (introSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (outroSound)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
