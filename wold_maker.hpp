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

    //buil world command
    if(command.build_flag == true)
    {
        return 5;
    }

    //show world command
    if(command.show_world_flag == true)
    {
        return 6;
    }

    //exit command
    if(command.exit_flag == true)
    {
        return 7;
    }

    return 0;
}


void builder(universe * world, sp build_map, int command_type)
{
    node node_temp;
    galaxy galaxy_temp;
    road road_temp;

    string origin_galaxy;
    string * origin_galaxy_ptr = &origin_galaxy;
    int origin_galaxy_index;
    string origin_node;
    string * origin_node_ptr = &origin_node;
    int origin_node_index;

    string destination_galaxy;
    string * destination_galaxy_ptr = &destination_galaxy;
    int destination_galaxy_index;
    string destination_node;
    string * destination_node_ptr = &destination_node;
    int destination_node_index;

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

        //extracting galaxy name and node name of origin
        road_create_name_cutter(origin_galaxy_ptr, origin_node_ptr, build_map.name);
        //extracting galaxy name and node name of destination 
        road_create_name_cutter(destination_galaxy_ptr, destination_node_ptr, build_map.name2);

        //finding origin galaxy
        origin_galaxy_index = (*world).search_galaxy(origin_galaxy);
        origin_node_index = (*world).search_node(origin_node, origin_galaxy_index);

        //finding destination galaxy
        destination_galaxy_index = (*world).search_galaxy(destination_galaxy);
        destination_node_index = (*world).search_node(destination_node, destination_galaxy_index);
        /*
        cout << "origin galaxy name = " << origin_galaxy << " index = " << origin_galaxy_index << " ";
        cout << "origin node name = " << origin_node << " index = " << origin_node_index << endl;
        cout << "destination galaxy name = " << destination_galaxy << " index = " << destination_galaxy_index << " ";
        cout << "destination node name = " << destination_node << " index = " << destination_node_index << endl;
        */
        //create external road
        if(origin_galaxy != destination_galaxy)
        {
            road_temp.external_flag = true;
            road_temp.internal_flag = false;
        }
        //create internal road
        else
        {
            road_temp.external_flag = false;
            road_temp.internal_flag = true;
        }

        //initialize road
        road_temp.cost = stoi(build_map.cost);

        road_temp.destination_galaxy_name = destination_galaxy;
        road_temp.destination_node_name = destination_node;
        string help1;

        road_temp.origin_node_name = origin_node;
        road_temp.origin_galaxy_name = origin_galaxy;
        string help2;

        //putting road in the origin node
        (*world).galaxy_list[origin_galaxy_index].node_list[origin_node_index].road_list.push_back(road_temp);

        //changing origin and destination to store in the another node
        help1 = road_temp.origin_galaxy_name;
        road_temp.origin_galaxy_name = road_temp.destination_galaxy_name;
        road_temp.destination_galaxy_name = help1;

        help2 = road_temp.origin_node_name;
        road_temp.origin_node_name = road_temp.destination_node_name;
        road_temp.destination_node_name = help2;

        //putting road in the destination node
        (*world).galaxy_list[destination_galaxy_index].node_list[destination_node_index].road_list.push_back(road_temp);


        break;
    }

}







#endif