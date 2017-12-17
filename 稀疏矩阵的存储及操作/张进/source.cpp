#include<stdio.h>
using namespace std;
class node
{
public:
	int heng;
	int zong;
	int zhi;
	node *sp;
	node *sz;
	node()
	{
		sp=sz=NULL;
	}
	node(int m,int n,int p)
	{
		heng=m;zong=n;zhi=p;
		sp=sz=NULL;
	}
};
class juzhen
{
public:
	int m;
	int n;
	node *hang;
	node *lie;
	juzhen(int m,int n):m(m),n(n)
	{
		hang=new node[m];
		lie=new node[n];
	}
	void insert(int m,int n,int p)
	{
		if(p!=0)
		{
			node *i;node *temp=new node(m,n,p);
		for(i=&hang[m];i->sp!=NULL;i=i->sp)
		{
			if(i->sp->zong>n){temp->sp=i->sp;i->sp=temp;break;}
		}
		if(i->sp==NULL){i->sp=temp;}
		for(i=&lie[n];i->sz!=NULL;i=i->sz)
		{
			if(i->sz->heng>m){temp->sz=i->sz;i->sz=temp;break;}
		}
		if(i->sz==NULL){i->sz=temp;}
		}
		
	}
	void print()
	{
		int j=0;
		for(j=0;j<m;j++)
		{
			node *i=hang[j].sp;
			while(i!=NULL)
			{
				printf("%d %d %d\n",i->heng,i->zong,i->zhi);
				i=i->sp;
			}
		}
		
	}
	void print_transpose()
	{
		int j=0;
		for(j=0;j<n;j++)
		{
			node *i=lie[j].sz;
			while(i!=NULL)
			{
				printf("%d %d %d\n",i->zong,i->heng,i->zhi);
				i=i->sz;
			}
		}
	}
	void print_sum(juzhen t)
	{
		int i=0;node *t1;node *t2;
		for(i=0;i<m;i++)
		{
			t1=hang[i].sp;t2=t.hang[i].sp;
			while(t1!=NULL&&t2!=NULL)
			{
				if(t1->zong<t2->zong) {printf("%d %d %d\n",t1->heng,t1->zong,t1->zhi);t1=t1->sp;}
				else if(t1->zong>t2->zong) {printf("%d %d %d\n",t2->heng,t2->zong,t2->zhi);t2=t2->sp;}
				else {if(t1->zhi+t2->zhi!=0) printf("%d %d %d\n",t1->heng,t1->zong,t1->zhi+t2->zhi);t1=t1->sp;t2=t2->sp;}
			}
			if(t1!=NULL) 
			{
				while(t1!=NULL)
				{
					printf("%d %d %d\n",t1->heng,t1->zong,t1->zhi);t1=t1->sp;
				}
			}
			else if(t2!=NULL)
			{
				while(t2!=NULL)
				{
					printf("%d %d %d\n",t2->heng,t2->zong,t2->zhi);t2=t2->sp;
				}
			}
		}
	}
	void print_mul(juzhen t)
	{
		int i=0,j=0,temp=0;node *t1;node *t2;
		for(i=0;i<m;i++)
			for(j=0;j<m;j++)
			{
				temp=0;
				t1=hang[i].sp;t2=t.lie[j].sz;
				while(t1!=NULL&&t2!=NULL)
				{
					if(t1->zong<t2->heng) {t1=t1->sp;}
				else if(t1->zong>t2->heng) {t2=t2->sz;}
				else {temp+=(t1->zhi)*(t2->zhi);t1=t1->sp;t2=t2->sz;}
				
				}
				if(temp!=0) printf("%d %d %d\n",i,j,temp);
			}
	}
};


int main()
{
	int m, n, p;int cishu;int i=0;
	scanf("%d%d%d",&m,&n,&cishu);
	juzhen jz(m,n);
	juzhen trans(n,m);
	for(i=0;i<cishu;i++)
	{
		scanf("%d%d%d",&m,&n,&p);
		jz.insert(m,n,p);
		trans.insert(n,m,p);
	}
	//jz.print();
	trans.print();
	jz.print_sum(trans);
	jz.print_mul(trans);
	return 0;
}
