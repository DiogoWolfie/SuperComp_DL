#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <string>
#include <cmath>


using namespace std;
int N = 100000;


void Monte_Carlo(float& circulo){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_real_distribution<float> distribution(0.0,1.0);
    for(int i = 0; i < N; i++){
        float x = distribution(generator);
        float y = distribution(generator);
        if(pow(x,2) + pow(y,2) <= 1.0){
            circulo++;
        }

    }

}

int main(){
    float circulo = 0.0;
    
    auto start = std::chrono::high_resolution_clock::now();

    Monte_Carlo(circulo);
    float pi = 4*(circulo/N);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double exec_time = duration.count();

    cout << "valor de pi: " << pi << endl;
    cout<< "tempo de execucao: " << exec_time << " s" << endl;

    return 0;
}
