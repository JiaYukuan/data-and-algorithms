#include<stdio.h>
#define vec true
#define hoz false
#define PosInf 20000000
#define NegInf -1
/*kd树的结点类型 int+bool
在内部节点时，int用来记录分割直线 bool记录分割方向
在叶子结点时，int用来存一个指针，指针指向一个坐标，bool弃用*/

struct node
{
	int x;
	int y;
	node(int x = 0, int y = 0) :x(x), y(y) {};
	void operator = (const node& t) { x = t.x, y = t.y; }

};
struct range
{
	node ld; //左下角 闭区域
	node ru; //右上角 开区域
	range(int ldx, int ldy, int rux, int ruy) :ld(ldx, ldy), ru(rux, ruy) {}
	bool is_contained_by(const range& r);  //判断调用者是否被参数包含
	bool is_splited_with(const range& r);
	void operator=(const range &r) { ld = r.ld, ru = r.ru; }
};

void quickfindmiddle(node* p, int start, int end, bool direction, int aim);

struct Bnode
{
	long point;  //在内部节点存放range 在叶子节点存放数据点
	bool direction;
	int leaf_number;
	Bnode* lc;
	Bnode* rc;
	Bnode(long point, bool dierction, Bnode* lc, Bnode* rc) :point(point), direction(direction), lc(lc), rc(rc) {};
};

class KdTree
{
public:
	Bnode* root;
	int count;
	KdTree(node* p, int start, int end, bool direction);
	range R;
	Bnode* Create_KdTree(node* p, range* pr, int start, int end, bool direction);
	void update_leafnumber(Bnode* t);
	//void pre_tarvel(Bnode* _root);
	void search(Bnode* _root);
};

KdTree::KdTree(node * p, int start, int end, bool direction) :R(0, 0, 0, 0)
{
	count = 0;
	range* r = new range(NegInf, NegInf, PosInf, PosInf);
	root = Create_KdTree(p, r, start, end, direction);
	update_leafnumber(root);
}

Bnode* KdTree::Create_KdTree(node * p, range* rp, int start, int end, bool direction) //将[start，end）区域中的点进行二分
{
	if (start == end - 1) //到达递归基 叶子节点 存放指针数据
	{
		long c = (long)(&p[start]);
		Bnode* _root = new Bnode(c, true, NULL, NULL);
		return _root;
	}
	else
	{
		quickfindmiddle(p, start, end, direction, (start + end) / 2);
		Bnode* _root;
		range* lcp, *rcp;
		int middle = (start + end) / 2;
		if (direction == vec)  //分割线是垂直的
		{
			int line = p[middle].x;
			lcp = new range(rp->ld.x, rp->ld.y, line, rp->ru.y);
			rcp = new range(line, rp->ld.y, rp->ru.x, rp->ru.y);
		}
		else
		{
			int line = p[middle].y;
			lcp = new range(rp->ld.x, rp->ld.y, rp->ru.x, line);
			rcp = new range(rp->ld.x, line, rp->ru.x, rp->ru.y);

		}
		Bnode* lc = Create_KdTree(p, lcp, start, middle, !direction);
		Bnode* rc = Create_KdTree(p, rcp, middle, end, !direction);
		_root = new Bnode((long)rp, direction, lc, rc);
		return _root;
	}
}

void KdTree::update_leafnumber(Bnode * t)
{
	if (t->lc == NULL&&t->rc == NULL)
	{
		t->leaf_number = 1;
		return;
	}
	update_leafnumber(t->lc);
	update_leafnumber(t->rc);
	t->leaf_number = t->lc->leaf_number + t->rc->leaf_number;
}

/*void KdTree::pre_tarvel(Bnode * _root)
{
	if ((_root->lc == NULL&&_root->rc == NULL))
	{
		count++;
		node* p = (node*)(_root->point);
		cout << p->x << " " << p->y << "leaf" << _root->leaf_number << endl;
		return;
	}
	range* rp = (range*)_root->point;
	cout << "leaf" << _root->leaf_number << "||" << rp->ld.x << " " << rp->ld.y << ";" << rp->ru.x << " " << rp->ru.y << endl;
	if (_root->lc != NULL)
		pre_tarvel(_root->lc);
	if (_root->rc != NULL)
		pre_tarvel(_root->rc);

}*/

void KdTree::search(Bnode* _root)
{
	if (_root->lc == NULL)
	{
		node* p = (node*)(_root->point);
		if (p->x >= R.ld.x&&p->x <= R.ru.x&&p->y >= R.ld.y&&p->y <= R.ru.y)
			count++;
		return;
	}
	range* r = (range*)_root->point;
	if (r->is_splited_with(R))
		return;
	if (r->is_contained_by(R))
	{
		count += _root->leaf_number;
		return;
	}
	search(_root->lc);
	search(_root->rc);
}

void quickfindmiddle(node* p, int start, int end, bool direction, int aim)  //[start,end)左闭右开区间
{
	if (start >= end - 1)
		return;
	int pnow = start;
	int pend = end - 1;
	node temp;
	int middle = (start + end) / 2;
	temp.x = p[middle].x;
	temp.y = p[middle].y;
	p[middle].x = p[start].x;
	p[middle].y = p[start].y;
	p[start].x = temp.x;
	p[start].y = temp.y;
	if (direction == vec)
	{
		while (pnow<pend)
		{
			if (p[pnow].x >= p[pnow + 1].x)
			{
				temp.x = p[pnow].x;
				temp.y = p[pnow].y;
				p[pnow].x = p[pnow + 1].x;
				p[pnow].y = p[pnow + 1].y;
				p[pnow + 1].x = temp.x;
				p[pnow + 1].y = temp.y;
				pnow++;
			}
			else if (p[pnow].x < p[pnow + 1].x)
			{
				temp.x = p[pend].x;
				temp.y = p[pend].y;
				p[pend].x = p[pnow + 1].x;
				p[pend].y = p[pnow + 1].y;
				p[pnow + 1].x = temp.x;
				p[pnow + 1].y = temp.y;
				pend--;
			}
		}
		if (pnow == aim)  //已经基于中位数进行了排序
			return;
		if (pnow<aim)  //中位数在pnow的右面
			quickfindmiddle(p, pnow + 1, end, direction, aim);
		else  //中位数在pnow左面
			quickfindmiddle(p, start, pnow, direction, aim);
	}
	else if (direction == hoz)
	{
		while (pnow<pend)
		{
			if (p[pnow].y > p[pnow + 1].y)
			{
				temp.x = p[pnow].x;
				temp.y = p[pnow].y;
				p[pnow].x = p[pnow + 1].x;
				p[pnow].y = p[pnow + 1].y;
				p[pnow + 1].x = temp.x;
				p[pnow + 1].y = temp.y;
				pnow++;
			}
			else if (p[pnow].y <= p[pnow + 1].y)
			{
				temp.x = p[pend].x;
				temp.y = p[pend].y;
				p[pend].x = p[pnow + 1].x;
				p[pend].y = p[pnow + 1].y;
				p[pnow + 1].x = temp.x;
				p[pnow + 1].y = temp.y;
				pend--;
			}
		}//将第一个点移动到中间
		if (pnow == aim)  //已经基于中位数进行了排序
			return;
		if (pnow<aim)  //中位数在pnow的右面
			quickfindmiddle(p, pnow + 1, end, direction, aim);
		else  //中位数在pnow左面
			quickfindmiddle(p, start, pnow, direction, aim);
	}
}

int main()
{
	int m, n;
	scanf("%d %d", &m, &n);
	node* p = new node[m];
	for (int i = 0; i < m; i++)
		scanf("%d %d", &(p[i].x), &(p[i].y));
	KdTree t(p, 0, m, vec);
	//	t.pre_tarvel(t.root);
	range R(0, 0, 0, 0);
	int x, y, d;
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d %d", &x, &y, &d);
		R.ld.x = x - d;
		R.ld.y = y - d;
		R.ru.x = x + d;
		R.ru.y = y + d;
		t.R = R;
		t.search(t.root);
		printf("%d\n", t.count);
		t.count = 0;
	}
}

bool range::is_contained_by(const range & r)
{
	return ld.x >= r.ld.x&&ld.y >= r.ld.y&&ru.x <= r.ru.x&&ru.y <= r.ru.y;
}

bool range::is_splited_with(const range & r)
{
	return (ru.x <= r.ld.x) || (ld.x >r.ru.x)||(ru.y<r.ld.y)||(ld.y>r.ru.y);
}
