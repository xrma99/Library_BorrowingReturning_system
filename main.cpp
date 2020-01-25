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
		l->type=b->num[0];//保存类型
		l->books=b;
		l->next=NULL;
		return l;
	}
	book *c=searchnum(l,&b->num[0]);
	if(c==NULL)//不存在该类
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
	while(in>>temp)//读取文件
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
				i=0;//无借书人
				l=addbook(l,help);
			}
			else
			{
				j=help->total - help->store;
				i=5;
			}
			break;
		case 5:
			if(r==0)//输入借书人ID
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
					i=0;//所有借书人信息录用完毕
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
		cout<<"1.采编入库\n2.借书\n3.还书\n4.打印图书馆馆藏\n5.交罚款\n";
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
		cout<<"请问您还想继续操作吗？（如果不想请输入0）:";
		cin>>tag;
	}
	printlibraryback(l);
	system("pause");
	return 0;
}