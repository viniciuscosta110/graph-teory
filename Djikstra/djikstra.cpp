#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <fstream>
#include "handleargs.h"

using namespace std;

typedef pair<int, int> aresta;  // aresta (peso, vertice)

const int INF = numeric_limits<int>::max();

vector<vector<aresta>> graph; //vetor que vai armazenar as arestas

vector<int> dijkstra(int start, int n) {
    vector<int> dist(n, INF);  //vetores de distancia e visitados
    vector<bool> visited(n, false);

    priority_queue<aresta, vector<aresta>, greater<aresta>> pq; //fila de prioridade
    dist[start] = 0;    //inicio pelo no inicial com distancia 0
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;    //pego o vertice atual de acordo com o topo da fila de prioridade
        pq.pop();

        if (visited[u])         
            continue;

        visited[u] = true;  //marco como visitado

        for (const auto& neighbor : graph[u]) {  //itero pelos vizinhos
            int v = neighbor.first;         //pego o vertice vizinho
            int weight = neighbor.second;       //pego o custo pra ele

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main(int argc, char* argv[]) {

    bool print_tree_flag = false;
    int s;
    string input_file = "", output_file = "";
    handle_args(argc, argv, input_file, output_file, s, print_tree_flag);

    ifstream fin(input_file);
    ofstream fout(output_file);

    int startVertex;
    int n, m; 
    fin >> n >> m; //entrada de vertices e numero de aresta

    graph.resize(n);

    for (int i = 0; i < m; ++i) {  //leio cada aresta e adiciono de forma bilateral (Vai e volta)
        int u, v, weight;
        fin >> u >> v >> weight;
        graph[u-1].push_back({v - 1, weight});
        graph[v-1].push_back({u - 1, weight});
    }
    
    if(s > 0 && s <= n)
    {
        startVertex = s;
    }

    else
    {
        startVertex = 0;
    }
    

    vector<int> shortestDistances = dijkstra(startVertex, n);

    for (int i = 0; i < n; ++i) {
        cout << i + 1 << ":" << shortestDistances[i] << " ";
    }
    

    return 0;
}
