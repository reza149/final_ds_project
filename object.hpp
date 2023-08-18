#ifndef OBJECT_HPP
#define OBJECT_HPP

#include<iostream>
#include<string>
#include<vector>

#include"object.hpp"

using namespace std;
typedef struct road road;

struct road
{
    bool internal_flag;
    bool external_flag;

    string origin_node_name;
    string origin_galaxy_name;

    string destination_node_name;
    string destination_galaxy_name;

    int cost;
};

///////////////////////////////////////////////////////////////////////
class node
{
    public:
    vector <road> road_list;

    void set_name_id_galaxy(string input, string number, string input2);
    void print_name_id();
    string get_name();

    private:
    string name;
    string id;
    string type;
};

string node::get_name()
{
    return name;
}

void node::print_name_id()
{
    cout << "node name: " << name << " " << "id = " << id << "*** ";
}

void node::set_name_id_galaxy(string input, string number, string input2)
{
    name = input;
    id = number;
    type = input2;
}

///////////////////////////////////////////////////////////////////////
class galaxy
{
    public:
    vector <node> node_list;

    void set_name_id(string input, string number);
    string get_name();

    private:
    string name;
    string id;
};

string galaxy::get_name()
{
    return name;
}

void galaxy::set_name_id(string input, string number)
{
    name = input;
    id = number;
}



///////////////////////////////////////////////////////////////////////
class universe
{
    public:
    vector <galaxy> galaxy_list;
    
    void show_universe();
};


//print all galaxies and nodes and  roads
void universe::show_universe()
{
    for(int i = 0; i < galaxy_list.size(); i++)
    {
        cout << galaxy_list[i].get_name() << endl;
        for(int j = 0; j < galaxy_list[i].node_list.size(); j++)
        {
            galaxy_list[i].node_list[j].print_name_id();
            for(int h = 0; h < galaxy_list[i].node_list[j].road_list.size(); h++)
            {
                if(galaxy_list[i].node_list[j].road_list[h].internal_flag == true)
                {
                    cout << "destination name = " 
                    << galaxy_list[i].node_list[j].road_list[h].destination_node_name 
                    << " cost = " << galaxy_list[i].node_list[j].road_list[h].cost << "*** ";
                }
                if(galaxy_list[i].node_list[j].road_list[h].external_flag == true)
                {
                    cout << "destination galaxy name = " << galaxy_list[i].node_list[j].road_list[h].destination_galaxy_name 
                    << " destination name = " << galaxy_list[i].node_list[j].road_list[h].destination_node_name 
                    << " cost = " <<  galaxy_list[i].node_list[j].road_list[h].cost << "*** ";                                         
                }
            }
            cout << endl;
        }
        cout << "\n\n";
    }
}





#endif