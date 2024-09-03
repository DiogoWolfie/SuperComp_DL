#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>     // Inclui a biblioteca para medição de tempo.
#include <random>
#include <algorithm>
using namespace std;

void lerArquivos(string& nomeArquivo, vector<int>& mochila){
    ifstream file(nomeArquivo);
    if(file.is_open()){
        int valor;
        while(file >> valor){
            mochila.push_back(valor);
        }
        file.close();

    }
    else{
        cout << "deu ruim para ler o arquivo" << endl;
    }
}

void separaValores (vector<int>& mochila, int& N, int& W, vector<int>& pesos, vector<int>& valores){
    N = mochila[0];
    W = mochila[1];
    mochila.erase(mochila.begin());
    mochila.erase(mochila.begin());

    for(int n =0 ; n < mochila.size(); n++ ){
        if(n % 2 == 0){
            pesos.push_back(mochila[n]);
        }else{
            valores.push_back(mochila[n]);
        }
    }
}



void BagCount(int N, int W, vector<int>& pesos, vector<int>& valores, int& pesofinal, int& valorfinal){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0,1);

    for(int i = 0; i <= pesos.size(); i++){
        int d = distribution(generator); //gera número aleatorio entre 0 e 1
        if(d > 0.4 && pesofinal + pesos[i] <= W && N>0){
            pesofinal += pesos[i];
            valorfinal += valores[i];
            N--;
        }
    }
    return;
}

int main(){

    string nomeArquivo;
    vector<int> mochila;

    cout << "nome do arquivo desejado: " << endl;
    cin >> nomeArquivo;

    for(int n =0 ; n <5; n++){

        auto start = std::chrono::high_resolution_clock::now(); // Inicia a medição de tempo.
        lerArquivos(nomeArquivo, mochila);

        //separando número de objetos e capacidade da mochila
        int N; //númeor de objetos
        int W; //capacidade 
        vector<int> pesos; //vetor de pesos
        vector<int> valores; //vetor de money

        separaValores(mochila, N, W, pesos, valores);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        double exec_time = duration.count(); // Tempo de execução em segundos.

        
        //agora começa a brincadeira
        auto start2 = std::chrono::high_resolution_clock::now(); // Inicia a medição de tempo.
        int pesofinal =0 ;
        int valorfinal = 0;
    
        BagCount(N, W, pesos, valores, pesofinal, valorfinal);

        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration2 = end2 - start2;
        double exec_time2 = duration2.count(); // Tempo de execução em segundos.

        cout << nomeArquivo << " peso ocupado: "<< pesofinal << " kg" << " e valor alcancado: " << valorfinal << " dilmas"<<endl;
        cout << "tempo das outras funções: "<<exec_time << endl;
        cout << "tempo da função BagCount: " << exec_time2 << endl;
    }

    

   return 0;
}