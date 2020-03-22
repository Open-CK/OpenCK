/***** BEGIN LICENSE BLOCK *****
BSD License
Copyright (c) 2005-2012, NIF File Format Library and Tools
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the NIF File Format Library and Tools project may not be
   used to endorse or promote products derived from this software
   without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***** END LICENCE BLOCK *****/


#include "FSManager.h"
#include "FSEngine.h"

#include <algorithm>
#include <iterator>


//! Global BSA file manager
static FSManager *theFSManager = nullptr;

FSManager* FSManager::get() {
	if (!theFSManager)
		theFSManager = new FSManager();
	return theFSManager;
}

bool FSManager::exists() {
	return theFSManager != nullptr;
}

void FSManager::del() {
	if (theFSManager) {
		delete theFSManager;
		theFSManager = nullptr;
	}
}

std::list<FSArchiveFile*> FSManager::archiveList() {
	std::list<FSArchiveFile*> archives;

	std::transform(get()->archives.begin(), get()->archives.end(), std::back_inserter(archives),
		[](std::map<std::string, FSArchiveHandler*>::value_type& val){ return val.second->getArchive(); });

	return archives;
}

void FSManager::addArchives(const std::vector<std::string>& archiveList) {
	for (auto &archive : archiveList) {
		if (FSArchiveHandler *a = FSArchiveHandler::openArchive(archive))
			get()->archives[archive] = a;
	}
}

FSManager::FSManager() {
}

FSManager::~FSManager() {
	for (auto &it : archives)
		delete it.second;

	archives.clear();
}