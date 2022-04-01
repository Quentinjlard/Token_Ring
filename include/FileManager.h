#ifndef __FILEMANAGER_H
#define __FILEMANAGER_H

#include "system.h"
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

typedef int file_t;

bool dirExist(const int id);

void createDir(const int id);

void editTime(const int id, const int move, const int cur_ms, const int old_ms);

#endif /* __FILEMANAGER_H */
