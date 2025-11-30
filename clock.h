#include <iostream>
#include<ctime>
#include<string>
#include<conio.h>
#include<windows.h>
using namespace std;

void view_time();
void set_alarm();


void clock_logic()
{

    int choice_check=1;
    while(true)
    {
        system("cls");
    cout<<"==================="<<endl;
    cout<<"      CLOCK       "<<endl;
    cout<<"==================="<<endl;
    cout<<(choice_check == 1 ? "=>VIEW TIME\n" : "VIEW TIME\n");
    cout<<(choice_check == 2 ? "=>SET-ALARM\n" : "SET-ALARM\n");
    cout<<(choice_check == 3 ? "=>EXIT\n" : "EXIT\n");
    cout<<"==================="<<endl;
    char key = _getch();
    if (key == 72 && choice_check > 1)choice_check--;
    else if(key == 80 && choice_check < 3)choice_check++;
    else if (key == 13)
    {
        system("cls");
        switch (choice_check)
        {
            case 1:
                view_time();
                break;
            case 2:
                cout<<"alarm feature coming soon!"<<endl;
                system("pause");
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                Sleep(1000);
                break;
        }
    }
    }

}
void view_time()
{
    int hour,minute,second,year,month,day;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    year = 1900 + ltm->tm_year;
    month = 1 +ltm->tm_mon;
    day = ltm->tm_mday;
    hour = ltm->tm_hour;
    minute = ltm->tm_min;
    second = ltm->tm_sec;
    cout<<"Date: "<<day<<"/"<<month<<"/"<<year<<endl;
    cout<<"Time: "<<hour<<":"<<minute<<":"<<second<<endl;
 }   
void set_alarm()
{  int ahour,aminute,asecond;
    cout<<"enter alarm time (HH MM SS): ";
    cin>>ahour>>aminute>>asecond;
    cout<<"Alarm set for "<<ahour<<":"<<aminute<<":"<<asecond<<endl;
    if (ahour<0 || ahour>23 || aminute<0 || aminute>59 || asecond<0 || asecond>59)
    {
        cout<<"invalid time format. please try again."<<endl;
        system("pause");
        return;
    }
    while (true)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int hour = ltm->tm_hour;
        int minute = ltm->tm_min;
        int second = ltm->tm_sec;
        if (hour == ahour && minute == aminute && second == asecond)
        {
            cout<<"ALARM! ALARM! ALARM!"<<endl;
            Beep(1000, 500);
            Beep(1200, 500);
            Beep(1400, 500);
            Beep(1600, 500);
            Beep(1800, 500);
            Beep(2000, 500);
            Beep(2200, 500);
            Beep(2400, 500);
            break;
        }
        Sleep(1000);
    }

}  















