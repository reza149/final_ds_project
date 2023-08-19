#ifndef OBJECT_HPP
#define OBJECT_HPP

#include<iostream>
#include<string>
#include<vector>
#include<map>
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
    void find_shortest(node ,node);
    int find_node(string);

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


void galaxy :: find_shortest(node start ,node end_node)
{
    auto it = find(node_list.begin() ,node_list.end() ,start);


    if (it == node_list.end())
    {
        cerr << "Can Not Find Node" << endl;
        return ;
    }

    map<int ,string> temp ;
    map<string ,int> answer ;
    string last_str ;
    int last_cost ;

    for (size_t i = 0; i < start.road_list.size() ; i++)
    {
        temp[start.road_list[i].cost] = start.road_list[i].destination_node_name;
        answer[start.road_list[i].destination_node_name] = start.road_list[i].cost ;

        sort(temp.begin() ,temp.end());
    }

    int index = it - node_list.begin() ;

    if (index + 1 > node_list.size())
    {
        cerr << "Invalid Position" << endl;
        return ;
    }

    while (true)
    {
        index = find_node(temp.begin()->second);
        last_str = temp.begin()->second;
        last_cost = temp.begin()->first;
        temp.erase(temp.begin()->first);

        

        for (size_t i = 0; i < node_list[index].road_list.size() ; i++)
        {
            if (answer.find(node_list[index].road_list[i].destination_node_name) == answer.end())
            {
                answer[node_list[index].road_list[i].destination_node_name] = node_list[index].road_list[i].cost + last_cost ;
                temp[node_list[index].road_list[i].cost + last_cost ] = node_list[index].road_list[i].destination_node_name;
            }
            
            else
            {
                if (node_list[index].road_list[i].cost + last_cost < answer[node_list[index].road_list[i].destination_node_name])
                {
                    auto replace = answer.find(node_list[index].road_list[i].destination_node_name);

                    replace->second = node_list[index].road_list[i].cost + last_cost;

                    while (true)
                    {
                        if (temp.find(replace->second) != temp.end() && temp[replace->second] == replace->first)
                        {
                            auto temp2 = temp.find(replace->second);
                            temp2->second = replace->first ;
                            break;
                        }
                    } // end of while
                } // end of if
            } // end of else

            sort(temp.begin() ,temp.end());
        } // end of for

        if (temp.size() <= 1)
            break;
    } // end of while(true)
    
    
    cout << "Cost : " << answer.find(end_node.get_name())->second << endl;

}



int galaxy :: find_node(string n)
{
    for (size_t i = 0; i < node_list.size() ; i++)
    {
        if (n == node_list[i].get_name())
            return i ;
    }   
}

int main()
{
    return 0;
}

//g++ -o fpp object_083209.cpp

#endif
