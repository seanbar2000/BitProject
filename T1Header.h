#ifndef T1Header
#define T1Header

#define _CRT_SECURE_NO_WARNINGS // created by: sean bar
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
typedef unsigned char BYTE;
typedef struct _short_client
{
	unsigned char short_id[4];
	unsigned char short_phone[5];
} Short_client;

typedef struct _client
{
	char id[9];     
	char phone[12]; 	
} Client;

Short_client compressClientData(Client client);
Short_client* compressData(Client* clients, int size);
Short_client* createShortClientArr(int size);
char* searchClientByID(Short_client* arr, int size, char* id);
BYTE* compressID(char* id);
int compareId(BYTE* id1, BYTE* id2);
char* decompressPhone(Short_client client);



#endif