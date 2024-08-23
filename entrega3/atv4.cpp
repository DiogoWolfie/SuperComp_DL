#include <iostream>
#include <vector>
using namespace std;

class Vector {
public:
    Vector(int tamanho) : tam(tamanho), capacidade(tamanho), dados(new int[tamanho]) {}
        
    // Destrutor para liberar a memória alocada dinamicamente
    ~Vector(){
        delete[] dados;
        cout << "Destruído" << endl;
    }
    void inicializa(int valor){
        for (int i =0; i<tam; i++ ){
            dados[i] = valor;
        }
    }
    int get(int index) const{
        return dados[index];
    }
    void set(int index, int valor){
        dados[index] = valor;
    }
    void inserir(int index, int valor){
        if (tam==capacidade){
            redimensiona(capacidade*2);
        }
        for (int i =tam ; i > index; i--){
            dados[i] = dados[i-1]; //move para a direita
        }
        dados[index] = valor;
        tam++;


    }
    void remover(int index){
        for(int i = index; i < tam-1; i++){
            dados[i] = dados[i+1]; //move para a esquerda
        }
        tam--;

    }
    void imprime() const{
        for(int i =0 ; i < tam; i++){
            cout << dados[i] << " ";
        }
        cout << endl;
    }

private:
    int* dados;
    int tam;
    int capacidade;
    void redimensiona(int novaCapacidade){
        int* novosDados = new int[novaCapacidade];
        for (int i = 0; i < tam; ++i) {
            novosDados[i] = dados[i];
        }
        delete[] dados;
        dados = novosDados;
        capacidade = novaCapacidade;
    
    }
};

// Implementação das funções...

int main() {
    Vector vec(5);
    vec.inicializa(0);
    vec.imprime();

    vec.set(2, 10);
    vec.imprime();

    vec.inserir(1, 5);
    vec.imprime();

    vec.remover(3);
    vec.imprime();

    return 0;
}