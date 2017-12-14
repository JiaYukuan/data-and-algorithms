#include"stdio.h"
#include"memory.h"

struct node
{
	float x;
	float y;
};

int main()
{
	int k, num;
	
	scanf("%d",&k);

	bool **judge = new bool*[k];
	short *count=new short [k];
	for(int i=0;i<k;i++)
	{
		
		scanf("%d",&num);
		node *Node=new node [num];
		count[i]=0;
		bool *mem =new bool [num];
		for(int j=0;j<num;j++)				//输入点列
			scanf("%f%f",&Node[j].x,&Node[j].y);
		memset(mem, 0, num);
		for(int j=0;j<num;j++)
		{
			float Val;
			Val=(Node[(j+2)%num].x-Node[(j+1)%num].x)*(Node[(j+1)%num].y-Node[j].y)-
				(Node[(j+2)%num].y-Node[(j+1)%num].y)*(Node[(j+1)%num].x-Node[j].x);
			if(Val<0)
				{mem[(j+1)%num]=1;count[i]++;}
			
		}
		judge[i] = new bool[num];

		for(int j=0;j<num;j++)
			judge[i][j] = mem[j];
		delete[] mem;
		delete [] Node;
	}

	for(int i=0;i<k;i++)
	{
		if(count[i]==0)
			{printf("%c\n",'y');continue;}
		for(int j=0;j<num;j++)
			if(judge[i][j]==1)
				printf("%d ",j);
			printf("\n");
	}

	for (int i = 0; i < k; i++)				//循环删除内存
			delete[] judge[i];
	delete[] judge;							//删除一阶
	delete[] count;
	return 0;
}
