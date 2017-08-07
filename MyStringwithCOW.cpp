#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
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

// MyString+Copy-On-Write 
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
	MyCOWString& operator=(const MyCOWString& s)
	{
		if (this != &s)
		{
			_str = s._str;
			_refCount = s._refCount;
			(*_refCount)++;
		}
		return *this;
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
	MyCOWString s2(s1);
	s2.PrintString();
	MyCOWString s3("Hello String");
	s1 = s3;
	s2.PrintString();
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