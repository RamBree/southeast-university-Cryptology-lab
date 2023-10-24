//����p=453371
//���������p-1����������p1��p2   pnum����2-��p-1��������֤a��p1��p2   pnum�η��Ƿ�==1
//�Ӷ�������б�ԭ��
//Xa Xb���ѡȡ �˹�ѡȡһ����ԭ�����м�����֤
//����������̳�RSA
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
ll Pows(ll x, ll n, ll mod)//������
{
	int a[1000], i = 0;
	while (n) { a[i++] = n & 0x000001; n = n >> 1; }//��
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
void PrimCal(ll n, ll *a, ll &num)//����Fai(p)�������ֽ�
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
	for (int i = 1; i < p; i++)//�������п��ܵĴ�
	{
		int tp = 0;
		while (tp<num)
		{
			if (Pows(i, P[tp], p) == 1) break;
			tp++;
		}
		if (tp == num&& Pows(i, p-1, p) == 1) {
			G[gnum++] = i;//��ԭ��
		}
	}
	cout << "��ԭ���У�";
	Show(G, gnum);
	cout << "ѡ��ԭ��" << endl;
	cin >> a;
}
void Init()
{
	p = 453371;
	cout << "p=" << p << endl;
	srand(time(0));
	Xa = rand() % p;
	Xb = rand() % p;
	cout << "��Կ:Xa=" << Xa << " Xb=" << Xb << endl;
	Eluer(p-1, E, ffp);
	cout<<"Fai(Fai(p))=" << ffp << endl;
	PrimCal(p-1, P, num);
	cout << "Fai(p)���������У�";
	Show(P, num);
	Gcal();//���㱾ԭ��
}
void Code()
{
	Ya = Pows(a, Xa, p);//��Կ����
	Yb = Pows(a, Xb, p);
	cout << "A�Ĺ�ԿYAΪ��" << Ya<<"    " << "B�Ĺ�ԿYBΪ��" << Yb << endl;
	Ka = Pows(Yb, Xa, p);
	Kb = Pows(Ya, Xb, p);
	cout << "A�յ��Ĺ�ԿKa=Yb��Xa�η�=" << Ka << endl;
	cout << "B�յ��Ĺ�ԿKb=Ya��Xb�η�=" << Kb << endl;
}
int main()
{
	Init();
	Code();
	return 0;
}
