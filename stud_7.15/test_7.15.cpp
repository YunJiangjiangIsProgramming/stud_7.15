#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;
#include<deque>
#include<queue>
#include <functional>

#include "priorityQueue.h"


void test1()
{
	//luow::priority_queue<int> pq; // < // 大堆
	luow::priority_queue<int, vector<int>, greater<int>> pq; // >  // 小堆
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
	// 大堆，需要用户在自定义类型中提供<的重载
	priority_queue<Date> q1;
	q1.push(Date(2024, 10, 29));
	q1.push(Date(2024, 10, 28));
	q1.push(Date(2024, 10, 30));
	cout << q1.top() << endl;

	// 如果要创建小堆，需要用户提供>的重载
	priority_queue<Date, vector<Date>, greater<Date>> q2;
	q2.push(Date(2024, 10, 29));
	q2.push(Date(2024, 10, 28));
	q2.push(Date(2024, 10, 30));
	cout << q2.top() << endl;


	// 大堆
	priority_queue<Date*, vector<Date*>, PDateLess> q3;
	q3.push(new Date(2024, 10, 29));
	q3.push(new Date(2024, 10, 28));
	q3.push(new Date(2024, 10, 30));
	cout << *q3.top() << endl;

	// 小堆
	priority_queue<Date*, vector<Date*>, PDateGreater> q4;
	q4.push(new Date(2024, 10, 29));
	q4.push(new Date(2024, 10, 28));
	q4.push(new Date(2024, 10, 30));
	cout << *q4.top() << endl;
}
//找Suzuki中第k大的数
//1.直接用sort（）快排O(N*log(N))

class Solution0 {
public:
	int findKthLargest(vector<int>& nums, int k)
	{
		// 使用 C++ 标准库中的 sort 函数对 nums 进行排序。sort 函数默认是按照升序排列。
		sort(nums.begin(), nums.end());

		// 由于排序后数组是升序的，所以第k大的元素在排序后的数组中是位于索引 size-k 的位置。
		// 这里的 size 是 nums 数组的大小。我们返回这个位置上的元素。
		return nums[nums.size() - k];
	}
};


class Solution1 {
public:

	int findKthLargest(vector<int>& nums, int k)
	{

		// 默认情况下，priority_queue 是一个最大堆，即它能确保父节点的值永远大于其子节点的值。
		priority_queue<int> pq;

		// 遍历数组 nums 中的每个元素，并将其加入最大堆中。
		for (auto e : nums) {
			pq.push(e);
		}

		// 弹出最大堆中的元素 k-1 次。这样做是为了移除前 k-1 大的元素，
		// 这样堆顶元素就是第k大的元素。
		while (--k) //--k,while循环走了k-1次pop()出去了前k-1个数字
		{
			pq.pop();
		}

		// 返回最大堆的堆顶元素，即现在是第k大的元素。
		return pq.top();
	}
};
//这种方法的时间复杂度是 O(n log n)，因为每次插入一个元素到优先队列中都需要 log n 的时间复杂度。
//它在空间复杂度上是 O(n)，因为我们需要存储整个数组的元素


class Solution2 {
public:
	
	int findKthLargest(vector<int>& nums, int k)
	{
		// 使用一个最小堆（通过 priority_queue 实现）来存储数组中的元素。
		// 这里我们传递了三个参数给 priority_queue：
		// 1. int：堆中元素的类型。
		// 2. vector<int>：容器类型，用来存储堆中的元素。
		// 3. greater<int>：比较函数对象，它确保最小堆的特性，即父节点的值小于其子节点的值。
		priority_queue<int, vector<int>, greater<int>> minHeap;

		// 我们首先将前 k 个元素插入到最小堆中。
		// 使用 size_t 类型来确保索引 i 不会变成负数，这是一个好的编程实践。
		size_t i = 0;
		for (; i < k; ++i) {
			minHeap.push(nums[i]);
		}

		// 然后，我们从第 k+1 个元素开始遍历数组的其余部分。
		for (; i < nums.size(); ++i) {
			// 如果当前元素大于最小堆的顶部元素，那么我们就弹出最小堆的顶部元素，
			// 并将当前元素插入最小堆中。这样可以确保最小堆中的元素都是最大的 k 个。
			if (nums[i] > minHeap.top()) {
				minHeap.pop();
				minHeap.push(nums[i]);
			}
		}

		// 最后，最小堆的顶部元素就是第k大的元素，所以我们用 return minHeap.top(); 返回它。
		return minHeap.top();
	}
};
//这种方法的时间复杂度是 O(n log k)，因为在最坏的情况下，我们可能需要将每个元素都插入到最小堆中，并且每次插入操作都需要 log k 的时间。
//它在空间复杂度上是 O(k)，因为我们需要存储最大的 k 个元素。
//这种方法的优点是它不需要对整个数组进行排序，只需要维护一个最小堆。
//对于大数据集来说，当我们只关心第 k 大的元素，而不是整个数组时，这种方法更为高效。对n>>k海量数据处理也很高效

int main()
{
	//test1();
	TestPriorityQueue();

	return 0;
}