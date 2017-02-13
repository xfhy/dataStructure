# include "comdef.h"
# include <iostream>

using namespace std;

//----------------稀疏矩阵的十字链表存储表示-----------
typedef struct OLNode
{
	int i,j;      //非零元素的行和列下标
	ElemType e;  //非零元素本体
	struct OLNode *right,*down;   //该非零元素的行表和列表的后继链域
}OLNode,*OLink;
typedef struct
{
	OLink *rhead,*chead;   //行和列链表头指针向量基址由CreateSmatrix分配
	int mu;             //行数
	int nu;              //列数
	int tu;          //稀疏矩阵的非零元素个数
}CrossList;

//创建稀疏矩阵M,才用十字链表存储表示
Status CreateSmatrix(CrossList &M)
{
	/*
	          潇氏小算法:
	输入M的行数,列数,非零元的个数
	给每一行,每一列的头指针分配空间
	循环输入非零元的行号,列号,值
	输入一个非零元素后立即判断该插入到该行,列的确定位置
	(行:if该行是空的,或者需要插入的元素的列号比先前已存在的改行的第一个元素的列号小,则直接插入;
	    否则需要查找该元素该放在该行的适当位置再进行插入;   )
	*/
	M.mu = 6;   M.nu = 7;   M.tu = 3;   //默认的行数列数和非零元个数
	if( !(M.rhead=(OLink *)malloc(sizeof(OLNode)*(M.mu+1))) )     exit(0);  //每一行头指针分配空间,0号不要
	if( !(M.chead=(OLink *)malloc(sizeof(OLNode)*(M.nu+1))) )     exit(0);
	//将每一行,列的链表的头指针指向NULL
	for(int i=0; i<=M.mu; i++)    M.rhead[i] = NULL;
	for(int i=0; i<=M.nu; i++)    M.chead[i] = NULL;

	int mu,nu;   ElemType e;     //非零元素的行,列,值
	OLink p,q;
	for(scanf("%d,%d,%d",&mu,&nu,&e);mu!=0;scanf("%d,%d,%d",&mu,&nu,&e))   //当输入的行(hang)为0时退出输入循环
	{
		p = (OLNode *)malloc(sizeof(OLNode));
		p->i = mu;   p->j = nu;    p->e = e;

		//-----------------行链表-------------
		if( M.rhead[mu]==NULL || M.rhead[mu]->j>nu)
			//if该行是空的,或者需要插入的元素的列号比先前已存在的改行的第一个元素的列号小,则直接插入
		{
			p->right = M.rhead[mu];  M.rhead[mu] = p;   p->right = NULL;
		}
		else  //否则需要查找合适位置
		{
			for(q=M.rhead[mu];(q->right)&&(q->right->j<nu);q=q->right) ;    //空循环,出循环时,已经找到合适位置
			p->right = q->right;
			q->right = p;
		}

		//---------------列链表---------------------
		if(M.chead[nu]==NULL || M.chead[nu]->i>mu)
		{
			p->down = M.chead[nu];  M.chead[nu] = p;  p->down = NULL;
		}
		else
		{
			for(q=M.chead[nu];(q->down)&&(q->down->i<mu);q=q->down) ;
			p->down = q->down;
			q->down = p;
		}
	}
	return OK;
}

//输出矩阵(行)
Status Show(CrossList M)
{
	OLNode *q;
	for(int i=1; i<=M.mu; i++)
	{
		q = M.rhead[i];   //每一行的链表的头指针
		for(int j=1; j<=M.nu; j++)
		{
			if( (q!=NULL) && (q->i==i)&& (q->j==j) )
			{
				cout.width(4);
				cout<<q->e;
				q = q->right;
			}
			else
			{
				cout.width(4);
				cout<<0;
			}
		}
		cout<<endl;
	}
	return OK;
}

int main(void)
{
	CrossList M;
	CreateSmatrix(M);
	Show(M);

	system("pause");
	return 0;
}