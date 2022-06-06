#include "T1Header.h"

// the function creates a compressed array that holds client information
Short_client* createShortClientArr(int size)
{
	Client* clients = (Client*)malloc(sizeof(Client) * size);
	Short_client* res;

	for (int i = 0; i < size; i++)
	{
		printf("Please enter id and then phone num:\n");
		scanf("%s%s", clients[i].id, clients[i].phone);
	}

	res = compressData(clients, size);
	return res;
}

// compresses the information frome a client array.
// the function stores numbers in half a BYTE as their binary representation.
// numbers are from 0 - 9.
Short_client* compressData(Client* clients, int size)
{
	Short_client* res = (Short_client*)malloc(sizeof(Short_client) * size);
	for (int i = 0; i < size; i++)
	{
		
		res[i] = compressClientData(clients[i]);
	}
	return res;
}

// compresses client phone number(without "-") and ID into BYTE array
Short_client compressClientData(Client client)
{
	Short_client res;
	BYTE mask1 = 0X0, mask2 = 0X0;
	int num1, num2, i, j = 0;

	// ---- compresses ID ----
	// runs on 4 BYTES and adds a number in binary
	// every 4 bits in the BYTE
	for (i = 0; i < 4; i++)
	{
		num1 = client.id[i * 2] - '0';
		num2 = client.id[i * 2 + 1] - '0';
		mask1 = (BYTE)num1;
		mask2 = (BYTE)num2;
		mask1 = mask1 << 4;
		res.short_id[i] = mask2 | mask1;
	}
	i = 0;

	// ---- compresses phone number ----
	// inputs a single digit number in binary, into 4 bits in a BYTE
	while(client.phone[j] != '\0' && i < 5)
	{
		num1 = client.phone[j] - '0';
		if (client.phone[j + 1] == '-')
		{
			j++;
			num2 = client.phone[j + 1] - '0';
		}
		num2 = client.phone[j + 1] - '0';
		mask1 = (BYTE)num1;
		mask2 = (BYTE)num2;
		mask1 = mask1 << 4;
		res.short_phone[i] = mask2 | mask1;
		j += 2;
		i++;
	}
	return res;
}

// compresses the recieved ID and compares it with all the other ID's from the client array
char* searchClientByID(Short_client* arr, int size, char* id)
{
	char* res = NULL;
	BYTE* short_id = compressID(id);
	for (int i = 0; i < size; i++)
	{
		if (compareId(short_id, arr[i].short_id) == 0)
		{
			res = decompressPhone(arr[i]);
		}
	}
	return res;
}

// compresses an ID into a 4 BYTE array
BYTE* compressID(char* id)
{
	BYTE* short_id = (BYTE*)malloc(sizeof(BYTE) * 4);
	int num1, num2, i = 0;
	BYTE mask1, mask2;

	// changes single digit number into a binary representation
	// and adds it to the first or second 4 bits in BYTE
	for (i = 0; i < 4; i++)
	{
		num1 = id[i * 2] - '0';
		num2 = id[i * 2 + 1] - '0';
		mask1 = (BYTE)num1;
		mask2 = (BYTE)num2;
		mask1 = mask1 << 4;
		short_id[i] = mask1 | mask2;
	}
	return short_id;
}

// compares every 4 bits in the BYTE arrays
int compareId(BYTE* id1, BYTE* id2)
{
	int res = 0;
	for (int i = 0; i < 4 && res == 0; i++)
	{
		if (id1[i] != id2[i])
			res = 1;
	}
	return res;
}

// converts the BYTE array into a string
// by converting every 4 bits in a BYTE to number strings
char* decompressPhone(Short_client client)
{
	BYTE mask1 = 0XF0, mask2 = 0X0F, tmp1, tmp2;
	int j = 0;
	char* res = (char*)malloc(sizeof(char) * 12);
	for (int i = 0; i < 10; i += 2)
	{
		tmp1 = mask1 & client.short_phone[j];
		tmp2 = mask2 & client.short_phone[j];
		tmp1 = tmp1 >> 4;
		res[i] = tmp1 + '0';

		if (i + 1 == 3)
		{
			res[i + 1] = '-';
			i++;
		}

		res[i + 1] = tmp2 + '0';
		mask1 = 0XF0;
		mask2 = 0X0F;
		j++;
	}
	res[11] = '\0';
	return res;
}