#include <vector>
#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <omp.h>


double conta_complexa(int i) {
    return 2 * i;
}

int main() {
    int N = 10000; 
    std::vector<double> vec;
    vec.resize(N);
    double init_time, final_time;
    init_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        vec[i] = conta_complexa(i);
    }

    for (int i = 0; i < N; i++) {
        std::cout << i << " ";
    }

    final_time = omp_get_wtime() - init_time;

    std::cout << "time: " << final_time << std::endl;

    //return 0;
}