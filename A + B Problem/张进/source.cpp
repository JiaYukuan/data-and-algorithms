#include<iostream>
#include<stdio.h>
using namespace std;

int main()
{
	int a[150];
	int lena=0;
	int lenb=0;
	int b[150];
	char x;
	int i=0;
	while(scanf("%c",&x))
	{
		if(x==' ')
		{
			break;
		}
		a[i]=x-'0';
		i++;
		lena++;
	}
	i=0;
	while(scanf("%c",&x))
	{
		if(x=='\n')
		{
			break;
		}
		b[i]=x-'0';
		i++;
		lenb++;
	}
	/*for(i=0;i<lena;i++)
	{
		printf("%c",a[i]);
	}
	printf("\n");
	for(i=0;i<lenb;i++)
	{
		printf("%c",b[i]);
	}*/
	int maxlen=lena>lenb? (lena+1):(lenb+1);
	
	/*for(i=0;i<maxlen;i++)
	{
		printf("%d",a[i]);
	}
	printf("\n");
	for(i=0;i<maxlen;i++)
	{
		printf("%d",b[i]);
	}*/
	int tempa,tempb;
	/*for(i=0;i<maxlen/2;i++)
	{
		tempa=a[i];
		a[i]=a[maxlen-i-1];
		a[maxlen-i-1]=tempa;
		tempb=b[i];
		b[i]=b[maxlen-i-1];
		b[maxlen-i-1]=tempb;
	}*/
	for(i=0;i<lena/2;i++)
	{
		tempa=a[i];
		a[i]=a[lena-i-1];
		a[lena-i-1]=tempa;
    }
	for(i=0;i<lenb/2;i++)
	{
		tempb=b[i];
		b[i]=b[lenb-i-1];
		b[lenb-i-1]=tempb;
    }
	for(i=lena;i<maxlen;i++)
		a[i]=0;
	for(i=lenb;i<maxlen;i++)
		b[i]=0;
	/*for(i=0;i<maxlen;i++)
	{
		printf("%d",a[i]);
	}
	printf("\n");
	for(i=0;i<maxlen;i++)
	{
		printf("%d",b[i]);
	}*/
	int c[151];
	int tempc=0;
	for(i=0;i<maxlen;i++)
	{
		c[i]=a[i]+b[i]+tempc;
		tempc=c[i]/10;
		c[i]=c[i]%10;
	}
	if(c[maxlen-1]==0)
	{
		for(i=maxlen-2;i>-1;i--)
			printf("%d",c[i]);
		
	}
	else
	{
		for(i=maxlen-1;i>-1;i--)
			printf("%d",c[i]);
	}
	return 0;
}
