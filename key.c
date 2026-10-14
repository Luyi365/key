#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "key.h"

static int keygen = 0;
static int offset = 0;

static int default_keygen = 0x9527;


void reset_keygen()
{
    set_keygen(default_keygen);
}

void set_keygen(int key)
{
    keygen = key;
    offset = 0;
}

int born_seed(int sync, int key)
{
    return (sync ^ key);
}

int request_key(int sync, int key_num, char key[])
{
    int i, j, r;
    int seed;

    seed = born_seed(sync, keygen);

    srand(seed);
    if(key_num > MAX_KEY_REQUEST)
    {
        key_num = MAX_KEY_REQUEST;
    }

    for(i = 0;i < offset;i++)
    {
        rand();
    }

    for(j = 0; j < key_num; j++) {
        r = rand() & 0xff;
        key[j] = r;
    }
    offset += key_num;
    return key_num;
}
