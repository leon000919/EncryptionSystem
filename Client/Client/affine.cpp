//affine√‹¬Î

#include<iostream>

using namespace std;

inline char* AffineEncryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);

	int a = 0;
	int b = 0;
	char* atext;
	char* btext;
	atext = strtok_s(ktext, ",", &btext);
	for (int i = 0;i < strlen(atext);i++)
	{
		a *= 10;
		a += atext[i] - '0';
	}
	for (int i = 0;i < strlen(btext);i++)
	{
		b *= 10;
		b += btext[i] - '0';
	}

	for (int i = 0;i < strlen(text);i++)
	{
		if (text[i] >= 'a' && text[i] <= 'z')
		{
			result[i] = ((text[i] - 'a') * a + b) % 26 + 'a';
		}
		else if (text[i] >= 'A' && text[i] <= 'Z')
		{
			result[i] = ((text[i] - 'A') * a + b) % 26 + 'A';
		}
	}

	return result;
}

inline char* AffineDecryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);

	int a = 0;
	int b = 0;
	char* atext;
	char* btext;
	atext = strtok_s(ktext, ",", &btext);
	for (int i = 0;i < strlen(atext);i++)
	{
		a *= 10;
		a += atext[i] - '0';
	}
	for (int i = 0;i < strlen(btext);i++)
	{
		b *= 10;
		b += btext[i] - '0';
	}

	int a_inv;
	//≥À∑®ƒÊ‘™
	for (int i = 0; i < 26; i++)
	{
		if ((a * i) % 26 == 1)
		{
			a_inv = i;
		}
	}
	for (int i = 0;i < strlen(text);i++)
	{
		if (text[i] >= 'a' && text[i] <= 'z')
		{
			result[i] = (((text[i] - 'a') - b + 26) * a_inv) % 26 + 'a';
		}
		else if (text[i] >= 'A' && text[i] <= 'Z')
		{
			result[i] = (((text[i] - 'A') - b + 26) * a_inv) % 26 + 'A';
		}
	}

	return result;
}