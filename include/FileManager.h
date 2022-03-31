#ifndef __FILEMANAGER_H
#define __FILEMANAGER_H

#include "system.h"
#include <fcntl.h>
#include <time.h>

typedef int file_t;

bool dirExist(const int id);

void createDir(const int id);

void editTime(const int id, const int move, const struct timespec *time);

#endif /* __FILEMANAGER_H */
