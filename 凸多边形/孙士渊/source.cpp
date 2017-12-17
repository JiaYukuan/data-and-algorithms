#include "stdio.h"
using namespace std;
int main(void)
{
	int N,count(0),c;
	scanf("%d",&N);
	int *Record;
	double **table;
	for(int i(0);i<N;i++)			//第i个多边形
	{
		table=new double*[2];
		scanf("%d",&c);							//边长
		Record=new int[c];
		table[0]=new double[c];			//记录x点
		table[1]=new double[c];			//记录y点
		for(int j(0);j<c;j++)
		{
			//输入double必须用lf
			scanf("%lf%lf",&table[0][j],&table[1][j]);		//记录
		}	
		for(int j(0);j<c;j++)
		{
			if(((table[0][(j+1)%c]-table[0][j])*(table[1][j]-table[1][(j-1+c)%c])-(table[0][j]-table[0][(j-1+c)%c])*(table[1][(j+1)%c]-table[1][j]))<0)		//不满足条件
			{
				Record[count]=j;
				count++;
			}
		}
		if(count==0)
		{printf("%c\n",'y');
		}
		else
		{for(int s(0);s<count;s++)
			{printf("%d",Record[s]);
			printf(" ");
			}
		printf("\n");
		}
		delete[]Record;
		delete[]table[0];
		delete[]table[1];
		delete[]table;
		count=0;
	}
	return 0;
}
