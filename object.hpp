#ifndef OBJECT_HPP
#define OBJECT_HPP

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>

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

    void set_name_id_type(string input, string number, string input2);
    void print_name_id();
    string get_name();
    string get_type();
    int is_there_road(string name);

    private:
    string name;
    string id;
    string type;
};

string node::get_type()
{
    return type;
}

string node::get_name()
{
    return name;
}

void node::print_name_id()
{
    cout << "node name: " << name << " " << "id = " << id << "*** ";
}

void node::set_name_id_type(string input, string number, string input2)
{
    name = input;
    id = number;
    type = input2;
}

int node::is_there_road(string name)
{
    for(int i = 0; i < road_list.size(); i++)
    {
        if(road_list[i].destination_node_name == name)
        {
            return i;
        }
    }
    return -1;
}

///////////////////////////////////////////////////////////////////////
class galaxy
{
    public:
    vector <node> node_list;

    void set_name_id(string input, string number);
    string get_name();
    //void find_shortest(node strart, node end);
    //int find_node(string name);

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
    vector <node> external_node_list;

    int search_galaxy(string galaxy_name);
    int search_node(string node_name, int galaxy_index);

    void external_graph_maker();
    void show_universe();
};

//returning the index of the galaxy
int universe::search_galaxy(string galaxy_name)
{
    for(int i = 0; i < galaxy_list.size(); i++)
    {
        if(galaxy_name == galaxy_list[i].get_name())
        {
            return i;
        }
    }
    return -1;
}

//returning the index of the node
int universe::search_node(string node_name, int galaxy_index)
{
    for(int i = 0; i < galaxy_list[galaxy_index].node_list.size(); i++)
    {
        if(galaxy_list[galaxy_index].node_list[i].get_name() == node_name)
        {
            return i;
        }
    }
    return -1;
}

//making external graph
void universe::external_graph_maker()
{
    node temp;
    for(int i = 0; i < galaxy_list.size(); i++)
    {
        for(int j = 0; j < galaxy_list[i].node_list.size(); j++)
        {
            temp = galaxy_list[i].node_list[j];
            external_node_list.push_back(temp);
        }
    }
}



//print all galaxies and nodes and  roads
void universe::show_universe()
{
    cout << "fuck" << endl;
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
                   cout << "internal(nonbg) : " 
                   << galaxy_list[i].node_list[j].road_list[h].origin_node_name 
                   << "-> " << galaxy_list[i].node_list[j].road_list[h].destination_node_name 
                   << " cost = " << galaxy_list[i].node_list[j].road_list[h].cost
                   << " ** ";
                }
                if(galaxy_list[i].node_list[j].road_list[h].external_flag == true)
                {
                    cout << "external(bg) : " 
                   << galaxy_list[i].node_list[j].road_list[h].origin_node_name 
                   << "-> " << galaxy_list[i].node_list[j].road_list[h].destination_node_name 
                   << " cost = " << galaxy_list[i].node_list[j].road_list[h].cost
                   << " ** ";                                  
                }
            }
            cout << endl;
        }
        cout << "\n\n";
    }
}


#endif
