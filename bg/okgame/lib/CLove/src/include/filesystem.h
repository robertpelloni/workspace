/*
#   clove
#
#   Copyright (C) 2016-2021 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include <stdbool.h>

#define USE_PHYSFS 1

#ifdef USE_PHYSFS
#include "../3rdparty/physfs/physfs.h"
#endif

#include "../3rdparty/SDL2/include/SDL.h"

enum FileType {
	FileType_REGULAR,
	FileType_DIRECTORY,
	FileType_SYMLIN,
	FileType_OTHER
};

struct FileInfo {
	int64_t size;
	int64_t modtime;
	int64_t accesstime;
	int64_t createtime;
	enum FileType type;
};

void filesystem_init(char* argv0, bool stats);
void filesystem_free(void);

const char* filesystem_getOS(void);
const char* filesystem_getSaveDirectory(const char* company, const char* projName);
int filesystem_read(char const* filename, char** output);
int filesystem_write(const char* name, const char* data);
int filesystem_append(const char* name, const char* data);
bool filesystem_exists(const char* name);
bool filesystem_getInfo(const char* path, struct FileInfo *info);
bool filesystem_equals(const char* a,const char* b,int l);
bool filesystem_contain(const char* a, const char* b);
bool filesystem_remove(const char* name);
bool filesystem_rename(const char *old_name, const char *new_name);
bool filesystem_state(const char* file, int mode);
bool filesystem_isSymLink(const char* dir);
bool filesystem_isDir(const char* dir);
bool filesystem_mkDir(const char* path);
const char* filesystem_getCurrentDirectory(void);
char** filesystem_enumerate(const char* path);
const char* filesystem_getUsrDir(void);
bool filesystem_setIdentity(const char* path);

bool filesystem_mount(const char* path, const char* mountPoint, int appendToPath);
bool filesystem_unmount(const char* path);

void filesystem_setSource(const char* source);
const char* filesystem_getSource(void);
