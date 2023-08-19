#ifndef COMMAND_READER_HPP
#define COMMAND_READER_HPP

#include<iostream>
#include<string>

using namespace std;
typedef struct package sp;

void road_create_name_cutter(string * galaxy_name, string * node_name ,string name);

struct package
{
    bool create_flag;
    bool find_flag;
    bool node_flag;
    bool galaxy_flag;
    bool road_flag;
    //user handling flags
    bool build_flag;
    bool exit_flag;
    bool show_world_flag;
    string name;
    string name2;
    string node_type;
    string address;
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
    inp.build_flag = false;
    inp.show_world_flag = false;
    inp.name = "&";
    inp.name2 = "&";
    inp.node_type = "&";
    inp.id = "&";
    inp.galaxy_name = "&";
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

sp command_flag(sp inp, string command)
{
    //finding create word
    inp.create_flag = word_finder(command, "create ");

    //finding find word
    inp.find_flag = word_finder(command, "find ");

    //finding node word
    inp.node_flag = word_finder(command, " node,");

    //finding galaxy word
    inp.galaxy_flag = word_finder(command, "galaxy, ");

    //finding road word
    inp.road_flag = word_finder(command, ":road ");

    //finding build word
    inp.build_flag = word_finder(command, "build world");

    //finding exit word
    inp.exit_flag = word_finder(command, "exit");

    //finding show world
    inp.show_world_flag = word_finder(command, "show world");

    return inp;
}

//find mode address separator
void find_address_cutter(string address, string * o_galaxy, string * o_node, string * d_galaxy, string * d_node)
{
    string help;
    string help2;

    bool point_flag = false;
    int half_index;


    for(int i = 0; address[i] != '-'; i++)
    {
        help = help + address[i];
        half_index = i;
    }
    road_create_name_cutter(o_galaxy, o_node, help);
    for(int i = half_index + 3; i < address.size(); i++)
    {
        help2 = help2 + address[i];
    }
    road_create_name_cutter(d_galaxy, d_node, help2);
}

//road create mode name separator 
void road_create_name_cutter(string * galaxy_name, string * node_name ,string name)
{
    bool point_flag = false;
    for(int i = 0; i < name.size(); i++)
    {
        if(name[i] == '.')
        {
            point_flag = true;
        }
        if(point_flag == false)
        {
            (*galaxy_name) = (*galaxy_name) + name[i];
        }
        if(point_flag == true)
        {
            if(name[i] != '.')
            {
                (*node_name) = (*node_name) + name[i];
            }
        }
    }
}

//extracting information from command
sp get_command_inf(string command)
{
    sp f_out;
    sp * f_out_ptr = &f_out;
    f_out = default_func(f_out);

    f_out = command_flag(f_out, command);

    string name;
    string address;
    string node_type;
    string id;
    string cost;

    int help;
    char help2 = 39;
    bool name_flag = false;

    //extracting from the command
    for(int i = 0; i < command.size(); i++)
    {
        //extracting  the address
        if((command[i - 1] == ' ') && (f_out.find_flag == true))
        {
            help = i;
            while(help < command.size())
            {
                address = address + command[help];
                help++;
            }
            f_out.address = address;
        }

        //extracting the name of node or galaxy 
        //or strat node of road
        //and end node of road
        if((command[i - 1] == '(') && (f_out.create_flag == true))
        {
            help = i;
            while((command[help] != ':') && (command[help] != ')'))
            {
                name = name + command[help];
                help++;
            }
            //extracting start node name in create road mode
            if(name_flag == false)
            {
                f_out.name = name;
                name.clear();
                name_flag = true;
            }
            //extracting end node name in create road mode
            else
            {
                f_out.name2 = name;
                name.clear();
            }
        }

        //extracting node type
        if((command[i - 3] == 'e') && (f_out.node_flag == true) && (command[i] == help2))
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
        if((command[i - 3] == 'd') && (f_out.create_flag == true) && (command[i] == help2))
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
        if((command[i - 1] == 't') && (f_out.road_flag == true) && (command[i] == ':'))
        {
            help = i + 1;
            while(command[help] != '}')
            {
                cost = cost + command[help];
                help++;
            }
            f_out.cost = cost;
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
    cout << "name = " << inp.name << endl;
    cout << "name2 = " << inp.name2 << endl;
    cout << "node type = " << inp.node_type << endl;
    cout << "id = " << inp.id << endl;
    cout << "galaxy name = " << inp.galaxy_name << endl;
    cout << "\n----------------------------\n";
}

#endif