#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

namespace imadLib  {

char convertLetter(char Ch){
    return isupper(Ch) ? tolower(Ch) : toupper(Ch);
}   

int randomnumber(int from , int to){
    int result = rand() % (to - from + 1) + from ;
    return result;
}

vector<string> SplitString(string S1 , string space){

    vector<string>strimad;
    string word ;
    int Position = 0 ;

    while ((Position = S1.find(space)) != std::string::npos)
    {
        word = S1.substr(0,Position);
        if (word != "")
        {   
            strimad.push_back(word);
        }
        S1.erase(0,Position + space.length());
    }
    if (S1 != " ")
    {
        strimad.push_back(S1);
    }
    return strimad;
}

string TrimLeft(string S1){

    char space = ' ';

    for (int i = 0; i < S1.length(); i++)
    {
        if (S1[i] != ' '){
         return S1.substr(i,S1.length() -i);
        }
    }
    return "";
}

string TrimRight(string S1){

    for (int i = S1.length() - 1; i > 0 ; i--)
    {
        if (S1[i] != ' '){
         return S1.substr(0,i + 1);
        }
    }
    return "";
}

string JoinString(string SpaceOrWhatEver , vector<string>imadspace){

    string STRsum = "";
    for ( string i : imadspace)
    {
        STRsum = STRsum + i + SpaceOrWhatEver ;
    }
    return STRsum.substr(0,STRsum.length() - SpaceOrWhatEver.length());
}

string JoinString(string SpaceOrWhatEver , string imadarry[] , short length){
    string STRsum ;

    for (int i = 0 ; i < length ; i++)
    {
        STRsum = STRsum + imadarry[i] + SpaceOrWhatEver;
    }
    return STRsum.substr(0,STRsum.length() - SpaceOrWhatEver.length());
}

string ReplaceFunction(string s1 , string YouSearchingFor , string ReplaceTo){


    int position = s1.find(YouSearchingFor);

    while (position != std::string::npos)
    {
        s1 = s1.replace(position,YouSearchingFor.length(),ReplaceTo);
        position = s1.find(YouSearchingFor);
    }
    return s1;
}

string IsPunctuation(string s1){

    string s9 = "";

    for (int i = 0; i < s1.length(); i++)
    {
        if (!ispunct(s1[i]))
        {
            s9 = s9 + s1[i];
        }
    }
    return s9;
}

bool isLeapYear(int year){

    return (year % 4 == 0 && year != 100 == 0) || (year % 400 == 0) ;
}


}