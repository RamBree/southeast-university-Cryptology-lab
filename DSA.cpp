#include<iostream>
#include<cstdlib>
#include<time.h>
#include<cmath>
#include "SHA1.h"
using namespace std;
long long p, q, h, g;
long long E[1000000],Enum;
long long x,y,k,_k;
long long r, s,_s;
long long w, u1, u2, v;
long long HM;
string M;
long long gcd(long long a, long long b)
{
	if (b == 0)return a;
	else return gcd(b, a % b);
}
void exgcd(long long a, long long b, long long& x, long long& y)
{
    if (b == 0) { x = 1; y = 0; return; }
    exgcd(b, a % b, x, y);
    long long tp = x;
    x = y; y = tp - a / b * y;
}//贝祖定理求ax+by=gcd（x，y）
int Isprim(long long n)
{
	for (long long i = 2; i < sqrt(n); i++)
	{
		if (n % i == 0) return 0;
	}
	return 1;
}
void Show(long long a[], long long n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
long long Pows(long long m, long long e, long long mod)
{
	int a[1000], i = 0;
	while (e) { a[i++] = e & 0x000001; e = e >> 1; }//快速幂
	long long b = m, result = 1;
	for (int j = 0; j < i; j++)
	{
		result *= a[j] == 0 ? 1 : b;
		result = result % mod;
		b *= b;
		b = b % mod;
	}
	return result % mod;
}//快速幂算法
void Sel(long long p, long long* a, long long& num)
{
	for (int i = 3; i < p; i+=2)
	{
		if (Isprim(i)&&p%i==0) *(a + num++) = i;//素数且整除
	}
}
void SelH()
{
	for (long long i = 2; i < p - 1; i++)
	{
		if ((g=Pows(i, (p - 1) / q, p)) > 1)
		{
			h = i;
			cout << "h=" << h << endl;
			cout << "g=" << g << endl;
			return;
		}
	}
}
void CalParameter()
{
	p = 453371;
	cout << "取p=" << p << endl;
	Sel(p - 1, E, Enum);
	cout << "素因子有：" << endl;
	Show(E, Enum);
	q = E[Enum - 1];
	cout << "选择q=" <<q<< endl;
	system("pause");
	SelH();

}
void CalKey()
{
	srand(time(0));
	x = rand() % q;
	y = Pows(g, x, p);
	cout << "私钥x=" << x << "	公钥y=" << y << endl;
}
void CalSig()
{
	k = rand() % q;
	cout <<"随机数取" << "k=" << k << endl;
	r = Pows(g, k, p)%q;
	long long temp=0;
	exgcd(k, q, _k, temp);//k*_k+q*temp=gcd(k,q)=1;
	_k = _k > 0 ? _k : _k + q;//求k逆
	s = (_k * ((HM + x * r) % q))%q;
	cout << "签名为（" << r << "，" << s << "）" << endl;
}
void DSA()
{
	CalParameter();
	CalKey();
	cout << "输入你要加密的明文" << endl;
	cin >> M;
	Sha1(M,HM,q);//保存为HM的十进制，modq
	cout <<"hash值转化为十进制后（取mod）" << dec << HM << endl;
	CalSig();
}
void Pro()//证明
{
	long long temp = 0;
	exgcd(s, q, _s, temp);//s*_s+q*temp=gcd(k,q)=1;
	_s = _s > 0 ? _s : _s + q;//求s逆
	w=_s;
	u1 = (HM * w) % q;
	u2 = (r * w) % q;
	v = ((Pows(g, u1, p) * Pows(y, u2, p)) % p) % q;
	cout << "v=" << v << endl;
	cout << "验证成功" << endl;
}
int main()
{
    DSA();
	Pro();
    return 0;
}