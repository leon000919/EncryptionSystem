//playfair密码

#include<iostream>
#include<string>

using namespace std;

inline char* PlayfairEncryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 2) * sizeof(char));
	memset(result, 0, strlen(text) + 2);

	int i = 0, j = 0, k = 0;
	int flag = 1;
	char temp[25] = {};
	char matrix[5][5] = {};
	for (i = 0; i < strlen(ktext); i++)
	{
		if (ktext[i] == 'j')
		{
			ktext[i] = 'i';
		}
	}
	for (i = 0; i < strlen(text); i++)
	{
		if (text[i] == 'j')
		{
			text[i] = 'i';
		}
	}
	for (i = 0; i < strlen(ktext); i++)
	{		//提取key
		flag = 1;
		for (j = 0; j < strlen(temp); j++) 
		{
			if (temp[j] == ktext[i])
			{
				flag = 0;
				break;
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
		if (i != 'j' - 'a')
		{
			flag = 1;
			for (j = 0; j < strlen(temp); j++)
			{
				if (temp[j] == i + 'a')
				{
					flag = 0;
					break;
				}
			}
			if (flag)
			{
				temp[strlen(temp)] = i + 'a';
			}
		}
	}
	//存入矩阵
	for (i = 0; i < 25; i++)
	{
		matrix[i / 5][i % 5] = temp[i];
	}
	//明文连续时，相同字符中间插入z
	for (i = 1; i < strlen(text); i++)
	{
		if (text[i] == text[i - 1] && (i + 1) % 2 == 0)
		{
			for (j = strlen(text); j > i - 1; j--)
			{
				text[j + 1] = text[j];
			}
			text[i] = 'z';
		}
	}
	text[strlen(text) + 1] = 0;
	//明文为奇数位，末尾插入z
	if (strlen(text) % 2 != 0)
	{
		text[strlen(text)] = 'z';
		text[strlen(text) + 1] = 0;
	}
	//开始操作
	for (i = 0; i < strlen(text); i += 2)
	{
		//寻找坐标
		int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		for (j = 0; j < 5; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (matrix[j][k] == text[i])
				{
					x1 = j;
					y1 = k;
				}
				else if (matrix[j][k] == text[i + 1])
				{
					x2 = j;
					y2 = k;
				}
			}
		}
		//判断条件
		//同行右侧替代
		if (x1 == x2)
		{
			y1 = (y1 + 1) % 5;
			y2 = (y2 + 1) % 5;
			result[i] = matrix[x1][y1];
			result[i + 1] = matrix[x2][y2];
		}
		//同列下方替代
		else if (y1 == y2)
		{
			x1 = (x1 + 1) % 5;
			x2 = (x2 + 1) % 5;
			result[i] = matrix[x1][y1];
			result[i + 1] = matrix[x2][y2];
		}
		//对角线
		else
		{
			result[i] = matrix[x1][y2];
			result[i + 1] = matrix[x2][y1];
		}
	}

	return result;
}

inline char* PlayfairDecryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 2) * sizeof(char));
	memset(result, 0, strlen(text) + 2);

	int i = 0, j = 0, k = 0;
	int flag = 1;
	char temp[25] = {};
	char matrix[5][5] = {};
	for (i = 0; i < strlen(ktext); i++)
	{
		if (ktext[i] == 'j')
		{
			ktext[i] = 'i';
		}
	}
	for (i = 0; i < strlen(text); i++)
	{
		if (text[i] == 'j')
		{
			text[i] = 'i';
		}
	}
	for (i = 0; i < strlen(ktext); i++)
	{		//提取key
		flag = 1;
		for (j = 0; j < strlen(temp); j++)
		{
			if (temp[j] == ktext[i])
			{
				flag = 0;
				break;
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
		if (i != 'j' - 'a')
		{
			flag = 1;
			for (j = 0; j < strlen(temp); j++)
			{
				if (temp[j] == i + 'a')
				{
					flag = 0;
					break;
				}
			}
			if (flag)
			{
				temp[strlen(temp)] = i + 'a';
			}
		}
	}
	//存入矩阵
	for (i = 0; i < 25; i++)
	{
		matrix[i / 5][i % 5] = temp[i];
	}
	for (i = 0; i < strlen(text); i += 2)
	{
		//寻找坐标
		int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		for (j = 0; j < 5; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (matrix[j][k] == text[i])
				{
					x1 = j;
					y1 = k;
				}
				else if (matrix[j][k] == text[i + 1])
				{
					x2 = j;
					y2 = k;
				}
			}
		}
		//同行,左侧为明文
		if (x1 == x2)
		{
			y1 = (y1 + 5 - 1) % 5;
			y2 = (y2 + 5 - 1) % 5;
			result[i] = matrix[x1][y1];
			result[i + 1] = matrix[x2][y2];
		}
		//同列上侧
		else if (y1 == y2)
		{
			x1 = (x1 + 5 - 1) % 5;
			x2 = (x2 + 5 - 1) % 5;
			result[i] = matrix[x1][y1];
			result[i + 1] = matrix[x2][y2];
		}
		else
		{
			result[i] = matrix[x1][y2];
			result[i + 1] = matrix[x2][y1];
		}
	}

	return result;
}