#include <iostream>
#include <vector>
#include <queue>
#include <limits> 
#include <string>
#include <fstream>

#include "handleArgs.h"

using namespace std;

// Define type aliases for convenience
using PairInt = pair<int, int>;
using VectorPairInt = vector<PairInt>;
using pq = priority_queue<PairInt, VectorPairInt, greater<PairInt>>;

const int INF = numeric_limits<int>::max();
VectorPairInt minimum_spanning_tree;

class Graph {
    private:
        int V;
        vector<VectorPairInt> adjacentList;

    public:
        Graph(int V) : V{V}, adjacentList(V) {}

        void addEdge(int u, int v, int w) {
            adjacentList[u-1].emplace_back(v-1, w);
            adjacentList[v-1].emplace_back(u-1, w);
        }

        int primMST(int initialNode = 0) {
            int total_weight = 0;
            
            vector<int> weights(V, INF);
            vector<int> parent(V, -1);
            vector<bool> inMST(V, false);

            pq queue;

            weights[initialNode] = 0;
            
            queue.emplace(weights[initialNode], initialNode);

            while (!queue.empty()) {
                int currentNode = queue.top().second;
                queue.pop();

                if(inMST[currentNode] == true) continue;
                
                inMST[currentNode] = true;

                for (PairInt adjacentPair : adjacentList[currentNode]) {
                    int adjacentVertex = adjacentPair.first;
                    int adjacentWeight = adjacentPair.second;

                    if (!inMST[adjacentVertex] && weights[adjacentVertex] > adjacentWeight) {
                        weights[adjacentVertex] = adjacentWeight;
                        parent[adjacentVertex] = currentNode;
                        queue.emplace(adjacentWeight, adjacentVertex);
                    }
                }
            }

            // Build minimum spanning tree from parent array
            for (int i = 0; i < V; i++) {
                total_weight += weights[i];
                if (parent[i] == -1) continue;
                minimum_spanning_tree.emplace_back(parent[i], i);
            }

            return total_weight;
        }

        void print_tree() {
            for (PairInt adjacentPair : minimum_spanning_tree) {
                cout << adjacentPair.first + 1 << " " << adjacentPair.second + 1 << endl;
            }
        }
};

int main(int argc, char *argv[]) {
    bool print_tree_flag = false;
    int s;
    string input_file = "", output_file = "";
    handle_args(argc, argv, input_file, output_file, s, print_tree_flag);

    ifstream fin(input_file);
    ofstream fout(output_file);
     
    int V, E;
    fin >> V >> E;

    Graph G(V);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        G.addEdge(u, v, w);
    }

    int mst_weight = 0;

    if(s > 0 && s <= V) {
        mst_weight = G.primMST(s - 1);
    } else {
        mst_weight = G.primMST();
    }

    if(print_tree_flag){
        G.print_tree();
    } else {
        cout << mst_weight << endl;
    }

    if(fout.is_open()){
        for (PairInt adjacentPair : minimum_spanning_tree) {
            fout << adjacentPair.first + 1 << " " << adjacentPair.second + 1 << endl;
        }
        fout << "Minimum spanning tree weight: " << mst_weight << endl;
    }

    if(fin.is_open()){
        fin.close();
    }

    return 0;
}
