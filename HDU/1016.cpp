#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;
bool b[21]={0};
int total=0,a[21]={0};
int search(int);                           //���ݹ���
int print();                               //�������
bool pd(int,int);                          //�ж�����
int n,cmt;
int main()
{
	while(~ scanf("%d",&n))
	{
		printf("Case %d:\n",++ cmt);
		b[1] = a[1] = 1;
    	search(2);
    	printf("\n");
	}
	return 0;
}
int search(int t)
{
    int i;
    for (i = 2;i <= n;i ++)                     //��20������ѡ
    	if (pd(a[t-1],i)&&(!b[i]))            //�ж���ǰһ�����Ƿ񹹳������������Ƿ����
      	{
	        a[t] = i;
	        b[i] = 1;
	        if (t == n) { if (pd(a[n],a[1])) print();}
	            else search(t+1);
	        b[i] = 0;
		}
}
int print()
{
	printf("1");
	for(int j = 2;j <= n;j ++)
		printf(" %d",a[j]);
	printf("\n");
}
bool pd(int x,int y)
{
    int k = 2,i = x + y;
    while (k <= sqrt(i) && i % k != 0) k ++;
    if (k > sqrt(i)) return 1;
       else return 0;
}

