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

// #define BIGRAM_FREQUENCY_AS_FITNESS

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
        /* y */ 0.0145984, /* z */ 0.0007836, /*   */ 0.1918182
};

typedef struct bg
{
    char *b;
    double f;
} bg;

/* frequency of english bigrams */
static const bg bigrams[] = {
    { "TH", 0.271 }, { "EN", 0.113 }, { "NG", 0.089 },
    { "HE", 0.233 }, { "AT", 0.112 }, { "AL", 0.088 },
    { "IN", 0.203 }, { "ED", 0.108 }, { "IT", 0.088 },
    { "ER", 0.178 }, { "ND", 0.107 }, { "AS", 0.087 },
    { "AN", 0.161 }, { "TO", 0.107 }, { "IS", 0.086 },
    { "RE", 0.141 }, { "OR", 0.106 }, { "HA", 0.083 },
    { "ES", 0.132 }, { "EA", 0.100 }, { "ET", 0.076 },
    { "ON", 0.132 }, { "TI", 0.099 }, { "SE", 0.073 },
    { "ST", 0.125 }, { "AR", 0.098 }, { "OU", 0.072 },
    { "NT", 0.117 }, { "TE", 0.098 }, { "OF", 0.071 }
};

typedef struct cromossome
{
    char *key;
    size_t key_len;
    double fitness;
} cromossome;


double cromossome_fitness (cromossome * const, char * (*decrypt)(char * const key));
cromossome *cromossome_crossover (cromossome * const, cromossome * const);
cromossome *new_cromossome (const size_t, char * const);
void mutate_cromossome (cromossome * const);
void del_cromossome (cromossome *);

#endif /* cromossome.h */
