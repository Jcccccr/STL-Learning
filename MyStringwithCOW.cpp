#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

// MyString  
class MyString
{
	friend void PrintMyString(const MyString& s);
private:
	char* _str;
public:
	MyString(const char* str = "")
		:_str(new char[strlen(str)+1])
	{
		strcpy(_str, str);
		cout << "构造" << endl;
	}
	MyString(const MyString& s)
		:_str(new char[strlen(s._str)+1])      //深拷贝
	{
		strcpy(_str, s._str);
		cout << "拷贝构造" << endl;
	}
	MyString& operator=(const MyString& s)
	{
		if (this != &s)
		{
			char* tmp = _str;
			_str = new char[strlen(s._str) + 1];     //深拷贝
			strcpy(_str, s._str);
			delete[] tmp;
		}
		return *this;
	}
	~MyString()
	{
		if (_str != NULL)
		{
			delete[] _str;
			_str = NULL;              //注意置空防止野指针
		}
		cout << "~MyString()" << endl;
	}
};

void PrintMyString(const MyString& s)
{
	cout << s._str << endl;
}

// MyString+Copy-On-Write ,  当发生拷贝或者赋值的时候将引用计数++！ 
class MyCOWString
{
private:
	char* _str;
	int* _refCount;
public:
	MyCOWString(const char* str = "")
		:_str(new char[strlen(str) + 1])
		, _refCount(new int(1))
	{
		strcpy(_str, str);
		cout << "构造" << endl;
	}
	MyCOWString(const MyCOWString& s)
		:_str(s._str)
		, _refCount(s._refCount)
	{
		cout << "拷贝构造" << endl;
		(*_refCount)++;
	}
	//MyCOWString& operator=(const MyCOWString& s)      //這样的方案是错误的，需要考虑到是否需要释放之前的空间
	//{
	//	if (this != &s)
	//	{
	//		_str = s._str;
	//		_refCount = s._refCount;
	//		(*_refCount)++;
	//	}
	//	return *this;
	//}

	MyCOWString& operator=(const MyCOWString& s)
	{
		if (this != &s)
		{
			if (--(*_refCount) == 0)           //考虑被赋值的对象的资源有可能还被其他对象占有；当--计数器为0的时候，释放空间
			{
				delete[] _str;
				_str = NULL;
			}
			_str = s._str;
			_refCount = s._refCount;
			(*_refCount)++;
		}
		return *this;
	}
	const char& operator[](size_t index) const        //下标引用的重载  只读
	{
		assert(index < strlen(_str));
		return _str[index];
	}
	char& operator[](size_t index)                    //切记返回引用
	{
		assert(index < strlen(_str));
		if (--(*_refCount) != 0)                      //注意這里也需要注意对象的引用计数个数
		{
			if (_str)
			{
				char* tmp = new char[strlen(_str) + 1];     //這里就是写时拷贝的体现啦
				strcpy(tmp, _str);
				_str = tmp;
			}
		}
		return _str[index];
	}
	~MyCOWString()
	{
		if (--(*_refCount) == 0)       //注意此时对引用计数进行--操作
		{
			if (_str != NULL)
			{
				delete[] _str;
				_str = NULL;
				cout << "~MyCOWString" << endl;
			}
		}
	}
	void PrintString()
	{
		if (_str)
		{
			cout << _str << endl;
		}
	}
};
void MyCOWStringTest(void)
{
	MyCOWString s1("Hello COW");
	MyCOWString s3("Hello String");
	s3 = s1;
	s1[1] = 'o';
	//MyCOWString s2(s1);
	//s2.PrintString();
	//MyCOWString s3("Hello String");
	//s2.PrintString();
	//MyCOWString s4(s1);
	//MyCOWString s5(s1);
	//s4 = s1;
	//s4.PrintString();
	//cout << s1[1] << endl;
	s1.PrintString();
	s3.PrintString();
}

void MyStringTest(void)
{
	MyString s;
	MyString s2("Hello MyString");
	//PrintMyString(s2);
    MyString s3(s2);
	MyString s4("This is MyString");
	s2 = s4;
	PrintMyString(s2);
}
int main()
{
	//MyStringTest();
	MyCOWStringTest();
	return 0;
}