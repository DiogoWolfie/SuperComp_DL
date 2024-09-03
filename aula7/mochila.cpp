#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>     // Inclui a biblioteca para medição de tempo.
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



int BagCount(int N, int W, vector<int>& pesos, vector<int>& valores, int& pesofinal){

    //caso base
    if(N ==0 || W==0){
        return 0;
    }
    //caso base onde eu ultrapasso o peso permitido
    if(pesos[N-1] > W){
        return BagCount(N-1, W, pesos, valores, pesofinal);
    }
    else{
        int pesoAdicionado = pesofinal + pesos[N-1];
        int valorAdicionado = valores[N-1] + BagCount(N-1, W-pesos[N-1], pesos, valores, pesoAdicionado);
        
        int pesoNaoAdicionado = pesofinal;
        int valorNaoAdicionado = BagCount(N-1, W, pesos, valores, pesoNaoAdicionado);
        

        if(valorAdicionado > valorNaoAdicionado){
            pesofinal= pesoAdicionado;
        }else{
            pesofinal = pesoNaoAdicionado;
        }
        return max(valorAdicionado, valorNaoAdicionado);
    }
}

int main(){

    string nomeArquivo;
    vector<int> mochila;

    cout << "nome do arquivo desejado: " << endl;
    cin >> nomeArquivo;

    auto start = std::chrono::high_resolution_clock::now(); // Inicia a medição de tempo.
    lerArquivos(nomeArquivo, mochila);

    //separando número de objetos e capacidade da mochila
    int N; //númeor de objetos
    int W; //capacidade 
    vector<int> pesos;
    vector<int> valores;

    separaValores(mochila, N, W, pesos, valores);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double exec_time = duration.count(); // Tempo de execução em segundos.

    //agora começa a brincadeira
    auto start2 = std::chrono::high_resolution_clock::now(); // Inicia a medição de tempo.
    int pesofinal =0 ;

   
    int valorfinal = BagCount(N, W, pesos, valores, pesofinal);

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    double exec_time2 = duration2.count(); // Tempo de execução em segundos.


    cout << nomeArquivo << " peso ocupado: "<< pesofinal << " kg" << " e valor alcancado: " << valorfinal << " dilmas"<<endl;
    cout << "tempo das outras funções: "<<exec_time << endl;
    cout << "tempo da recursiva: " << exec_time2 << endl;


    return 0;
}