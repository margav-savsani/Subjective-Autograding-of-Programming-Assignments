#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#include "Graph.h"
#include "std_headers.h"

Graph::Graph()
{
    std::cin >> numNodes;

    nodes = new Node[numNodes + 1];
    for (int i = 1; i <= numNodes; i++)
        nodes[i].value = i;

    int n1 = 0, n2 = 0;
    std::cin >> n1 >> n2;
    while (n1 != -1 || n2 != -1) {
        if (!nodes[n1].outbound_adjacency.contains(n2))
            nodes[n1].outbound_adjacency.insert(n2);
        std::cin >> n1 >> n2;
    }

    for (int i = 1; i <= numNodes; i++) {
        for (int adj : nodes[i].outbound_adjacency) {
            if (!nodes[adj].inbound_adjacency.contains(i))
                nodes[adj].inbound_adjacency.insert(i);
        }
    }

    // finding sources
    for (int i = 1; i <= numNodes; i++) {
        if (nodes[i].inbound_adjacency.is_empty())
            sources.insert(i);
        else
            non_sources.insert(i);
    }
    std::cin >> n1 >> n2;
    while (n1 != -1 || n2 != -1) {
        if (sources.contains(n1) && sources.contains(n2) && !nodes[n1].similar.contains(n2))
            nodes[n1].similar.insert(n2);
        std::cin >> n1 >> n2;
    }

    for (int i = 1; i <= numNodes; i++) {
        if (nodes[i].inbound_adjacency.size() == 1)
            nodes[i].similar.insert(*nodes[i].inbound_adjacency.begin());
    }

    update_similarity(sources);

    for (int i = 1; i <= numNodes; i++)
        for (int s : nodes[i].similar)
            similar_pairs_list.insert(Pair<int>(i, s));
}

void Graph::update_similarity(LinkedList<int> l)
{
    LinkedList<int> new_layer;
    for (int i = 1; i <= numNodes; i++) {
        if (l.contains(i))
            continue;

        bool shd_continue = false;
        for (int p : nodes[i].inbound_adjacency) {
            if (!l.contains(p)) {
                shd_continue = true;
                break;
            }
        }
        if (shd_continue)
            continue;
        new_layer.insert(i);
    }

    for (int n1 : new_layer) {
        for (int n2 : new_layer) {
            if (n2 >= n1)
                continue;
            bool is_correct = true;
            for (int m1 : nodes[n1].inbound_adjacency) {
                bool found = false;

                for (int m2 : nodes[n2].inbound_adjacency) {
                    if (nodes[m1].similar.contains(m2)) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    is_correct = false;
                    break;
                }
            }
            if (!is_correct)
                continue;

            for (int m2 : nodes[n2].inbound_adjacency) {
                bool found = false;

                for (int m1 : nodes[n1].inbound_adjacency) {
                    if (nodes[m2].similar.contains(m1)) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    is_correct = false;
                    break;
                }
            }

            if (is_correct) {
                nodes[n1].similar.insert(n2);
                nodes[n2].similar.insert(n1);
            }
        }
    }

    for (int n1 : new_layer) {
        for (int n2 : l) {
            bool is_correct = true;
            for (int m1 : nodes[n1].inbound_adjacency) {
                bool found = false;

                for (int m2 : nodes[n2].inbound_adjacency) {
                    if (nodes[m1].similar.contains(m2)) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    is_correct = false;
                    break;
                }
            }
            if (!is_correct)
                continue;

            for (int m2 : nodes[n2].inbound_adjacency) {
                bool found = false;

                for (int m1 : nodes[n1].inbound_adjacency) {
                    if (nodes[m2].similar.contains(m1)) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    is_correct = false;
                    break;
                }
            }

            if (is_correct) {
                nodes[n1].similar.insert(n2);
                nodes[n2].similar.insert(n1);
            }
        }
    }

    for (int n : new_layer)
        l.insert(n);

    if (l.size() < numNodes)
        update_similarity(l);
}

Graph::~Graph()
{
    delete[] nodes;
}

LinkedList<int> Graph::source() const
{
    return sources;
}

LinkedList<Pair<int>> Graph::similar_pairs() const
{
    return similar_pairs_list;
}

void Graph::collapse_similarity(std::ofstream& f) const
{
    int* sim_class = new int[numNodes + 1];
    for (int i = 1; i <= numNodes; i++)
        sim_class[i] = i;
    for (Pair<int> p : similar_pairs_list) {
        if (sim_class[p.v1] != sim_class[p.v2]) {
            int l = (sim_class[p.v1] < sim_class[p.v2] ? sim_class[p.v1] : sim_class[p.v2]);
            int m = sim_class[p.v1] + sim_class[p.v2] - l;
            for (int i = 1; i <= numNodes; i++) {
                if (sim_class[i] == l)
                    sim_class[i] = m;
            }
        }
    }

    LinkedList<int> new_vertices;
    for (int i = 1; i <= numNodes; i++) {
        if (!new_vertices.contains(sim_class[i]))
            new_vertices.insert(sim_class[i]);
    }
    LinkedList<Pair<int>> new_edges;
    for (int i = 1; i <= numNodes; i++) {
        for (int j = 1; j <= numNodes; j++) {
            if (j >= i || sim_class[j] == sim_class[i])
                continue;
            if (nodes[i].outbound_adjacency.contains(j) && !new_edges.contains(Pair<int>(sim_class[i], sim_class[j])))
                new_edges.insert(Pair<int>(sim_class[i], sim_class[j]));
            if (nodes[j].outbound_adjacency.contains(i) && !new_edges.contains(Pair<int>(sim_class[j], sim_class[i])))
                new_edges.insert(Pair<int>(sim_class[j], sim_class[i]));
        }
    }

    delete[] sim_class;

    f << new_vertices.size() << ": ";
    for (int i : new_vertices)
        f << i << ' ';
    f << '\n';
    for (Pair<int> p : new_edges) {
        f << p.v1 << ' ' << p.v2 << '\n';
    }
}

#endif
