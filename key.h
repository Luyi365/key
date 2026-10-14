#ifndef _KEY_STATION
#define _KEY_STATION
#define MAX_KEY_REQUEST 512

void reset_keygen(int sync);
void set_keygen(int sync,int key);
int born_seed(int sync,int key);
int request_key(int key_num,unsigned char key[]);

#endif
