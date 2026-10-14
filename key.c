#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "key.h"

static int keygen = 0;
static int sync_code = 0;
static int offset = 0;
static int seeded = 0;

static int default_keygen = 0x9527;


void reset_keygen(int sync)
{
    set_keygen(sync, default_keygen);
}

void set_keygen(int sync, int key)
{
    sync_code = sync;
    keygen = key;
    offset = 0;
    seeded = 0;
}

int born_seed(int sync, int key)
{
    return (sync ^ key);
}

int request_key(int key_num, unsigned char key[])
{
    int j, r;
    int seed;

    if(!seeded)
    {
        seed = born_seed(sync_code, keygen);
        srand(seed);
        seeded = 1;
    }

    if(key_num > MAX_KEY_REQUEST)
    {
        key_num = MAX_KEY_REQUEST;
    }

    for(j = 0; j < key_num; j++) {
        r = rand() & 0xff;
        key[j] = (unsigned char)r;
    }
    offset += key_num;
    return key_num;
}
