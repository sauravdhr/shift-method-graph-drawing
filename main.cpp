#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <glut.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <stack>
#include "point.h"
#include "edge.h"

using namespace std;

#define pi (2*acos(0.0))

///global variable///
int grid;
double cameraHeight;
double cameraAngle;
int N,M;
int canonical[20];
int order[20];
vector<Point> allVertx;
vector<Edge> allEdge;
vector<int> outerCycle;
vector< vector<int> > graph(50);
Node *root;
/////////////////////

void drawEdges()
{
    glColor3f(0.0, 1.0, 0.0);

    for(int i=0; i<M; i++)
    {
        glBegin(GL_LINES);
        glVertex3f(allVertx[allEdge[i].v1].x, allVertx[allEdge[i].v1].y, 0);
        glVertex3f(allVertx[allEdge[i].v2].x, allVertx[allEdge[i].v2].y, 0);
        glEnd();
    }

}

void drawGrid()
{
    if(grid==1)
    {
        glColor3f(0.26, 0.26, 0.26);
        glBegin(GL_LINES);
        {
            for(int i=0; i<=N-2; i++)
            {
                glVertex3f(0, i, 0);
                glVertex3f(2*N-4, i, 0);
            }
            for(int i=0; i<=2*N-4; i++)
            {
                glVertex3f(i, 0, 0);
                glVertex3f(i,N-2, 0);
            }
        }
        glEnd();
    }


}
void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {
    case '1':
        grid=1-grid;
        break;
    case '2':
        break;
    case '3':
        break;
    default:
        break;
    }
}


void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN:		//down arrow key
        cameraHeight -= 3.0;
        break;
    case GLUT_KEY_UP:		// up arrow key
        cameraHeight += 3.0;
        break;

    case GLUT_KEY_RIGHT:
        cameraAngle += 0.03;
        break;
    case GLUT_KEY_LEFT:
        cameraAngle -= 0.03;
        break;

    case GLUT_KEY_PAGE_UP:
        break;
    case GLUT_KEY_PAGE_DOWN:
        break;

    case GLUT_KEY_INSERT:
        break;

    case GLUT_KEY_HOME:
        break;
    case GLUT_KEY_END:
        break;

    default:
        break;
    }
}


void mouseListener(int button, int state, int x, int y)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN)
        {
        }
        break;

    case GLUT_RIGHT_BUTTON:
        //........
        break;

    case GLUT_MIDDLE_BUTTON:
        //........
        break;

    default:
        break;
    }
}



void display()
{
    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************
    / set-up camera here
    ********************/
    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();
    gluLookAt(0,0,cameraHeight,	0,0,0,	0,1,0);

    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);

    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    glTranslatef(-N+2,-(N-2)/2,0);

    drawEdges();
    drawGrid();

    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}

void animate()
{
    //codes for any changes in Models, Camera
    glutPostRedisplay();
}

void readInputs()
{
    ifstream infile;
    infile.open("input4.txt");
    infile>>N;
    for(int i=0; i<N; i++)
        allVertx.push_back(Point());
    infile>>M;
    Edge temp;
    for(int i=0; i<M; i++)
    {
        infile >> temp.v1 >> temp.v2;
        graph[temp.v1].push_back(temp.v2);
        graph[temp.v2].push_back(temp.v1);
        allEdge.push_back(temp);
    }
    int out;
    for(int i=0; i<3; i++)
    {
        infile >> out;
        outerCycle.push_back(out);
    }
    infile.close();

    for(int i=0; i<N; i++)
        canonical[i]=-1;
}

bool hasNoChord(int x)
{
    int chord=0;
    for(int i=0; i<graph[x].size(); i++)
    {
        if(canonical[graph[x][i]]==0)
            chord++;
        else if(canonical[graph[x][i]]==1)
            chord++;
        else if(canonical[graph[x][i]]==2)
            chord++;
    }
    if(chord==2)
        return true;
    else
        return false;
}

int chooseNext()
{
    int i=0;
    //    while(i<N&&canonical[i]==0)
    for(i=0; i<N; i++)
    {
//        cout<<"cn "<<i<<endl;
        if(canonical[i]==0)
            if(hasNoChord(i))
                return i;

    }
}

void canonicalOrder()
{
    cout<<"Canonical Order"<<endl;
    for(int i=0; i<N; i++)
        cout<<canonical[i]<<" ";
    cout<<endl;
    for(int i=0; i<N; i++)
        cout<<order[i]<<" ";
    cout<<endl;
}

void setCanonicalOrder()
{
    allVertx[outerCycle[0]].order=1;
    allVertx[outerCycle[1]].order=N;
    allVertx[outerCycle[2]].order=2;

    canonical[outerCycle[0]]=1;
    canonical[outerCycle[1]]=N;
    canonical[outerCycle[2]]=2;

    int dlt=outerCycle[1];
    for(int i=0; i<graph[dlt].size(); i++)
    {
        if(canonical[graph[dlt][i]]==-1)
            canonical[graph[dlt][i]]=0;
    }
//    canonicalOrder();
    for(int i=N-1; i!=2; i--)
    {
//        canonicalOrder();
        int next=chooseNext();
//        cout<<"next "<<next;
//        cout<<endl;
        canonical[next]=i;
        for(int j=0; j<graph[next].size(); j++)
        {
            if(canonical[graph[next][j]]==-1)
                canonical[graph[next][j]]=0;
        }
//        canonicalOrder();
    }

    for(int i=0; i<N; i++)
    {
        order[canonical[i]-1]=i;
    }
}

void printAllEdge()
{
    for(int i=0; i<M; i++)
        cout<<allEdge[i];

    cout<<endl;
}

void printAllVertex()
{
    for(int i=0; i<N; i++)
        cout<<allVertx[i]<<endl;;
}

void printGraph()
{
    for(int i=0; i<N; i++)
    {
        cout<<i<<":";
        for(int j=0; j<graph[i].size(); j++)
        {
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
}

void init()
{
    //codes for initialization
    grid=0;
    cameraHeight=150.0;
    cameraAngle=1.0;
    readInputs();
    //clear the screen
    glClearColor(0,0,0,0);

    /************************
    / set-up projection here
    ************************/
    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(80,	1,	1,	1000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X direction (horizontally)
    //near distance
    //far distance
}

Point middlePoint(int a, int b)
{
    int x1=allVertx[a].x-allVertx[a].y;
    int x2=allVertx[b].x+allVertx[b].y;
    int d=(x2-x1)/2;
    return Point(x1+d,d);
}

bool containsIn(int val,int index)
{
    for(int j=0; j<graph[index].size(); j++)
    {
        if(graph[index][j]==val)
            return true;
    }
    return false;
}

void incrementX(Node *n,int d)
{
    if (n == NULL) return;
    incrementX(n->left,d);
    allVertx[n->data].x+=d;
    incrementX(n->right,d);
}

void insertNode(int x)
{
//    cout<<"inserting :"<<x<<endl;
    Node *cur=root;
    while(cur!=NULL)
    {
//        cout<<cur->data<<" ";
        if(containsIn(cur->data,x))
            break;
        cur=cur->left;
    }

    Node *preCur=cur;
//    cout<<"pre :"<<preCur->data<<endl;
    cur=cur->left;
    while(cur->left!=NULL)
    {
//        cout<<cur->left->data<<" ";
        if(!containsIn(cur->left->data,x))
            break;
        cur=cur->left;
    }
//    while(cur!=NULL)
//    {
//        cout<<cur->data<<" ";
//        if(!containsIn(cur->data,x))
//            break;
//        cur=cur->left;
//    }
    Node *postCur=cur;
//    cout<<"post :"<<postCur->data<<endl;
//    incrementX(postCur,2);
    Node *in=new Node(x);
    if(preCur->left->data!=postCur->data)
    {
        postCur->parent->left=NULL;
        in->right=preCur->left;
        in->right->parent=in;
    }
    preCur->left=in;
    in->parent=preCur;
    in->left=postCur;
    postCur->parent=in;
    incrementX(in->left,2);
    incrementX(in->right,1);
    allVertx[x]=middlePoint(preCur->data,postCur->data);

}

void setCoordinate()
{
    allVertx[order[0]]=Point(0,0);
    allVertx[order[1]]=Point(2,0);
    allVertx[order[2]]=Point(1,1);
    root=new Node(order[0]);
    root->left=new Node(order[2]);
    root->left->parent=root;
    root->left->left=new Node(order[1]);
    root->left->left->parent=root->left;

//    printAllVertex();
    for(int i=3; i<N; i++)
    {
        insertNode(order[i]);
    }
//    insertNode(5);
//    insertNode(0);
//    printAllVertex();
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    init();
//    printAllEdge();
//    printGraph();
//    canonicalOrder();
    setCanonicalOrder();
    canonicalOrder();

    setCoordinate();
    printAllVertex();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing
    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}
