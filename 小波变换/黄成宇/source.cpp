#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TRUE 1
#define FALSE 0

float* WaveLet(float* data, int length, int k)
{
	if (!k)return data;
	else {
		float* data_tmp = (float*)malloc(sizeof(float)*pow(2, length));
		float* data_return = (float*)malloc(sizeof(float)*pow(2, length));
		data_tmp = WaveLet(data, length, k - 1);
		for (int i = 0; i<pow(2, length - k); i++) {
			data_return[i] = (data_tmp[2 * i] + data_tmp[2 * i + 1]) / 2;
		}
		for (int i = pow(2, length - k); i<pow(2, length - k + 1); i++) {
			data_return[i] = (data_tmp[2 * (i - (int) pow(2, length - k)) + 1] - data_tmp[2 * (i - (int) pow(2, length - k))]) / 2;
		}
		for (int i = pow(2, length - k + 1); i<pow(2, length); i++)data_return[i] = data_tmp[i];
		free(data_tmp);
		return data_return;
	}
}

int main()
{
	int length;
	scanf("%d", &length);
	float* data = (float*)malloc(sizeof(float)*pow(2, length));
	float* data_result = (float*)malloc(sizeof(float)*pow(2, length));
	for (int i = 0; i<pow(2, length); i++)scanf("%f", data + i);
	data_result = WaveLet(data, length, length);
	for (int i = 0; i<pow(2, length); i++)printf("%.4f ", data_result[i]);
	free(data_result);
	return 0;
}
