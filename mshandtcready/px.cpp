// jcpx
#if 0
#include <iostream>
#include <cassert>
using namespace std;

// cp {4 1 7 6 9 2 8 0 3 5} 
int SubSort(int* arr, int left, int right)
{
	int tmp = arr[right];
	while (left < right)
	{
		while (left < right && arr[left] <= tmp)  //因为有可能有相同的值，防止越界，所以加上left < right
		{
			++left;
		}

		arr[right] = arr[left];

		while (left < right && arr[right] >= tmp)
		{
			--right;
		}
		
		arr[left] = arr[right];
	}

	arr[right] = tmp;

	return left;
}

void QuickSort(int* arr, int left, int right)
{
	if (nullptr == arr)
	{
		return;
	}

	if (left >= right)                        //表示已经完成一个组
	{
		return;
	}

	int index = SubSort(arr, left, right);    //枢轴的位置
	QuickSort(arr, left, index - 1);
	QuickSort(arr, index + 1, right);
}

#include <stack>
void QuickSortNotR(int* array, int left, int right)
{
	assert(array);
	stack<int> s;
	s.push(left);
	s.push(right);                            //后入的right，所以要先拿right
	while (!s.empty())                          //栈不为空
	{
		int right = s.top();
		s.pop();
		int left = s.top();
		s.pop();

		int index = SubSort(array, left, right);
		if ((index - 1) > left)                //左子序列
		{
			s.push(left);
			s.push(index - 1);
		}
		if ((index + 1) < right)               //右子序列
		{
			s.push(index + 1);
			s.push(right);
		}
	}
}

// dp
#include <stdio.h>

void swap(int array[], int x, int y) {
	int key;
	key = array[x];
	array[x] = array[y];
	array[y] = key;
}

//从小到大排序
void Down(int array[], int i, int n) {						//最后结果就是大顶堆 
	int parent = i;										//父节点下标
	int child = 2 * i + 1;									//子节点下标  
	while (child < n) {
		if (child + 1 < n && array[child] < array[child + 1]) {	//判断子节点那个大，大的与父节点比较 
			child++;
		}

		if (array[parent] < array[child]) {				//判断父节点是否小于子节点 
			swap(array, parent, child);					//交换父节点和子节点 
			parent = child;								//子节点下标 赋给 父节点下标 
		}

		child = child * 2 + 1;								//换行，比较下面的父节点和子节点 
	}
}

void BuildHeap(int array[], int size)
{
	int i = 0;												//倒数第二排开始 
	for (i = size / 2 - 1; i >= 0; i--) {							//创建大顶堆，必须从下往上比较 
		Down(array, i, size);								//否则有的不符合大顶堆定义 
	}
}

void heapSort(int array[], int size) {
	BuildHeap(array, size);								//初始化堆 
	printf("初始化数组：");
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	for (int i = size - 1; i > 0; i--)
	{
		swap(array, 0, i);								//交换顶点和第 i 个数据 
		//因为只有array[0]改变，其它都符合大顶堆的定义，所以可以从上往下重新建立 
		Down(array, 0, i);								//重新建立大顶堆 

		printf("排序的数组：");
		for (int i = 0; i < size; i++) {
			printf("%d ", array[i]);
		}
		printf("\n");
	}
}

// tp
//设置一个定量的数组当作空桶；
//遍历输入数据，并且把数据一个一个放到对应的桶里去(数据的最高位跟数组索引保持一致)；
//对每个不是空的桶进行排序；
//从不是空的桶里把排好序的数据拼接起来。

// 问题 top10
	// ①
	// ②找出top10
		// 算法二：部分排序
		// 题目要求是求出Top 10，因此我们没有必要对所有的Query都进行排序，我们只需要维护一个10个大小的数组，初始化放入10个Query，
		// 按照每个Query的统计次数由大到小排序，然后遍历这300万条记录，每读一条记录就和数组最后一个Query对比，如果小于这个Query，
		// 那么继续遍历，否则，将数组中最后一条数据淘汰，加入当前的Query, 移动保证有序。最后当所有的数据都遍历完毕之后，那么这个数组中的10个Query便是我们要找的Top10了。
		// 不难分析出，这样，算法的最坏时间复杂度是N * K， 其中K是指top多少。
		// 算法三：堆
		// 在算法二中，我们已经将时间复杂度由NlogN优化到NK，不得不说这是一个比较大的改进了，可是有没有更好的办法呢？
		// 分析一下，在算法二中，每次比较完成之后，需要的操作复杂度都是K，因为要把元素插入到一个线性表之中，而且采用的是顺序比较。这里我们注意一下，该数组是有序的，一次我们每次查找的时候可以采用二分的方法查找，这样操作的复杂度就降到了logK，可是，随之而来的问题就是数据移动，因为移动数据次数增多了。不过，这个算法还是比算法二有了改进。
		// 基于以上的分析，我们想想，有没有一种既能快速查找，又能快速移动元素的数据结构呢？回答是肯定的，那就是堆。
		// 借助堆结构，我们可以在log量级的时间内查找和调整 / 移动。因此到这里，我们的算法可以改进为这样，维护一个K(该题目中是10)大小的小根堆，然后遍历300万的Query，分别和根元素进行对比。
		// 思想与上述算法二一致，只是算法在算法三，我们采用了最小堆这种数据结构代替数组，把查找目标元素的时间复杂度有O（K）降到了O（logK）。
		// 那么这样，采用堆数据结构，算法三，最终的时间复杂度就降到了N‘logK，和算法二相比，又有了比较大的改进。
		// 总结：
		// 至此，算法就完全结束了，经过上述第一步、先用Hash表统计每个Query出现的次数，O（N）；然后第二步、采用堆数据结构找出Top 10，N * O（logK）。所以，我们最终的时间复杂度是：O（N） + N’ * O（logK）。（N为1000万，N’为300万）。如果各位有什么更好的算法，欢迎留言评论。第一部分，完。

// jspx
//基数排序是按照低位先排序，然后收集；再按照高位排序，然后再收集；依次类推，直到最高位。有时候有些属性是有优先级顺序的，先按低优先级排序，再按高优先级排序。最后的次序就是高优先级高的在前，高优先级相同的低优先级高的在前。

// wp

int main()
{
	int arr[10] = { 4, 1, 7, 6, 9, 2, 8, 0, 3, 5 };
	
	// kp
	//QuickSortNotR(arr, 0, 9);
	
	// dp
	int size = sizeof(arr) / sizeof(int);
	printf("%d \n", size);
	printf("排序前数组：");
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	heapSort(arr, size);
	// tp

	for (auto i : arr)
	{
		cout << i << ",";
	}

	cout << endl;
	return 0;
}
#endif
