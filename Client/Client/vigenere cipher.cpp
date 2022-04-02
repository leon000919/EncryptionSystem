//Vigenere密码

#include<iostream>
#include<string>

using namespace std;

//加解密算法中密文ciphertext记为c；明文plaintext记为p
//加密算法
inline char* VigenereEncryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);
	int j = 0;
	for (int i = 0; i < strlen(text); i++)
	{
		//由于密钥是循环的，i%keylength结果j即为第i次加密时所使用的密钥为key中的第j位
		j = i % strlen(ktext);
		if (text[i] >= 'a' && text[i] <= 'z' && ktext[j] >= 'a' && ktext[j] <= 'z')
		{
			result[i] = (text[i] - 'a' + ktext[j] - 'a') % 26 + 'a';
		}
		else if (text[i] >= 'A' && text[i] <= 'Z' && ktext[j] >= 'a' && ktext[j] <= 'z')
		{
			result[i] = (text[i] - 'A' + ktext[j] - 'a') % 26 + 'A';
		}
		else if (text[i] >= 'a' && text[i] <= 'z' && ktext[j] >= 'A' && ktext[j] <= 'Z')
		{
			result[i] = (text[i] - 'a' + ktext[j] - 'A') % 26 + 'a';
		}
		else if (text[i] >= 'A' && text[i] <= 'Z' && ktext[j] >= 'A' && ktext[j] <= 'Z')
		{
			result[i] = (text[i] - 'A' + ktext[j] - 'A') % 26 + 'A';
		}
	}
	return result;
}
//解密算法
inline char* VigenereDecryption(char* text, char* ktext)
{
	char* result = (char*)malloc((strlen(text) + 1) * sizeof(char));
	memset(result, 0, strlen(text) + 1);
	int j = 0;
	for (int i = 0; i < strlen(text); i++)
	{
		j = i % strlen(ktext);
		if (text[i] >= 'a' && text[i] <= 'z' && ktext[j] >= 'a' && ktext[j] <= 'z')
		{
			result[i] = (text[i] - ktext[j] + 26) % 26 + 'a';
		}
		else if (text[i] >= 'A' && text[i] <= 'Z' && ktext[j] >= 'a' && ktext[j] <= 'z')
		{
			result[i] = (text[i] - 'A' - ktext[j] + 'a' + 26) % 26 + 'A';
		}
		else if (text[i] >= 'a' && text[i] <= 'z' && ktext[j] >= 'A' && ktext[j] <= 'Z')
		{
			result[i] = (text[i] - 'a' - ktext[j] + 'A' + 26) % 26 + 'a';
		}
		else if (text[i] >= 'A' && text[i] <= 'Z' && ktext[j] >= 'A' && ktext[j] <= 'Z')
		{
			result[i] = (text[i] - ktext[j] + 26) % 26 + 'A';
		}
	}
	return result;
}
