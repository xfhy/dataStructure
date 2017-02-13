#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <malloc.h>
#include <process.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;
#define INIFINITY 1000   			    // 最大值
#define MAX_VERTEX_NUM 20    			//最大顶点数
typedef enum{DG,DN,UDG,UDN} GraphKind; 	//图的四种类型  {有向图,有向网,无向图,无向网}
typedef char VertexType;                //顶点信息
typedef int  InfoType;                  //权