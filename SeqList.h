#pragma once

//顺序表类定义

//#include"linearList.h"
#include<iostream>
#include<cstdlib>

using namespace std;

const int defaultSize=100;

template<class T>
class SeqList
{
protected:
	T *data;                                          //存放数组
	int maxSize;                                      //最大可容纳表项的项数
	int last;                                         //当前已存放表项的最后位置（从0开始）
	void reSize(int newSize);                         //改变data数组空间大小
public:
	SeqList(int sz=defaultSize);                      //构造函数
	SeqList(SeqList<T> &L);                           //复制构造函数
	~SeqList(){delete []data;}                        //析构函数
	int Size()const{return maxSize;}                  //计算表最大可容纳表项个数
	int Length()const {return last+1;}                //计算表长度
	int Search(T& x)const;                            //搜索x在表中位置，函数返回表项序号
	T Locate(int i)const;                           //定位第i个表项，函数返回表项序号
	bool getData(int i,T& x)const                     //取第i个表项的值
	{
		if(i>0 && i<=last+1)
		{
			x=data[i-1];
			return true;
		}
		else return false;
	}
	bool setData(int i,T& x)                          //修改第i个表项的值
	{
		if(i>0 && i<last+1)
		{
			data[i-1]=x;
			return true;
		}
		else return false;
	}
	bool Insert(int i,T& x);                          //插入x在第i个表项之后
	bool Remove(int i,T& x);                          //删除第i个表项，通过x返回表项的值
	bool IsEmpty()const                               //判断表空否，空则返回true,否则返回false
	{
		return (last==-1)?true:false;
	}
	bool IsFull()const                                //判断表满否，满则返回true,否则返回false
	{
		return (last==maxSize-1)?true:false;
	}
	void input();                                     //输入
	void output();                                    //输出
	SeqList<T> operator = (SeqList<T> &L);           //表整体赋值

};



template<class T>
SeqList<T>::SeqList(int sz)
{
	//构造函数，通过指定参数sz定义数组的长度
	if(sz>0)
	{
		maxSize=sz;
		last=-1;                                      //置表的实际长度为空
		data=new T[maxSize];                          //创建顺序表存储数组
		if(data==NULL)                                //动态分配错误
		{
			cerr<<"存储分配错误！"<<endl;
				exit(1);
		}
	}
}



template<class T>
SeqList<T>::SeqList(SeqList<T> &L)
{
	//复制构造函数，用参数表中给出的已有顺序表初始化新建顺序表
	maxSize=L.Size();
	last=L.Length()-1;
	data=new T[maxSize];                              //创建顺序表存储数组
	if(data==NULL)                                    //动态分配错误
	{
		cerr<<"存储分配错误！"<<endl;
			exit(1);
	}
	T value;
	for(int i=0;i<=last;i++)
	{
		L.getData(i+1,value);
		data[i]=value;
	}
}



template<class T>
void SeqList<T>::reSize(int newSize)
{
	//私有函数：扩充顺序表的存储数组空间大小，新数组的元素个数为newSize
	if(newSize<=0)                                    //检查数组大小的合理性
	{
		cerr<<"无效的数组大小！"<<endl;
		exit(1);
	}
	else if(newSize<=maxSize)
	{
		cerr<<"数组大小比原有数组小"<<endl;
		exit(1);
	}
	else                                              //修改数组大小
	{
		T *newarray=new T[newSize];                   //建立新数组
		if(newarray==NULL)                            //分配错误
		{
			cerr<<"存储分配错误！"<<endl;
		}
		int n=last+1;
		T *srcptr=data;                               //原数组的首地址
		T *destptr=newarray;                          //目的数组的首地址
		while(n--)
		{
			*destptr++=*srcptr++;                     //复制各表项的值
		}
		delete []data;                                //删除原有数组
		data=newarray;                                //复制新数组
		maxSize=newSize;
	}

}



template<class T>
int SeqList<T>::Search(T& x)const
{
	//搜索函数：在表中顺序搜索与给定值x匹配的表项，找到则函数返回该表项是第几个元素,否则函数返回0，表示搜索失败
	for(int i=0;i<=last;i++)                          //顺序搜索
	{
		if(data[i]==x) return i+1;
	}
	return 0;                                         //搜索失败
}



template<class T>
T SeqList<T>::Locate(int i)const
{
	//定位函数：函数返回第i（1<=i<=last+1)个表项的值，否则函数返回0，表示定位失败
	if(i>=1 && i<=last+1) return data[i-1];
	else return 0;
}



template<class T>
bool SeqList<T>::Insert(int i,T& x)
{
	//将新元素x插入到表中第i（0<=i<=last+1)个表项之后。函数返回插入情况，若插入成功，则返回true；
	//否则返回false；i=0是虚拟的，实际上是插入到第1个元素位置
	if(last==maxSize-1)                               //表满，不能插入，扩充数组
	{
		reSize(maxSize+defaultSize);
	}
	if(i<0 || i>last+1) return false;                 //参数i不合理，不能插入
	for(int j=last;j>=i;j--)                          //依次后移，空出第i号位置
	{
		data[j+1]=data[j];
	}
	data[i]=x;                                        //插入
	last++;                                           //最后位置加1
	return true;                                      //插入成功
}



template<class T>
bool SeqList<T>::Remove(int i,T& x)
{
	//从表中删除第i（1<=i<=last+1)个表项，通过引用型参数x返回删除的元素值。函数返回删除情况
	//若删除成功则返回true,否则返回false.
	if(last==-1)                                      //表空，不能删除
	{
		cerr<<"顺序表为空表，不能执行删除操作！"<<endl;
		return false;
	}
	if(i<1 || i>last+1)                               //参数i不合理，不能删除
	{
		cerr<<"参数i不合理，不能执行删除操作！"<<endl;
		return false;
	}
	x=data[i-1];                                      //存被删元素的值
	for(int j=i;j<last+1;j++)                         //依次前移，填补。
	{
		data[j-1]=data[j];
	}
	last--;                                           //最后位置减1
	return true;
}



template<class T>
void SeqList<T>::input()
{
	//从标准输入（键盘）逐个输入数据，建立顺序表
	cout<<"开始建立顺序表，请输入表中元素个数：";
	int n;
	while(1)
	{
		cin>>n;                                        //输入表元素的个数
		if(n>0 && n<=maxSize) break;
		cout<<"表元素个数输入有误，范围应在(1,"<<maxSize+1<<")之中"<<endl;
		cout<<"请重新输入：";
	}
	for(int i=0;i<n;i++)                              //逐个输入表元素
	{
		cout<<"请输入第"<<i+1<<"个表元素：";
		cin>>data[i];
	}
	last=n-1;                                         //表元素的最后位置
}



template<class T>
void SeqList<T>::output()
{
	//将顺序表全部输出到屏幕上。
	cout<<"顺序表当前元素的个数为："<<last+1<<endl;
	for(int i=0;i<=last;i++)
	{
		cout<<"第"<<i+1<<"个元素为："<<data[i]<<endl;
	}
	cout<<"元素输出完成！"<<endl;
}



template<class T>
SeqList<T> SeqList<T>::operator = (SeqList<T> &L)
{
	//重载函数：顺序表整体赋值。
	maxSize=L.Size();
	last=L.Length()-1;
	data=new T[maxSize];                              //创建顺序表存储数组
	if(data==NULL)                                    //动态分配失败
	{
		cerr<<"存储分配错误！"<<endl;
		exit(1);
	}
	T value;
	for(int i=1;i<=last+1;i++)
	{
		L.getData(i,value);
		data[i-1]=value;
	}
}