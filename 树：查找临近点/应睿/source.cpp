#include <stdio.h>
#include <stack>
#include <vector>
using namespace std;

int sum = 0;

struct NodeX
{
	vector<int> yTree; // Stored in a vector and use BST later
	NodeX* left = NULL;
	NodeX* right = NULL;
	int x;
	int y;
};

// Recurrence quick sort
// Use std::stack to simulate the recursion process
void quickSort(int(*a)[2], int pos, int begin, int end) {
	if (begin >= end) return;

	stack<pair<int, int>> sortStack;

	sortStack.push(make_pair(begin, end));

	while (!sortStack.empty()) {
		pair<int, int> range = sortStack.top();
		sortStack.pop();

		if (range.first >= range.second) {
			continue;
		}
		int left = range.first;
		int right = range.second - 1;
		int pivot = a[range.second][pos];

		while (left < right) {
			while (left < right && a[left][pos] < pivot) {
				left++;
			}
			while (left < right && a[right][pos] >= pivot) {
				right--;
			}
			swap(a[left], a[right]);
		}

		if (a[range.second][pos] <= a[left][pos]) {
			swap(a[left], a[range.second]);
		}
		else {
			left++;
		}

		if (left > range.first) {
			sortStack.push(make_pair(range.first, left - 1));
		}
		if (right < range.second) {
			sortStack.push(make_pair(left + 1, range.second));
		}
	}
}

void quickSort2(vector<int>& a, int begin, int end) {
	if (begin >= end) return;

	stack<pair<int, int>> sortStack;

	sortStack.push(make_pair(begin, end));

	while (!sortStack.empty()) {
		pair<int, int> range = sortStack.top();
		sortStack.pop();

		if (range.first >= range.second) {
			continue;
		}
		int left = range.first;
		int right = range.second - 1;
		int pivot = a[range.second];

		while (left < right) {
			while (left < right && a[left] < pivot) {
				left++;
			}
			while (left < right && a[right] >= pivot) {
				right--;
			}
			swap(a[left], a[right]);
		}

		if (a[range.second] <= a[left]) {
			swap(a[left], a[range.second]);
		}
		else {
			left++;
		}

		if (left > range.first) {
			sortStack.push(make_pair(range.first, left - 1));
		}
		if (right < range.second) {
			sortStack.push(make_pair(left + 1, range.second));
		}
	}
}

// Store the associated y tree in a sorted vector 
vector<int> buildBinaryTreeY(int(*a)[2], int begin, int end) {
	vector<int> b;
	for (int i = 0; i < end - begin + 1; ++i) {
		b.push_back(a[i + begin][1]);
	}
	quickSort2(b, 0, end - begin);
	return b;
}

NodeX* buildRangeTree2D(int(*a)[2], int begin, int end) {
	if (begin > end) return NULL;

	// Build the associated y tree
	vector<int> yTree = buildBinaryTreeY(a, begin, end);
	NodeX* nodeX = NULL;

	// When the recursion ends
	if (begin == end) {
		nodeX = new NodeX;
		nodeX->x = a[begin][0];
		nodeX->y = a[begin][1];
		nodeX->left = NULL;
		nodeX->right = NULL;
		nodeX->yTree = yTree;
	}
	// Bisection method
	else {
		int mid = begin + (end - begin) / 2;
		nodeX = new NodeX;
		nodeX->x = a[mid][0];
		nodeX->y = a[mid][1];
		nodeX->yTree = yTree;
		nodeX->left = buildRangeTree2D(a, begin, mid);
		nodeX->right = buildRangeTree2D(a, mid + 1, end);
	}

	// Return the root node
	return nodeX;
}

// Find the node where the paths for the leftmost and the rightmost split
NodeX* findSplitNodeX(NodeX* nodeX, const int& minX, const int& maxX) {
	if (nodeX == NULL) return NULL;

	NodeX* node = nodeX;
	// Find the first node in the given range
	// It's a pretreatment
	while (node != NULL && (node->x > maxX || node->x < minX)) {
		// When the node is too right
		if (node->x > maxX) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}

	if (node == NULL) return NULL;

	// Find the leftmost node the search path will go into
	NodeX* nodeLeft = node->left;
	while (true)
	{
		if (nodeLeft != NULL) {
			if (nodeLeft->x < minX) {
				if (nodeLeft->right == NULL) {
					break;
				}
				else {
					nodeLeft = nodeLeft->right;
				}
			}
			else {
				if (nodeLeft->left == NULL) {
					break;
				}
				else {
					nodeLeft = nodeLeft->left;
				}
			}
		}
	}

	// Find the rightmost node the search path will go into
	NodeX* nodeRight = node->right;
	while (true)
	{
		if (nodeRight != NULL) {
			if (nodeRight->x > maxX) {
				if (nodeRight->left == NULL) {
					break;
				}
				else {
					nodeRight = nodeRight->left;
				}
			}
			else {
				if (nodeRight->right == NULL) {
					break;
				}
				else {
					nodeRight = nodeRight->right;
				}
			}
		}
	}

	// Continue to locate the node which is between the leftmost and rightmost nodes
	while (node != NULL && (node->x > nodeRight->x || node->x < nodeLeft->x)) {
		if (node->x > nodeRight->x) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}

	return node;
}

void searchRangeTreeY(vector<int>& a, int start, int end, const int& min, const int& max) {
	// When the recursion ends
	if (start == end) {
		if (a[start] >= min && a[start] <= max) sum++;
	}

	if (start < end) {
		int mid = start + (end - start) / 2;

		if (a[mid] < min) {
			searchRangeTreeY(a, mid + 1, end, min, max);
		}
		else if (a[mid] > max) {
			searchRangeTreeY(a, start, mid - 1, min, max);
		}
		else {
			searchRangeTreeY(a, start, mid - 1, min, max);
			sum++;
			searchRangeTreeY(a, mid + 1, end, min, max);
		}
	}
}

void searchRangeTree2D(NodeX* xTree, const int& minX, const int& maxX, const int& minY, const int& maxY) {
	NodeX* splitNodeX = findSplitNodeX(xTree, minX, maxX);

	if (splitNodeX == NULL) return;

	// If the split node is a leaf, check if it's in the range
	if (splitNodeX->left == NULL && splitNodeX->right == NULL) {
		if (splitNodeX->y >= minY && splitNodeX->y <= maxY) {
			sum++;
		}
	}
	else {
		// Search on the left
		NodeX* node = splitNodeX->left;
		while (!(node->left == NULL && node->right == NULL)) {
			if (node->x >= minX) {
				// Only go on searching the y tree for the right node
				searchRangeTreeY(node->right->yTree, 0, node->right->yTree.size() - 1, minY, maxY);
				node = node->left;
			}
			else {
				node = node->right;
			}
		}
		// Check whether the last node is in the range
		if (node->x >= minX && node->x <= maxX && node->y >= minY && node->y <= maxY) {
			sum++;
		}

		// Search on the right
		node = splitNodeX->right;
		while (!(node->left == NULL && node->right == NULL)) {
			if (node->x <= maxX) {
				// Only go on searching the y tree for the left node
				searchRangeTreeY(node->left->yTree, 0, node->left->yTree.size() - 1, minY, maxY);
				node = node->right;
			}
			else {
				node = node->left;
			}
		}
		// Check whether the last node is in the range
		if (node->x >= minX && node->x <= maxX && node->y >= minY && node->y <= maxY) {
			sum++;
		}
	}
}

int main() {
	int m, n;
	scanf("%d %d", &n, &m);

	int(*a)[2] = new int[n][2];

	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &a[i][0], &a[i][1]);
	}

	// Pre-sort a on X
	quickSort(a, 0, 0, n - 1);
	NodeX* rangeTree = buildRangeTree2D(a, 0, n - 1);

	for (int i = 0; i < m; ++i) {
		int x, y, d;
		scanf("%d %d %d", &x, &y, &d);

		searchRangeTree2D(rangeTree, x - d, x + d, y - d, y + d);
		printf("%d\n", sum);
		sum = 0;
	}

	delete[] a;
	return 0;
}