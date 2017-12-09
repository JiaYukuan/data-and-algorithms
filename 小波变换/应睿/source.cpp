#include <stdio.h>
#include <math.h>

int N0;

float* haarTransform(float* f0, int N) {
	// f0是输入的待变换信号
	// f1是是上一次计算得到的结果
	// f2是这次计算将要得到的结果
	float* f1 = NULL;
	float* f2 = new float[N0];

	if (N == N0 / 2) {
		for (int n = 0; n < N; ++n) {
			f2[n] = (f0[2 * n] + f0[2 * n + 1]) / 2;
		}
		for (int n = N; n < N * 2; ++n) {
			f2[n] = (f0[2 * (n - N) + 1] - f0[2 * (n - N)]) / 2;
		}

		// f0已经没用了
		delete[] f0;
		f0 = NULL;

		// 将结果保存在f1
		f1 = f2;
		f2 = NULL;

		return f1;
	}
	else {
		// 从上一级获得f1
		f1 = haarTransform(f0, N * 2);

		for (int n = 0; n < N; ++n) {
			f2[n] = (f1[2 * n] + f1[2 * n + 1]) / 2;
		}
		for (int n = N; n < N * 2; ++n) {
			f2[n] = (f1[2 * (n - N) + 1] - f1[2 * (n - N)]) / 2;
		}
		for (int n = N * 2; n < N0; ++n) {
			f2[n] = f1[n];
		}

		// 将结果保存在新的f1，并清除之前的f1
		float* tmp;
		tmp = f1;
		f1 = f2;
		delete[] tmp;
		f2 = NULL;

		return f1;
	}
}

int main() {
	scanf("%d", &N0);
	N0 = pow(2, N0);
	float* f0 = new float[N0];
	for (int i = 0; i < N0; ++i) {
		scanf("%f", &f0[i]);
	}

	float* fL = haarTransform(f0, 1);

	for (int i = 0; i < N0 - 1; ++i) {
		printf("%f ", fL[i]);
	}
	printf("%f\n", fL[N0 - 1]);

	delete fL;
	return 0;
}