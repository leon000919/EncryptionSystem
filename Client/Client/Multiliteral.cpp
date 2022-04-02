//Multiliteral√‹¬Î

#include<iostream>

using namespace std;

inline char* MultiliteralEncryption(char* text, char* ktext)
{
	char* result = (char*)malloc((2 * strlen(text) + 1) * sizeof(char));
	memset(result, 0, 2 * strlen(text) + 1);

	for (int i = 0;i < strlen(text);i++)
	{
		if (text[i] >= 'a' && text[i] <= 'z')
		{
			if (text[i] <= 'i')
			{
				result[2 * i] = ktext[(text[i] - 'a') / 5];
				result[2 * i + 1] = ktext[(text[i] - 'a') % 5];
			}
			else
			{
				result[2 * i] = ktext[(text[i] - 'a' - 1) / 5];
				result[2 * i + 1] =  ktext[(text[i] - 'a' - 1) % 5];
			}
		}
		else if (text[i] >= 'A' && text[i] <= 'Z')
		{
			if (text[i] <= 'I')
			{
				result[2 * i] = ktext[(text[i] - 'A') / 5];
				result[2 * i + 1] = ktext[(text[i] - 'A') % 5];
			}
			else
			{
				result[2 * i] = ktext[(text[i] - 'A' - 1) / 5];
				result[2 * i + 1] = ktext[(text[i] - 'A' - 1) % 5];
			}
		}
	}
	return result;
}

inline char* MultiliteralDecryption(char* text, char* ktext)
{
	int size;
	if (strlen(text) % 2 == 0)
	{
		size = strlen(text) / 2 + 1;
	}
	else 
	{
		size = strlen(text) / 2 + 2;
	}

	char* result = (char*)malloc(size * sizeof(char));
	memset(result, 0, size);

	for (int i = 0;i < size;i++)
	{
		if (2 * i + 1  == strlen(text))
		{
			text[2 * i + 1] = 'z';
		}
		if (text[2 * i] >= 'a' && text[2 * i] <= 'z' && text[2 * i + 1] >= 'a' && text[2 * i + 1] <= 'z')
		{
			for (int j = 0;j < 5;j++)
			{
				if (text[2 * i + 1] == ktext[j])
				{
					for (int k = 0;k < 5;k++)
					{
						if (text[2 * i] == ktext[k])
						{
							result[i] = j + k * 5 + 'a';
							if (result[i] > 'i')
							{
								result[i]--;
							}
						}
					}
				}
			}
		}
	}
	return result;
}