#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;


void login_logic();
void login();
void register_user();


string username;
string password;
bool logged_in = false;
bool running = true;


string password_generator()
{
    const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string generated_password;
    for (int i = 0; i < 5; ++i)
    {
        generated_password += chars[rand() % chars.size()];
    }
    return generated_password;
}
void login_menu()
{
   cout << "=========================================" << endl;
   cout << "          LOGIN MENU                    " << endl;
   cout << "=========================================" << endl;
   cout << "1. Login" << endl;
   cout << "2. Register" << endl;
   cout << "3. Exit" << endl;
   cout << "=========================================" << endl;
}

void login()
{   
    system("color 0A");
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("passwords.txt");
    string line;
    bool found = false;
    while (getline(file, line))
    {
        if (line == username + ":" + password)
        {
            found = true;
            logged_in = true;
            break;
        }
    }
    file.close();

    if (found)
    {
        cout << "Login successful! Welcome, " << username << endl;
        system("pause");
        running = false;
    }
    else
        cout << "Invalid username or password.\n";
}

void register_user()
{   
    system("cls");
    cout << "Enter new username: ";
    string new_username;
    cin >> new_username;
    cout << "Enter new password Or generate custom password (press n): ";
    string new_password;
    cin >> new_password;

    if (new_password == "n")
    {
        new_password = password_generator();
        cout << "Generated password: " << new_password << endl;
    }

    ofstream file("passwords.txt", ios::app);
    file << new_username << ":" << new_password << endl;
    file.close();

    cout << "User registered successfully!\n";
}

void login_logic()
{
   int choice = 1; 
   

   while (running)
   {
       system("cls");
       cout << "=========================================" << endl;
       cout << "          LOGIN MENU                    " << endl;
       cout << "=========================================" << endl;

       cout << (choice == 1 ? "1.=> LOGIN\n"     : "1. Login\n");
       cout << (choice == 2 ? "2.=> REGISTER\n"  : "2. Register\n");
       cout << (choice == 3 ? "3.=> EXIT\n"      : "3. Exit\n");

       cout << "=========================================" << endl;

       char key = _getch();

       if (key == 72 && choice > 1) choice--;  

       else if (key == 80 && choice < 3) choice++; 

       else if (key == 13) 
       {
           system("cls");
           switch (choice)
           {
               case 1:
                   if (!logged_in)
                       login();
                   else
                       cout << "Already logged in as " << username << endl;
                   break;
               case 2:
                   register_user();
                   break;
               case 3:
                   cout << "Exiting..." << endl;
                   running = false;
                   break;
           }
           if (running)
           {
               cout << "\nPress any key to return to menu...";
               _getch();
           }
       }
   }
}
 
