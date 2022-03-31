#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

typedef enum {
    false,
    true
} bool;

/**
 * Termine le processus en cas de succès
 */
void end();

/**
 * Termine le processus en cas d'erreur
 */
void die();

#endif /* _SYSTEM_H */
