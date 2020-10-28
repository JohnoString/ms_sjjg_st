// jcpx
#if 0
#include <iostream>
#include <cassert>
using namespace std;

// kp {4 1 7 6 9 2 8 0 3 5} 
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
/*
 * 获取数组a中最大值
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
 */
int get_max(int a[], int n)
{
	int i, max;

	max = a[0];
	for (i = 1; i < n; i++)
		if (a[i] > max)
			max = a[i];
	return max;
}

/*
 * 对数组按照"某个位数"进行排序(桶排序)
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
 *     exp -- 指数。对数组a按照该指数进行排序。
 *
 * 例如，对于数组a={50, 3, 542, 745, 2014, 154, 63, 616}；
 *    (01) 当exp=1表示按照"个位"对数组a进行排序
 *    (02) 当exp=10表示按照"十位"对数组a进行排序
 *    (03) 当exp=100表示按照"百位"对数组a进行排序
 *    ...
 */

#include <vector>
using namespace std;

void count_sort(int a[], int n, int exp)
{
	vector<int> output;
	output.resize(10);// 存储"被排序数据"的临时数组
	int i, buckets[10] = { 0 };

	// 将数据出现的次数存储在buckets[]中
	for (i = 0; i < n; i++)
		buckets[(a[i] / exp) % 10]++;

	// 更改buckets[i]。目的是让更改后的buckets[i]的值，是该数据在output[]中的位置。
	for (i = 1; i < 10; i++)
		buckets[i] += buckets[i - 1];

	//算法优化
	//	在算法的原理中，我们是以一张二维数组的表来存储这些无序的元素。使用二维数组有一个很明显的不足就是二维数组太过稀疏。数组的利用率为 10 % 。
	//	在寻求优化的路上，我们想到一种可以压缩空间的方法，且时间复杂度并没有偏离得太厉害。那就是设计了两个辅助数组，一个是 count[]，一个是 bucket[]。count 用于记录在某个桶中的最后一个元素的下标，然后再把原数组中的元素计算一下它应该属于哪个“桶”，并修改相应位置的 count 值。直到最大数的最高位也被添加到桶中，或者说，当所有的元素都被被在第 0 个桶中，基数排序就结束了。
	// 将数据存储到临时数组output[]中  优化版本
	for (i = n - 1; i >= 0; i--)
	{
		output[buckets[(a[i] / exp) % 10] - 1] = a[i];
		buckets[(a[i] / exp) % 10]--;
	}

	// 将排序好的数据赋值给a[]
	for (i = 0; i < n; i++)
		a[i] = output[i];
}

/*
 * 基数排序
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
 */
void radix_sort(int a[], int n)
{
	int exp;    // 指数。当对数组按各位进行排序时，exp=1；按十位进行排序时，exp=10；...
	int max = get_max(a, n);    // 数组a中的最大值

	// 从个位开始，对数组a按"指数"进行排序
	for (exp = 1; max / exp > 0; exp *= 10)
		count_sort(a, n, exp);
}

// guibing
/*
基本思想：利用归并的思想实现的排序算法，该算法采用经典的分治策略。分治法分为两个阶段，首先是分阶段，分阶段将问题分成一系列小的问题然后进行递归求解，然后是治阶段，治阶段将分阶段得到的各个答案“修补”在一起，这就是分而治之。
时间复杂度：O(nlogn)
空间复杂度：O(N)，归并排序需要一个与原数组相同长度的数组做辅助来排序
稳定性：归并排序是稳定的排序算法，temp[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];这行代码可以保证当左右两部分的值相等的时候，先复制左边的值，这样可以保证值相等的时候两个元素的相对位置不变。
*/

// wp
/*
多路归并排序算法的过程大致为：
1）：首先将k个归并段中的首元素关键字依次存入b[0]--b[k-1]的叶子结点空间里，然后调用CreateLoserTree创建败者树，创建完毕之后最小的关键字下标（即所在归并段的序号）便被存入ls[0]中。然后不断循环：
2）把ls[0]所存最小关键字来自于哪个归并段的序号得到为q，将该归并段的首元素输出到有序归并段里，然后把下一个元素关键字放入上一个元素本来所 在的叶子结点b[q]中，调用Adjust顺着b[q]这个叶子结点往
上调整败者树直到新的最小的关键字被选出来，其下标同样存在ls[0]中。循环这个 操作过程直至所有元素被写到有序归并段里。

胜者树
败者树
*/

int main()
{
	int arr[10] = { 4, 1, 7, 6, 9, 2, 8, 0, 3, 5 };
	
	// kp
	//QuickSortNotR(arr, 0, 9);
	
	// dp
	//int size = sizeof(arr) / sizeof(int);
	//printf("%d \n", size);
	//printf("排序前数组：");
	//for (int i = 0; i < size; i++) {
	//	printf("%d ", arr[i]);
	//}
	//printf("\n");
	//heapSort(arr, size);
	// tp

	// jspx
	radix_sort(arr, 10);
	for (auto i : arr)
	{
		cout << i << ",";
	}

	cout << endl;
	return 0;
}
#endif
