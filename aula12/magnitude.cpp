#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>


float magnitude_cpu(const std::vector<float>& v) {
    float soma_quadrados = 0.0;
    for (float x : v) {
        soma_quadrados += x * x;
    }
    return std::sqrt(soma_quadrados);
}

int main() {
    
    std::vector<float> v(1000, 0.0); 
    for(int i = 0; i < v.size(); i++){
        v[i] += i;
    }

    auto t1 = std::chrono::steady_clock::now();
    float mag_cpu = magnitude_cpu(v);
    auto t2 = std::chrono::steady_clock::now();
    
    std::chrono::duration<double> cpu_time = t2 - t1;

    std::cout << "Magnitude (CPU): " << mag_cpu << std::endl;
    std::cout << "Tempo (CPU): " << cpu_time.count() << " s" << std::endl;

    return 0;
}
