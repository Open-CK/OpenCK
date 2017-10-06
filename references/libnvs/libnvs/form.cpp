/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#include "zlib.h"
#include "texturesetform.h"
#include "globalform.h"
#include "classform.h"
#include "factionform.h"
#include "soundform.h"
#include "acousticspaceform.h"
#include "magiceffectform.h"
#include "scriptform.h"
#include "landscapetextureform.h"
#include "enchantmentform.h"
#include "spellform.h"
#include "activatorform.h"
#include "talkingactivatorform.h"
#include "terminalform.h"
#include "armorform.h"
#include "containerform.h"
#include "doorform.h"
#include "lightform.h"
#include "miscform.h"
#include "staticform.h"
#include "staticcollectionform.h"
#include "moveablestaticform.h"
#include "furnitureform.h"
#include "cellform.h"
#include "refrform.h"
#include "messageform.h"
#include "gamesettingform.h"
#include "worldspaceform.h"
#include "navmeshinfomapform.h"
#include "navmeshform.h"
#include "landform.h"
#include "placeablewaterform.h"
#include "npcform.h"
#include "leveleditemform.h"
#include "formlistform.h"
#include "camerashotform.h"
#include "weaponform.h"
#include "creatureform.h"
#include "noteform.h"
#include "ammoform.h"
#include "bookform.h"
#include "alchemyform.h"
#include "dialogform.h"
#include "dialogresponseform.h"
#include "questform.h"
#include "packageform.h"
#include "raceform.h"
#include "waterform.h"
#include "actorvalueinfoform.h"
#include "headpartform.h"
#include "leveledactorform.h"
#include "idlemarkerform.h"
#include "projectileform.h"
#include "loadscreenform.h"
#include "perkform.h"
#include "voicetypeform.h"
#include "imagespacemodifierform.h"
#include "armoraddonform.h"
#include "ingredientitemform.h"
#include "regionform.h"
#include "bodypartdataform.h"
#include "debrisform.h"
#include "explosionform.h"
#include "idleform.h"
#include "hairform.h"
#include "animatedobjectform.h"
#include "camerapathform.h"
#include "weatherform.h"
#include "climateform.h"
#include "eyesform.h"
#include "grassform.h"
#include "treeform.h"
#include "effectshaderform.h"
#include "combatstyleform.h"
#include "encounterzoneform.h"
#include "imagespaceform.h"
#include "ragdollform.h"
#include "musictypeform.h"
#include "menuiconform.h"
#include "addonnodeform.h"
#include "impactdataform.h"
#include "impactdatasetform.h"
#include "lightingtemplateform.h"
#include "radiationstageform.h"
#include "defaultobjectmanagerform.h"
#include "reputationform.h"
#include "itemmodform.h"
#include "recipeform.h"
#include "recipecategoryform.h"
#include "challengeform.h"
#include "ammoeffectform.h"
#include "medialocationcontrollerform.h"
#include "mediasetform.h"
#include "caravancardform.h"
#include "casinochipform.h"
#include "casinoform.h"
#include "loadscreentypeform.h"
#include "caravanmoneyform.h"
#include "caravandeckform.h"
void Form::LoadCompressed(FileRead *f)
{
	ubyte *outbuf = 0;
	if (header.flags & 0x00040000)
	{
		ulong len = f->read<ulong>();
		uncompsize = len;
		ubyte *buffer = f->readarray<ubyte>(header.dataSize-4);
		outbuf = new ubyte[len];
		z_stream s;
		s.total_out = 0;
		s.zalloc = (alloc_func)0;
		s.zfree = (free_func)0;
		s.opaque = (voidpf)0;
		s.next_in = (Bytef*)buffer;
		s.avail_in = (uInt)(header.dataSize - 4);
		s.next_out = (Bytef*)outbuf;
		s.avail_out = (uInt)(len);
		inflateInit(&s);
		inflate(&s,0);
		inflateEnd(&s);
		if (header.id == 0x00150FC0)
		{
			FILE *fx = fopen("in.bin","wb");
			fwrite(buffer,header.dataSize - 4,1,fx);
			fclose(fx);
		}
		delete[] buffer;
		f->SetCompressed(outbuf);
	}
	if (uncompsize == 0)
	{
		deleted = true;
	}
	else
	{
		Load(f);
	}
	if (header.flags & 0x00040000)
	{
		f->ClearCompressed();
		delete[] outbuf;
	}
}
void Form::SaveCompressed(FileWrite *f)
{
	if (deleted)
	{
		f->write<FormHeader>(header);
		return;
	}
	int size = GetSaveSize();
	if (size == 0)
	{
		f->write<FormHeader>(header);
		return;
	}
	ubyte *outbuf = new ubyte[size];
	f->SetCompressed(outbuf);
	Save(f);
	f->ClearCompressed();
	if (header.flags & 0x00040000)
	{
		ubyte *compbuf = new ubyte[size * 2];
		z_stream s;
		s.total_out = 0;
		s.zalloc = (alloc_func)0;
		s.zfree = (free_func)0;
		s.opaque = (voidpf)0;
		s.next_in = (Bytef*)outbuf;
		s.avail_in = (uInt)(size);
		s.next_out = (Bytef*)compbuf;
		s.avail_out = (uInt)(size * 2);
		deflateInit(&s,-1);
		deflate(&s,4);
		deflateEnd(&s);
		header.dataSize = ((size * 2) - s.avail_out) + 4;
		f->write<FormHeader>(header);
		f->write<ulong>(size);
		f->writearray<ubyte>((size * 2) - s.avail_out,compbuf);
		if (header.id == 0x00150FC0)
		{
			FILE *fx = fopen("out.bin","wb");
			fwrite(compbuf,(size * 2) - s.avail_out,1,fx);
			fclose(fx);
		}
		delete[] compbuf;
	}
	else
	{
		f->write<FormHeader>(header);
		f->writearray<ubyte>(size,outbuf);
	}
	delete[] outbuf;
}
Form *CreateForm(FormHeader header,ModFile *f)
{
	switch(SwapBytes(header.type))
	{
	case 'SCPT':
		return new ScriptForm(header,f);
	case 'ARMO':
		return new ArmorForm(header,f);
	case 'WEAP':
		return new WeaponForm(header,f);
	case 'QUST':
		return new QuestForm(header,f);
	case 'MESG':
		return new MessageForm(header,f);
	case 'TXST':
		return new TextureSetForm(header,f);
	case 'STAT':
		return new StaticForm(header,f);
	case 'SPEL':
 		return new SpellForm(header,f);
	case 'MISC':
	case 'KEYM':
		return new MiscForm(header,f);
	case 'FACT':
		return new FactionForm(header,f);
	case 'SOUN':
		return new SoundForm(header,f);
	case 'MGEF':
		return new MagicEffectForm(header,f);
	case 'ENCH':
		return new EnchantmentForm(header,f);
	case 'PERK':
		return new PerkForm(header,f);
	case 'CREA':
		return new CreatureForm(header,f);
	case 'GLOB':
		return new GlobalForm(header,f);
	case 'CONT':
		return new ContainerForm(header,f);
	case 'NPC_':
		return new NPCForm(header,f);
	case 'LVLI':
	case 'LVSP':
		return new LeveledItemForm(header,f);
	case 'DIAL':
		return new DialogForm(header,f);
	case 'INFO':
		return new DialogResponseForm(header,f);
	case 'FLST':
		return new FormListForm(header,f);
	case 'REPU':
		return new ReputationForm(header,f);
	case 'CELL':
		return new CellForm(header,f);
	case 'REFR':
	case 'ACHR':
	case 'ACRE':
	case 'PMIS':
	case 'PGRE':
	case 'PBEA':
	case 'PFLA':
	case 'PCBE':
		return new RefrForm(header,f);
	case 'WRLD':
		return new WorldspaceForm(header,f);
	case 'ACTI':
		return new ActivatorForm(header,f);
	case 'NOTE':
		return new NoteForm(header,f);
	case 'TERM':
		return new TerminalForm(header,f);
	case 'BOOK':
		return new BookForm(header,f);
	case 'CLAS':
		return new ClassForm(header,f);
	case 'ASPC':
		return new AcousticSpaceForm(header,f);
	case 'TACT':
		return new TalkingActivatorForm(header,f);
	case 'GMST':
		return new GameSettingForm(header,f);
	case 'RACE':
		return new RaceForm(header,f);
	case 'LTEX':
		return new LandscapeTextureForm(header,f);
	case 'MICN':
		return new MenuIconForm(header,f);
	case 'HDPT':
		return new HeadPartForm(header,f);
	case 'DOOR':
		return new DoorForm(header,f);
	case 'LIGH':
		return new LightForm(header,f);
	case 'SCOL':
		return new StaticCollectionForm(header,f);
	case 'MSTT':
		return new MoveableStaticForm(header,f);
	case 'PWAT':
		return new PlaceableWaterForm(header,f);
	case 'FURN':
		return new FurnitureForm(header,f);
	case 'AMMO':
		return new AmmoForm(header,f);
	case 'LVLC':
	case 'LVLN':
		return new LeveledActorForm(header,f);
	case 'ALCH':
		return new AlchemyForm(header,f);
	case 'IDLM':
		return new IdleMarkerForm(header,f);
	case 'PROJ':
		return new ProjectileForm(header,f);
	case 'REGN':
		return new RegionForm(header,f);
	case 'NAVI':
		return new NavMeshInfoMapForm(header,f);
	case 'NAVM':
		return new NavMeshForm(header,f);
	case 'IDLE':
		return new IdleForm(header,f);
	case 'PACK':
		return new PackageForm(header,f);
	case 'CSTY':
		return new CombatStyleForm(header,f);
	case 'ANIO':
		return new AnimatedObjectForm(header,f);
	case 'WATR':
		return new WaterForm(header,f);
	case 'EFSH':
		return new EffectShaderForm(header,f);
	case 'EXPL':
		return new ExplosionForm(header,f);
	case 'DEBR':
		return new DebrisForm(header,f);
	case 'IMGS':
		return new ImageSpaceForm(header,f);
	case 'IMAD':
		return new ImageSpaceModifierForm(header,f);
	case 'BPTD':
		return new BodyPartDataForm(header,f);
	case 'ADDN':
		return new AddonNodeForm(header,f);
	case 'CAMS':
		return new CameraShotForm(header,f);
	case 'CPTH':
		return new CameraPathForm(header,f);
	case 'VTYP':
		return new VoiceTypeForm(header,f);
	case 'IPCT':
		return new ImpactDataForm(header,f);
	case 'IPDS':
		return new ImpactDataSetForm(header,f);
	case 'ARMA':
		return new ArmorAddonForm(header,f);
	case 'ECZN':
		return new EncounterZoneForm(header,f);
	case 'RGDL':
		return new RagdollForm(header,f);
	case 'MUSC':
		return new MusicTypeForm(header,f);
	case 'EYES':
		return new EyesForm(header,f);
	case 'LSCR':
		return new LoadScreenForm(header,f);
	case 'LAND':
		return new LandForm(header,f);
	case 'AVIF':
		return new ActorValueInfoForm(header,f);
	case 'INGR':
		return new IngredientItemForm(header,f);
	case 'HAIR':
		return new HairForm(header,f);
	case 'GRAS':
		return new GrassForm(header,f);
	case 'TREE':
		return new TreeForm(header,f);
	case 'LGTM':
		return new LightingTemplateForm(header,f);
	case 'RADS':
	case 'HUNG':
	case 'DEHY':
	case 'SLPD':
		return new RadiationStageForm(header,f);
	case 'DOBJ':
		return new DefaultObjectManagerForm(header,f);
	case 'CLMT':
		return new ClimateForm(header,f);
	case 'WTHR':
		return new WeatherForm(header,f);
	case 'IMOD':
		return new ItemModForm(header,f);
	case 'RCPE':
		return new RecipeForm(header,f);
	case 'RCCT':
		return new RecipeCategoryForm(header,f);
	case 'CHAL':
		return new ChallengeForm(header,f);
	case 'AMEF':
		return new AmmoEffectForm(header,f);
	case 'ALOC':
		return new MediaLocationControllerForm(header,f);
	case 'MSET':
		return new MediaSetForm(header,f);
	case 'CCRD':
		return new CaravanCardForm(header,f);
	case 'CHIP':
		return new CasinoChipForm(header,f);
	case 'CSNO':
		return new CasinoForm(header,f);
	case 'LSCT':
		return new LoadScreenTypeForm(header,f);
	case 'CMNY':
		return new CaravanMoneyForm(header,f);
	case 'CDCK':
		return new CaravanDeckForm(header,f);
	default:
		printf("Unknown form type found");
		__debugbreak();
		return 0;
	}
}
