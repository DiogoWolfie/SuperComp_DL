#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mpi.h>
#include <omp.h>
#include <cctype> // para deixar maiúsculas as letras
using namespace std;

struct DNA {
    int A = 0;
    int T = 0;
    int C = 0;
    int G = 0;

    DNA& operator+=(const DNA& other) {
        A += other.A;
        T += other.T;
        C += other.C;
        G += other.G;
        return *this;
    }
};

void ContagemdeBases(const string& sequencia, DNA& dna) {
    int countA = 0, countT = 0, countC = 0, countG = 0;

    #pragma omp parallel for reduction(+:countA, countT, countC, countG)
    for (size_t i = 0; i < sequencia.size(); ++i) {
        char base = toupper(sequencia[i]); // Converte para maiúsculas
        switch (base) {
            case 'A': countA++; break;
            case 'T': countT++; break;
            case 'C': countC++; break;
            case 'G': countG++; break;
        }
    }

    dna.A += countA;
    dna.T += countT;
    dna.C += countC;
    dna.G += countG;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    DNA dnaTotalGeral = {0, 0, 0, 0};
    DNA dnaLocal = {0, 0, 0, 0};

    // Processar 22 arquivos dinamicamente
    for (int i = 1; i <= 22; ++i) {
        // Gerar o nome do arquivo dinamicamente
        string arquivoDNA = "chr" + to_string(i) + ".subst.fa";

        DNA dnaLocalArquivo = {0, 0, 0, 0};
        DNA dnaTotalArquivo = {0, 0, 0, 0};

        if (rank == 0) {
            cout << "Processando arquivo: " << arquivoDNA << endl;
        }

        MPI_File arquivo;
        MPI_File_open(MPI_COMM_WORLD, arquivoDNA.c_str(), MPI_MODE_RDONLY, MPI_INFO_NULL, &arquivo);

        MPI_Offset tamanhoArquivo;
        MPI_File_get_size(arquivo, &tamanhoArquivo);

        if (tamanhoArquivo <= 0) {
            if (rank == 0) {
                cerr << "Erro: Arquivo vazio ou inválido: " << arquivoDNA << endl;
            }
            MPI_File_close(&arquivo);
            continue;
        }

        MPI_Offset offsetInicial = 0;
        if (rank == 0) {
            char linha[256];
            MPI_File_read(arquivo, linha, 255, MPI_CHAR, MPI_STATUS_IGNORE);
            linha[255] = '\0'; // Garante que a string termina
            string strLinha(linha);

            if (strLinha[0] == '>') {
                offsetInicial = strLinha.size() + 1;
                tamanhoArquivo -= offsetInicial;
            }
        }

        MPI_Bcast(&offsetInicial, 1, MPI_OFFSET, 0, MPI_COMM_WORLD);

        MPI_Offset tamanhoPorProcesso = tamanhoArquivo / size;
        char* buffer = new (nothrow) char[tamanhoPorProcesso + 1];
        if (!buffer) {
            cerr << "Erro ao alocar memória para o buffer no processo " << rank << endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        MPI_File_read_at_all(arquivo, offsetInicial + rank * tamanhoPorProcesso, buffer, tamanhoPorProcesso, MPI_CHAR, MPI_STATUS_IGNORE);
        buffer[tamanhoPorProcesso] = '\0';

        ContagemdeBases(string(buffer), dnaLocalArquivo);

        MPI_Reduce(&dnaLocalArquivo, &dnaTotalArquivo, 4, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            cout << "Contagem do arquivo " << arquivoDNA << ": \n";
            cout << "A: " << dnaTotalArquivo.A << "\n";
            cout << "T: " << dnaTotalArquivo.T << "\n";
            cout << "C: " << dnaTotalArquivo.C << "\n";
            cout << "G: " << dnaTotalArquivo.G << "\n";

            dnaTotalGeral += dnaTotalArquivo;
        }

        delete[] buffer;
        MPI_File_close(&arquivo);
    }

    if (rank == 0) {
        cout << "\nContagem total acumulada de todos os arquivos:\n";
        cout << "A: " << dnaTotalGeral.A << "\n";
        cout << "T: " << dnaTotalGeral.T << "\n";
        cout << "C: " << dnaTotalGeral.C << "\n";
        cout << "G: " << dnaTotalGeral.G << "\n";
    }

    MPI_Finalize();
    return 0;
}
