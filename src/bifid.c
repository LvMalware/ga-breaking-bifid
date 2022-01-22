#include "bifid.h"

void
bifid_clean (bifid * const b)
{
    memset(b->key.bytes, 0x00, KEY_LEN * sizeof(char));
    memset(b->indexes, 0x00, (KEY_LEN + 1) * sizeof(int));
    free(b);
}

bifid *
bifid_init (char * const key, int bs, BIFID_MODE mode)
{
    bifid *b = calloc(1, sizeof(*b));
    b->block_size = bs;
    b->mode = mode;
    size_t i, j = 0, len = strlen(key);
    for (i = 0; i < len; i ++)
    {
        char c = toupper(key[i]);
        if (c == 'J')
            c = 'I';
        if (strchr(b->key.bytes, c) == NULL)
        {
            b->indexes[c - 0x41] = j;
            b->key.bytes[j ++] = c;
        }
    }

    for (i = 0; i < KEY_LEN && j < KEY_LEN; i ++)
    {
        char c = ALPHABET[i];
        if (strchr(b->key.bytes, c) == NULL)
        {
            b->indexes[c - 0x41] = j;
            b->key.bytes[j ++] = c;
        }
    }

    return b;
}

void
encrypt_block(bifid * const b, char * const block, int bs)
{
    int i;
    char *transposed = calloc(bs * 2, sizeof(*transposed));
    for (i = 0; i < bs; i ++)
    {
        int idx            = b->indexes[block[i] - 0x41];
        transposed[i]      = idx / SQR_LEN;
        transposed[i + bs] = idx % SQR_LEN;
    }

    int j = 0;
    for (i = 0; i < 2 * bs; i += 2)
    {
        int idx     = transposed[i] * SQR_LEN + transposed[i + 1];
        block[j ++] = b->key.bytes[idx];
    }

    free(transposed);
}

void
decrypt_block(bifid * const b, char * const block, int bs)
{
    int i, j = 0;
    char *transposed = calloc(bs * 2, sizeof(*transposed));
    for (i = 0; i < 2 * bs; i += 2)
    {
        int idx            = b->indexes[block[j++] - 0x41];
        transposed[i]      = idx / SQR_LEN;
        transposed[i + 1]  = idx % SQR_LEN;
    }

    j = 0;

    for (i = 0; i < bs; i ++ )
    {
        int idx = transposed[i] * SQR_LEN + transposed[i + bs];
        block[j ++] = b->key.bytes[idx];
    }

    free(transposed);
}

static inline int
index_alpha(const char c)
{
    int i;
    for (i = 0; i < KEY_LEN; i ++)
        if (ALPHABET[i] == c)
            break;
    return i;
}

static inline void
mask(char * const block, char * const smask, const int bs)
{
    int i;
    for (i = 0; i < bs; i ++)
    {
        int a = index_alpha(block[i]);
        int b = index_alpha(smask[i]);
        block[i] = ALPHABET[(a + b) % KEY_LEN];
    }
}

static inline void
unmask(char * const block, char * const smask, const int bs)
{
    int i;
    for (i = 0; i < bs; i ++)
    {
        int a = index_alpha(block[i]);
        int b = index_alpha(smask[i]);
        block[i] = ALPHABET[(KEY_LEN + (a - b)) % KEY_LEN];
    }
}

char *
bifid_encrypt(bifid * const b, char * const plain)
{
    size_t i = 0, len = strlen(plain);

    char *out = calloc(1 + len + b->mode * b->block_size, sizeof(*out));
    char *iv = out;

    size_t j = b->mode * b->block_size;
    for (i = 0; i < len; i ++)
    {
        char c = toupper(plain[i]);
        if (c >= 0x41 && c <= 0x5a)
            out[j++] = (c == 'J') ? 'I' : c;
    }

    len = j;

    if (b->mode == MODE_CBC)
    {
        for (i = 0; i < b->block_size; i ++)
            out[i] = ALPHABET[rand() % KEY_LEN];
        out += b->block_size;
        len -= b->block_size;
    }

    for (i = 0; i < len; i += b->block_size)
    {
       int bs = b->block_size;
       if ((i + bs) > len)
           bs = len % bs;

       if (b->mode == MODE_CBC)
           mask(&out[i], iv, bs);

       encrypt_block(b, &out[i], bs);
       iv = &out[i];
    }

    if (b->mode == MODE_CBC)
        out -= b->block_size;

    return out;
}

char *
bifid_decrypt(bifid * const b, char * const cipher)
{
    size_t i = 0, len = strlen(cipher);

    if (b->mode == MODE_CBC)
        len -= b->block_size;

    char *out = calloc(1 + len, sizeof(*out));
    char *iv = cipher; 

    if (b->mode == MODE_CBC)
        memcpy(out, &cipher[b->block_size], len);
    else
        memcpy(out, cipher, len);

    for (i = 0; i < len; i += b->block_size)
    {
       int bs = b->block_size;
       if ((i + bs) > len)
           bs = len % bs;

       decrypt_block(b, &out[i], bs);

       if (b->mode == MODE_CBC)
           unmask(&out[i], iv, bs);
       iv += b->block_size;
    }

    return out;
}
