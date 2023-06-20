/*
    BloodBank Group Project
    CS103BloodBank.cpp : This file contains the 'main' function
    Credits: Paia M, Hunter R
    https://github.com/IMAG0D/CS103BloodBank
    http://animation.onlearn.co.nz/mod/assign/view.php?id=16615
    Started 12 June, finished 3 July
    Yoobee Colleges
*/

//Prerequisites
#include "Header.h"
#include "Config.c"
using namespace std;

//Main Func.
int main()
{
    mainMenu();
    return 0;
}

// Function mainMenu loop
void mainMenu() {
main_menu:
    //Everything to do with the Main Menu is below.
    line();
    cout << "\n\t\t\tCS103BloodBank.cpp\n";
    line();
    cout << "\n\t\t\tMain Menu\n";
    line();
    //Display.
    char decision;
    cout << "\n\n1. Login";
    cout << "\n2. Register";
    cout << "\n3. General Info";
    cout << "\n4. Exit";
    //Gather input for user.
    cout << "\n\n\nPlease Enter your Choice : ";
    cin >> decision;
    switch (decision) {
    case '1':
        mainLogin();
        break;
    case '2':
        mainRegister();
        break;
    case '3':
        infoScreen();
        break;
    case '4':
        break;

    default:
        //Re-prompt user after invalid input .
        clearConsole();
        goto main_menu;
    }
}

// fn to display info screen
void infoScreen()
{
    clearConsole();
    line();
    cout << "\n\t\t\tGeneral Information\n";
    line();
    cout << "\nBLOOD BANK SYSTEM v1.1\n\nlink: https://github.com/IMAG0D/CS103BloodBank \n\nInfo\n\nBloodBank Group Project\n'Spare only 15 minutes and save one life'\n\nSometimes we tend to forget how easy can be to help another human\nbeen but this quote manages to remind us. By highlighting the\nsimplicity of the process, the slogan has also the merit to\ncomfortand convince people that are afraid of donating blood to\ngive it a try.\n\nCredits: Paia M, Hunter R @ Yoobee Colleges - City Road Campus  \n\n\n";
    system("pause");
    clearConsole();
    mainMenu();
}

// fn to display a line
void line()
{
    for (int i = 0; i < 65; i++)
    {
        cout << LINE_CHAR;
    }
}

// fn to clear console
void clearConsole() {
    system("CLS");
}

/*
    Credits: Paia M, Hunter R
*/