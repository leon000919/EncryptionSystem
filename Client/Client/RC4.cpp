//RC4
#include<iostream>
#include<stdio.h>

using namespace std;

inline char* RC4Encryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);

	unsigned char s[128] = {};
	int i = 0, j = 0;

	for (i = 0; i < 128; i++)
	{
		s[i] = i;
	}

	unsigned char k[128] = {};
	for (i = strlen(ktext); i < 128; i++)
	{
		k[i] = ktext[i % strlen(ktext)];
	}
	//KSA
	for (i = 0; i < 128; i++)
	{
		j = (s[i] + k[i] + j) % 128;
		//交换
		swap(s[i], s[j]);
	}
	//PRGA
	int t;
	i = 0;
	j = 0;
	for (int x = 0; x < strlen(text); x++)
	{
		i = (i + 1) % 128;
		j = (j + s[i]) % 128;
		swap(s[i], s[j]);
		t = (s[i] + s[j]) % 128;
		result[x] = text[x] ^ s[t];
	}
	for (int i = 0;i < strlen(result);i++)
	{
		result[i] = (unsigned char)result[i];
	}
	return result;
}