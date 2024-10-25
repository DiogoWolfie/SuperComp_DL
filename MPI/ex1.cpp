#include <iostream>
#include <cstring>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv){
    char mensagem[5];
    int i, rank, size,type = 42;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        strcpy(mensagem, "olá");
        MPI_Send(mensagem, 4, MPI_CHAR, 1, type, MPI_COMM_WORLD);
        MPI_Recv(mensagem, 3, MPI_CHAR,1, type, MPI_COMM_WORLD, &status);
        cout<< "mensagem do nó 1: " << mensagem << endl;
    }else{
        MPI_Recv(mensagem, 4, MPI_CHAR,0, type, MPI_COMM_WORLD, &status);
        cout<< "mensagem do nó 0: " << mensagem << endl;
        strcpy(mensagem, "oi");
        MPI_Send(mensagem, 3, MPI_CHAR, 0, type, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
