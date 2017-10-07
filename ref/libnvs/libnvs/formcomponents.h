/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
//fullname data
class FullName
{
public:
	char *fullName;
	FullName() : fullName(0)
	{
	}
	virtual ~FullName()
	{
		if (fullName)
		{
			delete[] fullName;
		}
	}
	FullName & operator = (const FullName & that)
	{
		fullName = newstr(that.fullName);
		return *this;
	}
};
#define FullNameLoad() \
			case 'FULL': \
				fullName = f->readzstring(h.size); \
				readSize += h.size; \
				break;
#define FullNameSave() \
		WriteZStringSubrecord('FULL',fullName,f);
#define FullNameGetSaveSize() \
		size += ZStringSubrecordSize(fullName);

//description data
class Description
{
public:
	char *description;
	Description() : description(0)
	{
	}
	virtual ~Description()
	{
		if (description)
		{
			delete[] description;
		}
	}
	Description & operator = (const Description & that)
	{
		description = newstr(that.description);
		return *this;
	}
};
#define DescriptionLoad() \
			case 'DESC': \
				description = f->readzstring(h.size); \
				readSize += h.size; \
				break;
#define DescriptionSave() \
		WriteZStringSubrecord('DESC',description,f);
#define DescriptionGetSaveSize() \
		size += ZStringSubrecordSize(description);

//texture data
class Texture
{
public:
	char *texture;
	Texture() : texture(0)
	{
	}
	virtual ~Texture()
	{
		if (texture)
		{
			delete[] texture;
		}
	}
	Texture & operator = (const Texture & that)
	{
		texture = newstr(that.texture);
		return *this;
	}
};
#define TextureLoad(tex,srid) \
			case srid: \
				tex->texture = f->readzstring(h.size); \
				readSize += h.size; \
				break;
#define TextureSave(tex,srid) \
		WriteZStringSubrecord(srid,tex->texture,f);
#define TextureGetSaveSize(tex) \
		size += ZStringSubrecordSize(tex->texture);

class MessageTexture
{
public:
	char *messageTexture;
	MessageTexture() : messageTexture(0)
	{
	}
	virtual ~MessageTexture()
	{
		if (messageTexture)
		{
			delete[] messageTexture;
		}
	}
	MessageTexture & operator = (const MessageTexture & that)
	{
		messageTexture = newstr(that.messageTexture);
		return *this;
	}
};
#define MessageTextureLoad(tex,srid) \
			case srid: \
				tex->messageTexture = f->readzstring(h.size); \
				readSize += h.size; \
				break;
#define MessageTextureSave(tex,srid) \
		WriteZStringSubrecord(srid,tex->messageTexture,f);
#define MessageTextureGetSaveSize(tex) \
		size += ZStringSubrecordSize(tex->messageTexture);

//reaction data
struct FactionReaction
{
	formid faction;
	long mod;
	ulong combatReaction;
};
class Reaction
{
public:
	SimpleDynVecClass<FactionReaction> reactions;
};

#define ReactionLoad() \
			case 'XNAM': \
				{ \
					FactionReaction r = f->read<FactionReaction>(); \
					readSize += sizeof(FactionReaction); \
					reactions.Add(r); \
				} \
				break;
#define ReactionSave() \
		for (int reactioncount = 0;reactioncount < reactions.Count();reactioncount++) \
		{ \
			WriteSubrecord('XNAM',sizeof(FactionReaction),f); \
			f->write<FactionReaction>(reactions[reactioncount]); \
		}
#define ReactionGetSaveSize() \
		for (int reactioncount = 0;reactioncount < reactions.Count();reactioncount++) \
		{ \
			size += ComputeSubrecordSize(sizeof(FactionReaction)); \
		}

//soundfile data
class SoundFile
{
public:
	char *soundFile;
	SoundFile() : soundFile(0)
	{
	}
	virtual ~SoundFile()
	{
		if (soundFile)
		{
			delete[] soundFile;
		}
	}
	SoundFile & operator = (const SoundFile & that)
	{
		soundFile = newstr(that.soundFile);
		return *this;
	}
};
#define SoundFileLoad() \
			case 'FNAM': \
				soundFile = f->readzstring(h.size); \
				readSize += h.size; \
				break;
#define SoundFileSave() \
		WriteZStringSubrecord('FNAM',soundFile,f);
#define SoundFileGetSaveSize() \
		size += ZStringSubrecordSize(soundFile);

//model data
struct TextureHash
{
	ulong filenameHash1;
	ulong filenameHash2;
	ulong unkHash1;
	ulong unkHash2;
	ulong pathHash1;
	ulong pathHash2;
};

struct AlternateTexture
{
	char *name;
	formid texture;
	long index;
	AlternateTexture() : name(0), texture(0), index(0)
	{
	}
	virtual ~AlternateTexture()
	{
		if (name)
		{
			delete[] name;
		}
	}
	AlternateTexture & operator = (const AlternateTexture & that)
	{
		name = newstr(that.name);
		return *this;
	}
};

class Model
{
public:
	char *model;
	int modellen;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	float boundRadius;
	bool boundRadiusSeen;
	Model() : model(0), textureHashesCount(0), textureHashes(0), boundRadiusSeen(false)
	{
	}
	virtual ~Model()
	{
		if (model)
		{
			delete[] model;
		}
		if (textureHashes)
		{
			delete[] textureHashes;
		}
	}
	Model & operator = (const Model & that)
	{
		model = newstr(that.model);
		textureHashesCount = that.textureHashesCount;
		textureHashes = new TextureHash[textureHashesCount];
		memcpy(textureHashes,that.textureHashes,textureHashesCount * sizeof(TextureHash));
		return *this;
	}
};

#define ModelBRLoad(mod,srid1,br,srid2) \
			case srid1: \
				mod->model = f->readzstring(h.size); \
				mod->modellen = h.size; \
				readSize += h.size; \
				break; \
			case br: \
				mod->boundRadiusSeen = true; \
				mod->boundRadius = f->read<float>(); \
				readSize += h.size; \
				break; \
			case srid2: \
				mod->textureHashesCount = h.size / sizeof(TextureHash); \
				mod->textureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash)); \
				readSize += h.size; \
				break;
#define ModelBRSave(mod,srid1,br,srid2) \
		WriteZStringSubrecord2(srid1,mod->model,mod->modellen,f); \
		if (mod->boundRadiusSeen) \
		{ \
			WriteSubrecord(br,4,f); \
			f->write<float>(mod->boundRadius); \
		} \
		if (mod->textureHashesCount) \
		{ \
			WriteSubrecord(srid2,mod->textureHashesCount * sizeof(TextureHash),f); \
			f->writearray<TextureHash>(mod->textureHashesCount,mod->textureHashes); \
		}
#define ModelBRGetSaveSize(mod) \
		size += ZStringSubrecordSize2(mod->model,mod->modellen); \
		if (mod->boundRadiusSeen) \
		{ \
			size += ComputeSubrecordSize(4); \
		} \
		if (mod->textureHashesCount) \
		{ \
			size += ComputeSubrecordSize(mod->textureHashesCount * sizeof(TextureHash)); \
		}

class ModelTextureSwap : public Model
{
public:
	ulong alternateTextureCount;
	AlternateTexture *alternateTextures;
	ModelTextureSwap() : alternateTextureCount(0), alternateTextures(0)
	{
	}
	virtual ~ModelTextureSwap()
	{
		if (alternateTextures)
		{
			delete[] alternateTextures;
		}
	}
	ModelTextureSwap & operator = (const ModelTextureSwap & that)
	{
		Model::operator=(that);
		alternateTextureCount = that.alternateTextureCount;
		alternateTextures = new AlternateTexture[alternateTextureCount];
		memcpy(alternateTextures,that.alternateTextures,alternateTextureCount * sizeof(AlternateTexture));
		return *this;
	}
};

#define ModelTextureSwapBRLoad(mod,srid1,br,srid2,srid3) \
			ModelBRLoad(mod,srid1,br,srid2); \
			case srid3: \
				mod->alternateTextureCount = f->read<ulong>(); \
				mod->alternateTextures = new AlternateTexture[mod->alternateTextureCount]; \
				for (ulong texturecount = 0;texturecount < mod->alternateTextureCount;texturecount++) \
				{ \
					mod->alternateTextures[texturecount].name = f->readlstring(); \
					mod->alternateTextures[texturecount].texture = f->read<formid>(); \
					mod->alternateTextures[texturecount].index = f->read<long>(); \
				} \
				readSize += h.size; \
				break;
#define ModelTextureSwapBRSave(mod,srid1,br,srid2,srid3) \
		ModelBRSave(mod,srid1,br,srid2); \
		if (mod->alternateTextureCount) \
		{ \
			ulong size = 4; \
			for (ulong texturecount = 0;texturecount < mod->alternateTextureCount;texturecount++) \
			{ \
				size += 4; \
				size += strlen(mod->alternateTextures[texturecount].name); \
				size += 4; \
				size += 4; \
			} \
			WriteSubrecord(srid3,size,f); \
			f->write<ulong>(mod->alternateTextureCount); \
			for (ulong texturecount = 0;texturecount < mod->alternateTextureCount;texturecount++) \
			{ \
				f->writelstring(mod->alternateTextures[texturecount].name); \
				f->write<formid>(mod->alternateTextures[texturecount].texture); \
				f->write<ulong>(mod->alternateTextures[texturecount].index); \
			} \
		}
#define ModelTextureSwapBRGetSaveSize(mod) \
		ModelBRGetSaveSize(mod); \
		if (mod->alternateTextureCount) \
		{ \
			size += ComputeSubrecordSize(4); \
			for (ulong texturecount = 0;texturecount < mod->alternateTextureCount;texturecount++) \
			{ \
				size += 4; \
				size += strlen(mod->alternateTextures[texturecount].name); \
				size += 4; \
				size += 4; \
			} \
		}

class ModelFaceGenFlags
{
public:
	ubyte flags;
	ModelFaceGenFlags() : flags(0)
	{
	}
};

#define ModelFaceGenFlagsLoad(mod,srid) \
			case srid: \
				mod->flags = f->read<ubyte>(); \
				readSize += 1; \
				break;
#define ModelFaceGenFlagsSave(mod,srid) \
		if (mod->flags) \
		{ \
			WriteSubrecord(srid,1,f); \
			f->write<ubyte>(mod->flags); \
		}

#define ModelFaceGenFlagsGetSaveSize(mod) \
		if (mod->flags) \
		{ \
			size += ComputeSubrecordSize(1); \
		}

//script data
struct VariableInfo
{
	ulong idx;
	double data;
	ubyte type;
	ulong unk14;
};

struct ScriptRef
{
	ulong type;
	ulong item;
};

struct ScriptInfo
{
	ulong unk;
	ulong refCount;
	ulong compiledSize;
	ulong variableCount;
	ushort type;
	ushort flags;
};

class Script
{
public:
	ScriptInfo info;
	ulong compiledScriptSize;
	byte *compiledScript;
	ulong scriptTextSize;
	char *scriptText;
	SimpleDynVecClass<VariableInfo> variables;
	SimpleDynVecClass<char *> variableNames;
	SimpleDynVecClass<ScriptRef> references;
	Script() : compiledScriptSize(0), compiledScript(0), scriptTextSize(0), scriptText(0)
	{
	}
	virtual ~Script()
	{
		if (compiledScript)
		{
			delete[] compiledScript;
		}
		if (scriptText)
		{
			delete[] scriptText;
		}
		for (int i = 0;i < variables.Count();i++)
		{
			delete[] variableNames[i];
		}
	}
	Script & Script::operator = (const Script & that)
	{
		info = that.info;
		if (that.compiledScript)
		{
			compiledScript = new byte[info.compiledSize];
			memcpy(compiledScript,that.compiledScript,info.compiledSize);
		}
		scriptTextSize = that.scriptTextSize;
		if (that.scriptText)
		{
			scriptText = newstr(that.scriptText);
		}
		variables = that.variables;
		variableNames = that.variableNames;
		references = that.references;
		return *this;
	}
};

#define ScriptLoad(scr) \
			case 'SCHR': \
				scr->info = f->read<ScriptInfo>(); \
				readSize += sizeof(ScriptInfo); \
				break; \
			case 'SCDA': \
				scr->compiledScriptSize = h.size; \
				scr->compiledScript = f->readarray<byte>(h.size); \
				readSize += h.size; \
				break; \
			case 'SCTX': \
				scr->scriptTextSize = h.size; \
				scr->scriptText = f->readarray<char>(h.size); \
				readSize += h.size; \
				break; \
			case 'SLSD': \
				scr->variables.Add(f->read<VariableInfo>()); \
				readSize += sizeof(VariableInfo); \
				break; \
			case 'SCVR': \
				scr->variableNames.Add(f->readzstring(h.size)); \
				readSize += h.size; \
				break; \
			case 'SCRV': \
			case 'SCRO': \
				{ \
					ScriptRef r; \
					r.type = h.type; \
					r.item = f->read<ulong>(); \
					scr->references.Add(r); \
					readSize += 4; \
				} \
				break;
#define ScriptSave(scr,form) \
		form->WriteSubrecord('SCHR',sizeof(ScriptInfo),f); \
		f->write<ScriptInfo>(scr->info); \
		if (scr->compiledScriptSize) \
		{ \
				form->WriteSubrecord('SCDA',scr->compiledScriptSize,f); \
				f->writearray<byte>(scr->compiledScriptSize,scr->compiledScript); \
		} \
		if (scr->scriptText) \
		{ \
			form->WriteSubrecord('SCTX',scr->scriptTextSize,f); \
			f->writearray<char>(scr->scriptTextSize,scr->scriptText); \
		} \
		for (int varcount = 0;varcount < scr->variables.Count();varcount++) \
		{ \
			form->WriteSubrecord('SLSD',sizeof(VariableInfo),f); \
			f->write<VariableInfo>(scr->variables[varcount]); \
			form->WriteZStringSubrecord('SCVR',scr->variableNames[varcount],f); \
		} \
		for (int refcount = 0;refcount < scr->references.Count();refcount++) \
		{ \
			form->WriteSubrecord(scr->references[refcount].type,4,f); \
			f->write<ulong>(scr->references[refcount].item); \
		}
#define ScriptGetSaveSize(scr,form) \
		size += form->ComputeSubrecordSize(sizeof(ScriptInfo)); \
		if (scr->compiledScriptSize) \
		{ \
			size += form->ComputeSubrecordSize(scr->compiledScriptSize); \
		} \
		if (scr->scriptText) \
		{ \
			size += form->ComputeSubrecordSize(scr->scriptTextSize); \
		} \
		for (int varcount = 0;varcount < scr->variables.Count();varcount++) \
		{ \
			size += form->ComputeSubrecordSize(sizeof(VariableInfo)); \
			size += form->ZStringSubrecordSize(scr->variableNames[varcount]); \
		} \
		for (int refcount = 0;refcount < scr->references.Count();refcount++) \
		{ \
			size += form->ComputeSubrecordSize(4); \
		}

class Scriptable
{
public:
	formid script;
	Scriptable() : script(0)
	{
	}
};

#define ScriptableLoad() \
			case 'SCRI': \
				script = f->read<formid>(); \
				readSize += 4; \
				break;
#define ScriptableSave() \
		if (script) \
		{ \
			WriteSubrecord('SCRI',4,f); \
			f->write<formid>(script); \
		}
#define ScriptableGetSaveSize() \
		if (script) \
		{ \
			size += ComputeSubrecordSize(4); \
		}

//destructible data
struct DestructibleObjectHeader
{
	long health;
	ubyte count;
	ubyte flags;
};
struct DestructibleObjectStageData
{
	ubyte healthPercentage;
	ubyte index;
	ubyte stage;
	ubyte flags;
	long selfDamagePerSecond;
	formid explosion;
	formid debris;
	long debrisCount;
};
class DestructibleObjectStage : public ModelTextureSwap
{
public:
	DestructibleObjectStageData data;
	bool stageEndMarker;
	DestructibleObjectStage() : stageEndMarker(false)
	{
	}
};
class DestructibleObject
{
public:
	bool hasDestructibleObjectData;
	DestructibleObjectHeader destructibleHeader;
	int currentStage;
	DestructibleObjectStage *stages;
	DestructibleObject() : stages(0), currentStage(-1), hasDestructibleObjectData(false)
	{
	}
	virtual ~DestructibleObject()
	{
		if (stages)
		{
			delete[] stages;
		}
	}
	DestructibleObject & operator = (const DestructibleObject & that)
	{
		hasDestructibleObjectData = that.hasDestructibleObjectData;
		destructibleHeader = that.destructibleHeader;
		currentStage = that.currentStage;
		stages = new DestructibleObjectStage[destructibleHeader.count];
		memcpy(stages,that.stages,destructibleHeader.count * sizeof(DestructibleObjectStage));
		return *this;
	}
};

#define DestructibleObjectLoad() \
			case 'DEST': \
				hasDestructibleObjectData = true; \
				destructibleHeader = f->read<DestructibleObjectHeader>(); \
				stages = new DestructibleObjectStage[destructibleHeader.count]; \
				readSize += sizeof(DestructibleObjectHeader); \
				break; \
			case 'DSTD': \
				currentStage++; \
				stages[currentStage].data = f->read<DestructibleObjectStageData>(); \
				readSize += sizeof(DestructibleObjectStageData); \
				break; \
			ModelTextureSwapBRLoad((&stages[currentStage]),'DMDL','DMDB','DMDT','DMDS'); \
			case 'DSTF': \
				stages[currentStage].stageEndMarker = true; \
				break;
#define DestructibleObjectSave() \
		if (hasDestructibleObjectData) \
		{ \
			WriteSubrecord('DEST',sizeof(DestructibleObjectHeader),f); \
			f->write<DestructibleObjectHeader>(destructibleHeader); \
			for (int count = 0;count < currentStage + 1;count++) \
			{ \
				WriteSubrecord('DSTD',sizeof(DestructibleObjectStageData),f); \
				f->write<DestructibleObjectStageData>(stages[count].data); \
				ModelTextureSwapBRSave((&stages[count]),'DMDL','DMDB','DMDT','DMDS'); \
				if (stages[count].stageEndMarker) \
				{ \
					WriteSubrecord('DSTF',0,f); \
				} \
			} \
		}
#define DestructibleObjectGetSaveSize() \
		if (hasDestructibleObjectData) \
		{ \
			size += ComputeSubrecordSize(sizeof(DestructibleObjectHeader)); \
			for (int count = 0;count < currentStage + 1;count++) \
			{ \
				size += ComputeSubrecordSize(sizeof(DestructibleObjectStageData)); \
				ModelTextureSwapBRGetSaveSize((&stages[count])); \
				if (stages[count].stageEndMarker) \
				{ \
					size += ComputeSubrecordSize(0); \
				} \
			} \
		}

//enchantable data
class Enchantable
{
public:
	formid enchantment;
	ushort enchantmentPoints;
	bool hasEnchantmentPoints;
	Enchantable() : enchantment(0), hasEnchantmentPoints(false)
	{
	}
};

#define EnchantableLoad() \
			case 'EITM': \
				enchantment = f->read<formid>(); \
				readSize += 4; \
				break; \
			case 'EAMT': \
				enchantmentPoints = f->read<ushort>(); \
				hasEnchantmentPoints = true; \
				readSize += 2; \
				break;
#define EnchantableSave() \
		if (enchantment) \
		{ \
			WriteSubrecord('EITM',4,f); \
			f->write<formid>(enchantment); \
		} \
		if (hasEnchantmentPoints) \
		{ \
			WriteSubrecord('EAMT',2,f); \
			f->write<ushort>(enchantmentPoints); \
		}
#define EnchantableGetSaveSize() \
		if (enchantment) \
		{ \
			size += ComputeSubrecordSize(4); \
		} \
		if (hasEnchantmentPoints) \
		{ \
			size += ComputeSubrecordSize(2); \
		}

//biped model data
struct BipedData
{
	ulong bipedFlags;
	ushort generalFlags;
};

class BipedModel
{
public:
	BipedData bipedData;
	ModelTextureSwap maleBipedData;
	ModelFaceGenFlags maleBipedFlags;
	ModelTextureSwap maleWorldData;
	Texture maleInventoryIcon;
	MessageTexture maleMessageIcon;
	ModelTextureSwap femaleBipedData;
	ModelFaceGenFlags femaleBipedFlags;
	ModelTextureSwap femaleWorldData;
	Texture femaleInventoryIcon;
	MessageTexture femaleMessageIcon;
	char *ragdollConstraint;
	BipedModel() : ragdollConstraint(0)
	{
	}
	virtual ~BipedModel()
	{
		if (ragdollConstraint)
		{
			delete[] ragdollConstraint;
		}
	}
};

#define BipedModelLoad() \
			case 'BMDT': \
				bipedData = f->read<BipedData>(); \
				readSize += sizeof(BipedData); \
				break; \
			ModelTextureSwapBRLoad((&maleBipedData),'MODL','MODB','MODT','MODS'); \
			ModelFaceGenFlagsLoad((&maleBipedFlags),'MODD'); \
			ModelTextureSwapBRLoad((&maleWorldData),'MOD2','MO2B','MO2T','MO2S'); \
			TextureLoad((&maleInventoryIcon),'ICON'); \
			MessageTextureLoad((&maleMessageIcon),'MICO'); \
			ModelTextureSwapBRLoad((&femaleBipedData),'MOD3','MO3B','MO3T','MO3S'); \
			ModelFaceGenFlagsLoad((&femaleBipedFlags),'MOSD'); \
			ModelTextureSwapBRLoad((&femaleWorldData),'MOD4','MO4B','MO4T','MO4S'); \
			TextureLoad((&femaleInventoryIcon),'ICO2'); \
			MessageTextureLoad((&femaleMessageIcon),'MIC2'); \
			case 'BMCT': \
				ragdollConstraint = f->readzstring(h.size); \
				readSize += h.size; \
				break;
#define BipedModelSave() \
			WriteSubrecord('BMDT',sizeof(BipedData),f); \
			f->write<BipedData>(bipedData); \
			ModelTextureSwapBRSave((&maleBipedData),'MODL','MODB','MODT','MODS'); \
			ModelFaceGenFlagsSave((&maleBipedFlags),'MODD'); \
			ModelTextureSwapBRSave((&maleWorldData),'MOD2','MO2B','MO2T','MO2S'); \
			TextureSave((&maleInventoryIcon),'ICON'); \
			MessageTextureSave((&maleMessageIcon),'MICO'); \
			ModelTextureSwapBRSave((&femaleBipedData),'MOD3','MO3B','MO3T','MO3S'); \
			ModelFaceGenFlagsSave((&femaleBipedFlags),'MOSD'); \
			ModelTextureSwapBRSave((&femaleWorldData),'MOD4','MO4B','MO4T','MO4S'); \
			TextureSave((&femaleInventoryIcon),'ICO2'); \
			MessageTextureSave((&femaleMessageIcon),'MIC2'); \
			WriteZStringSubrecord('BMCT',ragdollConstraint,f);

#define BipedModelGetSaveSize() \
			size += ComputeSubrecordSize(sizeof(BipedData)); \
			ModelTextureSwapBRGetSaveSize((&maleBipedData)); \
			ModelFaceGenFlagsGetSaveSize((&maleBipedFlags)); \
			ModelTextureSwapBRGetSaveSize((&maleWorldData)); \
			TextureGetSaveSize((&maleInventoryIcon)); \
			MessageTextureGetSaveSize((&maleMessageIcon)); \
			ModelTextureSwapBRGetSaveSize((&femaleBipedData)); \
			ModelFaceGenFlagsGetSaveSize((&femaleBipedFlags)); \
			ModelTextureSwapBRGetSaveSize((&femaleWorldData)); \
			TextureGetSaveSize((&femaleInventoryIcon)); \
			MessageTextureGetSaveSize((&femaleMessageIcon)); \
			size += ZStringSubrecordSize(ragdollConstraint);

//condition data
struct Condition
{
	ubyte type;
	float comparison;
	ushort function;
	ulong firstParameter;
	ulong secondParameter;
	ulong runOn;
	formid reference;
};

struct ConditionOld
{
	ubyte type;
	float comparison;
	ushort function;
	ulong firstParameter;
	ulong secondParameter;
	ulong runOn;
};

struct ConditionOld2
{
	ubyte type;
	float comparison;
	ushort function;
	ulong firstParameter;
	ulong secondParameter;
};

//repair item data
class RepairItem
{
public:
	formid repairItem;
	RepairItem() : repairItem(0)
	{
	}
};

#define RepairItemLoad() \
			case 'REPL': \
				repairItem = f->read<formid>(); \
				readSize += 4; \
				break;
#define RepairItemSave() \
		if (repairItem) \
		{ \
			WriteSubrecord('REPL',4,f); \
			f->write<formid>(repairItem); \
		}
#define RepairItemGetSaveSize() \
		if (repairItem) \
		{ \
			size += ComputeSubrecordSize(4); \
		}

//biped model list
class BipedModelList
{
public:
	formid bipedModelList;
	BipedModelList() : bipedModelList(0)
	{
	}
};

#define BipedModelListLoad() \
			case 'BIPL': \
				bipedModelList = f->read<formid>(); \
				readSize += 4; \
				break;
#define BipedModelListSave() \
		if (bipedModelList) \
		{ \
			WriteSubrecord('BIPL',4,f); \
			f->write<formid>(bipedModelList); \
		}
#define BipedModelListGetSaveSize() \
		if (bipedModelList) \
		{ \
			size += ComputeSubrecordSize(4); \
		}

//equip type data
class EquipType
{
public:
	long equipType;
	EquipType() : equipType(0)
	{
	}
};

#define EquipTypeLoad() \
			case 'ETYP': \
				equipType = f->read<long>(); \
				readSize += 4; \
				break;
#define EquipTypeSave() \
		WriteSubrecord('ETYP',4,f); \
		f->write<long>(equipType);
#define EquipTypeGetSaveSize() \
		size += ComputeSubrecordSize(4);

//pickup putdown sounds data
class PickupPutdownSounds
{
public:
	formid pickupSound;
	formid putdownSound;
	PickupPutdownSounds() : pickupSound(0), putdownSound(0)
	{
	}
};

#define PickupPutdownSoundsLoad() \
			case 'YNAM': \
				pickupSound = f->read<formid>(); \
				readSize += 4; \
				break; \
			case 'ZNAM': \
				putdownSound = f->read<formid>(); \
				readSize += 4; \
				break;
#define PickupPutdownSoundsSave() \
		if (pickupSound) \
		{ \
			WriteSubrecord('YNAM',4,f); \
			f->write<formid>(pickupSound); \
		} \
		if (putdownSound) \
		{ \
			WriteSubrecord('ZNAM',4,f); \
			f->write<formid>(putdownSound); \
		}
#define PickupPutdownSoundsGetSaveSize() \
		if (pickupSound) \
		{ \
			size += ComputeSubrecordSize(4); \
		} \
		if (putdownSound) \
		{ \
			size += ComputeSubrecordSize(4); \
		}

//container data
struct ContainerItem
{
	formid item;
	long count;
};

struct ContainerExtraData
{
	formid owner;
	formid global;
	float condition;
	ContainerExtraData() : owner(0), global(0), condition(1)
	{
	}
};

class Container
{
public:
	long currentItem;
	SimpleDynVecClass<ContainerItem> items;
	SimpleDynVecClass<ContainerExtraData> extraData;
	Container() : currentItem(-1)
	{
	}
};

#define ContainerLoad() \
			case 'CNTO': \
				currentItem++; \
				items.Add(f->read<ContainerItem>()); \
				readSize += sizeof(ContainerItem); \
				extraData.Add(ContainerExtraData()); \
				break; \
			case 'COED': \
				extraData[currentItem] = f->read<ContainerExtraData>(); \
				readSize += sizeof(ContainerExtraData); \
				break;
#define ContainerSave() \
		for (int itemCount = 0;itemCount < items.Count();itemCount++) \
		{ \
			WriteSubrecord('CNTO',sizeof(ContainerItem),f); \
			f->write<ContainerItem>(items[itemCount]); \
			if (extraData[itemCount].owner != 0 || extraData[itemCount].condition != 1.0f) \
			{ \
				WriteSubrecord('COED',sizeof(ContainerExtraData),f); \
				f->write<ContainerExtraData>(extraData[itemCount]); \
			} \
		}
#define ContainerGetSaveSize() \
		for (int itemCount = 0;itemCount < items.Count();itemCount++) \
		{ \
			size += ComputeSubrecordSize(sizeof(ContainerItem)); \
			if (extraData[itemCount].owner != 0 || extraData[itemCount].condition != 1.0f) \
			{ \
				size += ComputeSubrecordSize(sizeof(ContainerExtraData)); \
			} \
		}

//spell list data
class SpellList
{
public:
	SimpleDynVecClass<formid> spells;
};

#define SpellListLoad() \
			case 'SPLO': \
				spells.Add(f->read<formid>()); \
				readSize += 4; \
				break;
#define SpellListSave() \
		for (int spellCount = 0;spellCount < spells.Count();spellCount++) \
		{ \
			WriteSubrecord('SPLO',4,f); \
			f->write<formid>(spells[spellCount]); \
		}
#define SpellListGetSaveSize() \
		for (int spellCount = 0;spellCount < spells.Count();spellCount++) \
		{ \
			size += ComputeSubrecordSize(4); \
		}

//ammo data
class Ammo
{
public:
	formid ammo;
	Ammo() : ammo(0)
	{
	}
};

#define AmmoLoad() \
			case 'NAM0': \
				ammo = f->read<formid>(); \
				readSize += 4; \
				break;
#define AmmoSave() \
		if (ammo) \
		{ \
			WriteSubrecord('NAM0',4,f); \
			f->write<formid>(ammo); \
		}
#define AmmoGetSaveSize() \
		if (ammo) \
		{ \
			size += ComputeSubrecordSize(4); \
		}

//model list data
class ModelList
{
public:
	ubyte *modelList;
	ulong modelSize;
	ubyte *textureHashList;
	ulong textureHashSize;
	ModelList() : modelList(0), textureHashList(0), modelSize(0), textureHashSize(0)
	{
	}
	virtual ~ModelList()
	{
		if (modelList)
		{
			delete[] modelList;
		}
		if (textureHashList)
		{
			delete[] textureHashList;
		}
	}
};

#define ModelListLoad() \
			case 'NIFZ': \
				modelSize = h.size; \
				modelList = f->readarray<ubyte>(modelSize); \
				readSize += h.size; \
				break; \
			case 'NIFT': \
				textureHashSize = h.size; \
				textureHashList = f->readarray<ubyte>(textureHashSize); \
				readSize += h.size; \
				break;
#define ModelListSave() \
		if (modelList) \
		{ \
			WriteSubrecord('NIFZ',modelSize,f); \
			f->writearray<ubyte>(modelSize,modelList); \
		} \
		if (textureHashList) \
		{ \
			WriteSubrecord('NIFT',textureHashSize,f); \
			f->writearray<ubyte>(textureHashSize,textureHashList); \
		}
#define ModelListGetSaveSize() \
		if (modelList) \
		{ \
			size += ComputeSubrecordSize(modelSize); \
		} \
		if (textureHashList) \
		{ \
			size += ComputeSubrecordSize(textureHashSize); \
		}

//leveled list data
struct LeveledListEntry
{
	short level;
	formid item;
	short count;
};

class LeveledList
{
public:
	ubyte chanceNone;
	ubyte flags;
	formid global;
	int currentItem;
	SimpleDynVecClass<LeveledListEntry> listItems;
	SimpleDynVecClass<ContainerExtraData> extraData;
	SimpleDynVecClass<bool> extraDataPresent;
	LeveledList() : global(0), currentItem(-1)
	{
	}
};

#define LeveledListLoad() \
			case 'LVLD': \
				chanceNone = f->read<ubyte>(); \
				readSize += 1; \
				break; \
			case 'LVLF': \
				flags = f->read<ubyte>(); \
				readSize += 1; \
				break; \
			case 'LVLG': \
				global = f->read<formid>(); \
				readSize += 4; \
				break; \
			case 'LVLO': \
				currentItem++; \
				listItems.Add(f->read<LeveledListEntry>()); \
				extraData.Add(ContainerExtraData()); \
				extraDataPresent.Add(false); \
				readSize += sizeof(LeveledListEntry); \
				break; \
			case 'COED': \
				extraData[currentItem] = f->read<ContainerExtraData>(); \
				extraDataPresent[currentItem] = true; \
				readSize += sizeof(ContainerExtraData); \
				break;
#define LeveledListSave() \
		WriteSubrecord('LVLD',1,f); \
		f->write<ubyte>(chanceNone); \
		WriteSubrecord('LVLF',1,f); \
		f->write<ubyte>(flags); \
		if (global) \
		{ \
			WriteSubrecord('LVLG',4,f); \
			f->write<formid>(global); \
		} \
		for (int i = 0;i < listItems.Count();i++) \
		{ \
			WriteSubrecord('LVLO',sizeof(LeveledListEntry),f); \
			f->write<LeveledListEntry>(listItems[i]); \
			if (extraDataPresent[i]) \
			{ \
				WriteSubrecord('COED',sizeof(ContainerExtraData),f); \
				f->write<ContainerExtraData>(extraData[i]); \
			} \
		}
#define LeveledListGetSaveSize()\
		size += ComputeSubrecordSize(1); \
		size += ComputeSubrecordSize(1); \
		if (global) \
		{ \
			size += ComputeSubrecordSize(4); \
		} \
		for (int i = 0;i < listItems.Count();i++) \
		{ \
			size += ComputeSubrecordSize(sizeof(LeveledListEntry)); \
			if (extraDataPresent[i]) \
			{ \
				size += ComputeSubrecordSize(sizeof(ContainerExtraData)); \
			} \
		}

//idle collection data
class IdleCollection
{
public:
	ubyte idleAnimationFlags;
	ulong idleAnimationCount;
	float idleTimerSetting;
	int idleCount;
	formid *idleAnimations;
	bool largeIdleCount;
	ulong idlb;
	bool hasidlb;
	IdleCollection() : idleAnimations(0), idleAnimationCount(0), largeIdleCount(false), hasidlb(false), idleCount(0)
	{
	}
	virtual ~IdleCollection()
	{
		if (idleAnimations)
		{
			delete[] idleAnimations;
		}
	}
};

#define IdleCollectionLoad() \
			case 'IDLF': \
				idleAnimationFlags = f->read<ubyte>(); \
				readSize += 1; \
				break; \
			case 'IDLC': \
				if (h.size == 4) \
				{ \
					largeIdleCount = true; \
					idleAnimationCount = f->read<ulong>(); \
					readSize += 4; \
				} \
				else \
				{ \
					idleAnimationCount = f->read<ubyte>(); \
					readSize += 1; \
				} \
				break; \
			case 'IDLT': \
				idleTimerSetting = f->read<float>(); \
				readSize += 4; \
				break; \
			case 'IDLA': \
				idleCount = h.size / 4; \
				idleAnimations = f->readarray<formid>(idleCount); \
				readSize += h.size; \
				break; \
			case 'IDLB': \
				hasidlb = true; \
				idlb = f->read<ulong>(); \
				readSize += 4; \
				break;
#define IdleCollectionSave() \
		if (idleCount) \
		{ \
			WriteSubrecord('IDLF',1,f); \
			f->write<ubyte>(idleAnimationFlags); \
			if (largeIdleCount) \
			{ \
				WriteSubrecord('IDLC',4,f); \
				f->write<ulong>(idleAnimationCount); \
			} \
			else \
			{ \
				WriteSubrecord('IDLC',1,f); \
				f->write<ubyte>((ubyte)idleAnimationCount); \
			} \
			WriteSubrecord('IDLT',4,f); \
			f->write<float>(idleTimerSetting); \
			WriteSubrecord('IDLA',4 * idleCount,f); \
			f->writearray<formid>(idleCount,idleAnimations); \
			if (hasidlb) \
			{ \
				WriteSubrecord('IDLB',4,f); \
				f->write<ulong>(idlb); \
			} \
		}
#define IdleCollectionGetSaveSize() \
		if (idleCount) \
		{ \
			size += ComputeSubrecordSize(1); \
			if (largeIdleCount) \
			{ \
				size += ComputeSubrecordSize(4); \
			} \
			else \
			{ \
				size += ComputeSubrecordSize(1); \
			} \
			size += ComputeSubrecordSize(4); \
			size += ComputeSubrecordSize(4 * idleCount); \
			if (hasidlb) \
			{ \
				size += ComputeSubrecordSize(4); \
			} \
		}

//image space modifiable data
class ImageSpaceModifiable
{
public:
	formid imageSpace;
	ImageSpaceModifiable() : imageSpace(0)
	{
	}
};

#define ImageSpaceModifiableLoad() \
			case 'MNAM': \
				imageSpace = f->read<formid>(); \
				readSize += 4; \
				break;
#define ImageSpaceModifiableSave() \
		if (imageSpace) \
		{ \
			WriteSubrecord('MNAM',4,f); \
			f->write<formid>(imageSpace); \
		}
#define ImageSpaceModifiableGetSaveSize() \
		if (imageSpace) \
		{ \
			size += ComputeSubrecordSize(4); \
		}

//cell impact data
struct ImpactSwap
{
	ulong materialType;
	formid oldImpact;
	formid newImpact;
};
