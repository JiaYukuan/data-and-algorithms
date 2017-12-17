#include "stdio.h"
#include <algorithm>
#include <cmath>
using namespace std;
struct node{
	node(){
		flag=-2;
		Lchild=NULL;
		Rchild=NULL;
	}
	int x;
	int y;
	int flag;
	node*Lchild;
	node*Rchild;
};
bool Xcompare(node a, node b){				//node按照x坐标升序排列
	return a.x<b.x?true:false;
}
bool Ycompare(node a, node b){				//node按照y坐标升序排列
	return a.y<b.y?true:false;
}
class KDtree{
	public:
		KDtree(){
			root=NULL;
		}
//		KDtree(const KDtree&);
		~KDtree(){
		}
		void set(node*Node,int left,int right,int flag){
			root=CreateTree(Node,left,right,flag);
		}
		node* CreateTree(node*,int,int,int);
		int Find(node*,int,int,int);
		node*Getroot(){
			return root;
		}
	private:
		node*root;
};
node* KDtree::CreateTree(node*Node,int left,int right,int flag){			//left right 是索引
	//排序
	if(left>right){
		return NULL;
	}
	if(flag==0){												//第一次纵分flag=0
		sort(Node+left,Node+right+1,Xcompare);
	}
	else{
		sort(Node+left,Node+right+1,Ycompare);	
	}
	int mid=(left+right)/2;
	node*new_node=new node;
	new_node->x=Node[mid].x;
	new_node->y=Node[mid].y;
	if(left==right){
		new_node->flag=-2;
		return new_node;
	}
	else{
		new_node->flag=flag;
	}
	new_node->Lchild=CreateTree(Node,left,mid-1,!flag);
	new_node->Rchild=CreateTree(Node,mid+1,right,!flag);
	return new_node;
}
int KDtree::Find(node*Node,int Xtar,int Ytar,int Dis){
	int count(0);
	if(Node==NULL){
		return 0;
	}
	if(Node->flag==-2){
		return	max(abs(Node->x-Xtar),abs(Node->y-Ytar))<=Dis?1:0; 
	}
	else if(Node->flag==0){									//需要判断剪枝
		if(abs(Node->x-Xtar)<Dis){
			count=max(abs(Node->x-Xtar),abs(Node->y-Ytar))<=Dis?(1+Find(Node->Lchild,Xtar,Ytar,Dis)+Find(Node->Rchild,Xtar,Ytar,Dis))
				:(Find(Node->Lchild,Xtar,Ytar,Dis)+Find(Node->Rchild,Xtar,Ytar,Dis));
		}
		else if(Node->x-Xtar>=Dis){
			count=max(abs(Node->x-Xtar),abs(Node->y-Ytar))<=Dis?(1+Find(Node->Lchild,Xtar,Ytar,Dis))
				:Find(Node->Lchild,Xtar,Ytar,Dis);
		}
		else{
			count=max(abs(Node->x-Xtar),abs(Node->y-Ytar))<=Dis?(1+Find(Node->Rchild,Xtar,Ytar,Dis))
				:Find(Node->Rchild,Xtar,Ytar,Dis);
		}
	}
	else{													//flag==1
		if(abs(Node->y-Ytar)<Dis){
			count=max(abs(Node->x-Xtar),abs(Node->y-Ytar))<=Dis?(1+Find(Node->Lchild,Xtar,Ytar,Dis)+Find(Node->Rchild,Xtar,Ytar,Dis))
				:(Find(Node->Lchild,Xtar,Ytar,Dis)+Find(Node->Rchild,Xtar,Ytar,Dis));
		}
		else if(Node->y-Ytar>=Dis){
			count=max(abs(Node->x-Xtar),abs(Node->y-Ytar))<=Dis?(1+Find(Node->Lchild,Xtar,Ytar,Dis))
				:Find(Node->Lchild,Xtar,Ytar,Dis);
		}
		else{
			count=max(abs(Node->x-Xtar),abs(Node->y-Ytar))<=Dis?(1+Find(Node->Rchild,Xtar,Ytar,Dis))
				:Find(Node->Rchild,Xtar,Ytar,Dis);
		}
	}
	return count;
}
int main(void)
{
	int N,M,i,x,y,d;
	scanf("%d%d",&N,&M);
	node*Node=new node[N];
	for(i=0;i<N;i++){
		scanf("%d%d",&Node[i].x,&Node[i].y);
	}
	KDtree mytree;
	mytree.set(Node,0,N-1,0);
	for(i=0;i<M;i++){
		scanf("%d%d%d",&x,&y,&d);
		printf("%d\n",mytree.Find(mytree.Getroot(),x,y,d));
	}
	delete[]Node;
	return 0;
}
