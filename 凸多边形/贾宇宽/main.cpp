//
//  main.cpp
//  OJ201701
//  凸多边形
//  Created by 贾宇宽 on 17/10/1.
//  Copyright © 2017年 贾宇宽. All rights reserved.
//

#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

class Point
{
public:
    Point():x(0), y(0) {}
    Point(double inx, double iny): x(inx), y(iny) {}
    friend double calc_slope(Point& prev, Point& next);
private:
    double x, y;
};

double calc_slope(Point& prev, Point& next)
{
    if(next.y > prev.y)
    {
        if(next.x - prev.x > 0)
            return atan((next.y - prev.y) / (next.x - prev.x));
        else if(next.x - prev.x < 0)
            return atan((next.y - prev.y) / (next.x - prev.x)) + M_PI;
        else
            return M_PI * 0.5;
    }
    else if(next.y < prev.y)
    {
        if(next.x - prev.x > 0)
            return atan((next.y - prev.y) / (next.x - prev.x)) + 2.0 * M_PI;
        if(next.x - prev.x < 0)
            return atan((next.y - prev.y) / (next.x - prev.x)) + M_PI;
        else
            return M_PI * 1.5;
    }
    else
        if(next.x > prev.x)
            return 0.0;
        else
            return M_PI;
}

bool is_concave(double prev, double next)
{
    if(prev <= M_PI)
    {
        if(next < prev || next > prev + M_PI)
            return false;
        else
            return true;
    }
    else
    {
        if(next > prev || next < prev - M_PI)
            return true;
        else
            return false;
    }
}
int main(int argc, const char * argv[])
{
    int k, n;
    queue<int> q;

    std::cin >> k;
    for(int i = 0; i < k; i++)
    {
        double x, y;
        std::cin >> n;
        std::cin >> x >> y;
        Point p_0(x, y);
        std::cin >> x >> y;
        Point p_last(x, y);
        double lastslope = calc_slope(p_0, p_last), slope_0 = lastslope;
        for(int j = 1; j < n - 1; j++)
        {
            std::cin >> x >> y;
            Point p_cur(x, y);
            double curslope = calc_slope(p_last, p_cur);
            if(is_concave(lastslope, curslope))
                q.push(j);
            lastslope = curslope;
            p_last = p_cur;
        }
        if(is_concave(lastslope, calc_slope(p_last, p_0)))
            q.push(n-1);
        if(!is_concave(calc_slope(p_last, p_0), slope_0))
        {
            if(q.empty())
                cout << "y";
            else
                while(!q.empty())
                {
                    int tmp = q.front();
                    cout << tmp << " ";
                    q.pop();
                }
        }
        else
        {
            cout << "0 ";
            while(!q.empty())
            {
                int tmp = q.front();
                cout << tmp << " ";
                q.pop();
            }
        }
        cout << endl;
    }
    return 0;
}
