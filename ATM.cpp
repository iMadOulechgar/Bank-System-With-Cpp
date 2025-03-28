#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

void ATMmainMenu();
void Login();
void PerformNormalWithdraw();
void PerformDepositAmountfun();
void PerformQuickWithdrawfun(int GetQuickWithdraw);

const string FileTextFormNamed = "iMadOulechgar.txt";

enum enATMOption{QuickWithdraw = 1 , NormalWithdraw = 2 , Deposit = 3 , CheckBalance = 4 , LogOut = 5 }; 

struct stClientInfo
{
    string AccountNumber;
    string codepin;
    string Name;
    string PhoneNumber;
    double balance;
    bool MarkClient = false;
};

stClientInfo CurrentCLient;

vector<string> SplitString(string Line , string Delim = "//*//"){

    vector<string>strimad;
    string word ;
    int Position = 0 ;

    while ((Position = Line.find(Delim)) != std::string::npos)
    {
        word = Line.substr(0,Position);
        if (word != "")
        {   
            strimad.push_back(word);
        }
        Line.erase(0,Position + Delim.length());
    }
    if (Line != " ")
    {
        strimad.push_back(Line);
    }

    return strimad;
}

stClientInfo ConvertLineToRecord(string Line , string Delim = "//*//"){

    stClientInfo ClientInfo;

        vector<string>vClient = SplitString(Line);

        ClientInfo.AccountNumber = vClient.at(0);
        ClientInfo.codepin = vClient.at(1);
        ClientInfo.Name = vClient.at(2);
        ClientInfo.PhoneNumber = vClient.at(3);
        ClientInfo.balance = stod(vClient.at(4));

    return ClientInfo; 
}

vector<stClientInfo>LoadClientDataFromFile(string FileName = FileTextFormNamed){

    stClientInfo Client ;
    string S9 = "";
    vector<stClientInfo>vClient;

    fstream Myfile;
    Myfile.open(FileName,ios::in);

    if (Myfile.is_open())
    {
        while (getline(Myfile,S9))
        {
            Client = ConvertLineToRecord(S9);
            vClient.push_back(Client);
        }
        Myfile.close();
    }
    return vClient;
}

string ConvertRecordTooLine(stClientInfo Client , string Delim = "//*//"){

    string S1 = "";

    S1 += Client.AccountNumber + Delim;
    S1 += Client.codepin + Delim;
    S1 += Client.Name + Delim;
    S1 += Client.PhoneNumber + Delim;
    S1 += to_string(Client.balance);

    return S1;
}

vector<stClientInfo>SaveDataToFile(string AccountNumber , string FileName ,vector<stClientInfo>vClient){

    fstream Myfile;
    string S1 ;

    Myfile.open(FileName,ios::out);

    for (stClientInfo C : vClient)
    {
        if (C.MarkClient == false)
        {
            S1 = ConvertRecordTooLine(C);
            Myfile<<S1<<endl;
        }
    }
    return vClient;
}

int ReadNumber(){

    int Number;
    
    cout<<"enter Number : ";
    cin>>Number;
    while (Number < 1 || Number > 9)
    {
        cout<<"This Number Not Found ): TryAgain ";
        cin>>Number;
    }
    return Number;
}

int ReadDeposit(){

    int Amount ;
    cout<<"Enter Amount : ";
    cin>>Amount;

    while (Amount <= 0)
    {
        cout<<"Imposible Try Again , enter Amount : ";
        cin>>Amount;
    }
    return Amount;
}

string ReadTExt(string message){

    string Text ;

    cout<<message;
    cin>>Text;

    return Text;
}

bool FindCLientByAccountNumberandCodepin(string AccountNUmber , string Codepin , stClientInfo &Client){

    vector<stClientInfo>vClient = LoadClientDataFromFile();

    for (stClientInfo C : vClient)
    {
        if (C.AccountNumber == AccountNUmber  &&  C.codepin == Codepin)
        {
            Client = C ;
            return true;
        }
    }
    return false;
}

bool CheckLogin(string AccountNUmber , string Codepin){

    if(FindCLientByAccountNumberandCodepin(AccountNUmber,Codepin,CurrentCLient))
        return true;
    else
        return false;
}

bool DepositFun(vector<stClientInfo>&vClient , int Amount , string AccountNumber){

    char yesorno = 'n';

    cout<<"Are You Sure You Wanna DEposit Too Your Acc : ";
    cin>>yesorno;

    if (yesorno == 'y' || yesorno == 'Y')
    {
        for (stClientInfo &C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.balance += Amount;
            SaveDataToFile(AccountNumber,FileTextFormNamed,vClient);
            cout<<"\n\nThe Deposit Was Done Succefuly . This Is Your New Balance :) "<<C.balance;
            return true;
        }
    }
    }
    else
    {
        cout<<"Next Time )-: ";
        return false;
    }
}

int Quick(int choice){

    switch (choice)
    {
    case 1:
        return 20;
    case 2:
        return 100;
    case 3:
        return 400;
    case 4:
        return 800;
    case 5:
        return 50;
    case 6:
        return 200;
    case 7:
        return 600;
    case 8:
        return 1000;
    default:
        return 0;
    }             
}

void ShowAndChoiceQuickWithdraw(){
    cout<<"_________________________________\n";
    cout<<" [1] 20 \t "<<"  [6] 200"<<endl;
    cout<<" [2] 100\t "<<"  [7] 600 "<<endl;
    cout<<" [3] 400\t "<<"  [8] 1000"<<endl;
    cout<<" [4] 800\n "<<"  [9] Exit"<<endl;
    cout<<"[5] 50 \n ";
    cout<<"_________________________________\n";
    PerformQuickWithdrawfun(ReadNumber());
}

void PerformQuickWithdrawfun(int GetQuickWithdraw){

        if (GetQuickWithdraw == 9)
        {
            return ;
        }

        float AmountYouChoose = Quick(GetQuickWithdraw);
        
        if (AmountYouChoose > CurrentCLient.balance){
            cout<<"You Dont have This Amount "<<AmountYouChoose<<" On Your Balance ): ";
            cout<<"Press Any Key ...";
            system("pause>0");
            ShowAndChoiceQuickWithdraw();
            return;
        } 
        else
        {
            vector<stClientInfo>vClient = LoadClientDataFromFile();
            DepositFun(vClient,AmountYouChoose * -1 ,CurrentCLient.AccountNumber);
            CurrentCLient.balance -= AmountYouChoose;
        }
}

int readNormalAmountWithdraw(){
    
    int Num;
    
    cout<<"Enter an Amount Multiple 5's: ";
    cin>>Num;

    while (Num % 5 != 0)
    {
        cout<<"Enter an Amount Multiple 5's: ";
        cin>>Num;
    }

    return Num;
}

void ShowNormalWithdrawScreen(){
    cout<<"___________________________________\n";
    cout<<"\t\tNormal Withdraw \n";
    cout<<"___________________________________\n";
      PerformNormalWithdraw();
}

void PerformNormalWithdraw(){

    char yesorno = 'y';
    int amount = readNormalAmountWithdraw();

    if (amount > CurrentCLient.balance)
    {
        cout<<"You Dont have This Amount "<<amount<<" On Your Balance ): ";
        cout<<"Press Any Key ...";
        system("pause>0");
        ShowNormalWithdrawScreen();
        return;
    }
    else
    {
            vector<stClientInfo>vClient = LoadClientDataFromFile();
            DepositFun(vClient,amount * -1,CurrentCLient.AccountNumber);
            CurrentCLient.balance -= amount;
    }
}

void ShowDepositAmount(){
    cout<<"\n________________________________________\n";
    cout<<"\t\tDeposit Balance                        ";
    cout<<"\n________________________________________\n";
    PerformDepositAmountfun();
}

void PerformDepositAmountfun(){

    double amount = ReadDeposit();

        vector<stClientInfo>vClient = LoadClientDataFromFile();
        DepositFun(vClient,amount,CurrentCLient.AccountNumber);
        CurrentCLient.balance += amount;
}

void AccountBalancefun(){

    cout<<"\n________________________________________\n";
    cout<<"\t\tAccount Balance                        ";
    cout<<"\n________________________________________\n";
    cout<<"This Is Your Balance : "<<CurrentCLient.balance;
}

void BackToMainMenu(){
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ATMmainMenu();
}

void PerformATMSYSTEM(enATMOption ATMOPTION){

    switch (ATMOPTION)
    {
    case enATMOption::QuickWithdraw:
        system("cls");
        ShowAndChoiceQuickWithdraw();
        BackToMainMenu();
        break;
    case enATMOption::NormalWithdraw:
        system("cls");
        ShowNormalWithdrawScreen();
        BackToMainMenu();
        break;
    case enATMOption::Deposit:
        system("cls");
        ShowDepositAmount();
        BackToMainMenu();
        break;
    case enATMOption::CheckBalance:
        system("cls");
        AccountBalancefun();
        BackToMainMenu();
        break;
    case enATMOption::LogOut:
        system("cls");
        Login();
    }
}

void Login(){

    bool Checker = false;

    do
    {
        if (Checker)
        {
            cout<<"\nInvalid Account ):\n";
        }
        
        string AccountNumber = ReadTExt("Enter Your Account NUmber : ");
        string Codepin = ReadTExt("Enter Your Code Pin : ");

        Checker = !CheckLogin(AccountNumber,Codepin);

    } while (Checker);
    ATMmainMenu();
}

int ReadMainPerform(){

    int Num ;

    cout<<"Choose From 1 to 5 : ";
    cin>>Num;

    while (Num < 1 || Num > 5)
    {
        cout<<"Choose From 1 to 5 : ";
        cin>>Num;
    }

    return Num;
}

void ATMmainMenu(){

    system("cls");
    cout<<"\n___________________________________________\n";
    cout<<"\tATM Main Menu ";
    cout<<"\n___________________________________________\n";
    cout<<"\t[1] Quick Withdraw . \n";
    cout<<"\t[2] Normale Withdraw . \n";
    cout<<"\t[3] Deposit . \n";
    cout<<"\t[4] Check Balance . \n";
    cout<<"\t[5] Log Out . \n";
    cout<<"______________________________________________\n";
    
    PerformATMSYSTEM((enATMOption)ReadMainPerform());
}

int main(){

    Login();

    return 0;
}