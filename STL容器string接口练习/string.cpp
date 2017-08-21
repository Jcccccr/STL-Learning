#define _CRT_SECURE_NO_WARNINGS 1


//////////////////////////////std::string的接口使用/////////////////////////////
#include<iostream>
#include<string>

using namespace std;

void Teststring()
{
	//构造
	string s1("hello world");
	string s2(s1);            //拷贝构造
	string s3(s2, 2, 6);       //去规定位置规定长度的子串
	string s4(s1, 4);              //取后4个字符
	string s5("code makes happy", 10); //取前10个字符
	string s6(10, 'x');            //构造10个‘x’
	string s7(10, 42);             //10个ASCII码为42的字符
	string s8(s1.begin(), s1.begin() + 5);
	/*cout << s1 << endl;
cout << s2 << endl;
cout << s3 << endl;
cout << s4 << endl;
cout << s5 << endl;
cout << s6 << endl;*/
	//cout << s7 << endl;
	//cout << s8 << endl;

	//赋值运算符重载 
	string str1("hahha");
	string str2("hhhehehe");
	//str2 = str1;
	string str3(str1 + str2);        //字符串拼接

	//cout << str3 << endl;

	//begin()、end()   //迭代器

	//rbegin() 、rend()   //反向迭代器  按照字符反向

	//size()
	cout << str1.size() << endl;  //字符串的长度
	//length()
	cout << str1.length() << endl; //字符串的长度
	//max_size()
	cout << str1.max_size() << endl;  //字符串可以容纳的最大长度
	//capacity()
	cout << str1.capacity() << endl;  //一般是15 就是目前字符串的容量
	//reserve()
	str1.reserve(20);               //增容  改变capacity
	cout << str1.capacity() << endl;   //這个时候capacity的值改为31
	//clear   删除字符串的内容，这将变成一个空字符串(长度为0)。
	s2.clear();
	//cout << s2 << endl;   //空串  长度为0
	//cout << sizeof(s2) << endl;    //一个空的string类型字节数28
	//empty()  判断字符串长度是否是0
	//operator[] 下标访问  
	//cout << str1[20] << endl;
	//at  下标访问        如果越界则抛出异常
	//cout << str1.at(10) << endl;
	//注意operator[] 和at()的区别

	//back()    字符串的最后一个字符

	//front     字符串的第一个字符

	//重点：
	//operator+=
	string str5 = "hello ";       //字符串拼接
	str5 += 'K';
	str5 += '.';
	str5 += "James";
	str5 += '\n';
	cout << str5;
	//append()     在末尾添加字符串

	//push_back()   在字符串末尾添加字符

	//assign()     将字符串进行替换
	str5.assign("hhahahahahahahahah");
	cout << str5 << endl;

	//insert()      在pos位置前插入字符或者字符串
	//str5.insert(5, "jj");   //在位置之前插入字符串
	str5.insert(5, 2, 'v');     //在位置5之前插入2个字符'v';
	cout << str5 << endl;

	//erase(pos，n)      对pos位置之后一个位置开始的n个数进行删除操作

	//replace()         替换字符串（固定长度）

	//swap(string& str)       用另一个字符串来替换之這个字符串
	//str5.swap("nihao!");   不能這样使用
	string str6 = "nihao!";
	str5.swap(str6);         //swap必须要创建一个对象然后才能交换不能直接使用一个字符串开替换
	//cout << str5 << endl;

	//pop_back()    C++11  
	//将字符串的最后一个字符删除


	//重要：   
	//c_str()    //返回一个字符数组的指针
	//作用：得到C字符串 ；返回一个数组的指针，该数组包含一个以null结尾的字符序列(即C风格字串)表示字符串对象的当前值。
	//这个数组包含了组成字符串对象值的相同字符序列，以及在末尾附加一个终止的空字符(' \ 0 ')。
	//使用场景： 在使用strcpy类的函数的时候，不支持string类型，這个时候就可以有必要将string转换为C风格字符串
	//char* strArr = new char[str5.size() + 1];
	//strcpy(strArr, str5.c_str());        //使用场景
	//cout << strArr << endl;

	//data            //功能和c_str()几乎一样  不知道区别
	char* strArr = new char[str5.size() + 1];
	strcpy(strArr, str5.data());        //使用场景
	cout << strArr << endl; 
	//data 和 c_str() 输出的结果一样

	//size_t copy (char* s, size_t len, size_t pos = 0) const;
	//将当前的字符串对象指定位置，指定长度，拷贝到指定字符串数组s中


	//find系列接口  返回值是size_t 返回的是第一次出现的位置 
	//size_t find (const string& str, size_t pos = pos) const;
	//1.find 查找指定位置之后的字符串中指定字符串第一次出现的位置
	//2.rfind 查找指定位置之前的字符串中第一次出现的指定字符串的位置
    
	//find_first_of   查找指定位置之后的指定字符串第一次出现的位置
	//find_first_not_of  查找字符串中第一次出现的不匹配的字符串。

	//substr(pos=0,len)  
	//获取子串，从指定的位置pos获取之后长度为len的子串
    
	//compare  字符串比较函数 可以指定位置只当长度
	cout << str5.compare("o") << endl;  //-1
	cout << str5.compare("hahahahhahaha") << endl;  //1
	cout << str5.compare("nihao!") << endl; //0
	//原理和strcmp是一样的


	//operator<<    operator<< 
	//string重载了输入输出运算符
}
int main()
{
	Teststring();
	return 0;
}