#include "dijkstras.h"

int main() {
    Graph G;
    string filename = "src/medium.txt";
    file_to_graph(filename, G);

    for (int destination = 0; destination < G.numVertices; ++destination) {
        vector<int> previous;
        vector<int> distances = dijkstra_shortest_path(G, 0, previous);

        vector<int> path = extract_shortest_path(distances, previous, destination);
        print_path(path, distances[destination]);
    }

    return 0;
}