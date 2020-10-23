#if 0
#include <iostream>
using namespace std;

// ¶þ·Ö
int BSearch(int* arr, int size, int key)
{
	int low = 0;
	int high = size - 1;
	int mid = (low + high) / 2;

	while (low <= high)
	{
		if (arr[mid] > key)
		{
			high = mid - 1;
		}
		else if (arr[mid] < key)
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}

		mid = (low + high) / 2;
	}
}


int BSearchR(int* arr, int low, int high, int key)
{
	int mid = (low + high) / 2;

	if (low <= high)
	{
		if (arr[mid] > key)
		{
			BSearchR(arr, low, mid - 1, key);
		}
		else if (arr[mid] < key)
		{
			BSearchR(arr, mid + 1, high, key);
		}
		else
		{
			return mid;
		}
	}
}

int main()
{
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	cout << BSearchR(arr, 0, 9, 9) << endl;
	return 0;
}
#endif