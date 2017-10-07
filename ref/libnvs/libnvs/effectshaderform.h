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
struct EffectShaderData
{
	ubyte flags;
	ulong memSBlend;
	ulong memBlendOp;
	ulong memZFunc;
	ulong fillColor;
	float fillAIn;
	float fillAFull;
	float fillAOut;
	float fillAPRatio;
	float fillAAmp;
	float fillAFreq;
	float fillAnimSpdU;
	float fillAnimSpdV;
	float edgeOff;
	ulong edgeEffectColor;
	float edgeAIn;
	float edgeAFull;
	float edgeAOut;
	float edgeAPRatio;
	float edgeAAmp;
	float edgeAFreq;
	float fillAFRatio;
	float edgeAFRatio;
	ulong memDBlend;
	ulong partSBlend;
	ulong partBlendOp;
	ulong partZFunc;
	ulong partDBlend;
	float partBUp;
	float partBFull;
	float partBDown;
	float partBFRatio;
	float partBPRatio;
	float partLTime;
	float partLDelta;
	float partNSpd;
	float partNAcc;
	float partVel1;
	float partVel2;
	float partVel3;
	float partAcc1;
	float partAcc2;
	float partAcc3;
	float partKey1;
	float partKey2;
	float partKey1Time;
	float partKey2Time;
	ulong key1Color;
	ulong key2Color;
	ulong key3Color;
	float key1A;
	float key2A;
	float key3A;
	float key1Time;
	float key2Time;
	float key3Time;
	float partInitialSpeed;
	float partInitialRot;
	float partInitialRotPlusMinus;
	float partRotSpeed;
	float partRotSpeedPlusMinus;
	formid addonModels;
	float holeStartTime;
	float holeEndTime;
	float holeStartValue;
	float holeEndValue;
	float edgeWidth;
	ulong edgeColor;
	float explWindSpeed;
	ulong texCountU;
	ulong texCountV;
	float addonFadeInTime;
	float addonFadeOutTime;
	float addonScaleStart;
	float addonScaleEnd;
	float addonScaleInTime;
	float addonScaleOutTime;
};
struct EffectShaderData2
{
	ubyte flags;
	ulong memSBlend;
	ulong memBlendOp;
	ulong memZFunc;
	ulong fillColor;
	float fillAIn;
	float fillAFull;
	float fillAOut;
	float fillAPRatio;
	float fillAAmp;
	float fillAFreq;
	float fillAnimSpdU;
	float fillAnimSpdV;
	float edgeOff;
	ulong edgeEffectColor;
	float edgeAIn;
	float edgeAFull;
	float edgeAOut;
	float edgeAPRatio;
	float edgeAAmp;
	float edgeAFreq;
	float fillAFRatio;
	float edgeAFRatio;
	ulong memDBlend;
	ulong partSBlend;
	ulong partBlendOp;
	ulong partZFunc;
	ulong partDBlend;
	float partBUp;
	float partBFull;
	float partBDown;
	float partBFRatio;
	float partBPRatio;
	float partLTime;
	float partLDelta;
	float partNSpd;
	float partNAcc;
	float partVel1;
	float partVel2;
	float partVel3;
	float partAcc1;
	float partAcc2;
	float partAcc3;
	float partKey1;
	float partKey2;
	float partKey1Time;
	float partKey2Time;
	ulong key1Color;
	ulong key2Color;
	ulong key3Color;
	float key1A;
	float key2A;
	float key3A;
	float key1Time;
	float key2Time;
	float key3Time;
};
struct EffectShaderData3
{
	ubyte flags;
	ulong memSBlend;
	ulong memBlendOp;
	ulong memZFunc;
	ulong fillColor;
	float fillAIn;
	float fillAFull;
	float fillAOut;
	float fillAPRatio;
	float fillAAmp;
	float fillAFreq;
	float fillAnimSpdU;
	float fillAnimSpdV;
	float edgeOff;
	ulong edgeEffectColor;
	float edgeAIn;
	float edgeAFull;
	float edgeAOut;
	float edgeAPRatio;
	float edgeAAmp;
	float edgeAFreq;
	float fillAFRatio;
	float edgeAFRatio;
	ulong memDBlend;
	ulong partSBlend;
	ulong partBlendOp;
	ulong partZFunc;
	ulong partDBlend;
	float partBUp;
	float partBFull;
	float partBDown;
	float partBFRatio;
	float partBPRatio;
	float partLTime;
	float partLDelta;
	float partNSpd;
	float partNAcc;
	float partVel1;
	float partVel2;
	float partVel3;
	float partAcc1;
	float partAcc2;
	float partAcc3;
	float partKey1;
	float partKey2;
	float partKey1Time;
	float partKey2Time;
	ulong key1Color;
	ulong key2Color;
	ulong key3Color;
	float key1A;
	float key2A;
	float key3A;
	float key1Time;
	float key2Time;
	float key3Time;
	float partInitialSpeed;
	float partInitialRot;
	float partInitialRotPlusMinus;
	float partRotSpeed;
	float partRotSpeedPlusMinus;
	formid addonModels;
};
struct EffectShaderData4
{
	ubyte flags;
	ulong memSBlend;
	ulong memBlendOp;
	ulong memZFunc;
	ulong fillColor;
	float fillAIn;
	float fillAFull;
	float fillAOut;
	float fillAPRatio;
	float fillAAmp;
	float fillAFreq;
	float fillAnimSpdU;
	float fillAnimSpdV;
	float edgeOff;
	ulong edgeEffectColor;
	float edgeAIn;
	float edgeAFull;
	float edgeAOut;
	float edgeAPRatio;
	float edgeAAmp;
	float edgeAFreq;
	float fillAFRatio;
	float edgeAFRatio;
	ulong memDBlend;
	ulong partSBlend;
	ulong partBlendOp;
	ulong partZFunc;
	ulong partDBlend;
	float partBUp;
	float partBFull;
	float partBDown;
	float partBFRatio;
	float partBPRatio;
	float partLTime;
	float partLDelta;
	float partNSpd;
	float partNAcc;
	float partVel1;
	float partVel2;
	float partVel3;
	float partAcc1;
	float partAcc2;
	float partAcc3;
	float partKey1;
	float partKey2;
	float partKey1Time;
	float partKey2Time;
	ulong key1Color;
	ulong key2Color;
	ulong key3Color;
	float key1A;
	float key2A;
	float key3A;
	float key1Time;
	float key2Time;
	float key3Time;
	float partInitialSpeed;
	float partInitialRot;
	float partInitialRotPlusMinus;
	float partRotSpeed;
	float partRotSpeedPlusMinus;
	formid addonModels;
	float holeStartTime;
	float holeEndTime;
	float holeStartValue;
	float holeEndValue;
	float edgeWidth;
	ulong edgeColor;
	float explWindSpeed;
	ulong texCountU;
	ulong texCountV;
	float addonFadeInTime;
	float addonFadeOutTime;
	float addonScaleStart;
	float addonScaleEnd;
};
struct EffectShaderData5
{
	ubyte flags;
	ulong memSBlend;
	ulong memBlendOp;
	ulong memZFunc;
	ulong fillColor;
	float fillAIn;
	float fillAFull;
	float fillAOut;
	float fillAPRatio;
	float fillAAmp;
	float fillAFreq;
	float fillAnimSpdU;
	float fillAnimSpdV;
	float edgeOff;
	ulong edgeEffectColor;
	float edgeAIn;
	float edgeAFull;
	float edgeAOut;
	float edgeAPRatio;
	float edgeAAmp;
	float edgeAFreq;
	float fillAFRatio;
	float edgeAFRatio;
	ulong memDBlend;
	ulong partSBlend;
	ulong partBlendOp;
	ulong partZFunc;
	ulong partDBlend;
	float partBUp;
	float partBFull;
	float partBDown;
	float partBFRatio;
	float partBPRatio;
	float partLTime;
	float partLDelta;
	float partNSpd;
	float partNAcc;
	float partVel1;
	float partVel2;
	float partVel3;
	float partAcc1;
	float partAcc2;
	float partAcc3;
	float partKey1;
	float partKey2;
	float partKey1Time;
	float partKey2Time;
	ulong key1Color;
	ulong key2Color;
	ulong key3Color;
	float key1A;
	float key2A;
	float key3A;
	float key1Time;
	float key2Time;
	float key3Time;
	float partInitialSpeed;
	float partInitialRot;
	float partInitialRotPlusMinus;
	float partRotSpeed;
	float partRotSpeedPlusMinus;
};
struct EffectShaderData6
{
	ubyte flags;
	ulong memSBlend;
	ulong memBlendOp;
	ulong memZFunc;
	ulong fillColor;
	float fillAIn;
	float fillAFull;
	float fillAOut;
	float fillAPRatio;
	float fillAAmp;
	float fillAFreq;
	float fillAnimSpdU;
	float fillAnimSpdV;
	float edgeOff;
	ulong edgeEffectColor;
	float edgeAIn;
	float edgeAFull;
	float edgeAOut;
	float edgeAPRatio;
	float edgeAAmp;
	float edgeAFreq;
	float fillAFRatio;
	float edgeAFRatio;
	ulong memDBlend;
	ulong partSBlend;
	ulong partBlendOp;
	ulong partZFunc;
	ulong partDBlend;
	float partBUp;
	float partBFull;
	float partBDown;
	float partBFRatio;
	float partBPRatio;
	float partLTime;
	float partLDelta;
	float partNSpd;
	float partNAcc;
	float partVel1;
	float partVel2;
	float partVel3;
	float partAcc1;
	float partAcc2;
	float partAcc3;
	float partKey1;
	float partKey2;
	float partKey1Time;
	float partKey2Time;
	ulong key1Color;
	ulong key2Color;
	ulong key3Color;
	float key1A;
	float key2A;
	float key3A;
	float key1Time;
	float key2Time;
	float key3Time;
	float partInitialSpeed;
	float partInitialRot;
	float partInitialRotPlusMinus;
	float partRotSpeed;
	float partRotSpeedPlusMinus;
	formid addonModels;
	float holeStartTime;
	float holeEndTime;
	float holeStartValue;
	float holeEndValue;
	float edgeWidth;
	ulong edgeColor;
	float explWindSpeed;
	ulong texCountU;
	ulong texCountV;
};
class EffectShaderForm : public Form
{
protected:
	EffectShaderData data;
	EffectShaderData2 data2;
	EffectShaderData3 data3;
	EffectShaderData4 data4;
	EffectShaderData5 data5;
	EffectShaderData6 data6;
	bool hasEffectShaderData2;
	bool hasEffectShaderData3;
	bool hasEffectShaderData4;
	bool hasEffectShaderData5;
	bool hasEffectShaderData6;
	Texture fillTexture;
	Texture particleTexture;
	Texture holeTexture;
public:
	EffectShaderForm(FormHeader h,ModFile *f) : Form(h,f), hasEffectShaderData2(false), hasEffectShaderData3(false), hasEffectShaderData4(false), hasEffectShaderData5(false), hasEffectShaderData6(false)
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
			TextureLoad((&fillTexture),'ICON');
			TextureLoad((&particleTexture),'ICO2');
			TextureLoad((&holeTexture),'NAM7');
			case 'DATA':
				if (h.size == sizeof(EffectShaderData))
				{
					data = f->read<EffectShaderData>();
					readSize += sizeof(EffectShaderData);
				}
				else if (h.size == sizeof(EffectShaderData2))
				{
					hasEffectShaderData2 = true;
					data2 = f->read<EffectShaderData2>();
					readSize += sizeof(EffectShaderData2);
				}
				else if (h.size == sizeof(EffectShaderData3))
				{
					hasEffectShaderData3 = true;
					data3 = f->read<EffectShaderData3>();
					readSize += sizeof(EffectShaderData3);
				}
				else if (h.size == sizeof(EffectShaderData4))
				{
					hasEffectShaderData4 = true;
					data4 = f->read<EffectShaderData4>();
					readSize += sizeof(EffectShaderData4);
				}
				else if (h.size == sizeof(EffectShaderData5))
				{
					hasEffectShaderData5 = true;
					data5 = f->read<EffectShaderData5>();
					readSize += sizeof(EffectShaderData5);
				}
				else if (h.size == sizeof(EffectShaderData6))
				{
					hasEffectShaderData6 = true;
					data6 = f->read<EffectShaderData6>();
					readSize += sizeof(EffectShaderData6);
				}
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
		TextureSave((&fillTexture),'ICON');
		TextureSave((&particleTexture),'ICO2');
		TextureSave((&holeTexture),'NAM7');
		if (hasEffectShaderData2)
		{
			WriteSubrecord('DATA',sizeof(EffectShaderData2),f);
			f->write<EffectShaderData2>(data2);
		}
		else if (hasEffectShaderData3)
		{
			WriteSubrecord('DATA',sizeof(EffectShaderData3),f);
			f->write<EffectShaderData3>(data3);
		}
		else if (hasEffectShaderData4)
		{
			WriteSubrecord('DATA',sizeof(EffectShaderData4),f);
			f->write<EffectShaderData4>(data4);
		}
		else if (hasEffectShaderData5)
		{
			WriteSubrecord('DATA',sizeof(EffectShaderData5),f);
			f->write<EffectShaderData5>(data5);
		}
		else if (hasEffectShaderData6)
		{
			WriteSubrecord('DATA',sizeof(EffectShaderData6),f);
			f->write<EffectShaderData6>(data6);
		}
		else
		{
			WriteSubrecord('DATA',sizeof(EffectShaderData),f);
			f->write<EffectShaderData>(data);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		TextureGetSaveSize((&fillTexture));
		TextureGetSaveSize((&particleTexture));
		TextureGetSaveSize((&holeTexture));
		if (hasEffectShaderData2)
		{
			size += ComputeSubrecordSize(sizeof(EffectShaderData2));
		}
		else if (hasEffectShaderData3)
		{
			size += ComputeSubrecordSize(sizeof(EffectShaderData3));
		}
		else if (hasEffectShaderData4)
		{
			size += ComputeSubrecordSize(sizeof(EffectShaderData4));
		}
		else if (hasEffectShaderData5)
		{
			size += ComputeSubrecordSize(sizeof(EffectShaderData5));
		}
		else if (hasEffectShaderData6)
		{
			size += ComputeSubrecordSize(sizeof(EffectShaderData6));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(EffectShaderData));
		}
		return size;
	}
};
