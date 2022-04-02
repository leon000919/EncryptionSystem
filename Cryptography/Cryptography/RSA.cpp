//RSA

#include<iostream>
#include<math.h>

using namespace std;

//最大公因数
typedef long long ll;
//求原根 求num mod p的原根
inline ll ExEuclid(ll a, ll b)
{
	if (b > a)
	{
		ll temp = b;
		b = a;
		a = temp;
	}
	if (a % b != 0)
	{
		ExEuclid(b, a % b);
	}
	else
	{
		return b;
	}
}
//素数判断
inline int prime(int n)
{
	for (int i = 2; i <= pow(n, 0.5); i++)
	{
		if (n % i == 0)
		{
			return	0;
		}
	}
	return 1;
}
//素数表生成
inline ll* initprime(int m)
{
	ll* num = new ll[m];
	int n = 0;
	for (int i = 10001; m != n; i += 2)
	{
		if (prime(i))
		{
			num[n++] = i;
		}
	}
	return num;
}
//快速幂 x^m mod n
inline ll q_pow(ll x, ll m, ll n)
{
	if (m == 0)
	{
		return 1;
	}
	ll temp = 1;
	while (m > 0)
	{
		if (m & 1)
		{
			temp = (temp * x) % n;
		}
		x = (x * x) % n;
		m = m / 2;
	}
	return temp;
}

inline ll pri_root(ll num)
{
	int flag = 1;
	for (ll i = num - 1; i > 2; i--)
	{
		flag = 1;
		for (ll j = 1; j < num - 1; j++)
		{
			if (q_pow(i, j, num) == 1)
			{
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			return i;
		}
	}
}

inline char* RSAKeyGeneration()
{
	int m = 1000;
	ll* p = initprime(m);
	srand((unsigned)time(NULL));
	//生成随机数
	ll prime_p = p[rand() % m];
	ll prime_q = p[rand() % m];
	ll n = prime_p * prime_q;
	ll fn = (prime_p - 1) * (prime_q - 1);
	ll d = rand() % fn;
	//生成e与fn互素.
	while (ExEuclid(d, fn) != 1)
	{
		d = rand() % fn;
	}
	ll e = 0;
	for (e = 1; e < fn; e++)
	{
		if ((d * e) % fn == 1)
		{
			break;
		}
	}
	char* str = (char*)malloc(1000 * sizeof(char));
	memset(str, 0, 1000 * sizeof(char));
	char* str1 = (char*)malloc(100 * sizeof(char));
	memset(str, 0, 1000 * sizeof(char));
	char* str2 = (char*)malloc(100 * sizeof(char));
	memset(str, 0, 1000 * sizeof(char));
	char* str3 = (char*)malloc(100 * sizeof(char));
	memset(str, 0, 1000 * sizeof(char));
	char* str4 = ",";
	itoa(e, str1, 10);
	itoa(d, str2, 10);
	itoa(n, str3, 10);
	strcat(str, str1);
	strcat(str, str4);
	strcat(str, str2);
	strcat(str, str4);
	strcat(str, str3);

	return str;
}

inline char* RSAEncryption(char* text, char* ktext)
{
	char* etext;
	char* ntext;
	etext = strtok_s(ktext, ",", &ntext);

	ll e = 0;
	for (int i = 0;i < strlen(etext);i++)
	{
		e *= 10;
		e += etext[i] - '0';
	}

	ll n = 0;
	for (int i = 0;i < strlen(ntext);i++)
	{
		n *= 10;
		n += ntext[i] - '0';
	}
	//加密
	ll ptext = 0;
	for (int i = 0;i < strlen(text);i++)
	{
		ptext *= 10;
		ptext += text[i] - '0';
	}
	ll ctext = q_pow(ptext, e, n);
	char* str = (char*)malloc(1000 * sizeof(char));
	memset(str, 0, 1000 * sizeof(char));
	char* str1 = itoa(ctext, str, 10);

	return str1;
}

inline char* RSADecryption(char* text, char* ktext)
{
	char* dtext;
	char* ntext;
	dtext = strtok_s(ktext, ",", &ntext);

	ll d = 0;
	for (int i = 0;i < strlen(dtext);i++)
	{
		d *= 10;
		d += dtext[i] - '0';
	}

	ll n = 0;
	for (int i = 0;i < strlen(ntext);i++)
	{
		n *= 10;
		n += ntext[i] - '0';
	}
	//解密
	ll ctext = 0;
	for (int i = 0;i < strlen(text);i++)
	{
		ctext *= 10;
		ctext += text[i] - '0';
	}
	ll ptext = q_pow(ctext, d, n);
	char* str = (char*)malloc(1000 * sizeof(char));
	memset(str, 0, 1000 * sizeof(char));
	char* str1 = itoa(ptext, str, 10);

	return str1;
}