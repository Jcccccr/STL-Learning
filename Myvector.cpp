#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
#include<string>

//模拟实现vector

template<class T>
class Myvector
{
	typedef T* Iterator;              
	typedef const T* ConstIterator;
private:
	Iterator _start;
	Iterator _finish;
	Iterator _endofstorage;
public:
	Myvector()               //构造
		:_start(NULL)
		, _finish(NULL)
		, _endofstorage(NULL)
	{
		cout << "~Myvector()" << endl;
	}
	Myvector(const Myvector<T>& v)    //拷贝构造,考size还是考capacity？ 为了结社空间是拷贝size
	{
		_start = new T[v.Size()];
		for (size_t i = 0; i < v.Size(); i++)
		{
			_start[i] = v[i];
		}
		_finish = _start + v.Size();
		_endofstorage = _finish;
	}
	Myvector<T>& operator=(const Myvector<T>& v)
	{
		if (this != &v)
		{
			if (this->Size())    //原来的空间存在
				Destory();
			_start = new T[v.Size()];
			for (size_t i = 0; i < v.Size(); i++)   //拷贝
			{
				_start[i] = v[i];
			}
			_finish = _start + v.Size();
			_endofstorage = _start + v.Capacity();
		}
		return *this;
	}
	//增容
	void CheckCapacity()
	{
		if (Size() >= Capacity())
			Capacity() = Capacity() + Capacity() / 2;           //为什么需要1.5倍增容
		Expand(Capacity());
	}
	//增加固定的体积然后拷贝数据函数
	void Expand(size_t n)
	{
		if (n == 0)
			return;
		T* tmp = new T[n];
		assert(tmp);
		for (size_t i = 0; i < Size(); i++)
		{
			tmp[i] = _start[i];
		}
		delete[] _start;
		_start = tmp;
		_finish = _start + Size();
		_endofstorage = _start + n;
	}
	void PushBack(const T& data)                //尾插
	{
		CheckCapacity();
		*_finish = data;
		_finish++;
	}
	void PopBack()                 //尾删
	{
		if (Size() <= 0)
			return;
		_finish--;
	}
	void ReSize(size_t n)
	{
		
	}
	void Reserve(size_t n)          //Reserve的值可以比原来小？
	{
		if (n <= Size())
			return;
		Expand(n);
	}
	T& operator[]()
	{
		return _start[i];
	}
	size_t Size()
	{
		return _finish - _start;
	}
	size_t Capacity()
	{
		return _endofstorage - _start;
	}
	void Destory()
	{
		delete[]_start;
		_start = NULL;
		_finish = NULL;
		_endofstorage = NULL;
	}
};
void test()
{

}
int main()
{
	test();
	return 0;
}