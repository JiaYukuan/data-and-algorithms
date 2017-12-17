#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int x,y;
	int a;
	Node* rightpointer;
	Node* downpointer;
};

int main()
{
	int m,n,l;
	int x,y,z;		//用来在scanf中存储数据
	int i,j;
	Node* p=NULL,*r=NULL;	//用来存储要打印的点的地址
	Node q;			//用来完成排序
	int flag=0;		//判断是否循环结束
	int choice=0;	//用于switchcase
	scanf("%d %d %d",&m,&n,&l);
	if(m==0) return 0;

	Node* nodep=new Node[l];
	Node** rowheadp=new Node*[m];
	Node** rowlastp=new Node*[m];
	Node** columnheadp=new Node*[n];
	Node** columnlastp=new Node*[n];
	for(i=0;i<n;i++)
	{
		rowheadp[i]=NULL;
		columnheadp[i]=NULL;
	}
	
	//读入结点并为其排序
	for(i=0;i<l;i++)
	{
		scanf("%d %d %d",&x,&y,&z);
		nodep[i].x=x;
		nodep[i].y=y;
		nodep[i].a=z;
		nodep[i].rightpointer=NULL;
		nodep[i].downpointer=NULL;
	}
	for(i=0;i<l-1;i++)
	{
		for(j=i+1;j<l;j++)
		{
			if(nodep[i].x>nodep[j].x) {q=nodep[i];nodep[i]=nodep[j];nodep[j]=q;}
			else if(nodep[i].x==nodep[j].x&&nodep[i].y>nodep[j].y) {q=nodep[i];nodep[i]=nodep[j];nodep[j]=q;}
		}
	}

	//搭建十字链表
	for(i=0;i<l;i++)
	{
		x=nodep[i].x;
		y=nodep[i].y;
		if(rowheadp[x]==NULL) 
		{rowheadp[x]=&nodep[i];rowlastp[x]=&nodep[i];}
		else
		{
			rowlastp[x]->rightpointer=&nodep[i];
			rowlastp[x]=&nodep[i];
		}

		if(columnheadp[y]==NULL) {columnheadp[y]=&nodep[i];columnlastp[y]=&nodep[i];}
		else
		{
			columnlastp[y]->downpointer=&nodep[i];
			columnlastp[y]=&nodep[i];
		}
	}

	//打印转置矩阵
	p=columnheadp[0];
	i=0;
	while(1)
	{
		while(p==NULL) 
		{
			if(i<n-1) {i++;p=columnheadp[i];}
			else {flag=1;break;}
		}
		if(flag==1) break;
		if(p->a!=0) printf("%d %d %d\n",p->y,p->x,p->a);
		p=p->downpointer;
	}

	//打印两矩阵的和
	i=j=0;		//记录原矩阵及转置矩阵的坐标
	flag=0;
	p=columnheadp[0];
	r=rowheadp[0];
	while(r==NULL)
	{
		j++;
		if(j==m){flag=1;break;}
		r=rowheadp[j];
	}
	while(p==NULL&&flag!=1) 
	{
		i++;
		if(i==n){flag=1;break;}
		p=columnheadp[i];
	}
	while(1)
	{
		if(flag!=1)
		{
			if(r->x==p->y&&r->y==p->x) choice=0;
			else if(r->x<p->y||(r->y<p->x&&r->x==p->y)) choice=1;
			else if(r->x>p->y||(r->y>p->x&&r->x==p->y)) choice=2;
		
			switch(choice)
			{
			case 0:{
				if(p->a+r->a!=0)
					printf("%d %d %d\n",p->y,p->x,p->a+r->a);
				r=r->rightpointer;p=p->downpointer;
				break;
					}
			case 1:{
				if(r->a!=0)
					printf("%d %d %d\n",r->x,r->y,r->a);
				r=r->rightpointer;
				break;
					}
			case 2:{
				if(p->a!=0)
					printf("%d %d %d\n",p->y,p->x,p->a);
				p=p->downpointer;
				break;
					} 
			}
		}
		if(p==NULL&&flag!=1)
		{
			while(p==NULL&&i<n) 
			{
				i++;
				if(i==m) break;
				p=columnheadp[i];
			}
			if(i==m)
			{
				while(1)
				{
					while(r==NULL)
					{
						if(j<m-1) {r=rowheadp[j+1];j++;}
						else {flag=1;break;}
					}
					if(flag==1) break; 
					if(r->a!=0) printf("%d %d %d\n",r->x,r->y,r->a);
					r=r->rightpointer;
				}
			}
		}
		if(r==NULL&&flag!=1)
		{
			while(r==NULL&&j<n) 
			{
				j++;
				if(j==n) break;
				r=rowheadp[j];
			}
			if(j==n)
			{
				while(1)
				{
					while(p==NULL)
					{
						if(i<m-1) {p=columnheadp[i+1];i++;}
						else {flag=1;break;}
					}
					if(flag==1) break;
					if(p->a!=0){printf("%d %d %d\n",p->y,p->x,p->a);}
					p=p->downpointer;
				}
			}
		}
		if(flag==1) break;
	}
		
	//打印两矩阵的乘积
	p=rowheadp[0];
	r=rowheadp[0];
	int s=0;					//记录要输出的数
	flag=0;						//判断循环是否终止
	choice=0;
	for(i=0;i<m;i++)			//循环每一行
	{
		r=rowheadp[i];
		if(r==NULL) continue;
		for(j=0;j<m;j++)		//循环每一列
		{
			p=rowheadp[j];
			r=rowheadp[i];
			if(p==NULL) continue;
			s=0;
			while(1)
			{
				if(r->y==p->y) choice=0;
				else if(r->y>p->y) choice=1;
				else if(r->y<p->y) choice=2;
				switch(choice)
				{
				case 0:{
					s+=r->a*p->a;
					p=p->rightpointer;r=r->rightpointer;
					break;
						}
				case 1:{
					p=p->rightpointer;
					break;
					   }
				case 2:{
					r=r->rightpointer;
					break;
					   }
				}
				if(r==NULL||p==NULL) 
				{
					if(s!=0) printf("%d %d %d\n",i,j,s);
					break;
				}
			}
		}
	}
	delete []nodep;
	return 0;
}
