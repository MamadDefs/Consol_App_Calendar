#include <iostream>
#include <ctime>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;

//=============================================================
// in this function we are using the formula which gives us the number of the week day with givven day , month and year => https://www.tondering.dk/claus/cal/chrweek.php#calcdow
int dayofweek(int d, int m, int y)  
{  
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };  
    y -= m < 3;  
    return ( y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}
//=============================================================
//in this function we are showing the user the notes that we take on a current date
void showNotes(int day_,int month_,int year_,string type)
{
    system("cls");
    string day=to_string(day_);
    string month=to_string(month_);
    string year=to_string(year_);
    if(type=="persian")
    {
        fstream persian;
	    persian.open("persian.txt");
	    string line,d,m,y;
	    while (getline(persian,line))
        {
            getline(persian,y);
            getline(persian,m);
            getline(persian,d);
            if(d==day && m==month && y==year)
                cout<<line<<endl;
        }
    
	    persian.close();
    }
    if(type=="gregorian")
    {
        fstream gregorian;
	    gregorian.open("gregorian.txt");
	    string line,d,m,y;
	    while (getline(gregorian,line))
        {
            getline(gregorian,y);
            getline(gregorian,m);
            getline(gregorian,d);
            if(d==day && m==month && y==year)
                cout<<line<<endl;
        }
    
	    gregorian.close();
    }
	system("pause");
    system("cls");
}
//=============================================================
// in this function we are adding a note to current date that we are in it 
void addNotes(int day,int month,int year,string type)
{
    system("cls");
    string line;
    if(type=="persian")
    {
        cout<<"Enter the note : ";
        fstream persian;
        persian.open("persian.txt",ios::app);
        getline(cin,line);
        persian<<line<<endl;
        persian<<year<<endl;
        persian<<month<<endl;
        persian<<day<<endl;
        persian.close();
    }
    if(type=="gregorian")
    {
        cout<<"Enter the note : ";
        fstream gregorian;
        gregorian.open("gregorian.txt",ios::app);
        getline(cin,line);
        gregorian<<line<<endl;
        gregorian<<year<<endl;
        gregorian<<month<<endl;
        gregorian<<day<<endl;
        gregorian.close();
    }
    system("cls");
}
//=============================================================
// checking if there is a note for a givven date or not
bool isRed(int day_,int month_,int year_,string type)
{
    string day=to_string(day_);
    string month=to_string(month_);
    string year=to_string(year_);
    if(type=="persian")
    {
        fstream persian;
	    persian.open("persian.txt");
	    string line,d,m,y;
	    while (getline(persian,line))
        {
            getline(persian,y);
            getline(persian,m);
            getline(persian,d);
            if(d==day && m==month && y==year)
                return true;
        }
    
	    persian.close();
    }
    if(type=="gregorian")
    {
        fstream gregorian;
	    gregorian.open("gregorian.txt");
	    string line,d,m,y;
	    while (getline(gregorian,line))
        {
            getline(gregorian,y);
            getline(gregorian,m);
            getline(gregorian,d);
            if(d==day && m==month && y==year)
                return true;
        }
	    gregorian.close();
    }
    return  false;
}
//======================================================================================
// we will define a class with 6 variable 
//year = current year
//day = current day
//month = current month
//weekDay = the number of the day in a week
//nameOfMonth = hold the name of the current month
//typeOFCalendar = represent the type of calendar | it can be gregorain or persian 
//***************************************************************************************
//fucntions
//display = will print the calendar (persian and gregorian are diffrent calendars due to the typeOfCalendar variable)
//setNameToMonth = this function will use the month variable and will set a name for month into nameOfMonth variable (the name depends on type of calendar)
//MaxDayOfMonth = this function will return the days that current month have - we will use this for printing the calendar and moving forward and backward in it
//converter = this function will use the (https://github.com/SCR-IR/jalaliDate-Cpp) and personalize it to convert the gregorian date to perisan date
//dayOfweek_persian = we will convert persian date to gregorian date with using this source : (https://github.com/SCR-IR/jalaliDate-Cpp) ||| and after that we will calculate the number of the day in week with using this formula : https://www.tondering.dk/claus/cal/chrweek.php#calcdow
// n = moving forward in calendar
// p = moving backward in calendar
// s = watching or writing Notes for current day  
class date
{
private:
    int year,month,day,weekDay;
    string nameOfMonth;
    string typeOfCalendar;
public:
    date(string);
    void display();
    void SetNameToMonth();
    int MaxDayOfMonth();
    void converter(int,int,int);
    int dayOfWeek_persian(int,int,int);
    void n();
    void p();
    void s();
};

//=============================================================
 date::date(string t)
{
   time_t now = time(0);
   tm *ltm = localtime(&now);
   //gregorian dates
   year=1900+ltm->tm_year;
   month=1 + ltm->tm_mon;
   day=ltm->tm_mday;
   weekDay=dayofweek(day,month,year);
   this->typeOfCalendar=t;
   //convert to persian dates
   if(this->typeOfCalendar=="persian")
   converter(this->day,this->month,this->year);
   //setting the name of the month based on type of calendar
   SetNameToMonth();
}
//=============================================================
int date::dayOfWeek_persian(int pd,int pm,int py)
{
  py += 1595;
  int days = -355668 + (365 * py) + (((int)(py / 33)) * 8) + ((int)(((py % 33) + 3) / 4)) + pd + ((pm < 7) ? (pm - 1) * 31 : ((pm - 7) * 30) + 186);
  int gy = 400 * ((int)(days / 146097));
  days %= 146097;
  if (days > 36524) {
    gy += 100 * ((int)(--days / 36524));
    days %= 36524;
    if (days >= 365) days++;
  }
  gy += 4 * ((int)(days / 1461));
  days %= 1461;
  if (days > 365) {
    gy += (int)((days - 1) / 365);
    days = (days - 1) % 365;
  }
  int gd = days + 1;
  int gm;
  {
    long sal_a[13] = {0, 31, ((gy % 4 == 0 && gy % 100 != 0) || (gy % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (gm = 0; gm < 13 && gd > sal_a[gm]; gm++) gd -= sal_a[gm];
  }
  static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };  
    gy -= gm < 3;  
    return ( gy + gy / 4 - gy / 100 + gy / 400 + t[gm - 1] + gd) % 7; 
}


//=============================================================
void date::converter(int gd, int gm, int gy)
{
  long days;
  {
    int gy2 = (gm > 2) ? (gy + 1) : gy;
    int g_d_m[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    days = 355666 + (365 * gy) + ((int)((gy2 + 3) / 4)) - ((int)((gy2 + 99) / 100)) + ((int)((gy2 + 399) / 400)) + gd + g_d_m[gm - 1];
  }
  int jy = -1595 + (33 * ((int)(days / 12053)));
  days %= 12053;
  jy += 4 * ((int)(days / 1461));
  days %= 1461;
  if (days > 365) {
    jy += (int)((days - 1) / 365);
    days = (days - 1) % 365;
  }
  this->year = jy;
  if (days < 186) {
    this->month/*jm*/ = 1 + (int)(days / 31);
    this->day/*jd*/ = 1 + (days % 31);
  } else {
    this->month/*jm*/ = 7 + (int)((days - 186) / 30);
    this->day/*jd*/ = 1 + ((days - 186) % 30);
  }
}

//=============================================================
void date::display()
{
int maxDays=MaxDayOfMonth();
int startDay;
if(this->typeOfCalendar=="gregorian")
{
    startDay=dayofweek(1,month,year);
    weekDay=dayofweek(day,month,year);
}
if(this->typeOfCalendar=="persian")
{
    startDay=dayOfWeek_persian(1,month,year);
    weekDay=dayOfWeek_persian(day,month,year);
}

this->SetNameToMonth();

if(this->typeOfCalendar=="gregorian")
{
    cout<<"--------------------------"<<endl;
    cout<<"     "<<nameOfMonth<<" , "<<year<<endl;
    cout<<"--------------------------"<<endl;
    cout<<"S   M   T   M   T   F   S    "<<endl;
for(int i=0;i<startDay;i++)
{
    cout<<"    ";
}
for(int i=0;i<maxDays;i++)
{
    if(startDay==6)
    {
        if(i+1==this->day)
        {
            cout<<"\033[3;104;30m"<<i+1<<"\033[0m"<<endl;
            startDay=0;
        }
        else
        {
            if(isRed(i+1,this->month,this->year,this->typeOfCalendar))
            {
                cout<<"\x1B[31m"<<i+1<<"\033[0m"<<endl;
                startDay=0;
            }
            else
            {
                cout<<i+1<<endl;
                startDay=0;
            }
        }
        
    }
    else
    {
        if(i+1<10)
        {
            if(i+1==this->day)
            {
                cout<<"\033[3;104;30m"<<i+1<<"\033[0m"<<"   ";
                startDay++;
            }
            else
            {
                if(isRed(i+1,this->month,this->year,this->typeOfCalendar))
                {
                    cout<<"\x1B[31m"<<i+1<<"\033[0m"<<"   ";
                    startDay++;
                }
                else
                {
                    cout<<i+1<<"   ";
                    startDay++;
                }
            }
        }
        else
        {
            if(i+1==this->day)
            {
                cout<<"\033[3;104;30m"<<i+1<<"\033[0m"<<"  ";
                startDay++;
            }
            else
            {
                if(isRed(i+1,this->month,this->year,this->typeOfCalendar))
                {
                    cout<<"\x1B[31m"<<i+1<<"\033[0m"<<"  ";
                    startDay++;
                }
                else
                {
                    cout<<i+1<<"  ";
                    startDay++;
                }
            }
            
        }
        
    }
}
}
if(this->typeOfCalendar=="persian")
{
    cout<<"--------------------------------"<<endl;
    cout<<"       "<<nameOfMonth<<" , "<<year<<endl;
    cout<<"--------------------------------"<<endl;
    cout<<"1S   2S   3S   4S   5S   J    S    "<<endl;
for(int i=0;i<startDay;i++)
{
    cout<<"     ";
}
for(int i=0;i<maxDays;i++)
{
    
    if(startDay==6)
    {
        if(i+1==this->day)
        {
            cout<<"\033[3;104;30m"<<i+1<<"\033[0m"<<endl;
            startDay=0;
        }
        else
        {
            if(isRed(i+1,this->month,this->year,this->typeOfCalendar))
            {
                cout<<"\x1B[31m"<<i+1<<"\033[0m"<<endl;
                startDay=0;
            }
            else
            {
                cout<<i+1<<endl;
                startDay=0;
            }
        }
        
    }
    else
    {
        if(i+1<10)
        {
            if(i+1==this->day)
            {
                cout<<"\033[3;104;30m"<<i+1<<"\033[0m"<<"    ";
                startDay++;
            }
            else
            {
                if(isRed(i+1,this->month,this->year,this->typeOfCalendar))
                {
                    cout<<"\x1B[31m"<<i+1<<"\033[0m"<<"    ";
                    startDay++;
                }
                else
                {
                    cout<<i+1<<"    ";
                    startDay++;
                }
            }
        }
        else
        {
            if(i+1==this->day)
            {
                cout<<"\033[3;104;30m"<<i+1<<"\033[0m"<<"   ";
                startDay++;
            }
            else
            {
                if(isRed(i+1,this->month,this->year,this->typeOfCalendar))
                {
                    cout<<"\x1B[31m"<<i+1<<"\033[0m"<<"   ";
                    startDay++;
                }
                else
                {
                    cout<<i+1<<"   ";
                    startDay++;
                }
            }
            
        }
        
    }
}
}
cout<<endl<<"--------------------------------"<<endl;
cout<<"n-Next\np-Previous\ns-Read or Write Notes\nq-Quit\n";
cout<<"Option= ";
cout<<endl;
}
//=============================================================
void date::SetNameToMonth()
{
    if(this->typeOfCalendar=="gregorian")
    {
        switch(this->month)
            {
                case 1: this->nameOfMonth="January";break;;
                case 2: this->nameOfMonth="February";break;
                case 3: this->nameOfMonth="March";break;
                case 4: this->nameOfMonth="April";break;
                case 5: this->nameOfMonth="May";break;
                case 6: this->nameOfMonth="June";break;
                case 7: this->nameOfMonth="July";break;
                case 8: this->nameOfMonth="August";break;
                case 9: this->nameOfMonth="September";break;
                case 10: this->nameOfMonth="October";break;
                case 11: this->nameOfMonth="November";break;
                case 12: this->nameOfMonth="December";break;
                default: break;
            }
    }
    if(this->typeOfCalendar=="persian")
    {
        switch(this->month)
            {
                case 1: this->nameOfMonth="Farvardin";break;;
                case 2: this->nameOfMonth="Ordibehesht";break;
                case 3: this->nameOfMonth="Khordad";break;
                case 4: this->nameOfMonth="Tir";break;
                case 5: this->nameOfMonth="Mordad";break;
                case 6: this->nameOfMonth="Shahrivar";break;
                case 7: this->nameOfMonth="Mehr";break;
                case 8: this->nameOfMonth="Aban";break;
                case 9: this->nameOfMonth="Azar";break;
                case 10: this->nameOfMonth="Dey";break;
                case 11: this->nameOfMonth="Bahman";break;
                case 12: this->nameOfMonth="Esfand";break;
                default: break;
            }
    }
    
}
//=============================================================
int date::MaxDayOfMonth()
{
    if(this->typeOfCalendar=="gregorian")
    {
          switch(this->month)
            {
                case 1: return 31;break;;
                case 2: return 28;;break;
                case 3: return 31;break;
                case 4: return 30;break;
                case 5: return 31;break;
                case 6: return 30;break;
                case 7: return 31;break;
                case 8: return 31;break;
                case 9: return 30;break;
                case 10: return 31;break;
                case 11: return 30;break;
                case 12: return 31;break;
                default: break;
            }  
    }
    if(this->typeOfCalendar=="persian")
    {
          switch(this->month)
            {
                case 1: return 31;break;;
                case 2: return 31;;break;
                case 3: return 31;break;
                case 4: return 31;break;
                case 5: return 31;break;
                case 6: return 31;break;
                case 7: return 30;break;
                case 8: return 30;break;
                case 9: return 30;break;
                case 10: return 30;break;
                case 11: return 30;break;
                case 12: return 29;break;
                default: break;
            }  
    }
    
}
//=============================================================
void date::n()
{
    if(this->MaxDayOfMonth()!=this->day)
    this->day++;
    else
        {
            if(this->month!=12)
            {
                this->month++;
                this->day=1;
            }
            else
            {
                this->year++;
                this->month=1;
                this->day=1;
            }
        }
}

//=============================================================
void date::p()
{
    if(this->typeOfCalendar=="gregorian")
    {
    if(this->day!=1)
    this->day--;
    else
        {
            if(this->month!=1)
            {
                this->month--;
                this->day=this->MaxDayOfMonth();
            }
            else
            {
                this->year--;
                this->month=12;
                this->day=this->MaxDayOfMonth();
            }
        }        
    }
    if(this->typeOfCalendar=="persian")
    {
    if(this->day!=1)
    this->day--;
    else
        {
            if(this->month!=1)
            {
                this->month--;
                this->day=this->MaxDayOfMonth();
            }
            else
            {
                this->year--;
                this->month=12;
                this->day=this->MaxDayOfMonth();
            }
        }        
    }
    
}
//=============================================================
void date::s()
{
    system("cls");
    char x;
    bool flag=false;
    while(!flag)
    {   
        cout<<"s-Show Notes\nw-Write a new Note\nq-back\n";
        x=getche();
        switch (x)
        {
        case 's':showNotes(this->day,this->month,this->year,this->typeOfCalendar); break;
        case 'w':addNotes(this->day,this->month,this->year,this->typeOfCalendar); break;
        case 'q': flag=true; break;
        default:  system("cls"); break;
        }
    }
}
//=============================================================
void PersianCalendar()
{
    date G("persian");
    system("cls");
    G.display();
    char x;
    bool flag=false;
    while(!flag)
    { 
        x=getche();
        switch (x)
        {
        case 'n':G.n(); break;
        case 'p':G.p(); break;
        case 's':G.s(); break;
        case 'q': flag=true; break;
        default:  system("cls"); G.display(); break;
        }
    }
}
//=============================================================
void GregorianCalendar()
{
    date G("gregorian");
    system("cls");
    G.display();
    char x;
    bool flag=false;
    while(!flag)
    {   
        x=getche();
        switch (x)
        {
        case 'n':G.n();  break;
        case 'p':G.p();  break;
        case 's': G.s(); break;
        case 'q': flag=true; break;
        default:  system("cls"); G.display(); break;
        }
    }
}
//=============================================================
int main()
{
    char x;
    bool flag=false;
    while(!flag)
    {   
        cout<<"p-Persian"<<endl<<"g-Gregorian"<<endl<<"q-Quit"<<endl;
        cout<<"Choose your calendar: ";
        x=getche();
        switch (x)
        {
        case 'p':PersianCalendar(); system("cls"); break;
        case 'g':GregorianCalendar(); system("cls"); break;
        case 'q': flag=true; break;
        default: system("cls"); break;
        }
    }
    cin.get();
    return 0;
}
