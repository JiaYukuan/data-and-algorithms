#include"stdio.h"

typedef struct LinkList
{
	int x,y,value,plus;
	LinkList *right;
}NODE,*PNODE;

struct CrossList
{
	PNODE* rhead;
	int row,col,num;
};

int Create(CrossList );
int Insert(CrossList,int,int,int,int,PNODE);
int Display(CrossList&);

PNODE Judge(CrossList,int,int);
int M_plus(CrossList& );
int Multiple(CrossList&);

int Delete(CrossList &);

int main()
{
	CrossList M;
	scanf("%d%d%d",&M.row,&M.col,&M.num);

	M.rhead=new PNODE [M.row];
	for(int i=0;i<M.row;i++)M.rhead[i]=NULL;
	
	Create(M);

	printf("\n");
	M_plus(M);

	printf("\n");
	Multiple(M);
	return 0;
}

int Create(CrossList M)
{
	
	int px,py,pv;
	for(int i=0;i<M.num;i++)
	{
		scanf("%d%d%d",&px,&py,&pv);
		if(pv==0)continue;
		Insert(M,px,py,pv,0,NULL);
	}
	return 0;
}

int Insert(CrossList M,int x,int y,int value,int plus,PNODE q)
{

	PNODE temp,temp1;
	PNODE p=new LinkList[1];
	p->x=x;
	p->y=y;
	p->value=value;
	p->plus=plus;
	
	p->right=q;

	if(M.rhead[x]==NULL)
		M.rhead[x]=p;
	else if(M.rhead[x]->y > y)
	{
		p->right=M.rhead[x];
		M.rhead[x]=p;
	}
	else 
	{
		temp=temp1=M.rhead[x];
		while(temp!=NULL&&y > temp->y)
		{
			temp1=temp;
			temp=temp->right;
		}
		p->right=temp;
		temp1->right=p;
	}
	
	return 0;
}

int Display(CrossList &M)			//输出矩阵本身
{
	int k;
	PNODE p;
	for(k=0;k<M.row;k++)
	{
		p=M.rhead[k];
		while(p!=NULL)
		{
			if(p->value+p->plus!=0)
				printf("%d %d %d\n",p->x,p->y,p->value+p->plus);
			p=p->right;
		}

	}
	return 0;
}

int M_plus(CrossList &M)
{
	PNODE rtemp,temp;
	int k;
	for(k=0;k<M.row;k++)
	{
		rtemp=M.rhead[k];			//rtemp M中指针
		while(rtemp!=NULL)			
		{
			temp=Judge(M,rtemp->y,rtemp->x);
			if(temp==NULL)
				Insert(M,rtemp->y,rtemp->x,0,rtemp->value,NULL);
			else 
			{
				temp->plus = rtemp->value;
			}
			rtemp=rtemp->right;
		}
	}
	for(k=0;k<M.row;k++)			//打印转置矩阵
	{
		temp=M.rhead[k];
		while(temp!=NULL)
		{
			if(temp->plus!=0)
				printf("%d %d %d\n",temp->x,temp->y,temp->plus);
			temp=temp->right;
		}
	}
	printf("\n");
	Display(M);
	
	return 0;
}

PNODE Judge(CrossList MT,int px,int py)			
{
	PNODE q;									
	q = MT.rhead[px];
	while (q!=NULL)
	{
		if (q->y==py) return q;							//返回MT中的指针
		else q = q->right;
	}
	return NULL;
}

int Multiple(CrossList& M)
{
	
	PNODE temp1,temp2;
	int value;

	for(int k=0;k<M.row;k++)
	{
		int i;
		for(i=0;i<M.row;i++)
		{
			temp2=M.rhead[i];
			value=0;
			while(temp2!=NULL)
			{
				temp1=M.rhead[k];
				
				while(temp1!=NULL)
				{
					if(temp2->y==temp1->y)
						value+=temp2->value*temp1->value;
					temp1=temp1->right;
				}
				temp2=temp2->right;
			}
			if(value!=0)printf("%d %d %d\n",k,i,value);
		}
	
	}
	return 0;
}
