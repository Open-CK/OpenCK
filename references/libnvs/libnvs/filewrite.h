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
class FileWrite
{
private:
	FILE *f;
	ubyte *buffer;
public:
	FileWrite(const char *name) : buffer(0)
	{
		f = fopen(name,"wb");
	}
	~FileWrite()
	{
		if (f)
		{
			fclose(f);
		}
	}
	void SetCompressed(ubyte *buf)
	{
		if (!buffer)
		{
			buffer = buf;
		}
	}
	void ClearCompressed()
	{
		buffer = 0;
	}
	template<typename T> inline void write(T data)
	{
		if (buffer)
		{
			memcpy(buffer,&data,sizeof(T));
			buffer += sizeof(T);
		}
		else
		{
			fwrite(&data,sizeof(T),1,f);
		}
	}
	template<typename T> inline void writearray(int count,T *data)
	{
		if (count)
		{
			if (buffer)
			{
				memcpy(buffer,data,sizeof(T) * count);
				buffer += (sizeof(T) * count);
			}
			else
			{
				fwrite(data,sizeof(T),count,f);
			}
		}
	}
	void writebstring(char *string)
	{
		byte count = (byte)strlen(string);
		write<byte>(count);
		if (buffer)
		{
			memcpy(buffer,string,count);
			buffer += count;
		}
		else
		{
			fwrite(string,1,count,f);
		}
	}
	void writelstring(char *string)
	{
		ulong count = (ulong)strlen(string);
		write<ulong>(count);
		if (buffer)
		{
			memcpy(buffer,string,count);
			buffer += count;
		}
		else
		{
			fwrite(string,1,count,f);
		}
	}
	void writebzstring(char *string)
	{
		byte count = (byte)strlen(string);
		write<byte>(count+1);
		if (buffer)
		{
			memcpy(buffer,string,count+1);
			buffer += (count + 1);
		}
		else
		{
			fwrite(string,1,count+1,f);
		}
	}
	void writestring(int count,char *string)
	{
		if (buffer)
		{
			memcpy(buffer,string,count);
			buffer += count;
		}
		else
		{
			fwrite(string,1,count,f);
		}
	}
	void writezstring(int count,char *string)
	{
		if (buffer)
		{
			memcpy(buffer,string,count);
			buffer += count;
		}
		else
		{
			fwrite(string,1,count,f);
		}
	}
};
