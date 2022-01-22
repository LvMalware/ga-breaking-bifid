#ifndef _BIFID_H
#define _BIFID_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SQR_LEN 5
#define KEY_LEN 25 

/* I and J are the same */
static const char ALPHABET[KEY_LEN] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

typedef enum
{
    MODE_ECB,
    MODE_CBC
} BIFID_MODE;

typedef struct bifid
{
    union {
        char bytes[KEY_LEN];
        char square[SQR_LEN][SQR_LEN];
    } key;
    int indexes[KEY_LEN + 1];
    int block_size;
    BIFID_MODE mode;
} bifid;

void bifid_clean (bifid * const);
bifid *bifid_init (char * const, int, BIFID_MODE);
char *bifid_encrypt (bifid * const, char * const);
char *bifid_decrypt (bifid * const, char * const);

#endif /* bifid.h */
