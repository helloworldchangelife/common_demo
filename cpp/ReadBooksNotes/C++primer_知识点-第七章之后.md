### 第二章 （2.3）复合类型
##### 引用和指针：
- 下面代码会输出什么（知识点：引用）
```cpp
#include <iostream>
using namespace std;
int i, &r = i;

int main()
{
	i = 1;
	r = 9;
	cout << i <<" "<< r << endl;
	system("pause");
	return 0;
}
```
会输出：9 9
- 下面那个变量改变了：
```cpp
int *ptr=nullptr;//初始化
int ivalue=20;
ptr=&ivalue;
*ptr=0;
```
上面代码  变化的是ivalue,而ptr指针不变
- ==**面对一条比较复杂的指针或引用声明的语句，从右往左的阅读有助于理解**==
- 定义一个返回值是==数组指针==的函数：
```cpp
int (*func(int i))[10]; //返回值是数组指针的函数
```
- 尾置返回类型（简化上面的返回值是数组指针的函数）
```cpp
auto func(int i)->int(*) [10];//任何函数的定义都能使用尾置返回  但对于返回值比较复杂的最为有效（例如：返回值是数组指针或者数组的引用。）
```
- decltype(类型声明的关键字)：如果知道函数的返回指针指向的那个数组，就可以用decltype声明返回类型；
```cpp
int odd[5]={1,3,5,7,9};
int even[5]={0,2,4,6,8};
decltype(odd) *arrptr(int i)//需要定义成指针类型   指向数组
{
    return (i%2) ? &odd : &even;//返回一个指向数组的指针
}
```
- 一个拥有顶层const形参和另一个没有顶层const形参无法区分开来。例如：
```cpp
int func(int i);
int func(const int i);  //错误的，重复声明了func  说明不能够重载
```
- 另一方面，如果形参是某种类型的指针或者引用的时候；则通过判断指向的是常量对象还是非常量对象可以实现重载，此时const是底层的。例如代码：
```cpp
int func(int *ptr)；
int func(const int *ptr);   //合法的新函数  (重载)作用于常量的引用   
```
- const_cast和重载(见 C++primer 6.4)
- 重载与作用域:如果在内作用域声明名字，它将隐藏外层外层作用域中同名实体；
```cpp
string read();
void print(const string &);
void print(double);
void func(int value)
{
	bool read = false;//新作用域，隐藏外层read
	string s = read();//错误：read是一个布尔值，而非函数（通常来说，在局部作用域中声明函数不是一个好的选择）
	
	void print(int);//新作用域 隐藏外层print（平时不该放在内层，要放到外层）
	
	print("value:");//错误，print(const string &)被隐藏掉了
	print(value);//正确  当前print
	print(3.14);//正确，但调用的是print(int),print(double)被隐藏
}
```
`C++语言中，名字查找出现在类型检查之前;`
- 特殊用途语言特性
    - 默认实参：某个形参在多次调用时都被赋予相同的值，把反复出现的这个值就叫做默认实参(一旦某个形参被赋为默认值，其后面的形参都必须有默认值.不能修改已经存在的默认值)；
    - 内联函数和constexpr:内联函数是针对那些流程直接、规模小、频繁调动的函数，减少函数调用次数，减少系统资源开销；但是内联只是向编译器的一个请求，编译器可以忽略这个请求。总得来说就是优化程序。
	
- decltype 从表达式推断出变量的类型（decltype(fun()) sum ； 则sum类型是fun的返回类型）
- 函数指针
```cpp
bool lengthCompare(const string &,const string &);
//pf指向一个函数
bool *pf(const string &,const string &);
//使用函数指针
pf=lengthCompare;//指向lenfgthCompare
pf=&lengthCompare;//等价于上一个，取地址符是可选的

//还可以直接使用函数指针调用该函数，无需提前解引用指针
bool b0=pf("hello","goodbye");//调用lengthCompare函数
bool b2=(*pf)("hello","goodbye");//与前面等价
bool b3=lengthCompare("hello","goodbye");//另一个等价的调用
```
- 在指向不同函数类型的指针间不存在转换原则。（但我们可以给指针赋值一个nullptr或者值为0的整型常量表达式，表示该指针没有指向任何一个函数）
```cpp
string::size_type sumlength(const string& ，const string&)；
bool cstringCompare(const char*,const char*);
pf=0;//正确：pf不指向任何函数
pf=sumlength   //错误：返回类型不匹配
pf=cstringCompare;//错误：形参类型不匹配
pf=lengthCompare; //正确：函数和指针的类型精确匹配
```
### 第七章  类
##### 构造函数
- 默认构造函数只能适用于那些非常简单的类
- 对于一个普通类，要自己定义构造函数，原因有：
    -  只有当类没有申明过任何构造函数的情况下，编译器才会自动生成默认构造函数
    -  如果类包含内置类型或者复合类型的成员，则只有当这些成员全都被赋予了类内的初始值时，这个类才可以使用合成默认构造函数。
    -  编译器不能为某些类合成默认的构造函数。
- 一般情况下  最好在类内初始化值
- 如果要用到友元声明（一般情况下 要在类内声明的友元函数  都会和类在同一个头文件中，则最好在头文件里类外单独声明需要友元的函数）
```cpp
//test.h文件（范例）
#include<stdio.h>
#include<iostream>

func(int a);//单独声明

class test
{
    test()
    {}
    ~test()
    {}
    friend func(int a);  //友元
};
```
- 友元还可以友元类（如果B类的某些成员可能需要访问他管理的A类的内部数据（一般是private数据））
```cpp
class A
{
    friend class B;
}
```
- 友元函数不具有传递性（A类友元类B，B又友元类C，在C中无法访问A里面的非公有成员）
```cpp
class A
{
    friend class B;
private:
    int result;
}
class B
{
    friend class C;
private:
    int count;
}
class C
{
    //该类里面无法访问到，result，则说明友元不存在传递性
}
```
- 如果友元的是非成员函数或者其他类的成员函数，可以在声明友元的时候进行定义，但必须在这之前声明才可以调用；（有点拗口  详见C++primer7.3.4）
##### 构造函数再探
- 赋值与初始化的区别：赋值是先初始化再赋值，（这里考虑效率问题的话，养成构造函数初始值的好习惯，因为有的数据必须先要初始化，比如const修饰的数据）
- 委托构造函数：允许类中的一个构造函数通过初始化列表方式来调用同一个类中的另一个构造函数
```cpp
class X
{
 public:
    X(const string& name) : name_(name) 
    { 
     ...
    }
    //下面是类X中的另一个构造函数，其不接受任何参数，
    //而是通过初始化列表方式调用了上面的构造函数
    X() : X("委托构造") { } 。
};

```
- explicit关键字只能在类内构造函数处声明使用
```cpp
//错误：关键字explicit只允许出现在类内构造函数声明处
explicit SS::SS(istream& is)
{
    return (is,*this);
}
```
- 发生隐式转换的一种情况时当我们执行拷贝形式的初始化（使用=），当用explicit关键字声明的构造函数，只能使用直接初始化的方式。
```cpp
class SS
{
   SS()=default;
   
   explicit SS(std::istream&);
};
//正确，直接初始化
SS::SS test(scin);
//错误 不能将explicit构造函数用于拷贝式的初始化
SS::SS test=scin;
```
- constexpr:是C++11中新增的关键字，其语义是“常量表达式”，也就是在编译期可求值的表达式。最基础的常量表达式就是字面值或全局变量/函数的地址或sizeof等关键字返回的结果，而其它常量表达式都是由基础表达式通过各种确定的运算得到的。constexpr值可用于enum、switch、数组长度等场合。
```cpp
constexpr int Inc(int i) {
    return i + 1;
}
 
constexpr int a = Inc(1); // ok
constexpr int b = Inc(cin.get()); // !error
constexpr int c = a * 2 + 1; // ok
```
- constexpr还能用于修饰类的构造函数，即保证如果提供给该构造函数的参数都是constexpr，那么产生的对象中的所有成员都会是constexpr，该对象也就是constexpr对象了，可用于各种只能使用constexpr的场合。注意，constexpr构造函数必须有一个空的函数体，即所有成员变量的初始化都放到初始化列表中。
```cpp
struct A {
    constexpr A(int xx, int yy): x(xx), y(yy) {}
    int x, y;
};
 
constexpr A a(1, 2);
enum {SIZE_X = a.x, SIZE_Y = a.y};
```
- `constexpr所修饰的变量一定是编译期可求值的，所修饰的函数在其所有参数都是constexpr时，一定会返回constexpr`。
- constexpr的好处：
    - 是一种很强的约束，更好地保证程序的正确语义不被破坏。
    - 编译器可以在编译期对constexpr的代码进行非常大的优化，比如将用到的constexpr表达式都直接替换成最终结果等。
    - 相比宏来说，没有额外的开销，但更安全可靠。
- 字面值常量类：（constexpr函数参数和返回值都必须是字面值类型）
- 内联函数：在类里面定义的函数为内联函数。
- 聚合类：所有成员都是public；没有定义任何构造函数，没有类内初始值，没有基类，也没有虚函数(virtual)。
# C++标准库
#### IO库
- IO对象没有拷贝或赋值操作
- IO读写流的条件状态值：badbit是系统级错误，不可恢复的，一旦被置位，数据流就无法使用了；failbit被置位，（比如期望读取一个数值却读到一个字符），可以修正，数据流可以继续使用。
##### 管理输出缓冲
- 刷新输出缓冲区：
```cpp
cout<<"hello"<<endl;  //输出hello和一个换行，然后刷新缓冲区
cout<<"hello"<<ends;  //输出hello和一个空字符，然后刷新缓冲区
cout<<"hello"<<flush; //输出hello，然后刷新缓冲区，不附加任何字符
```
- 刷新缓冲区的用途：有时候输入的数据会被“垃圾”数据污染，会影响我们想要的结果。（个人理解，不太准确）
- tie：有两个版本，其中一个是不带参数的，返回指向输出流的指针（就是关联到输出流的指针）；另一个版本是带参数，接受一个指向ostream（输出流）的指针，将自己关联到ostream上。即x.tie(&o)将x关联到输出流o上面。
```cpp
cin.tie(&cout);   //标准库将cin关联到cout(tie带参数的版本)
```
- 若想彻底解开关联，需要传一个空指针进去。
```cpp
ostream* old_tie=cin.tie(nullptr);
```
- 2017-11-23
- 看了C++primer里面的ifstream、ofstream、fstream相关知识点，在从文件读取到内存（ifstream）时，出现空格符对之后不能进行读取（比如：file.txt文件中内容是"cpp is best",当读取到后遇见的一个空格之后读取到"cpp"）;当出现这种情况之后，在网上搜到可以使用istreambuf_iterator,读取到字符(需要一个一个字符输入时考虑使用istreambuf_iterator),istreambuf_iterator(Effective STL里面的知识点)详细内容见：http://blog.csdn.net/bichenggui/article/details/4710996
```cpp
/*************************************************************************
	> File Name   : iostream.cpp
	> Author      : wangyifei
	> Mail        : wangyufei.coder@gmail.com 
	> Created Time: Wed 22 Nov 2017 08:27:18 PM EST
	> Os System   : Linux Centos
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<iterator>
using namespace std;
int main()
{
	fstream fout;
	if(fout)
	{
		fout.open("/home/wyf/demo_wyf/file.txt",ios::app|ios::out);//显式指定文件模式，保留文件中的原数据
		fout<<"cppisbest"<<endl;
		fout.close();
	}
	else
	{
		cout<<"无法打开文件无法输出到文件中"<<endl;
	}
	ifstream fin("/home/wyf/demo_wyf/file.txt");
	if(fin)
	{
		string buffer((istreambuf_iterator<char>(fin)),istreambuf_iterator<char>());//这里就是解决对于空格等特殊字符的读取
		//也可以使用istream_iterator(但是有弊端，需要检查的东西太多，详细解惑查看上面网址，这里就不做介绍了)
		fin.close();
		cout<<buffer;
	}
	else
	{
		cout<<"文件无法打开无法将文件写入内存"<<endl;
	}
	return 0; 
}
```
- 当一个fstream对象被销毁时，close()会被自动调用关闭文件；
- ofstream打开文件之后，从内存把输出流写入到文件时，如果文件内有数据内容，要想保留住数据内容要在打开文件时显示指定该方法（ios::app或者ios::in）
- 每次打开文件都要设置文件的模式，可能是显式的设置，也可能是隐式的设置，当程序未设置时是默认设置。
```cpp
文件模式有：
in：以读方式打开
out：以写方式打开
app：每次操作前均定位到文件尾末；
ate：打开文件后立即定位到文件尾末；
trunc：截断文件  只有out的时候才可以设置trunc模式
binary:以二进制方式进行IO
```
#### string流
```cpp
//对输入字符串以空格分割开（eg:输入"wangyufei 000"  输出"wangyufei"和"000"）
#include<iostream>
#include<sstream>
#include<vector>
using namespace std;
int main()
{
	string line;
	vector<string>words;
	string word;
	getline(cin,line);
	istringstream ss(line);//也可以用stringstream
	while(ss>>word)
		words.push_back(word);
	vector<string>::iterator it=words.begin();
	while(it!=words.end())
	{
		cout<<*it++<<endl;
	}
	return 0;
}
```
- stringstream类似于fream,可以读也可以写；istringstream从string流中读取数据；ostringstream给string写数据；
- ostringstream当不断构造输出时，最后希望将一起打印，这时候ostringstream会很有用。
### 第九章：顺序容器
- 顺序容器有：
    - list:双向链表。支持插入删除速度很快，但也内存额外开销大。
    - vector：可变大小数组。支持快速随机访问，在头尾之外的部分插入删除元素速度可能很慢。
    - deque：双端队列。支持随机访问。头尾部分插入或删除速度很快。
    - forward_list：单向链表。只支持单向顺序访问，在链表的任何位置插入删除都很快。和list类似，内存额外开销也较大。(不支持获取元素数目c.size()操作)
    - array：固定数组大小。支持快速查找，因为固定大小，不能添加或者删除。
		* `注意：array没有默认构造函数((1)不支持指定范围的元素拷贝；例如：C c(b,e)是b至e范围内的元素拷贝到c。(2)不能将里面的元素替换成列表中的元素。比如：c1={a,b,c...})`
    - string：与vector相似的容器，但是专门保存字符，，随机访问快、尾部插入删除快。
- c开头(类似cbegin\cend等)的是C++11的，新标准，区别是：
```cpp
begin():Return iterator to beginning (public member function )
cbegin():Return const_iterator to beginning (public member function )//后者返回的是一个不可修改的迭代器，前者可修改。 
```
- 只有顺序容器的构造函数才能接受大小参数（除过array）
- 为拷贝另一个容器而创建一个容器，两个容器类型和元素类型要必须当匹配。
```cpp
list<string> auth={"a","b","c"};
list<string> list2(auth);   //正确的
deque<string> authdeque(auth);  //错误 容器类型不匹配
list<char> ccauth(auth);   //错误，元素类型不匹配
```
- 当传递迭代器参数来拷贝一个范围时，容器类型可以不同，元素类型也可以不同；
```cpp
vector<const char*> vtest={"aa","bb","cc"};
forward_list<string> fltest(vtest.begin(),vtest.end());//可以把"const char*"转换为string
```
- C++新标准中可以对顺序容器(除array之外)进行列表初始化
```cpp
vector<string> str={"wyf","www","comcom"};
```
- 赋值相关运算会导致左侧容器的迭代器、指针和引用失效;而swap不会使它们失效（容器类型为array和string的情况除外）。
- assign操作不适用于关联容器和array（仅适用于出array的顺序容器）
```cpp
//assign的用途：
list<string> list0;
vector<const char*> vtest;
list0=vtest;//错误容器类型不匹配
//此时，assign就该上场了
//将const char*转化为string
list0.assign(vtest.begin(),vtest.end());
```
- 除array外，swap操作不会造成任何元素的拷贝、删除或插入操作，故而可保证在常数时间内完成。（array与其他容器不同，会真正的交换两个array的元素，故而交换两个array的所需要时间和元素数量成正比）
- string类型容器不会造成元素的移动，但是特殊的是，例如下面例子：加入iter在swap之前指向vsc1[3]，swap之后指向的是vsc2[3]。故而与其他容器不一样，string会造成指针、迭代器等失效。
```cpp
vector<string> vsc1(10);
vector<string> vsc2(20);
swap(vsc1,vsc2);
```
```cpp
/*************************************************************************
	> File Name   : sequence_string.cpp
	> Author      : wangyifei
	> Mail        : wangyufei.coder@gmail.com 
	> Created Time: Sun 26 Nov 2017 09:00:05 PM EST
    > Platform    : Linux Centos
 ************************************************************************/
//示例
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str="cpp is best";
	string::iterator start=str.begin();
	string::iterator end=str.end();
	cout<<"打印string容器元素"<<endl;
	while(start<end)
	{
		cout<<*start;
		*start++;
	}
	int i=str.size();
	cout<<endl;
	cout<<i<<endl;
	return 0;
}
```
- 容器的运算符：每个容器都支持（==和!=）;除过无序关联容器外的所有容器都支持关系运算符（>,>=,<,<=）。关系运算符左右两边的运算对象必须是相同类型的容器，而且保存相同类型的元素。
- 两个容器比较大小，如果一个容器的元素不是另一个容器前缀的子序列，则他们的比较结果取决于第一个元素的比较结果。
```cpp
vector<int> v0={1,3,5,7,9,11,12}//列表初始化容器
vector<int> v1={1,3,5,9}
v0<v1   //true   因为在v0[3]<v1[3]
```
- 顺序容器和关联容器的不同之处在于阻止元素的方式不同，这些不同直接关系到元素的删除、插入、修改、访问操作。
- 除array之外的的容器都提供灵活的内存管理,在运行时动态添加或者删除改变容器大小。
- 向一个vector、string、deque里面插入一个元素会使所有指向容器的迭代器、指针、引用都失效。
##### 向容器里面插入元素
- push_front（list、forward_list、deque支持push_front）:将元素插入到容器头部。
- push_back（除过array和forward_list，其他容器都支持该操作）:将元素追加到容器尾部。
- insert（forward_list是特殊版的insert）:可以指定范围添加元素、特定位置添加元素、
- emplace(emplace_back\emplace_front\emplace)在函数直接在容器中构造元素，传递给emplace的参数必须要与元素类型的构造函数相匹配。（==新知识点==）
##### 访问容器元素
- 每个顺序容器都有一个front成员函数。（容器内第一个元素，首元素的引用）
- 除forward_list之外的顺序容器都有一个back成员函数（尾元素的引用）
- 在容器中访问元素的成员函数（即back、front、下标、at）返回的都是引用，如果容器是一个const对象，则返回的是const引用。
- 如果我们需要下标合法，可以采用at成员函数；
```cpp
vector<string> vstr;//空vector
cout<<vstr[0];//运行时错误，vstr内没有元素
cout<<vstr.at(0);//抛出一个out_of_range的异常
```
##### 删除容器内的元素
- forward_list不支持pop_back,有特殊版本的erase；
- vector和string都不支持pop_front;
- deque删除首尾元素之外的任何元素都会是所有的迭代器、指针、引用失效；指向vector或string删除点之后位置的迭代器、指针、引用都会失效。
```cpp
/*************************************************************************
	> File Name   : delete_container.cpp
	> Author      : wangyifei
	> Mail        : wangyufei.coder@gmail.com 
	> Created Time: Mon 27 Nov 2017 09:10:03 PM EST
    > Platform    : Linux Centos
 ************************************************************************/

#include<iostream>
#include<list>
using namespace std;
int main()
{
	list<int> list_integer={0,1,2,3,4,5,6,7,8,9,10,11,12,132};
	auto itor=list_integer.begin();
	while(itor!=list_integer.end())
	{
		if(*itor%2)
			itor=list_integer.erase(itor);
		else
			++itor;
	}
	auto iter=list_integer.begin();
	while(iter!=list_integer.end())
	{
		cout<<*iter<<" ";
		iter++;
	}
	cout<<endl;
	return 0;
}
```
- 删除容器中所有元素时，用clear成员函数；范围删除的时候用erase成员函数；
##### forward_list的特殊操作
- 参考地址： http://www.linuxidc.com/Linux/2017-01/139905.htm
- forward_list是单向链表，内部只维护了单向遍历的信息。因此，forward_list的迭代器是前向迭代器（forward intertor)。除此之外，它们的插入操作也有明显的不同，具体体现在传入的迭代器上：list::insert：在传入的迭代器之前插入；forward_list::insert:在传入的迭代器之后插入。
- forward_list没有insert、emplace、erase，而是insert_after,emplace_after,erase_after（首元素的前驱结点：before_begin,before_cbegin）
- forward_list删除或者插入的时候需要知道该位置元素的前驱，用来改变前驱的链接；但是forward_list是一个单向链表，没有简单的方法获取前驱，因此在forward_list中在添加或者删除时，通常改变的给定元素之后的元素。
```cpp
/*************************************************************************
	> File Name   : forward_list.cpp
	> Author      : wangyifei
	> Mail        : wangyufei.coder@gmail.com 
	> Created Time: Tue 28 Nov 2017 01:18:47 AM EST
    > Platform    : Linux Centos
 ************************************************************************/

#include<iostream>
#include<forward_list>
using namespace std;
int main()
{
	forward_list<int> flist={1,2,3,4,5,6,7,8,9,0,11,13,45,67,65,77,899,90};
	auto prev=flist.before_begin();//表示flist的首前元素（我的理解 就是flist第一个元素的前驱吧）
	auto curr=flist.begin();       //表示flist的第一个元素
	while(curr!=flist.end())
	{
		if(*curr%2)
		{
			curr=flist.erase_after(prev);//curr指向序列中下一个元素 prev保持不变，仍指向（新）curr之前的元素
		}
		else
		{
			prev=curr;
			++curr;
		}
	}
	auto flistcout=flist.begin();
	while(flistcout!=flist.end())
	{
		cout<<*flistcout<<" ";
		flistcout++;
	}
	cout<<endl;
	return 0;
}
```
- 个人理解：forward_list的插入和删除等操作是在传入迭代器的之后位置操作（比如上例中要删除奇数，传入prev则实际删除的是curr），而list在之前位置操作。
#####  改变容器大小
- 顺序容器array不支持resize操作；
- resize如果要缩小容器，则被删除的元素的迭代器、引用、指针都会失效；如果vector、deque、string进行resize操作可能会导致迭代器、引用、指针会失效。
##### 容器操作可能会使迭代器失效
###### 给容器中插入一个元素之后：
- 如果容器是vector或者string，且存储空间被重新分配，则指向容器的迭代器、指针、引用都会失效。如果没有重新分配空间，则指向插入位置之前的迭代器、指针、引用仍然有效，但指向插入位置之后的元素迭代器、指针、引用都将会失效。
- 对于deque，插入到除首尾之外的任何位置都会导致迭代器、指针、引用的失效。如果在容器的首尾位置添加元素，会导致迭代器失效，但是指向存在元素的指针和引用都不会失效。
- 对于list和forward_list,指向容器的迭代器（包括尾后迭代器和首前迭代器）、指针、引用仍有效
###### 当从容器中删除一个元素之后：
- 对于list和forward_list,指向容器的迭代器（包括尾后迭代器和首前迭代器）、指针、引用仍有效。
- 对于deque,如果在首尾之外的任何位置删除元素，那么指向被删除元素外的其他元素的迭代器、引用、指针；如果删deque尾部元素，则尾后迭代器会失效，但其他迭代器、指针、引用都不失效。如果删首元素，这些也都不会受影响。
- 对于vector和string，指向被删除元素位置之前元素的迭代器、引用、指针都不会失效。

`注意：当删除元素之后，尾后迭代器（比如:vector<int> vint={1,2,3,5,8,7}; vint.end()是尾后迭代器，vint.begin()是首前迭代器......个人理解）`
- 添加/删除vector、string或deque元素的循环程序必须考虑迭代器、指针、引用可能失效的问题；程序保证每个循环步骤中都更新迭代器、引用或指针。如果循环中调用的insert或erase，那个更新迭代器容易了，这些操作都会返回迭代器。
```cpp
#include<iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> vi = {1,2,3,4,5,6,7,8,9,0};
	auto iter = vi.begin();
	while (iter!=vi.end())
	{
		if (*iter%2)
		{
			iter = vi.insert(iter, *iter);
			iter += 2;              //更新迭代器
		}
		else
		{
			iter = vi.erase(iter);  //返回一个指向删除元素下一个的迭代器
		}
	}
	auto iter0 = vi.begin();
	while (iter0!=vi.end())
	{
		cout << *iter0<< " ";
		iter0++;
	}
	cout << endl;
	system("pause");
	return 0;
}
```
- 如果在一个循环中插入/删除deque、vector、string中的元素，不要缓存end返回的迭代器。
##### 管理容器的成员函数
- shrink_to_fit只适用于vecto、string和deque
- capacity只适用于vector和string；
```cpp
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	std::vector<int> vec;
	for (int i=0;i<10;i++)
	{
		vec.push_back(i);
	}
	cout << "没有更改容器大小，库自动分配" << endl;
	cout << "size: " << vec.size() << endl;
	cout << "capacity: " << vec.capacity() << endl;
	vec.shrink_to_fit();   //容器capacity和size一样大小，把多余申请的内存退还回来
	cout << "把容器和size看齐" << endl;
	cout << "size:" << vec.size() << endl;
	cout << "capacity:" << vec.capacity() << endl;
	system("pause");
	return 0;
}
```
##### string
- 如果当我们以const char*去创建一个String时，指针指向的数组必须以空字符结尾，拷贝遇到空字符时停止；如果我们给构造函数传入一个计数值，则不必以空字符结尾；如果没有空字符也没传入计数值，或者给定计数值大小大于数组大小，这种函数行为是未定义的。
- 当从一个string拷贝字符时，可选用一个开始位置以及计数值，开始位置必须小于或等于给定的string大小。如果大于size则构造函数抛出一个out_of_range的异常。如果我们传递了一个计数值，则从给定位置拷贝这么多个字符。不管要拷贝多少个字符，string最多拷贝到尾部，不会更多。
- string的substr操作
    - 可以传递啊给一个可选的位置值和计数值,返回值是一个string;
```cpp
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string str("hello cplusplus");
	cout << str.substr(0, 6) << endl;//输出hello(起始位置为0，向后读取6个字符)
	system("pause");
	return 0;
}
```
##### 适配器（`不知所以然`）
- C++中的容器适配器是干什么的呢？可以做一个类比，我们已有的容器（比如vector、list、deque）就是设备，这个设备支持的操作很多，比如插入，删除，迭代器访问等等。而我们希望这个容器表现出来的是栈的样子：先进后出，入栈出栈等等，此时，我们没有必要重新动手写一个新的数据结构，而是把原来的容器重新封装一下，改变它的接口，就能把它当做栈使用了。
## 泛型算法（第十章）
- 前言
    - 因为实现共同的操作，故而称之为“算法”；而“泛型”指的是他们可以操作在多种容器上--不但可以作用于vector或者list这些标准库类型，还可用在内置数组类型、甚至其他类型的序列上。如果自定义的容器类型只要与标准库兼容，同样使用这些反向算法，解算法最基本的方法是了解该算法是否读元素、写元素或者对元素进行重新排序。
    - 大多数算法是通过遍历两个迭代器标记的一段元素来实现其功能。
    - 泛型算法本身从不执行容器操作，只是单独依赖迭代0和迭代器操作实现器。算法也许会对存储在容器中的值进行改变或删除，但是算法从不直接添加删除容器中的元素，也不直接更改容器的大小。
    - 除了少数情况之外，所有算法都在一段范围内的元素上操作，这个范围称为输出范围，带有输入范围参数的算法总是使用头两个形参标记该范围。这两个形参是分别指向要处理的第一个元素和最后一个元素的下一位置的迭代器。
```cpp
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
int main()
{
	int arr[] = {12,15,16,18,98};
	int val = 98;
	auto result0 = find(begin(arr), end(arr), 18);//对于存在的返回查找值的位置
	auto result = find(begin(arr), end(arr), val);
	auto result1 = find(begin(arr), end(arr), 100);//对于不存在的，返回的是最后一个元素下一位置的迭代器
	cout << result << endl;
	cout << result0 << endl;
	cout << result1 << endl;
	system("pause");
	return 0;
}
```
- 
