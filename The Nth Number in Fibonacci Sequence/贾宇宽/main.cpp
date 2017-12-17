//
//  main.cpp
//  OJ1002
//
//  用stdio代替iostream以减少memory
//  Created by 贾宇宽 on 17/9/25.
//  Copyright © 2017年 贾宇宽. All rights reserved.
//

#include <stdio.h>
#define mod 9973

class matrix_2_2
{
private:
    int a11, a12, a21, a22;
public:
    matrix_2_2();
    matrix_2_2(int a11, int a12, int a21, int a22);
    matrix_2_2 operator* (const matrix_2_2& another) const;
    void operator= (const matrix_2_2& another);
    int get_a12();
};
matrix_2_2::matrix_2_2(): a11(0), a12(0), a21(0), a22(0) {}
matrix_2_2::matrix_2_2(int a11, int a12, int a21, int a22)
{
    this->a11 = a11;
    this->a12 = a12;
    this->a21 = a21;
    this->a22 = a22;
}
matrix_2_2 matrix_2_2::operator* (const matrix_2_2& another) const
{
    int result11, result12, result21, result22;
    result11 = (a11 * another.a11 + a12 * another.a21) % mod;
    result12 = (a11 * another.a12 + a12 * another.a22) % mod;
    result21 = (a21 * another.a11 + a22 * another.a21) % mod;
    result22 = (a21 * another.a12 + a22 * another.a22) % mod;
    return matrix_2_2(result11, result12, result21, result22);
}
void matrix_2_2::operator= (const matrix_2_2& another)
{
    a11 = another.a11;
    a12 = another.a12;
    a21 = another.a21;
    a22 = another.a22;
}
int matrix_2_2::get_a12()
{
    return a12;
}

int main(int argc, const char * argv[])
{
    //记录从矩阵的2^0次方到2^30(1073743824)次方
    matrix_2_2 base[32];
    base[0] = matrix_2_2(1, 1, 1, 0);
    for(int i = 1; i < 32; i++)
        base[i] = base[i - 1] * base[i - 1];
    
    int n, a[20];
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for(int i = 0; i < n; i++)
    {
        if(a[i] == 0)
        {
            printf("0\n");
            continue;
        }
        matrix_2_2 result(1, 0, 0, 1);
        int digit = 0;
        while(a[i] / 2)
        {
            if(a[i] % 2)
                result = result * base[digit];
            a[i] /= 2;
            digit++;
        }
        result = result * base[digit];
        printf("%d\n", result.get_a12());
    }
    return 0;
}
