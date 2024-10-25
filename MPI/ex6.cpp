#include <iostream>
#include <cstring>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv) {
    char mensagem[10] = "salve";
    int rank, size, type = 42;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            
            MPI_Send(mensagem, 6, MPI_CHAR, i, type, MPI_COMM_WORLD);
            cout << "Processo 0 envia a mensagem: '" << mensagem << "' para o processo " << i << endl;

    
            MPI_Recv(mensagem, 6, MPI_CHAR, i, type, MPI_COMM_WORLD, &status);
            cout << "Processo 0 recebeu a mensagem de volta: '" << mensagem << "' do processo " << i << endl;
        }
    } else {
        
        MPI_Recv(mensagem, 6, MPI_CHAR, 0, type, MPI_COMM_WORLD, &status);
        cout << "Processo " << rank << " recebeu a mensagem: '" << mensagem << "' do processo 0" << endl;

        MPI_Send(mensagem, 6, MPI_CHAR, 0, type, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
