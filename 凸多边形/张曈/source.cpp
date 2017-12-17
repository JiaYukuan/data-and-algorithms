#include <stdio.h>
#include <stdlib.h>
#include <cmath>
int main()
{
	int i,j,k;
	int t1,t2;				//记录叉乘用点的编号
	double x1,y1,x2,y2;		//记录叉乘用向量的坐标
	
	int num=0;				//记录多边形数量
	scanf("%d",&num);

	int edgenum=0;			//记录某多边形边的数量
	double* position;		//申请动态内存记录多边形点的位置
	int* whetherao;			//申请动态内存记录各个点是否为凹点
	int aonum;				//记录凹点数量
	for(i=0;i<num;i++)
	{
		scanf("%d",&edgenum);
		aonum=0;
		position=new double[2*edgenum];
		whetherao=new int [edgenum];
		for(j=0;j<2*edgenum;j++)
		{
			scanf("%lf",&position[j]);
		}

		//利用叉乘判断凹点
		for(j=0;j<edgenum;j++)
		{
			//先将是否为凹点置0
			whetherao[j]=0;		

			//求相邻点编号
			t1=j-1;
			t2=j+1;
			if(t1<0) t1+=edgenum;
			if(t2>edgenum-1)  t2-=edgenum;

			//求叉乘向量坐标
			x1=position[2*j]-position[2*t1];
			y1=position[2*j+1]-position[2*t1+1];
			x2=position[2*j]-position[2*t2];
			y2=position[2*j+1]-position[2*t2+1];

			if((x1*y2-x2*y1)<0) {whetherao[j]=1;aonum++;}
		}

		if(aonum==0) printf("y\n");
		else
		{
			for(j=0;j<edgenum;j++)
				if(whetherao[j]!=0)
				{
					printf("%d ",j);
				}
			printf("\n");
		}

		delete []position;
		delete []whetherao;
	}

	return 0;
}
