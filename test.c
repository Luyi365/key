#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "key.h"

char data0[10] = {
    0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0x10,
};
char data1[10] = {
    0x1,0x1,0x1,0x1
};

void print_array(unsigned char title[], unsigned char data[], unsigned int len)
{
    int i;

    printf("%s ----[%d]\n", title, len);
    for(i = 0;i < len;i++)
    {
        printf("%02x ", data[i]);
    }
    printf("\n");
}
int main(int argc, char *argv[])
{
    int i;
    unsigned int len;
    int j, r, key_num;
    unsigned int sync = 0;
    unsigned char key[MAX_KEY_REQUEST];
    char buf[120] = { 0 };
    unsigned int mykeygen;

#if 1
    if(argc != 4) {
        fprintf(stderr, "Usage: %s <seed> <key num> <keygen>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sync = atoi(argv[1]);
    key_num = atoi(argv[2]);
    mykeygen = atoi(argv[3]);

#endif

    printf("\n--------------采用自定义的keygen、同步码开始加密----------------\n");
    set_keygen(mykeygen);
    print_array("\n明文:", data0, key_num);

    memset(key, 0, sizeof(key));
    len = request_key(sync, key_num, key);

    print_array("密钥:", key, len);

    for(i = 0;i < len;i++)
    {
        buf[i] = data0[i] ^ key[i];
    }

    print_array("\n密文:", buf, len);

    printf("\n--------------------开始解密--------------------\n");
    set_keygen(mykeygen);

    memset(key, 0, sizeof(key));
    len = request_key(sync, key_num, key);

    for(i = 0;i < len;i++)
    {
        buf[i] = buf[i] ^ key[i];
    }

    print_array("\n明文:", buf, len);

    exit(EXIT_SUCCESS);

    key_num = 10;

#if 0
    printf("\n--------------采用默认keygen 同步码=0 产生密文----------------\n");
    reset_keygen();

    memset(key, 0, sizeof(key));
    len = request_key(sync, key_num, key);

    print_array("密钥0-9:", key, len);

    memset(key, 0, sizeof(key));
    len = request_key(sync, key_num, key);

    print_array("密钥10-19:", key, len);

    printf("\n--------------采用keygen=1234 同步码=0 产生密文----------------\n");
    set_keygen(1234);

    memset(key, 0, sizeof(key));
    len = request_key(sync, key_num, key);

    print_array("密钥0-9:", key, len);

    memset(key, 0, sizeof(key));
    len = request_key(sync, key_num, key);

    print_array("密钥10-19:", key, len);

#endif

#if 0
    if(argc != 4) {
        fprintf(stderr, "Usage: %s <seed> <key num> <keygen>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sync = atoi(argv[1]);
    key_num = atoi(argv[2]);
    mykeygen = atoi(argv[3]);

#endif

    printf("\n--------------采用默认keygen开始加密----------------\n");
    reset_keygen();
    print_array("\n明文:", data0, 10);

    memset(key, 0, sizeof(key));
    len = request_key(sync, 10, key);

    print_array("密钥:", key, len);

    for(i = 0;i < len;i++)
    {
        buf[i] = data0[i] ^ key[i];
    }

    print_array("\n密文:", buf, len);

    printf("\n--------------------开始解密--------------------\n");
    reset_keygen();

    memset(key, 0, sizeof(key));
    len = request_key(sync, 10, key);

    for(i = 0;i < len;i++)
    {
        buf[i] = buf[i] ^ key[i];
    }

    print_array("\n明文:", buf, len);

    exit(EXIT_SUCCESS);
}