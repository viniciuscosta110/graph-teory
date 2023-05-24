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
    public:
        int V;
        vector<int> path;
        vector <int> distance;
        vector<VectorPairInt> adjacentList;

        Graph(int V) : V{V}, path(V), distance(V, INF), adjacentList(V) {}

        bool BellmanFord(int initial_vertex = 0) {
            distance[initial_vertex] = 0;            

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

            return false;
        }

        void printBestPath() {
            // In the formate vertex:distance
            for (int i = 0; i < V; i++) {
                if (distance[i] == INF) continue;
                cout << i+1 << ":";
                cout << distance[i] << " ";
            }
        }

        void printGraph() {
            cout << "Graph: " << endl;
            for (int i = 0; i < V; i++) {
                cout << i+1 << ":";
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
    bool print = false;
    string input_file = "", output_file = "";
    handle_args(argc, argv, input_file, output_file, initial_vertex, print);

    ifstream fin(input_file);
    ofstream fout(output_file);
     
    int V, E;

    if(input_file != "") fin >> V >> E;
    else cin >> V >> E;

    Graph G(V);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        G.addEdge(u, v, w);
    }

    if(initial_vertex < 1 || initial_vertex > V) initial_vertex = 1;
    hasNegativeCycle = G.BellmanFord(initial_vertex-1);

    if(print) {
        G.printBestPath();
        G.printDistance();
    }

    if(fout.is_open()){
        fout << "Best path: " << endl;
        for (int i = 0; i < V; i++) {
            fout << i+1 << ": " << G.path[i]+1 << "\n";
        }

        fout << endl << endl;

        fout << "Cost to get to each vertex: " << endl;
        for (int i = 0; i < V; i++) {
            string distance_str = G.distance[i] != INF ? to_string(G.distance[i]) : "Infinite";
            fout << i+1 << " " <<  distance_str << endl;
        }
    }
    
    if(hasNegativeCycle) cout << endl << "This graph contains a negative cycle" << endl;

    //G.printGraph();
    G.printBestPath();

    fin.close();
    fout.close();

    return 0;
}
