/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include <stdlib.h>
#pragma warning(disable: 4100)
struct systemtime
{
    unsigned short wYear;
    unsigned short wMonth;
    unsigned short wDayOfWeek;
    unsigned short wDay;
    unsigned short wHour;
    unsigned short wMinute;
    unsigned short wSecond;
    unsigned short wMilliseconds;
};
typedef signed char byte;
typedef unsigned char ubyte;
//char
//short
typedef unsigned short ushort;
//long
typedef unsigned long ulong;
//float
typedef ulong formid;
typedef ulong iref;
typedef long long int64;
typedef unsigned long long uint64;
typedef unsigned long long hash;
struct NiPoint3
{
	float x,y,z;
};
struct NiPoint2
{
	float x,y;
};
struct Position
{
	NiPoint3 position;
	NiPoint3 rotation;
	float scale;
};

template <class T> class SimpleVecClass {
protected:
	T *Vector; // 0004
	int VectorMax; // 0008
public:
	explicit SimpleVecClass(int size = 0)
	{
		Vector = 0;
		VectorMax = 0;
		if (size > 0)
		{
			Resize(size);
		}
	}
	virtual ~SimpleVecClass()
	{
		if (Vector)
		{
			delete[] Vector;
			Vector = 0;
			VectorMax = 0;
		}
	}
	SimpleVecClass(const SimpleVecClass<T>& vector)
	{
		Vector = (T*)(new char[vector.VectorMax * sizeof(T)]);
		VectorMax = vector.VectorMax;
		memcpy(Vector,vector.Vector, VectorMax * sizeof(T));
	}
	SimpleVecClass<T>& operator =(const SimpleVecClass<T>& vector)
	{
		if (this != &vector)
		{
			delete[] Vector;
			Vector = (T*)(new char[vector.VectorMax * sizeof(T)]);
			VectorMax = vector.VectorMax;
			memcpy(Vector,vector.Vector, VectorMax * sizeof(T));
		}
		return *this;
	}
	virtual bool Resize(int newsize)
	{
		if (VectorMax == newsize)
		{
			return true;
		}
		if (newsize > 0)
		{
			T *vec = new T[newsize];
			if (Vector)
			{
				int count = VectorMax;
				if (newsize < count)
				{
					count = newsize;
				}
				for (int i = 0;i < count;i++)
				{
					vec[i] = Vector[i];
				}
				delete[] Vector;
				Vector = 0;
			}
			Vector = vec;
			VectorMax = newsize;
		}
		else
		{
			VectorMax = 0;
			if (Vector)
			{
				delete[] Vector;
				Vector = 0;
			}
		}
		return true;
	}
	virtual bool Uninitialised_Grow(int newsize)
	{
		if (newsize <= VectorMax)
		{
			return true;
		}
		if (newsize > 0)
		{
			if (Vector)
			{
				delete[] Vector;
			}
			Vector = new T[newsize];
			VectorMax = newsize;
		}
		return true;
	}
	void Uninitialized_Resize(int newsize)
	{
		delete[] Vector;
		Vector = new T[newsize];
		VectorMax = newsize;
	}
	int Length() const
	{
		return VectorMax;
	}
	T &operator[](int index)
	{
		return Vector[index];
	}
	T const &operator[](int index) const
	{
		return Vector[index];
	}
    T* Peek()
    {
        return Vector;
    }
    const T* Peek() const
    {
        return Vector;
    }
	void Zero_Memory()
	{
		if (Vector != NULL)
		{
			memset(Vector,0,VectorMax * sizeof(T));
		}
	}
}; // 000C

template <class T> class SimpleDynVecClass :
	public SimpleVecClass<T>
{
protected:
	int ActiveCount; // 000C
	bool Grow(int new_size_hint)
	{
		int new_size = __max(VectorMax + VectorMax/4,VectorMax + 4);
		new_size = __max(new_size,new_size_hint);
		return Resize(new_size);
	}
	bool Shrink(void)
	{
		if (ActiveCount < VectorMax/4)
		{
			return Resize(ActiveCount);
		}
		return true;
	}
public:
	virtual ~SimpleDynVecClass()
	{
		ActiveCount = 0;
	}
	explicit SimpleDynVecClass(int size = 0) : SimpleVecClass<T>(size)
	{
		ActiveCount = 0;
	}
	SimpleDynVecClass(const SimpleDynVecClass<T>& vector): SimpleVecClass(vector), ActiveCount(vector.ActiveCount)
	{
		/* nothing */
	}
	SimpleDynVecClass<T>& operator =(const SimpleDynVecClass<T>& vector)
	{
		if (this != &vector)
		{
			SimpleVecClass<T>::operator =(vector);
			ActiveCount = vector.ActiveCount;
		}
		return *this;
	}
	int Find_Index(T const & object)
	{
		for (int index = 0;index < Count();index++)
		{
			if (Vector[index] == object)
			{
				return index;
			}
		}
		return -1;
	}
	int Count() const
	{
		return ActiveCount;
	}
	T &operator[](int index)
	{
		return Vector[index];
	}
	T const &operator[](int index) const
	{
		return Vector[index];
	}
	bool Resize(int newsize)
	{
		if (SimpleVecClass<T>::Resize(newsize))
		{
			if (VectorMax < ActiveCount)
			{
				ActiveCount = VectorMax;
			}
			return true;
		}
		return false;
	}
	bool Add(T const& data, int new_size_hint = 0)
	{
		if (ActiveCount >= VectorMax)
		{
			if (!Grow(new_size_hint))
			{
				return false;
			}
		}
		Vector[ActiveCount++] = data;
		return true;
	}
	T *Add_Multiple(int number_to_add)
	{
		int index = ActiveCount;
		ActiveCount += number_to_add;
		if (ActiveCount >= VectorMax)
		{
			Grow( ActiveCount );
		}
		return &Vector[index];
	}
	bool Add_Head(const T& object)
	{
		return Insert(0, object);
	}
	bool Insert(int index, const T& object)
	{
		if (ActiveCount >= VectorMax)
		{
			if (!Grow(0))
			{
				return false;
			}
		}
		if (index < ActiveCount)
		{
			memmove(&Vector[index+1], &Vector[index], (ActiveCount-index) * sizeof(T));
		}
		Vector[index] = object;
		++ActiveCount;
		return true;
	}
	bool Delete(int index,bool allow_shrink = true)
	{
		if (index < ActiveCount-1)
		{
			memmove(&(Vector[index]),&(Vector[index+1]),(ActiveCount - index - 1) * sizeof(T));
		}
		ActiveCount--;
		if (allow_shrink)
		{
			Shrink();
		}
		return true;
	}
	bool Delete(T const & object,bool allow_shrink = true)
	{
		int id = Find_Index(object);
		if (id != -1)
		{
			return Delete(id,allow_shrink);
		}
		return false;
	}
	bool Delete_Range(int start,int count,bool allow_shrink = true)
	{
		if (start < ActiveCount - count)
		{
			memmove(&(Vector[start]),&(Vector[start + count]),(ActiveCount - start - count) * sizeof(T));
		}
		ActiveCount -= count;
		if (allow_shrink)
		{
			Shrink();
		}
		return true;
	}
	void Delete_All(bool allow_shrink = true)
	{
		ActiveCount = 0;
		if (allow_shrink)
		{
			Shrink();
		}
	}
	void qsort(int (*compareCallback)(const T&, const T&))
	{
		::qsort(Vector, ActiveCount, sizeof(T), (int (*)(const void*, const void*))compareCallback);
	}
	bool isEmpty() const { return ActiveCount == 0; }
}; // 0010
inline ulong SwapBytes(ulong ui)
{
    return (ui >> 24) |
         ((ui<<8) & 0x00FF0000) |
         ((ui>>8) & 0x0000FF00) |
         (ui << 24);
}
inline char *newstr(const char *str)
{
	if (str)
	{
		size_t len = strlen(str)+1;
		char *s = new char[len];
		memcpy(s,str,len);
		return s;	
	}
	return 0;
};
struct FormHeader
{
	ulong type;
	ulong dataSize;
	ulong flags;
	formid id;
	ulong vcinfo1;
	ushort formVersion;
	ushort vcinfo2;
};
struct TypeGroupHeader
{
	ulong type;
	ulong groupSize;
	ulong label;
	ulong groupType;
	ulong stamp;
	ulong unknown;
};
struct ParentGroupHeader
{
	ulong type;
	ulong groupSize;
	formid parent;
	ulong groupType;
	ulong stamp;
	ulong unknown;
};
struct InteriorCellHeader
{
	ulong type;
	ulong groupSize;
	long blockNumber;
	ulong groupType;
	ulong stamp;
	ulong unknown;
};
struct ExteriorCellHeader
{
	ulong type;
	ulong groupSize;
	short Y;
	short X;
	ulong groupType;
	ulong stamp;
	ulong unknown;
};
#if 0
struct TESGlobal
{
	formid global;
	float value;
};
struct DeathCount
{
	formid actor;
	ushort deathCount;
};
struct Crime
{
	ubyte unk10;
	ubyte isBountyApplied;
	ubyte isGuardComing;
	ulong crimeType;
	ulong stealingAmount;
	ulong crimeId;
	formid target;
	formid criminal;
	formid stealingForm;
	formid owner;
	ushort witnessCount;
	formid *witnesses;
};
struct SpectatorEventParticipant
{
	formid actor;
	ubyte isEventSource;
	ulong unk2;
};
class SpectatorPackageData;
struct SpectatorEvent
{
	ushort participantCount;
	SpectatorEventParticipant *participants;
	formid actor;
	formid package;
	SpectatorPackageData *packageData;
	ulong unk1;
	ulong unk2;
	NiPoint3 eventCenter;
	float unkTimer;
};
struct QuickKey
{
	ubyte count;
	formid *keys;
};
struct Region
{
	formid id;
	float unk;
};
struct ChangeRecordHeader
{
	formid id;
	ubyte type;
	ulong flags;
	ubyte version;
	ushort dataSize;
};
struct ReactionInfo
{
	formid target;
	ulong reaction;
};
struct NPCFaction
{
	formid faction;
	ubyte rank;
};
struct Modifier
{
	ubyte valueIndex;
	float modValue;
};
struct QuestStageItem
{
	ubyte index;
	ushort dayOfYear;
	ushort year;
};
struct QuestStageStruct
{
	ubyte index;
	ubyte flags;
	ubyte itemCount;
	QuestStageItem *items;
};
struct ScriptVar
{
	ulong flags;
	formid id;
	double value;
};
struct ScriptEffectInfo
{
	bool bRunEffectStartBlock;
	bool bRunEffectFinishBlock;
	ubyte pad[2];
	float ElapsedSeconds;
};
enum CreatedFlags
{
	ArrowProjectile = 1,
	MagicProjectile = 2,
	WorldItem = 3
};
struct MovedData
{
	formid cell;
	NiPoint3 pos;
	NiPoint3 rot;
};
struct ChangedData
{
	formid cell;
	NiPoint3 pos;
	MovedData data;
};
struct CreatedData
{
	ulong flags;
	formid baseItem;
	MovedData data;
};;
struct Point
{
	NiPoint3 pos;
	ulong connections;
};
struct EffectItem
{
	ulong effectID;
	ulong effectID2;
	ulong magnitude;
	ulong area;
	ulong duration;
	ulong type;
	ulong actorValueIndex;
	ulong scriptSize;
	formid scriptEffect;
	ulong scriptMagicSchool;
	ulong scriptVisualEffect;
	ulong scriptFlags;
	char *scriptName;
	bool hasEFMEData;
	ubyte version;
	ubyte beta;
	ubyte minor;
	ubyte major;
	ubyte efitParam;
	ubyte efixParam;
	ubyte efmeReserved[0xA];
	char *icon;
	bool hasEFIXData;
	ulong efixOverrides;
	ulong efixFlags;
	float efixBaseCost;
	ulong efixResistAV;
	ubyte efixReserved[0x10];
	EffectItem() : effectID(0), magnitude(0), area(0), duration(0), type(0), actorValueIndex(0), scriptSize(0), scriptEffect(0), scriptMagicSchool(0), scriptVisualEffect(0), scriptFlags(0), scriptName(0), hasEFMEData(false), version(0), beta(0), minor(0), major(0), efitParam(0), efixParam(0), icon(0), hasEFIXData(false), efixOverrides(0), efixFlags(0), efixBaseCost(0), efixResistAV(0)
	{
	}
};
struct FactionRef
{
	formid faction;
	ulong rank;
};
#endif
