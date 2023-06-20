/*
    BloodBank Group Project
    CS103BloodBank.cpp : Login.cpp
*/

//Prerequisites
#include "Header.h"
#include "Config.c"
using namespace std;

//Main Func.
void mainLogin()
{
// Main loop
main_login:
    clearConsole();
    //header
    line();
    cout << "\n\t\t\tLogin\n";
    line();
    char decision;
    cout << "\n\n1. General";
    cout << "\n2. Admin";
    cout << "\n3. Back to Main Menu";
    //Gather input for user.
    cout << "\n\n\nPlease Enter your Choice : ";
    cin >> decision;
    switch (decision) {
    case '1':
        //General
        clearConsole();
        login_select_num(1);
        break;
    case '2':
        //Admin
        clearConsole();
        login_select_num(2);
        break;
    case '3':
        //Main Mneu
        clearConsole();
        mainMenu();
        break;
    default:
        //Re-prompt user after invalid input .
        clearConsole();
        goto main_login;
    }
}

int LoginAttempt = 0;
//general login function path:1
void login_select_num(int x)
{
    //Header.
    string loginTypes[] = { "", "Admin " };
    int retry_counter = 0;
    line();cout << "\n\t\t\t" << loginTypes[x - 1] << "Login\n";line();
    //Ethier show Login trys or cin.ingore to stop it Escaping the first field.
    if (LoginAttempt == MAX_LOGIN) {
        // KICK FUNC
        clearConsole();
        LoginAttempt = 0; // Reset 4 user
        cout << "Bad Login, please ensure you have Correct Credidentals. \n\n";
        mainMenu();
    } else if (LoginAttempt != 0) {
        // WARNING FUNC
        cout << "\n\n\t( " << LoginAttempt << " / " << MAX_LOGIN << " ) ";
    } else if (LoginAttempt == 0) {
        // Ignore FUNC
        cin.ignore();
    }
    if (x == 1) {
        //Login for Patient
        char email[50] = "", pass[50] = "";
        // Gather Inputs
        cout << "\n\n\tEMAIL\t  :   ";
        cin.getline(email, 50);
        cout << "\tPASSWORD  :   ";
        cin.getline(pass, 50);
        // Match Inputs
        find_member(email, pass);
        system("PAUSE");
    }
    else if (x == 2) {
        //Admin Login.
        char login_id[50] = "", pass[50] = "";
        // Gather Inputs
        cout << "\n\n\tADMIN ID  :   ";
        cin.getline(login_id, 50);
        cout << "\tPASSWORD  :   ";
        cin.getline(pass, 50);
        // Match Inputs
        admin_login(login_id, pass);
        system("PAUSE");
    }
}
//general login function path:2
void admin_login(char login_id[50], char password[50]) {
    //if matches login details.
    if ((strcmp(ADMIN_LOGIN_ID, login_id) == 0) && (strcmp(ADMIN_PASSWORD, password) == 0)) {
        cout << "\n\tLOGIN SUCCESSFUL\n\t";
        system("PAUSE");
        LoginAttempt = 0;
        Admin();
    }
    else {
        cout << "\n\tLOGIN WRONG\n\t";
        system("PAUSE");
        LoginAttempt++;
        clearConsole();
        login_select_num(2);
    }
}
//loading profile Function. Runs by default.
void find_member(char email[50], char password[50]) {
    //find record func
    fstream file; member member; bool flag = false;
    file.open("DB.dat", ios::in | ios::binary);

    if (file.is_open()) 
    {
        while (!file.eof()) 
        {
            while (file.read(reinterpret_cast<char*>(&member), sizeof(member)))
            {                
                if ((strcmp(email, member.email) == 0) && (strcmp(password, member.password) == 0)) {
                    // temporary success statements
                    cout << "\n\tLOGIN SUCCESSFUL\n\t";
                    flag = true; LoginAttempt = 0;
                    system("PAUSE"); clearConsole();
                    mainProfile(member.email); return;
                }
            }
        }
    }
    else {
        //Should be impossible but im not sure.
        cout << "Error opening File."; // Error handling
    }
    //BAD
    if (!flag) {
        //Bad Login
        cout << "\n\tLOGIN WRONG\n\t";
        system("PAUSE");
        LoginAttempt++; clearConsole(); login_select_num(1);
    }
    //Close file for a good habit.
    file.close();
}