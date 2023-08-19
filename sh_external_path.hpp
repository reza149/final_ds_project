#ifndef SH_EXTERNAL_PATH_HPP
#define SH_EXTERNAL_PATH_HPP

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<queue>
#include<climits>
#include<algorithm>

#include"command_reader.hpp"
#include"wold_maker.hpp"
#include"object.hpp"

void findShortestPath(vector<node> graph, node startNode, node endNode);
void dijkstra(universe world, int o_galaxy_index, int o_node_index);


void find_path(sp command_inf, universe world)
{
    string o_galaxy_name;
    string * o_galaxy_name_ptr = &o_galaxy_name;
    string o_node_name;
    string * o_node_name_ptr = &o_node_name;

    string d_galaxy_name;
    string * d_galaxy_name_ptr = &d_galaxy_name;
    string d_node_name;
    string * d_node_name_ptr = &d_node_name;
    

    find_address_cutter(command_inf.address, o_galaxy_name_ptr, o_node_name_ptr, d_galaxy_name_ptr, d_node_name_ptr);

    int o_galaxy_index = world.search_galaxy(o_galaxy_name);
    int o_node_index = world.search_node(o_node_name, o_galaxy_index);
    int d_galaxy_index = world.search_galaxy(d_galaxy_name);
    int d_node_index = world.search_node(d_node_name, d_galaxy_index);

    dijkstra(world, o_node_index, o_galaxy_index);

    //cout << "o_g name = " << o_galaxy_name << "o_d name" << o_node_name << "d_g name = " << d_galaxy_name << "d_d name" << d_node_name << endl;

    if(o_galaxy_name != d_galaxy_name)
    {

    }
    if(o_galaxy_name == d_galaxy_name)
    {
        //world.galaxy_list[o_galaxy_index].find_shortest(world.galaxy_list[o_galaxy_index].node_list[o_node_index], world.galaxy_list[d_galaxy_index].node_list[d_node_index]);
    }
    
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

void dijkstra_my(universe world, int o_galaxy_index, int o_node_index)
{
    int graph_size = world.galaxy_list[o_galaxy_index].node_list.size();
    int graph[graph_size][graph_size];
    int road_index;

    for(int i = 0; i < graph_size; i++)
    {
        for(int j = 0; j < graph_size; j++)
        {
            graph[i][j] = 0;
        }
    }
    /*
    for(int i = 0; i < world.galaxy_list[o_galaxy_index].node_list.size(); i++)
    {
        cout << i << " = " << world.galaxy_list[o_galaxy_index].node_list[i].get_name() << endl;
    }
    */
    for(int i = 0; i < graph_size; i++)
    {
        for(int j = 0; j < graph_size; j++)
        {
            road_index = world.galaxy_list[o_galaxy_index].node_list[i].is_there_road(world.galaxy_list[o_galaxy_index].node_list[j].get_name());
            if(road_index != -1)
            {
                graph[i][j] = world.galaxy_list[o_galaxy_index].node_list[i].road_list[road_index].cost;
                //cout << graph[i][j] << endl;
            }
        }
    }
    /*
    for(int i = 0; i < graph_size; i++)
    {
        for(int j = 0; j < graph_size; j++)
        {
            cout << graph[i][j] << "\t";
        }
        cout << endl;
    }
    */
}

/////////////////////////////////////////////////////////////////////////////

int minDistance(int dist[], bool sptSet[], int g_size, vector <int> path[])
{
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < g_size; v++)
    {
        if (sptSet[v] == false && dist[v] <= min)
        {
            min = dist[v], min_index = v;
            //path[v].push_back(v);
        }
    }
        
    return min_index;
}
 
int printSolution(int dist[], int g_size, vector <int> path[])
{
    cout << "Vertex   Distance from Source " << endl;
    for (int i = 0; i < g_size; i++)
    {
        cout << i + 1 << " = " << dist[i] << " path = ";
        for(int j = 0; j < path[i].size(); j++)
        {
            cout << path[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
 

void dijkstra(universe world, int src, int o_galaxy_index)
{
    int g_size = world.galaxy_list[o_galaxy_index].node_list.size();
    int graph[g_size][g_size];
    int road_index;

    vector <int> path[g_size];

    for(int i = 0; i < g_size; i++)
    {
        for(int j = 0; j < g_size; j++)
        {
            graph[i][j] = 0;
        }
    }
    for(int i = 0; i < g_size; i++)
    {
        for(int j = 0; j < g_size; j++)
        {
            road_index = world.galaxy_list[o_galaxy_index].node_list[i].is_there_road(world.galaxy_list[o_galaxy_index].node_list[j].get_name());
            if(road_index != -1)
            {
                graph[i][j] = world.galaxy_list[o_galaxy_index].node_list[i].road_list[road_index].cost;
                //cout << graph[i][j] << endl;
            }
        }
    }

    int dist[g_size]; 
    bool sptSet[g_size]; 
    
 
    for (int i = 0; i < g_size; i++)
    {
        dist[i] = INT_MAX, sptSet[i] = false;
    }    
 
    
    dist[src] = 0;
 
    
    for (int count = 0; count < g_size - 1; count++) 
    {

        int u = minDistance(dist, sptSet, g_size, path);
 
        sptSet[u] = true;
 
        for (int v = 0; v < g_size; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                path[v].push_back(v + 1);
            }
        }
            
    }
 
    printSolution(dist, g_size, path);
}





#endif