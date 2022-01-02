#include<iostream>
#include<fstream>
#include<conio.h>
#include<cstring>
#include<iomanip>

void writedata();
void contactus();
void showuser(char[],char[]);
void showitemlist();
void additem();
void intro();
void thankyou();

using namespace std;

class shop
{
    public:
    int item_id;
    float mrp,gst,fprice,discount;
    char item_name[40];
    void showitems();
};

class order
{
public:
char username[25];    
char orderinput[10];
int inputindex;
void insertcart(char[]);
void placeorder(char[]);
void deleteorder(char[]);
void updatedetails();// to update all details order buy and cart update
};

class shopping
{
    private:
    
    public:
    char Name[90],Address[100],mob[11],uname[25],email[30],pwd[16],usign[25],psign[16];
    void signup();
    void signin();
    void signout();
    void displayuser();
    void cart();
};

//**********************************order class functions*************************************

//*************************************insertcart*********************************************
void order::insertcart(char name[])
{    
int flag=2;   
order od,od1;
strcpy(od1.username,name);
ofstream out;
ifstream in;
in.open("usercart.txt",ios::in);
while(in.read((char*)&od,sizeof(order)))
{
    if(!strcmp(od1.username,od.username))
    {
        od1.inputindex=od.inputindex;
        strcpy(od1.orderinput,od.orderinput);
        if(od1.inputindex==0)
        flag=0;
        else
        flag=1;
    }
}
cout<<"\nEnter the Item Id to BUY(0 to exit):-";
char a;
cin>>a;
if(a==48)
return;
if(flag==2)
{
od1.inputindex=0;
od1.orderinput[od1.inputindex++]=a;
out.open("usercart.txt",ios::app);
out.write((char*)&od1,sizeof(order));
out.close();
}
else if(flag==0)
{
od1.inputindex=0;
od1.orderinput[od1.inputindex++]=a;
od1.updatedetails();
}
else if(flag==1)
{
od1.orderinput[od1.inputindex++]=a;
od1.updatedetails();
}
in.close();
}
//******************************************placeorder*******************************************
void order::placeorder(char uname[])
{
    system("cls");
    cout<<"                                   PLACE ORDER\n";
    cout<<"                             ---------------------\n";
    float price=0;
    order od;
    ifstream in;
    in.open("usercart.txt",ios::in);
    if(!in)
    {
        cout<<"\nFile can not be opened!!!!!\n";
        getch();
        return;
    }
    cout<<"\n\n                                   YOUR CART\n";
    cout<<"                                  --------------\n";
    cout<<"Item ID"<<"     "<<"Item Name"<<setw(10)<<"   "<<"MRP"<<setw(8)<<"   "<<"GST"<<setw(8)<<"   "<<"Discount"<<setw(8)<<"   "<<"Price"<<"\n";
    while(in.read((char*)&od,sizeof(order)))
    {
    if(!strcmp(uname,od.username))
    {

        if(od.inputindex==0)
        {
            cout<<"\nThere are no element present in the cart !!!!!!";
            getch();
            return;
        }
        else
        {
         for(int i=0;i<od.inputindex;i++)
            {
                ifstream admin;
                shop ad;
                admin.open("itemlist.txt",ios::in);
                while(admin.read((char*)&ad,sizeof(shop)))
                {
                 if((od.orderinput[i]-48)==ad.item_id)
                 {
                 ad.showitems();
                 price+=ad.fprice;
                 }
                }
                admin.close();
            } 
             break;
        }       
    }
    }
    if(price==0)
    {
            cout<<"\nThere are no element present in the cart !!!!!!";
            getch();
            return;
    }
    cout<<"\nBill Details:-";
    cout<<"\nTotal Price:-"<<price;
    getch();
    cout<<"\nProceed to buy(Y/N):-";
    char choice;
    cin>>choice;
    if(choice=='y'||choice=='Y')
    {
    cout<<"\nItem Bought!!!!!";
    getch();
    strcpy(od.orderinput,"");
    od.inputindex=0;
    od.updatedetails();
    }
    in.close();
}
//****************************************update details*********************************************
void order::updatedetails()
{
order od;
fstream file;
file.open("usercart.txt",ios::out|ios::in);
if(!file)
{
    cout<<"\nFile can't be opened";
}
else
{
   while (file.read((char*)&od,sizeof(order)))
   {
       if(!strcmp(od.username,username))
        {
            int pos=(-1)*(sizeof(order));
			file.seekp(pos,ios::cur);
            file.write((char*)(this), sizeof(order));
        }
   }
    
}
file.close();
}
//**********************************************DELETE ORDER**************************
void order::deleteorder(char uname[])
{ 
system("cls");  
cout<<"                                  DELETE ORDER\n";
cout<<"                             ---------------------\n";   
order od;
ifstream in;
int flag=0;
in.open("usercart.txt",ios::in);  
if(!in)
{
    cout<<"\nFile can not be opened!!!!!!!\n";
    getch();
    return;
} 
else
{
cout<<"\n\n                                   YOUR CART\n";
cout<<"                                     --------------\n";  
cout<<"Item ID"<<"     "<<"Item Name"<<setw(10)<<"   "<<"MRP"<<setw(8)<<"   "<<"GST"<<setw(8)<<"   "<<"Discount"<<setw(8)<<"   "<<"Price"<<"\n";
while(in.read((char*)&od,sizeof(order)))
{
    if(!strcmp(uname,od.username))
    {

        if(od.inputindex==0)
        {
            cout<<"\nThere are no element present in the cart !!!!!!";
            getch();
            return;
        }
        else
        {
         for(int i=0;i<od.inputindex;i++)
            {
                ifstream admin;
                shop ad;
                admin.open("itemlist.txt",ios::in);
                while(admin.read((char*)&ad,sizeof(shop)))
                {
                 if((od.orderinput[i]-48)==ad.item_id)
                 {
                 ad.showitems();
                 }
                }
                admin.close();
            } 
             flag=1;
             break;
        }       
    }
}
if(flag==0)
{
            cout<<"\nThere are no element present in the cart !!!!!!";
            getch();
            return;
}
if(flag==1)
{
char a;     
cout<<"\nEnter the item id you want to delete:-";
cin>>a;
int i=0,j=0;
for(i=0;od.orderinput[i]!='\0';i++)
if(od.orderinput[i]!=a)
od.orderinput[j++]=od.orderinput[i];
od.orderinput[j]='\0';
od.inputindex=j;
od.updatedetails();
getch();
}
}
in.close();
}
//**********************************Shopping class functions*************************************


//*************************************Sign Up*****************************************************
void shopping::signup()
{ 
system("cls");
cout<<"                                              SIGN UP\n";
cout<<"                                         -------------------\n";    
cout<<"Hello User!";
cout<<"\nPlease enter your details below:-";
getchar();
cout<<"\nEnter your Name:-";
cin.getline(Name,90);
cout<<"\nEnter your Address:-";
cin.getline(Address,100);
cout<<"\nEnter your Mobile Number:-";
cin.getline(mob,11);
cout<<"\nEnter your Email Id:-";
cin.getline(email,30);
cout<<"\nPlease choose a username for your Account:-";
cin.getline(uname,25);
cout<<"\nCreate your Password(max 15 characters):-";
cin.getline(pwd,16);
}

//**********************************************Sign In**********************************************
bool userlogin;
void shopping::signin()
{ 
system("cls");    
cout<<"                                             SIGN IN\n";
cout<<"                                      ---------------------\n";
getchar();
cout<<"\nEnter your Username:-";
cin.getline(usign,25);
cout<<"\nEnter your Password:-";
cin.getline(psign,16);
int a;
userlogin=true;
getch();
order od;
while(userlogin)
{
system("cls");    
showuser(usign,psign);
if(userlogin==false)
break;
cout<<"\n";
cout<<"**************************************************************************************";
cout<<"\n                                       MENU";
cout<<"\n**************************************************************************************";
    cout<<"\n                                   1. Display Items";
    cout<<"\n                                   2. Sign out";   
    cout<<"\n                                   3. Cart"; 
    cout<<"\n                                   4. Contact Us";                                   
    cout<<"\n                                   Enter your choice(1-4):-";
    cin>>a;
    switch (a)
    {
    case  1:
        showitemlist();
        od.insertcart(usign);
        break;
    case  2:
        signout();
        userlogin=false;
        break;
    case 3:
        cart();
        break;    
    case  4:
        contactus();
        break;    
    default:
        cout<<"\nInvalid Choice";
        getch();
        break;
    }
}
}
//**************************************************cart*****************************************
void shopping::cart()
{
   
    bool active=true;
    int choice;
    order od;
    while(active)
    {
    system("cls");
    cout<<"                                          CART\n";
    cout<<"                                    ------------------\n";
    cout<<"\n1.Place Order";
    cout<<"\n2.Delete Item";
    cout<<"\n3.Goback";
    cout<<"\nEnter Your choice(1-3):-";
    cin>>choice;
    switch (choice)
    {
    case 1:
        od.placeorder(usign);
        break;
    case 2:
        od.deleteorder(usign);
        break;
    case 3:
        active=false;
        break;
    default:
        cout<<"\nInvalid Choice";
        break;
    }
    }
}

//****************************************Signout***********************************************************
void shopping::signout()
{
    cout<<"\nYou have been Signed Out";
}

//************************************User details***********************************************
void shopping::displayuser()
{
cout<<"\nName:- "<<Name;
cout<<"\nAddress:- "<<Address;
cout<<"\nMobile Number:- "<<mob;
cout<<"\nEmail Id:- "<<email<<"\n"; 
}

//******************************* Shop Class functions************************************* 

void shop::showitems()
{   
cout<<item_id<<"   "<<setw(20)<<item_name<<"  "<<setw(8)<<mrp<<"  "<<setw(10)<<gst<<"   "<<setw(10)<<discount<<"   "<<setw(12)<<fprice<<"\n";
}

int main(void)
{
    intro();
    getch();
    shopping shopper;
    char ch;
    label:
    do
    {
    system("cls");    
    int a;
    cout<<"**************************************************************************************";
    cout<<"\n                                       MENU";
    cout<<"\n**************************************************************************************";
    cout<<"\n                                   1. Display Items";
    cout<<"\n                                   2. Signup";
    cout<<"\n                                   3. Sign In";
    cout<<"\n                                   4. Contact Us";
   // cout<<"\n                                   5. add item list";//remove 
    cout<<"\n                                   Enter your choice(1-4):-";
    cin>>a;
    switch(a)
    {
        case 1:
        showitemlist();
        break;
        case 2:
        writedata();
        break;
        case 3:
        shopper.signin();
        break;
        case 4:
        contactus();
        break;
        case 5:
        additem();
        break;
        default:
            cout<<"\nInvalid choice ";
            break;
    }
    cout<<"\nDo you want to continue(Y/N):-";
    cin>>ch;
    } while (ch=='y'||ch=='Y');
    thankyou();
    return 0;
}

//file functions

//to create userdata file
void writedata()
{

    bool flag=false;
    shopping user,user2;
    user.signup();
    ofstream out;
    ifstream in;
    in.open("userdata.txt",ios::in);
    while(in.read((char*)&user2,sizeof(shopping)))
    {
    if(!strcmp(user.uname,user2.uname))
    {
       flag=true;
    }
    }
    in.close();
    if(flag!=true)
    {
    out.open("userdata.txt",ios::app);
    out.write((char*)&user,sizeof(user));
    out.close();
    }
    else
    cout<<"\nCan not create Account As the username is already taken!!!!!";
}

//to show contact us details
void contactus()
{
 system("cls");
 cout<<"                                       CONTACT US\n";
 cout<<"                                  ---------------------\n";   
 cout<<"Contact Deatils:-\n";
 ifstream in;
 in.open("contact.txt",ios::in);
 if(!in)
 {
 cout<<"File could not be open !! Press any Key...";
 return;
 }
 else
 {
     char ch;
     while(in.get(ch))
     {
                cout<<ch;
     }
 }
 getch();
}

//to show user details
void showuser(char usign[],char psign[])
{
shopping user;
ifstream in;
bool flag=false;
in.open("userdata.txt",ios::in);
if(!in)
{
    cout<<"File could not be open !! Press any key...";
    getch();
    userlogin=false;
    //return;
}
else
{
while(in.read((char*)&user,sizeof(shopping)))
{
    if(!strcmp(user.uname,usign))
    {
        if(!strcmp(user.pwd,psign))
        {
            user.displayuser();
            flag=true;
            break;
        }
    }
}
if(flag==false)
{
cout<<"\nInvalid Credentials!!!!!";
getch();
userlogin=false;
}
}
in.close();
}
//shop file functions
void additem()
{
    ofstream out;
    shop admin;
    float disc;
    out.open("itemlist.txt",ios::app);
    cout<<"\nEnter Item_id:-";
    cin>>admin.item_id;
    getchar();
    cout<<"\nEnter Item_name:-";
    cin.getline(admin.item_name,40);
    cout<<"\nEnter the MRP:-";
    cin>>admin.mrp;
    cout<<"\nEnter discount percentage:-";
    cin>>disc;
    admin.discount=(admin.mrp*disc)/100;
    if(admin.mrp>500.00)
    admin.gst=(admin.mrp*(18.00))/100;
    admin.fprice=admin.mrp+admin.gst-admin.discount;
    out.write((char*)&admin,sizeof(shop));
    out.close();
}

void showitemlist()
{
system("cls");    
cout<<"                                    ITEM LIST\n";
cout<<"                               ---------------------\n";
ifstream in;
shop admin;
in.open("itemlist.txt",ios::in);
if(!in)
{
    cout<<" File could not be open !! Press any key...";
    getch();
    return;
}
else
{
cout<<"Item ID"<<"     "<<"Item Name"<<setw(10)<<"   "<<"MRP"<<setw(8)<<"   "<<"GST"<<setw(8)<<"   "<<"Discount"<<setw(8)<<"   "<<"Price"<<"\n";    
while(in.read((char*)&admin,sizeof(shop)))
{
   admin.showitems();
} 
}
getch();
in.close();
}
//introduction
void intro()
{
    cout<<"\n************************************************************************************";
    cout<<"\n* ******************************************************************************** *";
    cout<<"\n* *                                                                              * *";
    cout<<"\n* *                           WELCOME!!!!!!!!!!!!!!                              * *";
    cout<<"\n* *                                                                              * *";
    cout<<"\n* *                               SHOPCLUSIVE                                    * *";
    cout<<"\n* *                            __________________                                * *";
    cout<<"\n* *               SHOPPING MANAGEMENT APPLICATION(CONSOLE BASED)                 * *";
    cout<<"\n* *                                                                              * *";
    cout<<"\n* *                          BY:-DIBYAJYOTI BHUYAN                               * *";
    cout<<"\n* *                                                                              * *";
    cout<<"\n* *                                                                              * *";
    cout<<"\n* ******************************************************************************** *";
    cout<<"\n************************************************************************************\n";
}
void thankyou()
{
    system("cls");
    cout<<"\n************************************************************************************";
    cout<<"\n* ******************************************************************************** *";
    cout<<"\n* *                                                                              * *";
    cout<<"\n* *                          THANK YOU!!!!!!!!!!!!                               * *";
    cout<<"\n* *                                                                              * *";
    cout<<"\n* *                               SHOPCLUSIVE                                    * *";
    cout<<"\n* *                            __________________                                * *";
    cout<<"\n* *                                                                              * *";
    cout<<"\n* *                SHOPPING MANAGEMENT APPLICATION(CONSOLE BASED)                * *";
    cout<<"\n* *                                                                              * *";
    cout<<"\n* *                           BY:-DIBYAJYOTI BHUYAN                              * *";
    cout<<"\n* *                                                                              * *";
    cout<<"\n* ******************************************************************************** *";
    cout<<"\n************************************************************************************\n";
    getch();
}