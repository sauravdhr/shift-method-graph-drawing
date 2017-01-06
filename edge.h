//
// Created by Saurav
//

#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <vector>
#include "point.h"

using namespace std;


class Edge
{
public:
    int v1,v2;

    Edge()
    {
        v1=v2=0;
    }

    Edge(int p1, int p2)
    {
        v1=p1;
        v2=p2;
    }

    //0=no, 1=felt, 2=right
//    int contains(Point p)
//    {
//        if(!valid) return 0;
//
//        if(PointInTriangle(p,v1,v2,left))
//            return 1;
//        if(PointInTriangle(p,v1,v2,right))
//            return 2;
//
//        return 0;
//    }

    bool operator == (Edge b)
    {
        return ((this->v1==b.v1)&&(this->v2==b.v2))||((this->v1==b.v2)&&(this->v2==b.v1));
    }

    friend ostream &operator<<(ostream &os, const Edge &e)
    {
//        os<<"v1: "<<e.v1<<" v2: "<<e.v2<<" left: "<<e.left<<" right: "<<e.right<<endl;
        os<<"v1: "<<e.v1<<" v2: "<<e.v2<<endl;
        return os;
    }
};

class Node
{
public:
    int data;
    Node *left,*right,*parent;

    Node()
    {
        data=-1;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
    Node(int d)
    {
        data=d;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};
#endif
