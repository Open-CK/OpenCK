/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
/*
#include "changerecord.h"
#include "itemchangerecord.h"
#include "factionchagerecord.h"
#include "bookchangerecord.h"
#include "creaturechangerecord.h"
#include "npcchangerecord.h"
#include "questchangerecord.h"
#include "cellchangerecord.h"
#include "unparsedchangerecord.h"
#include "refrchangerecord.h"
ChangeRecord *CreateChangeRecord(ChangeRecordHeader header,NVSFile *p)
{
	switch (header.type)
	{
	case GLOB:
	case CLAS:
	case HAIR:
	case EYES:
	case RACE:
	case SOUN:
	case SKIL:
	case MGEF:
	case SCPT:
	case LTEX:
	case ENCH:
	case SPEL:
	case BSGN:
	case ACTI:
	case CONT:
	case DOOR:
	case INGR:
	case STAT:
	case GRAS:
	case TREE:
	case FLOR:
	case FURN:
	case LVLC:
	case ALCH:
	case SBSP:
	case LVLI:
	case WTHR:
	case CLMT:
	case REGN:
	case PGRD:
	case WRLD:
	case LAND:
	case ROAD:
	case DIAL:
	case IDLE:
	case CSTY:
	case LSCR:
	case LVSP:
	case ANIO:
	case WATR:
	case EFSH:
	case INFO:
	case PACK:
		return new ChangeRecord(header,p);
	case APPA:
	case MISC:
	case SLGM:
	case KEYM:
	case SGST:
	case ARMO:
	case CLOT:
	case LIGH:
	case WEAP:
	case AMMO:
		return new ItemChangeRecord(header,p);
	case FACT:
		return new FactionChangeRecord(header,p);
	case BOOK:
		return new BookChangeRecord(header,p);
	case NPC_:
		return new NPCChangeRecord(header,p);
	case CREA:
		return new CreatureChangeRecord(header,p);
	case CELL:
		return new CellChangeRecord(header,p);
	case REFR:
		return new RefrChangeRecord(header,p); //TESObjectREFR::LoadGame
	case ACHR:
	case ACRE:
		return new UnparsedChangeRecord(header,p); //Actor::LoadGame
	case QUST:
		return new QuestChangeRecord(header,p);
	default:
		return 0;
	}
}
*/
