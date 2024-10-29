#include <iostream>
#include <cstdlib>
#include <ctime>
#include <mpi.h>
#include <omp.h>

using namespace std;

int main(int argc, char **argv){
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int array_size = 100;
    int array[array_size];
    int maior_valor = 0;


    if(rank == 0){
        srand(time(NULL));
        
        #pragma omp parallel for
        for(int i = 0; i < array_size; i++){
            array[i] = rand() % 200; // valores aleatórios entre 0 e 199
            #pragma omp critical
            {
                if(maior_valor < array[i]){
                    maior_valor = array[i];
                }
            }
        }
        
        cout << "\nMaior valor encontrado: " << maior_valor << endl;
    }


    MPI_Bcast(&maior_valor, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int chunk_size = array_size / size;
    int recv_array[chunk_size];

    MPI_Scatter(array, chunk_size, MPI_INT, recv_array, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    
    int menor_local = 200;
    for(int j = 0; j < chunk_size; j++){
        if(menor_local > recv_array[j]){
            menor_local = recv_array[j];
        }
    }

    double norm_array[chunk_size];
    for(int i = 0; i < chunk_size; i++){
        norm_array[i] = static_cast<double>(recv_array[i] - menor_local) / (maior_valor - menor_local);
    }


    double *global_norm_array = nullptr;
    if(rank == 0){
        global_norm_array = new double[array_size];
    }
    MPI_Gather(norm_array, chunk_size, MPI_DOUBLE, global_norm_array, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    
    if(rank == 0){
        cout << "Array normalizado: \n";
        for(int i = 0; i < array_size; i++) {
            cout << global_norm_array[i] << "\n";
        }
        cout << endl;
        delete[] global_norm_array;  
    }

    
    MPI_Finalize();
    return 0;
}
