#include <iostream>
#include"stdio.h"
#include<algorithm>
using namespace std;

typedef struct Anode
{
	int x,y;
	Anode *left,*right;
	Anode *up,*down;
	bool direction;			//0为纵向分割，1为横向分割
}Node,*PNode ;

struct node
{
	int x,y,length;
};

PNode insert(PNode &,int ,int ,bool);
int search(PNode ,node );
//void show(PNode&);
bool judge(node ,PNode);
bool xcompare(Node ,Node);
bool ycompare(Node ,Node);
//static PNode A=NULL;


int main()
{
	int m,n;
	scanf("%d%d",&m,&n);

	int x,y;
	int result=0;
	int* num=new int[n];
	PNode A=new Node [m]; 
	PNode root;
	node B;
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&A[i].x,&A[i].y);
		A[i].left=A[i].right=A[i].up=A[i].down=NULL;
		A[i].direction = -1;
	}
	root=insert(A,0,m-1,0);
	for(int i=0;i<n;i++)
	{
		scanf("%d%d%d",&B.x,&B.y,&B.length);
		num[i]=search(root,B);
	}
	
	for(int i=0;i<n;i++)
		printf("%d\n",num[i]);

	return 0;
}
/*void show(PNode &p)
{
	if(p==NULL)return ;
	else{
		cout<<p->x<<' '<<p->y<<endl;
		show(p->left);
		show(p->right);
		show(p->up);
		show(p->down);
	return ;
	}
}*/
PNode insert(PNode &p,int begin,int end,bool direction)
{
	if(begin>end){
		return NULL;
	}
	if(direction==0){												//第一次纵分flag=0
		sort(p+begin,p+end+1,xcompare);
	}
	else{
		sort(p+begin,p+end+1,ycompare);	
	}
	int mid=(begin+end)/2;
	PNode root;
	root=&p[mid];
	if(begin==end)
		return root;			//叶子结点
	else  root->direction=direction;


	if(direction==0)
	{
		root->left=insert(p,begin,mid-1,1);
		root->right=insert(p,mid+1,end,1);
	}
	else if(direction==1)
	{
		root->down=insert(p,begin,mid-1,0);
		root->up=insert(p,mid+1,end,0);
	}
	return root;
}
bool xcompare(Node a,Node b)
{
	return a.x < b.x;
}

bool ycompare(Node a,Node b)
{
	return a.y < b.y;
}

int search(PNode p,node B){
	int result=0;
	if(p == NULL){
		return 0;
	}
	if(p->up==NULL && p->down==NULL && p->left==NULL && p->right==NULL){
		return	judge(B,p) ? 1:0 ;		//叶子结点
	}                                            
	if(p->direction==0)
	{									//需要判断剪枝
		if(p->x < B.x+B.length && p->x > B.x-B.length)
		{
			result=judge(B,p) ?	(1+search(p->left,B)+search(p->right,B)):(search(p->left,B)+search(p->right,B));
		}
		else if(p->x-B.x>=B.length){
			result=judge(B,p) ? (1+search(p->left,B)):search(p->left,B);
		}
		else{
			result=judge(B,p) ?	(1+search(p->right,B)):search(p->right,B);
		}
	}
	else
	{													//direction==1
		if(p->y < B.y+B.length && p->y > B.y-B.length){
			result=judge(B,p) ?	(1+search(p->up,B)+search(p->down,B)):(search(p->up,B)+search(p->down,B));
		}
		else if(p->y-B.y>=B.length){
			result=judge(B,p) ? (1+search(p->down,B)):search(p->down,B);
		}
		else{
			result=judge(B,p) ? (1+search(p->up,B)):search(p->up,B);
		}
	}
	return result;
}

bool judge(node B,PNode p)
{
	if(p->x <= B.x+B.length && p->x >= B.x-B.length && 
		p->y <= B.y+B.length && p->y >= B.y-B.length)return true;
	else return false;
}
