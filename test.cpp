#include<iostream>
#include<list>
#include<functional>
using namespace std;

namespace bit
{
	template<class _Ty>
	class list;

	//½ÚµãÀà
	template<class _Ty>
	class ListNode
	{
		friend class list<_Ty>;
	public:
		ListNode() :_Value(_Ty()), _Next(nullptr), _Prev(nullptr)
		{}
		ListNode(_Ty V, ListNode *next = nullptr, ListNode *prev = nullptr)
			:_Value(V), _Next(next), _Prev(prev)
		{}
		~ListNode()
		{}
	private:
		_Ty       _Value;
		ListNode *_Next;
		ListNode *_Prev;
	};

	template<class _Ty>
	class list
	{
	public:
		typedef ListNode<_Ty>* _Nodeptr;
	public:
		list() :_Head(_Buynode()), _Size(0)
		{}
	protected:
		_Nodeptr _Buynode()
		{
			_Nodeptr _S = (_Nodeptr)malloc(sizeof(ListNode<_Ty>));
			_S->_Prev = _S->_Next = _S;
			return _S;
		}
	private:
		_Nodeptr      _Head;
		size_t        _Size;
	};
};


void TestListIterator1()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	list<int> lt(array, array + sizeof(array) / sizeof(array[0]));
	auto it = lt.begin();
	while (it != lt.end())
	{
		it = lt.erase(it);
		//it++;
	}

	for (const auto &e : lt)
		cout << e << " ";
	cout << endl;
}
void main()
{
	TestListIterator1();
}