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
#include <string.h>
class ChangeRecord;
class Form;
class ModFile;
class NVSFile;
#if 0
class NVSFile {
protected:
	char *fileId;
	ubyte version1;
	ubyte version2;
	systemtime exeTime;
	ulong version3;
	ulong saveHeaderSize;
	ulong saveNum;
	char *pcName;
	ushort pcLevel;
	char *pcLocation;
	float gameDays;
	ulong gameTicks;
	systemtime gameTime;
	ulong screenshotSize;
	ulong screenshotWidth;
	ulong screenshotHeight;
	ubyte *screenshotData;
	ubyte pluginCount;
	char **plugins;
	ModFile **pluginModFiles;
	ulong formIdsCount;
	formid *formIdArray;
	ulong worldSpaceIdsCount;
	formid *worldSpaceIdArray;
	ulong formIdsOffset;
	ulong changeRecordCount;
	formid nextObjectid;
	formid worldId;
	ulong worldX;
	ulong worldY;
	formid pcLocationCell;
	NiPoint3 pcLocationPos;
	ushort globalsNum;
	TESGlobal *globals;
	ushort tesClassSize;
	ulong deathCountsNum;
	DeathCount *deathCounts;
	float gameModeSeconds;
	ushort processDataSize;
	float processDataUnk;
	ushort crimeCount[6];
	Crime *crimeLists[6];
	ubyte *crimeListsGarbage[6];
	ushort specEventDataSize;
	ushort spectatorEventCount;
	SpectatorEvent *spectatorEvents;
	ushort weatherSize;
	formid weather1;
	formid weather2;
	formid weather3;
	formid weather4;
	float weatherf1;
	float weatherf2;
	float weatherf3;
	ulong weatheri1;
	ulong weatheri2;
	float weatherf4;
	ulong playerCombatCount;
	ulong createdNum;
	FormHeader *formHeaders;
	SimpleDynVecClass<Form *> forms;
	ushort quickKeysDataSize;
	QuickKey quickKeys[8];
	ushort reticuleDataSize;
	float enemyHealth;
	ushort interfaceDataSize;
	ubyte statsMenuCurrentTab;
	ubyte inventoryMenuCurrentTab;
	ubyte magicMenuCurrentTab;
	ubyte mapMenuCurrentTab;
	ulong hudMainCurrentTab;
	ubyte interface6;
	ushort regionDataSize;
	ushort regionCount;
	Region *regions;
	ChangeRecordHeader *changeRecordHeaders;
	SimpleDynVecClass<ChangeRecord *> changeRecords;
	ulong tempEffectsSize;
	ushort tempEffectCount;
	ubyte *tempEffects;
public:
	NVSFile();
	bool Open(const char *path);
	void Save(const char *path);
	formid GetFormID(iref id);
	formid GetWorldSpaceFormID(ushort id);
	iref GetFormiRef(formid id);
	ushort GetWorldSpaceFormiRef(formid id);
	virtual ~NVSFile();
};
#endif
ubyte GetLoadIndex(char *name,ubyte pos);
void AddModFile(char *name,ubyte index);
Form *FindForm(formid id);
void AddForm(Form *record);
void RemoveForm(Form *record);
void ClearForms();
