/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <map>
#include <string>
#include "nvsfile.h"
#include "form.h"
#include "modfile.h"
/*
#include "changerecord.h"
#include "SpectatorPackageData.h"
NVSFile::NVSFile(): fileId(0), pcName(0), pcLocation(0), screenshotData(0), plugins(0), pluginModFiles(0), formIdArray(0), worldSpaceIdArray(0), globals(0), deathCounts(0), formHeaders(0), forms(0), spectatorEvents(0), regions(0), changeRecords(0), tempEffects(0)
{
	crimeLists[0] = 0;
	crimeLists[1] = 0;
	crimeLists[2] = 0;
	crimeLists[3] = 0;
	crimeLists[4] = 0;
	crimeLists[5] = 0;
	quickKeys[0].keys = 0;
	quickKeys[1].keys = 0;
	quickKeys[2].keys = 0;
	quickKeys[3].keys = 0;
	quickKeys[4].keys = 0;
	quickKeys[5].keys = 0;
	quickKeys[6].keys = 0;
	quickKeys[7].keys = 0;
	crimeListsGarbage[0] = 0;
	crimeListsGarbage[1] = 0;
	crimeListsGarbage[2] = 0;
	crimeListsGarbage[3] = 0;
	crimeListsGarbage[4] = 0;
	crimeListsGarbage[5] = 0;
}

bool NVSFile::Open(const char *path)
{
	FileRead file(path);
	fileId = file.readstring(12);
	if (strcmp(fileId,"TES4SAVEGAME"))
	{
		return false;
	}
	version1 = file.read<ubyte>();
	if (version1 != 0)
	{
		return false;
	}
	version2 = file.read<ubyte>();
	if (version2 != 125)
	{
		return false;
	}
	exeTime = file.read<systemtime>();
	version3 = file.read<ulong>();
	if (version3 != 125)
	{
		return false;
	}
	saveHeaderSize = file.read<ulong>();
	saveNum = file.read<ulong>();
	pcName = file.readbzstring();
	pcLevel = file.read<ushort>();
	pcLocation = file.readbzstring();
	gameDays = file.read<float>();
	gameTicks = file.read<ulong>();
	gameTime = file.read<systemtime>();
	screenshotSize = file.read<ulong>();
	screenshotWidth = file.read<ulong>();
	screenshotHeight = file.read<ulong>();
	screenshotData = file.readarray<ubyte>(screenshotWidth * screenshotHeight * 3);
	pluginCount = file.read<ubyte>();
	if (pluginCount)
	{
		char obpath[MAX_PATH];
		HKEY key;
		LONG error = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Bethesda Softworks\\Oblivion",0,KEY_READ,&key);
		if (error)
		{
			return false;
		}
		unsigned long size = MAX_PATH;
		unsigned long type;
		error = RegQueryValueEx(key,"Installed Path",0,&type,(BYTE *)&obpath,&size);
		if (error)
		{
			return false;
		}
		RegCloseKey(key);
		plugins = new char *[pluginCount];
		pluginModFiles = new ModFile *[pluginCount];
		if (obpath[strlen(obpath)-1] != '\\')
		{
			strcat(obpath,"\\");
		}
		strcat(obpath,"data");
		char oldpath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,oldpath);
		SetCurrentDirectory(obpath);
		for (ubyte i = 0;i < pluginCount;i++)
		{
			plugins[i] = file.readbstring();
			AddModFile(plugins[i],i);
			pluginModFiles[i] = new ModFile();
			pluginModFiles[i]->Open(plugins[i]);
		}
		SetCurrentDirectory(oldpath);
	}
	formIdsOffset = file.read<ulong>();
	changeRecordCount = file.read<ulong>();
	long pos = file.pos();
	file.seek(formIdsOffset);
	formIdsCount = file.read<ulong>();
	formIdArray = file.readarray<formid>(formIdsCount);
	worldSpaceIdsCount = file.read<ulong>();
	worldSpaceIdArray = file.readarray<formid>(worldSpaceIdsCount);
	file.seek(pos);
	nextObjectid = file.read<ulong>();
	worldId = file.read<formid>();
	worldX = file.read<ulong>();
	worldY = file.read<ulong>();
	pcLocationCell = file.read<formid>();
	pcLocationPos = file.read<NiPoint3>();
	globalsNum = file.read<ushort>();
	if (globalsNum)
	{
		globals = new TESGlobal[globalsNum];
		for (ulong i = 0;i < globalsNum;i++)
		{
			globals[i].global = GetFormID(file.read<iref>());
			globals[i].value = file.read<float>();
		}
	}
	tesClassSize = file.read<ushort>();
	deathCountsNum = file.read<ulong>();
	if (deathCountsNum)
	{
		deathCounts = new DeathCount[deathCountsNum];
		for (ulong i = 0;i < deathCountsNum;i++)
		{
			deathCounts[i].actor = GetFormID(file.read<iref>());
			deathCounts[i].deathCount = file.read<ushort>();
		}
	}
	gameModeSeconds = file.read<float>();
	processDataSize = file.read<ushort>();
	processDataUnk = file.read<float>();
	for (ulong i = 0;i < 6;i++)
	{
		crimeCount[i] = file.read<ushort>();
		crimeLists[i] = 0;
		if (crimeCount[i])
		{
			crimeLists[i] = new Crime[crimeCount[i]];
			for (ushort j = 0;j < crimeCount[i];j++)
			{
				crimeLists[i][j].unk10 = file.read<ubyte>();
				crimeLists[i][j].isBountyApplied = file.read<ubyte>();
				crimeLists[i][j].isGuardComing = file.read<ubyte>();
				crimeLists[i][j].crimeType = file.read<ulong>();
				crimeLists[i][j].stealingAmount = file.read<ulong>();
				crimeLists[i][j].crimeId = file.read<ulong>();
				crimeLists[i][j].target = GetFormID(file.read<iref>());
				crimeLists[i][j].criminal = GetFormID(file.read<iref>());
				crimeLists[i][j].stealingForm = GetFormID(file.read<iref>());
				crimeLists[i][j].owner = GetFormID(file.read<iref>());
				crimeLists[i][j].witnessCount = file.read<ushort>();
				crimeLists[i][j].witnesses = 0;
				if (crimeLists[i][j].witnessCount)
				{
					crimeLists[i][j].witnesses = new formid[crimeLists[i][j].witnessCount];
					for (ushort k = 0;k < crimeLists[i][j].witnessCount;k++)
					{
						crimeLists[i][j].witnesses[k] = GetFormID(file.read<iref>());
					}
				}
			}
		}
	}
	for (ulong i = 0;i < 6;i++)
	{
		crimeListsGarbage[i] = file.readarray<ubyte>(crimeCount[i] * 4);
	}
	specEventDataSize = file.read<ushort>();
	spectatorEventCount = file.read<ushort>();
	if (spectatorEventCount)
	{
		spectatorEvents = new SpectatorEvent[spectatorEventCount];
		for (ushort i = 0;i < spectatorEventCount;i++)
		{
			spectatorEvents[i].participantCount = file.read<ushort>();
			spectatorEvents[i].participants = 0;
			if (spectatorEvents[i].participantCount)
			{
				spectatorEvents[i].participants = new SpectatorEventParticipant[spectatorEvents[i].participantCount];
				for (ushort j = 0;j < spectatorEvents[i].participantCount;j++)
				{
					spectatorEvents[i].participants[j].actor = GetFormID(file.read<iref>());
					spectatorEvents[i].participants[j].isEventSource = file.read<ubyte>();
					spectatorEvents[i].participants[j].unk2 = file.read<ulong>();
				}
			}
			spectatorEvents[i].actor = GetFormID(file.read<iref>());
			spectatorEvents[i].package = GetFormID(file.read<iref>());
			spectatorEvents[i].packageData = new SpectatorPackageData();
			spectatorEvents[i].packageData->Load(&file,this);
			spectatorEvents[i].unk1 = file.read<ulong>();
			spectatorEvents[i].unk2 = file.read<ulong>();
			spectatorEvents[i].eventCenter = file.read<NiPoint3>();
			spectatorEvents[i].unkTimer = file.read<float>();
		}
	}
	weatherSize = file.read<ushort>();
	weather1 = GetFormID(file.read<iref>());
	weather2 = GetFormID(file.read<iref>());
	weather3 = GetFormID(file.read<iref>());
	weather4 = GetFormID(file.read<iref>());
	weatherf1 = file.read<float>();
	weatherf2 = file.read<float>();
	weatherf3 = file.read<float>();
	weatheri1 = file.read<ulong>();
	weatheri2 = file.read<ulong>();
	weatherf4 = file.read<float>();
	playerCombatCount = file.read<ulong>();
	createdNum = file.read<ulong>();
	if (createdNum)
	{
		formHeaders = new FormHeader[createdNum];
		for (ulong i = 0;i < createdNum;i++)
		{
			formHeaders[i] = file.read<FormHeader>();
			Form *mr = CreateForm(formHeaders[i],0);
			if (!mr)
			{
				return false;
			}
			mr->Load(&file);
			forms.Add(mr);
		}
	}
	quickKeysDataSize = file.read<ushort>();
	for (ulong i = 0;i < 8;i++)
	{
		quickKeys[i].count = file.read<ubyte>();
		quickKeys[i].keys = 0;
		if (quickKeys[i].count)
		{
			quickKeys[i].keys = new formid[quickKeys[i].count];
			for (ubyte j = 0;j < quickKeys[i].count;j++)
			{
				quickKeys[i].keys[j] = GetFormID(file.read<iref>());
			}
		}
	}
	reticuleDataSize = file.read<ushort>();
	enemyHealth = file.read<float>();
	interfaceDataSize = file.read<ushort>();
	statsMenuCurrentTab = file.read<ubyte>();
	inventoryMenuCurrentTab = file.read<ubyte>();
	magicMenuCurrentTab = file.read<ubyte>();
	mapMenuCurrentTab = file.read<ubyte>();
	hudMainCurrentTab = file.read<ulong>();
	interface6 = file.read<ubyte>();
	regionDataSize = file.read<ushort>();
	regionCount = file.read<ushort>();
	if (regionCount)
	{
		regions = new Region[regionCount];
		for (ushort i = 0;i < regionCount;i++)
		{
			regions[i].id = GetFormID(file.read<iref>());
			regions[i].unk = file.read<float>();
		}
	}
	if (changeRecordCount)
	{
		changeRecordHeaders = new ChangeRecordHeader[changeRecordCount];
		for (ulong i = 0;i < changeRecordCount;i++)
		{
			changeRecordHeaders[i].id = file.read<formid>();
			changeRecordHeaders[i].type = file.read<ubyte>();
			changeRecordHeaders[i].flags = file.read<ulong>();
			changeRecordHeaders[i].version = file.read<ubyte>();
			if (changeRecordHeaders[i].version != 125)
			{
				return false;
			}
			changeRecordHeaders[i].dataSize = file.read<ushort>();
			int posx = file.pos();
			posx = 0;
			ChangeRecord *cr = CreateChangeRecord(changeRecordHeaders[i],this);
			if (!cr)
			{
				return false;
			}
			cr->Load(&file);
			changeRecords.Add(cr);
		}
	}
	tempEffectsSize = file.read<ulong>();
	tempEffectCount = file.read<ushort>();
	tempEffects = file.readarray<ubyte>(tempEffectCount);
	return true;
}
void NVSFile::Save(const char *path)
{
	FileWrite file(path);
	file.writestring(12,fileId);
	file.write<ubyte>(version1);
	file.write<ubyte>(version2);
	file.write<systemtime>(exeTime);
	file.write<ulong>(version3);
	file.write<ulong>(saveHeaderSize);
	file.write<ulong>(saveNum);
	file.writebzstring(pcName);
	file.write<ushort>(pcLevel);
	file.writebzstring(pcLocation);
	file.write<float>(gameDays);
	file.write<ulong>(gameTicks);
	file.write<systemtime>(gameTime);
	file.write<ulong>(screenshotSize);
	file.write<ulong>(screenshotWidth);
	file.write<ulong>(screenshotHeight);
	file.writearray<ubyte>(screenshotWidth * screenshotHeight * 3,screenshotData);
	file.write<ubyte>(pluginCount);
	if (pluginCount)
	{
		for (ulong i = 0;i < pluginCount;i++)
		{
			file.writebstring(plugins[i]);
		}
	}
	file.write<ulong>(formIdsOffset);
	file.write<ulong>(changeRecordCount);
	file.write<ulong>(nextObjectid);
	file.write<formid>(worldId);
	file.write<ulong>(worldX);
	file.write<ulong>(worldY);
	file.write<formid>(pcLocationCell);
	file.write<NiPoint3>(pcLocationPos);
	file.write<ushort>(globalsNum);
	if (globalsNum)
	{
		for (ulong i = 0;i < globalsNum;i++)
		{
			file.write<iref>(GetFormiRef(globals[i].global));
			file.write<float>(globals[i].value);
		}
	}
	file.write<ushort>(tesClassSize);
	file.write<ulong>(deathCountsNum);
	if (deathCountsNum)
	{
		for (ulong i = 0;i < deathCountsNum;i++)
		{
			file.write<iref>(GetFormiRef(deathCounts[i].actor));
			file.write<ushort>(deathCounts[i].deathCount);
		}
	}
	file.write<float>(gameModeSeconds);
	file.write<ushort>(processDataSize);
	file.write<float>(processDataUnk);
	for (ulong i = 0;i < 6;i++)
	{
		file.write<ushort>(crimeCount[i]);
		if (crimeCount[i])
		{
			for (ushort j = 0;j < crimeCount[i];j++)
			{
				file.write<ubyte>(crimeLists[i][j].unk10);
				file.write<ubyte>(crimeLists[i][j].isBountyApplied);
				file.write<ubyte>(crimeLists[i][j].isGuardComing);
				file.write<ulong>(crimeLists[i][j].crimeType);
				file.write<ulong>(crimeLists[i][j].stealingAmount);
				file.write<ulong>(crimeLists[i][j].crimeId);
				file.write<iref>(GetFormiRef(crimeLists[i][j].target));
				file.write<iref>(GetFormiRef(crimeLists[i][j].criminal));
				file.write<iref>(GetFormiRef(crimeLists[i][j].stealingForm));
				file.write<iref>(GetFormiRef(crimeLists[i][j].owner));
				file.write<ushort>(crimeLists[i][j].witnessCount);
				if (crimeLists[i][j].witnessCount)
				{
					for (ushort k = 0;k < crimeLists[i][j].witnessCount;k++)
					{
						file.write<iref>(GetFormiRef(crimeLists[i][j].witnesses[k]));
					}
				}
			}
		}
	}
	for (ulong i = 0;i < 6;i++)
	{
		file.writearray<ubyte>(crimeCount[i] * 4,crimeListsGarbage[i]);
	}
	file.write<ushort>(specEventDataSize);
	file.write<ushort>(spectatorEventCount);
	if (spectatorEventCount)
	{
		for (ushort i = 0;i < spectatorEventCount;i++)
		{
			file.write<ushort>(spectatorEvents[i].participantCount);
			if (spectatorEvents[i].participantCount)
			{
				for (ushort j = 0;j < spectatorEvents[i].participantCount;j++)
				{
					file.write<iref>(GetFormiRef(spectatorEvents[i].participants[j].actor));
					file.write<ubyte>(spectatorEvents[i].participants[j].isEventSource);
					file.write<ulong>(spectatorEvents[i].participants[j].unk2);
				}
			}
			file.write<iref>(GetFormiRef(spectatorEvents[i].actor));
			file.write<iref>(GetFormiRef(spectatorEvents[i].package));
			spectatorEvents[i].packageData->Save(&file,this);
			file.write<ulong>(spectatorEvents[i].unk1);
			file.write<ulong>(spectatorEvents[i].unk2);
			file.write<NiPoint3>(spectatorEvents[i].eventCenter);
			file.write<float>(spectatorEvents[i].unkTimer);
		}
	}
	file.write<ushort>(weatherSize);
	file.write<iref>(GetFormiRef(weather1));
	file.write<iref>(GetFormiRef(weather2));
	file.write<iref>(GetFormiRef(weather3));
	file.write<iref>(GetFormiRef(weather4));
	file.write<float>(weatherf1);
	file.write<float>(weatherf2);
	file.write<float>(weatherf3);
	file.write<ulong>(weatheri1);
	file.write<ulong>(weatheri2);
	file.write<float>(weatherf4);
	file.write<ulong>(playerCombatCount);
	file.write<ulong>(createdNum);
	if (createdNum)
	{
		for (ulong i = 0;i < createdNum;i++)
		{
			file.write<FormHeader>(formHeaders[i]);
			forms[i]->Save(&file);
		}
	}
	file.write<ushort>(quickKeysDataSize);
	for (ulong i = 0;i < 8;i++)
	{
		file.write<ubyte>(quickKeys[i].count);
		if (quickKeys[i].count)
		{
			for (ubyte j = 0;j < quickKeys[i].count;j++)
			{
				file.write<iref>(GetFormiRef(quickKeys[i].keys[j]));
			}
		}
	}
	file.write<ushort>(reticuleDataSize);
	file.write<float>(enemyHealth);
	file.write<ushort>(interfaceDataSize);
	file.write<ubyte>(statsMenuCurrentTab);
	file.write<ubyte>(inventoryMenuCurrentTab);
	file.write<ubyte>(magicMenuCurrentTab);
	file.write<ubyte>(mapMenuCurrentTab);
	file.write<ulong>(hudMainCurrentTab);
	file.write<ubyte>(interface6);
	file.write<ushort>(regionDataSize);
	file.write<ushort>(regionCount);
	if (regionCount)
	{
		for (ushort i = 0;i < regionCount;i++)
		{
			file.write<iref>(GetFormiRef(regions[i].id));
			file.write<float>(regions[i].unk);
		}
	}
	if (changeRecordCount)
	{
		for (ulong i = 0;i < changeRecordCount;i++)
		{
			file.write<formid>(changeRecordHeaders[i].id);
			file.write<ubyte>(changeRecordHeaders[i].type);
			file.write<ulong>(changeRecordHeaders[i].flags);
			file.write<ubyte>(changeRecordHeaders[i].version);
			file.write<ushort>(changeRecordHeaders[i].dataSize);
			changeRecords[i]->Save(&file);
		}
	}
	file.write<ulong>(tempEffectsSize);
	file.write<ushort>(tempEffectCount);
	file.writearray<ubyte>(tempEffectCount,tempEffects);
	file.write<ulong>(formIdsCount);
	file.writearray<formid>(formIdsCount,formIdArray);
	file.write<ulong>(worldSpaceIdsCount);
	file.writearray<formid>(worldSpaceIdsCount,worldSpaceIdArray);
}
formid NVSFile::GetFormID(iref id)
{
	if (id < 0xFF000000)
	{
		return formIdArray[id];
	}
	return id;
}
iref NVSFile::GetFormiRef(formid id)
{
	if (id < 0xFF000000)
	{
		for (ulong i = 0;i < formIdsCount;i++)
		{
			if (formIdArray[i] == id)
			{
				return i;
			}
		}
		return 0;
	}
	return id;
}
formid NVSFile::GetWorldSpaceFormID(ushort id)
{
	return worldSpaceIdArray[id];
}
ushort NVSFile::GetWorldSpaceFormiRef(formid id)
{
	for (ushort i = 0;i < worldSpaceIdsCount;i++)
	{
		if (worldSpaceIdArray[i] == id)
		{
			return i;
		}
	}
	return 0;
}
NVSFile::~NVSFile()
{
	if (fileId)
	{
		delete[] fileId;
	}
	if (pcName)
	{
		delete[] pcName;
	}
	if (pcLocation)
	{
		delete[] pcLocation;
	}
	if (screenshotData)
	{
		delete[] screenshotData;
	}
	if (plugins)
	{
		for (int i = 0;i < pluginCount;i++)
		{
			delete[] plugins[i];
		}
		delete[] plugins;
	}
	if (pluginModFiles)
	{
		for (int i = 0;i < pluginCount;i++)
		{
			delete[] pluginModFiles[i];
		}
		delete[] pluginModFiles;
	}
	if (formIdArray)
	{
		delete[] formIdArray;
	}
	if (worldSpaceIdArray)
	{
		delete[] worldSpaceIdArray;
	}
	if (globals)
	{
		delete[] globals;
	}
	if (deathCounts)
	{
		delete[] deathCounts;
	}
	for (int i = 0;i < 6;i++)
	{
		if (crimeLists[i])
		{
			for (int j = 0;j < crimeCount[i];j++)
			{
				if (crimeLists[i][j].witnesses)
				{
					delete[] crimeLists[i][j].witnesses;
				}
			}
			delete[] crimeLists[i];
		}
		if (crimeListsGarbage[i])
		{
			delete[] crimeListsGarbage[i];
		}
	}
	if (formHeaders)
	{
		delete[] formHeaders;
	}
	for (int i = 0;i < forms.Count();i++)
	{
		delete forms[i];
	}
	forms.Delete_All();
	if (spectatorEvents)
	{
		for (ushort i = 0;i < spectatorEventCount;i++)
		{
			delete[] spectatorEvents[i].participants;
			delete spectatorEvents[i].packageData;
		}
		delete[] spectatorEvents;
	}
	for (int i = 0;i < 8;i++)
	{
		if (quickKeys[i].keys)
		{
			delete[] quickKeys[i].keys;
		}
	}
	if (regions)
	{
		delete[] regions;
	}
	if (changeRecordHeaders)
	{
		delete[] changeRecordHeaders;
	}
	if (tempEffects)
	{
		delete[] tempEffects;
	}
	for (int i = 0;i < changeRecords.Count();i++)
	{
		delete changeRecords[i];
	}
	changeRecords.Delete_All();
}*/
std::map<std::string,ubyte> masterMap;
ubyte GetLoadIndex(char *name,ubyte pos)
{
	if (masterMap.find(name) != masterMap.end())
	{
		return masterMap[name];
	}
	return pos;
}
void AddModFile(char *name,ubyte index)
{
	masterMap[name] = index;
}
std::map<formid,Form *> formMap;
Form *FindForm(formid id)
{
	if (formMap.find(id) != formMap.end())
	{
		return formMap[id];
	}
	return 0;
}
void AddForm(Form *record)
{
	int id = record->Get_Header().id;
	formMap[record->RemapFormID(id)] = record;
}
void RemoveForm(Form *record)
{
	int id = record->Get_Header().id;
	formMap.erase(record->RemapFormID(id));
}
void ClearForms()
{
	formMap.clear();
}
