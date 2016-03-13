#pragma once

//˳����ඨ��

//#include"linearList.h"
#include<iostream>
#include<cstdlib>

using namespace std;

const int defaultSize=100;

template<class T>
class SeqList
{
protected:
	T *data;                                          //�������
	int maxSize;                                      //�������ɱ��������
	int last;                                         //��ǰ�Ѵ�ű�������λ�ã���0��ʼ��
	void reSize(int newSize);                         //�ı�data����ռ��С
public:
	SeqList(int sz=defaultSize);                      //���캯��
	SeqList(SeqList<T> &L);                           //���ƹ��캯��
	~SeqList(){delete []data;}                        //��������
	int Size()const{return maxSize;}                  //������������ɱ������
	int Length()const {return last+1;}                //�������
	int Search(T& x)const;                            //����x�ڱ���λ�ã��������ر������
	T Locate(int i)const;                           //��λ��i������������ر������
	bool getData(int i,T& x)const                     //ȡ��i�������ֵ
	{
		if(i>0 && i<=last+1)
		{
			x=data[i-1];
			return true;
		}
		else return false;
	}
	bool setData(int i,T& x)                          //�޸ĵ�i�������ֵ
	{
		if(i>0 && i<last+1)
		{
			data[i-1]=x;
			return true;
		}
		else return false;
	}
	bool Insert(int i,T& x);                          //����x�ڵ�i������֮��
	bool Remove(int i,T& x);                          //ɾ����i�����ͨ��x���ر����ֵ
	bool IsEmpty()const                               //�жϱ�շ񣬿��򷵻�true,���򷵻�false
	{
		return (last==-1)?true:false;
	}
	bool IsFull()const                                //�жϱ��������򷵻�true,���򷵻�false
	{
		return (last==maxSize-1)?true:false;
	}
	void input();                                     //����
	void output();                                    //���
	SeqList<T> operator = (SeqList<T> &L);           //�����帳ֵ

};



template<class T>
SeqList<T>::SeqList(int sz)
{
	//���캯����ͨ��ָ������sz��������ĳ���
	if(sz>0)
	{
		maxSize=sz;
		last=-1;                                      //�ñ��ʵ�ʳ���Ϊ��
		data=new T[maxSize];                          //����˳���洢����
		if(data==NULL)                                //��̬�������
		{
			cerr<<"�洢�������"<<endl;
				exit(1);
		}
	}
}



template<class T>
SeqList<T>::SeqList(SeqList<T> &L)
{
	//���ƹ��캯�����ò������и���������˳����ʼ���½�˳���
	maxSize=L.Size();
	last=L.Length()-1;
	data=new T[maxSize];                              //����˳���洢����
	if(data==NULL)                                    //��̬�������
	{
		cerr<<"�洢�������"<<endl;
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
	//˽�к���������˳���Ĵ洢����ռ��С���������Ԫ�ظ���ΪnewSize
	if(newSize<=0)                                    //��������С�ĺ�����
	{
		cerr<<"��Ч�������С��"<<endl;
		exit(1);
	}
	else if(newSize<=maxSize)
	{
		cerr<<"�����С��ԭ������С"<<endl;
		exit(1);
	}
	else                                              //�޸������С
	{
		T *newarray=new T[newSize];                   //����������
		if(newarray==NULL)                            //�������
		{
			cerr<<"�洢�������"<<endl;
		}
		int n=last+1;
		T *srcptr=data;                               //ԭ������׵�ַ
		T *destptr=newarray;                          //Ŀ��������׵�ַ
		while(n--)
		{
			*destptr++=*srcptr++;                     //���Ƹ������ֵ
		}
		delete []data;                                //ɾ��ԭ������
		data=newarray;                                //����������
		maxSize=newSize;
	}

}



template<class T>
int SeqList<T>::Search(T& x)const
{
	//�����������ڱ���˳�����������ֵxƥ��ı���ҵ��������ظñ����ǵڼ���Ԫ��,����������0����ʾ����ʧ��
	for(int i=0;i<=last;i++)                          //˳������
	{
		if(data[i]==x) return i+1;
	}
	return 0;                                         //����ʧ��
}



template<class T>
T SeqList<T>::Locate(int i)const
{
	//��λ�������������ص�i��1<=i<=last+1)�������ֵ������������0����ʾ��λʧ��
	if(i>=1 && i<=last+1) return data[i-1];
	else return 0;
}



template<class T>
bool SeqList<T>::Insert(int i,T& x)
{
	//����Ԫ��x���뵽���е�i��0<=i<=last+1)������֮�󡣺������ز��������������ɹ����򷵻�true��
	//���򷵻�false��i=0������ģ�ʵ�����ǲ��뵽��1��Ԫ��λ��
	if(last==maxSize-1)                               //���������ܲ��룬��������
	{
		reSize(maxSize+defaultSize);
	}
	if(i<0 || i>last+1) return false;                 //����i���������ܲ���
	for(int j=last;j>=i;j--)                          //���κ��ƣ��ճ���i��λ��
	{
		data[j+1]=data[j];
	}
	data[i]=x;                                        //����
	last++;                                           //���λ�ü�1
	return true;                                      //����ɹ�
}



template<class T>
bool SeqList<T>::Remove(int i,T& x)
{
	//�ӱ���ɾ����i��1<=i<=last+1)�����ͨ�������Ͳ���x����ɾ����Ԫ��ֵ����������ɾ�����
	//��ɾ���ɹ��򷵻�true,���򷵻�false.
	if(last==-1)                                      //��գ�����ɾ��
	{
		cerr<<"˳���Ϊ�ձ�����ִ��ɾ��������"<<endl;
		return false;
	}
	if(i<1 || i>last+1)                               //����i����������ɾ��
	{
		cerr<<"����i����������ִ��ɾ��������"<<endl;
		return false;
	}
	x=data[i-1];                                      //�汻ɾԪ�ص�ֵ
	for(int j=i;j<last+1;j++)                         //����ǰ�ƣ����
	{
		data[j-1]=data[j];
	}
	last--;                                           //���λ�ü�1
	return true;
}



template<class T>
void SeqList<T>::input()
{
	//�ӱ�׼���루���̣�����������ݣ�����˳���
	cout<<"��ʼ����˳������������Ԫ�ظ�����";
	int n;
	while(1)
	{
		cin>>n;                                        //�����Ԫ�صĸ���
		if(n>0 && n<=maxSize) break;
		cout<<"��Ԫ�ظ����������󣬷�ΧӦ��(1,"<<maxSize+1<<")֮��"<<endl;
		cout<<"���������룺";
	}
	for(int i=0;i<n;i++)                              //��������Ԫ��
	{
		cout<<"�������"<<i+1<<"����Ԫ�أ�";
		cin>>data[i];
	}
	last=n-1;                                         //��Ԫ�ص����λ��
}



template<class T>
void SeqList<T>::output()
{
	//��˳���ȫ���������Ļ�ϡ�
	cout<<"˳���ǰԪ�صĸ���Ϊ��"<<last+1<<endl;
	for(int i=0;i<=last;i++)
	{
		cout<<"��"<<i+1<<"��Ԫ��Ϊ��"<<data[i]<<endl;
	}
	cout<<"Ԫ�������ɣ�"<<endl;
}



template<class T>
SeqList<T> SeqList<T>::operator = (SeqList<T> &L)
{
	//���غ�����˳������帳ֵ��
	maxSize=L.Size();
	last=L.Length()-1;
	data=new T[maxSize];                              //����˳���洢����
	if(data==NULL)                                    //��̬����ʧ��
	{
		cerr<<"�洢�������"<<endl;
		exit(1);
	}
	T value;
	for(int i=1;i<=last+1;i++)
	{
		L.getData(i,value);
		data[i-1]=value;
	}
}