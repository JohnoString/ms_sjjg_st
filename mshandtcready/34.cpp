// ������������в���Ԫ�صĵ�һ�������һ��λ��
#if 0
#include <iostream>
#include <vector>
using namespace std;

// ���� ʱ�䣺O(n) �ռ䣺O(1)
vector<int> GetFirstAndLastIndex(vector<int> v, int key)
{
	vector<int> vres;

	int a = -1;  // ��¼��
	int b = -1;  // ��¼��
	bool isleft = false;
	bool isright = false;
	for (int i = 0; i < v.size(); ++i)
	{
		if (key == v[i])
		{
			if (!isleft)
			{
				a = i;
				isleft = true;
				isright = false;
				continue;
			}

			if (!isright)
			{
				b = i;
			}
		}
	}

	vres.emplace_back(a);
	vres.emplace_back(b);
	return vres;
}
 
/*��������Ŀǰ����ָ�룬��ָ�룬���ж��м�ֵ��Ŀ��ֵ֮��Ĺ�ϵ����ôһ�������ֹ�ϵ���

�м�ֵС��Ŀ��ֵ����Ŀ��ֵֻ��������������
�м�ֵ����Ŀ��ֵ����Ŀ��ֵֻ��������������
�м�ֵ����Ŀ��ֵ����Ŀ��ֵ�����������鶼���ܴ���
������1�����3�����м�ֵС��Ŀ��ֵ������ָ���������м䣬������ָ���������м䡣����һ�������ҵ�Ŀ��ֵ�ĳ�ʼ�±�
ͬ��������2�����3�����м�ֵ����Ŀ��ֵ������ָ���������м䣬������ָ���������м䣬����һ�������ҵ�Ŀ��ֵ�Ľ����±ꡣ
*/

int findFirst(vector<int> nums, int target) {
    int idx = -1;
    int start = 0;
    int end = nums.size() - 1;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (nums[mid] >= target) {
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
        if (nums[mid] == target) idx = mid;
    }
    return idx;
}

int findLast(vector<int> nums, int target) {
    int idx = -1;
    int start = 0;
    int end = nums.size() - 1;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (nums[mid] <= target) {
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
        if (nums[mid] == target) idx = mid;
    }
    return idx;
}

vector<int> searchRange3(vector<int> nums, int target) {
    vector<int> result;
    result.emplace_back(findFirst(nums, target));
    result.emplace_back(findLast(nums, target));
    return result;
}

int main()
{
	vector<int> v = { 5,7,7,8,8,10 };
	vector<int> vv = searchRange3(v, 8);
	cout << vv[0] << ", " << vv[1] << endl;
	return 0;
}
#endif