#include <iostream>
#include <cstdlib>
#include <ctime>
#include <mpi.h>
#include <numeric>
#include <cmath>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int array_size = 100;
    int array[array_size];

    if(rank == 0) {
        srand(time(NULL));
        for (int i = 0; i < array_size; i++) {
            array[i] = rand() % 100;
        }
    }

    int chunk_size = array_size / size;
    int recv_array[chunk_size];

    MPI_Scatter(array, chunk_size, MPI_INT, recv_array, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    double soma_local = accumulate(recv_array, recv_array + chunk_size, 0.0);
    double media_local = soma_local / chunk_size;

    double variacao_local = 0.0;
    for(int valor : recv_array) {
        variacao_local += pow(valor - media_local, 2);
    }
    cout << "media local do processo " <<rank << " é " << media_local << endl;
    cout << "variacao local do processo " <<rank << " é " << variacao_local << endl;

    double *medias = nullptr;
    double *variacoes = nullptr;
    if(rank == 0) {
        medias = new double[size];
        variacoes = new double[size];
    }

    MPI_Gather(&media_local, 1, MPI_DOUBLE, medias, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(&variacao_local, 1, MPI_DOUBLE, variacoes, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        
        double media_global = accumulate(medias, medias + size, 0.0) / size;
        cout << "MEDIA GLOBAL " << media_global << endl;

        //esse cálculo aqui foi totalmente via chat, não tenho dicernimento para dizer se está correto
        double variacao_global = 0.0;
        for(int i = 0; i < size; i++) {
            variacao_global += variacoes[i] + chunk_size * pow(medias[i] - media_global, 2);
        }
        variacao_global /= array_size;

        double desvio_padrao_global = sqrt(variacao_global);

        cout << "Desvio padrão final: " << desvio_padrao_global << endl;

        delete[] medias;
        delete[] variacoes;
    }

    MPI_Finalize();
    return 0;
}
