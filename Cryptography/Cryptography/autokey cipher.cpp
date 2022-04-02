//autokey cipher√‹¬Î

#include<iostream>
#include<string>

using namespace std;

inline char* AutokeyCiphertextEncryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);

	for (int i = 0; i < strlen(text); i++)
	{
		if (i < strlen(ktext))
			result[i] = (ktext[i] - 'a' + text[i] - 'a') % 26 + 'a';
		else
			result[i] = (result[i - strlen(ktext)] - 'a' + text[i] - 'a') % 26 + 'a';
	}

	return result;
}

inline char* AutokeyCiphertextDecryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);

	for (int i = 0; i < strlen(text); i++)
	{
		if (i < strlen(ktext))
			result[i] = (text[i] + 26 - ktext[i]) % 26 + 'a';
		else
			result[i] = (text[i] + 26 - text[i - strlen(ktext)]) % 26 + 'a';
	}

	return result;
}