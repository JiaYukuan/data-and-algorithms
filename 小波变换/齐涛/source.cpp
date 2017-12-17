#include<stdio.h>
#include<iostream>

void one_change(float* signal,int len)
{
	int half_len = len / 2;
	int quart_len = len / 4;
	if (quart_len)
	{
		float *temp =new float[quart_len];
		for (int i = quart_len; i <= half_len - 1; i++)
			temp[i - quart_len] = (signal[2 * i] + signal[2 * i + 1]) / 2;
		for (int i = len - 1; i >= half_len; i--)
			signal[i] = (signal[2 * (i - half_len)+1] - signal[2 * (i - half_len)]) / 2;
		for (int i = 0; i < quart_len; i++)
			signal[i] = (signal[2 * i] + signal[2 * i + 1]) / 2;
		for (int i = quart_len; i < half_len; i++)
			signal[i] = temp[i - quart_len];
		delete[]temp;
	}
	else
	{
		double temp = (signal[0] + signal[1]) / 2;
		signal[1] = (signal[1] - signal[0]) / 2;
		signal[0] = temp;
	}
}

int power2(int L)
{
	if (L == 1)
		return 2;
	if (L % 2 == 0)
	{
		int t = power2(L / 2);
		return t*t;
	}
	else
	{
		int t = power2(L / 2);
		return 2 * t*t;
	}
}

void change()
{
	float *signal;
	int len;
	int L;
	scanf("%d",&L);
	len = power2(L);
	int cplen = len;
	signal = new float[len];
	for (int i = 0; i < len; i++)
		scanf("%f",signal+i);
	for (int i = 0; i < L; i++)
	{
		one_change(signal, len);
		len /= 2;
	}
	for (int i = 0; i < cplen-1; i++)
		printf("%.4f ", signal[i]);
	printf("%.4f", signal[cplen - 1]);
}
int main()
{
	change();
}
