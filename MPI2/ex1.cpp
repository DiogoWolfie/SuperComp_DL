#include <iostream>
#include <cstring>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv){
    
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int array_size = 100;
    int array[array_size];
    
    if(rank == 0){
        srand(time(NULL));
        for (int i = 0; i < array_size ; i++){
            array[i] = rand() % 100;
        }
    }

    //para o caso do array não ser divisivel pelo size
    // int remainder = array_size % size;
    // if(rank < remainder){
    //     chunck_size += 1;
    // }
    int chunck_size = array_size/size;
    int recv_array[chunck_size];

    MPI_Scatter(array, chunck_size, MPI_INT, recv_array, chunck_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    
    double local_sum = 0.0;
    for(int i = 0; i < chunck_size; i++){
        local_sum += recv_array[i];
    }
    double local_mean = local_sum / chunck_size;


    double *local_means = nullptr;
    if(rank == 0){
        local_means = new double[size];
    }
    MPI_Gather(&local_mean, 1, MPI_DOUBLE, local_means, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    
    if(rank == 0){
        double global_sum = 0.0;
        for(int i = 0; i < size; i++){
            global_sum += local_means[i];
        }
        double global_mean = global_sum / size;
        cout << "Média global: " << global_mean << endl;

        delete[] local_means;  
    }

    
    MPI_Finalize();
    return 0;
}

