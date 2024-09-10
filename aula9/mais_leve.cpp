#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>     // Inclui a biblioteca para medição de tempo.
#include <random>
#include <algorithm>
using namespace std;


struct Mochila
{
    int N = 0;
    int W = 0;
    // vector<int> pesos;
    // vector<int> valores;
    vector<pair<int, int>> pares; //correspondente ao valor e ao peso, respectivamente

};

void LerArquivo(string& Arquivo, Mochila& mochila){
    ifstream file(Arquivo);
    if(file.is_open()){
        file >> mochila.N;
        file >> mochila.W;
        mochila.pares.resize(mochila.N);
        for(int i = 0; i < mochila.N ; i++){
            file >> mochila.pares[i].first; //pesos
            file >> mochila.pares[i].second; //valores
            // file >> mochila.pesos[i];
            // file >> mochila.valores[i];
            
        }
    file.close();
    }
    else{
        cout << "Arquivo nao encontrado" << endl;
    }
}

//função para deixar na ordem crescente de valores, sem importar o peso. Serve já para o próximo código
void Crescente(Mochila& mochila){

    sort(mochila.pares.begin(), mochila.pares.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first == b.first) {
            return a.second > b.second;  // Se os valores forem iguais, ordena pelo peso (mais leve primeiro, decrescente)
        }
        return a.first < b.first;  // Caso contrário, ordena pelo valor (mais valioso primeiro)
    });


}
void BagLight(Mochila& mochila, int& valorfinal, int& pesofinal){

    Crescente(mochila);
    for(int i = 0; i < mochila.N; i++){
        if(pesofinal + mochila.pares[i].first <= mochila.W){
            pesofinal += mochila.pares[i].first;
            valorfinal += mochila.pares[i].second;
        }
    }

}


int main(){

    string Arquivo;
    cout << "nome do arquivo a ser lido: "<<  endl;
    cin >> Arquivo; 

    // Abre o arquivo de saída no modo de apêndice
    ofstream saida("saida.txt", std::ios_base::app); 

    if(!saida.is_open()){
        cout << "Erro ao abrir o arquivo de saída." << endl;
        return 1;
    }

    for(int i = 0; i < 5 ;i++){
        
    }

    Mochila mochila;
    int valorfinal = 0;
    int pesofinal = 0;
    LerArquivo(Arquivo, mochila);
    BagLight(mochila, valorfinal, pesofinal);

    // for(int i =0; i < mochila.N ; i++){
    //     saida << "Vetor ordenado dos pesos: " << mochila.pares[i].first << endl;
    //     saida << "Vetor ordenado dos valores: " << mochila.pares[i].second << endl;  
    // }
    saida << "Heuristica do mais leve"<<endl;
    saida << "Peso final: "<< pesofinal << " kg" << endl;
    saida << "Valor final: "<<valorfinal << " Dinheiros" << endl;
    saida << "###########################################" << endl;
    saida << "\n" << endl;

    saida.close();



    return 0;
}