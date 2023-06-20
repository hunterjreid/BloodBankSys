/*
    BloodBank Group Project
    CS103BloodBank.cpp : Admin.cpp
*/

//Prerequisites
#include "Header.h"
#include "Config.c"
using namespace std;

//Main Func.
void Admin() {
    clearConsole();
reset:
    line();
    cout << "\n\t\t\tADMINISTRATOR PANEL\n";
    line();
    char decision;
    //Query user.
    cout << "\n\n1. View All Registered Users";
    cout << "\n2. View Specific User";
    cout << "\n3. View all recipient records";
    cout << "\n4. View all donor records";
    cout << "\n5. Filter records by blood type";
    cout << "\n6. Filter records by location";
    cout << "\n7. Logout to Main Menu";
    //Gather input for user.
    cout << "\n\nPlease Enter your Choice : ";
    cin >> decision;
    member member;
    switch (decision) {
        //Each path has seperate func.
    case '1':
        view_all_record(member);
        cout << endl;
        system("PAUSE");
        break;
    case '2':
        view_single_record();
        break;
    case '3':
        view_all_record_recipient(member);
        break;
    case '4':
        view_all_record_donor(member);
        break;
    case '5':
        donors_by_blood_type();
        break;
    case '6':
        donors_by_blood_type_location();
        break;
    case '7':
        clearConsole();
        mainMenu();
        break;
    default:
        //Re-prompt user after invalid input .
        clearConsole();
        goto reset;
    }
}
//End Main Func. start view donors by blood type function
void donors_by_blood_type() {
    //Func for viewing all records.
    clearConsole();
    char required[50] = { "NULL" }; char id[11] = { "0" };
    fstream file; string identification; member profile; member temp;
    
    line();
    cout << "\n\t\t\tSearch User\n";
    line();
    cout << "\n\n\tEnter blood type : ";
    cin >> identification;
    //Manipulate vals
    transform(identification.begin(), identification.end(), identification.begin(), ::toupper);
    bool flag = false;
    strcpy_s(temp.blood_type, identification.c_str());
    //Search File.
    file.open("DB.dat", ios::in | ios::binary); // Strictly read
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&profile), sizeof(profile))) {
            //Match between Blood types.
            if (strcmp(temp.blood_type, profile.blood_type) == 0) {
                flag = true; cout << "\n"; line();
               
                cout << "\n\n\t" << profile.f_name << " " << profile.l_name << ". #" << profile.id;
                cout << "\n\n\tBlood Type : " << profile.blood_type << ", can recive blood(s) " << profile.blood_needed;
                cout << "\n\tEmail : " << profile.email;
                cout << "\n\tStatus : " << profile.type;
                cout << "\n\n\tEMERGENCY PHONE CONTACT : " << profile.phone << "\n\n"; line(); cout << "\n\n\t";
            }
        }
    }
    else {
        cout << "ERROR: OPEN FILE"; // Error handling. 
    }
    if (!flag) {
        cout << "\n\tNothing on file ;( \n\n";
        line();
        cout << "\n\n\t";
    }
    system("PAUSE"); clearConsole(); file.close();
    // Return
    Admin();
}
// view donors by location function
void donors_by_blood_type_location() {
    //Func for viewing all records.
    clearConsole();
    fstream file;
    member profile, temp;
    string identification;

    char required[50] = { "NULL" }; char id[11] = { "0" }; bool flag = false;
    line();
    cout << "\n\t\t\tSearch User\n";
    line();
    cout << "\n\n\tEnter Location : ";
    cin >> identification;
    transform(identification.begin(), identification.end(), identification.begin(), ::toupper);
    strcpy_s(temp.address_1, identification.c_str());

    //Search File. Strictly read
    file.open("DB.dat", ios::in | ios::binary);
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&profile), sizeof(profile))) {
            //If either address_1 or address_2 matches then Return Result.
            if ((strcmp(temp.address_1, profile.address_1) == 0) || (strcmp(temp.address_1, profile.address_2) == 0)) {
                flag = true; cout << "\n"; line();
                //Display in module.
                cout << "\n\n\t" << profile.f_name << " " << profile.l_name << ". #" << profile.id;
                cout << "\n\n\tBlood Type : " << profile.blood_type << ", can recive blood(s) " << profile.blood_needed;
                cout << "\n\tEmail : " << profile.email;
                cout << "\n\tStatus : " << profile.type;
                cout << "\n\n\tEMERGENCY PHONE CONTACT : " << profile.phone << "\n\n"; line(); cout << "\n\n\t";
            }
        }
    }
    else {
        cout << "ERROR: OPEN FILE"; // For the Errors.
    }
    if (!flag) {
        cout << "\n\tNothing on file ;( \n\n";
        line();
        cout << "\n\n\t";
    }
    system("PAUSE"); clearConsole(); file.close(); Admin();
}
// view record single
void view_single_record() {
    //Func for viewing all records.
    clearConsole(); fstream file; member profile; member temp; string identification;
    char email[50] = { "NULL" };char id[11] = { "0" };
    //Display
    line();
    cout << "\n\t\t\tSearch User\n";
    line();
    cout << "\n\n\tEmail or ID Number : ";
    cin >> identification;
    if (all_of(identification.begin(), identification.end(), ::isdigit)) {
        //The string is only numbers.
        strcpy_s(temp.id, identification.c_str());
    } else {
        //assume email..
        strcpy_s(temp.email, identification.c_str());
    }
    //Start file open func
    bool flag = false;
    file.open("DB.dat", ios::in | ios::binary); // Strictly read
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&profile), sizeof(profile))) {



             if ((strcmp(temp.email, profile.email) == 0) || (strcmp(temp.id, profile.id) == 0)) {
                 flag = true; cout << "\n"; line();
                 
         
                 cout << "\n\n\t" << profile.f_name << " " << profile.l_name << ". #" << profile.id;
                 cout << "\n\n\tBlood Type : " << profile.blood_type << ", can recive blood(s) " << profile.blood_needed;

                 
                 cout << "\n\tEmail : " << profile.email;
                 cout << "\n\tStatus : " << profile.type;


                 cout << "\n\n\tAddress Line 1 : " << profile.address_1;
                 cout << "\n\tAddress Line 2 : " << profile.address_2;
                 cout << "\n\n\tEMERGENCY PHONE CONTACT : " << profile.phone << "\n\n";
                 line();
                 cout << "\n\n\t";
                 system("PAUSE");


                }

        }
    }
    else {
        cout << "ERROR: OPEN FILE";
    }
    if (!flag) {
        cout << "\n\tNothing on file ;( \n\n";
        line();
        cout << "\n\n\t";
        system("PAUSE");
    }


    file.close();
    Admin();

}
// view all record recipient
void view_all_record_recipient(struct member&) {
    // Func for viewing all records.
    clearConsole();
    fstream file;
    string identification = "RECIPIENT"; member member, temp;
    strcpy_s(temp.type, identification.c_str());

    //Open file in read
    file.open("DB.dat", ios::in | ios::binary); // Strictly read
    int counter = 0;
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&member), sizeof(member))) {
            if (strcmp(temp.type, member.type) == 0) {
                counter++;
                cout << "\n[Line: " << counter << "]-----------------------------\n\t";
                cout << member.f_name << " " << member.l_name << ", ID: " << member.id;
                cout << "\n\t@: " << member.email;
                cout << "\n\tTYPE: " << member.type;
                cout << "\n\tB-TYPE   : " << member.blood_type;
                cout << "\n\tBlood NEEDED : " << member.blood_needed;
                cout << "\n[Line: " << counter << "]-----------------------------\n\n\n";
            }
        }
    }
    else {
        cout << "ERROR: OPEN FILE";
    }
    if (counter == 0) {
        //No users
        cout << "---------------------------------------\n\tNo users on File.\n---------------------------------------\n\n\t";
    }
    else {
        //End
        cout << "---------------------------------------\n\tThat's all we have on File.\n---------------------------------------\n\n\t";
    }
    file.close(); system("PAUSE"); Admin();
}
// view all record SAME as recpient but donor
void view_all_record_donor(struct member&) {
    // Func for viewing all records.
    clearConsole();
    fstream file;
    string identification = "DONOR"; member member, temp;
    strcpy_s(temp.type, identification.c_str());

    //Open file in read
    file.open("DB.dat", ios::in | ios::binary); // Strictly read
    int counter = 0;
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&member), sizeof(member))) {
            if (strcmp(temp.type, member.type) == 0) {
                counter++;
                cout << "\n[Line: " << counter << "]-----------------------------\n\t";
                cout << member.f_name << " " << member.l_name << ", ID: " << member.id;
                cout << "\n\t@: " << member.email;
                cout << "\n\tTYPE: " << member.type;
                cout << "\n\tB-TYPE   : " << member.blood_type;
                cout << "\n\tBlood NEEDED : " << member.blood_needed;
                cout << "\n[Line: " << counter << "]-----------------------------\n\n\n";
            }
        }
    }
    else {
        cout << "ERROR: OPEN FILE";
    }
    if (counter == 0) {
        //No users
        cout << "---------------------------------------\n\tNo users on File.\n---------------------------------------\n\n\t";
    }
    else {
        //End
        cout << "---------------------------------------\n\tThat's all we have on File.\n---------------------------------------\n\n\t";
    }
    file.close(); system("PAUSE"); Admin();
}
// display all records
void view_all_record(struct member&) {
    //Func for viewing all records.
    clearConsole(); fstream file; member member; int counter = 0;
    file.open("DB.dat", ios::in | ios::binary); // Strictly read
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&member), sizeof(member))) {
            counter++;
            cout << "\n[Line: " << counter << "]-----------------------------\n\t";
            cout << member.f_name << " " << member.l_name << ", ID: " << member.id;
            cout << "\n\t@: " << member.email;
            cout << "\n\tTYPE: " << member.type;
            cout << "\n\tB-TYPE   : " << member.blood_type;
            cout << "\n\tBlood NEEDED : " << member.blood_needed;
            cout << "\n[Line: " << counter << "]-----------------------------\n\n\n";
        }
    }
    else {
        cout << "ERROR: OPEN FILE";
    }
    if (counter == 0) {
        cout << "---------------------------------------\n\tNo users on File.\n---------------------------------------\n\n\t";
    }
    else {
        cout << "---------------------------------------\n\tThat's all we have on File.\n---------------------------------------\n\n\t";
    }
    file.close(); system("PAUSE"); Admin();
}