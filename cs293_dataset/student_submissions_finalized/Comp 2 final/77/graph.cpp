#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "graph.h"
#endif
using namespace std;

// prints source nodes
void Graph::print_sources()
{
    graphfile << "Source nodes:";
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].count_of_adjacent_in == 0)
        {
            graphfile << " " << nodes[i].value;
        }
    }
    graphfile << endl;
}
// prints similar node pair
void Graph::similar_node_pairs()
{
    // used recursion program search for similar paths, like dfs here it searches upto 1 node and comes back if any path (n1 or n2) is null
    //(2nd point from similar node defination)
    for (int g = 1; g < count_similar_node_storecse; g++)
    {
        rec(similar_node_storecase[g].first_num, similar_node_storecase[g].second_num);
    }
    // add single parent nodes (3rd point from similar node defination)
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].count_of_adjacent_in == 1)
        {
            similar_node_storecase[count_similar_node_storecse].first_num = nodes[i].value;
            similar_node_storecase[count_similar_node_storecse].second_num = nodes[i].adjacent_in[0];
            count_similar_node_storecse++;
        }
    }
    // prints similar node
    graphfile << "Similar node pairs:";
    for (int i = 1; i < count_similar_node_storecse; i++)
    {
        graphfile << " (" << similar_node_storecase[i].first_num << ", " << similar_node_storecase[i].second_num << ")";
    }
    graphfile << endl;
}
// This function acts like dfs
void Graph::rec(int a, int b)
{
    bool val = false;
    for (int i = 1; i < count_similar_node_storecse; i++)
    {
        // checks if it,s symmetric part is present or not (according to 3rd point from defination)
        if (similar_node_storecase[i].first_num == b && similar_node_storecase[i].second_num == a)
        {
            val = true;
            break;
        }
    }
    // If symmetric part exists go ahead else stop
    if (val)
    {
        for (int k = 0; k < nodes[a - 1].count_of_adjacent_out; k++)
        {
            // following all paths from node a
            for (int j = 0; j < nodes[b - 1].count_of_adjacent_out; j++)
            {
                // following all paths from node b
                if (nodes[a - 1].adjacent_out[k] != nodes[b - 1].adjacent_out[j])
                {
                    // check if already this pair is discovered or not
                    if (!is_already_present(nodes[a - 1].adjacent_out[k], nodes[b - 1].adjacent_out[j]))
                    {
                        similar_node_storecase[count_similar_node_storecse].first_num = nodes[a - 1].adjacent_out[k];
                        similar_node_storecase[count_similar_node_storecse].second_num = nodes[b - 1].adjacent_out[j];
                        count_similar_node_storecse++;
                    }
                    // check if already this pair's symmetric part is discovered or not
                    if (!is_already_present(nodes[b - 1].adjacent_out[j], nodes[a - 1].adjacent_out[k]))
                    {
                        similar_node_storecase[count_similar_node_storecse].first_num = nodes[b - 1].adjacent_out[j];
                        similar_node_storecase[count_similar_node_storecse].second_num = nodes[a - 1].adjacent_out[k];
                        count_similar_node_storecse++;
                    }
                }
            }
        }
    }
}
// helper function
// tells whether already given pair is present in list of similar node pairs or not
bool Graph::is_already_present(int a, int b)
{
    bool is_present = false;
    for (int i = 1; i < count_similar_node_storecse; i++)
    {
        if (similar_node_storecase[i].first_num == a && similar_node_storecase[i].second_num == b)
        {
            is_present = true;
            break;
        }
    }
    return is_present;
}
// Prints collapsed part
void Graph::collapsed_graph()
{
    int arr[numNodes];
    int size_arr = 0;
    int similar_node_initial_size = count_similar_node_storecse;
    // Partioning into different groups based on thier equivalence relation
    while (similar_node_initial_size != 1)
    {
        bool over = false;
        int partition[numNodes];
        int size_partition = 0;
        int f = 1;
        // getting non-checked element
        while (similar_node_storecase[f].checked)
        {
            f++;
        }
        partition[size_partition] = similar_node_storecase[f].first_num;
        size_partition++;
        if (similar_node_storecase[f].first_num != similar_node_storecase[f].second_num)
        {
            partition[size_partition] = similar_node_storecase[f].second_num;
            size_partition++;
        }
        similar_node_storecase[f].checked = true;
        similar_node_initial_size--;
        // for each partition containing element which is at 'f'(written above) position.
        while (!over)
        {
            over = true;
            for (int m = f - 1; m < count_similar_node_storecse; m++)
            {
                if (!similar_node_storecase[m].checked)
                {
                    bool a, b;
                    // checking if already element is present in partion or not
                    // 3 cases:
                    //       1. a is present , b not
                    //       2. a not present , b is present
                    //       3. both are already present
                    a = is_present_in_partition(partition, size_partition, similar_node_storecase[m].first_num);
                    b = is_present_in_partition(partition, size_partition, similar_node_storecase[m].second_num);
                    if (!a && b)
                    {
                        partition[size_partition] = similar_node_storecase[m].first_num;
                        size_partition++;
                        similar_node_storecase[m].checked = true;
                        similar_node_initial_size--;
                        over = false;
                    }
                    else if (a && !b)
                    {
                        partition[size_partition] = similar_node_storecase[m].second_num;
                        size_partition++;
                        similar_node_storecase[m].checked = true;
                        similar_node_initial_size--;
                        over = false;
                    }
                    else if (a && b)
                    {
                        similar_node_storecase[m].checked = true;
                        similar_node_initial_size--;
                        over = false;
                    }
                }
            }
        }
        // to get collapse finding maximum elements
        int maximum = partition[0];
        for (int p = 0; p < size_partition; p++)
        {
            is_in_partition[partition[p] - 1] = 1;
            if (partition[p] > maximum)
            {
                maximum = partition[p];
            }
        }
        // updating information of each node in class Node
        // this info is used for edges
        for (int p = 0; p < size_partition; p++)
        {
            nodes[partition[p] - 1].partition_number = no_partitions;
            nodes[partition[p] - 1].max_number_from_partition = maximum;
        }
        arr[no_partitions] = maximum;
        size_arr++;
        no_partitions++;
    }
    // printing required information with single element as one each equivalence class
    graphfile << "Collapsed graph:" << endl;
    int single_elem = 0;
    for (int i = 0; i < numNodes; i++)
    {
        if (!is_in_partition[i])
        {
            single_elem++;
        }
    }
    graphfile << single_elem + no_partitions << ":";
    for (int k = 0; k < no_partitions; k++)
    {
        graphfile << " " << arr[k];
    }

    for (int i = 0; i < numNodes; i++)
    {
        if (!is_in_partition[i])
        {
            single_elem++;
            graphfile << " " << i + 1;
        }
    }
    graphfile << endl;
}
// helper function
bool Graph::is_present_in_partition(int *part, int size_part, int num)
{
    for (int i = 0; i < size_part; i++)
    {
        if (part[i] == num)
        {
            return true;
        }
    }
    return false;
}
// helper function which tells edge is already present or not
bool Graph::edge_already_present(int a, int b)
{
    for (int i = 0; i < nodes[a - 1].count_of_adjacent_out; i++)
    {
        if (nodes[a - 1].adjacent_out[i] == b)
        {
            return true;
        }
    }
    return false;
}
// this prints collapsed edges
void Graph::collapsed_edges()
{
    // updates info of nodes for single equivalence class nodes
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i].partition_number == -1)
        {
            nodes[i].partition_number = no_partitions + 1;
            no_partitions++;
            nodes[i].max_number_from_partition = nodes[i].value;
        }
    }
    // check if partion is different between each node
    // 2 cases:
    //        if different: add edge
    //        if same : it is internal edge
    for (int i = 0; i < numNodes; i++)
    {
        for (int j = 0; j < nodes[i].count_of_adjacent_out; j++)
        {
            if (nodes[i].partition_number != nodes[nodes[i].adjacent_out[j] - 1].partition_number)
            {
                bool is_present = false;
                for (int y = 0; y < count_final_edges; y++)
                {
                    if ((nodes[i].max_number_from_partition == final_edges[y].a) && (nodes[nodes[i].adjacent_out[j] - 1].max_number_from_partition == final_edges[y].b))
                    {
                        is_present = true;
                        break;
                    }
                }
                if (!is_present)
                {
                    final_edges[count_final_edges].a = nodes[i].max_number_from_partition;
                    final_edges[count_final_edges].b = nodes[nodes[i].adjacent_out[j] - 1].max_number_from_partition;
                    count_final_edges++;
                }
            }
        }
    }
    // printing final edges
    for (int r = 0; r < count_final_edges; r++)
    {
        graphfile << final_edges[r].a << " " << final_edges[r].b << endl;
    }
}