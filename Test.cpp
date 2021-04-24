#include<iostream>
#include<list>
#include<functional>
using namespace std;


namespace bit58
{
	template<class _Ty>
	class list;

	template<class _Ty>
	class ListIterator;

	//节点类
	template<class _Ty>
	class ListNode
	{
		friend class list<_Ty>;
		friend class ListIterator<_Ty>;
	public:
		ListNode():_Value(_Ty()), _Next(nullptr),_Prev(nullptr)
		{}
		ListNode(_Ty V, ListNode *next=nullptr, ListNode *prev=nullptr)
			:_Value(V), _Next(next),_Prev(prev)
		{}
		~ListNode()
		{}
	private:
		_Ty       _Value;
		ListNode *_Next;
		ListNode *_Prev;
	};

	//迭代器类
	template<class _Ty>
	class ListIterator
	{
		typedef ListIterator<_Ty> _It;
	public:
		ListIterator():_Ptr(nullptr)
		{}
		ListIterator(ListNode<_Ty> *_P) : _Ptr(_P)
		{}
	public:
		_It& operator++()
		{
			_Ptr = _Ptr->_Next;
			return *this;
		}
		_It& operator--()
		{
			_Ptr = _Ptr->_Prev;
			return *this;
		}
		_Ty& operator*()
		{
			return (_Ptr->_Value);
		}

		bool operator!=(const _It &it)
		{
			return _Ptr != it._Ptr;
		}
		bool operator==(const _It &it)
		{
			return _Ptr == it._Ptr;
		}
		ListNode<_Ty>* _Mynode()
		{
			return _Ptr;
		}
	private:
		ListNode<_Ty> *_Ptr;
	};

	//链表类
	template<class _Ty>
	class list
	{
	public:
		typedef ListNode<_Ty>* _Nodeptr;
		typedef ListIterator<_Ty> iterator;
	public:
		list():_Size(0)
		{
			CreateHead();
		}
		list(size_t n, const _Ty &x=_Ty()) : _Size(0)
		{
			CreateHead();
			insert(begin(), n, x);
		}
		list(const _Ty *first, const _Ty *last):_Size(0)
		{
			CreateHead();
			while(first != last)
				push_back(*first++);
		}
		list(iterator first,  iterator last)
		{
			CreateHead();
			while(first != last)
			{
				push_back(*first);
				++first;
			}
		}

		list(list<_Ty> &lt) : _Size(0)
		{
			CreateHead();
			list<_Ty> tmp(lt.begin(), lt.end());
			this->swap(tmp);
		}
		~list()
		{
			clear();
			delete _Head;
			_Size = 0;
		}
	public:
		void push_back(const _Ty &x)
		{
			insert(end(), x);
		}
		void pop_back()
		{
			erase(--end());
		}
		void push_front(const _Ty &x)
		{
			insert(begin(), x);
		}
		void pop_front()
		{
			erase(begin());
		}
		_Ty& front()
		{
			return *begin();
		}
		const _Ty& front()const 
		{
			return *begin();
		}
		_Ty& back()
		{
			return *--end();
		}
		const _Ty& back()const
		{
			return *--end();
		}

	public:
		size_t size()const
		{
			return _Size;
		}
		bool empty()const
		{
			return (size()==0);
		}
	public:
		iterator begin()
		{
			return iterator(_Head->_Next);
		}
		iterator end()
		{
			return iterator(_Head);
		}
		void clear()
		{
			erase(begin(), end());
		}
	public:
		iterator insert(iterator _P, const _Ty &x)
		{
			_Nodeptr cur = _P._Mynode();
			_Nodeptr _S = new ListNode<_Ty>(x);
			//_S->_Value = x;

			_S->_Next = cur;
			_S->_Prev = cur->_Prev;
			_S->_Prev->_Next = _S;
			_S->_Next->_Prev = _S;

			_Size++;
			return iterator(_S);
		}

		void insert(iterator _P, size_t n, const _Ty &x=_Ty())
		{
			while(n--)
				insert(_P, x);
		}

		iterator erase(iterator _P)
		{
			_Nodeptr cur = _P._Mynode();
			_Nodeptr next_node = cur->_Next;

			cur->_Prev->_Next = cur->_Next;
			cur->_Next->_Prev = cur->_Prev;
			delete cur;

			_Size--;

			return iterator(next_node);
		}
		iterator erase(iterator first, iterator last)
		{
			while(first != last)
			{
				first = erase(first);
			}
			return first;
		}

		void swap(list<_Ty> &lt)
		{
			std::swap(_Head, lt._Head);
			std::swap(_Size, lt._Size);
		}
	protected:
		void  CreateHead()
		{
			//_Head = (_Nodeptr)malloc(sizeof(ListNode<_Ty>));
			_Head =  new ListNode<_Ty>;
			_Head->_Prev = _Head->_Next = _Head;
		}
	private:
		_Nodeptr      _Head;
		size_t        _Size;
	};
};

void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	bit58::list<int> lt(ar, ar+5); 
	bit58::list<int> lt1(lt); 

	//lt.swap(lt1);

	bit58::list<int>::iterator it = lt.begin();
	while(it != lt.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	bit58::list<int>::iterator it1 = lt1.begin();
	while(it1 != lt1.end())
	{
		cout<<*it1<<" ";
		++it1;
	}
	cout<<endl;
}

/*
void main()
{
	bit58::list<int> lt; 

	lt.insert(lt.begin(), 1);
	lt.insert(lt.begin(), 2);
	lt.insert(lt.begin(), 3);
	lt.insert(lt.end(), 4);
	lt.insert(lt.end(), 5);
	lt.insert(lt.end(), 6);

	lt.erase(lt.begin());
	lt.erase(--lt.end());

	bit58::list<int>::iterator it = lt.begin();
	while(it != lt.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

/*
namespace bit58
{
	template<class _Ty>
	class list;

	//节点类
	template<class _Ty>
	class ListNode
	{
		friend class list<_Ty>;
	public:
		ListNode():_Value(_Ty()), _Next(nullptr),_Prev(nullptr)
		{}
		ListNode(_Ty V, ListNode *next=nullptr, ListNode *prev=nullptr)
			:_Value(V), _Next(next),_Prev(prev)
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
		list():_Head(_Buynode()),_Size(0)
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

void main()
{
	bit58::list<int> lt; 
}

/*
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

	for(const auto &e : lt)
		cout<<e<<" ";
	cout<<endl;
}
void main()
{
	TestListIterator1();
}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);

	list<int> mylist(ar, ar+n);
	
	//list<int>::iterator it = mylist.begin();

	auto it = mylist.begin(); //C++11
	auto it1 = find(mylist.begin(), mylist.end(), 5);
	cout<<*it<<endl;
	cout<<*it1<<endl;

	it = mylist.erase(it);

	cout<<*it<<endl; //继续访问
	cout<<*it1<<endl;

}

/*
void main()
{
	int ar[] = {1,9,4,7,8,2,3,0,5, 6, 10};
	int n = sizeof(ar) / sizeof(ar[0]);

	list<int> mylist(ar, ar+n); 
	
	//mylist.sort();
	mylist.sort(greater<int>()); //仿函数

	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);
	list<int> mylist(ar, ar+5);  //1 2 3 4 5
	list<int> youlist(ar+5, ar+n);//6,7, 8, 9, 10

	//mylist.assign(youlist.begin(), youlist.end());
	//mylist.merge(youlist);

	//mylist.remove(4);
	//mylist.unique();

	list<int>::iterator pos = find(mylist.begin(), mylist.end(), 4);
	//mylist.splice(pos, youlist, youlist.begin());

	mylist.splice(pos, youlist, youlist.begin(), youlist.end());

	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;

	list<int>::iterator yit = youlist.begin();
	while(yit != youlist.end())
	{
		cout<<*yit<<"-->";
		++yit;
	}
	cout<<"Over."<<endl;

}


/*
void main()
{
	int ar[] = {1,9,4,7,8,2,3,0,5, 6, 10};
	int n = sizeof(ar) / sizeof(ar[0]);

	list<int> mylist; 
	//mylist.assign(10, 2);
	mylist.assign(ar, ar+n);
	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
void main()
{
	int ar[] = {1,9,4,7,8,2,3,0,5, 6, 10};
	int n = sizeof(ar) / sizeof(ar[0]);
	list<int> mylist(ar, ar+n); 

	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;

	mylist.sort();

	it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;

	mylist.reverse();

	it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);
	list<int> mylist(ar, ar+5);  //1 2 3 4 5
	list<int> youlist(ar+5, ar+n);//6,7, 8, 9, 10

	mylist.swap(youlist);

	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;

	list<int>::iterator yit = youlist.begin();
	while(yit != youlist.end())
	{
		cout<<*yit<<"-->";
		++yit;
	}
	cout<<"Over."<<endl;

}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);

	list<int> mylist(ar, ar+n);

	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;

	//插入
	list<int>::iterator pos = find(mylist.begin(), mylist.end(), 5);
	//mylist.insert(pos, 100);
	//mylist.insert(pos, 10, 100);
	//mylist.insert(pos, ar+8, ar+10);

	//删除
	//mylist.erase(mylist.begin());
	//mylist.erase(--mylist.end());
	//mylist.erase(pos);
	mylist.erase(mylist.begin(), mylist.end());

	it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
void main()
{
	list<int> mylist;
	mylist.push_back(1);
	mylist.push_back(2);
	mylist.push_back(3);
	mylist.push_back(4);
	mylist.push_front(10);
	mylist.push_front(20);
	mylist.push_front(30);

	//30 20 10 1 2 3 4

	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;

	mylist.pop_back();
	mylist.pop_front();

	it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}



/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);

	list<int> mylist(ar, ar+n);
	cout<<"empty = "<<mylist.empty()<<endl;
	cout<<"size = "<<mylist.size()<<endl;

	cout<<"fornt = "<<mylist.front()<<endl;
	cout<<"back = "<<mylist.back()<<endl;

	mylist.front() = 100;
	mylist.back() = 200;

	cout<<"fornt = "<<mylist.front()<<endl;
	cout<<"back = "<<mylist.back()<<endl;



	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;

}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);

	list<int> mylist(ar, ar+n);

	list<int>::iterator it = mylist.end();
	while(--it != mylist.begin())
	{
		cout<<*it<<"-->";
	}
	cout<<*it<<"-->Over."<<endl;
}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);

	list<int> mylist(ar, ar+n);

	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;

	list<int>::reverse_iterator rit = mylist.rbegin();
	while(rit != mylist.rend())
	{
		cout<<*rit<<"-->";
		++rit;
	}
	cout<<"Over";

}

/*
void main()
{
	list<int> mylist(10, 5);

	list<int> youlist(mylist.begin(), mylist.end());

	list<int>::iterator it = youlist.begin();
	cout<<"Head->";
	while(it != youlist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);
	list<int> mylist(ar, ar+n);

	list<int>::iterator it = mylist.begin();
	cout<<"Head->";
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
void main()
{
	list<int> mylist(10, 5);

	list<int> youlist = mylist;

	list<int>::iterator it = youlist.begin();
	cout<<"Head->";
	while(it != youlist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
void main()
{
	list<int> mylist(10, 5);

	list<int> youlist = mylist;

	list<int>::iterator it = mylist.begin();
	cout<<"Head->";
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
void main()
{
	list<int> mylist;

	for(const auto &e : mylist)
		cout<<e<<" ";
	cout<<endl;
}
*/