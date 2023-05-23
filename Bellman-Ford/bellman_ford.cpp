#include <iostream>
#include <vector>
#include <queue>
#include <limits> 
#include <string>
#include <fstream>
#include <algorithm>

#include "handleArgs.h"

using namespace std;

// Define type aliases for convenience
using PairInt = pair<int, int>;
using VectorPairInt = vector<PairInt>;
using pq = priority_queue<PairInt, VectorPairInt, greater<PairInt>>;

const int INF = numeric_limits<int>::max();

class Graph {
    private:
        int V;
        vector<int> path;
        vector <int> distance;
        vector<VectorPairInt> adjacentList;

    public:
        Graph(int V) : V{V}, path(V), distance(V, INF), adjacentList(V) {}

        bool BellmanFord(int initial_vertex = 0) {
            distance[initial_vertex] = 0;

            for (int i = 0; i < V-1; i++) {
                if(i == initial_vertex) {
                    path[i] = initial_vertex;
                    continue;
                }
                path[i] = -2;
            }

            for (int i = 0; i < V-1; i++) {
                bool changed = false;
                for (int u = 0; u < V; u++) {
                    for (PairInt node : adjacentList[u]) {
                        int v = node.first;
                        int w = node.second;

                        if (distance[u] != INF && distance[u] + w < distance[v]) {
                            distance[v] = distance[u] + w;
                            path[v] = u;
                            changed = true;
                        }
                    }
                }

                if (!changed) break;
            }

            for (int u = 0; u < V; u++) {
                for (PairInt node : adjacentList[u]) {
                    int v = node.first;
                    int w = node.second;

                    if (distance[u] != INF && distance[u] + w < distance[v]) {
                        return true;
                    }
                }
            }

            return false;
        }

        void printBestPath() {
            cout << "Best path: ";
            for (int i = 0; i < V; i++) {
                cout << i+1 << ": " << path[i]+1 << "\n";
            }

            cout << endl << endl;
        }

        void printGraph() {
            cout << "Graph: " << endl;
            for (int i = 0; i < V; i++) {
                cout << i+1 << ": ";
                for (PairInt node : adjacentList[i]) {
                    cout << node.first+1 << " ";
                }
                cout << endl;
            }
        }

        void printDistance() {
            cout << "Cost to get to each vertex: " << endl;
            for (int i = 0; i < V; i++) {
                string distance_str = distance[i] != INF ? to_string(distance[i]) : "Infinite";
                cout << i+1 << " " <<  distance_str << endl;
            }
        }

        void addEdge(int u, int v, int w) {
            adjacentList[u-1].emplace_back(v-1, w);
        }    
};

int main(int argc, char *argv[]) {

    int initial_vertex;
    bool hasNegativeCycle = false;
    string input_file = "", output_file = "";
    handle_args(argc, argv, input_file, output_file, initial_vertex);

    ifstream fin(input_file);
    ofstream fout(output_file);
     
    int V, E;

    if(input_file != "") fin >> V >> E;
    else cin >> V >> E;

    Graph G(V);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        if(input_file != "") fin >> u >> v >> w;
        else cin >> u >> v >> w;
        G.addEdge(u, v, w);
    }

    if(initial_vertex < 1 || initial_vertex > V) initial_vertex = 1;
    hasNegativeCycle = G.BellmanFord(initial_vertex-1);

    G.printBestPath();
    G.printDistance();

    if(hasNegativeCycle) cout << endl << "This graph contains a negative cycle" << endl;

    //G.printGraph();

    fin.close();
    fout.close();

    return 0;
}
