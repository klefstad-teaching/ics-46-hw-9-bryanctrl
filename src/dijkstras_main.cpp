#include <iostream>
#include "dijkstras.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
        return 1;
    }

    string filename = argv[1];
    Graph G;

    try {
        file_to_graph(filename, G);
    } catch (const exception& e) {
        cerr << "Error loading graph: " << e.what() << endl;
        return 1;
    }

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    for (int i = 0; i < G.numVertices; ++i) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

    return 0;
}
