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
void dijkstra(universe world, int o_node_index, int o_galaxy_index, int d_node_index, int sum);
void ex_dijkstra(universe world, int o_galaxy_index, int d_galaxy_index, int o_node_index, int d_node_index);
void dijkstra_hot_potato(universe world, int o_node_index, int o_galaxy_index, int d_node_index, vector <int> bg_node, string * path_ptr, int * help2_index);
int dijkstra_between_galaxy(universe world, int o_node_index, int d_galaxy_index);
int dijkstra_just_cost(universe world, int o_node_index, int o_galaxy_index, int d_node_index);


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

    
    if(o_galaxy_name != d_galaxy_name)
    {
        ex_dijkstra(world, o_galaxy_index, d_galaxy_index, o_node_index, d_node_index);
    }
    if(o_galaxy_name == d_galaxy_name)
    {
        dijkstra(world, o_node_index, o_galaxy_index, d_node_index, 0);
    }
    
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
 
int printSolution(int dist[], int g_size, vector <int> parent, int d_node_index, int o_node_index, universe world, int galaxy_index, int sum)
{
    //cout << "Vertex   Distance from Source " << endl;
    vector <int> help;
    for (int i = 0; i < g_size; i++)
    {
        vector <int> path;
        int j = i;
        while(j != -1)
        {
            path.push_back(j);
            j = parent[j];
        }
        for(int h = path.size() - 1; h >= 0 ; h--)
        {
            if(i == d_node_index)
            {
                help.push_back(path[h]);
            }
        }
    }
    
   for(int i = 0; i < help.size(); i++)
   {
       if(i != (help.size() - 1))
       {
            cout << world.galaxy_list[galaxy_index].node_list[help[i]].get_name() << "->";
       }
       else
       {
            cout << world.galaxy_list[galaxy_index].node_list[help[i]].get_name() << " : ";
       }
   }
   cout << dist[d_node_index] + sum << endl;
   cout << endl;
    return 0;
}
 

void dijkstra(universe world, int o_node_index, int o_galaxy_index, int d_node_index, int sum)
{
    int g_size = world.galaxy_list[o_galaxy_index].node_list.size();
    int graph[g_size][g_size];
    int road_index;

    vector <int> path[g_size];
    vector <int> parent(g_size, -1);

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
            }
        }
    }

    int dist[g_size]; 
    bool sptSet[g_size]; 
    
 
    for (int i = 0; i < g_size; i++)
    {
        dist[i] = INT_MAX, sptSet[i] = false;
    }    
 
    
    dist[o_node_index] = 0;
 

    for (int count = 0; count < g_size - 1; count++) 
    {

        int u = minDistance(dist, sptSet, g_size, path);
 
        sptSet[u] = true;
 
        for (int v = 0; v < g_size; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
            
    }
 
    printSolution(dist, g_size, parent, d_node_index, o_node_index, world, o_galaxy_index, sum);
}

////////////////////////////////////////////////////////////////////////////////////////////

void ex_dijkstra(universe world, int o_galaxy_index, int d_galaxy_index, int o_node_index, int d_node_index)
{
    vector <int> o_bg_node_index;
    string path;
    string * path_ptr = &path;
    int sum = 0; // total cost
    int help2_index; // bg node of origin galaxy
    int * help2_index_ptr = &help2_index;
    int help_index;
    for(int i = 0; i < world.galaxy_list[o_galaxy_index].node_list.size(); i++)
    {
        if(world.galaxy_list[o_galaxy_index].node_list[i].get_type() == "bg")
        {
            o_bg_node_index.push_back(i);
        }
    }

    dijkstra_hot_potato(world, o_node_index, o_galaxy_index, d_node_index, o_bg_node_index, path_ptr, help2_index_ptr);

    sum = dijkstra_just_cost(world, o_node_index, o_galaxy_index, d_node_index);

    cout << path << "->";

    help_index = dijkstra_between_galaxy(world, help2_index, d_galaxy_index);

    dijkstra(world, help_index, d_galaxy_index, d_galaxy_index, sum);

}

////////////////////////////////////////////////////////////////////////////////////////////////////

string printSolution2(int dist[], int g_size, vector <int> parent, int d_node_index, int o_node_index, universe world, int galaxy_index)
{
    //cout << "Vertex   Distance from Source " << endl;
    string my_cout;
    my_cout.clear();
    vector <int> help;
    for (int i = 0; i < g_size; i++)
    {
        vector <int> path;
        int j = i;
        while(j != -1)
        {
            path.push_back(j);
            j = parent[j];
        }
        for(int h = path.size() - 1; h >= 0 ; h--)
        {
            if(i == d_node_index)
            {
                help.push_back(path[h]);
            }
        }
    }
    
   for(int i = 0; i < help.size(); i++)
   {
       if(i != (help.size() - 1))
       {
            //cout << world.galaxy_list[galaxy_index].node_list[help[i]].get_name() << "->";
            my_cout = my_cout + world.galaxy_list[galaxy_index].node_list[help[i]].get_name() + "->";
       }
       else
       {
            //cout << world.galaxy_list[galaxy_index].node_list[help[i]].get_name() << " : ";
            my_cout = my_cout + world.galaxy_list[galaxy_index].node_list[help[i]].get_name();
       }
   }

    return my_cout;
}
 

void dijkstra_hot_potato(universe world, int o_node_index, int o_galaxy_index, int d_node_index, vector <int> bg_node, string * path_ptr, int * help2_index)
{
    int g_size = world.galaxy_list[o_galaxy_index].node_list.size();
    int graph[g_size][g_size];
    int road_index;

    int short_way;
    int short_way_index;

    vector <int> path[g_size];
    vector <int> parent(g_size, -1);

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
                graph[i][j] = 1;
            }
        }
    }

    int dist[g_size]; 
    bool sptSet[g_size]; 
    
 
    for (int i = 0; i < g_size; i++)
    {
        dist[i] = INT_MAX, sptSet[i] = false;
    }    
 
    
    dist[o_node_index] = 0;
 

    for (int count = 0; count < g_size - 1; count++) 
    {

        int u = minDistance(dist, sptSet, g_size, path);
 
        sptSet[u] = true;
 
        for (int v = 0; v < g_size; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
            
    }

    short_way = dist[bg_node[0]];
    short_way_index = 0;
    for(int i = 1; i < bg_node.size(); i++)
    {
        if(short_way < dist[bg_node[i]])
        {
            short_way = dist[bg_node[i]];
            short_way_index = i;
        }
    }

    (*help2_index) = short_way_index;
    (*path_ptr) = printSolution2(dist, g_size, parent, short_way_index, o_node_index, world, o_galaxy_index);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      

int dijkstra_between_galaxy(universe world, int o_node_index, int d_galaxy_index)
{
    int g_size = world.external_node_list.size();
    int graph[g_size][g_size];
    int road_index;

    int short_way;
    int short_way_index;

    vector <int> path[g_size];
    vector <int> parent(g_size, -1);

    vector <int> o_galaxy_bg_node;
    for(int i = 0; i < world.galaxy_list[d_galaxy_index].node_list.size(); i++)
    {
        if(world.galaxy_list[d_galaxy_index].node_list[i].get_type() == "bg")
        {
            o_galaxy_bg_node.push_back(i);
        }
    }

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
            //road_index = world.galaxy_list[o_galaxy_index].node_list[i].is_there_road(world.galaxy_list[o_galaxy_index].node_list[j].get_name());
            road_index = world.external_node_list[i].is_there_road(world.external_node_list[j].get_name());
            if(road_index != -1)
            {
                graph[i][j] = world.external_node_list[j].road_list[road_index].cost;
            }
        }
    }

    int dist[g_size]; 
    bool sptSet[g_size]; 
    
 
    for (int i = 0; i < g_size; i++)
    {
        dist[i] = INT_MAX, sptSet[i] = false;
    }    
 
    
    dist[o_node_index] = 0;
 

    for (int count = 0; count < g_size - 1; count++) 
    {
        int u = minDistance(dist, sptSet, g_size, path);
 
        sptSet[u] = true;
 
        for (int v = 0; v < g_size; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }  
    }

    short_way = dist[o_galaxy_bg_node[0]];
    short_way_index = 0;
    for(int i = 1; i < o_galaxy_bg_node.size(); i++)
    {
        if(short_way < dist[o_galaxy_bg_node[i]])
        {
            short_way = dist[o_galaxy_bg_node[i]];
            short_way_index = i;
        }
    }

    return short_way_index;
}

////////////////////////////////////////////////////////////////////////////////////////////////
 
int dijkstra_just_cost(universe world, int o_node_index, int o_galaxy_index, int d_node_index)
{
    int g_size = world.galaxy_list[o_galaxy_index].node_list.size();
    int graph[g_size][g_size];
    int road_index;

    vector <int> path[g_size];
    vector <int> parent(g_size, -1);

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
            }
        }
    }

    int dist[g_size]; 
    bool sptSet[g_size]; 
    
 
    for (int i = 0; i < g_size; i++)
    {
        dist[i] = INT_MAX, sptSet[i] = false;
    }    
 
    
    dist[o_node_index] = 0;
 

    for (int count = 0; count < g_size - 1; count++) 
    {

        int u = minDistance(dist, sptSet, g_size, path);
 
        sptSet[u] = true;
 
        for (int v = 0; v < g_size; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
            
    }

    return dist[d_node_index];
}



#endif