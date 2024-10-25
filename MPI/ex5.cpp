#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv) {
    int init_num = 5;
    int rank, size, type = 42;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        MPI_Send(&init_num, 1, MPI_INT, 1, type, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&init_num, 1, MPI_INT, rank - 1, type, MPI_COMM_WORLD, &status);

        int next_rank = (rank + 1) % size;
        if (next_rank != 0) {
            int new_value = init_num + rank;
            MPI_Send(&new_value, 1, MPI_INT, next_rank, type, MPI_COMM_WORLD);
        } else {
            cout << "Processo " << rank << " recebeu a mensagem final: " << init_num << endl;
        }
    }

    MPI_Finalize();
    return 0;
}
