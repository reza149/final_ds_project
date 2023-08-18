#ifndef WORLD_MAKER_HPP
#define WORLD_MAKER_HPP

#include<iostream>
#include<fstream>

#include"command_reader.hpp"
#include"object.hpp"

using namespace std;



//stop reading protocol
bool stop_read(string inp)
{
    string end_word = "&&";
    int end_word_index = 0;
    int j = 0;
    for(int i = 0; i < inp.size(); i++)
    {
        if(inp[i] == end_word[j])
        {
            j++;
        }
        if(j == 2)
        {
            return true;
        }
    }
    return false;
}

//reading information of the command_list 
void read_file_command(vector <string> * command)
{
    fstream help;
    string help2;
    bool end_flag = false;

    help.open("./storage/help.txt", ios::in | ios:: out| ios:: app);

    help.seekg(0, ios::beg);

    while((!help.eof()) && (end_flag == false))
    {
        getline(help, help2);
        end_flag = stop_read(help2);
        if(end_flag == false)
        {
            (*command).push_back(help2);
        }
    }

    help.close();
}

int command_type_identifier(sp command)
{
    //creating node mode
    if((command.create_flag == true) && (command.node_flag == true))
    {
        return 1;
    }

    //crating galaxy mode
    if((command.create_flag == true) && (command.galaxy_flag == true) && (command.node_flag == false))
    {
        return 2;
    }

    //creating road mode
    if((command.create_flag == true) && (command.road_flag == true))
    {
        return 3;
    }

    //find command
    if((command.find_flag == true))
    {
        return 4;
    }

    return 0;
}


void builder(universe * world, sp build_map, int command_type)
{
    node node_temp;
    galaxy galaxy_temp;
    road road_temp;
    switch(command_type)
    {
        //creating node mode
        case 1:
        node_temp.set_name_id_galaxy(build_map.name, build_map.id, build_map.galaxy_name);

        for(int i = 0; i < (*world).galaxy_list.size(); i++)
        {
            if((*world).galaxy_list[i].get_name() == build_map.galaxy_name)
            {
                (*world).galaxy_list[i].node_list.push_back(node_temp);
            }   
        }

        break;

        //crating galaxy mode
        case 2:
        galaxy_temp.set_name_id(build_map.name, build_map.id);
        (*world).galaxy_list.push_back(galaxy_temp);

        break;

        //creating road mode
        case 3:
        //finding galaxy
        for(int i = 0; i < (*world).galaxy_list.size(); i++)
        {
            if((*world).galaxy_list[i].get_name() == build_map.galaxy_name)
            {
                //finding node
                for(int j = 0; j < (*world).galaxy_list[i].node_list.size(); j++)
                {
                    if((*world).galaxy_list[i].node_list[j].get_name() == build_map.name)
                    {   
                        //create external road
                        if(build_map.galaxy_name != (*world).galaxy_list[i].get_name())
                        {
                            road_temp.external_flag = true;
                            road_temp.internal_flag = false;

                            road_temp.cost = stoi(build_map.cost);

                            road_temp.destination_galaxy_name = build_map.galaxy_name;
                            road_temp.destination_node_name = build_map.name2;

                            road_temp.origin_node_name = build_map.name;
                            road_temp.origin_galaxy_name = 
                        }
                    }
                }
            }   
        }


        break;
    }

}







#endif