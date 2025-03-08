#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

const string FileTextFormNamed = "iMadOulechgar.txt";

void ShowMainMenu();
void ShowTransationMenu();

enum enOptions{ClientList = 1 ,AddClient = 2 ,DeleteClient = 3 , UpdateClient = 4 , FindClient = 5 , Transaction = 6 , Exit = 7};

enum enTransaction{Deposit = 1 , withdraw = 2 , TotalBalance = 3 , BackToMenu = 4};

string ReadAccountNumber(string message){

    string Acc ; 

    cout<<message;
    cin>>Acc;
    return Acc;
}

struct stClientInfo
{
    string AccountNumber;
    string codepin;
    string Name;
    string PhoneNumber;
    double balance;
    bool MarkClient = false;
};

int ChoiceMenu(){

    int choice = 0 ;

    cout<<"Enter From [1] To [7] Which Option You Want : ";
    cin>>choice;

return choice;
}

int ChoiceTransaction(){

    int choice = 0 ;

    cout<<"Enter From [1] To [4] Which Option You Want : ";
    cin>>choice;

return choice;
}

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

void PrintClient(stClientInfo Client){

    cout<<"| "<<setw(15)<<left<<Client.AccountNumber;
    cout<<"| "<<setw(10)<<left<<Client.codepin;
    cout<<"| "<<setw(40)<<left<<Client.Name;
    cout<<"| "<<setw(12)<<left<<Client.PhoneNumber;
    cout<<"| "<<setw(12)<<left<<to_string(Client.balance);
}

void Recherche(vector<stClientInfo>&vClient){

    cout<<"\n--------------------------------------------------------------------------------------------------------\n\n";
    cout<<"                                     Total Of The Client In The Bank("<<vClient.size()<<")";
    cout<<"\n\n--------------------------------------------------------------------------------------------------------\n";

    cout<<"\n_________________________________________________________________________________________________________\n\n";
    cout<<"| "<<setw(15)<<left<<"AccountNumber";
    cout<<"| "<<setw(10)<<left<<"codepin";
    cout<<"| "<<setw(40)<<left<<"FullName";
    cout<<"| "<<setw(12)<<left<<"PhoneNumber";
    cout<<"| "<<setw(12)<<left<<"balance";
    cout<<"\n\n_________________________________________________________________________________________________________\n\n";

    for (stClientInfo &C : vClient)
    {
        PrintClient(C);
        cout<<"\n";
    }
}

bool ClientExistsByAccountNumber(string AccountNumber , string FileName = FileTextFormNamed){

    fstream Myfile ;
    string Line;
    stClientInfo Client ;
    vector<stClientInfo>vClient;
    Myfile.open(FileName,ios::in);

    if (Myfile.is_open())
    {
        while (getline(Myfile,Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                Myfile.close();
                return true;
            }
            vClient.push_back(Client);
        }
        Myfile.close();
    }
    return false;
}

stClientInfo ReadNewClient(stClientInfo ClientInfo){

    cout<<"Enter Account Number : ";
    getline(cin>>ws,ClientInfo.AccountNumber);

    while (ClientExistsByAccountNumber(ClientInfo.AccountNumber))
    {
        cout<<"This AccountNum Is Already In The File Data Please Choose Another Num : ";
        getline(cin>>ws,ClientInfo.AccountNumber);
    }
    
    cout<<"Enter Code Pin : ";
    getline(cin,ClientInfo.codepin);
    cout<<"Enter Full Name : ";
    getline(cin,ClientInfo.Name);
    cout<<"Enter Phone Number : ";
    getline(cin,ClientInfo.PhoneNumber);
    cout<<"Enter Your Balance : ";
    cin>>ClientInfo.balance;
    
    return ClientInfo;
}

string ConvertRecordToLine(stClientInfo ClientInfo , string delim = "//*//"){

    string Line = "";

    Line += ClientInfo.AccountNumber + delim;
    Line += ClientInfo.codepin + delim;
    Line += ClientInfo.Name + delim;
    Line += ClientInfo.PhoneNumber + delim;
    Line += to_string(ClientInfo.balance);

    return Line;
}

void AddNewClientToFile(string FileName = FileTextFormNamed){

    fstream Myfile;
    stClientInfo Client ;
    string S9 = "";

    Myfile.open(FileName,ios::out | ios::app);

    if (Myfile.is_open())
    {
        Client = ReadNewClient(Client);
        S9 = ConvertRecordToLine(Client);
        cout<<'\n';
        Myfile<<S9;
        cout<<"Add Client Is Done :) ";
    }
    Myfile.close();
}

bool MarkClientFromRecord(string AccountNumber , vector<stClientInfo>&vClient){

    for (stClientInfo &C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkClient = true;
            return true;
        }
    }
    return false;
}

vector<stClientInfo>SaveDataClientToFile(string AccountNumber , string FileName ,vector<stClientInfo>vClient){

    fstream Myfile;
    string S1 ;

    Myfile.open(FileName,ios::out);

    for (stClientInfo C : vClient)
    {
        if (C.MarkClient == false)
        {
            S1 = ConvertRecordToLine(C);
            Myfile<<S1<<endl;
        }
    }
    return vClient;
}

bool FindClientData(string AccountNumber , vector<stClientInfo>vClient , stClientInfo&Client ){

    for (stClientInfo C : vClient)
    {
        if (AccountNumber == C.AccountNumber)
        {
            Client = C;
            return true; 
        }
    }
    return false;
}

void DeleteClientFromFile(string AccountNumber,vector<stClientInfo>&vClient){

    string s9 = "";
    stClientInfo C ;

       if(FindClientData(AccountNumber,vClient,C))
    {
        MarkClientFromRecord(AccountNumber,vClient);
        SaveDataClientToFile(AccountNumber,FileTextFormNamed,vClient);
        cout<<"The Client Deleted Succefuly :) ";
    }
    else
    {
        cout<<"This Client Is NOT Found ):";
    }
}
        
void PrintRechercheForClientAcc(stClientInfo Client){

    cout<<"-----------------------------------------------------\n";
    cout<<"Account Number : "<<Client.AccountNumber<<endl;
    cout<<"Code Pin : "<<Client.codepin<<endl;
    cout<<"Name : "<<Client.Name<<endl;
    cout<<"Phone Number : "<<Client.PhoneNumber<<endl;
    cout<<"Balance : "<<to_string(Client.balance)<<endl;
    cout<<"\n-----------------------------------------------------\n";
}

stClientInfo ReadUpdateClient(string AccountNumber){

    stClientInfo Client;

    Client.AccountNumber = AccountNumber;
    cout<<"CodePin? ";
    getline(cin>>ws,Client.codepin);
    cout<<"Name? ";
    getline(cin,Client.Name);
    cout<<"PhoneNumber? ";
    getline(cin,Client.PhoneNumber);
    cout<<"Balance? ";
    cin>>Client.balance;

    return Client;
}

bool UpdateDataFromFile(string AccountNumber, vector<stClientInfo>&vClient){

    stClientInfo Client;
    char yesorno = 'n';

    if (FindClientData(AccountNumber,vClient,Client))
    {
        PrintRechercheForClientAcc(Client);
        cout<<"\n\n Are You Sure You Wanna Update This Personne ? ";
        cin>>yesorno;

        if(yesorno  == 'y' || yesorno == 'Y')
        {
            for (stClientInfo & C : vClient)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C = ReadUpdateClient(AccountNumber);
                break;
            }
        }
        SaveDataClientToFile(AccountNumber,FileTextFormNamed,vClient);
        cout<<"The Update Was Succefuly :) ";
        return true;
        }
    }else{

        cout<<"No Client With This Account Number : ("<<AccountNumber<<") Ssory ):";
        return false;
    }
}

void ExitFunction(){

    cout<<"\n\n________________________________________________________________________\n\n";
    cout<<"\t\t\t    SEE YOU LATER\n";
    cout<<"\n___________________________________________________________________________\n\n";
}

void FindClientDataOnFile(string AccountNumber , vector<stClientInfo>vClient){

    stClientInfo Client ;
    if(FindClientData(AccountNumber , vClient , Client)){
        PrintRechercheForClientAcc(Client);
    }else{
        cout<<"This Client Isn't Found ):";
    }
}

void ShowListOfClients(){

    vector<stClientInfo>vClient = LoadClientDataFromFile();
    Recherche(vClient);
}

void DeleteClientFromDataFile(){

    vector<stClientInfo>vClient = LoadClientDataFromFile();
    string AccountNum = ReadAccountNumber("Enter The Account Number You searching for : ");
    DeleteClientFromFile(AccountNum , vClient);
}

void UpdateClientData(){

    vector<stClientInfo>vClient = LoadClientDataFromFile();
    string AccountNum = ReadAccountNumber("Enter The Account Number You searching for : ");
    UpdateDataFromFile(AccountNum , vClient);

}

void FindClientInfo(){

    vector<stClientInfo>vClient = LoadClientDataFromFile();
    string AccountNum = ReadAccountNumber("Enter The Account Number You searching for : ");
      FindClientDataOnFile(AccountNum,vClient);
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenu();
}

void PerformMainMenuOption(enOptions Option){

    switch (Option)
    {
    case enOptions::AddClient:
        system("cls");
        AddNewClientToFile();
        GoBackToMainMenue();
        break;
    case enOptions::ClientList:
        system("cls");
        ShowListOfClients();
        GoBackToMainMenue();
        break;
    case enOptions::UpdateClient:
        system("cls");
        UpdateClientData();
        GoBackToMainMenue();
        break;
    case enOptions::DeleteClient:
        system("cls");
        DeleteClientFromDataFile();
        GoBackToMainMenue();
        break;
    case enOptions::FindClient:
        system("cls");
        FindClientInfo();
        GoBackToMainMenue();
        break;    
    case enOptions::Exit:
        system("cls");
        ExitFunction();
        break;  
    case enOptions::Transaction:
        system("cls");
        ShowTransationMenu();
        break;
    }
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
            SaveDataClientToFile(AccountNumber,FileTextFormNamed,vClient);
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

void DepositAmountToClient(string FileName = FileTextFormNamed){

    vector<stClientInfo>vClient = LoadClientDataFromFile();

    stClientInfo Client;
    string AccNum = ReadAccountNumber("Enter You Account Number : ");

    while (!FindClientData(AccNum,vClient,Client))
    {
        string AccNum = ReadAccountNumber("AccNum Not Found , TryAgain : ");
    }
    
    PrintRechercheForClientAcc(Client);

    double Amount = 0;
    cout<<"\nEnter Amount You Wanna Add : \n";
    cin>>Amount;
    DepositFun(vClient,Amount,AccNum);
}

void WithdrawAmountFromClient(string FileName = FileTextFormNamed){

    vector<stClientInfo>vClient = LoadClientDataFromFile();

    stClientInfo Client;
    string AccNum = ReadAccountNumber("Enter You Account Number : ");

    while (!FindClientData(AccNum,vClient,Client))
    {
        string AccNum = ReadAccountNumber("AccNum Not Found , TryAgain : ");
    }
    
    PrintRechercheForClientAcc(Client);

    double Amount = 0 ;

    cout<<"Enter How Much You Wanna WithDraw From Your Account : ";
    cin>>Amount;
    DepositFun(vClient,Amount * -1 ,AccNum);
}

int CountTotalBalance(vector<stClientInfo>vClient){

    int Number = 0 ;

    for (stClientInfo C : vClient)
    {
        Number += C.balance;
    }

    return Number;
}

void PrintTOtalBalanceOfAllClients(){

    vector<stClientInfo>vClient = LoadClientDataFromFile();

    Recherche(vClient);
    cout<<"\n Totale Balance : "<<CountTotalBalance(vClient);
}

void GoBackToTransactionMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowTransationMenu();
}

void PerformTransactionClient(enTransaction Transaction){

 switch (Transaction)
 {
 case enTransaction::Deposit:
    system("cls");
    DepositAmountToClient();
    GoBackToTransactionMenue();
    break;
  case enTransaction::BackToMenu:
    system("cls");
    ShowMainMenu();
    break;
  case enTransaction::withdraw:
    system("cls");
    WithdrawAmountFromClient();
    GoBackToTransactionMenue();
    break;
  case enTransaction::TotalBalance:
    system("cls");
    PrintTOtalBalanceOfAllClients();
    GoBackToTransactionMenue();
    break;
 }

}

void ShowMainMenu(){

    system("cls");
    cout<<"_____________________________________________________________________________________\n";
    cout<<"\n_____________________________________________________________________________________\n";
    cout<<"\t\t | [1] Show ClientList \n";
    cout<<"\t\t | [2] Add Client Too File \n";
    cout<<"\t\t | [3] Delete Client From File \n";
    cout<<"\t\t | [4] Update Client Info \n";
    cout<<"\t\t | [5] Find Client Info \n";
    cout<<"\t\t | [6] Transaction \n";
    cout<<"\t\t | [7] Exit \n";
    cout<<"_____________________________________________________________________________________\n";
    cout<<"\n_____________________________________________________________________________________\n\n";

    PerformMainMenuOption((enOptions)ChoiceMenu());
}

void ShowTransationMenu(){

    system("cls");
    cout<<"_____________________________________________________________________________________\n";
    cout<<"\n_____________________________________________________________________________________\n";
    cout<<"\t\t | [1] Deposit \n";
    cout<<"\t\t | [2] Withdraw \n";
    cout<<"\t\t | [3] TotaleBalance \n";
    cout<<"\t\t | [4] MainMenu \n";
    cout<<"_____________________________________________________________________________________\n";
    cout<<"\n_____________________________________________________________________________________\n\n";
    PerformTransactionClient((enTransaction)ChoiceTransaction());
}

int main(){

    ShowMainMenu();


    return 0;
}