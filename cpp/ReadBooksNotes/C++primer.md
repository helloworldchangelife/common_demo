### �ڶ��� ��2.3����������
##### ���ú�ָ�룺
- �����������ʲô��֪ʶ�㣺���ã�
```
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
�������9 9
- �����Ǹ������ı��ˣ�
```
int *ptr=nullptr;//��ʼ��
int ivalue=20;
ptr=&ivalue;
*ptr=0;
```
�������  �仯����ivalue,��ptrָ�벻��
- ==**���һ���Ƚϸ��ӵ�ָ���������������䣬����������Ķ����������**==
- ����һ������ֵ��==����ָ��==�ĺ�����
```
int (*func(int i))[10]; //����ֵ������ָ��ĺ���
```
- β�÷������ͣ�������ķ���ֵ������ָ��ĺ�����
```
auto func(int i)->int(*) [10];//�κκ����Ķ��嶼��ʹ��β�÷���  �����ڷ���ֵ�Ƚϸ��ӵ���Ϊ��Ч�����磺����ֵ������ָ�������������á���
```
- decltype(���������Ĺؼ���)�����֪�������ķ���ָ��ָ����Ǹ����飬�Ϳ�����decltype�����������ͣ�
```
int odd[5]={1,3,5,7,9};
int even[5]={0,2,4,6,8};
decltype(odd) *arrptr(int i)//��Ҫ�����ָ������   ָ������
{
    return (i%2) ? &odd : &even;//����һ��ָ�������ָ��
}
```
- һ��ӵ�ж���const�βκ���һ��û�ж���const�β��޷����ֿ��������磺
```
int func(int i);
int func(const int i);  //����ģ��ظ�������func  ˵�����ܹ�����
```
- ��һ���棬����β���ĳ�����͵�ָ��������õ�ʱ����ͨ���ж�ָ����ǳ��������Ƿǳ����������ʵ�����أ���ʱconst�ǵײ�ġ�������룺
```
int func(int *ptr)��
int func(const int *ptr);   //�Ϸ����º���  (����)�����ڳ���������   
```
- const_cast������(�� C++primer 6.4)
- ������������:��������������������֣�����������������������ͬ��ʵ�壻
```
string read();
void print(const string &);
void print(double);
void func(int value)
{
	bool read = false;//���������������read
	string s = read();//����read��һ������ֵ�����Ǻ�����ͨ����˵���ھֲ���������������������һ���õ�ѡ��
	
	void print(int);//�������� �������print��ƽʱ���÷����ڲ㣬Ҫ�ŵ���㣩
	
	print("value:");//����print(const string &)�����ص���
	print(value);//��ȷ  ��ǰprint
	print(3.14);//��ȷ�������õ���print(int),print(double)������
}
```
==C++�����У����ֲ��ҳ��������ͼ��֮ǰ��==
- ������;��������
    - Ĭ��ʵ�Σ�ĳ���β��ڶ�ε���ʱ����������ͬ��ֵ���ѷ������ֵ����ֵ�ͽ���Ĭ��ʵ��(һ��ĳ���βα���ΪĬ��ֵ���������βζ�������Ĭ��ֵ.�����޸��Ѿ����ڵ�Ĭ��ֵ)��
    - ����������constexpr:���������������Щ����ֱ�ӡ���ģС��Ƶ�������ĺ��������ٺ������ô���������ϵͳ��Դ��������������ֻ�����������һ�����󣬱��������Ժ�����������ܵ���˵�����Ż�����
    - 
- decltype �ӱ��ʽ�ƶϳ����������ͣ�decltype(fun()) sum �� ��sum������fun�ķ������ͣ�
- ����ָ��
```
bool lengthCompare(const string &,const string &);
//pfָ��һ������
bool *pf(const string &,const string &);
//ʹ�ú���ָ��
pf=lengthCompare;//ָ��lenfgthCompare
pf=&lengthCompare;//�ȼ�����һ����ȡ��ַ���ǿ�ѡ��

//������ֱ��ʹ�ú���ָ����øú�����������ǰ������ָ��
bool b0=pf("hello","goodbye");//����lengthCompare����
bool b2=(*pf)("hello","goodbye");//��ǰ��ȼ�
bool b3=lengthCompare("hello","goodbye");//��һ���ȼ۵ĵ���
```
- ��ָ��ͬ�������͵�ָ��䲻����ת��ԭ�򡣣������ǿ��Ը�ָ�븳ֵһ��nullptr����ֵΪ0�����ͳ������ʽ����ʾ��ָ��û��ָ���κ�һ��������
```
string::size_type sumlength(const string& ��const string&)��
bool cstringCompare(const char*,const char*);
pf=0;//��ȷ��pf��ָ���κκ���
pf=sumlength   //���󣺷������Ͳ�ƥ��
pf=cstringCompare;//�����β����Ͳ�ƥ��
pf=lengthCompare; //��ȷ��������ָ������;�ȷƥ��
```
### ������  ��
##### ���캯��
- Ĭ�Ϲ��캯��ֻ����������Щ�ǳ��򵥵���
- ����һ����ͨ�࣬Ҫ�Լ����幹�캯����ԭ���У�
    -  ֻ�е���û���������κι��캯��������£��������Ż��Զ�����Ĭ�Ϲ��캯��
    -  ���������������ͻ��߸������͵ĳ�Ա����ֻ�е���Щ��Աȫ�������������ڵĳ�ʼֵʱ�������ſ���ʹ�úϳ�Ĭ�Ϲ��캯����
    -  ����������ΪĳЩ��ϳ�Ĭ�ϵĹ��캯����
- һ�������  ��������ڳ�ʼ��ֵ
- ���Ҫ�õ���Ԫ������һ������� Ҫ��������������Ԫ����  ���������ͬһ��ͷ�ļ��У��������ͷ�ļ������ⵥ��������Ҫ��Ԫ�ĺ�����
```
//test.h�ļ���������
#include<stdio.h>
#include<iostream>

func(int a);//��������

class test
{
    test()
    {}
    ~test()
    {}
    friend func(int a);  //��Ԫ
};
```
- ��Ԫ��������Ԫ�ࣨ���B���ĳЩ��Ա������Ҫ�����������A����ڲ����ݣ�һ����private���ݣ���
```
class A
{
    friend class B;
}
```
- ��Ԫ���������д����ԣ�A����Ԫ��B��B����Ԫ��C����C���޷�����A����ķǹ��г�Ա��
```
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
    //���������޷����ʵ���result����˵����Ԫ�����ڴ�����
}
```
- �����Ԫ���Ƿǳ�Ա��������������ĳ�Ա������������������Ԫ��ʱ����ж��壬����������֮ǰ�����ſ��Ե��ã����е��ֿ�  ���C++primer7.3.4��
##### ���캯����̽
- ��ֵ���ʼ�������𣺸�ֵ���ȳ�ʼ���ٸ�ֵ�������￼��Ч������Ļ������ɹ��캯����ʼֵ�ĺ�ϰ�ߣ���Ϊ�е����ݱ�����Ҫ��ʼ��������const���ε����ݣ�
- ί�й��캯�����������е�һ�����캯��ͨ����ʼ���б�ʽ������ͬһ�����е���һ�����캯��
```
class X
{
 public:
    X(const string& name) : name_(name) 
    { 
     ...
    }
    //��������X�е���һ�����캯�����䲻�����κβ�����
    //����ͨ����ʼ���б�ʽ����������Ĺ��캯��
    X() : X("ί�й���") { } ��
};

```
- explicit�ؼ���ֻ�������ڹ��캯��������ʹ��
```
//���󣺹ؼ���explicitֻ������������ڹ��캯��������
explicit SS::SS(istream& is)
{
    return (is,*this);
}
```
- ������ʽת����һ�����ʱ������ִ�п�����ʽ�ĳ�ʼ����ʹ��=��������explicit�ؼ��������Ĺ��캯����ֻ��ʹ��ֱ�ӳ�ʼ���ķ�ʽ��
```
class SS
{
   SS()=default;
   
   explicit SS(std::istream&);
};
//��ȷ��ֱ�ӳ�ʼ��
SS::SS test(scin);
//���� ���ܽ�explicit���캯�����ڿ���ʽ�ĳ�ʼ��
SS::SS test=scin;
```
- constexpr:��C++11�������Ĺؼ��֣��������ǡ��������ʽ����Ҳ�����ڱ����ڿ���ֵ�ı��ʽ��������ĳ������ʽ��������ֵ��ȫ�ֱ���/�����ĵ�ַ��sizeof�ȹؼ��ַ��صĽ�����������������ʽ�����ɻ������ʽͨ������ȷ��������õ��ġ�constexprֵ������enum��switch�����鳤�ȵȳ��ϡ�
```
constexpr int Inc(int i) {
    return i + 1;
}
 
constexpr int a = Inc(1); // ok
constexpr int b = Inc(cin.get()); // !error
constexpr int c = a * 2 + 1; // ok
```
- constexpr��������������Ĺ��캯��������֤����ṩ���ù��캯���Ĳ�������constexpr����ô�����Ķ����е����г�Ա������constexpr���ö���Ҳ����constexpr�����ˣ������ڸ���ֻ��ʹ��constexpr�ĳ��ϡ�ע�⣬constexpr���캯��������һ���յĺ����壬�����г�Ա�����ĳ�ʼ�����ŵ���ʼ���б��С�
```
struct A {
    constexpr A(int xx, int yy): x(xx), y(yy) {}
    int x, y;
};
 
constexpr A a(1, 2);
enum {SIZE_X = a.x, SIZE_Y = a.y};
```
- ==constexpr�����εı���һ���Ǳ����ڿ���ֵ�ģ������εĺ����������в�������constexprʱ��һ���᷵��constexpr��==
- constexpr�ĺô���
    - ��һ�ֺ�ǿ��Լ�������õر�֤�������ȷ���岻���ƻ���
    - �����������ڱ����ڶ�constexpr�Ĵ�����зǳ�����Ż������罫�õ���constexpr���ʽ��ֱ���滻�����ս���ȡ�
    - ��Ⱥ���˵��û�ж���Ŀ�����������ȫ�ɿ���
- ����ֵ�����ࣺ��constexpr���������ͷ���ֵ������������ֵ���ͣ�
- �����������������涨��ĺ���Ϊ����������
- �ۺ��ࣺ���г�Ա����public��û�ж����κι��캯����û�����ڳ�ʼֵ��û�л��࣬Ҳû���麯��(virtual)��
# C++��׼��
#### IO��
- IO����û�п�����ֵ����
- IO��д��������״ֵ̬��badbit��ϵͳ�����󣬲��ɻָ��ģ�һ������λ�����������޷�ʹ���ˣ�failbit����λ��������������ȡһ����ֵȴ����һ���ַ������������������������Լ���ʹ�á�
##### �����������
- ˢ�������������
```
cout<<"hello"<<endl;  //���hello��һ�����У�Ȼ��ˢ�»�����
cout<<"hello"<<ends;  //���hello��һ�����ַ���Ȼ��ˢ�»�����
cout<<"hello"<<flush; //���hello��Ȼ��ˢ�»��������������κ��ַ�
```
- ˢ�»���������;����ʱ����������ݻᱻ��������������Ⱦ����Ӱ��������Ҫ�Ľ������������⣬��̫׼ȷ��
- tie���������汾������һ���ǲ��������ģ�����ָ���������ָ�루���ǹ������������ָ�룩����һ���汾�Ǵ�����������һ��ָ��ostream�����������ָ�룬���Լ�������ostream�ϡ���x.tie(&o)��x�����������o���档
```
cin.tie(&cout);   //��׼�⽫cin������cout(tie�������İ汾)
```
- ���볹�׽⿪��������Ҫ��һ����ָ���ȥ��
```
ostream* old_tie=cin.tie(nullptr);
```
- 2017-11-23
- ����C++primer�����ifstream��ofstream��fstream���֪ʶ�㣬�ڴ��ļ���ȡ���ڴ棨ifstream��ʱ�����ֿո����֮���ܽ��ж�ȡ�����磺file.txt�ļ���������"cpp is best",����ȡ����������һ���ո�֮���ȡ��"cpp"��;�������������֮���������ѵ�����ʹ��istreambuf_iterator,��ȡ���ַ�(��Ҫһ��һ���ַ�����ʱ����ʹ��istreambuf_iterator),istreambuf_iterator(Effective STL�����֪ʶ��)��ϸ���ݼ���http://blog.csdn.net/bichenggui/article/details/4710996
```
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
		fout.open("/home/wyf/demo_wyf/file.txt",ios::app|ios::out);//��ʽָ���ļ�ģʽ�������ļ��е�ԭ����
		fout<<"cppisbest"<<endl;
		fout.close();
	}
	else
	{
		cout<<"�޷����ļ��޷�������ļ���"<<endl;
	}
	ifstream fin("/home/wyf/demo_wyf/file.txt");
	if(fin)
	{
		string buffer((istreambuf_iterator<char>(fin)),istreambuf_iterator<char>());//������ǽ�����ڿո�������ַ��Ķ�ȡ
		//Ҳ����ʹ��istream_iterator(�����б׶ˣ���Ҫ���Ķ���̫�࣬��ϸ���鿴������ַ������Ͳ���������)
		fin.close();
		cout<<buffer;
	}
	else
	{
		cout<<"�ļ��޷����޷����ļ�д���ڴ�"<<endl;
	}
	return 0; 
}
```
- ��һ��fstream��������ʱ��close()�ᱻ�Զ����ùر��ļ���
- ofstream���ļ�֮�󣬴��ڴ�������д�뵽�ļ�ʱ������ļ������������ݣ�Ҫ�뱣��ס��������Ҫ�ڴ��ļ�ʱ��ʾָ���÷�����ios::app����ios::in��
- ÿ�δ��ļ���Ҫ�����ļ���ģʽ����������ʽ�����ã�Ҳ��������ʽ�����ã�������δ����ʱ��Ĭ�����á�
```
�ļ�ģʽ�У�
in���Զ���ʽ��
out����д��ʽ��
app��ÿ�β���ǰ����λ���ļ�βĩ��
ate�����ļ���������λ���ļ�βĩ��
trunc���ض��ļ�  ֻ��out��ʱ��ſ�������truncģʽ
binary:�Զ����Ʒ�ʽ����IO
```
#### string��
```
//�������ַ����Կո�ָ��eg:����"wangyufei 000"  ���"wangyufei"��"000"��
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
	istringstream ss(line);//Ҳ������stringstream
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
- stringstream������fream,���Զ�Ҳ����д��istringstream��string���ж�ȡ���ݣ�ostringstream��stringд���ݣ�
- ostringstream�����Ϲ������ʱ�����ϣ����һ���ӡ����ʱ��ostringstream������á�
### �ھ��£�˳������
- ˳�������У�
    - list:˫������֧�ֲ���ɾ���ٶȺܿ죬��Ҳ�ڴ���⿪����
    - vector���ɱ��С���顣֧�ֿ���������ʣ���ͷβ֮��Ĳ��ֲ���ɾ��Ԫ���ٶȿ��ܺ�����
    - deque��˫�˶��С�֧��������ʡ�ͷβ���ֲ����ɾ���ٶȺܿ졣
    - forward_list����������ֻ֧�ֵ���˳����ʣ���������κ�λ�ò���ɾ�����ܿ졣��list���ƣ��ڴ���⿪��Ҳ�ϴ�(��֧�ֻ�ȡԪ����Ŀc.size()����)
    - array���̶������С��֧�ֿ��ٲ��ң���Ϊ�̶���С��������ӻ���ɾ����==ע�⣺arrayû��Ĭ�Ϲ��캯��==  ==((1)��֧��ָ����Χ��Ԫ�ؿ��������磺C c(b,e)��b��e��Χ�ڵ�Ԫ�ؿ�����c��(2)���ܽ������Ԫ���滻���б��е�Ԫ�ء����磺c1={a,b,c...})==
    - string����vector���Ƶ�����������ר�ű����ַ�����������ʿ졢β������ɾ���졣
- c��ͷ(����cbegin\cend��)����C++11�ģ��±�׼�������ǣ�
```
begin():Return iterator to beginning (public member function )
cbegin():Return const_iterator to beginning (public member function )//���߷��ص���һ�������޸ĵĵ�������ǰ�߿��޸ġ� 
```
- ֻ��˳�������Ĺ��캯�����ܽ��ܴ�С����������array��
- Ϊ������һ������������һ�������������������ͺ�Ԫ������Ҫ���뵱ƥ�䡣
```
list<string> auth={"a","b","c"};
list<string> list2(auth);   //��ȷ��
deque<string> authdeque(auth);  //���� �������Ͳ�ƥ��
list<char> ccauth(auth);   //����Ԫ�����Ͳ�ƥ��
```
- �����ݵ���������������һ����Χʱ���������Ϳ��Բ�ͬ��Ԫ������Ҳ���Բ�ͬ��
```
vector<const char*> vtest={"aa","bb","cc"};
forward_list<string> fltest(vtest.begin(),vtest.end());//���԰�"const char*"ת��Ϊstring
```
- C++�±�׼�п��Զ�˳������(��array֮��)�����б��ʼ��
```
vector<string> str={"wyf","www","comcom"};
```
- ��ֵ�������ᵼ����������ĵ�������ָ�������ʧЧ;��swap����ʹ����ʧЧ����������Ϊarray��string��������⣩��
- assign�����������ڹ���������array���������ڳ�array��˳��������
```
//assign����;��
list<string> list0;
vector<const char*> vtest;
list0=vtest;//�����������Ͳ�ƥ��
//��ʱ��assign�͸��ϳ���
//��const char*ת��Ϊstring
list0.assign(vtest.begin(),vtest.end());
```
- ��array�⣬swap������������κ�Ԫ�صĿ�����ɾ�������������ʶ��ɱ�֤�ڳ���ʱ������ɡ���array������������ͬ���������Ľ�������array��Ԫ�أ��ʶ���������array������Ҫʱ���Ԫ�����������ȣ�
- string���������������Ԫ�ص��ƶ�������������ǣ������������ӣ�����iter��swap֮ǰָ��vsc1[3]��swap֮��ָ�����vsc2[3]���ʶ�������������һ����string�����ָ�롢��������ʧЧ��
```
vector<string> vsc1(10);
vector<string> vsc2(20);
swap(vsc1,vsc2);
```
```
/*************************************************************************
	> File Name   : sequence_string.cpp
	> Author      : wangyifei
	> Mail        : wangyufei.coder@gmail.com 
	> Created Time: Sun 26 Nov 2017 09:00:05 PM EST
    > Platform    : Linux Centos
 ************************************************************************/
//ʾ��
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str="cpp is best";
	string::iterator start=str.begin();
	string::iterator end=str.end();
	cout<<"��ӡstring����Ԫ��"<<endl;
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
- �������������ÿ��������֧�֣�==��!=��;����������������������������֧�ֹ�ϵ�������>,>=,<,<=������ϵ������������ߵ���������������ͬ���͵����������ұ�����ͬ���͵�Ԫ�ء�
- ���������Ƚϴ�С�����һ��������Ԫ�ز�����һ������ǰ׺�������У������ǵıȽϽ��ȡ���ڵ�һ��Ԫ�صıȽϽ����
```
vector<int> v0={1,3,5,7,9,11,12}//�б��ʼ������
vector<int> v1={1,3,5,9}
v0<v1   //true   ��Ϊ��v0[3]<v1[3]
```
- ˳�������͹��������Ĳ�֮ͬ��������ֹԪ�صķ�ʽ��ͬ����Щ��ֱͬ�ӹ�ϵ��Ԫ�ص�ɾ�������롢�޸ġ����ʲ�����
- ��array֮��ĵ��������ṩ�����ڴ����,������ʱ��̬��ӻ���ɾ���ı�������С��
- ��һ��vector��string��deque�������һ��Ԫ�ػ�ʹ����ָ�������ĵ�������ָ�롢���ö�ʧЧ��
##### �������������Ԫ��
- push_front��list��forward_list��deque֧��push_front��:��Ԫ�ز��뵽����ͷ����
- push_back������array��forward_list������������֧�ָò�����:��Ԫ��׷�ӵ�����β����
- insert��forward_list��������insert��:����ָ����Χ���Ԫ�ء��ض�λ�����Ԫ�ء�
- emplace(emplace_back\emplace_front\emplace)�ں���ֱ���������й���Ԫ�أ����ݸ�emplace�Ĳ�������Ҫ��Ԫ�����͵Ĺ��캯����ƥ�䡣��==��֪ʶ��==��
##### ��������Ԫ��
- ÿ��˳����������һ��front��Ա�������������ڵ�һ��Ԫ�أ���Ԫ�ص����ã�
- ��forward_list֮���˳����������һ��back��Ա������βԪ�ص����ã�
- �������з���Ԫ�صĳ�Ա��������back��front���±ꡢat�����صĶ������ã����������һ��const�����򷵻ص���const���á�
- ���������Ҫ�±�Ϸ������Բ���at��Ա������
```
vector<string> vstr;//��vector
cout<<vstr[0];//����ʱ����vstr��û��Ԫ��
cout<<vstr.at(0);//�׳�һ��out_of_range���쳣
```
##### ɾ�������ڵ�Ԫ��
- forward_list��֧��pop_back,������汾��erase��
- vector��string����֧��pop_front;
- dequeɾ����βԪ��֮����κ�Ԫ�ض��������еĵ�������ָ�롢����ʧЧ��ָ��vector��stringɾ����֮��λ�õĵ�������ָ�롢���ö���ʧЧ��
```
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
- ɾ������������Ԫ��ʱ����clear��Ա��������Χɾ����ʱ����erase��Ա������
##### forward_list���������
- �ο���ַ�� http://www.linuxidc.com/Linux/2017-01/139905.htm
- forward_list�ǵ��������ڲ�ֻά���˵����������Ϣ����ˣ�forward_list�ĵ�������ǰ���������forward intertor)������֮�⣬���ǵĲ������Ҳ�����ԵĲ�ͬ�����������ڴ���ĵ������ϣ�list::insert���ڴ���ĵ�����֮ǰ���룻forward_list::insert:�ڴ���ĵ�����֮����롣
- forward_listû��insert��emplace��erase������insert_after,emplace_after,erase_after����Ԫ�ص�ǰ����㣺before_begin,before_cbegin��
- forward_listɾ�����߲����ʱ����Ҫ֪����λ��Ԫ�ص�ǰ���������ı�ǰ�������ӣ�����forward_list��һ����������û�м򵥵ķ�����ȡǰ���������forward_list������ӻ���ɾ��ʱ��ͨ���ı�ĸ���Ԫ��֮���Ԫ�ء�
```
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
	auto prev=flist.before_begin();//��ʾflist����ǰԪ�أ��ҵ���� ����flist��һ��Ԫ�ص�ǰ���ɣ�
	auto curr=flist.begin();       //��ʾflist�ĵ�һ��Ԫ��
	while(curr!=flist.end())
	{
		if(*curr%2)
		{
			curr=flist.erase_after(prev);//currָ����������һ��Ԫ�� prev���ֲ��䣬��ָ���£�curr֮ǰ��Ԫ��
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
- ������⣺forward_list�Ĳ����ɾ���Ȳ������ڴ����������֮��λ�ò���������������Ҫɾ������������prev��ʵ��ɾ������curr������list��֮ǰλ�ò�����
#####  �ı�������С
- ˳������array��֧��resize������
- resize���Ҫ��С��������ɾ����Ԫ�صĵ����������á�ָ�붼��ʧЧ�����vector��deque��string����resize�������ܻᵼ�µ����������á�ָ���ʧЧ��
##### �����������ܻ�ʹ������ʧЧ
###### �������в���һ��Ԫ��֮��
- ���������vector����string���Ҵ洢�ռ䱻���·��䣬��ָ�������ĵ�������ָ�롢���ö���ʧЧ�����û�����·���ռ䣬��ָ�����λ��֮ǰ�ĵ�������ָ�롢������Ȼ��Ч����ָ�����λ��֮���Ԫ�ص�������ָ�롢���ö�����ʧЧ��
- ����deque�����뵽����β֮����κ�λ�ö��ᵼ�µ�������ָ�롢���õ�ʧЧ���������������βλ�����Ԫ�أ��ᵼ�µ�����ʧЧ������ָ�����Ԫ�ص�ָ������ö�����ʧЧ��
- ����list��forward_list,ָ�������ĵ�����������β�����������ǰ����������ָ�롢��������Ч
###### ����������ɾ��һ��Ԫ��֮��
- ����list��forward_list,ָ�������ĵ�����������β�����������ǰ����������ָ�롢��������Ч��
- ����deque,�������β֮����κ�λ��ɾ��Ԫ�أ���ôָ��ɾ��Ԫ���������Ԫ�صĵ����������á�ָ�룻���ɾdequeβ��Ԫ�أ���β���������ʧЧ����������������ָ�롢���ö���ʧЧ�����ɾ��Ԫ�أ���ЩҲ��������Ӱ�졣
- ����vector��string��ָ��ɾ��Ԫ��λ��֮ǰԪ�صĵ����������á�ָ�붼����ʧЧ��

==ע�⣺��ɾ��Ԫ��֮��β�������������:vector<int> vint={1,2,3,5,8,7}; vint.end()��β���������vint.begin()����ǰ������......������⣩==
- ���/ɾ��vector��string��dequeԪ�ص�ѭ��������뿼�ǵ�������ָ�롢���ÿ���ʧЧ�����⣻����֤ÿ��ѭ�������ж����µ����������û�ָ�롣���ѭ���е��õ�insert��erase���Ǹ����µ����������ˣ���Щ�������᷵�ص�������
```
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
			iter += 2;              //���µ�����
		}
		else
		{
			iter = vi.erase(iter);  //����һ��ָ��ɾ��Ԫ����һ���ĵ�����
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
- �����һ��ѭ���в���/ɾ��deque��vector��string�е�Ԫ�أ���Ҫ����end���صĵ�������
##### ���������ĳ�Ա����
- shrink_to_fitֻ������vecto��string��deque
- capacityֻ������vector��string��
```
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
	cout << "û�и���������С�����Զ�����" << endl;
	cout << "size: " << vec.size() << endl;
	cout << "capacity: " << vec.capacity() << endl;
	vec.shrink_to_fit();   //����capacity��sizeһ����С���Ѷ���������ڴ��˻�����
	cout << "��������size����" << endl;
	cout << "size:" << vec.size() << endl;
	cout << "capacity:" << vec.capacity() << endl;
	system("pause");
	return 0;
}
```
##### string
- �����������const char*ȥ����һ��Stringʱ��ָ��ָ�����������Կ��ַ���β�������������ַ�ʱֹͣ��������Ǹ����캯������һ������ֵ���򲻱��Կ��ַ���β�����û�п��ַ�Ҳû�������ֵ�����߸�������ֵ��С���������С�����ֺ�����Ϊ��δ����ġ�
- ����һ��string�����ַ�ʱ����ѡ��һ����ʼλ���Լ�����ֵ����ʼλ�ñ���С�ڻ���ڸ�����string��С���������size���캯���׳�һ��out_of_range���쳣��������Ǵ�����һ������ֵ����Ӹ���λ�ÿ�����ô����ַ�������Ҫ�������ٸ��ַ���string��࿽����β����������ࡣ
- string��substr����
    - ���Դ��ݰ���һ����ѡ��λ��ֵ�ͼ���ֵ,����ֵ��һ��string;
```
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string str("hello cplusplus");
	cout << str.substr(0, 6) << endl;//���hello(��ʼλ��Ϊ0������ȡ6���ַ�)
	system("pause");
	return 0;
}
```
##### ��������==��֪����Ȼ==��
- C++�е������������Ǹ�ʲô���أ�������һ����ȣ��������е�����������vector��list��deque�������豸������豸֧�ֵĲ����ܶ࣬������룬ɾ�������������ʵȵȡ�������ϣ������������ֳ�������ջ�����ӣ��Ƚ��������ջ��ջ�ȵȣ���ʱ������û�б�Ҫ���¶���дһ���µ����ݽṹ�����ǰ�ԭ�����������·�װһ�£��ı����Ľӿڣ����ܰ�������ջʹ���ˡ�
## �����㷨����ʮ�£�
- ǰ��
    - ��Ϊʵ�ֹ�ͬ�Ĳ������ʶ���֮Ϊ���㷨�����������͡�ָ�������ǿ��Բ����ڶ���������--��������������vector����list��Щ��׼�����ͣ��������������������͡������������͵������ϡ�����Զ������������ֻҪ���׼����ݣ�ͬ��ʹ����Щ�����㷨�����㷨������ķ������˽���㷨�Ƿ��Ԫ�ء�дԪ�ػ��߶�Ԫ�ؽ�����������
    - ������㷨��ͨ������������������ǵ�һ��Ԫ����ʵ���书�ܡ�
    - �����㷨����Ӳ�ִ������������ֻ�ǵ�����������0�͵���������ʵ�������㷨Ҳ���Դ洢�������е�ֵ���иı��ɾ���������㷨�Ӳ�ֱ�����ɾ�������е�Ԫ�أ�Ҳ��ֱ�Ӹ��������Ĵ�С��
    - �����������֮�⣬�����㷨����һ�η�Χ�ڵ�Ԫ���ϲ����������Χ��Ϊ�����Χ���������뷶Χ�������㷨����ʹ��ͷ�����βα�Ǹ÷�Χ���������β��Ƿֱ�ָ��Ҫ����ĵ�һ��Ԫ�غ����һ��Ԫ�ص���һλ�õĵ�������
```
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
int main()
{
	int arr[] = {12,15,16,18,98};
	int val = 98;
	auto result0 = find(begin(arr), end(arr), 18);//���ڴ��ڵķ��ز���ֵ��λ��
	auto result = find(begin(arr), end(arr), val);
	auto result1 = find(begin(arr), end(arr), 100);//���ڲ����ڵģ����ص������һ��Ԫ����һλ�õĵ�����
	cout << result << endl;
	cout << result0 << endl;
	cout << result1 << endl;
	system("pause");
	return 0;
}
```
- 