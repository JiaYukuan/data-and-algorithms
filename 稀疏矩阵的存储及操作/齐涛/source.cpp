#include<stdio.h>
#include<iostream>

using namespace std;

class CrossLinkTable
{
private:
	struct Node
	{
		short data;
		short row;
		short column;
		Node* right;
		Node* down;
		Node(short d, short r, short c, Node* rig, Node* dow) :data(d), row(r), column(c), right(rig), down(dow) {}
	};

private:
	Node* head;  //top and left 
	short totalrow;
	short totalcolumn;

public:
	CrossLinkTable(short totalrow, short totalcolumn) :totalrow(totalrow), totalcolumn(totalcolumn), head(NULL) {}
	~CrossLinkTable() {};
	void insert(short &r, short &c, short &data);
	void printtranspose();
	void print_sumwithT();
	void print_dotwithT();
	void print();
};
/*
CrossLinkTable::~CrossLinkTable()
{
	Node* rowhead = head;
	Node* now;
	Node* next;
	for (; rowhead != NULL; )
	{
		for (now = rowhead->right; now != NULL;)
		{
			next = now->right;
			delete now;
			now = next;
		}
		now = rowhead;
		rowhead = rowhead->down;
		delete now;
	}
}*/

void CrossLinkTable::insert(short &r, short &c, short &data)
{
	if (head == NULL)
	{
		Node* newnode = new Node(data, r, c, NULL, NULL);
		Node* rownode = new Node((short)-11, r, (short)-1, newnode, NULL);
		Node* colnode = new Node(short(-11), short(-1), c, NULL, newnode);
		head = new Node(short(-11), -1, -1, colnode, rownode);
	}
	else
	{
		//先找到同一行左边的元素
		short rownext = head->down->row;
		short colnext = head->right->column;
		Node* pointnow = head;
		Node* leftnode = NULL;
		Node* upnode = NULL;
		while (rownext < r)
		{
			pointnow = pointnow->down;
			if (pointnow->down == NULL)
			{
				break;
			}
			rownext = pointnow->down->row;
		}
		if (pointnow->down == NULL || pointnow->down->row > r)
		{
			leftnode = new Node(-11, r, -1, NULL, pointnow->down);
			pointnow->down = leftnode;
		}
		else
		{
			pointnow = pointnow->down;
			for (; pointnow->right != NULL&& pointnow->right->column < c; pointnow = pointnow->right);
			leftnode = pointnow;
		}
		//现在的leftnode指向了和待加入元素同一行的左侧元素
		pointnow = head;
		while (colnext<c)
		{
			pointnow = pointnow->right;
			if (pointnow->right == NULL)
				break;
			colnext = pointnow->right->column;
		}
		if (pointnow->right == NULL || pointnow->right->column > c)
		{
			upnode = new Node(-11, -1, c, pointnow->right, NULL);
			pointnow->right = upnode;
		}
		else
		{
			pointnow = pointnow->right;
			for (; pointnow->down != NULL&&pointnow->down->row < r; pointnow = pointnow->down);
			upnode = pointnow;
		}
		//现在的upnode指向了和带加入元素同一列的上方元素
		Node* newnode = new Node(data, r, c, leftnode->right, upnode->down);
		leftnode->right = newnode;
		upnode->down = newnode;
	}
}

void CrossLinkTable::printtranspose()
{
	Node* colhead = head->right;
	Node* now = NULL;
	for (; colhead != NULL; colhead = colhead->right)
	{
		for (now = colhead->down; now != NULL; now = now->down)
			printf("%d %d %d \n", now->column, now->row, now->data);
	}

}

void CrossLinkTable::print_sumwithT()
{
	Node* rowhead = head->down;
	Node* colhead = head->right;
	Node* rownow = NULL;
	Node* colnow = NULL;
	short temp;
	for (; rowhead != NULL&&colhead != NULL;)
	{
		if (rowhead->row < colhead->column)
		{
			for (rownow = rowhead->right; rownow != NULL; rownow = rownow->right)
				printf("%d %d %d \n", rownow->row, rownow->column, rownow->data);
			rowhead = rowhead->down;
		}
		else if (rowhead->row > colhead->column)
		{
			for (colnow = colhead->down; colnow != NULL; colnow = colnow->down)
				printf("%d %d %d \n", colnow->column, colnow->row, colnow->data);
			colhead = colhead->right;
		}
		else
		{
			for (colnow = colhead->down, rownow = rowhead->right; colnow != NULL&&rownow != NULL;)
			{
				if (rownow != NULL&&colnow != NULL)
				{
					if (rownow->column< colnow->row)
					{
						printf("%d %d %d\n", rownow->row, rownow->column, rownow->data);
						rownow = rownow->right;
					}
					else if (rownow->column > colnow->row)
					{
						printf("%d %d %d\n", colnow->column, colnow->row, colnow->data);
						colnow = colnow->down;
					}
					else
					{
						temp = rownow->data + colnow->data;
						if (temp != 0)
							printf("%d %d %d\n", rownow->row, rownow->column, temp);
						rownow = rownow->right;
						colnow = colnow->down;
					}
				}
			}
			for (; rownow != NULL; rownow = rownow->right)
				printf("%d %d %d\n", rownow->row, rownow->column, rownow->data);
			for (; colnow != NULL; colnow = colnow->down)
				printf("%d %d %d\n", colnow->column, colnow->row, colnow->data);
			rowhead = rowhead->down;
			colhead = colhead->right;
		}
	}
	for (; rowhead != NULL; rowhead = rowhead->down)
	{
		for (rownow = rowhead->right; rownow != NULL; rownow = rownow->right)
			printf("%d %d %d", rownow->row, rownow->column, rownow->data);
	}
	for (; colhead != NULL; colhead = colhead->right)
		for (colnow = colhead->down; colnow != NULL; colnow = colnow->down)
			printf("%d %d %d", colnow->column, colnow->row, colnow->data);
}

void CrossLinkTable::print_dotwithT()
{
	Node* rowhead = head->down;
	Node* rowheadT = NULL;
	Node* now = NULL;
	Node* nowT = NULL;
	int sum;
	for (; rowhead != NULL; rowhead = rowhead->down)
	{
		for (rowheadT = head->down; rowheadT != NULL; rowheadT = rowheadT->down)
		{
			sum = 0;
			for (now = rowhead->right, nowT = rowheadT->right; now != NULL&&nowT != NULL;)
			{
				while (now != NULL&&nowT != NULL&&now->column != nowT->column)
				{
					if (now->column < nowT->column)
						now = now->right;
					else
						nowT = nowT->right;
				}
				if (now != NULL&& nowT != NULL)
				{
					sum += now->data*nowT->data;
					now = now->right;
					nowT = nowT->right;
				}
			}
			if (sum != 0)
				printf("%d %d %d\n", rowhead->row, rowheadT->row, sum);
		}
	}
}

void CrossLinkTable::print()
{
	Node* rowhead = head->down;
	Node* now = NULL;
	for (; rowhead != NULL; rowhead = rowhead->down)
	{
		for (now = rowhead->right; now != NULL; now = now->right)
			printf("%d %d %d \n", now->row, now->column, now->data);
	}
}


int main()
{
	int totalrow, totalcolumn;
	int total;
	//scanf("%d %d %d", &totalrow, &totalcolumn,&total);
	cin >> totalrow >> totalcolumn >> total;
	short row, column, data;
	//short srow, scolumn, sdata;
	CrossLinkTable mat(totalrow, totalcolumn);
	for (int i = 0; i < total; i++)
	{
		cin >> row >> column >> data;
		//scanf("%d %d %d", &row, &column, &data);
		if (data == 0)
			continue;
		mat.insert(row, column,data);
	}
	mat.printtranspose();
	mat.print_sumwithT();
	mat.print_dotwithT();
}
