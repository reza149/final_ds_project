#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
#include<vector>

#include"command_reader.hpp"
#include"wold_maker.hpp"
#include"object.hpp"
#include"sh_external_path.hpp"

using namespace std;

void func(vector <int> * temp)
{
    for(int i = 0; i < 9; i++)
    {
        (*temp).push_back(i);
    }   
}

void func2(vector <int>  temp)
{
    for(int i = 0; i < 9; i++)
    {
        temp.push_back(i);
    }   
}

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

void func_t()
{
    int help = 0;

    help++;

    cout << help << endl;
}

void road_create_name_cutter(string * galaxy_name, string * node_name , string name)
{
    cout << "fuck2" << endl;
    cout << name << endl; 
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
            cout << (*galaxy_name) << endl;
        }
        if(point_flag == true)
        {
            if(name[i] != '.')
            {
                (*node_name) = (*node_name) + name[i];
                cout << (*node_name) << endl;
            }
        }
    }
}

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
    cout << (*o_galaxy) << (*o_node) << endl;
    for(int i = half_index + 3; i < address.size(); i++)
    {
        help2 = help2 + address[i];
    }
    cout << help2 << endl;
    road_create_name_cutter(d_galaxy, d_node, help2);
    cout << (*d_galaxy) << (*d_node) << endl;
}

void func50(int * help)
{
    (*help) = (*help) + 5; 
}

void func45(int * help)
{
    func50(help);
}

int my_stoi(string inp)
{
    int conv;
    int sum = 0;
    for(int i = 0; i < inp.size(); i++)
    {
        conv = inp[i];
        sum = sum + conv;
    }
    return sum;
}



int main()
{
    vector <int> test;

    string o_galaxy_name;
    string * o_galaxy_name_ptr = &o_galaxy_name;
    string o_node_name;
    string * o_node_name_ptr = &o_node_name;

    string d_galaxy_name;
    string * d_galaxy_name_ptr = &d_galaxy_name;
    string d_node_name;
    string * d_node_name_ptr = &d_node_name;

    //find_address_cutter("AS4.W->AS4.X", o_galaxy_name_ptr, o_node_name_ptr, d_galaxy_name_ptr, d_node_name_ptr);

    //cout << "o_g name = " << o_galaxy_name << " o_d name = " << o_node_name << " d_g name = " << d_galaxy_name << " d_d name = " << d_node_name << endl;
    
    o_galaxy_name = "reza";

    o_galaxy_name.clear();

    cout << my_stoi(o_galaxy_name << endl;

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct dijkstra_unit dij_u;

struct dijkstra_unit
{
    string node_name;
    int cost;
    string path;
};



void dijkstra(universe world, int o_galaxy_index, int o_node_index)
{
    int graph_size = world.galaxy_list[o_galaxy_index].node_list.size() - 1;
    int graph[graph_size][graph_size];

    for(int i = 0; i < graph_size; i++)
    {
        for(int j = 0; j < graph_size; j++)
        {
            graph[i][j] = 0;
        }
    }

    for(int i = 0; i < graph_size; i++)
    {
        for(int j = i + 1; j < graph_size; j++)
        {
            if(world.galaxy_list[o_galaxy_index].node_list[i].is_there_road(world.galaxy_list[o_galaxy_index].node_list[j].get_name()))
            {
                graph[i][j] = 1;
            }
        }
    }

    for(int i = 0; i < graph_size; i++)
    {
        for(int j = 0; j < graph_size; j++)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

}


//g++ -o ap2 test2.cpp