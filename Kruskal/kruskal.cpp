#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <limits>
#include <fstream>
#include "handleargs.h"


using namespace std;

typedef pair<int, int> aresta;  // aresta (peso, vertice)

typedef struct aresta_completa
{
    int u,v,weight;
}aresta_completa;

const int INF = numeric_limits<int>::max();

vector<int> grupos;
vector<aresta_completa> lista_arestas;
vector<aresta_completa> graph_final; //grafo final depois do algoritmo

void inicializar(int n)
{
    for(int i = 0;i < n;i++)
    {
        grupos[i] = i;
    }
}

void marcar_grupo(aresta_completa arestai,int n)
{
    int valor1,valor2;
    if(grupos[arestai.u] > grupos[arestai.v])
    {
        valor1 = grupos[arestai.u];
        valor2 = grupos[arestai.v];
    }
    else
    {
        valor1 = grupos[arestai.v];
        valor2 = grupos[arestai.u];
    }

    for(int i = 0;i < n;i++)
    {
        if(grupos[i] == valor2)
        {
            grupos[i] = valor1;
        }
    }
}

int verifica(aresta_completa arestai,int n)
{
    if(grupos[arestai.u] != grupos[arestai.v])//essa entra
    {
        marcar_grupo(arestai,n);
        return 1;
    }

    return 0;
}

void kruskal(int n)
{   
    grupos.resize(n);
    inicializar(n);

    int i = 0;
    int contador = 0;

    while(contador < n-1)
    {
        if(verifica(lista_arestas[i],n) == 1)
        {   
            graph_final.push_back(lista_arestas[i]);
            contador++;
        }
        i++;  
    }
    
}

void ordenar_arestas(int m)
{
    for(int i = 0;i < m;i++)
    {
        for(int j = i + 1;j < m;j++)
        {
            if(lista_arestas[i].weight > lista_arestas[j].weight)
            {
                int aux;

                aux = lista_arestas[i].u;
                lista_arestas[i].u = lista_arestas[j].u;
                lista_arestas[j].u = aux;

                aux = lista_arestas[i].v;
                lista_arestas[i].v = lista_arestas[j].v;
                lista_arestas[j].v = aux;

                aux = lista_arestas[i].weight;
                lista_arestas[i].weight = lista_arestas[j].weight;
                lista_arestas[j].weight = aux;
            }
        }
    }
}

int main(int argc, char* argv[]) {

    bool print_tree_flag = false;
    int s;
    string input_file = "", output_file = "";
    handle_args(argc, argv, input_file, output_file, s, print_tree_flag);

    ifstream fin(input_file);
    ofstream fout(output_file);

    int n,m;
    fin >> n >> m; //entrada de vertices e numero de aresta

    for (int i = 0; i < m; ++i) {  //leio cada aresta e adiciono de forma bilateral (Vai e volta)
        int u, v, weight;
        aresta_completa nova;
        fin >> u >> v >> weight;

        nova.u = u - 1;
        nova.v = v - 1;
        nova.weight = weight;

        lista_arestas.push_back(nova);       
    }

    ordenar_arestas(m);
    kruskal(n);

    int output = 0;
    for(int i = 0;i < n -1;i++)
    {
        //cout << graph_final[i].u << " " << graph_final[i].v << " " << graph_final[i].weight << endl;
        output += graph_final[i].weight;
    }
    
    if(print_tree_flag)
    {
        for(int i = 0;i < n -1;i++)
        {
            cout << graph_final[i].u + 1 << " " << graph_final[i].v + 1 << endl;
        }
        
    }
    else
    {
        cout << output << endl;
    }
    

    return 0;
}