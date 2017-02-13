     /*--------------快速排序---------------*/
//快速排序的一趟循环
//算法：将一个数，比它小的放到该数的前面，比它大的放到该数的后面
int Partition(SqList &L,int low,int high)
{
	ElemType pivotkey = L.elem[low];    //基准数
	while(low<high)  //快速将元素放到适当的位置（前小后大）
	{
		while( (low <high) && (L.elem[high]>=pivotkey) )
			high--;    //从 后往前循环，遇到比pivotkey小的，就把该值放到前面去
		L.elem[low] = L.elem[high];       //退出循环时，L.elem[high]<=pivotkey
	    while( (low<high)&& (L.elem[low]<=pivotkey) )
			low++;
		L.elem[high] = L.elem[low];       //退出循环时，L.elem[low]>=pivotkey
	}
	L.elem[low] = pivotkey;     //回归

	return low;
}
//快速排序
void QSort(SqList &L,int low,int high)   
{
	int pivotloc;
	if(low<high)
	{
		pivotloc  = Partition(L,low,high);    //这里pivotloc是某个元素的位置
		QSort(L,low,pivotloc-1);   //从pivotloc的位置一直（递归）到low=pivotloc-1   终止
		QSort(L,pivotloc+1,high);  ///从pivotloc的位置一直（递归）到pivotloc+1=high   终止
	}
}