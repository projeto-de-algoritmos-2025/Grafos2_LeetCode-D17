/*
 778 Swim in Rising Water
 Exercício resolvido por Diego Souza e Marcos Castilhos

 Abordagem:
Usamos uma variação do algoritmo de Dijkstra para encontrar o menor "tempo" necessário
para ir do canto superior esquerdo até o canto inferior direito da grade.

A ideia é usar uma min-heap (priority_queue) que sempre escolhe a próxima célula
com menor altura possível. A cada passo, mantemos o valor máximo (ans) da altura
já encontrada no caminho. Quando alcançamos o destino, esse ans representa o
menor nível da água em que é possível completar o trajeto.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // Min-heap: (altura necessária, linha, coluna)
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
        
        // Marcar visitados
        vector<vector<bool>> visited(n, vector<bool>(n,false));
        
        // Começamos no canto superior esquerdo
        pq.push({grid[0][0], 0, 0});
        visited[0][0] = true;
        
        int ans = 0;
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        
        while (!pq.empty()) {
            auto [h, x, y] = pq.top();
            pq.pop();
            
            // Atualiza altura máxima no caminho até agora
            ans = max(ans, h);
            
            // Se chegamos ao destino
            if (x == n-1 && y == n-1) return ans;
            
            // Explora vizinhos
            for (auto& d : dirs) {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx >= 0 && ny >= 0 && nx < n && ny < n && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    pq.push({grid[nx][ny], nx, ny});
                }
            }
        }
        
        return ans; 
    }
};

