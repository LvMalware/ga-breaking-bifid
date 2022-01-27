/*
 * Copyright (C) 2022 Lucas V. Araujo <lucas.vieira.ar@disroot.org>
 *
 * This program is a free software. You can use, redistribute and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3, or any later version.
 */

#ifndef _CROMOSSOME_H
#define _CROMOSSOME_H

/*
 * Uncomment the line below to use bigram frequency as cromossome fitness;
 * It is slower, but may give better results than single letters;
 */

#define BIGRAM_FREQUENCY_AS_FITNESS

#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* frequency of english letters */
static const double frequences[] = {
        /* a */ 0.0651738, /* b */ 0.0124248, /* c */ 0.0217339, /* d */ 0.0349835,
        /* e */ 0.1041442, /* f */ 0.0197881, /* g */ 0.0158610, /* h */ 0.0492888,
        /* i */ 0.0558094, /* j */ 0.0009033, /* k */ 0.0050529, /* l */ 0.0331490,
        /* m */ 0.0202124, /* n */ 0.0564513, /* o */ 0.0596302, /* p */ 0.0137645,
        /* q */ 0.0008606, /* r */ 0.0497563, /* s */ 0.0515760, /* t */ 0.0729357,
        /* u */ 0.0225134, /* v */ 0.0082903, /* w */ 0.0171272, /* x */ 0.0013692,
        /* y */ 0.0145984, /* z */ 0.0007836 
};

typedef struct bg
{
    char *b;
    double f;
} bg;

/* frequency of english bigrams */
static const bg bigrams[] = {
    { "TH", 3.56 }, { "HE", 3.07 }, { "IN", 2.43 }, { "ER", 2.05 },
    { "AN", 1.99 }, { "RE", 1.85 }, { "ON", 1.76 }, { "AT", 1.49 },
    { "EN", 1.45 }, { "ND", 1.35 }, { "TI", 1.34 }, { "ES", 1.34 },
    { "OR", 1.28 }, { "TE", 1.20 }, { "OF", 1.17 }, { "ED", 1.17 },
    { "IS", 1.13 }, { "IT", 1.12 }, { "AL", 1.09 }, { "AR", 1.07 },
    { "ST", 1.05 }, { "TO", 1.04 }, { "NT", 1.04 }, { "NG", 0.95 },
    { "SE", 0.93 }, { "HA", 0.93 }, { "AS", 0.87 }, { "OU", 0.87 },
    { "IO", 0.83 }, { "LE", 0.83 }, { "VE", 0.83 }, { "CO", 0.79 },
    { "ME", 0.79 }, { "DE", 0.76 }, { "HI", 0.76 }, { "RI", 0.73 },
    { "RO", 0.73 }, { "IC", 0.70 }, { "NE", 0.69 }, { "EA", 0.69 },
    { "RA", 0.69 }, { "CE", 0.65 }, { "LI", 0.62 }, { "CH", 0.60 },
    { "LL", 0.58 }, { "BE", 0.58 }, { "MA", 0.57 }, { "SI", 0.55 },
    { "OM", 0.55 }, { "UR", 0.54 }
};

typedef struct cromossome
{
    char key[26];
    size_t key_len;
    double fitness;
} cromossome;


double cromossome_fitness (cromossome * const, char * (*decrypt)(char * const key));
cromossome *cromossome_crossover (cromossome * const, cromossome * const);
cromossome *new_cromossome (const size_t, char * const);
void mutate_cromossome (cromossome * const);
void del_cromossome (cromossome *);

#endif /* cromossome.h */
