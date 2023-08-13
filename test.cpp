#include<iostream>
#include<string>
#include"command_reader.hpp"

using namespace std;

int main()
{
    string command;
    getline(cin, command);

    
    get_string(command);
    
    

    return 0;
}
//g++ -o app test.cpp