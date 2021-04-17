#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<stdio.h>
#include<fstream.h>
#include<graphics.h>

class PRODUCT
{ int p_no;
  char p_name[20];
  int quantity;
  float price;
  int discount;
  public:
  PRODUCT()
  {
    p_no=0;
    strcpy(p_name,"NULL");
    quantity=0;
    price=0.00;
    discount=0;
  }
  void ENTER();
  void SHOW();
  int NUMBER()
  {  return p_no;
  }
  char* NAME()
  {  return p_name;
  }
  int QUANTITY()
  {  return quantity;
  }
  float PRICE()
  {  return price;
  }
  int DISCOUNT()
  {  return discount;
  }
} P;
void PRODUCT::ENTER()
{
  gotoxy(25,5);
  cout<<"Enter product number: ";
  cin>>p_no;

  gotoxy(25,6);
  cout<<"Enter product name: ";
  gets(p_name);

  gotoxy(25,7);
  cout<<"Enter price of the product: ";
  cin>>price;

  gotoxy(25,8);
  cout<<"Enter quantity of products: ";
  cin>>quantity;

  gotoxy(25,9);
  cout<<"Enter discount of product: ";
  cin>>discount;
}
void PRODUCT::SHOW()
{
  gotoxy(25,5);
  cout<<"Product number:   "<<p_no;
  gotoxy(25,6);
  cout<<"Product name:     ";
  puts(p_name);
  gotoxy(25,7);
  cout<<"Product price:    "<<price;
  gotoxy(25,8);
  cout<<"Product quantity: "<<quantity;
  gotoxy(25,9);
  cout<<"Product discount: "<<discount;
}

void LOGIN()
{ clrscr();
  int pos=1;
  char pass1,pass2,pass3,pass4,pass5;
  gotoxy(30,9);
  cout<<"ENTER LOGIN PASSWORD: ";
  pass1=getch();
  cout<<"*";
  pass2=getch();
  cout<<"*";
  pass3=getch();
  cout<<"*";
  pass4=getch();
  cout<<"*";
  pass5=getch();
  cout<<"*";

  if((pass1=='s')&&(pass2=='a')&&(pass3=='n')&&(pass4=='d')&&(pass5=='y'))
    pos=0;
  clrscr();
  if(pos==0)
  {
     return;
  }
  else
  {  gotoxy(30,9);
     cout<<"SORRY!!! INCORRECT PASSWORD";
  }
  getch();
  exit(0);
}

void BOX(void)
{
  for(int i=18;i<60;i+=2)
  { gotoxy(i,1);
    cout<<"+";
  }
  for(i=18;i<60;i+=2)
  { gotoxy(i,3);
    cout<<"+";
  }
  for(i=18;i<60;i+=2)
  { gotoxy(i,21);
    cout<<"+";
  }
  for(i=1;i<22;i++)
  { gotoxy(16,i);
    cout<<"+";
  }
  for(i=1;i<22;i++)
  { gotoxy(61,i);
    cout<<"+";
  }
}

void CREATE()
{
  BOX();
  gotoxy(32,2);
  cout<<"CREATE PRODUCT";
  ofstream fout;
  fout.open("market.dat",ios::out|ios::app|ios::binary);
  P.ENTER();
  fout.write((char*)&P, sizeof(PRODUCT));
  fout.close();
  gotoxy(25,20);
  cout<<"THE PRODUCT HAS BEEN CREATED...";
  getch();
}

void DISPLAY()
{
  clrscr();
  BOX();
  gotoxy(32,2);
  cout<<"DISPLAY ALL PRODUCTS";
  ifstream fin;
  fin.open("market.dat",ios::in|ios::binary);
  while(fin.read((char*)&P,sizeof(PRODUCT)))
  {
    P.SHOW();
    getch();
  }
  fin.close();
  getch();

}

void SEARCH()
{
   int flag=0,x;
   BOX();
   gotoxy(32,2);
   cout<<"SEARCH PRODUCT";
   gotoxy(25,4);
   cout<<"ENTER THE PRODUCT NUMBER: ";
   cin>>x;
   ifstream fin;
   fin.open("market.dat",ios::in|ios::binary);
   while(fin.read((char*)&P,sizeof(PRODUCT)))
   {
     if(P.NUMBER()==x)
     {
       P.SHOW();
       flag=1;
     }
   }
   fin.close();
   if(flag==0)
   {
     gotoxy(25,13);
     cout<<"RECORD NOT EXIST";
   }
   getch();
}

void MODIFY()
{
   int n,pos,flag=0;
   clrscr();
   BOX();
   gotoxy(32,2);
   cout<<"MODIFY PRODUCT";
   gotoxy(25,4);
   cout<<"ENTER THE PRODUCT NUMBER: ";
   cin>>n;
   fstream f;
   f.open("market.dat",ios::in|ios::out);
   while(f.read((char*)&P,sizeof(PRODUCT)))
   {
     if(P.NUMBER()==n)
     {
       P.SHOW();
       getch();
       clrscr();
       BOX();
       gotoxy(32,2);
       cout<<"MODIFY PRODUCT";
       gotoxy(25,4);
       cout<<"Enter the new details:- ";
       P.ENTER();
       pos=-1*sizeof(P);
       f.seekp(pos,ios::cur);
       f.write((char*)&P,sizeof(PRODUCT));
       gotoxy(25,14);
       cout<<"RECORD UPDATED";
       flag=1;
     }
   }
   f.close();
   if(flag==0)
   {
     gotoxy(25,14);
     cout<<"RECORD NOT FOUND";
   }
   getch();
}

void DELETE()
{
  int n;
  clrscr();
  BOX();
  gotoxy(32,2);
  cout<<"DELETE RECORD";
  gotoxy(25,4);
  cout<<"Enter the product number: ";
  cin>>n;
  fstream f,f1;
  f.open("market.dat",ios::in|ios::binary);
  f1.open("bazar.dat",ios::out|ios::binary);
  f.seekg(0,ios::beg);
  while(f.read((char*)&P,sizeof(PRODUCT)))
  {
    if(P.NUMBER()!=n)
    {
      f1.write((char*)&P,sizeof(PRODUCT));
    }
  }
  f.close();
  f1.close();
  remove("market.dat");
  rename("bazar.dat","market.dat");
  gotoxy(25,14);
  cout<<"RECORD DELETED ";
  getch();
}

void MENU()
{
  clrscr();
  ifstream fin;
  fin.open("market.dat",ios::in|ios::binary);
  if(!fin)
  {
    cout<<"\t\t\tERROR!!! FILE NOT OPEN";
    cout<<"\n\n\t\t\tGO TO ADMIN MENU TO CREATE FILE";
    cout<<"\n\n\n\t\t\tPROGRAM IS CLOSING...";
    getch();
    exit(0);
  }
  BOX();
  gotoxy(32,2);
  cout<<"PRODUCT MENU";
  gotoxy(32,4);
  cout<<"PRODUCT LIST";
  for(int i=18;i<59;i++)
  {
    gotoxy(i,5);
    cout<<"-";
    gotoxy(i,7);
    cout<<"-";
  }
  gotoxy(20,6);
  cout<<"P.NO\t\tNAME\t\tPRICE";
  while(fin.read((char*)&P,sizeof(PRODUCT)))
  {
    gotoxy(20,8);
    cout<<P.NUMBER()<<"\t\t"<<P.NAME()<<"\t\t "<<P.PRICE();
  }
  fin.close();
}

void ORDER()
{
  int order[20], qty[20], c=0;
  float amt, damt, total=0;
  char ch='y';
  MENU();
  getch();
  clrscr();
  BOX();
  gotoxy(32,2);
  cout<<"PLACE YOUR ORDER";
  do
  {
    gotoxy(25,4);
    cout<<"ENTER THE PRODUCT NUMBER: ";
    cin>>order[c];
    gotoxy(25,5);
    cout<<"QUANTITY: ";
    cin>>qty[c];
    c++;
    gotoxy(20,10);
    cout<<"DO YOU WANT TO ORDER MORE?? (Y/N): ";
    cin>>ch;
  }while((ch=='y')||(ch=='Y'));
  gotoxy(25,12);
  cout<<"THANK YOU";
  getch();
  clrscr();
  BOX();
  gotoxy(32,2);
  cout<<"--:YOURS BILL:--";
  gotoxy(17,4);
  cout<<"P.NO  P.NAME  QTY  PRICE  AMOUNT\   DIS_PRICE";
  ifstream fin;
  for(int i=17;i<61;i++)
  {
    gotoxy(i,5);
    cout<<"-";
  }
  for(i=0;i<=c;i++)
  {
     fin.open("market.dat",ios::in|ios::binary);
     fin.read((char*)&P,sizeof(PRODUCT));
     while(!fin.eof())
     {
	if(P.NUMBER()==order[i])
	{
	  amt=P.PRICE()*order[i];
	  damt=amt-(amt*P.DISCOUNT()/100);
	  gotoxy(20,6);
	  cout<<order[i]<<" "<<P.NAME()<<" "<<qty[i]<<" "<<P.PRICE()<<" "<<amt<<"\t"<<damt;
	  total=total+damt;
	}
	fin.read((char*)&P,sizeof(PRODUCT));
     }
     fin.close();
  }
  gotoxy(25,10);
  cout<<"TOTAL= "<<total;
  getch();
}

void INTRO()
{
  clrscr();
  BOX();
  gotoxy(25,2);
  cout<<"|----------WELCOME----------|";
  gotoxy(28,5);
  cout<<"||SUPER MARKET BILLING||";
  gotoxy(34,10);
  cout<<"-:PROJECT:-";
  gotoxy(18,17);
  cout<<"Made By: Roshmi Chakrabortty * Sandip Ash";
  gotoxy(26,18);
  cout<<"* Sayan Mukherjee * Sayan Mondal";
  gotoxy(18,20);
  cout<<"School: DAV Public School,DVC,MTPS";
  getch();
}

void ADMINISTRATION()
{
  clrscr();
  BOX();
  char ch;
  gotoxy(32,2);
  cout<<"ADMINISTRATION MENU";
  gotoxy(28,4);
  cout<<"1. CREATE PRODUCT";
  gotoxy(28,6);
  cout<<"2. DISPLAY ALL PRODUCTS";
  gotoxy(28,8);
  cout<<"3. SEARCH PRODUCT ";
  gotoxy(28,10);
  cout<<"4. MODIFY PRODUCT ";
  gotoxy(28,12);
  cout<<"5. DELETE PRODUCT ";
  gotoxy(28,14);
  cout<<"6. PRODUCT MENU ";
  gotoxy(28,16);
  cout<<"7. BACK TO MAIN MENU";
  gotoxy(28,18);
  cout<<"8. EXIT ";
  gotoxy(25,20);
  cout<<"ENTER YOUR CHOICE: ";
  ch=getch();
  switch(ch)
  {
    case '1':
	clrscr();
	textcolor(10);
	CREATE();
	break;
    case '2':
	textcolor(7);
	DISPLAY();
	break;
    case '3':
	clrscr();
	textcolor(5);
	SEARCH();
	break;
    case '4':
	textcolor(15);
	MODIFY();
	break;
    case '5':
	textcolor(25);
	DELETE();
	break;
    case '6':
	textcolor(3);
	MENU();
	getch();
    case '7':
	break;
    case '8':
	exit(0);
	break;
    default:
	textcolor(19);
	cout<<"\a";
	ADMINISTRATION();
    }
}

void main()
{
   char ch;
   textcolor(30);
   INTRO();
   textcolor(22);
   LOGIN();
   do
   {
      clrscr();
      BOX();
      gotoxy(34,2);
      cout<<"MAIN MENU";
      gotoxy(32,4);
      cout<<"1. CUSTOMER";
      gotoxy(30,6);
      cout<<"2. ADMINISTRATION";
      gotoxy(34,8);
      cout<<"3. EXIT";
      gotoxy(25,19);
      cout<<"ENTER YOUR CHOICE: ";
      ch=getch();
      switch(ch)
      {
	 case '1':
	     clrscr();
	     textcolor(25);
	     ORDER();
	     getch();
	     break;
	 case '2':
	     textcolor(30);
	     ADMINISTRATION();
	     break;
	 case '3':
	     exit(0);
	     break;
	 default:
	     cout<<"SORRY!!! WRONG INPUT";
	     break;
      }
   }while(ch!='3');
}

