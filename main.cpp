#include<ios>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include"book.h"

using namespace std;

library* addbook(library* l,book* b)
{
	library *p,*q;
	
	if(l==NULL)
	{
		l=new library;
		l->type=b->num[0];//��������
		l->books=b;
		l->next=NULL;
		return l;
	}
	book *c=searchnum(l,&b->num[0]);
	if(c==NULL)//�����ڸ���
	{
		for(p=l;p->next;p=p->next);
		q=new library;
		q->type=b->num[0];
		q->books=b;
		q->next=NULL;
		p->next=q;
	}
	else
	{
		c->next=b;
	}
	return l;
}
int main()
{
	library* l=NULL;
	book *help=NULL,*p;
	borrower *b,*c;
	int tag=1;
	int op;
	ifstream in("libraryy.txt");
	string temp;
	int i=0,j,k=0,r=0,s;
	while(in>>temp)//��ȡ�ļ�
	{
		switch(i)
		{
		case 0:
			help=new book;
			help->num=temp;
			i++;
			break;
		case 1:
			help->name=temp;
			i++;
			break;
		case 2:
			help->author=temp;
			i++;
			break;
		case 3:
			for(j=0;j<strlen(&temp[0]);j++)
				help->total=help->total*10 + temp[j]-'0';
			i++;
			break;
		case 4:
			for(j=0;j<strlen(&temp[0]);j++)
				help->store=help->store*10 + temp[j]-'0';
			if(help->total==help->store)
			{
				help->next=NULL;
				i=0;//�޽�����
				l=addbook(l,help);
			}
			else
			{
				j=help->total - help->store;
				i=5;
			}
			break;
		case 5:
			if(r==0)//���������ID
			{
				b=new borrower;
				b->ID=temp;
				r=1;
			}
			else
			{
				for(s=0;s<strlen(&temp[0]);s++)
					b->date= b->date * 10 + temp[s]-'0';
				r=0;
				if(help->people==NULL)
				{
					help->people=c=b;
				}
				else
				{
					c->next=b;
					c=c->next;
				}
				k++;
				if(k==j)
				{
					i=0;//���н�������Ϣ¼�����
					b->next=NULL;
					help->next=NULL;
					l=addbook(l,help);
				}
			}
			break;
		default:
			cout<<"error!";
			break;
		}
	}
	while(tag)
	{
		cout<<"1.�ɱ����\n2.����\n3.����\n4.��ӡͼ��ݹݲ�\n5.������\n";
		cin>>op;
		switch(op)
		{
		case 1:
			l=buybook(l);
			break;
		case 2:
			l=borrowbook(l);
			break;
		case 3:
			l=returnbook(l);
			break;
		case 4:
			printlibrary(l);
			break;
		case 5:
			ripeoff();
			break;
		default:
			cout<<"wrong instruction!"<<endl;
			break;
		}
		cout<<"������������������𣿣��������������0��:";
		cin>>tag;
	}
	printlibraryback(l);
	system("pause");
	return 0;
}