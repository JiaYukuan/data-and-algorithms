#include"stdio.h"
using namespace std;
struct node
{
	int row;
	int col;
	int value;
	node*right;
	node*down;
};
int main()
{
	node*head;
	int N,num,r,c,elem;
	scanf("%d%d%d",&N,&N,&num);
	int count(0);
	head=new node;			//初始化head
	node*p=head;
	head->right=head;
	head->down=head;
	head->value=num;
	head->row=N;
	head->col=N;
	for(int i(0);i<N;i++)		//初始化稀疏表的列标
	{
		node*ColNode=new node;
		ColNode->down=ColNode;
		ColNode->row=-1;
		ColNode->col=i;
		p->right=ColNode;
		p=p->right;
	}
	p->right=head;
	p=head;
	for(int i(0);i<N;i++)		//初始化稀疏表的行标
	{
		node*RowNode=new node;
		RowNode->right=RowNode;
		p->down=RowNode;
		RowNode->row=i;
		RowNode->col=-1;
		p=p->down;
	}
	p->down=head;
	node*q,*temp,*pRight,*qDown;
	for(int i(0);i<num;i++)		//输入num个数字并记录在稀疏表中
	{
		p=head->down;
		q=head->right;
		scanf("%d%d%d",&r,&c,&elem);
		if(elem==0)
		{
			continue;
		}
		node*new_node=new node;
		new_node->col=c;
		new_node->row=r;
		new_node->value=elem;
		for(int j(0);j<r;j++)
		{
			p=p->down;
		}
		for(int j(0);j<c;j++)
		{
			q=q->right;
		}
		//先入行
		while(p->right->col<c&&p->right->col!=-1)
		{
			p=p->right;
		}
		temp=p->right;
		p->right=new_node;
		new_node->right=temp;
		//后入列
		while(q->down->row<r&&q->down->row!=-1)
		{
			q=q->down;
		}
		temp=q->down;
		q->down=new_node;
		new_node->down=temp;
	}
	p=head->right;
	do
	{
		q=p->right;
		while(p->down->row!=-1&&p->down->value!=0)
		{
			printf("%d %d %d\n",p->down->col,p->down->row,p->down->value);
			p=p->down;
		}
		p=q;
	}while(q!=head);
	p=head;
	q=head;
	while(1)
	{
		p=p->down;
		q=q->right;
		pRight=p->right;
		qDown=q->down;
		if(p==head)
			break;
		while(1)
		 {	
			if(pRight==p&&qDown==q)
				break;
			else if(pRight==p&&qDown!=q)
			{
				while(qDown!=q)
				{
					printf("%d %d %d\n",qDown->col,qDown->row,qDown->value);
					qDown=qDown->down;
				}
				break;
			}
			else if(pRight!=p&&qDown==q)
			{
				while(pRight!=p)
				{
					printf("%d %d %d\n",pRight->row,pRight->col,pRight->value);
					pRight=pRight->right;
				}
				break;
			}
			else
			{
				if(pRight->col<qDown->row)
				{
					printf("%d %d %d\n",pRight->row,pRight->col,pRight->value);
					pRight=pRight->right;
				}
				else if(pRight->col>qDown->row)
				{
					printf("%d %d %d\n",qDown->col,qDown->row,qDown->value);
					qDown=qDown->down;
				}
				else
				{
					if(pRight->value+qDown->value!=0)
					{
						printf("%d %d %d\n",pRight->row,pRight->col,pRight->value+qDown->value);
					}
					pRight=pRight->right;
					qDown=qDown->down;
				}				
			}
		}
	}
	count=0;
	node*qRight;
	p=head;
	while(1)							//head 的行循环
	{
		p=p->down;
		if(p==head)
			break;
		q=head;
		while(1)						//t.head的列循环
		{
			q=q->down;
			if(q==head)
				break;
			pRight=p->right;
			if(pRight==p)				//p行必然是0
			{
				break;
			}
			qRight=q->right;
			if(qRight==q)				//p行q列必然是0
			{
				continue;
			}
			while(pRight!=p&&qRight!=q)					//计算p行q列并存入result中
			{
				if(pRight->col<qRight->col)
				{
					pRight=pRight->right;
				}
				else if(pRight->col>qRight->col)
				{
					qRight=qRight->right;
				}
				else
				{
					count+=pRight->value*qRight->value;
					pRight=pRight->right;
					qRight=qRight->right;
				}
			}
			if(count!=0)
			{
				printf("%d %d %d\n",p->row,q->row,count);
				count=0;
			}
		}
	}
	return 0;
}
