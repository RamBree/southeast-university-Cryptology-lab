//素数p=453371
//先求出所有p-1的素数因子p1，p2   pnum，从2-（p-1）依次验证a的p1，p2   pnum次方是否==1
//从而求出所有本原根
//Xa Xb随机选取 人工选取一个本原根进行加密验证
//快速幂运算继承RSA
#include<iostream>
#include<cmath>
#include<time.h>
#include<algorithm>
#include<stdlib.h>
using namespace std;
typedef long long  ll;
ll A,B;
ll Xa, Xb,Ya,Yb,Ka,Kb;
ll a,p;
ll E[1000000], num = 0;
ll G[1000000], gnum = 0;
ll P[1000000], ffp;
ll Pows(ll x, ll n, ll mod)//快速幂
{
	int a[1000], i = 0;
	while (n) { a[i++] = n & 0x000001; n = n >> 1; }//求
	ll b = x, result = 1;
	for (int j = 0; j < i; j++)
	{
		result *= a[j] == 0 ? 1 : b;
		result = result % mod;
		b *= b;
		b = b % mod;
	}
	return result % mod;
}
void PrimCal(ll n, ll *a, ll &num)//计算Fai(p)的素数分解
{
	int i = 2,flag=0;
	while (n!=1)
	{
		if (n % i==0)
		{
			if (!flag) { *(a + num++) = i; flag = 1; }
			n /= i;
		}
		else
		{
			i++;
			flag = 0;
		}
	}
}
ll gcd(ll a, ll b)
{
	if (b == 0) return a;
	else return gcd(b, a % b);
}
void Eluer(ll p, ll *a, ll& num)
{
	for (int i = 1; i <p; i++)
	{
		if (gcd(p,i)==1) *(a + num++) = i;
	}
}
void Show(ll a[], ll n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i]<<" ";
	}
	cout << endl;
}
void Gcal()
{
	for (int i = 1; i < p; i++)//遍历所有可能的答案
	{
		int tp = 0;
		while (tp<num)
		{
			if (Pows(i, P[tp], p) == 1) break;
			tp++;
		}
		if (tp == num&& Pows(i, p-1, p) == 1) {
			G[gnum++] = i;//本原根
		}
	}
	cout << "本原根有：";
	Show(G, gnum);
	cout << "选择本原根" << endl;
	cin >> a;
}
void Init()
{
	p = 453371;
	cout << "p=" << p << endl;
	srand(time(0));
	Xa = rand() % p;
	Xb = rand() % p;
	cout << "密钥:Xa=" << Xa << " Xb=" << Xb << endl;
	Eluer(p-1, E, ffp);
	cout<<"Fai(Fai(p))=" << ffp << endl;
	PrimCal(p-1, P, num);
	cout << "Fai(p)的素因子有：";
	Show(P, num);
	Gcal();//计算本原根
}
void Code()
{
	Ya = Pows(a, Xa, p);//公钥计算
	Yb = Pows(a, Xb, p);
	cout << "A的公钥YA为：" << Ya<<"    " << "B的公钥YB为：" << Yb << endl;
	Ka = Pows(Yb, Xa, p);
	Kb = Pows(Ya, Xb, p);
	cout << "A收到的公钥Ka=Yb的Xa次方=" << Ka << endl;
	cout << "B收到的公钥Kb=Ya的Xb次方=" << Kb << endl;
}
int main()
{
	Init();
	Code();
	return 0;
}
