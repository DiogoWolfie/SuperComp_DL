#include <iostream>
#include <cstring>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv) {
    char mensagem[5] = "blz?";
    int rank, size, type = 42;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
    if (rank == 0) {
        MPI_Send(mensagem, 5, MPI_CHAR, 1, type, MPI_COMM_WORLD);
        MPI_Recv(mensagem, 5, MPI_CHAR, size - 1, type, MPI_COMM_WORLD, &status);
        cout << "Processo " << rank << " recebeu a mensagem: " << mensagem << " do processo " << size - 1 << endl;
    } else {
        
        MPI_Recv(mensagem, 5, MPI_CHAR, rank - 1, type, MPI_COMM_WORLD, &status);
        cout << "Processo " << rank << " recebeu a mensagem: " << mensagem << " do processo " << rank - 1 << endl;
        
        int next_rank = (rank + 1) % size;  //para o ciclo funcionar - quando o divisor é maior que o dividendo o resto é o próprio dividendo
        MPI_Send(mensagem, 5, MPI_CHAR, next_rank, type, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
