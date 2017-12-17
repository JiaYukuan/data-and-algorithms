#include<stdio.h>
using namespace std;
class output
{
public:
	bool istu;
	short num;
	output(bool b,short s):istu(b),num(s){}
	output(bool b):istu(true),num(0){}

};
class point
{
public:
	float x;
	float y;
};
float chacheng(point p1,point p2,point p3)
{
	float x1,y1,x2,y2;
	x1=p2.x-p1.x,y1=p2.y-p1.y;
	x2=p3.x-p2.x,y2=p3.y-p2.y;
	return (x1*y2-x2*y1);
}
class dbx
{
public:
	short k;
	point *p;
	dbx()
	{
		scanf("%d",&k);
		p=new point[k];
		for(int i=0;i<k;i++)
		{
			scanf("%f",&p[i].x);
			scanf("%f",&p[i].y);
		}
	}
	void print()
	{
		for(int i=0;i<k;i++)
			printf("(%f,%f) ",p[i].x,p[i].y);
	}
	~dbx()
	{
		delete p;
	}
	void istu(short *list)
	{
		int count =0;
		if(k==3) {list[0]=0;return;}
		else
		{
			int i=0;
			for(i=0;i<k;i++)
			{
				if(chacheng(p[i>0? i-1:i-1+k],p[i],p[i<k-1? i+1:i+1-k])>0) 
				{
					count++;
					list[count]=i;
				}
			}
			list[0]=count;
		}
	}
};
int main()
{
	int k;short i=0;short j=0;
	scanf("%d",&k);
	dbx *head;
	short **hea=new short* [k];
	for( i=0;i<k;i++)
	{
		head=new dbx;
		hea[i]=new short [(head->k)+1];
		head->istu(hea[i]);
		delete head;
	}
	for( i=0;i<k;i++)
	{
		if(hea[i][0]==0) printf("y\n");
		else
		{
			for(j=1;j<=hea[i][0];j++)
			{printf("%d ",hea[i][j]);}
			printf("\n");
		}
		delete hea[i];
	}
	delete hea;
	return 0;
}
