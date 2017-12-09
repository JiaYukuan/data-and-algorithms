#include <iostream>
#include <cstring>

int main()
{
	char a[1000] = { '0' };
	std::cin.getline(a, 1000, ' ');
	char b[1000] = { '0' };
	std::cin.getline(b, 1000, '\n');
	int c[1000];

	if (strlen(b) > strlen(a)) {
		char tmp[1000];
		strcpy(tmp, b);
		strcpy(b, a);
		strcpy(a, tmp);
	}

	int i = strlen(a);
	int j = strlen(b);
	int m = 0;
	int up = 0, down = 0;

	while (1) {
		i--;
		j--;
		if (i == -1) {
			c[m] = up;
			break;
		}
		if (j <= -1) {
			up += a[i] - 48;
			down = 0;
		}
		else {
			up += a[i] - 48;
			down += b[j] - 48;
		}
		int sum = up + down;
		if (sum > 9) {
			c[m] = sum - 10;
			up = 1;
			down = 0;
		}
		else {
			c[m] = sum;
			up = 0;
			down = 0;
		}
		m++;
	}

	if (c[m] == 1) std::cout << 1;

	for (i = m - 1; i >= 0; --i) {
		std::cout << c[i];
	}

	return 0;
}