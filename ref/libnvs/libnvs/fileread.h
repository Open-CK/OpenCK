/*	libnvs
	Copyright 2015 Jonathan Wilson

	This file is part of libnvs
	libnvs is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include <stdio.h>
#include <string.h>
#include "fodata.h"
class FileRead
{
private:
	long size;
	ubyte *buffer;
	ubyte *bufferptr;
	ubyte *compbuffer;
public:
	FileRead(const char *name)
	{
		FILE *f = fopen(name,"rb");
		fseek(f,0,SEEK_END);
		size = ftell(f);
		fseek(f,0,SEEK_SET);
		buffer = new ubyte[size];
		fread(buffer,size,1,f);
		bufferptr = buffer;
		fclose(f);
		compbuffer = 0;
	}
	void SetCompressed(ubyte *buf)
	{
		if (!compbuffer)
		{
			compbuffer = bufferptr;
			bufferptr = buf;
		}
	}
	void ClearCompressed()
	{
		if (compbuffer)
		{
			bufferptr = compbuffer;
			compbuffer = 0;
		}
	}
	~FileRead()
	{
		delete[] buffer;
	}
	void seek(long pos)
	{
		if (!compbuffer)
		{
			bufferptr = buffer + pos;
		}
	}
	void unread(int count)
	{
		bufferptr -= count;
	}
	bool eof()
	{
		if (!compbuffer)
		{
			return bufferptr >= buffer + size;
		}
		return false;
	}
	long pos()
	{
		if (!compbuffer)
		{
			return bufferptr - buffer;
		}
		return 0;
	}
	template<typename T> inline T read()
	{
		T value;
		memcpy(&value,bufferptr,sizeof(T));
		bufferptr += sizeof(T);
		return value;
	}
	template<typename T> inline T* readarray(int count)
	{
		if (count)
		{
			T *value = new T[count];
			memcpy(value,bufferptr,sizeof(T) * count);
			bufferptr += sizeof(T) * count;
			return value;
		}
		return 0;
	}
	template<typename T> inline void readarray(int count,void *value)
	{
		if (count)
		{
			memcpy(value,bufferptr,sizeof(T) * count);
			bufferptr += sizeof(T) * count;
		}
	}
	char *readbstring()
	{
		byte count = read<byte>();
		char *string = new char[count+1];
		memcpy(string,bufferptr,count);
		bufferptr += count;
		string[count] = 0;
		return string;
	}
	char *readlstring()
	{
		ulong count = read<ulong>();
		char *string = new char[count+1];
		memcpy(string,bufferptr,count);
		bufferptr += count;
		string[count] = 0;
		return string;
	}
	char *readbzstring()
	{
		byte count = read<byte>();
		char *string = new char[count];
		memcpy(string,bufferptr,count);
		bufferptr += count;
		return string;
	}
	char *readstring(int count)
	{
		char *string = new char[count+1];
		memcpy(string,bufferptr,count);
		bufferptr += count;
		string[count] = 0;
		return string;
	}
	char *readzstring(int count)
	{
		char *string = new char[count];
		memcpy(string,bufferptr,count);
		bufferptr += count;
		return string;
	}
};

