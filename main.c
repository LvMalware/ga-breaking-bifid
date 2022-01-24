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
    
    /* Apparently Portuguese can't be broken with monograms... */
    
    char key[] = "CLZUPIYDVNWGXTARSHKFMEBQO";
    bifid *b = bifid_init(key, BLOCK_SIZE, MODE);
    ciphertext = bifid_encrypt(b,
        "Minha terra tem palmeiras,"
        "Onde canta o Sabia;"
        "As aves, que aqui gorjeiam,"
        "Não gorjeiam como la."
        "Nosso ceu tem mais estrelas,"
        "Nossas varzeas tem mais flores,"
        "Nossos bosques tem mais vida,"
        "Nossa vida mais amores."
        "Em cismar, sozinho, a noite,"
        "Mais prazer encontro eu la;"
        "Minha terra tem palmeiras,"
        "Onde canta o Sabia."
        "Minha terra tem primores,"
        "Que tais nao encontro eu ca;"
        "Em cismar — sozinho, a noite —"
        "Mais prazer encontro eu la;"
        "Minha terra tem palmeiras,"
        "Onde canta o Sabia."
        "Nao permita Deus que eu morra,"
        "Sem que eu volte para la;"
        "Sem que desfrute os primores"
        "Que nao encontro por ca;"
        "Sem quinda aviste as palmeiras,"
        "Onde canta o Sabia."
            );

    ga *g = new_ga("ABCDEFGHIKLMNOPQRSTUVWXYZ", decrypt);
    /* choose a random initial population */
    init_population(g, 3000, 25); 
    size_t start = time(NULL);
    ga_evolve(g, 12000, 3000, 1000, 0.8, 0.8);
    size_t end = time(NULL);
    size_t duration = end - start;
    printf("It took %lu seconds.\n", duration);
    ga_clean(g);
    return 0;
}
