#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;
#include<deque>
#include<queue>
#include <functional>

#include "priorityQueue.h"


void test1()
{
	//luow::priority_queue<int> pq; // < // ���
	luow::priority_queue<int, vector<int>, greater<int>> pq; // >  // С��
	pq.push(3);
	pq.push(1);
	pq.push(2);
	pq.push(5);

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;


}
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}

	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}

	friend ostream& operator<<(ostream& _cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}

private:
	int _year;
	int _month;
	int _day;
};

struct PDateLess
{
	bool operator()(const Date* d1, const Date* d2)
	{
		return *d1 < *d2;
	}
};

struct PDateGreater
{
	bool operator()(const Date* d1, const Date* d2)
	{
		return *d1 > *d2;
	}
};



void TestPriorityQueue()
{
	// ��ѣ���Ҫ�û����Զ����������ṩ<������
	priority_queue<Date> q1;
	q1.push(Date(2024, 10, 29));
	q1.push(Date(2024, 10, 28));
	q1.push(Date(2024, 10, 30));
	cout << q1.top() << endl;

	// ���Ҫ����С�ѣ���Ҫ�û��ṩ>������
	priority_queue<Date, vector<Date>, greater<Date>> q2;
	q2.push(Date(2024, 10, 29));
	q2.push(Date(2024, 10, 28));
	q2.push(Date(2024, 10, 30));
	cout << q2.top() << endl;


	// ���
	priority_queue<Date*, vector<Date*>, PDateLess> q3;
	q3.push(new Date(2024, 10, 29));
	q3.push(new Date(2024, 10, 28));
	q3.push(new Date(2024, 10, 30));
	cout << *q3.top() << endl;

	// С��
	priority_queue<Date*, vector<Date*>, PDateGreater> q4;
	q4.push(new Date(2024, 10, 29));
	q4.push(new Date(2024, 10, 28));
	q4.push(new Date(2024, 10, 30));
	cout << *q4.top() << endl;
}
//��Suzuki�е�k�����
//1.ֱ����sort��������O(N*log(N))

class Solution0 {
public:
	int findKthLargest(vector<int>& nums, int k)
	{
		// ʹ�� C++ ��׼���е� sort ������ nums ��������sort ����Ĭ���ǰ����������С�
		sort(nums.begin(), nums.end());

		// �������������������ģ����Ե�k���Ԫ������������������λ������ size-k ��λ�á�
		// ����� size �� nums ����Ĵ�С�����Ƿ������λ���ϵ�Ԫ�ء�
		return nums[nums.size() - k];
	}
};


class Solution1 {
public:

	int findKthLargest(vector<int>& nums, int k)
	{

		// Ĭ������£�priority_queue ��һ�����ѣ�������ȷ�����ڵ��ֵ��Զ�������ӽڵ��ֵ��
		priority_queue<int> pq;

		// �������� nums �е�ÿ��Ԫ�أ���������������С�
		for (auto e : nums) {
			pq.push(e);
		}

		// ���������е�Ԫ�� k-1 �Ρ���������Ϊ���Ƴ�ǰ k-1 ���Ԫ�أ�
		// �����Ѷ�Ԫ�ؾ��ǵ�k���Ԫ�ء�
		while (--k) //--k,whileѭ������k-1��pop()��ȥ��ǰk-1������
		{
			pq.pop();
		}

		// �������ѵĶѶ�Ԫ�أ��������ǵ�k���Ԫ�ء�
		return pq.top();
	}
};
//���ַ�����ʱ�临�Ӷ��� O(n log n)����Ϊÿ�β���һ��Ԫ�ص����ȶ����ж���Ҫ log n ��ʱ�临�Ӷȡ�
//���ڿռ临�Ӷ����� O(n)����Ϊ������Ҫ�洢���������Ԫ��


class Solution2 {
public:
	
	int findKthLargest(vector<int>& nums, int k)
	{
		// ʹ��һ����С�ѣ�ͨ�� priority_queue ʵ�֣����洢�����е�Ԫ�ء�
		// �������Ǵ��������������� priority_queue��
		// 1. int������Ԫ�ص����͡�
		// 2. vector<int>���������ͣ������洢���е�Ԫ�ء�
		// 3. greater<int>���ȽϺ���������ȷ����С�ѵ����ԣ������ڵ��ֵС�����ӽڵ��ֵ��
		priority_queue<int, vector<int>, greater<int>> minHeap;

		// �������Ƚ�ǰ k ��Ԫ�ز��뵽��С���С�
		// ʹ�� size_t ������ȷ������ i �����ɸ���������һ���õı��ʵ����
		size_t i = 0;
		for (; i < k; ++i) {
			minHeap.push(nums[i]);
		}

		// Ȼ�����Ǵӵ� k+1 ��Ԫ�ؿ�ʼ������������ಿ�֡�
		for (; i < nums.size(); ++i) {
			// �����ǰԪ�ش�����С�ѵĶ���Ԫ�أ���ô���Ǿ͵�����С�ѵĶ���Ԫ�أ�
			// ������ǰԪ�ز�����С���С���������ȷ����С���е�Ԫ�ض������� k ����
			if (nums[i] > minHeap.top()) {
				minHeap.pop();
				minHeap.push(nums[i]);
			}
		}

		// �����С�ѵĶ���Ԫ�ؾ��ǵ�k���Ԫ�أ����������� return minHeap.top(); ��������
		return minHeap.top();
	}
};
//���ַ�����ʱ�临�Ӷ��� O(n log k)����Ϊ���������£����ǿ�����Ҫ��ÿ��Ԫ�ض����뵽��С���У�����ÿ�β����������Ҫ log k ��ʱ�䡣
//���ڿռ临�Ӷ����� O(k)����Ϊ������Ҫ�洢���� k ��Ԫ�ء�
//���ַ������ŵ���������Ҫ�����������������ֻ��Ҫά��һ����С�ѡ�
//���ڴ����ݼ���˵��������ֻ���ĵ� k ���Ԫ�أ���������������ʱ�����ַ�����Ϊ��Ч����n>>k�������ݴ���Ҳ�ܸ�Ч

int main()
{
	//test1();
	TestPriorityQueue();

	return 0;
}