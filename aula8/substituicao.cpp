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
    vector<int> pesos;
    vector<int> valores;
    vector<int> pesos_inclusos;
    //vector<int> valores_inclusos;

};

void LerArquivo(string& Arquivo, Mochila& mochila){
    ifstream file(Arquivo);
    if(file.is_open()){
        file >> mochila.N;
        file >> mochila.W;
        mochila.pesos.resize(mochila.N);
        mochila.valores.resize(mochila.N);
        mochila.pesos_inclusos.resize(mochila.N);

        for(int i = 0; i < mochila.N ; i++){
        
            file >> mochila.pesos[i];
            file >> mochila.valores[i];
            
        }
    file.close();
    }
    else{
        cout << "Arquivo nao encontrado" << endl;
    }
}

//solução aleatória.
void Bag(Mochila& mochila, int& valorfinal,int& pesofinal){
    cout << "Executando Bag" <<endl;
    //gerando valor aleatório entre 0 e 1

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0,1.0);

    //loop de preenchimento
    for(int i = 0; i < mochila.N; i++){
        double ale = distribution(generator);
        if(ale > 0.4 && pesofinal + mochila.pesos[i] <= mochila.W){
            pesofinal += mochila.pesos[i];
            valorfinal += mochila.valores[i];

            mochila.pesos_inclusos[i] = mochila.pesos[i];
            mochila.pesos[i] = 0; //vou precisar saber qual eu acrescentei
            
        }
        mochila.pesos_inclusos[i] = 0;
    }
}

void mochila_cheia(Mochila& mochila, int& valorfinal, int& pesofinal){
    cout << "Executando mochila_cheia" << endl;
    
    for(int i = 0; i < mochila.N; i++){
        if(mochila.pesos[i] != 0 && mochila.pesos[i] + pesofinal <= mochila.W){
            pesofinal += mochila.pesos[i];
            valorfinal += mochila.valores[i];
            mochila.pesos[i] = 0;
        }
    }
}

void troca(Mochila& mochila, int& valorfinal, int& pesofinal){
    //loop externo para valores não adicionados
    //loop interno para valores adicionados

    for(int i = 0; i < mochila.N ; i++){
        if(mochila.pesos[i] != 0){
            for(int j = 0; j <mochila.N ; j++){
                if(mochila.pesos_inclusos[j] != 0 && mochila.valores[i] > mochila.valores[j] && pesofinal + mochila.pesos[i] - mochila.pesos[j] <= mochila.W){
                    pesofinal += (mochila.pesos[i] - mochila.pesos[j]);
                    valorfinal += (mochila.valores[i] - mochila.valores[j]);
                }
            }
        }
        

}
}


int main(){

    string Arquivo;
    cout << "nome do arquivo a ser lido: "<<  endl;
    cin >> Arquivo; 
    //lendo os arquivos - função ler arquivo

    // Abre o arquivo de saída no modo de apêndice
    ofstream saida("saida.txt", std::ios_base::app); 

    if(!saida.is_open()){
        cout << "Erro ao abrir o arquivo de saída." << endl;
        return 1;
    }

    for(int j = 0; j < 10; j++){

        auto start = std::chrono::high_resolution_clock::now();

        Mochila mochila;
        int valorfinal = 0;
        int pesofinal = 0;
        LerArquivo(Arquivo, mochila);


        //enchendo a mochila de forma aleatória com probabilidade - função Bag()
        Bag(mochila, valorfinal, pesofinal);
    
        bool trocando = true;

        while (trocando)
        {   
            mochila_cheia(mochila, valorfinal, pesofinal);
            int valor_final_antigo = valorfinal; //temporário
            troca(mochila, valorfinal, pesofinal);
            if(valor_final_antigo == valorfinal){
                trocando = false;
                cout << "acabou a troca" << endl;
            }
            
        }
        

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        double exec_time = duration.count();

        // Escrevendo os resultados de cada execução
        saida << "Execução " << j + 1 << ":" << endl;
        saida << "Valor final: " << valorfinal << " dinheiros" << endl;
        saida << "Peso final: " << pesofinal << " kg" << endl;
        saida << "Tempo: " << exec_time << " s" << endl;
        saida << "--------------------------" << endl;
    }

    saida.close();
    return 0; 

}