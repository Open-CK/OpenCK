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
struct RecipeData
{
	long skill;
	ulong level;
	formid category;
	formid subCategory;
};
struct RecipeItem
{
	formid item;
	ulong quantity;
};
class RecipeForm : public Form, public FullName
{
protected:
	SimpleDynVecClass<Condition> conditions;
	RecipeData data;
	SimpleDynVecClass<RecipeItem> ingredients;
	SimpleDynVecClass<RecipeItem> outputs;
public:
	RecipeForm(FormHeader h,ModFile *f) : Form(h,f)
	{
	}
protected:
	virtual void Load(FileRead *f)
	{
		int currentIngredient = -1;
		int currentOutput = -1;
		bool ing = false;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			FullNameLoad();
			case 'CTDA':
				conditions.Add(f->read<Condition>());
				readSize += sizeof(Condition);
				break;
			case 'DATA':
				data = f->read<RecipeData>();
				readSize += sizeof(RecipeData);
				break;
			case 'RCIL':
				currentIngredient++;
				ing = true;
				ingredients.Add(RecipeItem());
				ingredients[currentIngredient].item = f->read<formid>();
				readSize += 4;
				break;
			case 'RCOD':
				currentOutput++;
				ing = false;
				outputs.Add(RecipeItem());
				outputs[currentOutput].item = f->read<formid>();
				readSize += 4;
				break;
			case 'RCQY':
				if (ing)
				{
					ingredients[currentIngredient].quantity = f->read<ulong>();
				}
				else
				{
					outputs[currentOutput].quantity = f->read<ulong>();
				}
				readSize += 4;
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
		FullNameSave();
		for (int i = 0;i < conditions.Count();i++)
		{
			WriteSubrecord('CTDA',sizeof(Condition),f);
			f->write<Condition>(conditions[i]);
		}
		WriteSubrecord('DATA',sizeof(RecipeData),f);
		f->write<RecipeData>(data);
		for (int i = 0;i < ingredients.Count();i++)
		{
			WriteSubrecord('RCIL',4,f);
			f->write<formid>(ingredients[i].item);
			WriteSubrecord('RCQY',4,f);
			f->write<ulong>(ingredients[i].quantity);
		}
		for (int i = 0;i < outputs.Count();i++)
		{
			WriteSubrecord('RCOD',4,f);
			f->write<formid>(outputs[i].item);
			WriteSubrecord('RCQY',4,f);
			f->write<ulong>(outputs[i].quantity);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		FullNameGetSaveSize();
		for (int i = 0;i < conditions.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(Condition));
		}
		size += ComputeSubrecordSize(sizeof(RecipeData));
		for (int i = 0;i < ingredients.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < outputs.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
