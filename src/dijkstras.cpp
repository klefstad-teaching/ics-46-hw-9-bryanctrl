#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int n = G.numVertices();
    vector<int> distance(n, INF);
    vector<int> visited(n, false);
    previous.assign(n, -1);
    
    priorityQueue<pair<int, int>, vecotr<pair<int, int>>, greater<pair<int, int>>>pq;
    distance[source] = 0;
    pq.push(Node(source, 0));

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        if(visited[u]){
            continue;
        }
        visited[u] = true;
        for(const Edge& neighbor : G[u]){
            int v = neighbor.dst;
            int weight = neighbor.weight;
            if ((!visited[v] && distance[u] + weight) < distance[v]){
                distance[v] = distance[u] + weight;
                previous = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){

}

void print_path(const vector<int>& v, int total){

}

