/*
1584. Min Cost to Connect All Points: https://leetcode.com/problems/min-cost-to-connect-all-points/description/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem:
Este problema pede o custo mínimo para conectar todos os pontos, o que é um
problema clássico de encontrar uma Árvore Geradora Mínima (MST - Minimum Spanning Tree).
A solução utiliza o algoritmo de Prim, uma abordagem gulosa que constrói a MST
progressivamente.

O algoritmo funciona da seguinte forma:
1. Começamos com uma "árvore" contendo apenas um nó inicial (o ponto 0).
2. Mantemos um array `min_cost` que armazena, para cada ponto fora da árvore,
   o custo mínimo para conectá-lo a algum ponto que já está na árvore.
3. Em cada iteração, selecionamos o ponto fora da árvore que tem o menor
   custo de conexão (o menor valor em `min_cost`).
4. Adicionamos esse ponto e seu custo à nossa MST.
5. Após adicionar o novo ponto, recalculamos o `min_cost` para todos os
   outros pontos que ainda estão fora da árvore, pois o novo ponto pode
   oferecer um caminho de conexão mais barato para eles.
Repetimos os passos 3 a 5 até que todos os pontos tenham sido incluídos na árvore.
O custo total acumulado é a resposta. Essa implementação do Prim é otimizada
para grafos densos, tendo uma complexidade de O(N^2).
*/

#include <vector>
#include <cmath>
#include <limits>
#include <numeric>

using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 1) {
            return 0;
        }

        vector<int> min_cost(n, numeric_limits<int>::max());

        vector<bool> in_mst(n, false);

        // Começamos o algoritmo a partir do ponto 0.
        // O custo para conectar o ponto 0 a ele mesmo é 0.
        min_cost[0] = 0;

        int total_cost = 0;
        int edges_count = 0;

        // O loop principal continuará até que todos os pontos estejam na MST.
        while (edges_count < n) {
            int current_min_edge = numeric_limits<int>::max();
            int current_node = -1;

            // --- PASSO 1: Encontrar a conexão mais barata ---
            for (int i = 0; i < n; ++i) {
                if (!in_mst[i] && min_cost[i] < current_min_edge) {
                    current_min_edge = min_cost[i];
                    current_node = i;
                }
            }

            // --- PASSO 2: Adicionar o nó e o custo à MST ---
            total_cost += current_min_edge;
            in_mst[current_node] = true;
            edges_count++;

            // --- PASSO 3: Atualizar os custos para os outros nós ---
            for (int i = 0; i < n; ++i) {
                if (!in_mst[i]) {
                    int distance = abs(points[current_node][0] - points[i][0]) +
                                   abs(points[current_node][1] - points[i][1]);

                    if (distance < min_cost[i]) {
                        min_cost[i] = distance;
                    }
                }
            }
        }

        return total_cost;
    }
};