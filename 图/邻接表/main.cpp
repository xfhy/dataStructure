# include "comdef.h"
# include <iostream>

using namespace std;

typedef  struct ArcNode{      //顶点的一路走过去的路
     int adjvex;              //该弧所指向的顶点位置
     InfoType weight;         //权(默认是int)
     struct ArcNode *nextarc; //指向下一个顶点的位置
}ArcNode;

typedef struct Vnode{          //顶点
      VertexType  data;        //顶点信息(默认是char)
      ArcNode      *firstarc;  //指向第一个依附该顶点的指针
}VNode, AdjList[MAX_VERTEX_NUM ];    //这是结构体数组,没见过吧,哈哈 

typedef struct {               //图
       AdjList   vertices;     //一维数组,存的是每个顶点的指向
       int  vexnum;            //顶点数
	   int  arcnum;            //弧数
       GraphKind kind;         //图的种类标志
}ALGraph;

Status CreateGraph(ALGraph &G);  //创建图的菜单
int LocateVex(ALGraph G,VertexType v);  //查找该点在顶点数组里的位置
Status CreateDG(ALGraph &G);   //有向图的创建
Status CreateDN(ALGraph &G);   //有向网的创建
Status CreateUDG(ALGraph &G);  //无向图的创建
Status CreateUDN(ALGraph &G);  //无向网的创建
Status PrintGraph(ALGraph G);  //邻接表的输出
void DFSTraverse(ALGraph G);
void DFS(ALGraph G,int v);

              /*------------------创建图的菜单--------------------*/
Status CreateGraph(ALGraph &G){
   int kind;
   cout<<endl<<"输入图的类型：0-DG,1-DN,2-UDG,3-UDN:"<<endl;
   cin>>kind;
   G.kind=(GraphKind)kind;
   switch (G.kind){
       	case  DG	:return CreateDG(G);
       	case  DN	:return CreateDN(G); 
       	case  UDG	:return CreateUDG(G);
       	case  UDN	:return CreateUDN(G);
       	default 	:return ERROR;
   }
}//CreateGraph

              /*--------------查找该点在顶点数组里的位置----------*/
int LocateVex(ALGraph G,VertexType v)
{
	int i;
	for(i=0; G.vertices[i].data!=v; i++)   //当在顶点数组里查询时,未找到时就继续查找
		;
	return i;
}

             /*----------------有向图的创建DG------------*/
Status CreateDG(ALGraph &G)
{
	/*
	潇氏小算法:输入顶点,边数,和顶点信息(即顶点的内容和指向为NULL),再循环输入边的信息,即v1,v2,w;边1到边2的权;
	有向图这里权为1
	这是无向网,所以有G.vertices[i].firstarc,也有G.vertices[j].firstarc,双向的.
	*/
	cout<<"请输入顶点数,弧数"<<endl;
	cin>>G.vexnum>>G.arcnum;

	VertexType v1,v2;  //2条临时边
	ArcNode *p,*q;    //需要生产两个结点,i到j,j到i

	cout<<"请输入顶点内容(char):"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}

	for(int k=0; k<G.arcnum; k++)   //最长不超过弧数
	{
		 cout<<"请输入v1,v2"<<endl;
		 cin>>v1>>v2;
		 int i,j;
		 i = LocateVex(G,v1);
		 j = LocateVex(G,v2);
		 p = (ArcNode *)malloc(sizeof(ArcNode));
		 p->adjvex = j;    //指向的顶点位置
		 p->weight = 1;    //权
		 p->nextarc = G.vertices[i].firstarc;
		 G.vertices[i].firstarc = p;
	}
	return OK;
}//CreateUDN

             /*----------------有向网的创建DN------------*/
Status CreateDN(ALGraph &G)
{
	/*
	潇氏小算法:输入顶点,边数,和顶点信息(即顶点的内容和指向为NULL),再循环输入边的信息,即v1,v2,w;边1到边2的权;
	这是无向网,所以有G.vertices[i].firstarc,也有G.vertices[j].firstarc,双向的.
	*/
	cout<<"请输入顶点数,弧数"<<endl;
	cin>>G.vexnum>>G.arcnum;

	VertexType v1,v2;  //2条临时边
	InfoType w;        //临时权
	ArcNode *p,*q;    //需要生产两个结点,i到j,j到i

	cout<<"请输入顶点内容(char):"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}

	for(int k=0; k<G.arcnum; k++)   //最长不超过弧数
	{
		 cout<<"请输入v1,v2,w"<<endl;
		 cin>>v1>>v2>>w;
		 int i,j;
		 i = LocateVex(G,v1);
		 j = LocateVex(G,v2);
		 p = (ArcNode *)malloc(sizeof(ArcNode));
		 p->adjvex = j;
		 p->weight = w;
		 p->nextarc = G.vertices[i].firstarc;
		 G.vertices[i].firstarc = p;
	}
	return OK;
}//CreateUDN

             /*----------------无向图的创建UDG------------*/
Status CreateUDG(ALGraph &G)
{
	/*
	潇氏小算法:输入顶点,边数,和顶点信息(即顶点的内容和指向为NULL),再循环输入边的信息,即v1,v2,w;边1到边2的权;
	无向图这里权为1
	这是无向网,所以有G.vertices[i].firstarc,也有G.vertices[j].firstarc,双向的.
	*/
	cout<<"请输入顶点数,弧数"<<endl;
	cin>>G.vexnum>>G.arcnum;

	VertexType v1,v2;  //2条临时边
	ArcNode *p,*q;    //需要生产两个结点,i到j,j到i

	cout<<"请输入顶点内容(char):"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}

	for(int k=0; k<G.arcnum; k++)   //最长不超过弧数
	{
		 cout<<"请输入v1,v2"<<endl;
		 cin>>v1>>v2;
		 int i,j;
		 i = LocateVex(G,v1);
		 j = LocateVex(G,v2);
		 p = (ArcNode *)malloc(sizeof(ArcNode));
		 p->adjvex = j;
		 p->weight = 1;
		 p->nextarc = G.vertices[i].firstarc;
		 G.vertices[i].firstarc = p;

		 q = (ArcNode *)malloc(sizeof(ArcNode));
		 q->adjvex = i;
		 q->weight = 1;
		 q->nextarc = G.vertices[j].firstarc;
		 G.vertices[j].firstarc = q;
	}
	return OK;
}//CreateUDN

             /*----------------无向网的创建UDN------------*/
Status CreateUDN(ALGraph &G)
{
	/*
	潇氏小算法:输入顶点,边数,和顶点信息(即顶点的内容和指向为NULL),再循环输入边的信息,即v1,v2,w;边1到边2的权;
	这是无向网,所以有G.vertices[i].firstarc,也有G.vertices[j].firstarc,双向的.
	*/
	cout<<"请输入顶点数,弧数"<<endl;
	cin>>G.vexnum>>G.arcnum;

	VertexType v1,v2;  //2条临时边
	InfoType w;        //临时权
	ArcNode *p,*q;    //需要生产两个结点,i到j,j到i

	cout<<"请输入顶点内容(char):"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}

	for(int k=0; k<G.arcnum; k++)   //最长不超过弧数
	{
		 cout<<"请输入v1,v2,w"<<endl;
		 cin>>v1>>v2>>w;
		 int i,j;
		 i = LocateVex(G,v1);
		 j = LocateVex(G,v2);
		 p = (ArcNode *)malloc(sizeof(ArcNode));
		 p->adjvex = j;
		 p->weight = w;
		 p->nextarc = G.vertices[i].firstarc;
		 G.vertices[i].firstarc = p;

		 q = (ArcNode *)malloc(sizeof(ArcNode));
		 q->adjvex = i;
		 q->weight = w;
		 q->nextarc = G.vertices[j].firstarc;
		 G.vertices[j].firstarc = q;
	}
	return OK;
}//CreateUDN

           /*-----------入度的计算------------*/
void FindIndegree(ALGraph G,int* indegree)
{
   //将顶点数组里的每一个顶点的入度数存到indegree数组里    
	//遍历每一行,在遍历的同时遇到不是顶点的那个点,则将这个
	//这个位置的相应的indegree数组里加1
	ArcNode *p;
	int j=0;
	for(int i=0; i<G.vexnum; i++)    //顶点个数之内            
	{
		for(p=G.vertices[i].firstarc; p; p = p->nextarc)   //vertices:一维数组,存的是每个顶点的指向
		{
			indegree[p->adjvex]++;
		}
	}
}//FindIndegree

          /*-----------出度的计算-------------*/
void FindOutdegree(ALGraph G,int* outdegree)
{
	//将顶点数组里的每一个顶点的入度数存到indegree数组里	扫描顶点数组的每一行,看有多少个结点,则有多少个出度
   ArcNode *p;
   for(int i=0; i<G.vexnum; i++)
   {
	   p = G.vertices[i].firstarc;
	   while(p)
	   {
		   p = p->nextarc;
		   outdegree[i]++;
	   }
   }
}//FindOutdegree

          /*-----------出入度的统计输出---------*/
void GraphDegree(ALGraph G){
   int indegree[MAX_VERTEX_NUM]={0},outdegree[MAX_VERTEX_NUM]={0};
   int i;
   switch (G.kind){
       	case  DN	:
        case  DG	:FindIndegree(G,indegree);
			         for (i=0;i<G.vexnum;i++) 
						 cout<<endl<<G.vertices[i].data<<"的入度为 "<<indegree[i];
					 cout<<endl;
					 FindOutdegree(G,outdegree);
			         for (i=0;i<G.vexnum;i++) 
						 cout<<endl<<G.vertices[i].data<<"的出度为 "<<outdegree[i];
					 break;
       	
       	case  UDN	:
       	case  UDG	:FindOutdegree(G,outdegree);
			         for (i=0;i<G.vexnum;i++) 
						 cout<<endl<<G.vertices[i].data<<"的度为 "<<outdegree[i];
					 break;
   }
  cout<<endl;
}//GraphDegree

            /*----------------邻接表的输出-------------*/
Status PrintGraph(ALGraph G)
{
	cout<<"\t\t--------邻接表的输出----------"<<endl;
	ArcNode *p;
	cout<<"图的顶点数和弧数 :";
	cout<<G.vexnum<<",";
	cout<<G.arcnum<<endl;

	cout<<endl;
	cout<<"图的顶点信息 :"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		cout<<G.vertices[i].data;
	}

	cout<<endl;
	cout<<"图的邻接表 :"<<endl;
	for(int i=0; i<G.vexnum; i++)
	{
		cout<<G.vertices[i].data<<"的邻接点为:"<<endl;
		p = G.vertices[i].firstarc;
		while(p)
		{
			//p->adjvex指向的顶点位置
			cout<<G.vertices[p->adjvex].data<<endl;
			p = p->nextarc;
		}
		cout<<endl;
	}
	cout<<endl;
	return OK;
}

bool visited[MAX_VERTEX_NUM];
void DFSTraverse(ALGraph G)   //循环让那些点进去dfs,深度优先遍历
{
	cout<<"-----------深度优先算法----------"<<endl;
	for(int v=0; v<G.vexnum; v++)
		visited[v] = false;
	for(int v=0; v<G.vexnum; v++)
		DFS(G,v);
}
void DFS(ALGraph G,int v)
{
	if(visited[v]==false)
		cout<<G.vertices[v].data<<endl;       //输出顶点数组向量中的v结点	
	ArcNode *p;
	visited[v] = true;
	for(p = G.vertices[v].firstarc; p; p = p->nextarc)        //浏览每一行的每一个点,一行一行的
	{
		int w = p->adjvex;     //这是这一行的下一个结点的位置
		if( !visited[w] )
			DFS(G,w);
	}
}

int main(void)
{
	ALGraph G;
	CreateGraph(G);
	GraphDegree(G);
	PrintGraph(G);
	//DFSTraverse(G);
	system("pause");
	return 0;
}