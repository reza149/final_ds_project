#include<iostream>
#include<string>
#include<fstream>

#include"command_reader.hpp"
#include"wold_maker.hpp"
#include"object.hpp"
#include"sh_external_path.hpp"

using namespace std;

void print_command_struct()
{
    cout << "*******************************" << endl;
    cout << "the command struct of this app is:\n"
         << "create (A: node, {id: '1', type: 'bg or nonbg', galaxy: 'name'})\n"
         << "creat (ac: galaxy, {id: '23'})\n"
         << "create (A) - [:road {cost:50}] -> (B)\n"
         << "find AS4.W->AS4.X\n"
         << "build world\n"
         << "show world\n"
         << "exit" << endl;
    cout << "*******************************" << endl;
}



int main()
{
    //command vector for reading command from the file
    vector <string> file_command;
    vector <string> * file_command_ptr = &file_command;
    //world object
    universe world;
    universe * world_ptr = &world;
    //package 
    sp command_inf;
    //stream command is for user command
    string stream_command;
    //store stream command type
    int type_command;

    cout << "welcome to the app for using this app witre (start)" << endl;
    cin >> stream_command;
    if(stream_command == "start")
    {
        print_command_struct();
        while(type_command != 7)
        {
            //cin.ignore();
            getline(cin, stream_command);
            command_inf = get_command_inf(stream_command);
            type_command = command_type_identifier(command_inf);
            if(type_command == 0)
            {
                cout << "invalied input" << endl;
            }
            if((type_command != 0) && (type_command != 7))
            {
                //creating road or node or galaxy command
                if(type_command <= 3)
                {
                    command_inf = get_command_inf(stream_command);
                    builder(world_ptr, command_inf, type_command);
                }
                //find command 
                if(type_command == 4)
                {
                    command_inf = get_command_inf(stream_command);
                    find_path(command_inf, world);
                }
                //build world command
                if(type_command == 5)
                {
                    read_file_command(file_command_ptr);
                    for(int i = 0; i < file_command.size(); i++)
                    {
                        command_inf = get_command_inf(file_command[i]);
                        builder(world_ptr, command_inf, command_type_identifier(command_inf));
                    }
                }
                //show world command
                if(type_command == 6)
                {
                    world.show_universe();
                }
            }
        }
        
    }
    else
    {
        cout << "invalied input" << endl;
        
    }
    

   /*
   for(int k = 0; k < command.size(); k++)
   {
        cout << command[k] << endl;
   }
   */


  //world.show_universe();
   
    

    return 0;
}
//g++ -o app main.cpp