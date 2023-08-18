#ifndef OBJECT_HPP
#define OBJECT_HPP

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<queue>
#include<climits>
#include<algorithm>

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
    node(){}
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
    vector<node> shortest_path(vector<node>, node, node);
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


void findShortestPath(vector<node>& graph, node& startNode, node& endNode)
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
