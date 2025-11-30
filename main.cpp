#include <iostream>
#include "loginsystem.h"
#include <conio.h>
#include <windows.h>
#include "settings.h"
#include "calculator.h"
#include "space_trader_demo1.h"
#include "clock.h"


using namespace std;
int main()
{
    
    SetConsoleOutputCP(CP_UTF8);
    system("chcp 65001 >nul");
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    
    a: login_logic();
    if (logged_in) 
    {   system("cls");
        cout << "Welcome, " << username << "!" << endl;
    }
    else
    {   system("cls");
        cout << "Login failed." << endl;
        cout << "Try again or exit? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
         {
            goto a;
        } 
        else {
            exit(0);}

            
    }
    while(logged_in)
    {
        system("cls");
        SetConsoleTextAttribute(hConsole, 0xA7);
       cout << "\t\t\t=========================" << endl; 
       cout<< "\t\t\t||      PHONE MENU      ||"<<endl;
       SetConsoleTextAttribute(hConsole, 7);
       cout << "\t\t\t||1.  ⚙️  Settings       ||" << endl;
       cout << "\t\t\t||2.  🧮   Calculator   ||" << endl;
       cout << "\t\t\t||3.  🎮   Games        ||" << endl;
       cout << "\t\t\t||4.  🎵   Music App    ||" << endl;
       cout << "\t\t\t||5.  🌦️   Weather       ||" << endl;
       cout << "\t\t\t||6.  📍   Location     ||" << endl;
       cout << "\t\t\t||7.  🗓️   Planner       ||" << endl;
       cout << "\t\t\t||8.  🎨   Pixel Draw   ||" << endl;
       cout << "\t\t\t||9.  ⏰   Clock        ||" << endl;
       cout << "\t\t\t=========================" << endl;
       char key = _getch();
        system("cls");
        switch(key)
        {
        case '1':
            settings_logic();
            break;
        case '2':
            calculator_logic();
            break;
        case '3':
            space_trader_logic();
            break;
        case '4':
            cout<<"music app coming soon!"<<endl;
            system("pause");
            break;
        case '5':
            cout<<"weather app coming soon!"<<endl;
            system("pause");
            break;
        case '6':
            cout<<"location app coming soon!"<<endl;
            system("pause");
            break;
        case '7':
            cout<<"planner app coming soon!"<<endl;
            system("pause");
            break;
        case '8':
            cout<<"pixel draw app coming soon!"<<endl;
            system("pause");
            break;
        case '9':
            clock_logic();
            system("pause");
            break;        
        default:
           cout << "Invalid choice. Please try again." << endl;
            system("pause");
             break;
        }
    }
    return 0;


}