#include<iostream>
#include<fstream>
#include<conio.h>
#include<limits>
using namespace std;
const int MAX=100;
void insertnode(class Node* first_node, string basicString, string string1, int i1);
void display(Node* first_node);
fstream f;
int uid;
string uname;
string upass;
int uamount;
class Node
{
public:
    int id;
    string name;
    string pass;
    int amount;
    Node* next=NULL;
};
Node* first=new Node;

class Bank
{
public:
    Bank()
    {
        reload(first);
        cout<<"Welcome to Bank!"<<endl;
        cout<<"1.Login\n2.Register\n0.Exit"<<endl;
        while(1)
        {
            if(kbhit())
            {
                switch (getch())
                {
                    case '1':
                        login(first);
                        cout<<"1.Login\n2.Register\n0.Exit"<<endl;
                        break;
                    case '2':
                        reg();
                        cout<<"1.Login\n2.Register\n0.Exit"<<endl;
                        break;
                    case '0':
                        cout<<"Bye!";
                        write(first);
                        f.close();
                        free(first);
                        exit(0);
//                    default:
//                        cout<<"Invaild!"<<endl;
                }
            }
        }
    }
    void reg();
    void update(Node* current_node);
    void login(Node* first_node);
    void mainMenu(Node* first_node);
    void transfer(Node* first_node,Node* temp);
    void reload(Node* first_node);
    void write(Node* first_node);
private:
};
void Bank::login(Node* first_node)
{
    cout<<"Enter username to login : ";
    getline(cin,uname);

    cout<<"Enter password : ";
    getline(cin,upass);
    while(first_node!=NULL)
    {
        if(uname==first_node->name && upass==first_node->pass)
        {
            uid=first_node->id;
            cout<<"Login complete"<<endl;
//            cout<<"Your amount = "<< first_node->amount<<endl;
            mainMenu(first_node);
            return;
        }
        if(first_node->next==NULL)
        {
            cout<<"Username or password is wrong!"<<endl;
            return;
        }
        first_node=first_node->next;
    }
}
void Bank::reg()
{
    if(first==NULL)
    {
        printf("Memory cannot be created.");
        exit(0);
    }
    cout<<"Enter your name to register : ";
    getline(cin,uname);

    cout<<"Enter your password : ";
    getline(cin,upass);

    cout<<"Enter amount : ";
    cin>>uamount;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    insertnode(first,uname,upass,uamount);
//    insertnode(first,uname,upass,uamount);
//    display(first);
}
void Bank::update(Node* current_node)
{
    cout<<"1.Add money\n2.Get money\n0.Return"<<endl;
    while(1)
    {
        if(kbhit())
        {
            switch (getch())
            {
                case '1':
                    cout<<"Your amount = "<< current_node->amount<<endl;
                    cout<<"Enter amount to add : ";
                    cin>>uamount;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    current_node->amount=current_node->amount+uamount;
                    write(first);
                    cout<<"1.Add money\n2.Get money\n0.Return"<<endl;
                    break;
                case '2':
                    cout<<"Your amount = "<< current_node->amount<<endl;
                    cout<<"Enter amount to get cash : ";
                    cin>>uamount;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    current_node->amount=current_node->amount-uamount;
                    write(first);
                    cout<<"1.Add money\n2.Get money\n0.Return"<<endl;
                    break;
                case '0':
                    write(first);
                    return;
            }
        }
    }
};
void Bank::mainMenu(Node* first_node)
{
    cout<<"Welcome to Main Menu!"<<endl;
    cout<<"1.Check balance\n2.Transfer Money\n3.Update balance\n0.Return"<<endl;
    while(1)
    {
        if(kbhit())
        {
            switch (getch())
            {
                case '1':
                    cout<<"Your amount = "<< first_node->amount<<endl;
                    cout<<"1.Check balance\n2.Transfer Momey\n3.Update balance\n0.Return"<<endl;
                    break;
                case '2':
                    transfer(first_node,first);
                    cout<<"1.Check balance\n2.Transfer Momey\n3.Update balance\n0.Return"<<endl;
                    break;
                case '3':
                    update(first_node);
                    cout<<"1.Check balance\n2.Transfer Momey\n3.Update balance\n0.Return"<<endl;
                    break;
                case '0':
                    write(first);
                    return;
//                default:
//                    cout<<"Invaild!"<<endl;
            }
        }
    }
};
int main()
{
//    char ch;
//    while(1)
//    {
//    if (kbhit()) {
//        cout << "You pressed";
//        switch (getch()) {
//            case 'a':
//                cout << "You pressed a." << endl;
//        }
//    }
//    }
//    return 0;
    Bank mybank;
    return 0;
//    mybank.reg();
//    mybank.login(first);
}
void insertnode(Node* first_node,string name,string pass,int amount)
{
    int id=1;
    f.open("database.txt",ios::app);
    if(first_node==NULL)
    {
        cout<<"Error in insert"<<endl;
        return;
    }
    if(first_node->next==NULL)
    {
        first_node->id=id;
        first_node->name=name;
        first_node->pass=pass;
        first_node->amount=amount;
        Node* newNode=new Node;
        first_node->next=newNode;
        f<<first_node->id<<"|"<<first_node->name<<"|"<<first_node->pass<<"|"<<first_node->amount<<endl;
        f.close();
        return;
    }
    while(first_node!=NULL)
    {
        if(first_node->next==NULL)
        {
            first_node->id=id;
            first_node->name=name;
            first_node->pass=pass;
            first_node->amount=amount;
            Node* newNode=new Node;
            first_node->next=newNode;
            f<<first_node->id<<"|"<<first_node->name<<"|"<<first_node->pass<<"|"<<first_node->amount<<endl;
            f.close();
            return;
        }
        first_node=first_node->next;
        id++;
    }
}
void Bank::transfer(Node *first_node,Node *temp)
{
    string rname;
    int ramount=0;
    cout<<"Enter username to transfer: ";
    getline(cin,rname);
    if(temp->next==NULL)
    {
        cout<<"No Data!"<<endl;
    }
    while(temp!=NULL)
    {
        if(temp->name==rname)
        {
            cout<<"Enter amount to transfer: ";
            cin>>ramount;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            first_node->amount=first_node->amount-ramount;
            temp->amount=temp->amount+ramount;
//            display(first);
            write(first);
            return;
        }
        if(temp->next==NULL)
        {
            cout<<"No username found!"<<endl;
//            transfer(first_node,first);
            return;
        }
        temp=temp->next;
    }
}
void Bank::reload(Node* first_node)
{
    if(first_node==NULL)
    {
        cout<<"Error in insert"<<endl;
        return;
    }
    string temp;
    f.open("database.txt",ios::in);
    if (!f)
    {
        f.close();
        ofstream database("database.txt");
        database.close();
        return;
    }
    while(f.peek() != EOF)
    {
        getline(f,temp,'|');
        first_node->id=stoi(temp);
        getline(f,temp,'|');
        first_node->name=temp;
        getline(f,temp,'|');
        first_node->pass=temp;
        getline(f,temp,'\n');
        first_node->amount=stoi(temp);
        Node* newNode=new Node;
        first_node->next=newNode;
        first_node=first_node->next;
    }
    f.close();
};
void Bank::write(Node* first_node)
{
    f.open("database.txt",ios::out);
    if (!f)
    {
        f.close();
        ofstream database("database.txt");
        database.close();
        f.open("database.txt",ios::out);
    }
    while(first_node->next!=NULL)
    {
        f<<first_node->id<<"|"<<first_node->name<<"|"<<first_node->pass<<"|"<<first_node->amount<<endl;
        first_node=first_node->next;
    }
    f.close();
}
void display(Node *first_node)
{
    if(first_node==NULL)
    {
        cout<<"Error in display"<<endl;
    }
    else if(first_node->next==NULL)
    {
        cout<<"There's no data!"<<endl;
    }
    else
    {
        while(first_node->next!=NULL)
        {
            cout<<first_node->id<<"|"<<first_node->name<<"|"<<first_node->pass<<"|"<<first_node->amount<<endl;
            first_node=first_node->next;
        }
    }
}
