//#include<iostream>
#include"stdio.h"
#include<vector>
using namespace std;
int main(void)
{
	int N,i;
	scanf("%d",&N);
	vector<unsigned int>cir;
	int *c=new int[N];	
	int *a=new int[N];
	for(i=0;i<N;i++)
		scanf("%d",&c[i]);
	int f1=0,f2=1,k(0),f,t(0);			//t是开关按钮
	for(int i(0);k<N;i++)
	{
		if(!t)
		{
		f=f1;
		f1=f2;
		f2=f+f1;
		cir.push_back(f);
		}
		if(t==1||f2>=9973)
		{
			if(t==1)
			{
			f=f1;
			f1=f2;
			f2=f+f1;
			}
			f2%=9973;
			if(f1==0&&f2==1)			//可以弹出了
			{break;
			}
			t=1;						//开关打开
			cir.push_back(f1);
		}
		if(i==c[k])
		{
			a[k]=f;
			k++;
		}
	}
/*
	cout<<cir.size()<<endl;
	for(int i(0);i<cir.size();i++)
		cout<<cir[i]<<' ';
	system("pause");
*/
	if(k==N)
	{
		for(int i(0);i<N;i++)
			printf("%d\n",a[i]);
	}
	else
		for(int i(0);i<N;i++)
		{
			printf("%d\n",cir[c[i]%cir.size()]);
		}

	delete[]c;
	delete[]a;
	return 0;
}
/*

*/
