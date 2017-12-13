#include <stdio.h>

int main() {
	int polygon_num, point_num;
	float polygon_point_x[1000], polygon_point_y[1000];
	scanf("%d", &polygon_num);
	for (int k = 0; k<polygon_num; k++) {
		scanf("%d", &point_num);
		for (int i = 0; i<point_num; i++)scanf("%f%f", polygon_point_x + i, polygon_point_y + i);
		int bool_polyconcave = 1;
		float vector_head_x, vector_head_y, vector_prev_x, vector_prev_y;
		vector_prev_x = polygon_point_x[0] - polygon_point_x[point_num - 1];
		vector_prev_y = polygon_point_y[0] - polygon_point_y[point_num - 1];
		for (int i = 0; i<point_num; i++) {
			vector_head_x = polygon_point_x[(i + 1) % point_num] - polygon_point_x[i%point_num];
			vector_head_y = polygon_point_y[(i + 1) % point_num] - polygon_point_y[i%point_num];
			if (vector_prev_x*vector_head_y - vector_prev_y*vector_head_x>0){
				printf("%d ", i );
				bool_polyconcave = 0;
			}
			vector_prev_x = vector_head_x;
			vector_prev_y = vector_head_y;
		}
		if (bool_polyconcave)printf("y");
		printf("\n");
	}
	return 0;
}
