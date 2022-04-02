//keyword密码

#include<iostream>
#include<string>

using namespace std;

inline char* KeywordEncryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);
	char temp[27] = {};
	int i = 0, j = 0;
	int flag = 1;
	//生成对照表
	//key部分
	for (i = 0; i < strlen(ktext); i++) 
	{	//提取key
		flag = 1;
		for (j = 0; j < strlen(temp); j++) 
		{
			if (temp[j] == ktext[i])
			{
				flag = 0;
			}
		}
		if (flag)
		{
			temp[j] = ktext[i];
		}

	}
	//剩余部分
	for (i = 0; i < 26; i++)
	{
		flag = 1;
		for (j = 0; j < strlen(temp); j++)
		{
			if (temp[j] == i + 'a')
			{
				flag = 0;
			}
		}
		if (flag)
		{
			temp[strlen(temp)] = i + 'a';
		}
	}

	for (int k = 0;k < strlen(text);k++)
	{
		if (text[k] >= 'a' && text[k] <= 'z')
		{
			result[k] = temp[text[k] - 'a'];
		}
	}

	return result;
}

inline char* KeywordDecryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);
	char temp[27] = {};
	int i = 0, j = 0;
	int flag = 1;
	//生成对照表
	//key部分
	for (i = 0; i < strlen(ktext); i++)
	{	//提取key
		flag = 1;
		for (j = 0; j < strlen(temp); j++)
		{
			if (temp[j] == ktext[i])
			{
				flag = 0;
			}
		}
		if (flag)
		{
			temp[j] = ktext[i];
		}

	}
	//剩余部分
	for (i = 0; i < 26; i++)
	{
		flag = 1;
		for (j = 0; j < strlen(temp); j++)
		{
			if (temp[j] == i + 'a')
			{
				flag = 0;
			}
		}
		if (flag)
		{
			temp[strlen(temp)] = i + 'a';
		}
	}

	for (int k = 0;k < strlen(text);k++)
	{
		if (text[k] >= 'a' && text[k] <= 'z')
		{
			for (int l = 0;l < strlen(temp);l++)
			{
				if (temp[l] == text[k])
				{
					result[k] = l + 'a';
				}
			}
		}
	}

	return result;
}