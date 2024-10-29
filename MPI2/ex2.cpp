#include <iostream>
#include <cstring>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv){
    
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int valor_interacao;
    if(rank==0){
        valor_interacao = 10;
    }

    MPI_Bcast(&valor_interacao, 1, MPI_INT, 0, MPI_COMM_WORLD);

    cout << "processo " << rank << " vai realizar o loop: \n";
    int valor_local = 0;
    // Exemplo de uso do valor em um loop
    for (int i = 0; i < valor_interacao; i++) {
        valor_local  = valor_local + i;
    }
    cout << "processo "<<rank << " calculou " << valor_local << endl ;

    MPI_Finalize();
    return 0;
}

