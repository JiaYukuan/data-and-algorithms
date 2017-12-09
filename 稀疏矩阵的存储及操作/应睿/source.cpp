#include <stdio.h>

struct Triple {
	int row;
	int column;
	int value;
	Triple *down = NULL;
	Triple *right = NULL;
};

int main() {
	int n, line;
	scanf("%d %d %d", &n, &n, &line);

	// Head of all rows. Vertically placed.
	Triple** rowHead = new Triple*[n];

	// Head of all columns. Horizontally placed.
	Triple** columnHead = new Triple*[n];

	for (int i = 0; i < n; ++i) {
		rowHead[i] = NULL;
		columnHead[i] = NULL;
	}

	// Input the matrix.
	for (int i = 0; i < line; ++i) {
		Triple* triple = new Triple;
		scanf("%d %d %d", &triple->row, &triple->column, &triple->value);

		if (triple->value == 0) {
			continue;
		}

		Triple* p = NULL;

		// Initiate the head.
		if (rowHead[triple->column] == NULL) {
			rowHead[triple->column] = triple;
		}
		else {
			// Switch the head.
			if (rowHead[triple->column]->row > triple->row) {
				triple->down = rowHead[triple->column];
				rowHead[triple->column] = triple;
			}
			else {
				// Look through by the row. Note: vertically
				for (p = rowHead[triple->column]; p->down != NULL && p->down->row < triple->row; p = p->down) {
					// pass
				}
				// Insert.
				triple->down = p->down;
				p->down = triple;
			}
		}

		// Initiate the head.
		if (columnHead[triple->row] == NULL) {
			columnHead[triple->row] = triple;
		}
		else {
			// Switch the head if needed.
			if (columnHead[triple->row]->column > triple->column) {
				triple->right = columnHead[triple->row];
				columnHead[triple->row] = triple;
			}
			else {
				// Look through by the column. Note: horizontally
				for (p = columnHead[triple->row]; p->right != NULL && p->right->column < triple->column; p = p->right) {
					// pass
				}
				// Insert.
				triple->right = p->right;
				p->right = triple;
			}
		}
	}

	// Transpose the matrix.
	Triple* p = NULL;
	for (int i = 0; i < n; ++i) {
		// Look through by the row.
		p = rowHead[i];

		if (p != NULL) {
			printf("%d %d %d\n", p->column, p->row, p->value);

			// Print elements in the same row.
			p = p->down;
			while (p != NULL) {
				printf("%d %d %d\n", p->column, p->row, p->value);
				p = p->down;
			}
		}
	}

	// Sum up matrices.
	Triple* q = NULL;
	int s1, s2;
	for (int i = 0; i < n; ++i) {
		p = columnHead[i];
		q = rowHead[i];

		for (int j = 0; j < n; ++j) {
			if (p == NULL) {
				s1 = 0;
			}
			else {
				// The element will not be used this time.
				if (p->column != j) {
					s1 = 0;
				}
				// Proceed to the next.
				else {
					s1 = p->value;
					p = p->right;
				}
			}

			if (q == NULL) {
				s2 = 0;
			}
			else {
				// The element will not be used this time.
				if (q->row != j) {
					s2 = 0;
				}
				// Proceed to the next.
				else {
					s2 = q->value;
					q = q->down;
				}
			}

			int sum = s1 + s2;
			if (sum != 0) {
				printf("%d %d %d\n", i, j, sum);
			}
		}
	}

	// Multiply matrices.
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			// Present a row.
			p = columnHead[i];

			// Present a column.
			q = columnHead[j];

			int sum = 0;
			while (p != NULL && q != NULL) {
				// Ensure the multiplication only happens when they share the same row and column, or move the pointer.
				if (p->column < q->column) {
					for (; p != NULL && p->column < q->column; p = p->right) {
						// pass
					}
				}
				else if
					(p->column > q->column) {
					for (; q != NULL && p->column > q->column; q = q->right) {
						// pass
					}
				}
				else {
					sum += q->value * p->value;
					p = p->right;
					q = q->right;
				}
			}
			if (sum != 0) {
				printf("%d %d %d\n", i, j, sum);
			}
		}
	}

	delete[] rowHead, columnHead;
	return 0;
}