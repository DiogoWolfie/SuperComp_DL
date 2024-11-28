#include <iostream>
#include <fstream>
#include <string>
#include <mpi.h>
#include <omp.h>
#include <vector>
using namespace std;

//Esse código verifica todos os códons, incluindo casos em que os códons são sobrepostos
void contagem(const string& sequencia, int& prot) {
    #pragma omp parallel for reduction(+: prot)
    for (size_t i = 0; i < sequencia.size() - 2; i++) { // -2 para evitar leitura fora do limite
        if (sequencia.substr(i, 3) == "AUG") {
            prot++;
        }
    }
}


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int total_prot = 0;

    for (int i = 1; i <= 22; i++) {
        string arquivoRNA = "RNA" + to_string(i) + ".fa";

        if (rank == 0) {
            cout << "Processando arquivo: " << arquivoRNA << endl;
        }

        MPI_File arquivo;
        MPI_File_open(MPI_COMM_WORLD, arquivoRNA.c_str(), MPI_MODE_RDONLY, MPI_INFO_NULL, &arquivo);

        MPI_Offset tamanhoArquivo;
        MPI_File_get_size(arquivo, &tamanhoArquivo);

        if (tamanhoArquivo <= 0) {
            if (rank == 0) {
                cerr << "Erro: Arquivo vazio ou inválido: " << arquivoRNA << endl;
            }
            MPI_File_close(&arquivo);
            continue;
        }

        MPI_Offset tamanhoPorProcesso = (tamanhoArquivo / size) + 2; // Ajuste para blocos alinhados
        char* buffer = new (nothrow) char[tamanhoPorProcesso + 1];
        if (!buffer) {
            cerr << "Erro ao alocar memória no processo " << rank << endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        MPI_File_read_at_all(arquivo, rank * tamanhoPorProcesso, buffer, tamanhoPorProcesso, MPI_CHAR, MPI_STATUS_IGNORE);
        buffer[tamanhoPorProcesso] = '\0';

        int prot = 0;
        contagem(string(buffer), prot);

        delete[] buffer;
        MPI_File_close(&arquivo);

        MPI_Reduce(&prot, &total_prot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        cout << "Contagem total de códons AUG: " << total_prot << endl;
    }

    MPI_Finalize();
    return 0;
}
