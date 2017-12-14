//#include<iostream>
//using namespace std;
#include"stdio.h"
float trans(int x,int n,float f[]);
int squ(int );
int sum;

int main()
{
	int n,num=1;
	sum=1;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		sum*=2;
	float *f=new float [sum];
	for(int i=0;i<sum;i++)
		scanf("%f",&f[i]);

	for(int i=0;i<sum;i++)
		//cout<<trans(i,n,f)<<" ";
		printf("%f ",trans(i,n,f));
	//cout<<sum<<endl;
	delete [] f;
	return 0;
}
int squ(int m)
{
	int num=1;
	for(int i=0;i<m;i++)
		num*=2;
	return num;
}

float trans (int x,int n,float f[])
{
	if(n==0)return f[x];
	if(n==1) 
	{
		if(x<sum/2) return (trans(2*x,n-1,f)+trans(2*x+1,n-1,f))/2;
		else return (trans(2*(x-sum/2)+1,n-1,f)-trans(2*(x-sum/2),n-1,f)) / 2;
	}
//写出条件
	int num;
	num=sum/squ(n);
	if(x<num)
		return (trans(2*x,n-1,f)+trans(2*x+1,n-1,f)) / 2;
	else if(x<2*num) 
		return (trans(2*(x-num)+1,n-1,f)-trans(2*(x-num),n-1,f)) / 2;
	return trans(x,n-1,f);
}
