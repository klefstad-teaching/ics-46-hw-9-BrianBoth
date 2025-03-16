#include "dijkstras.h"

struct Node {
    int vertex, weight;
    Node(int v, int w) : vertex(v), weight(w) {}
    bool operator>(const Node& other) const {return weight > other.weight;}
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(source, 0));
    distances[source] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.vertex;

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distances[v]));
            }
        }
    }

    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) {
        return path;
    }

    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }

    vector<int> reversed_path;
    for (int i = path.size() - 1; i >= 0; --i) {
        reversed_path.push_back(path[i]);
    }

    return reversed_path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path" << endl;
        return;
    }

    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}