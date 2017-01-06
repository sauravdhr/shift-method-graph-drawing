//
// Created by Saurav
//
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

class Point
{

public:
    int x, y;
    int order;

    Point(void)
    {
        x= y= 0;
        order=-1;
    }

    Point(int a, int b)
    {
        x = a;
        y = b;
    }

    Point(const Point &obj)
    {
        x=obj.x;
        y=obj.y;
        order=obj.order;
    }

//    bool operator < (Point b)
//    {
//        if (this->y != b.y)
//            //return the leftmost point
//            return this->y > b.y;
//        return this->x > b.x;
//    }

    bool operator == (Point b)
    {
        return (this->x==b.x)&&(this->y==b.y);
    }

    friend ostream &operator<<(ostream &os, const Point &p)
    {
        os << "x: " << p.x << " y: " << p.y;
        return os;
    }

    double dist(Point p0)
    {
        return sqrt((x - p0.x) * (x - p0.x) +
                    (y - p0.y) * (y - p0.y));
    }

};

/*
 * Determines whether two vectors (p0, p1) and (p1, p2)
 * defined by three points p0, p1 and p2 make a left turn.
 */

float sign(Point p1,Point p2,Point p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(Point pt,Point v1,Point v2,Point v3)
{
    bool b1, b2, b3;

    b1 = sign(pt, v1, v2) < 0.0;
    b2 = sign(pt, v2, v3) < 0.0;
    b3 = sign(pt, v3, v1) < 0.0;

    return ((b1 == b2) && (b2 == b3));
}

bool double_equals(double a, double b)
{
    double epsilon = 0.0000000001;
    return (abs(a - b) < epsilon);
}

#endif
