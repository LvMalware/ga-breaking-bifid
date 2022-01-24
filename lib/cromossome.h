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
    { "DE", 0.2291532 }, { "RA", 0.2167392 }, { "ES", 0.1977868 },
    { "OS", 0.1910517 }, { "AS", 0.1891641 }, { "DO", 0.1817155 },
    { "AR", 0.1715414 }, { "QU", 0.1571998 }, { "EN", 0.156696  },
    { "ER", 0.1455598 }, { "DA", 0.1438171 }, { "SE", 0.1436301 },
    { "CO", 0.1435144 }, { "RE", 0.140696  }, { "NT", 0.1388766 },
    { "UE", 0.1355447 }, { "OR", 0.1294896 }, { "TE", 0.1289469 },
    { "MA", 0.1233426 }, { "AN", 0.1190085 }, { "TA", 0.1131793 },
    { "TO", 0.1102961 }, { "IA", 0.1053891 }, { "AD", 0.1053037 },
    { "IN", 0.1006691 }, { "ME", 0.0990431 }, { "EM", 0.098335  },
    { "CA", 0.0925988 }, { "AO", 0.0912896 }, { "RI", 0.0898842 }

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
