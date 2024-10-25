#include <iostream>
#include <cstring>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv) {
    char mensagem[10] = "beber?";
    int rank, size, type = 42;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
    if (rank == 0) {
        MPI_Send(mensagem, 7, MPI_CHAR, 1, type, MPI_COMM_WORLD);
        //MPI_Recv(mensagem, 7, MPI_CHAR, size - 1, type, MPI_COMM_WORLD, &status);
       
    } else {
        
        MPI_Recv(mensagem, 7, MPI_CHAR, rank - 1, type, MPI_COMM_WORLD, &status);
        
        int next_rank = (rank + 1) % size; 
        if(next_rank != 0){
            MPI_Send(mensagem, 7, MPI_CHAR, next_rank, type, MPI_COMM_WORLD);
        }else{
            cout << "processo " << size << " recebe a mensagem: bora " << mensagem << endl;
        }
       

    }

    MPI_Finalize();
    return 0;
}
