#include<iostream>
#include<string>
#include <conio.h>
#include<windows.h>
#include<cstdlib> 
#include<ctime>
#include<fstream>

using namespace std;

//prototypes

void running_game();
bool should_draw_planet(int x, int y);
int get_planet_color();
void settings_menu();
void draw_game_and_stats(int jet_x, int game_width, int height, string stats_lines[], int stats_count) ;
void check_event(int &fuel, int &credits, string stats[], int game_width, int height);
void space_trader_logic();
void about_game();
void trading_menu();
void sell_goods();
void buy_goods();
void view_market_prices();
void update_cargo();
int get_current_price(int item_index);
int get_planet_index();
void save_game(int jet_x, int fuel, int credits, int steps, int cargo, string area);
bool load_game(int &jet_x, int &fuel, int &credits, int &steps, int &cargo, string &area);

//structs and globals
struct Item {
    string name;
    int base_price;
    int quantity_owned;
};

struct Planet {
    string name;
    float price_multiplier[5];  
};

Item items[5] = {
    {"Water", 50, 0},
    {"Fuel Cells", 100, 0},
    {"Electronics", 200, 0},
    {"Minerals", 150, 0},
    {"Food", 75, 0}
};

Planet planets[5] = {
    {"Earth",   {1.0, 1.2, 0.8, 1.1, 0.9}}, 
    {"Mars",    {1.5, 0.9, 1.3, 0.7, 1.2}},
    {"Jupiter", {0.8, 1.4, 1.0, 1.5, 0.8}},  
    {"Saturn",  {1.3, 1.1, 0.9, 1.2, 1.4}},  
    {"Uranus",  {0.9, 0.8, 1.5, 1.0, 1.3}}   
};


// Global variables
int frequency = 440; 
bool audio_on = true;
bool music_playing = false;

int steps=0;
int next_event_at = 70;
string area = "Earth";
int credits = 500;

int cargo_capacity = 50;
int cargo_used = 0;


// Helper functions

void rocket_engine_sound()
 {
    if (!audio_on) return;  
    Beep(110, 20);      
}

DWORD WINAPI magical_space_tune(LPVOID lpParam)
 {
    int C4 = 262, D4 = 294, E4 = 330, F4 = 349, G4 = 392, A4 = 440;
int C5 = 523, D5 = 587, E5 = 659, F5 = 698, G5 = 784, A5 = 880,G3=196;

while (audio_on && music_playing) {
    
    Beep(C4, 300);
    Beep(E4, 300);
    Beep(G4, 300);
    Beep(C5, 600);
    Beep(G4, 300);
    Beep(E4, 300);
    Beep(C4, 600);
    Beep(G3, 300);
    Beep(C4, 300);
    Beep(E4, 300);
    Beep(G4, 600);
    Beep(E4, 300);
    Beep(C4, 300);
    Beep(G3, 600);
  
}
    return 0;
}

void SetColor(int color)
 {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void slow_scroller(string text,int delay = 5)
{   int k = 0;
    for (char c : text) {
         k++;
        if (k > 14) k = 1;
        SetColor(k); 
        cout << c;
        Beep(frequency,80);
        Sleep(delay); 
    }
    SetColor(7); 
    cout << endl;
}

void ShowConsoleCursor(bool showFlag)
 {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void ClearScreenNoFlicker() 
{
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//main game loop

// main game running function

void running_game(){
    int choice = 1;
    bool running = true;
    cout<<"Loading game..."<<endl;
    cout<<"use arrow keys or number keys to navigate the menu and press enter to select an option."<<endl;
    system("pause");
    while(running)
    {
        system("cls");
        cout << (choice == 1 ? "1.=> SETTINGS\n"     : "1. SETTINGS\n");
        cout << (choice == 2 ? "2.=> PLAY\n"         : "2. PLAY\n");
        cout << (choice == 3 ? "3.=> ABOUT THE GAME\n": "3. ABOUT THE GAME\n");
        cout << (choice == 4 ? "4.=> EXIT\n"         : "4. EXIT\n");
        cout << "===================================" << endl;

        char key = _getch();

        if (key == 72 && choice > 1) choice--;  
        else if (key == 80 && choice < 4) choice++; 
        else if (key == 13) 
        {
            system("cls");
            switch (choice)
            {
                case 1:
                    settings_menu();
                    system("cls");
                    break;
                case 2:
                    space_trader_logic();
                    break;
                case 3:
                    about_game();
                    break;
                case 4:
                    cout << "Exiting..." << endl;
                    running = false;
                    break;
            }
        }
    }
}


// game menu functions

void about_game()
{
slow_scroller("Space Trader is a fast-paced galaxy adventure where you travel between planets, buy and sell goods, and try to build your fortune. Each planet has changing prices, so every trip is a new opportunity.",2);
slow_scroller("But space is dangerous asteroids, pirates, and surprise loot can appear at any time. Manage your fuel, upgrade your cargo, and survive random events as you trade across the stars.",2);
slow_scroller("Your progress is saved using file handling so you can continue your journey anytime.",2);
slow_scroller("Created by Hassan Taimoor Ghazi, and Hafsa Qureshi.",2);
}

void settings_menu(){
    while(true){
    cout << "===================================" << endl;
    cout << "          SETTINGS MENU           " << endl;
    cout << "===================================" << endl;
    cout << "1. Audio Settings" << endl;
    cout << "2. Video Settings" << endl;
    cout << "3. Control Settings" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "===================================" << endl;
    char key = _getch();
    system("cls");
    switch(key)
    {
        case '1':
            
                cout<<"AUDIO STATUS: ";
            if (audio_on) 
                cout<<"ON"<<endl;
            else
                cout<<"OFF"<<endl;
            
            cout<<"CURRENT FREQUENCY: "<<frequency<<" Hz"<<endl;
            cout<<"press n to enter new frequency or t to toggle audio or e to exit: ";
            char audio_choice;
            cin>>audio_choice;
            if(audio_choice == 'n'){
                cout<<"Enter new frequency (in Hz): ";
                cin>>frequency;
                cout<<"Frequency updated to "<<frequency<<" Hz"<<endl;
            }
            else if(audio_choice == 't'){
                audio_on = !audio_on;
                cout<<"Audio turned "<<(audio_on ? "ON" : "OFF")<<endl;
            }    
            else if(audio_choice == 'e'){
                continue;
            }
            
            break;
        
        case '2':
           {

            cout<<"choose a theme: "<<endl;
            cout<<"1. Dark Mode"<<endl;
            cout<<"2. Light Mode"<<endl;
            cout<<"3. Retro Mode"<<endl;
            cout<<"4. Blueberry Purple Mode"<<endl;
            cout<<"5. Strawberry Mode"<<endl;
            cout<<"6. Mint Green Mode"<<endl;
            cout<<"7. Exit"<<endl;
            char key1 = _getch();
            if(key1 == '1'){
                cout<<"Dark Mode selected."<<endl;
                system("color 0F");
            }
            else if(key1 == '2'){
                cout<<"Light Mode selected."<<endl;
                system("color F0");
            }
            else if(key1 == '3'){
                cout<<"Retro Mode selected."<<endl;
                system("color 2E");
            }
            else if(key1 == '4'){
                cout<<"Blueberry Purple Mode selected."<<endl;
                system("color 5E");
            }
            else if(key1 == '5'){
                cout<<"Strawberry Mode selected."<<endl;
                system("color 4E");
            }
            else if(key1 == '6'){
                cout<<"Mint Green Mode selected."<<endl;
                system("color 3E");
            }
            else if(key1 == '7'){
                continue;
            }

            system("pause");
            break;
        }
        case '3':
        cout<<"control instructions: "<<endl;
            cout<<"Use W/A/S/D to navigate menus."<<endl;
            cout<<"Press Enter to select an option."<<endl;
            cout<<"press space to move forward in the game."<<endl;
            cout<<"Press Esc to go back to the previous menu."<<endl;
            system("pause");
            break;
        
        case '4':
            cout<<"Returning to main menu."<<endl;
            running_game();
            
            break;
            
        default:
           cout << "Invalid choice. Please try again." << endl;
            break;
    }
}
} 

// game-logic helping functions

int get_planet_index() {
    if (area == "Earth") return 0;
    if (area == "Mars") return 1;
    if (area == "Jupiter") return 2;
    if (area == "Saturn") return 3;
    if (area == "Uranus") return 4;
    return 0;
}

int get_current_price(int item_index) {
    int planet_idx = get_planet_index();
    return items[item_index].base_price * planets[planet_idx].price_multiplier[item_index];
}

void update_cargo() {
    cargo_used = 0;
    for (int i = 0; i < 5; i++) {
        cargo_used += items[i].quantity_owned;
    }
}

bool should_draw_planet(int x, int y) {
    
    return ((y == 6 && x >= 2 && x <= 4) ||
            (y == 7 && x >= 1 && x <= 5) ||
            (y == 8 && x >= 1 && x <= 5) ||
            (y == 9 && x >= 2 && x <= 4) ||
            (y == 5 && x >= 1 && x <= 3));
}

int get_planet_color() {
    
    if (steps >= 0 && steps <= 40) return 9;     
    if (steps > 100 && steps <= 140) return 12;
    if (steps > 200 && steps <= 240) return 6;    
    if (steps > 300 && steps <= 340) return 15;   
    if (steps > 400 && steps <= 440) return 3;    
    return -1;  
}

// game drawing functions

void draw_game_and_stats(int jet_x, int game_width, int height,string stats_lines[], int stats_count) 
{
    int spacing = 3;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < game_width; x++) {
            // Draws borders
            if (y == 0 || y == height - 1 || x == 0 || x == game_width - 1) {
                SetColor(1);
                cout << "*";
                SetColor(7);
            }
            // Draws road
            else if (y == 8) {
                SetColor(8);
                cout << "-";
                SetColor(7);
            }
            // Draws jet
            else if (y == 7 && x == jet_x) {
                SetColor(10);
                cout<< "#==";
                SetColor(4);
                cout << ">";
                SetColor(7);
                x += 3;
            }
            // Draws planets (using helper functions)
            else if (should_draw_planet(x, y)) {
                int color = get_planet_color();
                if (color != -1) {
                    SetColor(color);
                    cout << "O";
                    SetColor(7);
                } else {
                    cout << " ";
                }
            }
            // Draws empty space
            else {
                cout << " ";
            }
        }
        for (int s = 0; s < spacing; s++) {
            cout << " ";
        }

        // Stats panel
        if (y < stats_count) {
            SetColor(14);
            cout << stats_lines[y];
            SetColor(7);
        }

        cout << endl;
    }
}

// game logic  and event functions
void check_event(int &fuel, int &credits, string stats[], int game_width, int height)
{    
    if(steps == 100)
    {
        SetColor(3);    
        Beep(500, 500);    
        cout<<"REACHED MARS"<<endl;

        Sleep(5000);
        system("pause");

        SetColor(7);    
        trading_menu();
        steps += 1;
        area = "Mars";
        stats[5] = "Welcome to Mars!";
        Sleep(2000);
    }
    else if(steps == 200)
    {
        SetColor(3);      
        cout<<"REACHED JUPITER"<<endl;
        Sleep(500);
        system("pause");
        SetColor(7); 
        trading_menu();
        steps += 1;
        area = "Jupiter";
        stats[5] = "Welcome to Jupiter!";
        Sleep(2000);
    }
    else if(steps == 300)
    {
        SetColor(3);      
        cout<<"REACHED SATURN"<<endl;
        Sleep(500);
        system("pause");
        SetColor(7); 
        trading_menu();
        steps += 1;
        area = "Saturn";
        stats[5] = "Welcome to Saturn!";
        Sleep(2000);
    }
    else if(steps == 400)
    {
        SetColor(3); 
        Sleep(500);
        system("pause");
        cout<<"REACHED URANUS"<<endl;
        SetColor(7); 
        trading_menu();
        steps +=1;
        area = "Uranus";
        stats[5] = "Welcome to Uranus!";
        Sleep(2000);
    }
    
    // Random events every 70-80 steps
    if (steps >= next_event_at && steps > 0) {
        int event = rand() % 5;  
        
        switch(event) {
            case 0:  
                fuel += 50;
                stats[5] = "EVENT: Fuel pod found! +50";
                Beep(600, 200);
                break;
                
            case 1:  
                fuel -= 30;
                if(fuel < 0) fuel = 0;
                stats[5] = "EVENT: Asteroid hit! -30 fuel";
                Beep(200, 300);
                break;
                
            case 2:  
                credits += 150;
                stats[5] = "EVENT: Space loot! +150 credits";
                Beep(800, 200);
                break;
                
            case 3:  
                credits -= 75;
                if (credits < 0) credits = 0;
                stats[5] = "EVENT: Pirates attacked! -75 credits";
                Beep(150, 400);
                break;
                
            case 4:  
                fuel += 80;
                stats[5] = "EVENT: Space station! +80 fuel";
                Beep(700, 300);
                break;
             case 5:  
                fuel -= 50;
                if(fuel < 0) fuel = 0;
                stats[5] = "EVENT: Solar flare! -50 fuel";
                Beep(300, 250);
                Beep(250, 250);
                break;
                
            case 6:  
                credits += 200;
                fuel -= 20;
                if(fuel < 0) fuel = 0;
                stats[5] = "EVENT: Rescued ship! +200cr -20fuel";
                Beep(900, 150);
                Beep(1000, 150);
                break;
                
            case 7:  
                {
                    int gamble = rand() % 2;
                    if(gamble == 0) {
                        credits += 300;
                        stats[5] = "EVENT: Smuggler deal success! +300cr";
                        Beep(850, 200);
                    } else {
                        credits -= 100;
                        if(credits < 0) credits = 0;
                        stats[5] = "EVENT: Smuggler scammed you! -100cr";
                        Beep(150, 300);
                    }
                }
                break;
                
            case 8:  
                fuel -= 40;
                if(fuel < 0) fuel = 0;
                stats[5] = "EVENT: Nebula cloud passage! -40fuel";
                Beep(400, 300);
                break;
                
            case 9:  
                credits += 100;
                stats[5] = "EVENT: Found abandoned cargo! +100cr";
                Beep(750, 250);
                break;
                
            case 10:  
                fuel -= 60;
                credits -= 50;
                if(fuel < 0) fuel = 0;
                if(credits < 0) credits = 0;
                stats[5] = "EVENT: Meteor shower! -60fuel -50cr";
                Beep(200, 200);
                Beep(180, 200);
                Beep(160, 200);
                break;
                
            case 11:  
                credits += 125;
                fuel += 30;
                stats[5] = "EVENT: Traders met! +125cr +30fuel";
                Beep(650, 200);
                Beep(700, 200);
                break;
                
            case 12:  
                fuel += 120;
                stats[5] = "EVENT: Wormhole energy! +120 fuel";
                Beep(500, 150);
                Beep(600, 150);
                Beep(700, 150);
                break;
                
            case 13: 
                fuel -= 45;
                if(fuel < 0) fuel = 0;
                stats[5] = "EVENT: Engine malfunction! -45 fuel";
                Beep(250, 350);
                break;
                
            case 14:  
                credits += 500;
                stats[5] = "EVENT: TREASURE FOUND! +500 credits!";
                Beep(1000, 150);
                Beep(1100, 150);
                Beep(1200, 150);
                Beep(1300, 200);
                break;
 
        }
        
        // Set next event 70-80 steps later
        next_event_at = steps + 70 + (rand() % 11);
        Sleep(2000);  
    }
}


void space_trader_logic()
{
    bool game_running = true;
    int jet_x = 5;
    int fuel = 300;
    int credits = 500;
    int game_width = 50;      
    int height = 10;
    
    srand(time(0)); 
    steps = 0;
    next_event_at = 70 + (rand() % 11);

    ShowConsoleCursor(false);

    string stats[10];
    stats[0] = "=== STATS ===          ";
    stats[1] = "Fuel: "+ to_string(fuel)+"          ";
    stats[2] = "Credits: " + to_string(credits)+"          ";
    stats[3] = "Cargo: " + to_string(cargo_used) + "/" + to_string(cargo_capacity)+"          ";
    stats[4] = "Area: " +area+"          ";
    stats[5] = "                    ";
    stats[6] = "steps: " + to_string(steps)+"          ";
    stats[7] = "A/D - Move         ";
    stats[8] = "S-Save          ";
    stats[9] = "ESC - Pause          ";

    cout << "loading assets...." << endl;

    //load game
    cout<<"do you want to load previous save? (y/n): ";
    char load_choice;
    cin>>load_choice;
    if(load_choice == 'y' || load_choice == 'Y'){
        if(load_game(jet_x, fuel, credits, steps, cargo_used, area)){
            update_cargo();
        }
    }

    system("pause");
    system("cls");
    cout<<"\n\n\n\n\n\n\t\t\t\t\t";

    slow_scroller("WELCOME TO SPACE TRADER");
    
    music_playing = true;
    CreateThread(NULL, 0, magical_space_tune, NULL, 0, NULL);
    
    system("cls");

    while (game_running)
    {
        ClearScreenNoFlicker(); 
        // Update stats
        stats[6] = "steps: " + to_string(steps)+"          ";
        stats[2] = "Credits: " + to_string(credits)+"          ";
        stats[1] = "Fuel: " + to_string(fuel)+"          ";
        stats[4] = "Area: " +area+"          ";
        stats[3] = "Cargo: " + to_string(cargo_used) + "/" + to_string(cargo_capacity)+"          ";
        draw_game_and_stats(jet_x, game_width, height, stats, 10);
        //checks
        if (fuel == 0) {
            SetColor(4); 
            stats[5] = "OUT OF FUEL!";
            SetColor(7); 
            slow_scroller("GAME OVER! You ran out of fuel.");
            game_running = false;
            break;

        }

        // Input handling
        if (_kbhit()) {
        char key3 = _getch();

        if (key3 == 'a' || key3 == 'A') {
            if (fuel > 0) {
                rocket_engine_sound();
                jet_x--;
                steps += 1;
                if (jet_x <= 1) {
                    jet_x = game_width - 5;
                }
                fuel--;
            }
        }
        else if (key3 == 'd' || key3 == 'D') {
            if (fuel > 0) {
                rocket_engine_sound();
                jet_x++;
                steps += 1;
                if (jet_x >= game_width - 4) {
                    jet_x = 1;
                }
                fuel--;
            }
        }

        else if (key3 == 's' || key3 == 'S') {
            save_game(jet_x, fuel, credits, steps, cargo_used, area);
        }

        else if (key3 == 27) 
        {   
            music_playing = false;
            game_running = false;
        }
        //to prevent lag
        while (_kbhit())
        {
            _getch();
        }
        
        check_event(fuel, credits, stats, game_width, height);
        

    }
           
        
    }
}


//trading menu
void trading_menu()
{   
    bool trade_running = true;
    while(trade_running){
        system("cls");
        cout << "===================================" << endl;
        cout << "      TRADING POST - " << area << endl;
        cout << "===================================" << endl;
        cout << "Credits: " << credits << endl;
        cout << "Cargo: " << cargo_used << "/" << cargo_capacity << endl;
        cout << "-----------------------------------" << endl;
        cout << "1. Buy Goods" << endl;
        cout << "2. Sell Goods" << endl;
        cout << "3. View Market Prices" << endl;
        cout << "4. Back to Game" << endl;
        cout << "===================================" << endl;
        
        char key2 = _getch();
        
        switch(key2)
        {
            case '1':
                buy_goods();
                break;
            case '2':
                sell_goods();
                break;
            case '3':
                view_market_prices();
                break;
            case '4':
                trade_running = false;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                Sleep(1000);
                break;
        }
    }
    
}


// View Market Prices

void view_market_prices() {
    system("cls");
    cout << "===================================" << endl;
    cout << "    MARKET PRICES - " << area << endl;
    cout << "===================================" << endl;
    cout << "Item             Base    Current   Stock" << endl;
    cout << "-----------------------------------" << endl;
    
    for (int i = 0; i < 5; i++) {
        int current_price = get_current_price(i);
        cout << i + 1 << ". ";
        cout.width(15);
        cout << left << items[i].name;
        cout << items[i].base_price << "cr";
        cout << "   " << current_price << "cr";
        cout << "    " << items[i].quantity_owned << endl;
    }
    
    cout << "\n-----------------------------------" << endl;
    cout << "Cargo: " << cargo_used << "/" << cargo_capacity << endl;
    cout << "Credits: " << credits << endl;
    cout << "\nPress any key to return..." << endl;
    _getch();
}

// Buy Goods
void buy_goods() {
    bool buying = true;
    
    while (buying) {
        system("cls");
        cout << "===================================" << endl;
        cout << "      BUY GOODS - " << area << endl;
        cout << "===================================" << endl;
        cout << "Credits: " << credits << "  |  Cargo: " << cargo_used << "/" << cargo_capacity << endl;
        cout << "-----------------------------------" << endl;
        
        for (int i = 0; i < 5; i++) {
            int current_price = get_current_price(i);
            cout << i + 1 << ". " << items[i].name 
                 << " - " << current_price << " credits" << endl;
        }
        
        cout << "\n6. Back to Trading Menu" << endl;
        cout << "===================================" << endl;
        cout << "Select item to buy (1-6): ";
        
        char choice = _getch();
        
        if (choice >= '1' && choice <= '5') {
            int item_idx = choice - '1';
            int price = get_current_price(item_idx);
            
            system("cls");
            cout << "Buying: " << items[item_idx].name << endl;
            cout << "Price: " << price << " credits each" << endl;
            cout << "You have: " << credits << " credits" << endl;
            cout << "Cargo space: " << (cargo_capacity - cargo_used) << " remaining" << endl;
            cout << "\nHow many? (0 to cancel): ";
            
            int quantity;
            cin >> quantity;
            
            if (quantity > 0) {
                int total_cost = price * quantity;
                int cargo_space = cargo_capacity - cargo_used;
                
                // Check if player has enough money
                if (total_cost > credits) {
                    cout << "\nNot enough credits! Need " << total_cost 
                         << " but only have " << credits << endl;
                    Sleep(2000);
                }
                // Check if enough cargo space
                else if (quantity > cargo_space) {
                    cout << "\nNot enough cargo space! Only " << cargo_space 
                         << " slots available." << endl;
                    Sleep(2000);
                }
                else {
                    credits -= total_cost;
                    items[item_idx].quantity_owned += quantity;
                    update_cargo();
                    
                    cout << "\n you  Purchased " << quantity << "x " 
                         << items[item_idx].name << " for " << total_cost 
                         << " credits!" << endl;
                    if (audio_on) Beep(800, 200);
                    Sleep(1500);
                }
            }
        }
        else if (choice == '6') {
            buying = false;
        }
    }
}

// Sell Goods
void sell_goods() {
    bool selling = true;
    
    while (selling) {
        system("cls");
        cout << "===================================" << endl;
        cout << "      SELL GOODS - " << area << endl;
        cout << "===================================" << endl;
        cout << "Credits: " << credits << "  |  Cargo: " << cargo_used << "/" << cargo_capacity << endl;
        cout << "-----------------------------------" << endl;
        
        for (int i = 0; i < 5; i++) {
            int current_price = get_current_price(i);
            cout << i + 1 << ". " << items[i].name 
                 << " - " << current_price << " credits (Owned: " 
                 << items[i].quantity_owned << ")" << endl;
        }
        
        cout << "\n6. Back to Trading Menu" << endl;
        cout << "===================================" << endl;
        cout << "Select item to sell (1-6): ";
        
        char choice = _getch();
        
        if (choice >= '1' && choice <= '5') {
            int item_idx = choice - '1';
            
            if (items[item_idx].quantity_owned == 0) {
                cout << "\nYou don't own any " << items[item_idx].name << "!" << endl;
                Sleep(1500);
                continue;
            }
            
            int price = get_current_price(item_idx);
            
            system("cls");
            cout << "Selling: " << items[item_idx].name << endl;
            cout << "Price: " << price << " credits each" << endl;
            cout << "You own: " << items[item_idx].quantity_owned << endl;
            cout << "\nHow many? (0 to cancel): ";
            
            int quantity;
            cin >> quantity;
            
            if (quantity > 0) {
                if (quantity > items[item_idx].quantity_owned) {
                    cout << "\nYou only have " << items[item_idx].quantity_owned << "!" << endl;
                    Sleep(2000);
                }
                else {
                    int total_earned = price * quantity;
                    credits += total_earned;
                    items[item_idx].quantity_owned -= quantity;
                    update_cargo();
                    
                    cout << "\n✓ Sold " << quantity << "x " 
                         << items[item_idx].name << " for " << total_earned 
                         << " credits!" << endl;
                    if (audio_on) Beep(600, 200);
                    Sleep(1500);
                }
            }
        }
        else if (choice == '6') {
            selling = false;
        }
    }
}

//game saving mechanics
void save_game(int jet_x, int fuel, int credits, int steps, int cargo, string area) {
    ofstream saveFile("savegame.txt");
    
    if (saveFile.is_open()) {
        saveFile << jet_x << endl;
        saveFile << fuel << endl;
        saveFile << credits << endl;
        saveFile << steps << endl;
        saveFile << cargo << endl;
        saveFile << area << endl;
        saveFile.close();
        
        SetColor(10);
        cout << "Game saved successfully!" << endl;
        SetColor(7);
        Beep(800, 200);
    } else {
        SetColor(12);
        cout << "Error: Could not save game!" << endl;
        SetColor(7);
    }
}

bool load_game(int &jet_x, int &fuel, int &credits, int &steps, int &cargo, string &area) {
    ifstream loadFile("savegame.txt");
    
    if (loadFile.is_open()) {
        loadFile >> jet_x;
        loadFile >> fuel;
        loadFile >> credits;
        loadFile >> steps;
        loadFile >> cargo;
        loadFile.ignore(); 
        getline(loadFile, area);
        loadFile.close();
        
        SetColor(10);
        cout << "Game loaded successfully!" << endl;
        SetColor(7);
        Beep(800, 200);
        Sleep(1000);
        return true;
    } else {
        SetColor(14);
        cout << "No save file found. Starting new game..." << endl;
        SetColor(7);
        Sleep(1000);
        return false;
    }
}

