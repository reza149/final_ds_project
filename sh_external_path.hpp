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

    //cout << "o_g name = " << o_galaxy_name << "o_d name" << o_node_name << "d_g name = " << d_galaxy_name << "d_d name" << d_node_name << endl;

    if(o_galaxy_name != d_galaxy_name)
    {

    }

    if(o_galaxy_name == d_galaxy_name)
    {
        findShortestPath(world.galaxy_list[o_galaxy_index].node_list,  world.galaxy_list[o_galaxy_index].node_list[o_node_index], world.galaxy_list[d_galaxy_index].node_list[d_node_index]);
    }
    
}


void findShortestPath(vector<node> graph, node startNode, node endNode)
{
    int n = graph.size();
    vector<int> distance(n, INT_MAX); // Distance from start node to each node
    vector<int> prev(n, -1); // Previous node in the shortest path

    // Custom comparator for the priority queue
    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp); // Min heap for Dijkstra's algorithm

    // Initialize the distance of the start node to 0
    distance[stoi(startNode.get_name())] = 0;

    // Push the start node to the priority queue
    pq.push(make_pair(stoi(startNode.get_name()), 0));

    while (!pq.empty())
    {
        // Get the node with the minimum distance from the priority queue
        int currNode = pq.top().first;
        int currDist = pq.top().second;
        pq.pop();

        // If the current distance is greater than the calculated distance, skip the node
        if (currDist > distance[currNode])
            continue;

        // Iterate through all the roads from the current node
        for (const road& r : graph[currNode].road_list)
        {
            // Calculate the distance to the neighboring node
            int neighborNode = stoi(r.destination_node_name);
            int neighborDist = currDist + r.cost;

            // If the calculated distance is less than the current distance, update the distance and previous node
            if (neighborDist < distance[neighborNode])
            {
                distance[neighborNode] = neighborDist;
                prev[neighborNode] = currNode;
                pq.push(make_pair(neighborNode, neighborDist));
            }
        }
    }

    // Check if a path exists from the start node to the end node
    if (prev[stoi(endNode.get_name())] == -1)
    {
        cout << "No path exists between the nodes." << endl;
        return;
    }

    // Reconstruct the shortest path
    vector<int> path;
    int currentNode = stoi(endNode.get_name());
    while (currentNode != -1)
    {
        path.push_back(currentNode);
        currentNode = prev[currentNode];
    }
    reverse(path.begin(), path.end());

    // Print the shortest path
    cout << "Shortest path: ";
    for (int i : path)
    {
        cout << i << " ";
    }
    cout << endl;
}




#endif