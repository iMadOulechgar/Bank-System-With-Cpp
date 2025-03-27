#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

const string FileTextFormNamed = "iMadOulechgar.txt";
const string FileTextForUsers = "UserData.txt" ;

void ShowMainMenu();
void ShowTransationMenu();
void ShowManageUsersMenu();
void HeaderLoginMenu();
void GoBackToMainMenue();

enum enOptions{ClientList = 1 ,AddClient = 2 ,DeleteClient = 3 , UpdateClient = 4 , FindClient = 5 , Transaction = 6 , ManageUser = 7 ,logout = 8};

enum enTransaction{Deposit = 1 , withdraw = 2 , TotalBalance = 3 , BackToMenu = 4};

enum enManageUsers{UserList = 1 , AddNewUser = 2 , DeleteUser = 3 , UpdateUser = 4 , FindUser = 5 , BackToMainMenu = 6};

enum enPermissions{eAll = -1 , GetClientlist = 1 , GetAddClient = 2 , GetDeleteClient = 4 , GetUpdateClient = 8 , GetFindClient = 16 , GetTransaction = 32 , GetManagerUser = 64};

bool PermissionsChecker(enPermissions Permissions);

struct stClientInfo
{
    string AccountNumber;
    string codepin;
    string Name;
    string PhoneNumber;
    double balance;
    bool MarkClient = false;
};

struct stUserInfo
{
    
    string userName;
    string password;
    int Permission = 0; 
    bool markUser = false ;
};

stUserInfo CurrentUser;

void MessageUserDontHaveAcces(){
    cout<<"\nSsory ): , You Dont Have Permession To Do That , Contact Admin =) ";
}

string ReadAccountNumber(string message){

    string Acc ; 

    cout<<message;
    cin>>Acc;
    return Acc;
}

int ChoiceMenu(){

    int choice = 0 ;

    cout<<"Enter From [1] To [8] Which Option You Want : ";
    cin>>choice;

    return choice;
}

int ChoiceTransaction(){

    int choice = 0 ;

    cout<<"Enter From [1] To [4] Which Option You Want : ";
    cin>>choice;

    return choice;
}

int choiceManagerUser(){
    int number;

    cout<<"Choice From [1] To [6] : ";
    cin>>number;

    return number;
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

    if(!PermissionsChecker(enPermissions::GetAddClient)){
        MessageUserDontHaveAcces();
        GoBackToMainMenue();
    }

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

vector<stClientInfo>SaveDataToFile(string AccountNumber , string FileName ,vector<stClientInfo>vClient){

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
        SaveDataToFile(AccountNumber,FileTextFormNamed,vClient);
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
        SaveDataToFile(AccountNumber,FileTextFormNamed,vClient);
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

    if(!PermissionsChecker(enPermissions::GetClientlist)){
        MessageUserDontHaveAcces();
        GoBackToMainMenue();
    }
    vector<stClientInfo>vClient = LoadClientDataFromFile();
    Recherche(vClient);
}

void DeleteClientFromDataFile(){
    if(!PermissionsChecker(enPermissions::GetDeleteClient)){
        MessageUserDontHaveAcces();
        GoBackToMainMenue();
    }
    vector<stClientInfo>vClient = LoadClientDataFromFile();
    string AccountNum = ReadAccountNumber("Enter The Account Number You searching for : ");
    DeleteClientFromFile(AccountNum , vClient);
}

void UpdateClientData(){
    if(!PermissionsChecker(enPermissions::GetUpdateClient)){
        MessageUserDontHaveAcces();
        GoBackToMainMenue();
    }
    vector<stClientInfo>vClient = LoadClientDataFromFile();
    string AccountNum = ReadAccountNumber("Enter The Account Number You searching for : ");
    UpdateDataFromFile(AccountNum , vClient);

}

void FindClientInfo(){
    if(!PermissionsChecker(enPermissions::GetFindClient)){
        MessageUserDontHaveAcces();
        GoBackToMainMenue();
    }
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
    case enOptions::logout:
        system("cls");
        ExitFunction();
        break;  
    case enOptions::Transaction:
        system("cls");
        ShowTransationMenu();
        break;
    case enOptions::ManageUser:
        system("cls");
        ShowManageUsersMenu();
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

void WithdrawAmountFromClient(string FileName = FileTextFormNamed)
{
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

void GoBackToManageUsers()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowManageUsersMenu();
}

stUserInfo ConvertLineToRecordUser(string Line){

    vector<string>vUser = SplitString(Line);
    stUserInfo Userinfo;

    Userinfo.userName = vUser.at(0);
    Userinfo.password = vUser.at(1);
    Userinfo.Permission = stoi(vUser.at(2));

    return Userinfo;
}

vector<stUserInfo> LodingUserDatefromFile(string Filename = FileTextForUsers){
    
    vector<stUserInfo>vUser; 
    string S1;
    fstream Myfile;
    stUserInfo Userinfo;

    Myfile.open(Filename , ios::in);

    if(Myfile.is_open()){

    while(getline(Myfile,S1))
    {
        Userinfo = ConvertLineToRecordUser(S1);
        vUser.push_back(Userinfo);
    }
   }
    Myfile.close();

    return vUser;
}

bool FindUserNameAndPassword(string Username , string password , stUserInfo &user , string FileName = FileTextForUsers){

    vector<stUserInfo>vUser = LodingUserDatefromFile();
    
    for (stUserInfo U : vUser)
    {
        if (U.userName == Username && U.password == password)
        {
            user = U ;
            return true;
        }
    }
    return false;
}

bool PermissionsChecker(enPermissions Permissions){

    if(CurrentUser.Permission == enPermissions::eAll)
        return true;
    if ((CurrentUser.Permission & Permissions) == Permissions)
        return true;
    else
        return false;
}

void PrintUserIfFinded(stUserInfo user){

        cout<<"\n____________________________________________________\n";
        cout<<"UserName    : "<<user.userName<<endl;
        cout<<"Password    : "<<user.password<<endl;
        cout<<"Permission  :"<<user.Permission;
        cout<<"\n____________________________________________________\n";
}

void print(stUserInfo User){

    cout<<"| "<<setw(15)<<left<<User.userName;
    cout<<"| "<<setw(10)<<left<<User.password;
    cout<<"| "<<setw(12)<<left<<User.Permission;
}

void ListOfUsers(){

    vector<stUserInfo>vUsers  = LodingUserDatefromFile();

    cout<<"\n--------------------------------------------------------------------------------------------------------\n\n";
    cout<<"                                     Total Of The Client In The Bank("<<vUsers.size()<<")";
    cout<<"\n\n--------------------------------------------------------------------------------------------------------\n";

    cout<<"\n_________________________________________________________________________________________________________\n\n";
    cout<<"| "<<setw(15)<<left<<"UserName";
    cout<<"| "<<setw(10)<<left<<"Password";
    cout<<"| "<<setw(40)<<left<<"Permission";
    cout<<"\n\n_________________________________________________________________________________________________________\n\n";

    if(vUsers.size() == 0)
        cout<<"There Is Not One In The List ";
    else
        for (stUserInfo &Userinfo : vUsers)
       {
          print(Userinfo);
          cout<<'\n';
       }
}

string ConvertRecordToLineUserInfo(stUserInfo UserInfo , string Delim = "//*//"){

    string S1 = "";

    S1 += UserInfo.userName + Delim ;
    S1 += UserInfo.password + Delim ;
    S1 += to_string(UserInfo.Permission);

    return S1;
}

vector<stUserInfo>SaveDataOfUserToFile(string Username , string FileName ,vector<stUserInfo>vUser){

    fstream Myfile;
    string S1 = "";

    Myfile.open(FileName,ios::out);

    for (stUserInfo U : vUser)
    {
        if (U.markUser == false)
        {
            S1 = ConvertRecordToLineUserInfo(U);
            Myfile<<S1<<endl;
        }
    }
    return vUser;
}

void FindUserByUserNameAndPassword(){

    string username ;
    string password ;
    stUserInfo Userinfo;


    cout<<"Enter Username : ";
    cin>>username;
    cout<<"Enter Password : ";
    cin>>password;

    if (FindUserNameAndPassword(username,password,Userinfo))
    {
        PrintUserIfFinded(Userinfo);
    }
    else
    {
        cout<<"This User Is Not On The Data File ):";
    }
}

int GivingPermissions(){

    char choice = 'y';
    int permission = 0 ;

    cout<<"Do You Wanna Give Him Full Access ? y/n ";
    cin>>choice;
    if (choice == 'y' || choice == 'Y')
    {
        return -1; 
    }

    cout<<"\nAccess To Show ClientList y/n ? ";
    cin>>choice;
    if (choice=='y' || choice == 'Y')
    permission += enPermissions::GetClientlist;

        cout<<"\nAccess To Show AddNewClient y/n ? ";
        cin>>choice;
    if (choice=='y' || choice == 'Y')
    permission += enPermissions::GetAddClient;

        cout<<"\nAccess To Show DeleteClient y/n ? ";
        cin>>choice;
    if (choice=='y' || choice == 'Y')
    permission += enPermissions::GetDeleteClient;

        cout<<"\nAccess To Show UpdateClient y/n ? ";
        cin>>choice;
    if (choice=='y' || choice == 'Y')
    permission += enPermissions::GetUpdateClient;

        cout<<"\nAccess To Show FindClient y/n ? ";
        cin>>choice;
    if (choice=='y' || choice == 'Y')
    permission += enPermissions::GetFindClient;

        cout<<"\nAccess To Show Transaction y/n ? ";
        cin>>choice;
    if (choice=='y' || choice == 'Y')
    permission += enPermissions::GetTransaction;

        cout<<"\nAccess To Show manageUser y/n ? ";
        cin>>choice;
    if (choice=='y' || choice == 'Y')
    permission += enPermissions::GetManagerUser;

    return permission;
}

stUserInfo ReadNewUser(){

    stUserInfo UserInfo;

    cout<<"Enter UserName : \n";
    cin>>UserInfo.userName;
    cout<<"Enter Password : \n";
    cin>>UserInfo.password;

    while (FindUserNameAndPassword(UserInfo.userName , UserInfo.password , CurrentUser))
    {
        cout<<"\nThe User Name And Password Already exist : ";

        cout<<"Enter UserName : ";
        cin>>UserInfo.userName;
        cout<<"Enter Password : ";
        cin>>UserInfo.password;
    }
    UserInfo.Permission = GivingPermissions();
    
    return UserInfo;
}

void AddNewUserToFile(stUserInfo UserInfo , string FileName = FileTextForUsers){

    fstream Myfile;
    string S9 = "";

    Myfile.open(FileName,ios::out | ios::app);

    if (Myfile.is_open())
    {
        S9 = ConvertRecordToLineUserInfo(UserInfo);
        cout<<'\n';
        Myfile<<S9;
        cout<<"User Added succefly :) ";
    }
    Myfile.close();
}

void AddNewUserOneByOne(){
    stUserInfo User ;
    User = ReadNewUser();
    AddNewUserToFile(User);
}

void AddUserAndRepeat(){
    
    char YesOrNo = 'y';
   do
   {
    system("cls");
    cout<<"Adding New User : \n\n";

    AddNewUserOneByOne();
    cout<<"You Wanna Add More Users ? ";
    cin>>YesOrNo;

   }while(YesOrNo == 'y' || YesOrNo == 'Y');

}

bool MarkUser(string Username , vector<stUserInfo>&User){

    for (stUserInfo &U : User)
    {
        if (U.userName == Username)
        {
            U.markUser = true;
            return true;
        }
    }

    return false;
}

void deleteUser(string FileName = FileTextForUsers){

    string Username;
    string password;
    vector<stUserInfo>vUser = LodingUserDatefromFile();

    stUserInfo User;

    cout<<"\nEnter User You Wanna Delete : ";
    cin>>Username;
    cout<<"\nEnter Password : ";
    cin>>password;

    if (Username != "Admin")
    {
        if(FindUserNameAndPassword(Username,password,User))
    {
        MarkUser(Username , vUser);
        SaveDataOfUserToFile(Username,FileTextForUsers,vUser);
        cout<<"User Deleted Succefly :)";
    }
    else
    {
        cout<<"\nThis Client Not Found ):";
    }

    }
    else
    {
        cout<<"You Can Not Delete Admin From File :)";
    }
    
    
}

void Updateuser(){

    string uername;
    string password;
    char yesorno = 'y';
    stUserInfo User;
    vector<stUserInfo>vuser = LodingUserDatefromFile();

    cout<<"Enter Username : ";
    cin>>User.userName;
    cout<<"Enter Password : ";
    cin>>User.password;

    if(FindUserNameAndPassword(User.userName , User.password , User)){
        PrintUserIfFinded(User);
        cout<<"\n Are YOu Sure You Wanna Update This Personne y/n ? ";
        cin>>yesorno;
        if (yesorno == 'y' || yesorno == 'Y')
        {
            for (stUserInfo &U : vuser)
            {
                if (U.userName == User.userName)
                {
                    cout<<"Enter New Password : ";
                    cin>>password;
                    U.password = password;
                    cout<<"You Want Too Give Him Full Access ? y/n ";
                    cin>>yesorno;
                    if (yesorno == 'y' || yesorno == 'Y')
                        U.Permission = enPermissions::eAll; 
                    else
                        U.Permission = GivingPermissions();
                    
            
                      SaveDataOfUserToFile(User.userName , FileTextForUsers , vuser);
                      cout<<"User update Succefly :)";
                }
            }
        }
    }
    else
    {
        cout<<"This User Not Found ";
    }

}

void PerformManageUsers(enManageUsers ManageUsers){

    switch (ManageUsers)
    {
    case enManageUsers::UserList:
      system("cls");
      ListOfUsers();
      GoBackToManageUsers();
        break;
    case enManageUsers::BackToMainMenu:
      system("cls");
      ShowMainMenu();
        break;
    case enManageUsers::AddNewUser:
      system("cls");
      AddUserAndRepeat();
      GoBackToManageUsers();
        break;
    case enManageUsers::DeleteUser:
      system("cls");
      deleteUser();
      GoBackToManageUsers();
        break;
    case enManageUsers::UpdateUser:
      system("cls") ;
      Updateuser();
      GoBackToManageUsers();
    case enManageUsers::FindUser:
        system("cls");
        FindUserByUserNameAndPassword();
        GoBackToManageUsers();
    }
}

void ShowMainMenu(){

    system("cls");
    cout<<"_____________________________________________________________________________________\n";
    cout<<"                                         Main Menu                                 ";
    cout<<"\n_____________________________________________________________________________________\n";
    cout<<"\t\t | [1] Show ClientList \n";
    cout<<"\t\t | [2] Add Client Too File \n";
    cout<<"\t\t | [3] Delete Client From File \n";
    cout<<"\t\t | [4] Update Client Info \n";
    cout<<"\t\t | [5] Find Client Info \n";
    cout<<"\t\t | [6] Transaction \n";
    cout<<"\t\t | [7] Manage Users \n";
    cout<<"\t\t | [8] LogOut \n";
    cout<<"_____________________________________________________________________________________\n";
    cout<<"\n_____________________________________________________________________________________\n\n";

    PerformMainMenuOption((enOptions)ChoiceMenu());
}

void ShowTransationMenu(){

    if(!PermissionsChecker(enPermissions::GetTransaction)){
        MessageUserDontHaveAcces();
        GoBackToMainMenue();
    }

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

void ShowManageUsersMenu(){
    if(!PermissionsChecker(enPermissions::GetManagerUser)){
        MessageUserDontHaveAcces();
        GoBackToMainMenue();
    }

    system("cls");
    cout<<"_____________________________________________________________________________________\n";
    cout<<"                                  Manage UsesMenu                                ";
    cout<<"\n_____________________________________________________________________________________\n";
    cout<<"\t\t | [1] List User \n";
    cout<<"\t\t | [2] Add New User \n";
    cout<<"\t\t | [3] Delete User \n";
    cout<<"\t\t | [4] Update Use \n";
    cout<<"\t\t | [5] Find User \n";
    cout<<"\t\t | [6] Back To Main Menu \n";
    cout<<"_____________________________________________________________________________________\n";
    cout<<"\n_____________________________________________________________________________________\n\n";
    PerformManageUsers((enManageUsers)(choiceManagerUser()));
}

bool LoadUserinfo(string Username , string password){

    if(FindUserNameAndPassword(Username,password,CurrentUser))
        return true;
    else
        return false;
}

void HeaderLoginMenu(){

    bool checkLogin = false;

    cout<<"______________________       ____________________\n";
    cout<<"_______________________Login_____________________\n";
    cout<<"______________________       ___________________\n";
    do
    {

        if (checkLogin)
        {
            cout<<"Invalid Username And Password ): \n";
        }
        
        string username = ReadAccountNumber("Enter Username : ");
        string password = ReadAccountNumber("Enter password : ");

        checkLogin = !LoadUserinfo(username,password);

    } while (checkLogin);
    
    ShowMainMenu();
}

int main(){

    HeaderLoginMenu();

    return 0;
}