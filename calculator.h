#include <iostream>
#include <cmath>
#include <conio.h>
using namespace std;
double x,y;
void take_nums(double &x,double &y)
{
    cout<<"enter first number: ";
    cin >> x;
    cout<<"enter second number: ";
    cin >> y;
}

void addition()
{
    take_nums(x,y);
    cout<<"the addition is: "<<x + y<<endl;
    system("pause");
}
void substraction()
{
    take_nums(x,y);
    cout<<"the substraction is: "<<x - y<<endl;
    system("pause");
}
void division()
{
    take_nums(x,y);
    if (y == 0)
    {
        cout<<"error: division by zero is undefined."<<endl;
    }
    else
    {
        cout<<"the division is: "<<x / y<<endl;
    }
    system("pause");
}
void multiplication()
{
    take_nums(x,y);
    cout<<"the multiplication is: "<<x * y<<endl;
    system("pause");
}


void calculator_logic()
{  int choice = 1;
    bool runn = true;
    while (runn)
    {
    system("cls");
    
    cout<<"==========================================="<<endl;
    cout<<"                CALCULATOR                  "<<endl;
    cout<<(choice == 1? "=>ADDITION\n" : "addition\n");
    cout<<(choice == 2 ? "=>MULTIPLICATION\n" :"multiplication\n");
    cout<<(choice == 3 ? "=>SUBSTRACTION\n":"substraction\n");
    cout<<(choice == 4 ? "=>DIVISION\n":"division\n");
    cout<<(choice== 5 ? "=>EXIT\n":"exit\n");
    char key = _getch();
    if ( key == 72 && choice > 1)choice--;
    else if(key == 80 && choice <5)choice++;
    else if (key == 13)
    {
        system("cls");
        switch(choice)
        {
            case 1:
              addition();
              break;
            case 2:
              multiplication();
              break;
            case 3:
                substraction();
                break;
            case 4:
                division();  
                break;
            case 5:
                runn = false;    
            default:
                calculator_logic();  
                break;        
        }
    }}
}
