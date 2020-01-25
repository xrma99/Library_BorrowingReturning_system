#ifndef GUARD_book_h
#define GUARD_book_h

#include<ios>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<fstream>

struct borrower
{
	std::string ID;
	int date;//no bigger than 30000000
	borrower* next;
	borrower()
	{
		ID=date=0;
		next=NULL;
	}
};
struct book
{
	std::string num;
	std::string name;
	std::string author;
	int total;
	int store;
	borrower* people;
	book* next;

	book()
	{
		total=store=0;
		people=NULL;
		next=NULL;
	}
};
struct library
{
	char type;//�鼮��ŵ�һ����ĸ,�����鼮����
	book *books;//����ȫ���鼮
	library *next;
};
struct prisoner
{
	std::string ID;
	std::string bookname;
	int duedate;
	int redate;
	prisoner* next;
};
void Register(book*,borrower*);//����
void printborrower(borrower* b)
{
	if(b==NULL) return;
	std::cout<<"���������ѧ�ż���黹���ڣ�"<<std::endl;
	borrower* p=b;
	for(;p;p=p->next)
		std::cout<<p->ID<<' '<<p->date<<' '<<std::endl;
}
void printbook(book* p)
{
	if(p==NULL) return;
	std::cout<<p->num<<' '<<p->name<<' '<<p->author<<' ';
	std::cout<<p->total<<' '<<p->store<<' '<<std::endl;
	printborrower(p->people);
	std::cout<<std::endl;
}
void printbooks(book* l)
{
	book* p=l;
	for(;p!=NULL;p=p->next)
		printbook(p);
}
void printlibrary(library *l)
{
	std::cout<<"���\t����\t����\t�ݲ�\t�ִ�"<<std::endl;
	library *p=l;
	for(;p;p=p->next)
		printbooks(p->books);
}

book* searchnum(library* l,char* s)
{
	if(l==NULL)
	{
		std::cout<<"ͼ����޹ݲ�";
		return NULL;
	}
	library *p=l;
	book *a,*b;
	for(;p;p=p->next)
	{
		if(p->type==s[0])
		{
			for(a=b=p->books;b;a=b,b=b->next)
			{
				if(b->num==s) return b;//���ڸ���
			}
			return a;//�����ڸ��鵫�Ǵ��ڸ����������࣬���ظ������һ����
		}
	}
	return NULL;
}
book* searchname(library* l,std::string s)
{
	if(l==NULL)
	{
		std::cout<<"ͼ����޹ݲ�";
		return NULL;
	}
	library *p=l;
	book* q;
	for(;p;p=p->next)
	{
		for(q=p->books;q;q=q->next)
		{
			if(q->name==s) return q;
		}
	}
	return NULL;
}

library* buybook(library* l)
{
	std::cout<<"������������ţ����������ߣ�������"<<std::endl;
	book *n=new book;
	std::cin>>n->num;
	std::cin>>n->name>>n->author;
	std::cin>>n->store;

	n->total=n->store;
	n->people=NULL;
	n->next=NULL;

	if(l==NULL)//ͼ�����ԭ������
	{
		l=new library;
		l->type=n->num[0];
		l->books=n;
		return l;
	}
	book *p=NULL;
	p=searchnum(l,&n->num[0]);
	if(p!=NULL&&p->num==n->num)//�Ѿ������Ȿ��
	{
		p->total +=n->total;
		p->store +=n->total;
		delete n;
		std::cout<<"�ɱ����ɹ�"<<std::endl;
		return l;
	}
	//�������Ȿ��
	if(p!=NULL)//���ڸ�����������
	{
		p->next=n;
		std::cout<<"�ɱ����ɹ�"<<std::endl;
		return l;
	}
	library *q=l;
	while(q->next)  q=q->next;
	q->next=new library;
	q->next->type=n->num[0];
	q->next->books=n;
	q->next->next=NULL;
	std::cout<<"�ɱ����ɹ�"<<std::endl;
	return l;
}
bool isempty(book* b)//�жϸ������޽��
{
	if(b->store==0) return true;
	return false;
}
int gettime()
{
	time_t now=time(0);
	tm *ltem=localtime(&now);
	return (ltem->tm_year+1900)*10000+(1+ltem->tm_mon)*100+ltem->tm_mday;
}
bool islate(borrower* b)
{
	int t=gettime();
	if(t> b->date) return true;
	return false;
}

int calculatereturndate(int y,int m,int d)
{
	int res;
	switch(m)
	{
	case 1:case 3:case 8:case 10:
		if(d==31) d=30;
		break;
	case 11:
		if(d==29||d==30) d=28;//�������ֱ����黹����Ϊ2��28��
		break;
	default: break;
	}
	y=y+(m+3)/12;
	m=(m+3)%12;
	res=y*10000+m*100+d;
	return res;
}
library* borrowbook(library* l)
{
	std::cout<<"������������ĵ��鼮��"<<std::endl;
	std::cout<<"(1.���\t2.����)"<<std::endl;
	int flag=0;
	std::cin>>flag;
	std::string b;
	book* p=NULL;//�ҵ�����ĵ��Ǳ���
	switch(flag)
	{
	case 1: 
		std::cout<<"���������";
		std::cin>>b;
		p=searchnum(l,&b[0]);
		if(p!=NULL && p->num!=b)
		{
			std::cout<<"���鲻���ڣ�";
			return l;
		}
		break;
	case 2: std::cout<<"����������";std::cin>>b;p=searchname(l,b);break;
	default: std::cout<<"wrong instruction!";return l;
	}
	if(p==NULL)
	{
		std::cout<<"���鲻���ڣ�";
		return l;
	}
	if(isempty(p))
	{
		std::cout<<"�����Ѿ����˽��꣡";
		return l;
	}
	std::cout<<"����ɽ��ģ�"<<std::endl;
	p->store--;
	std::cout<<"�����������ѧ�ţ�";
	std::string stu_ID;
	std::cin>>stu_ID;
	borrower *q=new borrower,*temp;
	q->ID=stu_ID;
	time_t now=time(0);
	tm *ltem=localtime(&now);
	q->date=calculatereturndate(ltem->tm_year+1900,1+ltem->tm_mon,ltem->tm_mday);//�ɽ���������
	q->next=NULL;
	if(p->people==NULL) p->people=temp=q;//��ӵ���������Ϣ��
	else
	{
		for(temp=p->people;temp->next;temp=temp->next);
		temp->next=q;
	}
	std::cout<<"�ɹ����ģ�"<<std::endl;
	return l;
}
library* returnbook(library* l)
{
	std::string n;
	std::cout<<"����������黹���鼮���ƣ�";
	std::cin>>n;
	book* p=searchname(l,n);
	if(p==NULL)
	{
		std::cout<<"ͼ����޴���"<<std::endl;
		return l;
	}
	std::cout<<"�����������ѧ�ţ�";
	std::string stu_ID;
	std::cin>>stu_ID;
	borrower* b=p->people;
	if(b==NULL)
	{
		std::cout<<"�����޽�����"<<std::endl;
		return l;
	}
	if(b->ID==stu_ID)//��һ��������
	{
		p->people=b->next;
		p->store++;
		if(islate(b)==0) std::cout<<stu_ID<<"�û���"<<n<<"�ɹ�"<<std::endl;//��ʱ�黹
		else//���ڻ���
		{
			std::cout<<stu_ID<<"�û���"<<n<<"�ɹ������ڣ�������̨���ɷ���"<<std::endl;
			Register(p,b);
		}
		delete b;
		return l;
	}
	borrower* c=b->next;
	for(;c;b=c,c=c->next)
	{
		if(c->ID==stu_ID)
		{
			b->next=c->next;
			p->store++;
			if(islate(c)==0) std::cout<<stu_ID<<"�û���"<<n<<"�ɹ�"<<std::endl;//��ʱ�黹
			else//���ڻ���
			{
				std::cout<<stu_ID<<"�û���"<<n<<"�ɹ������ڣ�������̨���ɷ���"<<std::endl;
				Register(p,b);
			}
			delete c;
			return l;
		}
	}
	std::cout<<n<<"��"<<stu_ID<<"������"<<std::endl;
	return l;
}

void printlibraryback(library* l)
{
	std::ofstream out("libraryz.txt");
	library *p=l,*q;
	book *r;
	borrower* b;
	for(;p!=NULL;p=p->next)
	{
		for(r=p->books;r;r=r->next)
		{
			out<<r->num<<' '<<r->name<<' '<<r->author<<' ';
			out<<r->total<<' '<<r->store<<' '<<std::endl;
			if(r->total!=r->store)//���ڽ�����
			for(b=r->people;b;b=b->next) out<<b->ID<<' '<<b->date<<std::endl;
		}
	}
}

void Register(book* b,borrower* p)
{
	std::ifstream x("prisoner.txt");
	std::string temp;
	prisoner *r=NULL,*s=NULL,*help;
	int i=0,j;
	while(x>>temp)//��ȡ�ļ�
	{
		switch(i)
		{
		case 0:
			help=new prisoner;
			help->ID=temp;
			i++;
			break;
		case 1:
			help->bookname=temp;
			i++;
			break;
		case 2:
			for(j=0;j<strlen(&temp[0]);j++)
				help->duedate=help->duedate*10 + temp[j]-'0';
			i++;
			break;
		case 3:
			for(j=0;j<strlen(&temp[0]);j++)
				help->redate=help->redate*10 + temp[j]-'0';
			help->next=NULL;
			if(r==NULL) r=s=help;
			else
			{
				s->next=help;
				s=s->next;
			}
			i=0;
			break;
		
		default:
			std::cout<<"error!";
			break;
		}
	}
	help=new prisoner;
	help->ID=p->ID;
	help->bookname=b->name;
	help->duedate=p->date;
	help->redate=gettime();
	help->next=NULL;
	if(r==NULL) r=help;
	else s->next=help;
	std::ofstream y("prisonery.txt");
	for(s=r;s;s=s->next)
	{
		y<<s->ID<<' '<<s->bookname<<' '<<s->duedate<<' '<<s->redate<<std::endl;
	}
}
void ripeoff()
{
	std::cout<<"����������ѧ�ţ�";
	std::string t;
	std::cin>>t;
	std::ifstream x("prisonery.txt");
	std::string temp;
	prisoner *r=NULL,*s=NULL,*help;
	int i=0,j;
	while(x>>temp)//��ȡ�ļ�
	{
		switch(i)
		{
		case 0:
			help=new prisoner;
			help->ID=temp;
			i++;
			break;
		case 1:
			help->bookname=temp;
			i++;
			break;
		case 2:
			for(j=0;j<strlen(&temp[0]);j++)
				help->duedate=help->duedate*10 + temp[j]-'0';
			i++;
			break;
		case 3:
			for(j=0;j<strlen(&temp[0]);j++)
				help->redate=help->redate*10 + temp[j]-'0';
			help->next=NULL;
			if(r==NULL) r=s=help;
			else
			{
				s->next=help;
				s=s->next;
			}
			i=0;
			break;
		default:
			std::cout<<"error!";
			break;
		}
	}
	if(r==NULL)
	{
		std::cout<<"������������";
		return;
	}
	int g=0;
	if(r->ID==t)
	{
		s=r;
		r=r->next;
		g=1;
		delete s;
	}
	for(s=help=r;s;help=s,s=s->next)
		if(s->ID==t)
		{
			help->next=s->next;
			delete s;
			g=1;
		}
	if(g==0)
	{
		std::cout<<"�������޴��û�";
	}
	else std::cout<<"�ɹ����ɷ���";
	std::ofstream y("prisonerz.txt");
	for(s=r;s;s=s->next)
	{
		y<<s->ID<<' '<<s->bookname<<' '<<s->duedate<<' '<<s->redate<<std::endl;
	}
}
#endif