#include <stdio.h>
#include <math.h>
using namespace std;
struct pointa
{
	int x,y;
};
struct pointb
{
	int x,y,d;
};
struct treenode
{
	int x,y,depth;
	treenode *left;
	treenode *right;
	treenode(int depth=0,int x=0,int y=0):left(NULL),right(NULL),x(x),y(y),depth(depth){};
};
int main()
{
	void buildtree(treenode *h,int s,int t,pointa *p);
	void traverse(treenode *p,int &num,int x1,int x2,int y1,int y2);
	void Qsort(pointa *p,int left,int right,int h);

	int m,n;
	int i;
	int x1,x2,y1,y2;
	int num;			//记录符合条件的点的数目
	scanf("%d %d",&n,&m);
	pointa *pa=new pointa[n];
	pointb *pb=new pointb[m];
	for(i=0;i<n;i++)
		scanf("%d %d",&pa[i].x,&pa[i].y);
	for(i=0;i<m;i++)
		scanf("%d %d %d",&pb[i].x,&pb[i].y,&pb[i].d);

	treenode *head=new treenode;

	buildtree(head,0,n-1,pa);
	for(i=0;i<m;i++)
	{
		num=0;
		x1=pb[i].x-pb[i].d;
		x2=pb[i].x+pb[i].d;
		y1=pb[i].y-pb[i].d;
		y2=pb[i].y+pb[i].d;
		
		traverse(head,num,x1,x2,y1,y2);
		printf("%d\n",num);
	}

	return 0;
}

void Qsort(pointa *p,int left,int right,int h)
{  
    int l = left,r=right;  
	pointa q;
    if(l>=r) return ;
	switch (h%2)
	{
	case 0:
		{
			int key = p[l].x;  
			while(l<r)
			{  
				while(p[r].x>=key && l<r) r--;//找到当前右边第一个比key小的值  
				q=p[l];
				p[l]= p[r];
				p[r]=q;
				while(p[l].x<=key && l<r) l++;//找到当前左边第一个比key大的值  
				q=p[l];
				p[l]= p[r];
				p[r]=q;  
		    }  
			p[l].x = key;//将key值赋值给临界点l||r  
			//当前的l左边都比key小，右边都比key大  只需要更新[left,l-1]和[l+1,right]  
			Qsort(p,left,l-1,h);  
			Qsort(p,l+1,right,h);  
			break;
		}
	case 1:
		{
			int key = p[l].y;  
			while(l<r)
			{  
				while(p[r].y>=key && l<r) r--;//找到当前右边第一个比key小的值  
				q=p[l];
				p[l]= p[r];
				p[r]=q; 
				while(p[l].y<=key && l<r) l++;//找到当前左边第一个比key大的值  
				q=p[l];
				p[l]= p[r];
				p[r]=q;
		    }  
			p[l].y = key;//将key值赋值给临界点l||r  
			//当前的l左边都比key小，右边都比key大  只需要更新[left,l-1]和[l+1,right]  
			Qsort(p,left,l-1,h);  
			Qsort(p,l+1,right,h);  
			break;
		}
	}    
}  

void buildtree(treenode *h,int s,int t,pointa *p)	//传数组的起始位置和终止位置
{
	int i,j,a;
	int middle=(s+t)/2;								//记录中位数
	if(s==t)										//传过来数组结点数目为1，应为叶子结点
	{
		h->x=p[s].x;
		h->y=p[s].y;
		return;
	}
	else
	{
		h->left=new treenode(h->depth+1);
		h->right=new treenode(h->depth+1);
		pointa q;				//用来排序
		switch(h->depth%2)
		{
		case 0:					//h为偶数，则该层用来分x
			{
				/*for(i=s;i<=middle;i++)	//为x排序
				{
					a=i;
					for(j=i+1;j<=t;j++)
					{
						if(p[a].x>p[j].x)
						{
							a=j;
						}
					}
					if(a!=i)
					{
						q=p[i];
						p[i]=p[a];
						p[a]=q;
					}
				}*/
				Qsort(p,s,t,h->depth);
				h->x=p[middle].x;
				buildtree(h->left,s,middle,p);
				buildtree(h->right,middle+1,t,p);
				break;
			}
		case 1:					//h为奇数，则该层用来分y
			{
				/*for(i=s;i<=middle;i++)	//为y排序
				{
					a=i;
					for(j=i+1;j<=t;j++)
					{
						if(p[a].y>p[j].y)
						{
							a=j;
						}
					}
					if(a!=i)
					{
						q=p[i];
						p[i]=p[a];
						p[a]=q;
					}
				}*/
				Qsort(p,s,t,h->depth);
				h->y=p[middle].y;
				buildtree(h->left,s,middle,p);
				buildtree(h->right,middle+1,t,p);
				break;
			}
		}
	}
	return;
}

void traverse(treenode *p,int &num,int x1,int x2,int y1,int y2)					//遍历树
{
	if(p->left==NULL) 
	{
		if((p->x>=x1)&&(p->x<=x2)&&(p->y>=y1)&&(p->y<=y2)) num++;	//若为叶子结点，则符合要求，num++
	}
	else
	{
		switch(p->depth%2)						//判断结点的层数，若为偶数则判断x，奇数则y
		{
		case 0:
			{
				if(p->x>=x2)
				{
					traverse(p->left,num,x1,x2,y1,y2);
				}
				else if(p->x<x1)
				{
					traverse(p->right,num,x1,x2,y1,y2);
				}
				else
				{
					traverse(p->left,num,x1,x2,y1,y2);
					traverse(p->right,num,x1,x2,y1,y2);
				}
				break;
			}
		case 1:
			{
				if(p->y>=y2)
				{
					traverse(p->left,num,x1,x2,y1,y2);
				}
				else if(p->y<y1)
				{
					traverse(p->right,num,x1,x2,y1,y2);
				}
				else
				{
					traverse(p->left,num,x1,x2,y1,y2);
					traverse(p->right,num,x1,x2,y1,y2);
				}
				break;
			}
		}
	}
	return;
}
