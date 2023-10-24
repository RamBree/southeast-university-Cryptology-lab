//使用long long和模平方算法
#include<iostream>
#include<string>
#include <stdlib.h>
#include <time.h>
using namespace std;
long long gcd(long long a, long long b)
{
	if (b == 0) return a;
	else return gcd(b, a % b);
	return 0;
}
void exgcd(long long a, long long b, long long& x, long long& y)
{
	if (b == 0) { x = 1; y = 0; return; }
	exgcd(b, a % b, x, y);
	long long tp = x;
	x = y; y = tp - a / b * y;
}//贝祖定理求ax+by=gcd（x，y）
long long p, q, n,e,d,fn;
long long Pows(long long m, long long e, long long mod)
{
	int a[1000],i=0;
	while (e) { a[i++] = e & 0x000001; e = e >> 1; }//快速幂
	long long b=m, result=1;
	for (int j = 0; j < i; j++)
	{
		result *= a[j]==0?1:b;
		result =result% mod;
		b *= b;
		b =b% mod;
	}
	return result%mod;
}
void Init()
{
	p = 3517;
	q = 7211;//通过isprim计算得到
	cout << "p=" << p << " q=" << q<<endl;
	n = p * q;
	fn = n - p - q + 1;
	cout<<"n=" << n << endl;
	srand(time(0));
	e = rand() % fn;//通过随机数给出
	while (gcd(e, fn)!=1)//互质
	{	
		e = rand() % (n - 2);
	}
	cout <<"e=" << e << " d=";
	long long bd = 0;
	exgcd(e, fn, d, bd);
	d = (d+fn)%fn;
	cout << d << endl;
}
void Code()
{
	string str = "ilikeyou";
	long long count[100];
	string strc = "";//暗文
	for (int i = 0; i < str.length(); i++)
	{
		long long  m = str[i]; //明文
		long long c = Pows(m, e, n);
		cout << "当前需加密字符：" << m << " 加密之后  加密字符：" << c << endl;
		count[i] = c;
	}
	string strm = "";
	for (int i = 0; i < str.length(); i++)
	{
		long long c = count[i]; //密文
		long long m = Pows(c, d, n);
		strm.append(1, char(m));
		cout << "解密之后的字符：" << m << endl;
	}
	cout << "明文：" << strm << endl;
	cout << "同态性验证：\n";
	long long res1=1,res2=1;
	cout << "明文:";
	for (int i = 0; i < str.length()-1; i++)
	{
		long long  m = str[i];
		cout << m << "*";
		res1 *= m;
		res1 %= n;
	}
	long long temp = str[str.length() - 1];
	cout << temp << "=" <<temp * res1 % n<<endl;
	cout << temp * res1 % n <<"加密后" << Pows(temp * res1 % n, e, n) << endl;
	cout << "密文:";
	for (int i = 0; i < str.length() - 1; i++)
	{
		long long  c = count[i];
		cout << c << "*";
		res2 *= c;
		res2 %= n;
	}
	cout << count[str.length() - 1] << "=" << count[str.length() - 1] * res2 % n << endl;
}
int main()
{
	Init();
	Code();
	return 0;
}