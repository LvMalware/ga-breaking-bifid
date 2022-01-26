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

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* frequency of Portuguese letters
 * source: http://www.mat.uc.pt/~pedro/cientificos/Cripto/
 */
static const double frequences[] = {

    /* a */ 14.811241, /* e */ 12.775882, /* o */ 10.633712,
    /* s */ 7.917737, /* r */ 6.73638, /* i */ 5.898991, /* d */ 5.094293,
    /* n */ 4.909511, /* m */ 4.665041, /* u */ 4.473257, /* t */ 4.174096,
    /* c */ 3.690996, /* l */ 3.058572, /* p */ 2.429868, /* v */ 1.705386,
    /* h */ 1.4636, /* q */ 1.226368, /* g */ 1.210764, /* b */ 1.05156,
    /* f */ 0.980315, /* z */ 0.466385, /* j */ 0.371861, /* x */ 0.215266,
    /* y */ 0.027841, /* k */ 0.005934, /* w */ 0.005142
};

typedef struct bg
{
    char *b;
    double f;
} bg;

/* frequency of english bigrams */
static const bg bigrams[] = {
    { "VA", 0.700842 }, { "AN", 1.190085 }, { "OS", 1.910517 },
    { "UE", 1.355447 }, { "DE", 2.291532 }, { "ER", 1.455598 },
    { "IN", 1.006691 }, { "HA", 0.628594 }, { "AS", 1.891641 },
    { "ON", 0.687069 }, { "RO", 0.820453 }, { "IS", 0.842983 },
    { "PA", 0.813523 }, { "QU", 1.571998 }, { "MO", 0.656453 },
    { "IA", 1.053891 }, { "AD", 1.053037 }, { "DA", 1.438171 },
    { "EM", 0.98335  }, { "CA", 0.925988 }, { "LA", 0.719967 },
    { "PE", 0.644086 }, { "AL", 0.879296 }, { "TO", 1.102961 },
    { "UM", 0.788345 }, { "SS", 0.656994 }, { "ME", 0.990431 },
    { "AM", 0.866561 }, { "PO", 0.736269 }, { "OM", 0.845199 },
    { "NT", 1.388766 }, { "TE", 1.289469 }, { "RA", 2.167392 },
    { "EL", 0.883372 }, { "SE", 1.436301 }, { "ND", 0.854723 },
    { "DO", 1.817155 }, { "RI", 0.898842 }, { "EN", 1.56696  },
    { "AR", 1.715414 }, { "MA", 1.233426 }, { "AO", 0.912896 },
    { "ES", 1.977868 }, { "OR", 1.294896 }, { "OU", 0.684118 },
    { "TA", 1.131793 }, { "RE", 1.40696  }, { "CO", 1.435144 },
    { "ST", 0.891383 }, { "SA", 0.795556 }, { "EI", 0.689113 }
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
