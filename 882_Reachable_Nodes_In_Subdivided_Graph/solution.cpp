/*
882. Reachable Nodes In Subdivided Graph: https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/description/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem:
A solução evita construir o grafo subdividido, que seria excessivamente grande.
Em vez disso, o problema é resolvido em duas etapas principais.
Primeiro, usamos o algoritmo de Dijkstra no grafo original para encontrar o caminho
mais curto (menor número de movimentos) do nó 0 para todos os outros nós originais.
Neste grafo, o "peso" de uma aresta [u, v, cnt] é considerado como (cnt + 1), que
representa a distância real entre u e v no grafo subdividido.
Após o Dijkstra, calculamos o total de nós alcançáveis:
1. Contamos quantos nós *originais* são alcançáveis, verificando se a distância
   até eles (dist[i]) é menor ou igual a 'maxMoves'.
2. Iteramos sobre cada aresta original [u, v, cnt] e calculamos quantos nós de
   *subdivisão* são alcançáveis. Isso é feito somando quantos nós podemos alcançar
   a partir de 'u' (com os movimentos restantes 'maxMoves - dist[u]') e a partir
   de 'v' ('maxMoves - dist[v]'), com o total limitado a 'cnt' (o número de
   nós de subdivisão que existem na aresta).
O resultado final é a soma dessas duas contagens.
*/

#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        
        // --- ETAPA 1: DIJKSTRA NO GRAFO ORIGINAL ---

        // Grafo representado por lista de adjacência.
        // Para cada nó 'u', guardamos um par {v, peso} para cada vizinho 'v'.
        // O peso da aresta [u, v, cnt] é (cnt + 1).
        vector<pair<int, int>> adj[n];
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cnt = edge[2];
            adj[u].push_back({v, cnt + 1});
            adj[v].push_back({u, cnt + 1});
        }

        // Vetor para armazenar as menores distâncias do nó 0 a todos os outros.
        // Inicializamos com um valor "infinito".
        vector<int> dist(n, numeric_limits<int>::max());
        
        // Fila de prioridade (min-heap) para o algoritmo de Dijkstra.
        // Armazena pares {distancia, no}, priorizando a menor distância.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Ponto de partida do algoritmo: nó 0 com distância 0.
        dist[0] = 0;
        pq.push({0, 0});

        // Loop principal do Dijkstra
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) {
                continue;
            }

            // "Relaxamento": Tenta encontrar caminhos mais curtos para os vizinhos de 'u'.
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        // --- ETAPA 2: CONTAGEM DOS NÓS ALCANÇÁVEIS ---

        // Contar os nós ORIGINAIS que são alcançáveis.
        int reachable_count = 0;
        for (int i = 0; i < n; ++i) {
            if (dist[i] <= maxMoves) {
                reachable_count++;
            }
        }

        // Contar os nós de SUBDIVISÃO que são alcançáveis.
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cnt = edge[2];

            int moves_from_u = (dist[u] > maxMoves) ? 0 : maxMoves - dist[u];
            int moves_from_v = (dist[v] > maxMoves) ? 0 : maxMoves - dist[v];

            reachable_count += min(cnt, moves_from_u + moves_from_v);
        }

        return reachable_count;
    }
};