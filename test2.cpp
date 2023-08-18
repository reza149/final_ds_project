#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
#include<vector>

using namespace std;

void func(vector <int> * temp)
{
    for(int i = 0; i < 9; i++)
    {
        (*temp).push_back(i);
    }   
}

void func2(vector <int>  temp)
{
    for(int i = 0; i < 9; i++)
    {
        temp.push_back(i);
    }   
}

bool word_finder(string inp, string word)
{
    int found = inp.find(word);
    if(found != string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void func_t()
{
    int help = 0;

    help++;

    cout << help << endl;
}



int main()
{
    vector <int> test;

    for(int i = 0; i < 9; i++)
    {
        test.push_back(i);
    }

    for(int j = 0; j < test.size(); j++)
    {
        cout << test[j] << endl;
    }
    

    return 0;
}
//g++ -o ap2 test2.cpp