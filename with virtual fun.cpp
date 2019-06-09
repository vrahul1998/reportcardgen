#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;
class admin;
class display_base
{
	public:
		virtual void display(char* name,char* n)
		{
			cout<<"NAME:"<<name<<endl;
			cout<<"SUBJECT:"<<n<<endl;
		}
};
class display_derived:public display_base
{
	public:
		void display(char* name,char* usn)
		{
			cout<<"NAME:"<<name<<endl;
			cout<<"USN:"<<usn<<endl;
			cout<<endl;
		}
};
class student_data
{
	protected:
		char name[10];
		char USN[15];
		int sub[3][3];
		int ex[3];
		int total[3];
		double gpa;
		int complete[3];
		friend void student_entry(admin);
		
};
class teacher_data
{
	protected:
		char username[10];
		char passwd[10];
		int s;
		public:
		friend	void teacher_entry(admin);
		
};
class admin:protected student_data,protected teacher_data
{
	private:
		admin *teacher_head=NULL,*student_head=NULL;
		admin *student_next=NULL,*teacher_next=NULL;
	public:
		void *operator new(size_t s)
			{
				void *p;
				p=malloc(s);
				return p;
			}
		admin()
			{
				int i,j;
				for(i=0;i<3;i++)
					{
						for(j=0;j<3;j++)
						{
							sub[i][j]=-1;
							ex[i]=-1;
							total[i]=-1;
							complete[i]=0;
							gpa=0;
						}
					}
			}
		void teacher_insert(admin);
		void student_insert(admin);//object to insert int link list
		friend void student_entry(admin);
		void display();
		int display_student(int);
		void create_student(admin);
		friend	void admin_entry(admin);
		friend  void list(admin,int);
		friend  void teacher_entry(admin);
		void marks_enter(int);
		void teacher_begin();
		int get_subject(char [],char []);
		void teacher_ending();
		void student_ending();
		void student_begin();
		void create_teacher(admin);
		int edit_marks(char[],int);
		int operator ==(char []);
};
void list(admin s,int n)
{	display_base *d,d1;
	display_derived d2;
	admin *start;
	char s1[10]="MATHS";
	char s2[10]="OOPS";
	char s3[15]="MICROPROCESSOR";
	if(n==3)
	{
		d=&d1;
		start=s.teacher_head;
		cout<<"-----------------------------------\n";
		cout<<"\t\tTEACHER LIST\t\t\n";
		cout<<"------------------------------------\n";
		while(start!=NULL)
		{	if(start->s==0)
			d->display(start->username,s1);
			else if(start->s==1)
			d->display(start->username,s2);
			else if(start->s==2)
			d->display(start->username,s3);
			start=start->teacher_next;
		}
	}
	else if(n==4)
	{
		d=&d2;
		start=s.student_head;
		cout<<"-----------------------------------\n";
		cout<<"\t\tSTUDENT LIST\t\t\n";
		cout<<"------------------------------------\n";
		while(start!=NULL)
		{
			d->display(start->name,start->USN);
			start=start->student_next;
		}
	}
}
void student_entry(admin t)
	{	system("cls");
		cout<<"---------------------------------\n";
			cout<<"\t\tSTUDENT\t\t\n";
			cout<<"---------------------------------\n";
		int check=0;
		char usn[10];
		cout<<"ENTER USN:";
		cin>>usn;
				if(t==usn)
					{	check=1;
						cout<<"USN FOUND\n";
						admin *start;
						start=t.student_head;
						while(start!=NULL)
						{if(strcmp(start->USN,usn)==0){
						if(start->complete[0]==1&&start->complete[1]==1&&start->complete[2]==1)
							{
								cout<<"-------------------------------------------\n";
								cout<<"NEW HORIZON COLLEGE OF ENGINEERING\n";
								cout<<"-------------------------------------------\n";
								cout<<"NAME:"<<start->name<<endl;
								cout<<"USN:"<<start->USN<<endl;
								cout<<"---------------------------\n";
								cout<<"SUBJECT     \tCIE\tEXTERNAL\tTOTAL\n";
								cout<<"MATHEMATICS \t"<<(start->sub[0][0]+start->sub[0][1]+start->sub[0][2])/3<<"\t"<<start->ex[0]<<"\t"<<start->total[0]<<"\n";
								cout<<"OOPS        \t"<<(start->sub[1][0]+start->sub[1][1]+start->sub[1][2])/3<<"\t"<<start->ex[1]<<"\t"<<start->total[1]<<"\n";
								cout<<"MICROPROSSOR\t"<<(start->sub[2][0]+start->sub[2][1]+start->sub[2][2])/3<<"\t"<<start->ex[2]<<"\t"<<start->total[2]<<"\n";
								cout<<"\nGPA:"<<start->gpa<<endl;
							}
						else
							cout<<"RESULT NOT YET CALCULATED\n";
						}
						start=start->student_next;
			}}
		if(check==0)
			{
			cout<<"USN NOT FOUND\n";
			}
	}
int admin::display_student(int a)
	{
		int flag=0;
		admin *start=student_head;
		cout<<"STUDENT MARKS TO BE ENTERED\nNAME:USN\n";
		
		while(start!=NULL)
			{   
				if(start->complete[a]==0)
					{
						flag=1;
						cout<<start->name<<":";
						cout<<start->USN<<endl<<endl;
					}
				start=start->student_next;
			}
		if(flag==0)
			return 0;
		else
			return 1;
	}
void admin::marks_enter(int a)
	{	system("cls");
		cout<<"---------------------------------\n";
			cout<<"\t\tTEACHER\t\t\n";
			cout<<"---------------------------------\n";
		int check=0,flag;
		char temp[10];
		check=0;
		flag=display_student(a);
		if(flag==1)
			{
				cout<<"ENTER USN\n";
				cin>>temp;
				check=edit_marks(temp,a);
				if(check==0)
					{
						cout<<"INVALID USN\n";
					}
			}
		else
			cout<<"all student marks entered\n";
	}
int admin::edit_marks(char usn[10],int s)
	{
				
		int i=1,j,k,c,number;
		admin *start;
		start=student_head;
		while(start!=NULL)
			{
				if(strcmp(start->USN,usn)==0)
					{	
						k1:system("cls");
						cout<<"SUBJECT:";
						if(s==0)
						cout<<"MATHS\n";
						else if(s==1)
						cout<<"OOPS\n";
						else 
						cout<<"MICROPROSSOR\n";	
						cout<<"STUDENT NAME:"<<start->name<<endl;
						cout<<"MARKS IN SUBJECTS\nCIE1:";
						if(start->sub[s][0]==-1)
						cout<<"N/A\n";
						else
						cout<<start->sub[s][0]<<endl;
						cout<<"CIE2:";
						if(start->sub[s][1]==-1)
						cout<<"N/A\n";
						else
						cout<<start->sub[s][1]<<endl;
						cout<<"CIE3:";
						if(start->sub[s][2]==-1)
						cout<<"N/A\n";
						else
						cout<<start->sub[s][2]<<endl;
						cout<<"EXTERNAL:";
						if(start->ex[s]==-1)
						cout<<"N/A\n";
						else
						cout<<start->ex[s]<<endl;
						if(start->gpa!=0)
							{
								cout<<"all marks already entered \nenter 0 to exit or 1 to change marks\n";
								cin>>i;
							}
						if(i==1)
							{
								cout<<"enter 1 to 3 for cie or enter 4 to enter external mark";
								cin>>i;
								i--;
								cout<<"enter ";
								if(i==3)
									{	
										z1:cout<<"external marks:";
										
										cin>>number;
										if(number>100)
										{
											cout<<"ENETRED MARKS MORE THAN 100 PLEASE REENTER\n";
											goto z1;
										}
										else
										start->ex[s]=number;
									}
								else if(i<=2&&i>=0)
									{	z2:cout<<"INTERNALS:";
										cin>>number;
										if(number>50)
										{
										cout<<"ENETRED MARKS MORE THAN 50 PLEASE REENTER\n";
										goto z2;
								}
									else
									start->sub[s][i]=number;
								}
									else
									{
										cout<<"INVALID CHOICE PLEASE CHOOSE AGAIN\n";
										system("cls");
										long int p;
										for(p=0;p<10000000;p++);
										goto k1;
									}
								c=0;
								for(k=0;k<3;k++)
									{
										if(start->sub[s][k]==-1)
										c=1;
										if(start->ex[s]==-1)
										c=1;
									}
								if(c==0)
									{
										start->complete[s]=1;
										start->total[s]=((start->sub[s][0]+start->sub[s][1]+start->sub[s][2])/3)+(start->ex[s]/2);
										cout<<"\ntotal in sub"<<start->total[s]<<endl;
									}
								if(start->complete[s]!=1)
									{
										cout<<"enter 1 to enter another cie 0 to exit\n";
										cin>>i;
										if(i==1)
										goto k1;
									}
								else
									{
										cout<<"subject marks are all entered\n";
										c=0;
										for(j=0;j<3;j++)
											{
												if(start->total[j]==-1)
													c=1;
											}
										if(c==0)
											{
												start->gpa=(start->total[0]+start->total[1]+start->total[2])/30;
											}
									}
								
							}
							return 1;
					}
				else
					{
						start=start->student_next;	
					}
			}
		return 0;	
	}
void teacher_entry(admin t)
	{	system("cls");
		int sub;
		cout<<"ENTER USERNAME:\n";
		char n[10],pa[10];
		cin>>n;
		if(t==n)
			{	
				a1:cout<<"ENTER PASSWORD:";
				cin>>pa;
				sub=t.get_subject(n,pa);
				if(sub==-1)
				goto a1;
				t.marks_enter(sub);
			}
	}
int admin::get_subject(char n1[10],char n2[10])
	{
		admin *start=teacher_head;
		while(start!=NULL)
			{
				if(strcmp(start->username,n1)==0&&strcmp(start->passwd,n2)==0)
				return start->s;
				start=start->teacher_next;
			}
		cout<<"PASSWORD INCORRECT\n";
		return -1;
	}
void admin::create_student(admin t)
		{   
		s:	system("cls");
			cout<<"---------------------------------\n";
			cout<<"\t\tADMIN\t\t\n";
			cout<<"---------------------------------\n";
			cout<<"enter student name:";
			cin>>name;
			cout<<"\nenter student usn:";
			cin>>USN;
			if(t==USN)
			{
				cout<<"USN already registered\n";
				long int i;
				for(i=0;i<=100000;i++);
				goto s;
			}
		}
void admin::create_teacher(admin t)
		{   f:system("cls");
			cout<<"---------------------------------\n";
			cout<<"\t\tADMIN\t\t\n";
			cout<<"---------------------------------\n";
			cout<<"enter username:";
			cin>>username;
			if(t==username)
			{
				cout<<"username already in use\n";
				cout<<"try again\n";
				long int i;
				for(i=0;i<=10000000000;i++);
				goto f;
			}
		f1:	cout<<"\nenter password:";
			cin>>passwd;
			char test[10];
			cout<<"\nre enter password:";
			cin>>test;
			if(strcmp(test,passwd)==0)
			{
				cout<<"passowrd set\n";
				cout<<"enter subject\n1.math\n2.object oriented programming\n3.microprocessor";
				cin>>s;
				s=s-1;
			}
			else
			{
				cout<<"passwords dont match\n";
				long int i;
				for(i=0;i<=100000;i++);
				goto f1;
			}
	}
void admin_entry(admin t)
	{	system("cls");
	    char pass[10];
		char adminpass[10]="nhce123";
		int count=3;
		cout<<"---------------------------------\n";
		cout<<"\t\tADMIN\t\t\n";
		cout<<"---------------------------------\n";
		do{
			cout<<"ENTER PASSWORD:";
			cin>>pass;
			if(strcmp(pass,adminpass)==0)
				{
					cout<<"password correct\n";
					cout<<"1.new teacher\n";
					cout<<"2.new student\n";
					cout<<"3.teacher list\n";
					cout<<"4.student list\n";
					int ch;
					admin t1;
					cin>>ch;
					switch(ch)
						{
							case 1:
								t1.create_teacher(t);
								t.teacher_insert(t1);
								break;
							case 2:
								t1.create_student(t);
								t.student_insert(t1);
								break;
								case 3:
									list(t,3);
									break;
									case 4:
										list(t,4);
										break;
							default:
							cout<<"invalid choice\n";
						}
					count=0;
				}
			else
				{
					cout<<"password incorrect\n";
					cout<<"try again\n";
					count--;
				}
			}while(count!=0);
	}
int admin::operator ==(char no[10])
{
	admin *start;
	start=student_head;
	while(start!=NULL)
	{
		if(strcmp(start->USN,no)==0)
		return 1;
		start=start->student_next;
		
	}
	start=teacher_head;
		while(start!=NULL)
	{
		if(strcmp(start->username,no)==0)
		return 1;
		start=start->teacher_next;
		
	}
	return 0;
}
void admin::student_insert(admin t)
{   int i,j;
	admin *temp,*p;
	p=student_head;
	temp=new admin();
	strcpy(temp->name,t.name);
	strcpy(temp->USN,t.USN);
			for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				temp->sub[i][j]=t.sub[i][j];
				temp->ex[i]=t.ex[i];
				temp->total[i]=t.total[i];
				temp->complete[i]=t.complete[i];
			}
		}
		temp->gpa=t.gpa;
	temp->student_next=NULL;
	if(student_head==NULL)
	{
		student_head=temp;
	}
	else
	{
		while(p->student_next!=NULL)
		p=p->student_next;
		p->student_next=temp;
	}
}
void admin::teacher_insert(admin t)
{
	int i,j;
	admin *temp,*p;
	p=teacher_head;
	temp=new admin();
	strcpy(temp->username,t.username);
	strcpy(temp->passwd,t.passwd);
	temp->s=t.s;		
	temp->teacher_next=NULL;
	if(teacher_head==NULL)
	{
		teacher_head=temp;
	}
	else
	{
		while(p->teacher_next!=NULL)
		p=p->teacher_next;
		p->teacher_next=temp;
	}
}
void admin::display()
{
	admin *p;
	p=teacher_head;
	while(p!=NULL)
	{
		cout<<"teacher:-";
		cout<<"name:"<<p->username<<endl;
		cout<<"password:"<<p->passwd<<endl;
		p=p->teacher_next;
	}
	
}
void admin::student_begin()
{
	int count=0;
	ifstream fin;
	fin.open("rv.txt",ios::in);
	admin a;
	while(fin.read((char*)&a,sizeof(a)))
	{	student_insert(a);
	count=1;
	}
	if(count==0)
	{
	admin t;
	int choice;
	t.create_student(*this);
    //t.create_teacher(list);
    student_insert(t);
    //list.teacher_insert(t);	
	}
	fin.close();
}
void admin::student_ending()
{
	ofstream fout;
	int i,j;
	fout.open("rv.txt",ios::out|ios::trunc);
	admin a1;
	admin *start;
	start=student_head;
	while(start!=NULL)
	{
		strcpy(a1.name,start->name);
		strcpy(a1.USN,start->USN);
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				a1.sub[i][j]=start->sub[i][j];
			}
				a1.ex[i]=start->ex[i];
				a1.complete[i]=start->complete[i];
				a1.total[i]=start->total[i];
		}
		a1.gpa=start->gpa;
		fout.write((char*)&a1,sizeof(a1));
		start=start->student_next;
	}
	fout.close();
}
void admin::teacher_begin(){
	int ch=0;
	ifstream fin;
	fin.open("teacher.txt",ios::in);
	admin a;
	while(fin.read((char*)&a,sizeof(a)))
	{	teacher_insert(a);
	    ch=1;
	}
	if(ch==0)
	{	admin t;
		 t.create_teacher(*this);
    	teacher_insert(t);
	}
	fin.close();
}
void admin::teacher_ending()
{
	ofstream fout;
	int i,j;
	fout.open("teacher.txt",ios::out|ios::trunc);
	admin a1;
	admin *start;
	start=teacher_head;
	while(start!=NULL)
	{
		strcpy(a1.username,start->username);
		strcpy(a1.passwd,start->passwd);
		a1.s=start->s;
		fout.write((char*)&a1,sizeof(a1));
		start=start->teacher_next;
	}
	fout.close();
}
int main()
{   admin list;
   list.student_begin();
    list.teacher_begin();
	admin t;
	int choice;
	//t.create_student(list);
    //t.create_teacher(list);
    //list.student_insert(t);
    //list.teacher_insert(t);
    list.display();
    do{system("cls");
	cout<<"-----------------------------------------\n";
	cout<<"\tREPORT CARD GENERATOR\t\n";
	cout<<"------------------------------------------\n";
	cout<<"1.ADMIN"<<endl;
	cout<<"2.TEACHER"<<endl;
	cout<<"3.STUDENT"<<endl;
	cout<<"4.EXIT"<<endl;
	cin>>choice;
	switch(choice)
	{
	case 1:	
		admin_entry(list);
		break;
	case 2:
		teacher_entry(list);
		break;
	case 3:
		student_entry(list);
		break;
	case 4:
		goto v;
	break;	
		default:
			cout<<"invalid";
	}
	cout<<"1 to continue 0 to exit\n:";
	cin>>choice;
}while(choice==1);
	v:list.student_ending();
	  list.teacher_ending();
		cout<<"-----------------------------------------\n";
		cout<<"\t\tTHANK YOU\t\t\n";
		cout<<"-----------------------------------------\n";
	  return 0;
	
}
