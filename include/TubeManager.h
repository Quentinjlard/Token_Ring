#ifndef __TUBEMANAGER_H
#define __TUBEMANAGER_H

#include "system.h"
#include <fcntl.h>

typedef int stream_t;

/**
 * 
 */
typedef struct {
    stream_t read, write;
    pid_t proc;
} TubeManager;

/**
 * 
 */
void createTubeManager(TubeManager *tm, stream_t **ts, const int tc, const int id);

/**
 * 
 */
stream_t** tubes(const int tc);

/**
 * 
 */
void closeTubes(stream_t **ts, const int tc, TubeManager *tm);

/**
 * 
 */
void freeTubes(stream_t **ts, const int tc);

#endif /* __TUBEMANAGER_H */
