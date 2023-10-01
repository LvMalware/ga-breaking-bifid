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
    // from "Other People" by Neil Gaiman
    ciphertext = bifid_encrypt(b,
            "When he was done, he sat there, eyes closed, waiting for the voice to say, 'Again.', but nothing was said. He opened his eyes."
            "Slowly he stood up. He was alone."
            "At the far end of the room, there was a door, and as he watched, it opened."
            "A man stepped through the door. There was terror in the man's face, and arrogance, and pride. The man, who wore expensive clothes, took several hesitant steps into the room, and then stopped."
            "When he saw the man, he understood."
            "'Time is fluid here', he told the new arrival.");

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
