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

//recognising the type of command
sp get_string(string command)
{
    sp f_out;

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
        if(command[i] == create_key[st_create_index])
        {
            st_create_index++;
        }
        if(st_create_index == (create_key.size() - 1))
        {
            create_flag = true;
            f_out.create_flag = create_flag;
        }

        //finding find word
        if(command[i] == find_key[st_find_index])
        {
            st_find_index++;
        }
        if(st_find_index == (find_key.size() - 1))
        {
            find_flag = true;
            f_out.find_flag = find_flag;
        }

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
        if(command[i] == node_key[st_node_index])
        {
            st_node_index++;
        }
        if(st_node_index == (node_key.size() - 1))
        {
            node_flag = true;
            f_out.node_flag = node_flag;
        }

        //finding galaxy word
        if(command[i] == galaxy_key[st_galaxy_index])
        {
            st_galaxy_index++;
        }
        if(st_galaxy_index == (galaxy_key.size() - 1))
        {
            galaxy_flag = true;
            f_out.galaxy_flag = galaxy_flag;
        }

        //finding road word
        if(command[i] == road_key[st_road_index])
        {
            st_road_index++;
        }
        if(st_road_index == (road_key.size() - 1))
        {
            road_flag = true;
            f_out.road_flag = road_flag;
        }

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