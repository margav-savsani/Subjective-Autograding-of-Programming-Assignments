#include "DynamicArray.cpp"


int main() {
    int n;  // Number of nodes
    cin >> n;
    DynamicArray* edges = new DynamicArray[n];  // Adjacency list of the graph
    DynamicArray* reverse_edges = new DynamicArray[n];  // Adjacency list of the reversed graph
    int a, b;
    cin >> a >> b;
    while (a != -1) {
        a--, b--;
        edges[a].add(b);
        reverse_edges[b].add(a);
        cin >> a >> b;
    }

    // For all j that will be in similar[i], (i, j) will be a similar pair
    DynamicArray* similar = new DynamicArray[n];
    cin >> a >> b;
    while (a != -1) {
        a--, b--;
        similar[a].add(b);
        cin >> a >> b;
    }

    // Finding the source nodes of the graph
    // A source node has no edges leaving it in the reversed graph
    cout << "Source nodes: ";
    for (int i=0; i<n; i++) {
        if (!reverse_edges[i].size()) cout << i+1 << ' ';
    }
    cout << "\n\n";

    // Finding the similar nodes
    int updates;
    do {  // Keep running the loop until no new pairs are found
        updates = 0;
        // Iterate over all pairs of nodes
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (similar[i].find(j) || i == j) continue;

                // Condition 3
                if (reverse_edges[i].size() == 1 && reverse_edges[i].get(0) == j) {
                    similar[i].add(j);
                    updates++;
                } 
                
                // Condition 2
                if (reverse_edges[j].size() && reverse_edges[i].size()) {
                    bool sim { true };
                    for (int k=0; k<reverse_edges[i].size(); k++) {
                        bool s { false };
                        for (int l=0; l<reverse_edges[j].size(); l++) s |= similar[reverse_edges[i].get(k)].find(reverse_edges[j].get(l));
                        sim &= s;
                    }
                    for (int k=0; k<reverse_edges[j].size(); k++) {
                        bool s { false };
                        for (int l=0; l<reverse_edges[i].size(); l++) s |= similar[reverse_edges[j].get(k)].find(reverse_edges[i].get(l));
                        sim &= s;
                    }
                    if (sim) {
                        similar[i].add(j);
                        if (!similar[j].find(i)) similar[j].add(i);
                        updates++;
                    }
                }
            }
        }
        if (!updates) break;
    } while (updates);

    // Finding the representative of each equivalence class of nodes
    DynamicArray repr;
    for (int i=0; i<n; i++) repr.add(i);
    cout << "Similar node pairs: ";
    for (int i=0; i<n; i++) {
        for (int j=0; j<similar[i].size(); j++) {
            cout << "(" << i+1 << ", " << similar[i].get(j)+1 << ") ";
            DynamicArray v;
            for (int k=0; k<n; k++) {
                if (repr.get(k) == repr.get(i) || repr.get(k) == repr.get(similar[i].get(j))) v.add(k);
            }
            for (int k=0; k<v.size(); k++) repr.set(v.get(k), max(repr.get(i), repr.get(similar[i].get(j))));
        }
    }
    cout << "\n\n";

    // Finding nodes in the new graph
    DynamicArray new_graph;
    for (int i=0; i<n; i++) {
        if (!new_graph.find(repr.get(i))) new_graph.add(repr.get(i));
    }
    cout << "Collapsed graph: \n\n" << new_graph.size() << ": ";
    for (int i=0; i<new_graph.size(); i++) cout << new_graph.get(i)+1 << ' ';
    cout << "\n";

    // Finding edges in the new graph
    // New edges are old edges from one class to another
    DynamicArray* new_edges = new DynamicArray[n];
    for (int i=0; i<n; i++) {
        for (int j=0; j<edges[i].size(); j++) {
            if (!new_edges[repr.get(i)].find(repr.get(edges[i].get(j))) && repr.get(i) != repr.get(edges[i].get(j))) {
                new_edges[repr.get(i)].add(repr.get(edges[i].get(j)));
                cout << repr.get(i)+1 << ' ' << repr.get(edges[i].get(j))+1 << '\n';
            }
        }
    }
}