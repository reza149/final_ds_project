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
    string node_type;
    string id;
    string cost;
    string galaxy_name;

    //address for road mode
    string origin_galaxy;
    string origin_node;
    string destination_galaxy;
    string destination_node;
};

//put package in default state
sp default_func(sp inp)
{
    inp.find_flag = false;
    inp.galaxy_flag = false;
    inp.node_flag = false;
    inp.road_flag = false;
    inp.create_flag = false;
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

    return inp;
}

//address separator
void ad_cuter(sp * f_out_ptr, string address)
{
    string origin_galaxy_name;
    string origin_node_name;
    string destination_galaxy_name;
    string destination_node_name;

    bool point_flag = false;

    int i;

    for(i = 0; address[i] != '>'; i++)
    {
        if(address[i] == '.')
        {
            point_flag = true;
        }

        if(point_flag == false)
        {
            origin_galaxy_name = origin_galaxy_name + address[i];
        }

        if(point_flag == true)
        {
            origin_node_name = origin_node_name + address[i];
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
            ad_cuter(f_out_ptr, address);
        }

        //extracting the name of node or galaxy or strat node of road
        if((command[i - 1] == '(') && (f_out.create_flag == true) && (f_out.road_flag == false))
        {
            help = i;
            while((command[help] != ':') && (command[help] != ')'))
            {
                name = name + command[help];
                help++;
            }
            f_out.name = name;
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

        //extracting destination name
        if((command[i] == '(') && (f_out.road_flag == true))
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
    cout << "name = " << inp.name << endl;
    cout << "name2 = " << inp.name2 << endl;
    cout << "node type = " << inp.node_type << endl;
    cout << "id = " << inp.id << endl;
    cout << "galaxy name = " << inp.galaxy_name << endl;
    cout << "\n----------------------------\n";
}

#endif