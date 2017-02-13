# include <iostream>

using namespace std;

#ifndef h1
#define h1
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFFASIBLE -1
#define OVERFLOW -2
typedef int Status;          //返回的状态
typedef char TElemType ;       //数据类型

/*--------------------二叉树的二叉链表存储表示-----------*/
typedef struct BiTNode
{
	TElemType data;                    //数据域
	struct BiTNode *lchild, *rchild;   //左右孩子指针
}BiTNode,*BiTree;
typedef BiTree ElemType ;       //数据类型  结构体指针
#endif