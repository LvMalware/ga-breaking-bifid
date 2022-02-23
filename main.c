/*
 * Copyright (C) 2022 Lucas V. Araujo <lucas.vieira.ar@disroot.org>
 *
 * This program is a free software. You can use, redistribute and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3, or any later version.
 */

#include <time.h>
#include <stdio.h>

#include "ga.h"
#include "bifid.h"

#define BLOCK_SIZE 8
#define MODE MODE_CBC

char *ciphertext;

char *decrypt(char * const key)
{
    bifid *b = bifid_init(key, BLOCK_SIZE, MODE);
    char *plain = bifid_decrypt(b, ciphertext);
    bifid_clean(b);
    return plain;
}

int
main(int argc, char *argv[])
{
    srand(time(NULL));
    
    
    char key[] = "CLZUPIYDVNWGXTARSHKFMEBQO";
    bifid *b = bifid_init(key, BLOCK_SIZE, MODE);
    ciphertext = bifid_encrypt(b,
            "She should have died hereafter;"
            "There would have been a time for such a word."
            "To-morrow, and to-morrow, and to-morrow,"
            "Creeps in this petty pace from day to day"
            "To the last syllable of recorded time,"
            "And all our yesterdays have lighted fools"
            "The way to dusty death. Out, out, brief candle!"
            "Life's but a walking shadow, a poor player"
            "That struts and frets his hour upon the stage"
            "And then is heard no more: it is a tale"
            "Told by an idiot, full of sound and fury,"
            "Signifying nothing."
            );

    ga *g = new_ga("ABCDEFGHIKLMNOPQRSTUVWXYZ", decrypt);
    /* choose a random initial population */
    init_population(g, 3000, 25); 
    size_t start = time(NULL);
    ga_evolve(g, 12000, 3000, 1200, 0.8, 0.6);
    size_t end = time(NULL);
    size_t duration = end - start;
    printf("It took %lu seconds.\n", duration);
    ga_clean(g);
    return 0;
}
