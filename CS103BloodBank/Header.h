
/*
    BloodBank Group Project
    CS103BloodBank.cpp : Header.h
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>

using namespace std;
/*
    la déclaration el fonctions
*/
void mainMenu();
void infoScreen();
void donors_by_blood_type_location();
void line();
void view_single_record();
void donors_by_blood_type();
void clearConsole();
void Admin();
void find_member(char username[50], char password[50]);
void admin_login(char login_id[50], char password[50]);

//Passport for member
struct member {
    //Login Creds
    char email[50];
    char password[50];
    //General
    char type[17];
    char f_name[50];
    char l_name[50];
    char address_1[50];
    char address_2[50];
    char phone[17];
    //Blood
    char blood_type[101];
    char blood_needed[101];
    //identification
    char id[11];
};

void new_member(struct member&);
void view_all_record(struct member&);
void view_all_record_recipient(struct member&);
void view_all_record_donor(struct member&);

void view_record_by_blood(char blood[101]);
void who_can_receive_your_blood(char blood[101]);
void mainLogin();

void mainRegister();
void login_select_num(int);
void Register(int path);
void donate_Info(string email);
void donate_benefitsInfo(string email);
void donors_by_blood_type(string);
void view_contactDetails(string);
void name_search(string);
void mainProfile(string);
void donors_by_blood_type_location(string);
void view_all_record_donor(struct member&);

member define_Profile(char email[50]);