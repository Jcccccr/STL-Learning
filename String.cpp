#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
////模拟实现String类
//
//class String
//{
//	friend ostream& operator<<(ostream& out, String& s);
//private:
//      char* _str;
//public:
//	//String()                  //构造？   //我们本来打算写一个没有参数的构造函数以方便不带参数的对象调用  但是发现這样很不方便
//	//	:_str(NULL)
//	//{
//	//	cout << "String" << endl;
//	//}
//	String(const char* str="")              //带有默认参数的构造函数         //在這里 初始化了形参*str=""  给了一个空字符串 长度为0  1个字节                 
//		:_str(new char[strlen(str) + 1])    //开辟空间
//	{
//		cout << "String" << endl;
//		strcpy(_str, str);                 //值拷贝
//	}
//	String(const String& s)                      //拷贝构造
//		:_str(new char[strlen(s._str)+1])
//	{
//		cout << "String& s" << endl;
//		strcpy(_str, s._str);
//	}
//	String& operator=(const String& s)                           //赋值运算符的重载
//	{
//		cout << "String& operator=(const String& s)" << endl;
//		if (this != &s)                                         //避免自赋值
//		{
//			delete[] _str;                                      //记得delete[]成对使用
//			_str = new char[strlen(s._str) + 1];
//			strcpy(_str, s._str);
//		}
//		return *this;
//	}
//	~String()
//	{
//		cout << "~String" << endl;
//		if (_str != NULL)
//		{
//			delete[] _str;
//		}
//	}
//
//
//};
//ostream& operator<<(ostream& out, String& s)
//{
//	out << s._str;
//	return out;                                //這里记得返回值
//}
//int main()
//{
//	String s1("hello bit.\n");
//	String s3;                     //调用无参的构造函数
//	String s2(s3);                 //拷贝构造函数
//	String s4(s1);
//	String s5("hello world\n");
//	String s6;
//	s6 = s5;
//	cout << s1;
//	cout << s2;
//	cout << s3;
//	cout << s6;
//	return 0;
//}



//String 传统写法练习   深拷贝思想
//class String
//{   
//	friend ostream& operator<<(ostream& out, String& s);
//private:
//	 char* _str;
//public:
//	String(const char* str="")        //构造         刚开始的时 对于没有默认参数的构造函数为什么我们不能使用_str(str)进行赋值呢？
//		:_str(new char[strlen(str)+1])                   //想一想 形参str指向静态区的那个常量 初始化结束后_str也指向静态区  那么最后析构的时候，能释放静态区的字符串常量吗？
//	{                                                       //這样就存在问题  而且_str对于這个字符串也没有办法进行操作 所以要自己单独开辟空间
//		cout << "构造" << endl;
//		strcpy(_str, str);
//	}
//	String(const String& s)          //拷贝构造
//		:_str(new char[strlen(s._str)+1])
//	{
//		cout << "拷贝构造" << endl;
//		strcpy(_str, s._str);
//	}
//	String& operator=(const String& s)
//	{
//		if (this != &s)                             //這里一定要判断自赋值的问题  往往自赋值会带来很大的问题
//		{
//			cout << "赋值运算符重载" << endl;
//			char* tmp = new char[strlen(s._str) + 1];       //這里定义一个tmp的目的是为了防止在空间上出现问题 如果空间不够就暂停
//			strcpy(tmp, s._str);
//			delete[] _str;                           //如果這里自赋值了  那么這里就把自己释放了 
//			_str = tmp;                              //如果自己释放了 s._str还存在吗？
//		}
//		return *this;
//	}
//
//	~String()
//	{
//		cout << "析构" << endl;
//		if (_str != NULL)
//		{
//			delete[]_str;
//			_str = NULL;
//		}
//	}
//
//
//};
//ostream& operator<<(ostream& out, String& s)
//{
//	out << s._str;
//	return out;
//}
//int main()
//{
//	String s1("hello today\n");
//	cout << s1;
//	String s2(s1);
//	cout << s2;
//	String s3("hi\n");
//	s2 = s3;
//	cout << s2;
//	return 0;
//}

//new delete在开辟空间失败的时候会抛异常  




//写时拷贝
//（引用计数）浅拷贝的错误方式1
//class String
//{
//	friend ostream& operator<<(ostream& out, String& s);
//private:
//	char* _str;
//	int _refCount;
//public:
//	String(const char* str="")
//		:_str(new char[strlen(str)+1])
//		, _refCount(1)
//	{
//		cout << "构造" << endl;
//		strcpy(_str, str);
//	}
//	String( String& s)            //浅拷贝       //這里我们要把const去掉是因为下面会改变s引用的计数成员
//		:_str(s._str)
//	{
//		++s._refCount;
//		_refCount = s._refCount;         
//	}
//	~String()
//	{
//		if (--_refCount == 0)    
//		{
//            if (_str != NULL)
//			{
//				cout << "析构" << endl;
//				delete[] _str;
//				_str = NULL;
//			}
//		}
//	}
//};
//ostream& operator<<(ostream& out, String& s)
//{
//	cout << s._str;
//	return out;
//}
//int main()
//{
//	String s1("hello\n");
//	cout << s1;
//	String s2(s1);
//	return 0;
//}

//规避上述问题  使用static修饰refCount使其为静态    但是依然存在问题                  静态成员函数不存在this指针  静态成员函数不能访问非静态成员
//class String
//{
//	friend ostream& operator<<(ostream& out, String& s);
//private:
//	char* _str;
//	static int _refCount;      //静态成员不能在初始化列表中初始化  只能在函数内部或者类外进行初始化
//public:
//	String(const char* str = "")
//		:_str(new char[strlen(str) + 1])
//	{
//		_refCount = 1;
//		cout << "构造" << endl;
//		strcpy(_str, str);
//	}
//	String(String& s)            //浅拷贝       //這里我们要把const去掉是因为下面会改变s引用的计数成员
//		:_str(s._str)
//	{
//		++_refCount;             //
//	}
//	~String()
//	{
//		if (--_refCount == 0)
//		{
//			if (_str != NULL)
//			{
//				cout << "析构" << endl;
//				delete[] _str;
//				_str = NULL;
//			}
//		}
//	}
//};
//ostream& operator<<(ostream& out, String& s)
//{
//	cout << s._str;
//	return out;
//}
//int String::_refCount = 0;
//int main()
//{
//	String s1("hello\n");
//	cout << s1;
//	String s2(s1);               //這样就只析构了一次
//	String s3(s2);
//	String s4(s3);
//	cout << s3;
//
//	String s5("bit\n");    //這样发现了问题的存在  重新构造了一个对象之后 对静态的refCount造成影响 
//	String s6(s5);         //有俩个静态区的常量字符串被指向   但是依然只析构了一次                存在问题
//	cout << s6;
//	return 0;
//}



//最终的解决方案    CopyOnWrite  
class String
{
	friend ostream& operator<<(ostream& out, String& s);
private:
	char* _str;
    int* _refCount;                       //用指针维护這个变量     理解一下为什么用指针来维护
public:
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
		, _refCount(new int(1))
	{
		cout << "构造" << endl;
		strcpy(_str, str);
	}
	String(String& s)            
		:_str(s._str)
		, _refCount(s._refCount)
	{
		++(*_refCount);
		
	}
	String& operator=(String& s)           //赋值运算符的重载需要考虑3种情况       挺重要的
	{
		if (this != &s)                   //1.如果=号左右两边指向的是同一块空间 不执行
		{
			if (--(*_refCount) == 0)            //2.如果s1指向的空间没有其他的对象指向他 那么s1改变指向的需要把自己的成员变量所占的空间进行销毁
			{                                  //再指向s2
				cout << "析构" << endl;
				delete[]_str;
				delete _refCount;
			}
			_str = s._str;
			_refCount = s._refCount;             //3.如果s1指向的空间也有其他的对象指向  那么那块空间的_refCount-1就行了 s1直接改变指向其他啥都不用做
			++(*_refCount);                //注意：這里的计数已经不再是s1的计数了  已经是s2的计数了
		}
		return *this;
	}
	char& operator[](size_t index)         //下标引用运算符的重载  //這里为什么要返回一个char&  ?  思考
	{
		assert(index < strlen(_str));
		return _str[index];                 //這里返回的是_str所指向的字符串的某个字符的引用   所以使用char&  引用一个字符
	}

	~String()
	{
		if (--(*_refCount) == 0)
		{
			if (_str != NULL)
			{
				cout << "析构" << endl;
				delete[] _str;
				delete _refCount;
				_str = NULL;
			}
		}
	}
};
ostream& operator<<(ostream& out, String& s)
{
	cout << s._str;
	return out;
}
int main()
{
	String s1("hello\n");
	cout << s1;
	String s2(s1);           
	String s3(s2);
	String s4(s3);
	cout << s3;

	String s5("bit\n");       
	String s6(s5);            //這样就能够析构两次 
	cout << s6;
	s5 = s1;                         //针对于赋值运算符的重载  该怎么写时浅拷贝呢？
	String s7("juxin");
	String s8;
	s8 = s7;
	s7[3] = 'I';            //這里的意思和上面的函数配合起来就是s7[3]实际上代表的是下标为3的字符的引用   那么用‘I’来赋值 当然是可以从根源更改的 
	cout << s7;
	return 0;
}

