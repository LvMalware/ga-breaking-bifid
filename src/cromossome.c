/*
 * Copyright (C) 2022 Lucas V. Araujo <lucas.vieira.ar@disroot.org>
 *
 * This program is a free software. You can use, redistribute and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3, or any later version.
 */

#include "cromossome.h"

cromossome *
cromossome_crossover (cromossome * const a, cromossome * const b)
{
    cromossome *c = calloc(1, sizeof(*c));
    c->key_len = a->key_len;

    char *k1 = (a->fitness > b->fitness) ? a->key : b->key;
    char *k2 = (k1 == a->key) ? b->key : a->key;
    size_t count = rand() % c->key_len;
    if (count == 0)
	    count = c->key_len / 2;

    int i, j = 0;
    for (i = 0; i < count; i ++)
        c->key[j++] = k1[i];

    for (i = 0; i < c->key_len && j < c->key_len; i ++)
        if (strchr(c->key, k2[i]) == NULL)
            c->key[j ++] = k2[i];

    return c;
}

static inline void
swap (char * const a, char * const b)
{
    char c = *a;
    *a = *b;
    *b = c;
}

static inline void
shuffle (char * const alphabet)
{
    size_t i, len = strlen(alphabet);
    for (i = 0; i < len / 2; i ++)
        swap(&alphabet[i], &alphabet[rand() % len]);
}

cromossome *
new_cromossome (const size_t key_len, char * const alphabet)
{
    cromossome * c = calloc(1, sizeof(*c));
    c->key_len = key_len;
    shuffle(alphabet);
    memcpy(c->key, alphabet, key_len);
    return c;
}

static inline
double bg_freq(const char *b)
{
    size_t i;
    for (i = 0; i < sizeof(bigrams) / sizeof(bg); i ++)
        if (strncmp(b, bigrams[i].b, 2) == 0)
            return log(100 * bigrams[i].f) / log(10);
    return 0;
}

double
cromossome_fitness (cromossome * const c, char * (*decrypt)(char * const key))
{
    if (c->fitness == 0)
    {
        size_t i;
        char *plain = decrypt(c->key);
#ifndef BIGRAM_FREQUENCY_AS_FITNESS
        for (i = 0; i < strlen(plain); i ++)
            c->fitness += frequences[toupper(plain[i]) - 65];
#else
        for (i = 0; i < strlen(plain) - 1; i ++)
            c->fitness += bg_freq(&plain[i]);
#endif /* BIGRAM_FREQUENCY_AS_FITNESS */
        free(plain);
    }
    return c->fitness;
}

void
mutate_cromossome (cromossome * const c)
{
    int x = rand() % c->key_len;
    int y = rand() % c->key_len;
    swap(&c->key[x], &c->key[y]);
}

void
del_cromossome (cromossome * c)
{
    free(c);
}
