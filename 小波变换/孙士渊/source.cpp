#include"stdio.h"
using namespace std;
void HaarCalulate(float *Record,float *Help,int len)
{
	for(int i(0);i<len/4||(i==0&&len==2);i++)
	{
		Help[i]=Record[2*i+1];
	}
	for(int i(0);i<len/2;i++)
	{
		Record[i]=(Record[2*i]+Record[2*i+1])/2;
	}
/*
	for(int i(0);i<len;i++)
	{
		printf("%lf ",Record[i]);
	}
	printf("\n");
*/
	for(int i(len-1);i>=int(len*3/4);i--)
	{
		Record[i]=(Record[2*i-len+1]-Record[2*i-len])/2;
	}
/*
	for(int i(0);i<len;i++)
	{
		printf("%lf ",Record[i]);
	}
	printf("\n");
*/
	for(int i(len/2);i<int(len*3/4)||(len==2&&i==1);i++)
	{
		Record[i]=Help[i-len/2]-Record[i-len/2];
	}
/*
	for(int i(0);i<len;i++)
	{
		printf("%lf ",Record[i]);
	}
	printf("\n");
*/
	len/=2;
	if(len>1)
		HaarCalulate(Record,Help,len);
	return;
}
int main(void)
{
	int L,len=1;
	scanf("%d",&L);
	for(int i(0);i<L;i++)
		len*=2;
	float *Record=new float[len];
	float *Help=new float[len/4];
	for(int i(0);i<len;i++)
		scanf("%f",&Record[i]);
	HaarCalulate(Record,Help,len);
	for(int i(0);i<len;i++)
	{
		printf("%.4f ",Record[i]);
	}
	delete[]Record;
	delete[]Help;
	return 0;
}
