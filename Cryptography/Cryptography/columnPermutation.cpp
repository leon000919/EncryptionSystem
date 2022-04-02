//column permutation密码

#include<iostream>

using namespace std;

inline char* ColumnPermutationEncryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + strlen(ktext) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + strlen(ktext) + 1);

	int* newKeyword = (int*)malloc(sizeof(int) * (strlen(ktext) + 1));
	newKeyword[strlen(ktext)] = 0;
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
	int x = strlen(text) % strlen(ktext);//前x列多一个数
	int* columnLength = (int*)malloc(sizeof(int) * strlen(ktext));
	int flag = 0;
	for (int i = 0;i < strlen(ktext);i++)
	{
		if (newKeyword[i] >= x)
		{
			columnLength[i] = strlen(text) / strlen(ktext);
		}
		else
		{
			columnLength[i] = strlen(text) / strlen(ktext) + 1;
		}
	}
	for (int i = 0;i < strlen(ktext);i++)
	{
		for (int j = 0;j < columnLength[i];j++)
		{
			if ((text[j * strlen(ktext) + newKeyword[i]] >= 'a' && text[j * strlen(ktext) + newKeyword[i]] <= 'z') 
				|| (text[j * strlen(ktext) + newKeyword[i]] >= 'A' && text[j * strlen(ktext) + newKeyword[i]] <= 'Z'))
			{
				result[flag] = text[j * strlen(ktext) + newKeyword[i]];
				flag++;
			}
		}
	}

	return result;
}

inline char* ColumnPermutationDecryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + strlen(ktext) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + strlen(ktext) + 1);

	int* newKeyword = (int*)malloc(sizeof(int) * (strlen(ktext) + 1));
	newKeyword[strlen(ktext)] = 0;
	//获得新的密码数组（数学顺序）
	int n = 0;
	for (int i = 0;i < 26;i++)
	{
		for (int j = 0;j < strlen(ktext);j++)
		{
			if (ktext[j] == i + 'a')
			{
				newKeyword[j] = n;
				n++;
			}
		}
	}
	int x = strlen(text) % strlen(ktext);//前x列多一个数
	int* columnLength = (int*)malloc(sizeof(int) * strlen(ktext));
	int flag = 0;
	for (int i = 0;i < strlen(ktext);i++)
	{
		if (newKeyword[i] >= x)
		{
			columnLength[i] = strlen(text) / strlen(ktext);
		}
		else
		{
			columnLength[i] = strlen(text) / strlen(ktext) + 1;
		}
	}
	for (int i = 0;i < strlen(ktext);i++)
	{
		for (int j = 0;j < columnLength[i];j++)
		{
			if ((text[flag] >= 'a' && text[flag] <= 'z')
				|| (text[flag] >= 'A' && text[flag] <= 'Z'))
			{
				result[j * strlen(ktext) + newKeyword[i]] = text[flag];
				flag++;
			}
		}
	}

	return result;
}