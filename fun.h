#include"graphics.h"

class shop : public ui{
	private:
		struct data{
			string name;
			int sp,stock;
			bool in;
		};
		
		struct trie{
			trie *next[26];
			bool last = false;
			bool incart = false;
			int line ;
			data *info;
		};
		
		string itemname;
		vector<string> L;
		vector<int> St,Sp;
		trie *head = NULL;
		int fline; // Line number in file
		int total;
		
	public:
		shop();
		void newshop();
		string pass();	
		string getitem();
		void additem(string);
		void retrive();
		void home();	
		void lock();
		void keeper();
		void admin();
		void bye();
		void buyer_list();
		void get_list(trie*);
		void cart();
		void bill();
		void buy(string);
		void addcart(string,int,int);
		void init_list(trie*);
		void update(data*,int);
		void addnewDriver();
		void UpdateDriver();
		void updateitem(string);
		data* getdata(string str)
		{
				ofstream file;
        		data *item;
       			item = new data;
       		 	item->name=str;
        		cout<<"\n\nEnter Selling Price of "<<itemname<<" \n----> ";
        		cout<<"\n\nEnter Available Stock of "<<itemname<<"\n----> ";
       			gotoxy(6,5);
        		cin>>item->sp;
        		gotoxy(6,8);
        		cin>>item->stock;
        		file.open("shop.txt",ios::app);
        		file<<item->name<<" "<<item->sp<<" "<<item->stock<<"\n";
        		file.close();
        		return item;
		}
		void settings();
		void change_pass();
		bool check(string);
		
		~shop()
        {
            remove("cart.txt");
        }
};

shop::shop(){
	
	total = 0;
	ifstream file("shop.txt"); //items in shop along with sp
	int i;
	head  = new trie;
	for(i = 0 ; i < 26 ; i ++)
		head->next[i] = NULL;
	if(file.fail())
	{
		file.close();
		newshop();
	}
	else
	{
		file.close();
		ifstream("user.txt") ;// user password and graphics
		file>>bag>>forg>>sel>>password;
		file.close();
		retrive();
	}
	
}




void shop::newshop(){
	init();
	string p1,p2;
	int num = 0 ;
	string str;
	passw:
		init();
	cout<<"\nHello Shop Owner ...\nAs this is a New shop , There is Nothing in the stock Right now ";
    cout<<"\nIt is recommended to add some new Items First \n";
    cout<<"\nBefore that,";
    cout<<"\n\nSet a Password : ";
    cout<<"\n\nConfirm Your Password : ";
    gotoxy(17,7);
            p1=pass();
            gotoxy(24,9);
            p2=pass();
            if(p1!=p2)
            {
                cout<<"\n\n\n\nPassword Confirmation Failed, Please Try again\n\nPress Any Key to Continue . . . .";
                getch();
                goto passw;

            }    
            else
	        {
	                password=p1;
	                ofstream file("user.txt");
	                file<<bag<<"\n"<<forg<<"\n"<<sel<<"\n"<<password;
	                file.close();
	            }
	            
	            
	        while(num<=0)
            {
                cout<<"\n\nHow Many Items Would You Like to Add ? : ";
                cin>>num;
                if(num<=0)
                    cout<<"\nCannot Add "<<num<<" Items , Try Again !!";
            }
            for(int i=0;i<num;i++)
            {
                init();
                cout<<"\nEnter Item You Want To add :  ";
                cin.ignore();
                str=getitem();
                additem(str);
                cout<<"\nItem Added Successfully ";
            }
            cout<<"\nNow You Are Good to Go !\nPress Any Key to Continue . . . .";
            getch();
            home();
    
	
}

void shop::retrive()
{
	init();
	ifstream file("shop.txt");
	trie *mov;
	while(!file.eof())
	{
		trie *t;
		mov = head;
		data *dat;
		dat = new data;
		file >> dat->name >> dat->sp >> dat->stock;
		dat->in = false;
		for(int i=0;i<dat->name.length();i++)
		{
			if(mov->next[dat->name[i]-'A']==NULL)
			{
				t = new trie;
				t->info = NULL;
				for(int j = 0 ; j < 26 ; j++)
				{
					t->next[j] = NULL;
				}
				
				mov->next[dat->name[i]-'A'] = t;
			}
			
			mov = mov->next[dat->name[i]-'A'];
		}
			mov->last=true;
            mov->info = dat;
            mov->line=fline;
            fline++;
	}
	home();
}

string shop::getitem()
{
		string tmp,op;
        string sh;
        getline(cin,sh);
        itemname=sh;
        transform(sh.begin(),sh.end(),sh.begin(),::toupper);
        stringstream s(sh);
        while(s>>tmp)
        {
            op+=tmp;
        }
        return op;
}


void shop::additem(string item)
{
		trie *mov;
        mov=head;

        for(int i=0;i<item.length();i++)
        {
            trie *ch;
            if(!mov->next[item[i]-'A'])
            {
                ch=new trie;
                for(int j=0;j<26;j++)
                    ch->next[j]=NULL;
                ch->last=0;
                ch->info=NULL;
                mov->next[item[i]-'A']=ch;
            }
            mov=mov->next[item[i]-'A'];
        }
        mov->last=1;
        mov->line=fline++;
        mov->info=getdata(item);
}

void shop::home()
{
				int choice;
		        vector<string> v;
		        v.push_back("Use to Manipulate/Update Items");
		        v.push_back("Use to Sell Items");
		        while(1)
		        {
		            init();
		            choice=selector(v);
		
		            switch(choice)
		            {
		                case 1:lock();
		                    break;
		                case 2:keeper();
		                    break;
		                case -1:return;
		                case 0:bye();
		            }
		        }
}


void shop::lock()
{
        init();
        string sq;
        cout<<"Welcome to Admin Login...";
        cout<<"\n\nEnter Admin Password: ";
        sq=pass();
        if(password==sq)
        {
            cout<<"\n\nAdmin verified...\n\n\nPress any key to continue...";
            getch();
            admin();
        }
        else{
            cout<<"\n\nIncorrect password...\n\n\nPress any key to continue....";
            getch();
            home();
        }

}


void shop::keeper()
{
            vector<string> v;
            v.push_back("List Items");
            v.push_back("View Cart");
            v.push_back("Print Bill, Exit");
            int ch;
            while(1)
            {
                ch=selector(v);
                switch(ch)
                {
                    case -1:return;
                    case 0 : bye();
                    case 1 : buyer_list();
                        break;
                    case 2: cart();
                        break;
//                    case 3:bill();
//                        break;
                }

            }
}

void shop::admin()
{
        int choice;
        trie *mov;
        vector<string> v;
        v.push_back("List All Items");
        v.push_back("Add New Item");
        v.push_back("Update Existing Item");
        v.push_back("Settings");
        while(1)
        {

            choice=selector(v);
            switch(choice)
            {
               case -1:return;
                case 0:bye();
                case 1:
                    mov=head;
                    init_list(mov);
                    break;
                case 2:addnewDriver();
                    break;
                case 3:UpdateDriver();
                break;
                case 4:settings();
            }
        }
}


void shop::bye()
{
            init();
            ifstream ok("cart.txt");
            int in;

            vector<string> v;
            v.push_back("Yes, Discard Cart");
            v.push_back("NO, Continue Shopping");
            if(ok.fail())
            {
                exit:

                cout<<"Thank You\nFor Shopping\nIn Our Shop\n\nPlease Visit Again !!!";
                cout<<"\n\n\nPress Any Key To Exit . . . . ";
                getch();
                exit(0);
            }
            else
            {
                ok.close();
                string msg = "\nYou Haven't Checked Out Yet !\nExiting Now Will Discard Your Cart\nDo You Still Want To continue ? \n\n";
                in=selector(v,msg);
                switch(in)
                {
                    case 1:
                        remove("cart.txt");
                        goto exit;
                        break;
                    default:return;
                }
			}

}

void shop::buyer_list()
{
            trie *mov;
            mov=head;
            char ch=1;
            int loop;
            int x=0;
            while(1)
            {
                init();
                L.clear();
                Sp.clear();
                St.clear();
                get_list(mov);
                loop=L.size();
                cout<<setw(10)<<"Item Name"<<setw(14)<<"Price"<<setw(18)<<"Stock"<<endl;
                for(int i=0;i<L.size();i++)
                {
                    if(i==x)
                        color(16*bag+sel);
                    else
                        color(16*bag+forg);

                    cout<<setw(10)<<L[i]<<setw(14)<<Sp[i]<<setw(18)<<St[i]<<endl;
                }
                if(loop==0)
                {
                    cout<<"\nNot Any item Found";

                }
                ch=getch();
                if(ch<='z'&& ch >='a')
                {
                    x=0;
                    mov=head;
                    mov=mov->next[ch-'a'];
                }
                else if(ch=='0')
                {
                    mov=head;
                }
                else if(ch==8)
                {
                    return;
                }
                else if(ch==13)
                {
                    buy(L[x]);
                }
                else
                {
                    if(ch==56)
                    {
                        x==0?x=loop-1:x--;
                    }
                    if(ch==50)
                    {
                        x==loop-1?x=0:x++;
                    }
                }

            }
}

void shop::get_list(trie *mov)
{
            if(mov)
            {
                for(int i=0;i<26;i++)
                {
                    if(mov->next[i])
                    {
                        get_list(mov->next[i]);

                    }

                }
                if(mov->last==true && mov->info->name!="")
                {
                    //cout<<endl<<mov->info->name<<endl;
                   L.push_back(mov->info->name);
                   St.push_back(mov->info->stock);
                   Sp.push_back(mov->info->sp);
                }
            }
}

void shop::cart()
{
            init();
            ifstream ok("cart.txt");
            vector<string> name;
            string s;
            int a,b,c;
            vector<int> sp,tot,qty;
            int i=0;
            if(ok.fail())
            {
                cout<<"\nCart is Empty . . .";
                cout<<"\n\nPress any key to continue . . .";
                getch();
                return;
            }
            while(!ok.eof())
            {
                ok>>s>>a>>b>>c;
                name.push_back(s);
                sp.push_back(a);
                qty.push_back(b);
                tot.push_back(c);
                i++;
            }
            ok.close();
            cout<<setw(10)<<"Item Name"<<setw(14)<<"Price"<<setw(18)<<"Qty"<<setw(22)<<"Total Price"<<endl;
            for(int k=0;k<i;k++)
                cout<<setw(10)<<name[k]<<setw(14)<<sp[k]<<setw(18)<<qty[k]<<setw(22)<<tot[k]<<endl;
            cout<<"\nTotal - "<<total;
            cout<<"\n\nPress any key to continue . . .";
            getch();

}

void shop::bill()
{

            init();
            ifstream ok("cart.txt");
            vector<string> name;
            string s;
            int a,b,c;
            vector<int> sp,tot,qty;
            int i=0;
            while(!ok.eof())
            {
                ok>>s>>a>>b>>c;
                name.push_back(s);
                sp.push_back(a);
                qty.push_back(b);
                tot.push_back(c);
                i++;
            }
            ok.close();
            cout<<"--------------------------------------------------------------------------------------";
            cout<<setw(10)<<"Item Name"<<setw(14)<<"Price"<<setw(18)<<"Qty"<<setw(22)<<"Total Price"<<endl;
            cout<<"--------------------------------------------------------------------------------------";
            for(int k=0;k<i;k++)
                cout<<setw(10)<<name[k]<<setw(14)<<sp[k]<<setw(18)<<qty[k]<<setw(22)<<tot[k]<<endl;
            cout<<"--------------------------------------------------------------------------------------";
            cout<<setw(22)<<"Total - "<<total;
            remove("cart.txt");
            bye();

}
void shop::buy(string s)
{
            init();
            int qty;
            char ch;
            trie *mov=head;
            for(int i=0;i<s.length();i++)
                mov=mov->next[s[i]-'A'];
            cout<<"Selling Price of "<<s<<" = "<<mov->info->sp;
            cout<<"\n\n"<<s<<" in Stock = "<<mov->info->stock;
            cout<<"\n\nDo You want to buy "<<s<<" ? [y/n] ";
            cin>>ch;
            if(ch=='y')
            {
                cout<<"\n\nHow many "<<s<<" Do you want to buy ? : ";
                cin>>qty;
                if(qty<=0 || qty>mov->info->stock)
                {
                    cout<<"\nInvalid Quantity !!!";
                    cout<<"\n\nPress any key to continue. . .";
                    getch();
                }
                else
                {
                    mov->info->stock-=qty;
                    update(mov->info,mov->line);
                    addcart(mov->info->name,mov->info->sp,qty);
                }
            }

}
void shop::addcart(string name, int sp, int qty)
{
            ofstream cart("cart.txt",ios::app);
            cart<<name<<" "<<sp<<" "<<qty<<" "<<sp*qty<<"\n";
            total+=sp*qty;
            cout<<"\n"<<name<<" Successfully Added to Cart !!";

            cout<<"\n\nPress any key to Continue. . . .";
            getch();
}

void shop::update(data* item , int line)
{
        ifstream rem;
        ofstream file;
        string sh;
        int c=0;
        rem.open("shop.txt");
        file.open("nww.txt");
        while(!rem.eof())
        {
            getline(rem,sh);
            if(c==line)
            {
                file<<item->name<<" "<<item->sp<<" "<<item->stock<<"\n";
            }
            else
            {
                file<<sh<<"\n";
            }
            c++;
        }
        rem.close();
        file.close();
        remove("shop.txt");
        rename("nww.txt","shop.txt");

}

void shop::init_list(trie* mov)
{
            init();
            L.clear();
            St.clear();
            Sp.clear();
            get_list(mov);
            color(bag*16+sel);
            cout<<setw(10)<<"Item Name"<<setw(14)<<"Price"<<setw(18)<<"Stock"<<endl;
            color(bag*16+forg);
            for(int i=0;i<L.size();i++)
            {
                cout<<setw(10)<<L[i]<<setw(14)<<Sp[i]<<setw(18)<<St[i]<<endl;
            }
            cout<<"\n\nPress Any Key to Continue . . . .";
            getch();
}
	
void shop::addnewDriver()
{
        init();
        string item;
        fflush(stdin);
        cout<<"\nEnter Item You Want to Add : ";
        item=getitem();
        if(check(item))
        {
            cout<<"\nItem Already Exists\nRedirecting to Update Item ..\n\nPress Any Key to Continue . . . .";
            getch();
            updateitem(item);
            return;
        }
        else
        {
            additem(item);
        }

}

void shop::UpdateDriver()
{
        init();
        string item;
        fflush(stdin);
        cout<<"\nEnter Item You Want to Update : ";
        item=getitem();
        if(!check(item))
        {
            cout<<"\nItem Doesnot Exists\nRedirecting to Add Item ..\n\nPress Any Key to Continue . . . .";
            getch();
            init();
            additem(item);
            return;
        }
        else
        {
            updateitem(item);
        }
}

void shop::updateitem(string item)
{
        int ch;
        trie *mov;
        mov=head;
        for(int i=0;i<item.length();i++)
        {
            mov=mov->next[item[i]-'A'];
        }

        ch=0;
        cout<<"\nEnter Selling Price of "<<mov->info->name<<" ( press 0 for no change ) :  ";
        cin>>ch;
        if(ch)
            mov->info->sp=ch;
        ch=0;
        cout<<"\nEnter Updated Stock of "<<mov->info->name<<" ( press 0 for no change ) :  ";
        cin>>ch;
        if(ch)
            mov->info->stock=ch;
        cout<<mov->info->name;
        update(mov->info,mov->line);

}
string shop::pass()
{
            string str;
            char ch[20];
            int i;
            for(i=0;;i++)
            {
                ch[i]=getch();
                if(ch[i]==8)
                {
                    cout<<"\b \b";
                    if(i>2)
                        i-=2;
                }
                else if(ch[i]==13)
                {
                    ch[i]='\0';
                    break;
                }
                else
                {
                    cout<<"*";
                }
            }
            for(int j=0;j<i;j++)
            {
                str+=ch[j];
            }
            return str;
}


void shop::settings()
{
        vector<string> v;
        v.push_back("Change Background Color");
        v.push_back("Change Foreground Color");
        v.push_back("Change Highlight Color");
        v.push_back("Change Password");
        int in;
        while(1)
        {
            init();
            in=selector(v);
            switch(in)
            {
                case -1:return;
                    break;
                case 0:
                    bye();
                    break;
                case 1:
                    change_bg();
                    break;
                case 2:
                    change_fg();
                    break;
                case 3:
                    change_hi();
                    break;
                case 4:
                    change_pass();
                    break;
            }
        }


}


void shop::change_pass()
{
        string p1,p2,p3;
        init();
        cout<<"\n\nEnter Your Old Password : ";
        cout<<"\n\nEnter New Password : ";
        cout<<"\n\nConfirm New Password : ";
        gotoxy(27,2);
        p1=pass();
        gotoxy(22,4);
        p2=pass();
        gotoxy(24,6);
        p3=pass();
        if(p2==p3 && p1==password)
        {
            password=p2;
            save();
            cout<<"\n\nPassword Successfully Changed !";
            cout<<"\n\n\nPress any Key to Continue . . . .";
            getch();
            return;
        }
        else
        {
            cout<<"\n\nInvalid Password !!";
            cout<<"\n\n\nPress any Key to Continue . . . .";
            getch();
            return;
        }
    }

bool shop::check(string item)
{
        trie *mov;
        mov=head;
        if(mov==NULL)
        {
            return 0;
        }
        for(int i=0;i<item.length();i++)
        {
            if(!mov->next[item[i]-'A'])
            {
                return 0;
            }
            mov=mov->next[item[i]-'A'];
        }
        if(mov->last==1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
}


