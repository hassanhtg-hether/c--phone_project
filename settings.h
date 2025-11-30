#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
void settings_logic()
{
    cout<<"choose a theme: "<<endl;
    cout<<"1. Dark Mode"<<endl;
    cout<<"2. Light Mode"<<endl;
    cout<<"3. Retro Mode"<<endl;
    cout<<"4. Blueberry Purple Mode"<<endl;
    cout<<"5. Strawberry Mode"<<endl;
    cout<<"6. Mint Green Mode"<<endl;
    cout<<"7. Exit"<<endl;
    char key = _getch();
    switch(key)
    {
        case '1':
            cout<<"Dark Mode selected."<<endl;
            system("color 0F");
            break;
        case '2':
            cout<<"Light Mode selected."<<endl;
            system("color F0");
            break;
        case '3':
            cout<<"Retro Mode selected."<<endl;
            system("color 2E");
            break;
        case '4':
            cout<<"Blueberry Purple Mode selected."<<endl;
            system("color 5E");
            break;
        case '5':
            cout<<"Strawberry Mode selected."<<endl;
            system("color 4E");
            break;
        case '6':
            cout<<"Mint Green Mode selected."<<endl;
            system("color 3E");
            break;
        case '7':
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            Sleep(1000);
            break;
    }




}