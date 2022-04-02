//permutation密码

#include<iostream>

using namespace std;

inline char* PermutationEncryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);

	int* newKeyword = (int*)malloc(sizeof(int) * (strlen(text) + 1));
	newKeyword[strlen(text)] = 0;
	//获得新的密码数组（数学顺序）
	int n = 0;
	for (int i = 0;i < 26;i++)
	{
		for (int j = 0;j < strlen(ktext);j++)
		{
			if (ktext[j] == i + 'a' || ktext[j] == i + 'A')
			{
				newKeyword[j] = n;
				n++;
			}
		}
	}
	for (int i = 0;i < strlen(ktext);i++)
	{
		if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
		{
			result[newKeyword[i]] = text[i];
		}
	}

	return result;
}

inline char* PermutationDecryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);

	int* newKeyword = (int*)malloc(sizeof(int) * (strlen(text) + 1));
	newKeyword[strlen(text)] = 0;
	//获得新的密码数组（数学顺序）
	int n = 0;
	for (int i = 0;i < 26;i++)
	{
		for (int j = 0;j < strlen(ktext);j++)
		{
			if (ktext[j] == i + 'a' || ktext[j] == i + 'a')
			{
				newKeyword[j] = n;
				n++;
			}
		}
	}
	for (int i = 0;i < strlen(ktext);i++)
	{
		if ((text[newKeyword[i]] >= 'a' && text[newKeyword[i]] <= 'z') || (text[newKeyword[i]] >= 'A' && text[newKeyword[i]] <= 'Z'))
		{
			result[i] = text[newKeyword[i]];
		}
	}

	return result;
}