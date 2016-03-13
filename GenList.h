#pragma once

//������ඨ��

#include"SeqList.h"
#include<iostream>
#include<cassert>
#include<cstdlib>
#include<string>
#include<cctype>

using namespace std;


template<class T>
struct GenListNode;                   //�����ṹ��GenListNode


template<class T>
struct Items                             //����ֵ����ṹ����
{
	int utype;                           //=0/1/2
	union                                //����
	{
		int ref;                         //utype=0,����ͷ��㣬������ü���
		T value;                         //utype=1,�����ֵ
		GenListNode<T> *hlink;           //utype=2�����ָ���ӱ��ָ��
	}info;
	Items():utype(0),info.ref(0) {}      //���캯��
	Items(Items<T> &RL)                  //���ƹ��캯��
	{
		utype=RL.utype;
		info=RL.info;
	}
};


template<class T>
struct GenListNode                       //��������ඨ��
{
public:
	GenListNode():utype(0),tlink(NULL) {info.ref=0;}//���캯��
	GenListNode(GenListNode<T> &RL)      //���ƹ��캯��
	{
		utype=RL.utype;
		tlink=RL.tlink;
		info=RL.info;
	}
//private:                               //ע��
	int utype;                           //=0/1/2
	GenListNode<T> *tlink;               //ָ��ͬһ����һ����ָ��
	union                                //����
	{
		int ref;                         //utype=0,����ͷ��㣬������ü���
		T value;                         //utype=1,�����ֵ
		GenListNode<T> *hlink;           //utype=2�����ָ���ӱ��ָ��
	}info;
};



template<class T>
class GenList                            //�������ඨ��
{
public:
	GenList();                           //���캯��
	~GenList();                          //��������
    bool Head(Items<T> &x);              //���ر�ͷԪ��x
	bool Tail(GenList<T> &lt);           //���ر�βlt
	GenListNode<T>* First();             //���ص�һ��Ԫ��
	GenListNode<T>* nest(GenListNode<T> *elem);//���ر�Ԫ��elem��ֱ�Ӻ���Ԫ��
	void Copy(const GenList<T> &R);      //�����ĸ���
	int Length();                        //��������ĳ���
	int depth();                         //����һ���ǵݹ���������
	void delvalue(T x);                     //���ݸ���ֵ�ڹ������ɾ����Ӧ�����㷨
	template<class T>
	friend istream& operator >> (istream& in,GenList<T> &L);//��Ԫ��������������
private:
	GenListNode<T> *first;               //�����ͷָ��
	GenListNode<T> *Copy(GenListNode<T> *ls);//����һ��lsָʾ���޹���ǵݹ��
	int Length(GenListNode<T> *ls);      //������lsָʾ�Ĺ����ĳ���
	int depth(GenListNode<T> *ls);       //������lsָʾ�ķǵݹ���������
	bool equel(GenListNode<T> *s,GenListNode<T> *t);//�ж���s��tΪ��ͷ���������Ƿ����
	void delvalue(GenListNode<T> *ls,T x);//���ݸ���ֵ�ڹ������ɾ����Ӧ�����㷨
	void Remove(GenListNode<T> *ls);     //�ͷ���lsΪ����ͷ���Ĺ����
	                                     //����������������������ַ�������������һ��������ͷ���Ĺ����ṹ
	void Createlist(istream &in,GenListNode<T> * &ls,SeqList<T> &L1,SeqList<GenListNode<T> *> &L2);
};


template<class T>
GenList<T>::GenList()                     //���캯��
{
	first=new GenListNode<T>;
	assert(first!=NULL);
}


template<class T>
GenList<T>::~GenList()                    //��������
{
	Remove(first);
}


template<class T>
bool GenList<T>::Head(Items<T> &x)           //���ر�ͷԪ��x
{
	//�������ǿգ���ͨ��x�������һ��Ԫ�ص�ֵ��������û�ж���
	if(first->tlink==NULL) return false;    //�ձ�û�з���������
	else                                    //�ǿձ�
	{
		x.utype=first->tlink->utype;
		x.info=first->tlink->info;
		return true;                        //����true,���ر�ͷ��ֵ
	}
}


template<class T>
bool GenList<T>::Tail(GenList<T> &lt)     //���ر�βlt
{
	//�������ǿգ���ͨ��lt���ع�������ͷԪ����������Ԫ����ɵı�������û�ж���
	if(first->tlink==NULL) return false;  //�ձ�
	else                                  //�ǿձ�
	{
		lt.first->utype=0;                //���ø���ͷ���
		lt.first->info=0;
		lt.first->tlink=Copy(first->tlink->tlink);
		return true;
	}
}


template<class T>
GenListNode<T>* GenList<T>::First()       //���ص�һ��Ԫ��
{
	//���ع����ĵ�һ��Ԫ�أ�����գ��򷵻�һ���ض��Ŀ���NULL
	if(first-tlink==NULL) return NULL;   //�ձ�
	else return first->tlink;            //�ǿձ�
}


template<class T>
GenListNode<T>* GenList<T>::nest(GenListNode<T> *elem)//���ر�Ԫ��elem��ֱ�Ӻ���Ԫ��
{
	//���ر�Ԫ��elem��ֱ�Ӻ���Ԫ��
	if(elem->tlink==NULL) return NULL;    //�ձ�
	else return elem->tlink;              //�ǿձ�
}


template<class T>
void GenList<T>::Copy(const GenList<T> &R)//�����ĸ���
{                                         //���к���
	first=Copy(R.first);                  //����˽�к���
}


template<class T>
int GenList<T>::Length()                 //������ĳ���
{
	//���к�������ǰ�����ĳ���
	return Length(first);
}


template<class T>
int GenList<T>::depth()                  //��һ���ǵݹ���������
{
	//���к�������һ���ǵݹ������
	return depth(first);
}



template<class T>
void delvalue(T x)                      //���ݸ���ֵ�ڹ������ɾ����Ӧ�����㷨
{
	//���к��������ݸ���ֵ�ڹ������ɾ����Ӧ�����㷨
	delvalue(first,x);
}



template<class T>
istream& operator >> (istream& in,GenList<T> &L)  //��Ԫ��������������
{
	int n;
	cout<<"���������ַ������ַ�����"<<endl;
	in>>n;
	//T *Ls1=new T[n];
	SeqList<T> Ls1(n);
	//GenListNode<T> *Ls2=new GenListNode<T>[n];    //�����������鲢��ʼ��
	SeqList<GenListNode<T> *> Ls2(n);
	cout<<"�����������ַ���(�ַ����ַ�֮���ÿո����)��";
	L.Createlist(in,L.first,Ls1,Ls2);               //���������洢�ṹ
	GenListNode<T> *p=L.first;
	L.first=L.first->info.hlink;
	//delete []Ls1;
	//delete []Ls2;
	delete p;
	return in;
}



template<class T>
GenListNode<T>* GenList<T>::Copy(GenListNode<T> *ls)   //����һ��lsָʾ���޹���ǵݹ��
{
	//˽�к���������һ��lsָʾ���޹����ӱ�ķǵݹ��
	GenListNode<T> *q=NULL;
	if(ls!=NULL)  
	{
		q=new GenListNode<T>;                                   //����ǰ�Ľ��q
		q->utype=ls->utype;                                     //���ƽ������
		switch(ls->utype)                                       //����utype��ֵ������Ϣ
		{
		case 0:q->info.ref=ls->info.ref;break;                  //����ͷ���
		case 1:q->info.value=ls->info.value;break;              //ԭ�ӽ��
		case 2:q->info.hlink=Copy(ls->info.hlink);break;        //����
		}
		q->tlink=Copy(ls->tlink);                               //����ͬһ����һ���Ϊͷ�ı�
	}
	return q;
}



template<class T>
int GenList<T>::Length(GenListNode<T> *ls) //������lsָʾ�Ĺ����ĳ���
{
	//˽�к�����������lsΪͷָ��Ĺ����ĳ���
	if(ls!=NULL) return 1+Length(ls->tlink);
	else return 0;
}



template<class T>
int GenList<T>::depth(GenListNode<T> *ls)  //������lsָʾ�ķǵݹ���������
{
	//˽�к�����������lsָʾ�ķǵݹ���������
	if(ls->tlink==NULL) return 1;         //ls->tlink==NULL ���ձ����Ϊ1
	GenListNode<T> *temp=ls->tlink;
	int m=0,n;
	while(temp!=NULL)                     //temp�ڹ�������ɨ
	{ 
		if(temp->utype==2)                //ɨ�赽�Ľ��utypeΪ����ʱ 
		{
			n=depth(temp->info.hlink);    //�����Ըý��Ϊͷ�Ĺ�������
			if(m<n) m=n;                  //ȡ������
		}
		temp=temp->tlink;
	}
	return m+1;                           //�������
}



template<class T>
bool GenList<T>::equel(GenListNode<T> *s,GenListNode<T> *t)//�ж���s��tΪ��ͷ���������Ƿ����
{
	//˽�к�������s��t�����ǵݹ�����ı�ͷָ�룬��������ȣ���������true�����򷵻�false
	int x;
	if(s->tlink==NULL && t->tlink==NULL) return true;                      //��s���t���ǿձ�
	if(s->tlink!=NULL && t->tlink!=NULL && s->tlink-utype==t->tlink->utype)//�����ǿ��ҽ��������ͬ
	{
		if(s->tlink->utype==1)                                             //ԭ�ӽ�㣬�Ƚ϶�Ӧ����
		{
			x=(s->tlink->value==t->tlink->value)?1:0;
		}
		else if(s->tlink->utype==2)                                        //�ӱ��㣬�ݹ�Ƚ����ӱ�
		{
			x=depth(s->tlink->info.hlink,t->tlink->info.hlink);
		}
		if(x==1) return equal(s->tlink,t->tlink)                           //��ȣ��ݹ�Ƚ�ͬһ�����һ����㣻���ȣ����ٵݹ�Ƚ�
	}
	return false;                                                          //���ȣ�����false
}




template<class T>
void delvalue(GenListNode<T> *ls,T x)           //���ݸ���ֵ�ڹ������ɾ����Ӧ�����㷨
{
	//˽�к��������ݸ���ֵ�ڹ������ɾ����Ӧ�����㷨
	if(ls->tlink!=NULL)                                                //�ǿձ�
	{
		GenListNode<T> *q=ls->tlink;                                   //�ҵ�����ͷ����ĵ�һ�����
		while(q!=NULL && q->utype==1 && q->info.value==x)              //������x��㣬ɾ������qָ��ͬ����һ�����
		{
			ls->tlink=q->tlink;
			delete q;
			q=ls->tlink
		}
		if(q!=NULL)
		{
			if(q->utype==2)                                            //���ӱ���ɾ��
			{
				delvalue(q->info.hlink,x);
			}
			delvalue(q,x);                                             //����qΪͷ���Ĺ�����еݹ�ɾ��
		}
	}
}


template<class T>
void GenList<T>::Remove(GenListNode<T> *ls)     //�ͷ���lsΪ����ͷ���Ĺ����
{
	//˽�к������ͷ���lsΪ����ͷ���Ĺ����
	ls->info.ref--;                                                  //����ͷ�������ü�����1
	if(ls->info.ref<=0)                                              //�������0
	{
		GenListNode<T> *q;                                           
		while(ls->tlink!=NULL)                                      //��ɨ����
		{
			q=ls->tlink;                                            //�ҵ���һ�����
			if(q->utype==2)                                         //�ݹ�ɾ���ӱ�
			{
				Remove(q->info.hlink);
				if(q->info.hlink->info.ref<=0)
				{
					delete q->info.hlink;                           //ɾ���ӱ���ͷ���
				}
			}
			ls->tlink=q->tlink;
			delete q;
		}
	}
}



template<class T>                        //����������������������ַ�������������һ��������ͷ���Ĺ����ṹ
void GenList<T>::Createlist(istream &in,GenListNode<T> * &ls,SeqList<T> &L1,SeqList<GenListNode<T> *> &L2)
{
	//�ӹ������ַ�������s����������һ��������ͷ���Ĺ����ṹ��Ҫ��TΪchar����
	//�ڱ�L1�����д��ĸ�ı������ڱ�L2�洢������Ӧ�ӱ���ĵ�ַ
	T chr;
	in>>chr;                                       //����һ���ַ����˴�ֻ���ܶ���ո�#���������ź�Ӣ����ĸ
	if(isalpha(chr) && isupper(chr) || chr=='(')   //��д��ĸ�򡮣���
	{
		ls=new GenListNode<T>;                     //�����ӱ���
		ls->utype=2;                       
		if(isalpha(chr) && isupper(chr))
		{
			int n=L1.Length();
			int m=L1.Search(chr);
			if(m!=0)                               //�ñ��Ѿ�����
			{
				GenListNode<T> *p=L2.Locate(m);    //���ӱ��ַ
				p->info.ref++;                     //���ü�����һ
			}
			else
			{                                      //�����������ַ
				L1.Insert(n,chr);
				L2.Insert(m,ls);
			}
			in>>chr;
			if(chr!='(') exit(1);                  //��������ظ�'('
		}
		ls->info.hlink=new GenListNode<T>;         //������ͷ���
		ls->info.hlink->utype=0;
		ls->info.hlink->info.ref=1;
		Createlist(in,ls->info.hlink->tlink,L1,L2); //�ݹ齨�ӱ�
		Createlist(in,ls,L1,L2);              //??  �ݹ齨������
	}
	else if(isalpha(chr) && islower(chr))           //��Ԫ�ؽ��
	{
		ls=new GenListNode<T>;
		ls->utype=1;
		ls->info.value=chr;
		Createlist(in,ls,L1,L2);
	}
	else if(chr==',')                               //���������
	{
		Createlist(in,ls->tlink,L1,L2);
	}
	else if(chr==')')  ls->tlink=NULL;              //�����ţ�����β
	else if(chr=='#')  ls=NULL;                     //�ձ�����β
}



