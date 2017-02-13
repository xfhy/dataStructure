#ifndef h1
#define h1

# include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string.h>
#include <malloc.h>
#include <process.h>
using namespace std;



#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFFASIBLE -1
#define OVERFLOW -2
typedef char VertexType;
typedef int VRType;
typedef int Status;          //返回的状态
typedef int ElemType ;       //数据类型

#define INFINITY 1000        //最大值 
#define MAX_VERTEX_NUM 25   //最大顶点数
typedef enum{DG,DN,UDG,UDN}GraphKind;   //{有向图,有向网,无向图,无向网}
//有向图和无向图不带权
typedef int* ShortPathTable;
typedef int* PathMatrix;

#endif
