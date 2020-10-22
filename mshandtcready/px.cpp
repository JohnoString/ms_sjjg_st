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
		while (left < right && arr[left] <= tmp)  //��Ϊ�п�������ͬ��ֵ����ֹԽ�磬���Լ���left < right
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

	if (left >= right)                        //��ʾ�Ѿ����һ����
	{
		return;
	}

	int index = SubSort(arr, left, right);    //�����λ��
	QuickSort(arr, left, index - 1);
	QuickSort(arr, index + 1, right);
}

#include <stack>
void QuickSortNotR(int* array, int left, int right)
{
	assert(array);
	stack<int> s;
	s.push(left);
	s.push(right);                            //�����right������Ҫ����right
	while (!s.empty())                          //ջ��Ϊ��
	{
		int right = s.top();
		s.pop();
		int left = s.top();
		s.pop();

		int index = SubSort(array, left, right);
		if ((index - 1) > left)                //��������
		{
			s.push(left);
			s.push(index - 1);
		}
		if ((index + 1) < right)               //��������
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

//��С��������
void Down(int array[], int i, int n) {						//��������Ǵ󶥶� 
	int parent = i;										//���ڵ��±�
	int child = 2 * i + 1;									//�ӽڵ��±�  
	while (child < n) {
		if (child + 1 < n && array[child] < array[child + 1]) {	//�ж��ӽڵ��Ǹ��󣬴���븸�ڵ�Ƚ� 
			child++;
		}

		if (array[parent] < array[child]) {				//�жϸ��ڵ��Ƿ�С���ӽڵ� 
			swap(array, parent, child);					//�������ڵ���ӽڵ� 
			parent = child;								//�ӽڵ��±� ���� ���ڵ��±� 
		}

		child = child * 2 + 1;								//���У��Ƚ�����ĸ��ڵ���ӽڵ� 
	}
}

void BuildHeap(int array[], int size)
{
	int i = 0;												//�����ڶ��ſ�ʼ 
	for (i = size / 2 - 1; i >= 0; i--) {							//�����󶥶ѣ�����������ϱȽ� 
		Down(array, i, size);								//�����еĲ����ϴ󶥶Ѷ��� 
	}
}

void heapSort(int array[], int size) {
	BuildHeap(array, size);								//��ʼ���� 
	printf("��ʼ�����飺");
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	for (int i = size - 1; i > 0; i--)
	{
		swap(array, 0, i);								//��������͵� i ������ 
		//��Ϊֻ��array[0]�ı䣬���������ϴ󶥶ѵĶ��壬���Կ��Դ����������½��� 
		Down(array, 0, i);								//���½����󶥶� 

		printf("��������飺");
		for (int i = 0; i < size; i++) {
			printf("%d ", array[i]);
		}
		printf("\n");
	}
}

// tp
//����һ�����������鵱����Ͱ��
//�����������ݣ����Ұ�����һ��һ���ŵ���Ӧ��Ͱ��ȥ(���ݵ����λ��������������һ��)��
//��ÿ�����ǿյ�Ͱ��������
//�Ӳ��ǿյ�Ͱ����ź��������ƴ��������

// ���� top10
	// ��
	// ���ҳ�top10
		// �㷨������������
		// ��ĿҪ�������Top 10���������û�б�Ҫ�����е�Query��������������ֻ��Ҫά��һ��10����С�����飬��ʼ������10��Query��
		// ����ÿ��Query��ͳ�ƴ����ɴ�С����Ȼ�������300������¼��ÿ��һ����¼�ͺ��������һ��Query�Աȣ����С�����Query��
		// ��ô�������������򣬽����������һ��������̭�����뵱ǰ��Query, �ƶ���֤����������е����ݶ��������֮����ô��������е�10��Query��������Ҫ�ҵ�Top10�ˡ�
		// ���ѷ��������������㷨���ʱ�临�Ӷ���N * K�� ����K��ָtop���١�
		// �㷨������
		// ���㷨���У������Ѿ���ʱ�临�Ӷ���NlogN�Ż���NK�����ò�˵����һ���Ƚϴ�ĸĽ��ˣ�������û�и��õİ취�أ�
		// ����һ�£����㷨���У�ÿ�αȽ����֮����Ҫ�Ĳ������Ӷȶ���K����ΪҪ��Ԫ�ز��뵽һ�����Ա�֮�У����Ҳ��õ���˳��Ƚϡ���������ע��һ�£�������������ģ�һ������ÿ�β��ҵ�ʱ����Բ��ö��ֵķ������ң����������ĸ��ӶȾͽ�����logK�����ǣ���֮������������������ƶ�����Ϊ�ƶ����ݴ��������ˡ�����������㷨���Ǳ��㷨�����˸Ľ���
		// �������ϵķ������������룬��û��һ�ּ��ܿ��ٲ��ң����ܿ����ƶ�Ԫ�ص����ݽṹ�أ��ش��ǿ϶��ģ��Ǿ��Ƕѡ�
		// �����ѽṹ�����ǿ�����log������ʱ���ڲ��Һ͵��� / �ƶ�����˵�������ǵ��㷨���ԸĽ�Ϊ������ά��һ��K(����Ŀ����10)��С��С���ѣ�Ȼ�����300���Query���ֱ�͸�Ԫ�ؽ��жԱȡ�
		// ˼���������㷨��һ�£�ֻ���㷨���㷨�������ǲ�������С���������ݽṹ�������飬�Ѳ���Ŀ��Ԫ�ص�ʱ�临�Ӷ���O��K��������O��logK����
		// ��ô���������ö����ݽṹ���㷨�������յ�ʱ�临�ӶȾͽ�����N��logK�����㷨����ȣ������˱Ƚϴ�ĸĽ���
		// �ܽ᣺
		// ���ˣ��㷨����ȫ�����ˣ�����������һ��������Hash��ͳ��ÿ��Query���ֵĴ�����O��N����Ȼ��ڶ��������ö����ݽṹ�ҳ�Top 10��N * O��logK�������ԣ��������յ�ʱ�临�Ӷ��ǣ�O��N�� + N�� * O��logK������NΪ1000��N��Ϊ300�򣩡������λ��ʲô���õ��㷨����ӭ�������ۡ���һ���֣��ꡣ

// jspx
//���������ǰ��յ�λ������Ȼ���ռ����ٰ��ո�λ����Ȼ�����ռ����������ƣ�ֱ�����λ����ʱ����Щ�����������ȼ�˳��ģ��Ȱ������ȼ������ٰ������ȼ��������Ĵ�����Ǹ����ȼ��ߵ���ǰ�������ȼ���ͬ�ĵ����ȼ��ߵ���ǰ��

// wp

int main()
{
	int arr[10] = { 4, 1, 7, 6, 9, 2, 8, 0, 3, 5 };
	
	// kp
	//QuickSortNotR(arr, 0, 9);
	
	// dp
	int size = sizeof(arr) / sizeof(int);
	printf("%d \n", size);
	printf("����ǰ���飺");
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
