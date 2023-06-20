/*
    BloodBank Group Project
    CS103BloodBank.cpp : Register.cpp
*/

//Prerequisites
#include "Header.h"
#include "Config.c"
using namespace std;

void Book_Appoiment(string);

//Main Func
string temp;
void mainProfile(string profile_email) {
    // Find user to see what opt too display to them.
    // dissect string and grab profile information
    temp = profile_email;
    member profile;
    strcpy_s(profile.email, temp.c_str());
    profile = define_Profile(profile.email);
    //profile display
    line(); char decision;
    cout << "\n\t\t"<< profile_email << "\n";
    line(); cout << "\n\t\tProfile Menu\n"; line();
    //Display correct options to user type.
    if ((strcmp("DONOR", profile.type) == 0)) {
        //Donor menu options.
        cout << "\n\n1. Find recpients who can receive your blood";
        cout << "\n2. Procedure to donate Info";
        cout << "\n3. Blood donation benefits info";
        cout << "\n4. Logout to Main Menu";
    }
    else if ((strcmp("RECIPIENT", profile.type) == 0)) {
        //Recipient menu options.
        cout << "\n\n1. Find donors by your needed blood type";
        cout << "\n2. Find donors by blood type";
        cout << "\n3. Find donors by location";
        cout << "\n4. Find contact details by name search";
        cout << "\n5. Book Appoiment";
        cout << "\n6. Logout to Main Menu";
    }
    else {
        //They are not reipient not donor.
        cout << "\n\n1. Procedure to donate Info";
        cout << "\n2. Logout to Main Menu";
    }
    //Gather input for user.
    cout << "\n\nPlease Enter your Choice : ";
    cin >> decision;
    /*
    
    Probaly the most confusing thing here this
    switch case if massive but it links a calling
    the function attached to the number they entered
    according to the table above

    */
    switch (decision) {
    case '1':
        //case1
        if (strcmp("DONOR", profile.type) == 0) {
            who_can_receive_your_blood(profile.blood_type);
        }
        else if ((strcmp("RECIPIENT", profile.type) == 0)) {
            view_record_by_blood(profile.blood_needed);
        }
        else {
            donate_Info(profile_email);
        }
        break;
    case '2':
        //case2
        if (strcmp("DONOR", profile.type) == 0) {
            donate_Info(profile_email);
        }
        else if ((strcmp("RECIPIENT", profile.type) == 0)) {
            donors_by_blood_type(profile_email);
        }
        else {
            clearConsole();
            mainMenu();
            break;
        }
    case '3':
        //case3
        if (strcmp("DONOR", profile.type) == 0) {
            donate_benefitsInfo(profile_email);
        }
        else if ((strcmp("RECIPIENT", profile.type) == 0)) {
            donors_by_blood_type_location(profile_email);
        }
        else {
            clearConsole();
            mainMenu();
            break;
        }
        break;
    case '4':
        //case4
        if (strcmp("RECIPIENT", profile.type) == 0) {
            name_search(profile_email);
        }
        else {
            clearConsole();
            mainMenu();
            break;
        }
        break;
    case '5':
        if (strcmp("RECIPIENT", profile.type) == 0) {
            Book_Appoiment(profile_email);
        }
        else {
            clearConsole();
            mainMenu();
            break;
        }
    default:
        clearConsole();
        mainProfile(profile_email);
    }
    //end switch
}
//load member details after login
member define_Profile(char email[50]) {
    //find record func
    fstream file; member empty{};
    file.open("DB.dat", ios::in | ios::binary);
    //start file open
    if (file.is_open())
    {
        while (!file.eof())
        {
            member member;
            while (file.read(reinterpret_cast<char*>(&member), sizeof(member)))
            {
                if (strcmp(email, member.email) == 0) {
                    return member; // this should always return something valid
                }
            }
        }
    }
    else {
        cout << "Error opening File."; // Error handling
    }
    //Close file for a good habit.
    file.close(); return empty;
} 
// Search name func
void name_search(string return_val) {
    //Func for viewing all records.
    clearConsole();
    fstream file;
    member profile; member temp;
    string identification;
    char email[50] = { "NULL" }; char id[11] = { "0" }; bool flag = false;
    line();
    cout << "\n\t\t\tSearch User\n";
    line();
    cout << "\n\n\tFirst Name or ID Number : ";
    cin >> identification;
    //set to either first name or id number
    strcpy_s(temp.f_name, identification.c_str());
    strcpy_s(temp.email, identification.c_str());
    file.open("DB.dat", ios::in | ios::binary); // Strictly read
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&profile), sizeof(profile))) {
            if ((strcmp(temp.f_name, profile.f_name) == 0) || (strcmp(temp.email, profile.email) == 0)) {
                flag = true; cout << "\n"; line();

                cout << "\n\n\t" << profile.f_name << " " << profile.l_name << ". #" << profile.id;
                cout << "\n\n\tBlood Type : " << profile.blood_type << ", can recive blood(s) " << profile.blood_needed;
                cout << "\n\tEmail : " << profile.email;
                cout << "\n\tStatus : " << profile.type;
                cout << "\n\n\tAddress Line 1 : " << profile.address_1;
                cout << "\n\tAddress Line 2 : " << profile.address_2;
                cout << "\n\n\tEMERGENCY PHONE CONTACT : " << profile.phone << "\n\n"; line(); cout << "\n\n\t";
            }
        }
    }
    else {
        cout << "ERROR: OPEN FILE"; // error handling
    }
    if (!flag) {
        cout << "\n\tNothing on file ;( \n\n";
        line();
        cout << "\n\n\t";
    }
    //return
    system("PAUSE"); clearConsole(); file.close(); mainProfile(return_val);
}
// People who can accept your blood func
void who_can_receive_your_blood(char blood[101]) {
    //Func for viewing all records.
    clearConsole(); fstream file; member member; int counter = 0;
    file.open("DB.dat", ios::in | ios::binary); // Strictly read
    cout << "\n\tYour Blood: " << blood << "\n";
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&member), sizeof(member))) {
            string m_t = member.blood_needed; string b_t = blood;
            if (m_t == "Universal") { m_t = b_t; }
            //If blood types match display information
            if (strstr(m_t.c_str(), b_t.c_str()))
            {
                counter++;
                cout << "\n[Line: " << counter << "]-----------------------------\n\t";
                cout << member.f_name << " " << member.l_name << ", ID: " << member.id;
                cout << "\n\tBlood Needed : " << member.blood_needed;
                cout << "\n\n\t@: " << member.email;
                cout << "\n\tPH: " << member.phone;
                cout << "\n[Line: " << counter << "]-----------------------------\n\n";

            }
        }
    }
    else {
        cout << "ERROR: OPEN FILE";
    }
    if (counter == 0) {
        // no user
        cout << "---------------------------------------\n\tNo users on File.\n---------------------------------------\n\n\t";
    }
    else {
        // end file
        cout << "---------------------------------------\n\tThat's all we have on File.\n\tYou can give \n\tblood to " << counter << " people. \n---------------------------------------\n\n\t";
    }
    system("pause"); clearConsole(); mainProfile(temp);
}
// Donors by location func
void donors_by_blood_type_location(string return_val) {
    //Func for viewing all records.
    clearConsole();
    fstream file; member profile, temp; string identification;
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
            if ((strcmp(temp.address_1, profile.address_1) == 0) || (strcmp(temp.address_1, profile.address_2) == 0)) {
                flag = true; cout << "\n"; line();
                //display if matching
                cout << "\n\n\t" << profile.f_name << " " << profile.l_name << ". #" << profile.id;
                cout << "\n\n\tBlood Type : " << profile.blood_type << ", can recive blood(s) " << profile.blood_needed;
                cout << "\n\tEmail : " << profile.email;
                cout << "\n\tStatus : " << profile.type;
                cout << "\n\n\tEMERGENCY PHONE CONTACT : " << profile.phone << "\n\n";line();cout << "\n\n\t";
            }
        }
    }
    else {
        cout << "ERROR: OPEN FILE"; // error
    }
    if (!flag) {
        cout << "\n\tNothing on file ;( \n\n";
        line();
        cout << "\n\n\t";

    }
    system("PAUSE");
    clearConsole();
    file.close();
    mainProfile(return_val);
}
// Donors by blood types func
void donors_by_blood_type(string return_val) {
    //Func for viewing all records.
    clearConsole(); fstream file; member profile; member temp; string identification;
    char required[50] = { "NULL" }; char id[11] = { "0" };
    // search user
    line();
    cout << "\n\t\t\tSearch User\n";
    line();
    cout << "\n\n\tEnter blood type : ";
    cin >> identification;
    transform(identification.begin(), identification.end(), identification.begin(), ::toupper);
    bool flag = false;
    strcpy_s(temp.blood_type, identification.c_str());
    //Search File.
    file.open("DB.dat", ios::in | ios::binary); // Strictly read
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&profile), sizeof(profile))) {
            if (strcmp(temp.blood_type, profile.blood_type) == 0) {
                flag = true;
                cout << "\n";
                line();
                cout << "\n\n\t" << profile.f_name << " " << profile.l_name << ". #" << profile.id;
                cout << "\n\n\tBlood Type : " << profile.blood_type << ", can recive blood(s) " << profile.blood_needed;
                cout << "\n\tEmail : " << profile.email;
                cout << "\n\tStatus : " << profile.type;
                cout << "\n\n\tEMERGENCY PHONE CONTACT : " << profile.phone << "\n\n";
                line();
                cout << "\n\n\t";
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

    }
    system("PAUSE");
    clearConsole();
    file.close();
    mainProfile(return_val);
}
// View record by blood func
void view_record_by_blood(char blood[101]) {
    //Func for viewing all records.
    clearConsole();
    fstream file; member member;
    file.open("DB.dat", ios::in | ios::binary); // Strictly read
    int counter = 0;
    cout << "\n\tBlood needed: \n\t" << blood << "\n";
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&member), sizeof(member))) {
            // for universal case.
            string m_t = member.blood_type;
            string b_t = blood;
            if (b_t == "Universal" && m_t != "UNKNOWN") { m_t = b_t; }
            //If blood types match
            if (strstr(b_t.c_str(), m_t.c_str()))
            {
                
                counter++; cout << "\n[Line: " << counter << "]-----------------------------\n\t";
                cout << member.f_name << " " << member.l_name << ", ID: " << member.id;
                cout << "\n\tB-TYPE   : " << member.blood_type;
                cout << "\n\n\t@: " << member.email;
                cout << "\n\tPH: " << member.phone;
                cout << "\n[Line: " << counter << "]-----------------------------\n\n";

            }
        }
    }
    else {
        cout << "ERROR: OPEN FILE";
    }
    if (counter == 0) {
        cout << "---------------------------------------\n\tNo users on File.\n---------------------------------------\n\n\t";
    }
    else {
        cout << "---------------------------------------\n\tThat's all we have on File.\n\tYou can recive from "<<counter<<" people. \n---------------------------------------\n\n\t";
    }
    //close file and return menu
    system("pause"); clearConsole(); mainProfile(temp);
}
// donte benefits
void donate_benefitsInfo(string email) {
    clearConsole();
    line();
    cout << "\n\t\t\tDonate Benefits\n";
    line();
    cout << "\n\nlink: https://github.com/IMAG0D/CS103BloodBank\n\nInfo  Info  Info  Info  Info  Info  Info  Info  Info  \nInfo  Info  Info  Info  Info  Info  Info  Info  Info  \nInfo  Info  Info  Info  Info  Info  Info  Info  Info  \n\n\n";
    system("pause");
    clearConsole();
    mainProfile(email);
}
// donte infomation screen
void donate_Info(string email) {
    clearConsole();
    line();
    cout << "\n\t\t\tDonate Information\n";
    line();
    cout << "\n\nlink: https://github.com/IMAG0D/CS103BloodBank\n\nInfo  Info  Info  Info  Info  Info  Info  Info  Info  \nInfo  Info  Info  Info  Info  Info  Info  Info  Info  \nInfo  Info  Info  Info  Info  Info  Info  Info  Info  \n\n\n";
    system("pause");
    clearConsole();
    mainProfile(email);
}
// book app func
void Book_Appoiment(string return_email) {
    //Func for viewing all records.
    clearConsole();
    fstream file;
    member profile; member temp;
    string identification;
    char email[50] = { "NULL" }; char id[11] = { "0" }; bool flag = false;
    line();
    cout << "\n\t\t\tBook Appointment\n";
    line();
    cout << "\n\n\tFirst Name or ID Number : ";
    cin >> identification;
    //set to either first name or id number
    strcpy_s(temp.f_name, identification.c_str());
    strcpy_s(temp.email, identification.c_str());
    file.open("DB.dat", ios::in | ios::binary); // Strictly read
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&profile), sizeof(profile))) {
            if ((strcmp(temp.f_name, profile.f_name) == 0) || (strcmp(temp.email, profile.email) == 0)) {
                flag = true; cout << "\n"; line();
                // Display stats
                cout << "\n\n\t" << profile.f_name << " " << profile.l_name << ". #" << profile.id;
                cout << "\n\n\tBlood Type : " << profile.blood_type << ", can recive blood(s) " << profile.blood_needed;
                cout << "\n\tEmail : " << profile.email;
                cout << "\n\tStatus : " << profile.type;
                cout << "\n\n\tAddress Line 1 : " << profile.address_1;
                cout << "\n\tAddress Line 2 : " << profile.address_2;
                //Ask user if they wanna book an appointment
                cout << "\n\n\tEMERGENCY PHONE CONTACT : " << profile.phone << "\n\n"; line(); cout << "\n\n\tWould you like to book this appoiment\n\tplease enter (y/n) : ";
                char inputBookingyORn;  cin >> inputBookingyORn;
                if (tolower(inputBookingyORn) == 'y') {
                    cout << "\n"; line();
                    cout << "\n\n\tCONTINUE TO BOOK - ";
                    system("PAUSE");
                inputBooking_date:
                    //ask for booking date
                    cout << "\n\tPlease enter\n\ta date DD/MM/YY or DD/MM/YYYY : ";
                    string inputBooking_date; char inputBooking_date_correct; cin >> inputBooking_date;
                    cout << "\tIs " << inputBooking_date << " correct ? (y/n) : ";
                    cin >> inputBooking_date_correct;
                    if (tolower(inputBooking_date_correct) == 'n') {
                        goto inputBooking_date;
                    }
                inputBooking_time:
                    //ask for booking time
                    cout << "\n\tPlease enter\n\ta time (1:00PM or 1300) : ";
                    string inputBooking_time; char inputBooking_time_correct; cin >> inputBooking_time;
                    cout << "\tIs " << inputBooking_time << " correct ? (y/n) : ";
                    cin >> inputBooking_time_correct;
                    if (tolower(inputBooking_time_correct) == 'n') {
                        goto inputBooking_time;
                    }
                    cout << "\tCONFIRMATION - "; clearConsole(); line(); cout << "\n\t\t\tBooking Receipt\n"; line();
                    // for identification
                    string id_string_booking = to_string(rand() % 10000000 + 1000000000);
                    cout << "\n\nBooking #" << id_string_booking << " emailed to "<< return_email <<"\n\n";
                    cout << "booking Confirmed with" << profile.f_name << " " << profile.l_name;
                    cout << "\nTime " << inputBooking_time;
                    cout << "on Date " << inputBooking_date;
                    cout << "\nWHERE: Level 4/3 City Road, Grafton, Auckland 1010, New Zealand\n";
                

                    cout << "\n";

                }
                else {
                    cout << "\n"; line();
                    cout << "\n\n\tCANCELLED - ";
                }

            }
        }
    }
    else {
        cout << "ERROR: OPEN FILE"; // error handling
    }
    if (!flag) {
        cout << "\n\tNothing on file ;( \n\n";
        line();
        cout << "\n\n\t";
    }
    //return and if return then offer to book appoiment
    system("PAUSE");
    clearConsole(); file.close(); mainProfile(return_email);
}

