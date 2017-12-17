#include<stdio.h>
#include<math.h>
using namespace std;
float quzhi(float *fun,int weizhi,int l,int cishu)
{
	int cache=(int)pow(2.0,l-cishu);
	if(cishu!=0)
	{
		if(weizhi<cache) return (quzhi(fun,2*weizhi,l,cishu-1)+quzhi(fun,2*weizhi+1,l,cishu-1))/2;
		else if(weizhi<cache*2) return(quzhi(fun,2*(weizhi-cache)+1,l,cishu-1)-quzhi(fun,2*(weizhi-cache),l,cishu-1))/2;
		else return quzhi(fun,weizhi,l,cishu-1);
	}
	else return fun[weizhi];

}
void xiaobo(float *fun,int l,int cd)
{
	int i=0,j=0;int hold=cd/2;int temp;float *cache;
	cache=new float[cd];
	for(i=0;i<l;i++)
	{
		for(j=0;j<hold;j++)
		{
			temp=2*j;
			cache[j]=(fun[temp]+fun[temp+1])/2;
		}
		for(j=hold;j<2*hold;j++)
		{
			temp=2*(j-hold);
			cache[j]=(fun[temp+1]-fun[temp])/2;
		}
		for(j=0;j<hold;j++)
		{
			fun[j]=cache[j];
		}
		for(j=hold;j<2*hold;j++)
		{
			fun[j]=cache[j];
		}
		hold=hold/2;
	}
}


int main()
{
	int l,i;int cd;float *fun,*res;
	scanf("%d",&l);
	cd=(int)pow(2.0,l);
	fun=new float[cd];
	//printf("%d",cd);
	for(i=0;i<cd;i++)
	{
		scanf("%f",&fun[i]);
		//printf("%f",fun[i]);
	}
	//xiaobo(fun,l,cd);
	/*for(i=0;i<cd;i++)
	{
		//scanf("%f",&fun[i]);
		printf("%4f ",fun[i]);
	}*/
	for(i=0;i<cd;i++)
	{
		//scanf("%f",&fun[i]);
		printf("%4f ",quzhi(fun,i,l,l));
	}
	delete fun;
	return 0;
}
