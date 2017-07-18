/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#include "modfile.h"
#include "typegroup.h"
int main(int argc,char *argv[])
{
	argc;
	ModFile *m  = new ModFile();
	m->Open(argv[1]);
	char path[260];
	strcpy(path,"out\\");
	strcat(path,argv[1]);
	m->Save(path);
	return 0;
}
