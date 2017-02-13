# include "comdef.h"
# include <iostream>

using namespace std;

typedef struct
{
	int i,j;    //该非零元素的行下标和列下标
	ElemType e;  //元素
}Triple;
typedef struct
{
	Triple *data;  //非零元三元组表，动态构造
	int mu,nu,tu; //矩阵的行数，矩阵的列数，和非零元的个数
}TSMatrix;

//创建稀疏矩阵
Status CreatSMatrix(TSMatrix &M)
{
	M.data = (Triple *)malloc(sizeof(Triple)*42);   //初始化，6行，7列
	M.mu = 6;  //行数
	M.nu = 7;  //列数
	M.tu = 8;  //非零元的个数
	/*--------下面是初始化非零元素----------*/
	M.data[1].i = 1;   //从0开始
	M.data[1].j = 2;
	M.data[1].e = 12;
	M.data[2].i = 1;
	M.data[2].j = 3;
	M.data[2].e = 9;
	M.data[3].i = 3;
	M.data[3].j = 1;
	M.data[3].e = -3;
	M.data[4].i = 3;
	M.data[4].j = 6;
	M.data[4].e = 14;
	M.data[5].i = 4;
	M.data[5].j = 3;
	M.data[5].e = 24;
	M.data[6].i = 5;
	M.data[6].j = 2;
	M.data[6].e = 18;
	M.data[7].i = 6;
	M.data[7].j = 1;
	M.data[7].e = 15;
	M.data[8].i = 6;
	M.data[8].j = 4;
	M.data[8].e = -7;
	return OK;
}

//输出稀疏矩阵
void PrintSMatrix(TSMatrix M)
{
	if(M.data==NULL)
	{
		cout<<"矩阵为空"<<endl;
		return ;
	}
	int p = 1;   //非零元素，依次放到其中
	for(int k=1; k<=M.mu; k++)  //行数6
	{
		for(int t=1; t<=M.nu; t++)  //列数7
		{
			if(M.data[p].i==k && M.data[p].j==t)
			{
				cout.width(4);  //占4位
				cout<<M.data[p].e<<"   ";
				p++;
			}
			else
			{
				cout.width(4);
				cout<<0<<"   ";		
			}
		}
		cout<<endl;
	}
}

//销毁
Status DestroySMatrix(TSMatrix &M)
{
	free(M.data);
	M.data = NULL;
	return OK;
}

//矩阵转置2   按M的列序进行转置
Status TransposeSMatrix2(TSMatrix M,TSMatrix &T)
{
	//M.data  从1~8
	T.mu = M.nu;  T.nu = M.mu; T.tu = M.tu;   //将行,列,非零元个数弄过去    转置后行列数交换
	int p=1;  //临时值
	for(int k=1; k<=M.nu; k++)  //从列开始循环,这样列从1开始,则直接交换后,无需排序即可
	{
		for(int l=1; l<=M.tu; l++)  //非零元个数   从M的非零元素从1开始依次判断在哪一列
		{
			if( M.data[l].j==k )  //第一次,l==3和l==7时,刚好j==1    则开始转置,把自己的值复制给T
			{
				T.data[p].j = M.data[l].i;
				T.data[p].i = M.data[l].j;
				T.data[p].e = M.data[l].e;
				p++;   //放了一个元素之后,向后移
			}
		}
	}
	return OK;
}

//矩阵的快速转置   
Status FastTranspose(TSMatrix M,TSMatrix &T)
{
	T.mu = M.nu;  T.nu = M.mu; T.tu = M.tu;
	if(T.tu)   //有非零元素
	{
		/*---------------统计-----------------*/
		int num[9];   //存:M每一列中的非零元的个数   0号元素不用
		int cpot[9];  //存:T中每一行的非零元素的最开始的位置
		for(int col=0; col<=M.tu; col++)   num[col]=0;     //初始化num数组中每个元素都为零
		for(int t=1; t<=M.tu; t++)    num[M.data[t].j]++;  //把M中的每一列中有几个元素放到num数组中
		cpot[1] = 1;
		int col=0;
		for(col=2; col<=M.tu; col++)  cpot[col] = num[col-1] + cpot[col-1];   //前一个num与前一个cpot的和既是这一行的
		//第一个的序号(求第col列中第一个非零元在T.data中的序号)

		/*---------------关键代码-------------*/
		int q=1;
		for(int p=1; p<=M.tu; p++)
		{
			col = M.data[p].j;    //求出该元素的原来的列,既是新的矩阵的行
			q = cpot[col];   //求出该元素该放在新矩阵的那一行的第几个位置
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			cpot[col]++;    //该元素该放在新矩阵的那一行的那个位置要加1
		}
 	}
	return OK;
}

int main(void)
{
	TSMatrix M;
	CreatSMatrix(M);  //创建
	PrintSMatrix(M);  //输出
	//DestroySMatrix(M);
	//PrintSMatrix(M);
	cout<<"-----------交换后输出---------------"<<endl;
	TSMatrix T;
	CreatSMatrix(T);  //创建
	//TransposeSMatrix2(M,T);
	FastTranspose(M,T);
	PrintSMatrix(T);
	system("pause");
	return 0;
}