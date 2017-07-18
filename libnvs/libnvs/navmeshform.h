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
struct NavMeshData
{
	formid cell;
	ulong vertexCount;
	ulong triangleCount;
	ulong edgeExtraInfoCount;
	ulong coverTriangleCount;
	ulong doorPortalCount;
};
struct NavMeshTriangle
{
	ushort vertex1;
	ushort vertex2;
	ushort vertex3;
	ushort edge1;
	ushort edge2;
	ushort edge3;
	ulong flags;
};
struct NavMeshTriangleDoorPortal
{
	formid doorReference;
	ushort unk;
};
#pragma pack(push,1)
struct EdgeExtraInfo
{
	ulong unk;
	formid navMesh;
	ushort triangle;
};
#pragma pack(pop)
class NavMeshForm : public Form
{
public:
	ulong version;
	NavMeshData data;
	NiPoint3 *vertices;
	NavMeshTriangle *triangles;
	ushort *coverTriangles;
	NavMeshTriangleDoorPortal *doorPortals;
	ubyte *navMeshGrid;
	ulong navMeshGridSize;
	EdgeExtraInfo *edgeExtraInfo;
	NavMeshForm(FormHeader h,ModFile *f) : Form(h,f), vertices(0), triangles(0), coverTriangles(0), doorPortals(0), navMeshGrid(0), navMeshGridSize(0), edgeExtraInfo(0)
	{
	}
	virtual ~NavMeshForm()
	{
		if (vertices)
		{
			delete[] vertices;
		}
		if (triangles)
		{
			delete[] triangles;
		}
		if (coverTriangles)
		{
			delete[] coverTriangles;
		}
		if (doorPortals)
		{
			delete[] doorPortals;
		}
		if (navMeshGrid)
		{
			delete[] navMeshGrid;
		}
		if (edgeExtraInfo)
		{
			delete[] edgeExtraInfo;
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
			case 'NVER':
				version = f->read<ulong>();
				readSize += 4;
				break;
			case 'DATA':
				data = f->read<NavMeshData>();
				readSize += sizeof(NavMeshData);
				break;
			case 'NVVX':
				vertices = f->readarray<NiPoint3>(data.vertexCount);
				readSize += data.vertexCount * sizeof(NiPoint3);
				break;
			case 'NVTR':
				triangles = f->readarray<NavMeshTriangle>(data.triangleCount);
				readSize += data.triangleCount * sizeof(NavMeshTriangle);
				break;
			case 'NVCA':
				coverTriangles = f->readarray<ushort>(data.coverTriangleCount);
				readSize += data.coverTriangleCount * 2;
				break;
			case 'NVDP':
				doorPortals = f->readarray<NavMeshTriangleDoorPortal>(data.doorPortalCount);
				readSize += data.doorPortalCount * sizeof(NavMeshTriangleDoorPortal);
				break;
			case 'NVGD':
				navMeshGridSize = h.size;
				navMeshGrid = f->readarray<ubyte>(navMeshGridSize);
				readSize += navMeshGridSize;
				break;
			case 'NVEX':
				edgeExtraInfo = f->readarray<EdgeExtraInfo>(data.edgeExtraInfoCount);
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
		if (!(header.flags & 0x20))
		{
			WriteSubrecord('NVER',4,f);
			f->write<ulong>(version);
			WriteSubrecord('DATA',sizeof(NavMeshData),f);
			f->write<NavMeshData>(data);
			if (data.vertexCount)
			{
				WriteSubrecord('NVVX',data.vertexCount * sizeof(NiPoint3),f);
				f->writearray<NiPoint3>(data.vertexCount,vertices);
			}
			if (data.triangleCount)
			{
				WriteSubrecord('NVTR',data.triangleCount * sizeof(NavMeshTriangle),f);
				f->writearray<NavMeshTriangle>(data.triangleCount,triangles);
			}
			if (data.coverTriangleCount)
			{
				WriteSubrecord('NVCA',data.coverTriangleCount * 2,f);
				f->writearray<ushort>(data.coverTriangleCount,coverTriangles);
			}
			if (data.doorPortalCount)
			{
				WriteSubrecord('NVDP',data.doorPortalCount * sizeof(NavMeshTriangleDoorPortal),f);
				f->writearray<NavMeshTriangleDoorPortal>(data.doorPortalCount,doorPortals);
			}
			if (navMeshGridSize)
			{
				WriteSubrecord('NVGD',navMeshGridSize,f);
				f->writearray<ubyte>(navMeshGridSize,navMeshGrid);
			}
			if (data.edgeExtraInfoCount)
			{
				WriteSubrecord('NVEX',data.edgeExtraInfoCount * sizeof(EdgeExtraInfo),f);
				f->writearray<EdgeExtraInfo>(data.edgeExtraInfoCount,edgeExtraInfo);
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		if (!(header.flags & 0x20))
		{
			size += ComputeSubrecordSize(4);
			size += ComputeSubrecordSize(sizeof(NavMeshData));
			if (data.vertexCount)
			{
				size += ComputeSubrecordSize(data.vertexCount * sizeof(NiPoint3));
			}
			if (data.triangleCount)
			{
				size += ComputeSubrecordSize(data.triangleCount * sizeof(NavMeshTriangle));
			}
			if (data.coverTriangleCount)
			{
				size += ComputeSubrecordSize(data.coverTriangleCount * 2);
			}
			if (data.doorPortalCount)
			{
				size += ComputeSubrecordSize(data.doorPortalCount * sizeof(NavMeshTriangleDoorPortal));
			}
			if (navMeshGridSize)
			{
				size += ComputeSubrecordSize(navMeshGridSize);
			}
			if (data.edgeExtraInfoCount)
			{
				size += ComputeSubrecordSize(data.edgeExtraInfoCount * sizeof(EdgeExtraInfo));
			}
		}
		return size;
	}
};
