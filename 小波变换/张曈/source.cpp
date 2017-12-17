#include <stdio.h>
int main()
{
	int l;
	long long int i,j,k;
	long long int t=1;
	scanf("%d",&l);
	for(i=0;i<l;i++) t*=2; 
	float *p=new float[t];
	float *q=new float[t];

	for(i=0;i<t;i++)
	{
		scanf("%f",&p[i]);
	}

	for(k=t;k>1;k/=2)
	{
		for(i=0;i<k/2;i++) q[i]=(p[2*i]+p[2*i+1])/2;
		for(i=k/2;i<k;i++) q[i]=-(p[2*(i-k/2)]-p[2*(i-k/2)+1])/2;
		for(i=0;i<t;i++) p[i]=q[i];
	}
	
	for(i=0;i<t;i++) printf("%f ",q[i]);
	delete []p;
	delete []q;
	return 0;
}
