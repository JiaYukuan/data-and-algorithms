#include<stdio.h>
#include<math.h>
using namespace std;
class data
{
public:
	int zhi[2];
	data()
	{
		zhi[0]=zhi[1]=0;
	}
};
class node
{
public:
	int split;
	int axis;
	data * x;
	node * parent;
	node * left;
	node * right;
	node(int spli,int axi)
	{
		split=spli;
		axis=axi;
		parent=left=right=NULL;
		x=NULL;
	}
	node(node *par){left=right=NULL;parent=par;
		x=NULL;}
	node()
	{
		parent=left=right=NULL;
		x=NULL;
		split=0;
		axis=-1;
	}
};
class tree
{
public:
	node * root;
	tree()
	{
		root=NULL;
	}
	void jiaohuan(data *s1,data *s2)
	{
		int temp1;int temp2;
		temp1=s1->zhi[0],temp2=s1->zhi[1];
		s1->zhi[0]=s2->zhi[0],s1->zhi[1]=s2->zhi[1];
		s2->zhi[0]=temp1,s2->zhi[1]=temp2;
	}
	int part(data *dat,int start,int end,int axis)
	{
		int i=start-1;int j=end;
		int e=dat[end].zhi[axis];
		while(1)
		{
			while(dat[++i].zhi[axis]<e);
			while(e<dat[--j].zhi[axis]) if(j==start) break;
			if(i>=j) break;
			jiaohuan(dat+i,dat+j);
		}
		jiaohuan(dat+i,dat+end);
		return i;
	}
	void paixu(data *dat,int start ,int end,int axis)
	{
		int pos;
		if(end<=start) return;
		pos=part(dat,start,end,axis);
		paixu(dat,start,pos-1,axis);
		paixu(dat,pos+1,end,axis);
	}
	void cons(node **no,data *dat,int start,int end,int axis)
	{
		if(start==end) 
		{
			node *temp=new node(dat[end].zhi[axis],axis);
			if ((*no)==NULL) *no=temp;
			(*no)->x=new data;
			(*no)->x->zhi[0]=dat[end].zhi[0];
			(*no)->x->zhi[1]=dat[end].zhi[1];
			//printf("%d,%d\n",(*no)->x->zhi[0],(*no)->x->zhi[1]);
		}
		else
		{
			paixu(dat, start,end,axis);
			//for(int i=0;i<=3;i++) printf("%d,  %d\n",dat[i].zhi[0],dat[i].zhi[1]);
			int mid=(start+end)/2;
			//printf("%d!",mid);
			if((*no)==NULL) (*no)=new node(dat[mid].zhi[axis],axis),(*no)->left=new node((*no)),(*no)->right=new node((*no))/*,printf("%f\n",(*no)->split)*/;
			else {(*no)->split=dat[mid].zhi[axis],(*no)->axis=axis,(*no)->left=new node((*no)),(*no)->right=new node((*no))/*,printf("%f\n",(*no)->split)*/;}
			cons(&(*no)->left,dat,start,mid,1-axis);
			cons(&(*no)->right,dat,mid+1,end,1-axis);
		}
	}
	int search(node *roo,int xmid,int ymid,int range)
	{
		//int xmin=xmid-range,xmax=xmid+range,ymin=ymid-range,ymax=ymid+range;
		if(roo->x!=NULL)
		{
			if(abs(roo->x->zhi[0]-xmid)<=range&&abs(roo->x->zhi[1]-ymid)<=range) {/*printf("%d,%d\n",roo->x->zhi[0],roo->x->zhi[1]);*/return 1;}
			else return 0;
		}
		else
		{
			if(roo->axis==0)
			{
				if(abs(roo->split-xmid)<=range) {return search(roo->left,xmid,ymid,range)+search(roo->right,xmid,ymid,range);}
				else if(roo->split<(xmid-range))  {return search(roo->right,xmid,ymid,range);}
				else { return search(roo->left,xmid,ymid,range);}
			}
			else 
			{
				if(abs(roo->split-ymid)<=range)  {return search(roo->left,xmid,ymid,range)+search(roo->right,xmid,ymid,range);}
				else if(roo->split<(ymid-range))  {return search(roo->right,xmid,ymid,range);}
				else  {return search(roo->left,xmid,ymid,range);}
			}
		}
	}
};
int main()
{
	int n, m;tree kd;int i;
	int xmid,ymid,range;
	scanf("%d%d",&n,&m);
	data *dat=new data[n];
	for(i=0;i<n;i++)
	{
		scanf("%d%d",&dat[i].zhi[0],&dat[i].zhi[1]);
	}
	kd.cons(&kd.root,dat,0,n-1,0);
	for(i=0;i<m;i++)
	{
		scanf("%d%d%d",&xmid,&ymid,&range);
		printf("%d\n",kd.search(kd.root,xmid,ymid,range));
	}
	return 0;
}
