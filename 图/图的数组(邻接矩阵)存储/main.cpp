# include "comdef.h"
# include "queue.h"
# include <iostream>

using namespace std;

typedef struct
{
	VRType adj;    //顶点关系类型:对于无权图则为0或1,表示是否相邻,对于带权图则表示权
}AdjMatrix[5][5];      //二维数组,每个点表示该(i,j)的权
typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];   //顶点(数组)向量(存储顶点名称)
	AdjMatrix arcs;                    //邻接矩阵
	int vexnum;                        //图的当前顶点数
	int arcnum;                        //图的当前边数(弧数)
	GraphKind kind;                    //图的类型
}MGraph;
int LocateVex(VertexType v,MGraph G);   //找到顶点位置
Status CreateDG(MGraph &G);       //构造有向图DG
Status CreateDN(MGraph &G);       //构造有向网DN
Status CreateUDG(MGraph &G);      //构造无向图UDG
Status CreateUDN(MGraph &G);      //构造无向网UDN
Status Output(MGraph G);          //图的输出
void DFSTraverse(MGraph G);       //深度优先算法
void DFS(MGraph G,int v);
     //有向图和无向图不带权
void ShortestPath_DIJ(MGraph G,int v0);

void ShortestPath_DIJ(MGraph G,int v0)   //P:路径数组,D:最短路径
{
	/*
	通过Dijkstra计算图G中的最短路径时，需要指定起点s(即从顶点s开始计算)。
     此外，引进两个集合S和U。S的作用是记录已求出最短路径的顶点(以及相应的最短路径长度)，
	 而U则是记录还未求出最短路径的顶点(以及该顶点到起点s的距离)。
     初始时，S中只有起点s；U中是除s之外的顶点，并且U中顶点的路径是"起点s到该顶点的路径"。
	 然后，从U中找出路径最短的顶点，并将其加入到S中；接着，更新U中的顶点和顶点对应的路径。 
	 然后，再从U中找出路径最短的顶点，并将其加入到S中；
	 接着，更新U中的顶点和顶点对应的路径。 ... 重复该操作，直到遍历完所有顶点。
	*/
	int v,w,min;
	//  最终距离最短          路径存放点          从哪里到哪里        路径
	int final[MAX_VERTEX_NUM],D[MAX_VERTEX_NUM],from[MAX_VERTEX_NUM],path[MAX_VERTEX_NUM];

	//初始化
	for(int v=0; v<G.vexnum; v++)
	{
		final[v] = false;
		D[v] = G.arcs[v0][v].adj;   //权
		if(D[v]<INFINITY)
			from[v] = v0;
	}
	D[v0] = 0;  final[v0] = true;     //自己到自己,路径为0,且最终确定

	//开始主循环,每次求得v0到某个顶点的最短路径,并加v到S集                   
	for(int i=1; i<G.vexnum; i++)   //除开自己这个顶点的其他顶点
	{
		min = INFINITY;             //当前所知离v顶点的最近距离
		for(int w=0; w<G.vexnum; w++)
		{
			if(!final[w] && D[w]<min)
			{
				v = w;
				min = D[w];
			}
		} //v为最短路径的那个点
		final[v] = true;     //v这个顶点已经是最短距离了

		//输出一条最短路径
		if(D[v]==INFINITY)
			cout<<G.vexs[v0]<<"到"<<G.vexs[i]<<"的最短路径为∞"<<endl;
		else
		{
			cout<<G.vexs[v0]<<"到"<<G.vexs[i]<<"的最短路径为"<<D[i]<<endl;
			cout<<"且经过:"<<endl;
			int u = v;
			int k;
			for(k=0; u!=v0; k++)
			{
				path[k] = u;
				u = from[u];
			}
			cout<<G.vexs[v0];
			for(int p=k-1; p>=0; p--)
			{
				cout<<"--->"<<G.vexs[path[p]];
			}
			cout<<endl;
		}

		//更新当前最短路径及距离
		for(int w=0; w<G.vexnum; w++)
		{
			if(!final[w] && (min+G.arcs[v][w].adj<D[w]))
			{
				D[w] = min+G.arcs[v][w].adj;
				from[w] = v;
			}
		}
	}//for
}

                  /*--------------图的建立----------------------*/
Status CreateGraph(MGraph &G)     
{
	cout<<"请按照序号输入您想创建的图的类型"<<endl;
	cout<<"0:有向图  1:有向网  2:无向图  3:无向网"<<endl;
	int temp;
	cin>>temp;
	if(temp>3 || temp<0)
		return ERROR;
	G.kind = (GraphKind)temp;     //将对应的枚举类型取出放到G的种类当中
	switch(temp)
	{
	    case DG:                 //构造有向图
			 return CreateDG(G);
			 break;
		case DN:                   //构造有向网
			return CreateDN(G);
			break;
		case UDG:                  //构造无向图(没有权)
			return CreateUDG(G);
			break;
		case UDN:                  //构造无向网
			return CreateUDN(G);
			break;
		default:
			return ERROR;
	}
	return OK;
}

                  /*---------------构造有向图DG-----------------*/
Status CreateDG(MGraph &G)
{
	cout<<"请输入图的顶点数和弧数"<<endl;
	cin>>G.vexnum>>G.arcnum;
	cout<<"构造顶点向量(请依次输入顶点的名称)"<<endl;
	for(int i=0; i<G.vexnum; i++)  //存储顶点的名称   存到顶点数组里
		cin>>G.vexs[i];
	     
	for(int i=0; i<G.vexnum; i++)    //初始化邻接矩阵,每个(i,j)权初始化为零
		for(int j=0; j<G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;

	for(int k=0; k<G.arcnum; k++)     //小于当前的边数
	{
		VertexType v1,v2;            //2个顶点
		cout<<"请输入一条边依附的顶点(2个)"<<endl;
		cin>>v1>>v2;
		int i = LocateVex(v1,G);        //到顶点数组里把 顶点v1位置找到
		int j = LocateVex(v2,G);        //到顶点数组里把 顶点v2位置找到
		G.arcs[i][j].adj = 1;           //把该(i,j)两点之间的权赋值
	}

	return OK;
}

                 /*---------------构造有向网DN-----------------*/
Status CreateDN(MGraph &G)
{
	cout<<"请输入图的顶点数和弧数"<<endl;
	cin>>G.vexnum>>G.arcnum;
	cout<<"构造顶点向量(请依次输入顶点的名称)"<<endl;
	for(int i=0; i<G.vexnum; i++)  //存储顶点的名称   存到顶点数组里
		cin>>G.vexs[i];
	     
	for(int i=0; i<G.vexnum; i++)    //初始化邻接矩阵,每个(i,j)权初始化为零
		for(int j=0; j<G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;

	for(int k=0; k<G.arcnum; k++)     //小于当前的边数
	{
		VertexType v1,v2;            //2个顶点
		int w;                       //2个顶点之间的权
		cout<<"请输入一条边依附的顶点(2个)及带权值(1个)"<<endl;
		cin>>v1>>v2>>w;
		int i = LocateVex(v1,G);        //到顶点数组里把 顶点v1位置找到
		int j = LocateVex(v2,G);        //到顶点数组里把 顶点v2位置找到
		G.arcs[i][j].adj = w;           //把该(i,j)两点之间的权赋值
	}

	return OK;
}

                 /*---------------构造无向图UDG-----------------*/
Status CreateUDG(MGraph &G)
{
	cout<<"请输入图的顶点数和弧数"<<endl;
	cin>>G.vexnum>>G.arcnum;
	cout<<"构造顶点向量(请依次输入顶点的名称)"<<endl;
	for(int i=0; i<G.vexnum; i++)  //存储顶点的名称   存到顶点数组里
		cin>>G.vexs[i];
	     
	for(int i=0; i<G.vexnum; i++)    //初始化邻接矩阵,每个(i,j)权初始化为零
		for(int j=0; j<G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;

	for(int k=0; k<G.arcnum; k++)     //小于当前的边数
	{
		VertexType v1,v2;            //2个顶点
		cout<<"请输入一条边依附的顶点(2个)"<<endl;
		cin>>v1>>v2;
		int i = LocateVex(v1,G);        //到顶点数组里把 顶点v1位置找到
		int j = LocateVex(v2,G);        //到顶点数组里把 顶点v2位置找到
		G.arcs[i][j].adj = 1;           //把该(i,j)两点之间的权赋值
		G.arcs[j][i] = G.arcs[i][j];    //无向网是对称的,所以可以直接赋值  三角矩阵
	}
	return OK;
}

                 /*----------------构造无向网UDN-----------------*/

Status CreateUDN(MGraph &G)
{
	cout<<"请输入图的顶点数和弧数"<<endl;
	cin>>G.vexnum>>G.arcnum;
	cout<<"构造顶点向量(请依次输入顶点的名称)"<<endl;
	for(int i=0; i<G.vexnum; i++)  //存储顶点的名称   存到顶点数组里
		cin>>G.vexs[i];
	     
	for(int i=0; i<G.vexnum; i++)    //初始化邻接矩阵,每个(i,j)权初始化为零
		for(int j=0; j<G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;

	for(int k=0; k<G.arcnum; k++)     //小于当前的边数
	{
		VertexType v1,v2;            //2个顶点
		int w;                       //2个顶点之间的权
		cout<<"请输入一条边依附的顶点(2个)及带权值(1个)"<<endl;
		cin>>v1>>v2>>w;
		int i = LocateVex(v1,G);        //到顶点数组里把 顶点v1位置找到
		int j = LocateVex(v2,G);        //到顶点数组里把 顶点v2位置找到
		G.arcs[i][j].adj = w;           //把该(i,j)两点之间的权赋值
		G.arcs[j][i] = G.arcs[i][j];    //无向网是对称的,所以可以直接赋值  三角矩阵
	}

	return OK;
}//CreateUDN

                /*----------------找到顶点在顶点数组中的位置-------------------*/
int LocateVex(VertexType v,MGraph G)   //把送过来的顶点,找到在顶点数组里的位置
{
	int i;
	for(i=0; v!=G.vexs[i]; i++)     //当在顶点数组里找到与v这个点相同的,则返回该点的位置
		;
	return i;
}

                /*-----------------图的输出----------------------*/
Status Output(MGraph G)
{
	cout<<"-------------------------------图的输出------------------------------------"<<endl;

	cout<<"图的顶点数和边数 :"<<endl;
    cout<<setw(3)<<G.vexnum<<setw(3)<<G.arcnum;
	cout<<endl;

	cout<<"顶点的顶点信息 :"<<endl;      //输出顶点数组
	for(int i=0; i<G.vexnum; i++)
		cout<<G.vexs[i]<<":"<<i<<" ";
	cout<<endl;

	//输出顶点之间的权
	//cout<<"输出顶点之间的权:"<<endl;
	cout<<endl<<"图的邻接矩阵："<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)   
		{
			cout.width(6);
			if(G.arcs[i][j].adj!=INFINITY)   //如果是中间有权,则输出权值
				cout<<G.arcs[i][j].adj;
			else                      //中间无权的话,则输出无穷大∞
				cout<<"∞";
		}
		cout<<endl;
	}
	return OK;
}

                /*-----------------入度数计算--------------------*/
void FindIndegree(MGraph G,int* indegree)   //indegree是存放入度数的数组名
{
	/*
	算法:如果该列的有元素不为无穷大,则是有值的,且是入度
	*/
	for(int i=0; i<G.vexnum; i++)       
	{   
		for(int j=0; j<G.vexnum; j++)
		{
			if(G.arcs[j][i].adj!=INFINITY)     //0,0  1,0  2,0  3,0    一列一列的
				indegree[i]++;
		}
	}
}//FindIndegree

               /*-----------------出度数计算--------------------*/
void FindOutdegree(MGraph G,int* outdegree){
   /*
	算法:如果该行的有元素不为无穷大,则是有值的,且是出度
	*/
	for(int i=0; i<G.vexnum; i++)       
	{
		for(int j=0; j<G.vexnum; j++)
		{
			if(G.arcs[i][j].adj!=INFINITY)       //0,0  0,1  0,2  0,3  一行一行的 
				outdegree[i]++;
		}
	}
   
}//FindOutdegree

              /*-----------------输出度数信息----------------------*/
void GraphDegree(MGraph G){
   int indegree[MAX_VERTEX_NUM]={0},outdegree[MAX_VERTEX_NUM]={0};   //将每个点的出入度数用数组存储,并初始化为0
   int i;
   switch (G.kind){
       	case  DN	:   //有向图无度
        case  DG	:FindIndegree(G,indegree);
			         for (i=0;i<G.vexnum;i++) 
						 cout<<endl<<G.vexs[i]<<"的入度为 "<<indegree[i];
					 cout<<endl;
					 FindOutdegree(G,outdegree);
			         for (i=0;i<G.vexnum;i++) 
						 cout<<endl<<G.vexs[i]<<"的出度为 "<<outdegree[i];
					 break;
       	
       	case  UDN	:  //无向图无度
       	case  UDG	:FindOutdegree(G,outdegree);
			         for (i=0;i<G.vexnum;i++) 
						 cout<<endl<<G.vexs[i]<<"的度为 "<<outdegree[i];
					 break;
   }
    cout<<endl;
}//GraphDegree

               /*-----------深度优先算法----------*/
bool visited[MAX_VERTEX_NUM];
void DFSTraverse(MGraph G)   //循环让那些点进去dfs,深度优先遍历
{
	cout<<"-----------深度优先算法----------"<<endl;
	for(int v=0; v<G.vexnum; v++)
		visited[v] = false;
	for(int v=0; v<G.vexnum; v++)
		DFS(G,v);
}
void DFS(MGraph G,int v)
{
	if(visited[v]==false)
	    cout<<G.vexs[v]<<endl;       //输出顶点数组向量中的v结点	
	visited[v] = true;
	for(int w=0; w<G.vexnum; w++)                           //浏览每一行的每一个点,一行一行的
	{
		if( (G.arcs[v][w].adj!=INFINITY) && !visited[w] )   //当该行的那个点有值,并且是没有输出过的
		    DFS(G,w);
	}
}

              /*-----------广度优先遍历----------*/
LinkQueue Q;
void BFSTraverse(MGraph G)
{
	/*
	*潇氏小算法:从0顶点出发,在访问了0结点之后依次访问0结点未被访问的邻结点,
	然后分别从这些点出发,去访问他们各自的邻接点,访问了的就做标记.
	将需要访问的结点及该节点的邻结点入队,依次出队,出队的同时看看该点的邻接点是否被访问
	*/
	cout<<"---------------广度优先遍历---------------"<<endl;
	for(int i=0; i<G.vexnum; i++)  visited[i] = false;   //先初始化标志数组的每一个为false,未输出
	InitQueue(Q);             //初始化辅助队列,里面为空
	VertexType u = -10;
	for(int i=0; i<G.vexnum; i++)
	{
		if( !(visited[i]) )   //如果是false(未被输出)
		{
			cout<<G.vexs[i]<<endl;    
		    visited[i] = true;   //输出该元素后即刻将该元素的标志数组相应位置置为true
			EnQueue(Q,i);        //将当前元素插入队列
			while( !QueueEmpty(Q) )
			{
				DeQueue(Q,u);    //将队列首元素放到u里面
				for(int j=0; j<G.vexnum; j++)   //再对u元素对应的那一行的所有元素进行遍历
				{
					//如果该位置的元素有值,并且标志数组里该元素没被输出过,则入队列,并输出
					if( G.arcs[u][j].adj!=INFINITY && !visited[j] )  
					{
						visited[j] = true;           //该元素置为true,表示已经输出过了
						cout<<G.vexs[j]<<endl;       
						EnQueue(Q,j);                //入队
					}//if
				}//for
			}//while
		}//if
	}//for
}//BFSTraverse

int main(void)
{
	MGraph G;
	CreateGraph(G);   //构建图
	Output(G);
	ShortestPath_DIJ(G,0);
	system("pause");
	return 0;
}