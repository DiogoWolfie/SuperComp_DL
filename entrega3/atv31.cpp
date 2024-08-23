#include <iostream>   // Inclui a biblioteca padrão de entrada e saída, usada para operações como std::cout.
#include <chrono>     // Inclui a biblioteca para medição de tempo, usada para medir a performance do código.
#include <vector>
using namespace std;
using namespace chrono;

int main() {
    int N = 1000;  // Define o tamanho da matriz como N x N, onde N é 1000.


    vector<vector<int>> matriz(N, vector<int>(N, 0));

    // Aqui você pode inicializar e somar os elementos da matriz.
    for(int i = 0; i <N; i++){
        for(int j = 0; j < N; j++){
            matriz[i][j] = i+j;
        }
    }
    auto inicio = high_resolution_clock::now();
    long long soma = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            soma += matriz[i][j];
        }
    }
    auto fim = high_resolution_clock::now();
    auto duracao = duration_cast<milliseconds>(fim - inicio).count();

    cout << "Soma de todos os elementos: " << soma << endl;
    cout << "Tempo de execução: " << duracao << "ms" << endl;


   

    return 0;  // Retorna 0, indicando que o programa terminou com sucesso.
}