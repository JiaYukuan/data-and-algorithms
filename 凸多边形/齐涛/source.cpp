#include<iostream>
using namespace std;
struct tensor_dim1
{
	double x;
	double y;
};
inline double dot(tensor_dim1& n1, tensor_dim1& n2,tensor_dim1&n3)
{
	return n2.x*n3.y-n1.x*n3.y+n1.x*n2.y-n3.x*n2.y+n3.x*n1.y-n2.x*n1.y;
};

int main()
{
	int k;
	cin >> k;
	int m;
	tensor_dim1* v;
	tensor_dim1* node;
	bool flag = true;
	for (int p = 0; p < k; p++)
	{
		flag = true;
		cin >> m;
		node = new tensor_dim1[m];
		for (int i = 0; i < m; i++)
			cin >> node[i].x >> node[i].y;
		if (dot(node[m - 1], node[0], node[1]) > 0)
		{
			flag = false;
			cout << 0 << " ";
		}
		for (int i = 1; i < m - 1; i++)
		{
			if (dot(node[i - 1], node[i], node[i + 1]) > 0)
			{
				flag = false;
				cout << i << " ";
			}
		}
		if (dot(node[m - 2], node[m - 1], node[0])>0)
		{
			flag = false;
			cout << m - 1 << " ";
		}
		if (flag)
			cout << "y" << endl;
		else
			cout << endl;	
		delete[] node;
	}
}
