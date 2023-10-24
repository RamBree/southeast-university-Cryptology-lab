#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
int Isprim(unsigned long long n)
{
	for (unsigned long long i = 2; i < sqrt(n); i++)
	{
		if (n % i == 0) return 0;
	}
	return 1;
}
int main()
{
	unsigned long long p[100];
	unsigned long long i;
	int flag = 0, flag1;
	cout << "输入一个起点：";
	cin >> i;
	cout << "输入你想要的个数：";
	cin >> flag1;
	while (flag<flag1)
	{
		if (Isprim(i)==1)
		{
			p[flag++] = i;
		}
		i += 2;
	}
	fstream out;
	out.open("a.txt" , ios::app);
	for(int i=0;i<flag1;i++)
	  out << " " << p[i];
	out << endl;
	out.close();
	return 0;
}