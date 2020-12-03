#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;
class ui
{
protected:
    int forg,bag,sel;
    string password;
public :
    ui()
    {
        ifstream file("data.txt");
        if(file.fail())
        {
            file.close();
            forg=9;
            bag=15;
            sel=12;
            password="shop";

        }
        else
        {
            file>>bag>>forg>>sel>>password;
        }

    }
    void color(int c)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
    }
    void gotoxy(int x,int y)
    {
        COORD pos;
        pos.X=x;
        pos.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    }
    void init()
    {
        color(bag*16+forg);
        system("cls");
        gotoxy(0,25);
        cout<<"[up]-8   [down]-2    [select]-enter  [back]-backspace    [exit]-escape\n\n";
        gotoxy(0,0);

    }
    int selector(vector<string> v)
    {
        int loop=v.size();
        int x=0;
        int i;
        char option;
        while(1)
        {
            init();
            for(i=0;i<loop;i++)
            {
                if(i==x)
                    color(bag*16+sel);
                else
                    color(bag*16+forg);
                cout<<v[i]<<endl;
            }
            option=getch();
            if(option==13)
            {
                return x+1;
            }
            else if(option==8)
            {
                return -1;
            }
            else if(option==27)
            {
                return 0;
            }
            else
            {
                if(option==56)
                {
                    x==0?x=loop-1:x--;
                }
                if(option==50)
                {
                    x==loop-1?x=0:x++;
                }
            }

        }
    }
    int selector(vector<string> v, string s)
    {
        int loop=v.size();
        int x=0;
        int i;
        char option;
        while(1)
        {
            init();
            cout<<s;
            for(i=0;i<loop;i++)
            {
                if(i==x)
                    color(bag*16+sel);
                else
                    color(bag*16+forg);
                cout<<v[i]<<endl;
            }
            option=getch();
            if(option==13)
            {
                return x+1;
            }
            else if(option==8)
            {
                return -1;
            }
            else if(option==27)
            {
                return 0;
            }
            else
            {
                if(option==56)
                {
                    x==0?x=loop-1:x--;
                }
                if(option==50)
                {
                    x==loop-1?x=0:x++;
                }
            }

        }
    }
    void change_bg()
    {
        vector<string> v;
        int x=bag;
        int i;
        v.push_back("Black");
        v.push_back("Blue");
        v.push_back("Green");
        v.push_back("Aqua");
        v.push_back("Red");
        v.push_back("Purple");
        v.push_back("Yellow");
        v.push_back("White");
        v.push_back("Gray");
        v.push_back("Light Blue");
        v.push_back("Light Green");
        v.push_back("Light Aqua");
        v.push_back("Light Red");
        v.push_back("Light Purple");
        v.push_back("Light Yellow");
        v.push_back("Bright White");
        int loop=v.size();
        char option=2;
        while(1)
        {

            color(x*16+forg);
            system("cls");
            for(i=0;i<loop;i++)
            {
                if(i==x)
                    color(x*16+sel);
                else
                    color(x*16+forg);
                cout<<v[i]<<endl;
            }
            option=getch();
            if(option==13)
            {
                bag=x;
                save();
                return;
            }
            else if(option==8)
            {
                return ;
            }
            else
            {
                if(option==56)
                {
                    x==0?x=loop-1:x--;
                }
                if(option==50)
                {
                    x==loop-1?x=0:x++;
                }
            }

        }

    }
    void change_fg()
    {
        vector<string> v;
        int x=forg;
        int i;
        v.push_back("Black");
        v.push_back("Blue");
        v.push_back("Green");
        v.push_back("Aqua");
        v.push_back("Red");
        v.push_back("Purple");
        v.push_back("Yellow");
        v.push_back("White");
        v.push_back("Gray");
        v.push_back("Light Blue");
        v.push_back("Light Green");
        v.push_back("Light Aqua");
        v.push_back("Light Red");
        v.push_back("Light Purple");
        v.push_back("Light Yellow");
        v.push_back("Bright White");
        int loop=v.size();
        char option=2;
        while(1)
        {

            init();
            for(i=0;i<loop;i++)
            {
                if(i==x)
                    color(bag*16+sel);
                else
                    color(bag*16+x);
                cout<<v[i]<<endl;
            }
            option=getch();
            if(option==13)
            {
                forg=x;
                save();
                return;
            }
            else if(option==8)
            {
                return ;
            }
            else
            {
                if(option==56)
                {
                    x==0?x=loop-1:x--;
                }
                if(option==50)
                {
                    x==loop-1?x=0:x++;
                }
            }

        }

    }
    void change_hi()
    {
        vector<string> v;
        int x=sel;
        int i;
        v.push_back("Black");
        v.push_back("Blue");
        v.push_back("Green");
        v.push_back("Aqua");
        v.push_back("Red");
        v.push_back("Purple");
        v.push_back("Yellow");
        v.push_back("White");
        v.push_back("Gray");
        v.push_back("Light Blue");
        v.push_back("Light Green");
        v.push_back("Light Aqua");
        v.push_back("Light Red");
        v.push_back("Light Purple");
        v.push_back("Light Yellow");
        v.push_back("Bright White");
        int loop=v.size();
        char option=2;
        while(1)
        {

            color(bag*16+forg);
            system("cls");
            for(i=0;i<loop;i++)
            {
                if(i==x)
                    color(bag*16+x);
                else
                    color(bag*16+forg);
                cout<<v[i]<<endl;
            }
            option=getch();
            if(option==13)
            {
                sel=x;
                save();
                return;
            }
            else if(option==8)
            {
                return ;
            }
            else
            {
                if(option==56)
                {
                    x==0?x=loop-1:x--;
                }
                if(option==50)
                {
                    x==loop-1?x=0:x++;
                }
            }

        }

    }
    void save()
    {
        remove("data.txt");
        ofstream file("data.txt");
        file<<bag<<"\n"<<forg<<"\n"<<sel<<"\n"<<password;
        file.close();
    }




};
