#include <iostream>
#include <cstring>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv) {
    char mensagem[10];
    int rank, size, type = 42;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
    if(rank==0){
        for(int i=0; i < size;i++){
            string msg =  "mesg " + to_string(i);
            strcpy(mensagem, msg.c_str());
            MPI_Send(mensagem, 7, MPI_CHAR, i, type, MPI_COMM_WORLD);
        }
    }
    else{
        MPI_Recv(mensagem, 7, MPI_CHAR, 0, type, MPI_COMM_WORLD, &status);
        cout<< "mensagem: " << mensagem << " para o processo " << rank << endl;
    }
       

    

    MPI_Finalize();
    return 0;
}
