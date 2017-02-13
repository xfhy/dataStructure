# include "comdef.h"
# include <iostream>
# include "Queue.h"   //引入队列

         /*-------------先序遍历----------*/
void preorder1(BiTree T)    //BiTree是结构体指针
{
	if(T)         //如果还能往下
	{
		cout<<T->data<<endl;            //输出该节点的值    先序遍历
		preorder1(T->lchild);     //从该节点往左孩子方向探索指针
		preorder1(T->rchild);
	}
}

        /*-------------中序遍历----------*/
void preorder2(BiTree T)
{
	if(T)         //如果还能往下
	{
		preorder2(T->lchild);     //从该节点往左孩子方向探索指针
		cout<<T->data<<endl;     //中序遍历        
		preorder2(T->rchild);
	}
}

        /*-------------后序遍历----------*/
void preorder3(BiTree T)
{
	if(T)         //如果还能往下
	{
		preorder3(T->lchild);     //从该节点往左孩子方向探索指针  
		preorder3(T->rchild);
		cout<<T->data<<endl;      //后续遍历
	}
}

                /*-------------------先序存储建立二叉树 -----------------*/
//必须是先序,必须输入正确,这里需要输入int类型的结点数据
Status CreateBiTree(BiTree &T)
{
	//按先序次序输入二叉树中节点的值,(一个字符),空格字符表示空数
	//构造二叉链表表示的二叉树T	
	TElemType ch;    //TElemType 是 int 类型的
	cin>>ch;
	if(ch=='#')      //当输入-1时,则该节点就不再输入值,不再创建空间
		T=NULL;
	else
	{
		if(!(T=(BiTree)malloc(sizeof(BiTNode))))     //生成存放结点的内存空间
			exit(OVERFLOW);
		T->data = ch;            //该节点 
		CreateBiTree(T->lchild); //左孩子
		CreateBiTree(T->rchild); //右孩子
	}
	return OK; 
}

                /*------------------以二叉排序树的方式存储二叉树---------*/ 
//二叉排序树,如果是以中序输出,则输出时已经排好序,该函数只负责将数值插入到合适的位置
void insert(BiTree &T,TElemType x)    //这里的 x 为 int 类型,x表示需要插入的值
{
	if(T==NULL)   //如果为空的话,则插入第一个结点,且左右孩子置为空
	{
		T = (BiTree)malloc( sizeof(BiTNode) ); 
		T->data = x;
		T->lchild = T->rchild = NULL;   //先把左右孩子指针置为空
	}
	else   //小->左   大->右
	{
		if( x <= T->data )         //当需要插入的值小于当前节点的值,则沿着该节点左孩子方向继续寻找合适位置
			insert(T->lchild,x);  
		else
			insert(T->rchild,x);  
	}
}
//可以任意输入  
void CreateBiTree2(BiTree &root)
{
	root = NULL;    //最开始时将根置为空
	TElemType x;    //结点数据类型为int
	cin>>x;
	while(x!=-1)
	{
		insert(root,x);   //及时把用户输入的值插到排序二叉树里
		cin>>x;
	}
}

                 /*-----------------------二叉树的层次遍历--------------------*/
LinkQueue Q;
Status LevelOrder(BiTree T)
{
	/*
	*当输出该行的一个结点时,及时将下一行的这个结点的子孩子插入队列尾部.
	于是该行遍历完后,下一行的所有结点已插入队列尾部
	*/
	InitQueue(Q);      //这是初始化队列
	BiTree b=NULL;     //这是一个指针
	if(T)
	{
		EnQueue(Q,T);   //队列存的是指针
		while(!QueueEmpty(Q))    //判断队列是否为空
		{
			DeQueue(Q,b);       //出队列到b这个指针里
			cout<<b->data<<endl;
			if(b->lchild)       //判断b 的左孩子是否存在,如果存在则循环去输出左孩子,插入到队列
			   EnQueue(Q,b->lchild);   //将左孩子插入队列
			if(b->rchild)    //判断b 的右孩子是否存在,如果存在则循环去(及时)输出左孩子
				EnQueue(Q,b->rchild);   
		}
	}
	return OK;
}

              /*-----------------计算二叉树的高度--------------------------*/
int tree_depth(BiTree T)
{
	int h=0,lh=0,rh=0;  //总长
	if(!T)  //如果为空
		h=0;
	else{
		lh = tree_depth(T->lchild);   //左边的高度
		rh = tree_depth(T->rchild);   //右边的高度
		if(lh>=rh)         //左边高度大于右边高度
			h = lh+1;      //高度要加上自己的这一层
		else
			h = rh+1;
	}
	return h;
}

             /*-----------------交换二叉树的左右子树-----------------------*/
void change_lr(BiTree T)   //当然,有递归
{
	if(T)
	{
		change_lr(T->lchild);         //向左递归
		change_lr(T->rchild);         //向右递归
		
		    /*-------交换二叉树的左右指针-------*/
		BiTree temp;     //这是一个存储二叉树结构的指针
		temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = temp;
	}
}

             /*-----------------计算总结点的数目------------------------------*/
/*
当T不为空,依次递归下去,不停的计算自己的左结点加右结点再加上自己    f(左)+f(右)+1
*/
int count_n(BiTree T)
{
	int num=0,num1=0,num2=0;   //总,左,右
	if(!T)   //如果为空,num=0
		;
	else
	{
		num1 = count_n(T->lchild);      //递归下去计算左指针那一坨的结点数
		num2 = count_n(T->rchild);      //递归下去计算右指针那一坨的结点数
		num = num1 + num2 + 1;           //总结点数 = 左边的结点数 + 右边的结点数
	}
	return num;
}

            /*-----------------计算叶子总数----------------------------------*/
int count_n0(BiTree T)
{
	int num=0,num1=0,num2=0;
	if(!T)                                         // T为空
		num=0;
	else if(T->lchild==NULL && T->rchild==NULL)   //T只有一个结点   则叶子数为1
		num=1;
	else
	{
		num1 = count_n0(T->lchild);               //计算左边的那一坨的叶子数
		num2 = count_n0(T->rchild);               //计算右边的那一坨的叶子数
		num = num1 + num2;                        //左边加右边等于总数
	}
	return num;
}

            /*-----------------计算单支数的数量-----------------------------*/
int count_n1(BiTree T)
{
	int num = 0, num1 = 0, num2 = 0;   //总,左,右    单支数
	if(!T)    //这是递归的出口
		;
	else
	{
		num1 = count_n1(T->lchild);     //向左递归,不断的寻找单支数
		num2 = count_n1(T->rchild);     //向右递归,不断的寻找单支数
		//当结点的左孩子非空,右孩子为空,则该结点为单支数,左边的那一坨加一个单支数
		if( T->lchild!=NULL && T->rchild==NULL )
		    num1++;
		//当结点的左孩子为空,右孩子非空,则该结点为单支数,右边的那一坨加一个单支数
		if( T->lchild==NULL && T->rchild!=NULL )        
	        num2++;
		num = num1 + num2;
	}
	return num;
}

            /*-----------------计算双支结点数的数量-----------------------------*/
            
int count_n2(BiTree T)
{
	int num=0,num1=0,num2=0;
	if(!T || (T->lchild==NULL && T->rchild==NULL))   //T为空,    或者T没有孩子
		num=0;
	else
	{
		if(!T->lchild)        //左孩子为空,只有右孩子
			num = count_n2(T->rchild);
		else if(!T->rchild)  //右孩子为空,只有左孩子
			num = count_n2(T->lchild);
		else
			num = count_n2(T->lchild) + count_n2(T->rchild) + 1;
	}
	return num;
}

           /*------------------计算所有的二叉树的相关信息------------------------*/
void count(BiTree T,int &n0,int &n1,int &n2,int &n)   //叶子数,单支数,双支数,总结点的数
{
	if(T)
	{
	    n++;                       //当进来的时候有结点,则结点数+1
		if(T->lchild==NULL && T->rchild==NULL)    //当左右都没有孩子,则是叶子,+1
			n0++;
		if( (T->lchild!=NULL && T->rchild==NULL) || (T->lchild==NULL && T->rchild!=NULL) )  //当只有1边有孩子,则单支数+1 
			n1++;
		if(T->lchild!=NULL && T->rchild!=NULL)   //当左右都有孩子,则双支数=1
			n2++;
		count(T->lchild,n0,n1,n2,n);       //继续往左递归
		count(T->rchild,n0,n1,n2,n);       //继续往右递归
	}
}

int main(void)
{
	BiTree T=NULL;

	
	cout<<"a. 先序存储建立二叉树"<<endl;
	CreateBiTree(T);

	int num1 = count_n1(T);
	cout<<"单支结点数"<<num1<<endl;

    int num = count_n2(T);
	cout<<"双支结点数"<<num<<endl;

	//cout<<"b. 二叉树的层次遍历"<<endl;
	//LevelOrder(T);

	/*cout<<"c. 先序遍历"<<endl;
	preorder1(T);
	cout<<"d. 中序遍历"<<endl;
	preorder2(T);
	cout<<"e. 后序遍历"<<endl;
	preorder3(T);*/

	

	/*
	int h = tree_depth(T);
	cout<<"树高度为"<<h<<endl;
	*/

	/*
	cout<<"交换二叉树的左右子树"<<endl;
	change_lr(T);
	cout<<"二叉树的层次遍历"<<endl;
	LevelOrder(T);*/

	/*
	cout<<"f. 通过单个函数计算相应的点子数"<<endl;
	int n0 = count_n0(T);
	cout<<"叶子数为"<<n0<<endl;

	int n1 = count_n1(T);
	cout<<"单支数数目为"<<n1<<endl;

	int n2 = count_n2(T);
	cout<<"双支数数目为"<<n2<<endl;

	int n = count_n(T);
	cout<<"结点总数目为"<<n<<endl;*/

	cout<<endl;
	cout<<"g. 通过一个函数计算所有的点子数"<<endl;
	int a[4] = {0};
	count(T,a[0],a[1],a[2],a[3]);   //计算所有的点子数
	
	cout<<"叶子数为"<<a[0]<<endl;
	cout<<"单支数数目为"<<a[1]<<endl;
	cout<<"双支数数目为"<<a[2]<<endl;
	cout<<"结点总数目为"<<a[3]<<endl;

	/*
	cout<<"a. 建立一棵二叉排序树"<<endl;
	CreateBiTree2(T);    //建立一棵二叉排序树
	cout<<"b. 先序遍历"<<endl;
	preorder1(T);
	cout<<"c. 中序遍历"<<endl;
	preorder2(T);
	cout<<"d. 后序遍历"<<endl;
	preorder3(T);*/

	/*cout<<"a. 建立一棵二叉排序树"<<endl;
	CreateBiTree2(T);    //建立一棵二叉排序树
	cout<<"b. 二叉树的层次遍历"<<endl;
	LevelOrder(T);*/
	system("pause");
	return 0;
}