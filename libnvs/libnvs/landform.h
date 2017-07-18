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
struct LandTexture
{
	formid texture;
	ushort quadrant;
	short layer;
};
struct LandVertexTexture
{
	ushort position;
	float opacity;
};
struct LandTextureData
{
	ubyte type; //0 = BTEX, 1 = ATEX, 2 = VTEX
	LandTexture texture;
	ulong opacityCount;
	LandVertexTexture *opacities;
	LandTextureData() : opacities(0)
	{
	}
	virtual ~LandTextureData()
	{
		if (opacities)
		{
			delete[] opacities;
		}
	}
};
struct VertexNormal
{
	ubyte x;
	ubyte y;
	ubyte z;
};
struct VertexColor
{
	ubyte red;
	ubyte green;
	ubyte blue;
};
class LandForm : public Form
{
protected:
	ulong flags;
	VertexNormal *vertexNormals;
	float heightOffset;
	byte *heightValues;
	ubyte heightUnk1;
	ubyte heightUnk2;
	ubyte heightUnk3;
	VertexColor *vertexColors;
	SimpleDynVecClass<LandTextureData *> landTextures;
	ulong vertexTextureCount;
	formid *vertexTextures;
public:
	LandForm(FormHeader h,ModFile *f) : Form(h,f), vertexNormals(0), heightValues(0), vertexColors(0), vertexTextureCount(0), vertexTextures(0)
	{
	}
	virtual ~LandForm()
	{
		if (vertexNormals)
		{
			delete[] vertexNormals;
		}
		if (heightValues)
		{
			delete[] heightValues;
		}
		if (vertexColors)
		{
			delete[] vertexColors;
		}
		for (int i = 0;i < landTextures.Count();i++)
		{
			delete landTextures[i];
		}
		if (vertexTextures)
		{
			delete[] vertexTextures;
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
			case 'DATA':
				flags = f->read<ulong>();
				readSize += 4;
				break;
			case 'VNML':
				vertexNormals = f->readarray<VertexNormal>(1089);
				readSize += (1089 * sizeof(VertexNormal));
				break;
			case 'VHGT':
				heightOffset = f->read<float>();
				readSize += 4;
				heightValues = f->readarray<byte>(1089);
				readSize += 1089;
				heightUnk1 = f->read<byte>();
				readSize += 4;
				heightUnk2 = f->read<byte>();
				readSize += 4;
				heightUnk3 = f->read<byte>();
				readSize += 4;
				break;
			case 'VCLR':
				vertexColors = f->readarray<VertexColor>(1089);
				readSize += (1089 * sizeof(VertexColor));
				break;
			case 'BTXT':
				{
					LandTextureData *tex = new LandTextureData;
					tex->type = 0;
					tex->texture = f->read<LandTexture>();
					readSize += sizeof(LandTexture);
					landTextures.Add(tex);
				}
				break;
			case 'ATXT':
				{
					LandTextureData *tex = new LandTextureData;
					tex->type = 1;
					tex->texture = f->read<LandTexture>();
					readSize += sizeof(LandTexture);
					landTextures.Add(tex);
				}
				break;
			case 'VTXT':
				{
					LandTextureData *tex = new LandTextureData;
					tex->type = 2;
					tex->opacityCount = h.size / sizeof(LandVertexTexture);
					tex->opacities = f->readarray<LandVertexTexture>(tex->opacityCount);
					readSize += h.size;
					landTextures.Add(tex);
				}
				break;
			case 'VTEX':
				vertexTextureCount = h.size / 4;
				vertexTextures = f->readarray<formid>(vertexTextureCount);
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
		WriteSubrecord('DATA',4,f);
		f->write<ulong>(flags);
		if (vertexNormals)
		{
			WriteSubrecord('VNML',3267,f);
			f->writearray<VertexNormal>(1089,vertexNormals);
		}
		if (heightValues)
		{
			WriteSubrecord('VHGT',1096,f);
			f->write<float>(heightOffset);
			f->writearray<byte>(1089,heightValues);
			f->write<ubyte>(heightUnk1);
			f->write<ubyte>(heightUnk2);
			f->write<ubyte>(heightUnk3);
		}
		if (vertexColors)
		{
			WriteSubrecord('VCLR',3267,f);
			f->writearray<VertexColor>(1089,vertexColors);
		}
		for (int i = 0;i < landTextures.Count();i++)
		{
			if (landTextures[i]->type == 0)
			{
				WriteSubrecord('BTXT',8,f);
				f->write<LandTexture>(landTextures[i]->texture);
			}
			if (landTextures[i]->type == 1)
			{
				WriteSubrecord('ATXT',8,f);
				f->write<LandTexture>(landTextures[i]->texture);
			}
			if (landTextures[i]->type == 2)
			{
				WriteSubrecord('VTXT',landTextures[i]->opacityCount * sizeof(LandVertexTexture),f);
				f->writearray<LandVertexTexture>(landTextures[i]->opacityCount,landTextures[i]->opacities);
			}
		}
		if (vertexTextures)
		{
			WriteSubrecord('VTEX',vertexTextureCount * 4,f);
			f->writearray<formid>(vertexTextureCount,vertexTextures);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ComputeSubrecordSize(4);
		if (vertexNormals)
		{
			size += ComputeSubrecordSize(3267);
		}
		if (heightValues)
		{
			size += ComputeSubrecordSize(1096);
		}
		if (vertexColors)
		{
			size += ComputeSubrecordSize(3267);
		}
		for (int i = 0;i < landTextures.Count();i++)
		{
			if (landTextures[i]->type == 0)
			{
				size += ComputeSubrecordSize(8);
			}
			if (landTextures[i]->type == 1)
			{
				size += ComputeSubrecordSize(8);
			}
			if (landTextures[i]->type == 2)
			{
				size += ComputeSubrecordSize(landTextures[i]->opacityCount * sizeof(LandVertexTexture));
			}
		}
		if (vertexTextures)
		{
			size += ComputeSubrecordSize(vertexTextureCount * 4);
		}
		return size;
	}
};
