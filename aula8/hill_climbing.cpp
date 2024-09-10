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


//usando a mochila probabilística

void BagCount(int N, int W, vector<int>& pesos, vector<int>& valores, int& pesofinal, int& valorfinal, string& binario){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0,1);

    for(int i = 0; i <= pesos.size(); i++){
        int d = distribution(generator); //gera número aleatorio entre 0 e 1
        if(d > 0.4 && pesofinal + pesos[i] <= W && N>0){
            pesofinal += pesos[i];
            valorfinal += valores[i];
            binario += '1';
            N--;
        }
        else{
            binario += '0';
        }
    }
    return;
}

void vizinhos (int N, int W, vector<int>& pesos, vector<int>& valores, int& pesofinal, int& valorfinal, string& binario){

    int valor_temp = valorfinal;
    int peso_temp = pesofinal;
    
    string temp = binario;

    for(int i=0; i < N; i++){
        
        int pesonovo = 0;
        int valornovo = 0;
        if(temp[i] == '0'){
            //só posso somar depois de ter comparar o binário
            temp[i] = '1';
            pesonovo = peso_temp + pesos[i];
            valornovo = valor_temp + valores[i];
            // cout << "peso novo: "<< pesonovo << endl;
            // cout << "peso : "<< peso_temp << endl;
            // cout << "valor novo: "<< valornovo << endl;
            // cout << "valor : "<< valor_temp << endl;


            if(pesonovo <= W && valornovo > valorfinal){
                pesofinal = pesonovo;
                valorfinal = valornovo;
                binario[i] = '1';
                cout << "novo binario: " << binario << endl;
                binario[i] = '0';//para não modificar o binario original
            }

        }
        
    }
    if(valorfinal == valor_temp){
        cout << "nenhuma troca foi feita" << endl;
    }
}

int main(){

    string nomeArquivo;
    vector<int> mochila;

    cout << "nome do arquivo desejado: " << endl;
    cin >> nomeArquivo;

    string binario;

    //separando número de objetos e capacidade da mochila
    int N; //númeor de objetos
    int W; //capacidade 
    vector<int> pesos;
    vector<int> valores;

    for(int i = 0; i< 10;i++){

    auto start = std::chrono::high_resolution_clock::now(); // Inicia a medição de tempo.
    lerArquivos(nomeArquivo, mochila);

    separaValores(mochila, N, W, pesos, valores);


    //agora começa a brincadeira
    
    int pesofinal =0 ;
    int valorfinal = 0;

   
    BagCount(N, W, pesos, valores, pesofinal,valorfinal, binario);
    cout << "binario: " << binario << endl;
    vizinhos(N, W, pesos, valores, pesofinal,valorfinal, binario);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double exec_time = duration.count(); // Tempo de execução em segundos.


    cout << nomeArquivo << " peso ocupado: "<< pesofinal << " kg" << " e valor alcancado: " << valorfinal << " dilmas"<<endl;
    cout << "tempo de execucao: "<<exec_time << " s"<< endl;
    
    

    }

   


    return 0;
}