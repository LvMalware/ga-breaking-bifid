#ifndef _GA_H
#define _GA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cromossome.h"

#ifdef DEBUG_GA
#include <stdio.h>
#endif /* DEBUG_GA */

typedef struct ga
{
    char *alphabet;
    size_t pop_size;
    char * (*decrypt)(char * const key);
    cromossome **population;
} ga;

ga *new_ga (char * const, char * (*decrypt)(char * const key));
void init_population (ga * const, size_t, size_t);
void ga_evolve (ga * const, size_t, size_t, size_t, double, double);
void ga_clean (ga * const);

#endif /* ga.h */
