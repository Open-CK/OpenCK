/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "fileread.h"
#include "filewrite.h"
class TypeGroup;
class TES4Form;
struct Master
{
	char *name;
	ubyte loadID;
};
enum FormType
{
	NONE = 0,
	TES4 = 1,
	GRUP = 2,
	GMST = 3,
	TXST = 4,
	MICN = 5,
	GLOB = 6,
	CLAS = 7,
	FACT = 8,
	HDPT = 9,
	HAIR = 10,
	EYES = 11,
	RACE = 12,
	SOUN = 13,
	ASPC = 14,
	SKIL = 15,
	MGEF = 16,
	SCPT = 17,
	LTEX = 18,
	ENCH = 19,
	SPEL = 20,
	ACTI = 21,
	TACT = 22,
	TERM = 23,
	ARMO = 24,
	BOOK = 25,
	CLOT = 26,
	CONT = 27,
	DOOR = 28,
	INGR = 29,
	LIGH = 30,
	MISC = 31,
	STAT = 32,
	SCOL = 33,
	MSTT = 34,
	PWAT = 35,
	GRAS = 36,
	TREE = 37,
	FLOR = 38,
	FURN = 39,
	WEAP = 40,
	AMMO = 41,
	NPC_ = 42,
	CREA = 43,
	LVLC = 44,
	LVLN = 45,
	KEYM = 46,
	ALCH = 47,
	IDLM = 48,
	NOTE = 49,
	COBJ = 50,
	PROJ = 51,
	LVLI = 52,
	WTHR = 53,
	CMLT = 54,
	REGN = 55,
	NAVI = 56,
	CELL = 57,
	REFR = 58,
	ACHR = 59,
	ACRE = 60,
	PMIS = 61,
	PGRE = 62,
	PBEA = 63,
	PFLA = 64,
	WRLD = 65,
	LAND = 66,
	NAVM = 67,
	TLOD = 68,
	DIAL = 69,
	INFO = 70,
	QUST = 71,
	IDLE = 72,
	PACK = 73,
	CSTY = 74,
	LSCR = 75,
	LVSP = 76,
	ANIV = 77,
	WATR = 78,
	EFSH = 79,
	TOFT = 80,
	EXPL = 81,
	DEBR = 82,
	IMGS = 83,
	IMAD = 84,
	FLST = 85,
	PERK = 86,
	BPTD = 87,
	ADDN = 88,
	AVIF = 89,
	RADS = 90,
	CAMS = 91,
	CPTH = 92,
	VTYP = 93,
	IPCT = 94,
	IPDS = 95,
	ARMA = 96,
	ECZN = 97,
	MESG = 98,
	RGDL = 99,
	DOBJ = 100,
	LGTN = 101,
	MUSC = 102
};
class ModFile {
protected:
	FormHeader h;
	TES4Form *header;
	char *fname;
	SimpleDynVecClass<TypeGroupHeader> typeGroupHeaders;
	SimpleDynVecClass<TypeGroup *> typeGroups;
	SimpleDynVecClass<Master> masters;
public:
	ModFile();
	void Open(const char *path);
	void Save(const char *path);
	virtual ~ModFile();
	int GroupCount()
	{
		return typeGroups.Count();
	}
	TypeGroup *GetGroup(int pos)
	{
		return typeGroups[pos];
	}
	ubyte GetLoadID(ubyte index)
	{
		return masters[index].loadID;
	}
};
