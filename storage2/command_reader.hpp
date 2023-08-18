#ifndef COMMAND_READER_HPP
#define COMMAND_READER_HPP

#include<iostream>
#include<string>

using namespace std;
typedef struct package sp;

struct package
{
    bool create_flag;
    bool find_flag;
    bool node_flag;
    bool galaxy_flag;
    bool road_flag;
    string name;
    string name2;
    string address;
    string node_type;
    string id;
    string cost;
    string galaxy_name;
};

//put package in default state
sp default_func(sp inp)
{
    inp.find_flag = false;
    inp.galaxy_flag = false;
    inp.node_flag = false;
    inp.road_flag = false;
    inp.create_flag = false;
    return inp;
}

//finding a word in a string
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

sp command_flag(sp inp, string inp2)
{
    
}



//extracting information from command
sp get_command_inf(string command)
{
    sp f_out;
    f_out = default_func(f_out);

    string create_key = "create";
    string find_key = "find";
    string node_key = "node";
    string galaxy_key = "galaxy";
    string road_key = "road";

    bool create_flag = false;
    bool find_flag = false;
    bool node_flag = false;
    bool galaxy_flag = false;
    bool road_flag = false;

    int st_create_index = 0;
    int st_find_index = 0;
    int st_node_index = 0;
    int st_galaxy_index = 0;
    int st_road_index = 0;

    string name;
    string address;
    string node_type;
    string id;
    string cost;

    int help;
    char help2 = 39;


    //finding words in command
    for(int i = 0; i < command.size(); i++)
    {
        //finding create word
        create_flag = word_finder(command, "create ");

        //finding find word
        find_flag = word_finder(command, "find ");

        //extracting  the address
        if((command[i - 1] == ' ') && (find_flag == true))
        {
            help = i;
            while(help < command.size())
            {
                address = address + command[help];
                help++;
            }
            f_out.address = address;
        }

        //extracting the name of node or galaxy or strat node of road
        if((command[i - 1] == '(') && (create_flag == true) && (road_flag == false))
        {
            help = i;
            while((command[help] != ':') && (command[help] != ')'))
            {
                name = name + command[help];
                help++;
            }
            f_out.name = name;
        }


        //finding node word
        node_flag = word_finder(command, "node, ");

        //finding galaxy word
        galaxy_flag = word_finder(command, "galaxy, ");

        //finding road word
        node_flag = word_finder(command, ":road ");

        //extracting node type
        if((command[i - 3] == 'e') && (node_flag == true) && (command[i] == help2))
        {
            help = i + 1;
            while(command[help] != help2)
            {
                node_type = node_type + command[help];
                help++;
            }
            f_out.node_type = node_type;
        }

        //extracting node or galaxy id
        if((command[i - 3] == 'd') && (create_flag == true) && (command[i] == help2))
        {
            help = i + 1;
            while(command[help] != help2)
            {
                id = id + command[help];
                help++;
            }
            f_out.id = id;
        }

        //extracting road cost
        if((command[i - 1] == 't') && (road_flag == true) && (command[i] == ':'))
        {
            help = i + 1;
            while(command[help] != '}')
            {
                cost = cost + command[help];
                help++;
            }
            f_out.cost = cost;
        }

        //extracting destination name
        if((command[i] == '(') && (road_flag == true))
        {
            help = i + 1;
            name.clear();
            while(command[help] != ')')
            {
                name = name + command[help];
                help++;
            }
            f_out.name2 = name;
        }

        //extracting galaxy name
        if((command[i] == help2) && (command[i - 3] == 'y'))
        {
            help = i + 1;
            name.clear();
            while(command[help] != help2)
            {
                name = name + command[help];
                help++;
            }
            f_out.galaxy_name = name;
        }
    }

    return f_out;
}


void show_package(sp inp)
{
    cout << boolalpha << "create_flag = " << inp.create_flag << endl;
    cout << boolalpha << "find_flsg = " << inp.find_flag << endl;
    cout << boolalpha << "node_flag = " << inp.node_flag << endl;
    cout << boolalpha << "galaxy_flag = " << inp.galaxy_flag << endl;
    cout << boolalpha << "road_flag = " << inp.road_flag << endl;
}

#endif