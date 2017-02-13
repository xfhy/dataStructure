/*
*给定n个权值作为n的叶子结点，构造一棵二叉树，若带权路径长度达到最小，称这样的二叉树为最优二叉树，
也称为哈夫曼树(Huffman Tree)。哈夫曼树是带权路径长度最短的树，权值较大的结点离根较近。
*/

# include "comdef.h"
# include <iostream>

using namespace std;

typedef struct
{
	unsigned int weight;                 //权
	unsigned int parent,lchild,rchild;   //亲,左孩子,右孩子
}HTNode,*HuffmanTree;

typedef char ** HuffmanCode;

                  /*---------------构造哈夫曼树---------------------*/
//选出最小的2个结点
void Select(HuffmanTree HT,int t,int &s1,int &s2)   //哈夫曼树的表,下标,需要求的2个最小值
{
	s1 = s2 = HT[0].weight;
	for(int i=1; i<=t; i++)
	{
		if(HT[i].parent==0)              //判断是否有亲人
		{
			if( s2 > HT[i].weight )      //比大的那个数还小
			{
				if( s1 > HT[i].weight )  //比较和2个数中最小的数谁大    比最小的那个数还小
					s1 = HT[i].weight;
				else                     //a[i] 介于2个数中间
				    s2 = HT[i].weight;
			}
		}
	}
}
void CreatHuffmanTree(HuffmanTree &HT,int w[],int n)   //哈弗曼树,最初的数组,数组的最初长度
{
	if(n<=1)  return ;
	int s1=0,s2=0;
	int m = 2*n - 1;    //哈夫曼树的最终结点数  == 2*最初的点数 - 1
	HT = (HuffmanTree)malloc( sizeof(HTNode) * (m+1) );   //0号下标不用,所以多申请一个结点空间
	for(int i=1; i<=m; i++)
	{
		if(i<=n)   //初始化从1到n的结点的自己的权
		{
			HT[i].weight = w[i-1];   HT[i].parent = 0;
            HT[i].lchild = 0;        HT[i].rchild = 0;
		}
		else    //其他的结点暂时存储为0
		{
			HT[i].weight = 0;        HT[i].parent = 0;
			HT[i].lchild = 0;        HT[i].rchild = 0;
		}
	}
	for(int i=n+1; i<=m; i++)   //建立哈弗曼树
	{
		Select(HT,i-1,s1,s2);
		HT[s1].parent = i;   HT[s2].parent = i;    //认自己的亲人
		HT[i].lchild = s1;   HT[i].rchild = s2;    //认自己的孩子
		HT[i].weight = HT[s1].weight + HT[s2].weight;  //计算自己(新生产的结点)的权重
	}
}

                 /*---------------哈弗曼树的编码--------------------*/
void HuffmanCoding(HuffmanTree HT,HuffmanCode &HC,int n)
{
	HC = (HuffmanCode)malloc( sizeof(char*) * (n+1) );  //存储  分配n个字符编码的头指针向量([0]不用)
	char *cd = (char *)malloc( sizeof(char) * n );      //分配求编码的工作空间
	cd[n-1] = '\0';     //空间结束符
	int start;          //倒着存的,start是下标
	int c,f;            //c是当前节点的序号,f是当前结点亲人的序号
	for(int i=1; i<=n; i++)
	{
		start=n-1;
		for(c=i,f=HT[i].parent; f!=0; c=f,f=HT[f].parent)
		{
			if(HT[f].lchild==c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char *)malloc( sizeof(char) * n-start );
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
}
                 

int main(void)
{
	int w[4] = {7,5,2,4};
	HuffmanTree HT;
	CreatHuffmanTree(HT,w,4);
	HuffmanCode HC;
	HuffmanCoding(HT,HC,4);
	system("pause");
	return 0;
}