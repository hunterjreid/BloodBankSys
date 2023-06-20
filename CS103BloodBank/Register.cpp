/*
    BloodBank Group Project
    CS103BloodBank.cpp : Register.cpp
*/

//Prerequisites
#include "Header.h"
#include "Config.c"
using namespace std;

//Main Func
void mainRegister()
{
    //Function, pretty basic compared to the others.
main_register:
    //Everything to do with the main Registeration sys is below.
    clearConsole();
    line();
    cout << "\n\t\t\tSignup\n";
    line();

    char decision;
    cout << "\n\n1. New Account";
    cout << "\n2. Back to Main Menu";
    //Gather input for user.
    cout << "\n\n\nPlease Enter your Choice : ";
    cin >> decision;

    switch (decision) {
    case '1':
        clearConsole();
        Register(1);
        break;
    case '2':
        clearConsole();
        mainMenu();
        break;
    default:
        //Re-prompt user after invalid input .
        clearConsole();
        goto main_register;
    }
}
// Register Func
void Register(int path) {
    //added paths for future proofing.
    if (path == 1) {
        fstream file;
        file.close();
        member member;
        file.open("DB.dat", ios::out | ios::app | ios::binary);
        new_member(member);
        file.write(reinterpret_cast<char*>(&member), sizeof(member));
        //Send user back to main menu
        clearConsole();
        file.close();
        cout << "New Account Created, Please Sign In.\n\n";
        mainMenu();
    }
}
/*

New Member is a func which grabs heaps of inputs with cin.getline 
& inserts them into a struct member ready for file insertion.

*/
void new_member(struct member& member) {
    //gather inputs
    cin.ignore();
    line();
    cout << "\n\t\t\tSignup\n";
    line();
    // Gen ID for user.
    srand((unsigned)time(0));
    int id = rand() % 10000000 + 1000000000;
    // for identification
    string id_string = to_string(id); char opt;
    strcpy_s(member.id, id_string.c_str());
    cout << "\n\n\tFirst Name : ";
    cin.getline(member.f_name, 50);
    cout << "\tLast Name : ";
    cin.getline(member.l_name, 50);
    cout << "\tEmail : ";
    cin.getline(member.email, 50);
donor_question:
    cout << "\n\tAre you considering being a Donor\n\tby signing up Today? (y/n): ";
    cin >> opt;
    if (tolower(opt) == 'y') {
        string temp = "DONOR";
        strcpy_s(member.type, temp.c_str());
        goto continued;
    }
    else if (tolower(opt) == 'n') {
        goto recipient_question;
    }
    else {
        goto donor_question;
    }
recipient_question:
    cout << "\n\tAre you considering being a Recipient\n\tof blood by signing up Today? (y/n): ";
    cin >> opt;
    if (tolower(opt) == 'y') {
        string temp = "RECIPIENT";
        strcpy_s(member.type, temp.c_str());
    }
    else if (tolower(opt) == 'n') {
        string temp = "NEITHER";
        strcpy_s(member.type, temp.c_str());
        goto continued;
    }
    else {
        goto recipient_question;    
    }
continued:
    cin.ignore();
    cout << "\n\tAddress Line 1: ";
    cin.getline(member.address_1, 50);
    cout << "\tAddress Line 2: ";
    cin.getline(member.address_2, 50);
    cout << "\tMobile : ";
    cin.getline(member.phone, 17);
blood_question:
    cout << "\n\tDo you know your Blood\n\ttype? (y/n): ";
    cin >> opt;
    if (tolower(opt) == 'y') {
        string _bloodtype;
        string _neededtype;
    invalid_blood:
        cout << "\tBlood Type : ";
        cin.ignore();
        cin >> _bloodtype;
        //Smart transform
        transform(_bloodtype.begin(), _bloodtype.end(), _bloodtype.begin(), toupper);
        // All these are offical arrcording to https://www.nhs.uk/conditions/blood-groups/#:~:text=There%20are%204%20main%20blood,there%20are%208%20blood%20groups.
        if (_bloodtype == "A+") {
            _neededtype = "A+, A-, O+, O-";
        }
        else if (_bloodtype == "A-") {
            _neededtype = "A-, O-";
        }
        else if (_bloodtype == "B+") {
            _neededtype = "B+, B-, O+, O-";
        }
        else if (_bloodtype == "B-") {
            _neededtype = "B-, O-";
        }
        else if (_bloodtype == "AB+") {
            _neededtype = "Universal";
        }
        else if (_bloodtype == "AB-") {
            _neededtype = "AB-, A-, B-, O-";
        }
        else if (_bloodtype == "O+") {
            _neededtype = "O+, O-";
        }
        else if (_bloodtype == "O-") {
            _neededtype = "O-";
        }
        else {
            cout << "\tThis is not a Valid Blood type,\n";
            goto invalid_blood;
        }
        strcpy_s(member.blood_needed, _neededtype.c_str());
        strcpy_s(member.blood_type, _bloodtype.c_str());
        cin.ignore();
    }
    else if (tolower(opt) == 'n') {
        string temp = "UNKNOWN";
        strcpy_s(member.blood_type, temp.c_str());
        strcpy_s(member.blood_needed, temp.c_str());
        cin.ignore();
    }
    else {
        cin.ignore();
        goto blood_question;
    }
    cout << "\n\tEnter Password : ";
    cin.getline(member.password, 50);
    //Account created after this point.
    cout << "\n\tACCOUNT ID: " << id << "\n\t";
    system("PAUSE");
}