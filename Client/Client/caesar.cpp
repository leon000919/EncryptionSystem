//Caesar密码

#include<iostream>

using namespace std;

inline char* CaesarEncryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);
	int key = 0;
	for (int i = 0;i < strlen(ktext);i++)
	{
		key *= 10;
		key += ktext[i] - 'a';
	}
	
	for (int i = 0;i < strlen(text);i++)
	{
		if (text[i] >= 'a' && text[i] <= 'z')
		{
			result[i] = (text[i] - 'a' + key) % 26 + 'a';
		}
		else if (text[i] >= 'A' && text[i] <= 'Z')
		{
			result[i] = (text[i] - 'A' + key) % 26 + 'A';
		}
	}
	
	return result;
}

inline char* CaesarDecryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);
	int key = 0;
	for (int i = 0;i < strlen(ktext);i++)
	{
		key *= 10;
		key += ktext[i] - 'a';
	}
	
	for (int i = 0;i < strlen(text);i++)
	{
		if (text[i] >= 'a' && text[i] <= 'z')
		{
			result[i] = (text[i] - 'a' - key) % 26 + 'a';
		}
		else if (text[i] >= 'A' && text[i] <= 'Z')
		{
			result[i] = (text[i] - 'A' - key) % 26 + 'A';
		}
	}

	return result;
}