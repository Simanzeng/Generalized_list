#pragma once

//广义表类定义

#include"SeqList.h"
#include<iostream>
#include<cassert>
#include<cstdlib>
#include<string>
#include<cctype>

using namespace std;


template<class T>
struct GenListNode;                   //声明结构体GenListNode


template<class T>
struct Items                             //返回值的类结构定义
{
	int utype;                           //=0/1/2
	union                                //联合
	{
		int ref;                         //utype=0,附加头结点，存放引用计数
		T value;                         //utype=1,存放数值
		GenListNode<T> *hlink;           //utype=2，存放指向子表的指针
	}info;
	Items():utype(0),info.ref(0) {}      //构造函数
	Items(Items<T> &RL)                  //复制构造函数
	{
		utype=RL.utype;
		info=RL.info;
	}
};


template<class T>
struct GenListNode                       //广义表结点类定义
{
public:
	GenListNode():utype(0),tlink(NULL) {info.ref=0;}//构造函数
	GenListNode(GenListNode<T> &RL)      //复制构造函数
	{
		utype=RL.utype;
		tlink=RL.tlink;
		info=RL.info;
	}
//private:                               //注意
	int utype;                           //=0/1/2
	GenListNode<T> *tlink;               //指向同一层下一结点的指针
	union                                //联合
	{
		int ref;                         //utype=0,附加头结点，存放引用计数
		T value;                         //utype=1,存放数值
		GenListNode<T> *hlink;           //utype=2，存放指向子表的指针
	}info;
};



template<class T>
class GenList                            //广义表的类定义
{
public:
	GenList();                           //构造函数
	~GenList();                          //析构函数
    bool Head(Items<T> &x);              //返回表头元素x
	bool Tail(GenList<T> &lt);           //返回表尾lt
	GenListNode<T>* First();             //返回第一个元素
	GenListNode<T>* nest(GenListNode<T> *elem);//返回表元素elem的直接后续元素
	void Copy(const GenList<T> &R);      //广义表的复制
	int Length();                        //计算广义表的长度
	int depth();                         //计算一个非递归广义表的深度
	void delvalue(T x);                     //根据给定值在广义表中删除相应结点的算法
	template<class T>
	friend istream& operator >> (istream& in,GenList<T> &L);//友元函数，输入广义表
private:
	GenListNode<T> *first;               //广义表头指针
	GenListNode<T> *Copy(GenListNode<T> *ls);//复制一个ls指示的无共享非递归表
	int Length(GenListNode<T> *ls);      //计算由ls指示的广义表的长度
	int depth(GenListNode<T> *ls);       //计算由ls指示的非递归广义表的深度
	bool equel(GenListNode<T> *s,GenListNode<T> *t);//判断以s和t为表头的两个表是否相等
	void delvalue(GenListNode<T> *ls,T x);//根据给定值在广义表中删除相应结点的算法
	void Remove(GenListNode<T> *ls);     //释放以ls为附加头结点的广义表
	                                     //从输入流对象输入广义表的字符串描述，建立一个带附加头结点的广义表结构
	void Createlist(istream &in,GenListNode<T> * &ls,SeqList<T> &L1,SeqList<GenListNode<T> *> &L2);
};


template<class T>
GenList<T>::GenList()                     //构造函数
{
	first=new GenListNode<T>;
	assert(first!=NULL);
}


template<class T>
GenList<T>::~GenList()                    //析构函数
{
	Remove(first);
}


template<class T>
bool GenList<T>::Head(Items<T> &x)           //返回表头元素x
{
	//若广义表非空，则通过x返回其第一个元素的值，否则函数没有定义
	if(first->tlink==NULL) return false;    //空表，没有返回至可用
	else                                    //非空表
	{
		x.utype=first->tlink->utype;
		x.info=first->tlink->info;
		return true;                        //返回true,返回表头的值
	}
}


template<class T>
bool GenList<T>::Tail(GenList<T> &lt)     //返回表尾lt
{
	//若广义表非空，则通过lt返回广义表除表头元素以外其他元素组成的表，否则函数没有定义
	if(first->tlink==NULL) return false;  //空表
	else                                  //非空表
	{
		lt.first->utype=0;                //设置附加头结点
		lt.first->info=0;
		lt.first->tlink=Copy(first->tlink->tlink);
		return true;
	}
}


template<class T>
GenListNode<T>* GenList<T>::First()       //返回第一个元素
{
	//返回广义表的第一个元素（若表空，则返回一个特定的空置NULL
	if(first-tlink==NULL) return NULL;   //空表
	else return first->tlink;            //非空表
}


template<class T>
GenListNode<T>* GenList<T>::nest(GenListNode<T> *elem)//返回表元素elem的直接后续元素
{
	//返回表元素elem的直接后续元素
	if(elem->tlink==NULL) return NULL;    //空表
	else return elem->tlink;              //非空表
}


template<class T>
void GenList<T>::Copy(const GenList<T> &R)//广义表的复制
{                                         //公有函数
	first=Copy(R.first);                  //调用私有函数
}


template<class T>
int GenList<T>::Length()                 //求广义表的长度
{
	//公有函数，求当前广义表的长度
	return Length(first);
}


template<class T>
int GenList<T>::depth()                  //求一个非递归广义表的深度
{
	//公有函数，求一个非递归表的深度
	return depth(first);
}



template<class T>
void delvalue(T x)                      //根据给定值在广义表中删除相应结点的算法
{
	//公有函数：根据给定值在广义表中删除相应结点的算法
	delvalue(first,x);
}



template<class T>
istream& operator >> (istream& in,GenList<T> &L)  //友元函数，输入广义表
{
	int n;
	cout<<"输入广义表字符串的字符个数"<<endl;
	in>>n;
	//T *Ls1=new T[n];
	SeqList<T> Ls1(n);
	//GenListNode<T> *Ls2=new GenListNode<T>[n];    //创建辅助数组并初始化
	SeqList<GenListNode<T> *> Ls2(n);
	cout<<"请输入广义表字符串(字符和字符之间用空格隔开)：";
	L.Createlist(in,L.first,Ls1,Ls2);               //建立广义表存储结构
	GenListNode<T> *p=L.first;
	L.first=L.first->info.hlink;
	//delete []Ls1;
	//delete []Ls2;
	delete p;
	return in;
}



template<class T>
GenListNode<T>* GenList<T>::Copy(GenListNode<T> *ls)   //复制一个ls指示的无共享非递归表
{
	//私有函数，复制一个ls指示的无共享子表的非递归表
	GenListNode<T> *q=NULL;
	if(ls!=NULL)  
	{
		q=new GenListNode<T>;                                   //处理当前的结点q
		q->utype=ls->utype;                                     //复制结点类型
		switch(ls->utype)                                       //根据utype的值传送信息
		{
		case 0:q->info.ref=ls->info.ref;break;                  //附加头结点
		case 1:q->info.value=ls->info.value;break;              //原子结点
		case 2:q->info.hlink=Copy(ls->info.hlink);break;        //表结点
		}
		q->tlink=Copy(ls->tlink);                               //处理同一层下一结点为头的表
	}
	return q;
}



template<class T>
int GenList<T>::Length(GenListNode<T> *ls) //计算由ls指示的广义表的长度
{
	//私有函数：计算以ls为头指针的广义表的长度
	if(ls!=NULL) return 1+Length(ls->tlink);
	else return 0;
}



template<class T>
int GenList<T>::depth(GenListNode<T> *ls)  //计算由ls指示的非递归广义表的深度
{
	//私有函数：计算由ls指示的非递归广义表的深度
	if(ls->tlink==NULL) return 1;         //ls->tlink==NULL ，空表，深度为1
	GenListNode<T> *temp=ls->tlink;
	int m=0,n;
	while(temp!=NULL)                     //temp在广义表顶层横扫
	{ 
		if(temp->utype==2)                //扫描到的结点utype为表结点时 
		{
			n=depth(temp->info.hlink);    //计算以该结点为头的广义表深度
			if(m<n) m=n;                  //取最大深度
		}
		temp=temp->tlink;
	}
	return m+1;                           //返回深度
}



template<class T>
bool GenList<T>::equel(GenListNode<T> *s,GenListNode<T> *t)//判断以s和t为表头的两个表是否相等
{
	//私有函数：设s与t两个非递归广义表的表头指针，若两表相等，函数返回true，否则返回false
	int x;
	if(s->tlink==NULL && t->tlink==NULL) return true;                      //表s与表t都是空表
	if(s->tlink!=NULL && t->tlink!=NULL && s->tlink-utype==t->tlink->utype)//两表都非空且结点类型相同
	{
		if(s->tlink->utype==1)                                             //原子结点，比较对应数据
		{
			x=(s->tlink->value==t->tlink->value)?1:0;
		}
		else if(s->tlink->utype==2)                                        //子表结点，递归比较其子表
		{
			x=depth(s->tlink->info.hlink,t->tlink->info.hlink);
		}
		if(x==1) return equal(s->tlink,t->tlink)                           //相等，递归比较同一层的下一个结点；不等，不再递归比较
	}
	return false;                                                          //不等，返回false
}




template<class T>
void delvalue(GenListNode<T> *ls,T x)           //根据给定值在广义表中删除相应结点的算法
{
	//私有函数：根据给定值在广义表中删除相应结点的算法
	if(ls->tlink!=NULL)                                                //非空表
	{
		GenListNode<T> *q=ls->tlink;                                   //找到附加头结点后的第一个结点
		while(q!=NULL && q->utype==1 && q->info.value==x)              //若含有x结点，删除它，q指向同层下一个结点
		{
			ls->tlink=q->tlink;
			delete q;
			q=ls->tlink
		}
		if(q!=NULL)
		{
			if(q->utype==2)                                            //在子表中删除
			{
				delvalue(q->info.hlink,x);
			}
			delvalue(q,x);                                             //在以q为头结点的广义表中递归删除
		}
	}
}


template<class T>
void GenList<T>::Remove(GenListNode<T> *ls)     //释放以ls为附加头结点的广义表
{
	//私有函数：释放以ls为附加头结点的广义表
	ls->info.ref--;                                                  //附加头结点的引用计数减1
	if(ls->info.ref<=0)                                              //如果减到0
	{
		GenListNode<T> *q;                                           
		while(ls->tlink!=NULL)                                      //横扫表顶层
		{
			q=ls->tlink;                                            //找到第一个结点
			if(q->utype==2)                                         //递归删除子表
			{
				Remove(q->info.hlink);
				if(q->info.hlink->info.ref<=0)
				{
					delete q->info.hlink;                           //删除子表附加头结点
				}
			}
			ls->tlink=q->tlink;
			delete q;
		}
	}
}



template<class T>                        //从输入流对象输入广义表的字符串描述，建立一个带附加头结点的广义表结构
void GenList<T>::Createlist(istream &in,GenListNode<T> * &ls,SeqList<T> &L1,SeqList<GenListNode<T> *> &L2)
{
	//从广义表的字符串描述s出发，建立一个带附加头结点的广义表结构，要求T为char类型
	//在表L1储存大写字母的表名，在表L2存储表名对应子表结点的地址
	T chr;
	in>>chr;                                       //读入一个字符，此处只可能读入空格（#）、左括号和英文字母
	if(isalpha(chr) && isupper(chr) || chr=='(')   //大写字母或‘（’
	{
		ls=new GenListNode<T>;                     //建立子表结点
		ls->utype=2;                       
		if(isalpha(chr) && isupper(chr))
		{
			int n=L1.Length();
			int m=L1.Search(chr);
			if(m!=0)                               //该表已经建立
			{
				GenListNode<T> *p=L2.Locate(m);    //查子表地址
				p->info.ref++;                     //引用计数加一
			}
			else
			{                                      //保存表名及地址
				L1.Insert(n,chr);
				L2.Insert(m,ls);
			}
			in>>chr;
			if(chr!='(') exit(1);                  //表名后面必跟'('
		}
		ls->info.hlink=new GenListNode<T>;         //建附加头结点
		ls->info.hlink->utype=0;
		ls->info.hlink->info.ref=1;
		Createlist(in,ls->info.hlink->tlink,L1,L2); //递归建子表
		Createlist(in,ls,L1,L2);              //??  递归建后续表
	}
	else if(isalpha(chr) && islower(chr))           //建元素结点
	{
		ls=new GenListNode<T>;
		ls->utype=1;
		ls->info.value=chr;
		Createlist(in,ls,L1,L2);
	}
	else if(chr==',')                               //建后续结点
	{
		Createlist(in,ls->tlink,L1,L2);
	}
	else if(chr==')')  ls->tlink=NULL;              //右括号，链收尾
	else if(chr=='#')  ls=NULL;                     //空表，链收尾
}



