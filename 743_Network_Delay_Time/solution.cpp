/*
743. Network Delay Time

Exercício resolvido por Diego Souza e Marcos Castilhos
Abordagem:
Este código implementa o algoritmo de Dijkstra para calcular o tempo mínimo
necessário para que um sinal enviado a partir do nó `k` alcance todos os outros nós.

- O grafo é representado como lista de adjacência, onde cada aresta tem um peso (tempo).
- Mantemos um vetor `dist` com a menor distância conhecida até cada nó.
- Usamos uma min-heap (priority_queue com greater<>) para sempre expandir o nó
  com a menor distância atual.
- A cada iteração, relaxamos as arestas (checamos se `dist[u] + w < dist[v]`).
- No final, o tempo de propagação é a maior distância encontrada.
- Se algum nó não for alcançável (`dist` ainda for INT_MAX), retornamos -1. 
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Grafo como lista de adjacência
        vector<vector<pair<int,int>>> graph(n+1);
        for (auto &t : times) {
            graph[t[0]].push_back({t[1], t[2]});
        }
        
        // Distâncias
        vector<int> dist(n+1, INT_MAX);
        dist[k] = 0;
        
        // Min-heap (distância, nó)
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0, k});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto [v, w] : graph[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        int ans = *max_element(dist.begin()+1, dist.end());
        return ans == INT_MAX ? -1 : ans;
    }
};

