#include<iostream>
#include<string>
#include<fstream>

#include"command_reader.hpp"
#include"wold_maker.hpp"
#include"object.hpp"

using namespace std;



int main()
{
    vector <string> command;
    vector <string> * command_ptr = &command; 

    universe world;
    universe * world_ptr = &world;

    sp command_inf;

    
    read_file_command(command_ptr);

    
    for(int i = 0; i < command.size(); i++)
    {
        command_inf = get_command_inf(command[i]);
        builder(world_ptr, command_inf, command_type_identifier(command_inf));
    }
    

   /*
   for(int k = 0; k < command.size(); k++)
   {
        cout << command[k] << endl;
   }
   */
   world.show_universe();
   
    

    return 0;
}
//g++ -o app test.cpp