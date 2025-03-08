#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream> 



using namespace std;

int ReadNumber(string Message){

    int Number;
    cout<<Message;
    cin>>Number;

    return Number;
}

bool isLeapYear(int year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int NumberOfDays(int year){
    return isLeapYear(year) ? 366 : 365;
}

int NumberOfOfDaysInAmonth(int year , int Month){
    
    int arryMonth[7] = {1,3,5,7,8,10,12};

    if (Month < 1 || Month > 12)
        return 0 ;
    else
        return isLeapYear(year)?
    
    
}

int NumberOfHours(int year , int month){
    return NumberOfOfDaysInAmonth(year , month) * 24 ;
}

int NumberOfMinutes(int year , int month){
return NumberOfHours(year , month) * 60;
}

int NumberOfSeconds(int year , int month){
    return NumberOfMinutes(year , month) * 60;
}


int main(){

    int Year = ReadNumber("Enter Year : "); 
    int month = ReadNumber("Enter Month : ");

    cout<<"Number Of Days On Year "<<Year<<" is : "<<NumberOfOfDaysInAmonth(Year , month)<<endl;
    cout<<"Number Of Hours On Year "<<Year<<" is : "<<NumberOfHours(Year , month)<<endl;
    cout<<"Number Of Minutes On Year "<<Year<<" is : "<<NumberOfMinutes(Year , month)<<endl;
    cout<<"Number of Seconds On Year "<<Year<<" is : "<<NumberOfSeconds(Year , month);


    return 0;

}