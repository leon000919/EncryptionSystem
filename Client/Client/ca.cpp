//cellular automata细胞自动机（ASCII）
//输入为字符（明文），整数（种子），整数（rule）

#include <stdio.h>
#include <iostream>

using namespace std;

inline char* CAEncryption(char* text, char* ktext)
{
	char* result = (char*)malloc(257 * sizeof(char));
	memset(result, 0, 257);

	//字符
	int ch_value = text[0];
	char ch[7] = {};
	for (int i = 0;i < 7;i++)
	{
		if (ch_value % 2 == 0)
		{
			ch[6 - i] = '0';
		}
		else
		{
			ch[6 - i] = '1';
		}
		ch_value /= 2;
	}
	//整数（种子），整数（rule）
	char* atext;
	char* btext;
	atext = strtok_s(ktext, ",", &btext);
	int seed = atext[0] - '0';
	int k = 0;
	for (int i = 0;i < strlen(btext);i++)
	{
		k *= 10;
		k += btext[i] - '0';
	}
	char key[8];
	for (int i = 0;i <= 7;i++)
	{
		if (k % 2 == 0)
		{
			key[7 - i] = '0';
		}
		else
		{
			key[7 - i] = '1';
		}
		k /= 2;
	}

	for (int i = 0;i < 256;i++)
	{
		char temp[7];
		for (int j = 0;j < 7;j++)
		{
			temp[j] = key[(ch[(j + 1 + 7) % 7] - '0') + 2 * (ch[(j + 7) % 7] - '0') + 4 * (ch[(j - 1 + 7) % 7] - '0')];
		}
		for (int j = 0;j < 7;j++)
		{
			ch[j] = temp[j];
		}
		result[i] = ch[seed];
	}
	return result;
}