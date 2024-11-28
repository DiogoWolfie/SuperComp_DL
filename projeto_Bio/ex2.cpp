#include <iostream>
#include <fstream>
#include <string>
#include <mpi.h>
#include <omp.h>
#include <cctype> // para deixar maiúsculas as letras
#include <vector>
using namespace std;

// void DNAtoRNA(const string& sequencia, ofstream& RNA) {
//     string resultado;

//     #pragma omp parallel
//     {
//         string localResultado;
//         #pragma omp for
//         for (size_t i = 0; i < sequencia.size(); i++) {
//             char base = toupper(sequencia[i]);
//             switch (base) {
//                 case 'A': localResultado += 'A'; break;
//                 case 'T': localResultado += 'U'; break;
//                 case 'C': localResultado += 'C'; break;
//                 case 'G': localResultado += 'G'; break;
//                 default: break; // Ignorar caracteres inválidos
//             }
//         }

//         #pragma omp critical
//         resultado += localResultado;
//     }

//     RNA << resultado << endl; // Escreve a sequência convertida no arquivo
// }

void DNAtoRNA(const string& sequencia, ofstream& RNA) {
    vector<char> resultado(sequencia.size());

    #pragma omp parallel for
    for (size_t i = 0; i < sequencia.size(); ++i) {
        char base = toupper(sequencia[i]);
        switch (base) {
            case 'A': resultado[i] = 'A'; break;
            case 'T': resultado[i] = 'U'; break;
            case 'C': resultado[i] = 'C'; break;
            case 'G': resultado[i] = 'G'; break;
            default: resultado[i] = '\0'; break; // Ignorar caracteres inválidos
        }
    }

    for (char base : resultado) {
        if (base != '\0') {
            RNA << base;
        }
    }
    RNA << endl;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 1; i <= 22; i++) {
        string arquivoDNA = "chr" + to_string(i) + ".subst.fa";
        string arquivoRNA = "RNA" + to_string(i) + ".fa";

        if (rank == 0) {
            cout << "Processando arquivo: " << arquivoDNA << endl;
        }

        ofstream rnaFile(arquivoRNA);
        if (!rnaFile.is_open()) {
            cerr << "Erro ao criar o arquivo RNA: " << arquivoRNA << endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
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
            rnaFile.close();
            continue;
        }

        MPI_Offset offsetInicial = 0;
        if (rank == 0) {
            char linha[256];
            MPI_File_read(arquivo, linha, 255, MPI_CHAR, MPI_STATUS_IGNORE);
            linha[255] = '\0';
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
            cerr << "Erro ao alocar memória no processo " << rank << endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        MPI_File_read_at_all(arquivo, offsetInicial + rank * tamanhoPorProcesso, buffer, tamanhoPorProcesso, MPI_CHAR, MPI_STATUS_IGNORE);
        buffer[tamanhoPorProcesso] = '\0';

        DNAtoRNA(string(buffer), rnaFile);

        delete[] buffer;
        MPI_File_close(&arquivo);
        rnaFile.close();
    }

    MPI_Finalize();

    string arquivoRNA = "RNA1.fa"; // Nome do arquivo RNA que deseja verificar
    ifstream rnaFile(arquivoRNA);

    if (!rnaFile.is_open()) {
        cerr << "Erro ao abrir o arquivo RNA: " << arquivoRNA << endl;
        return 1;
    }

    string primeiraLinha;
    if (getline(rnaFile, primeiraLinha)) {
        cout << "Primeira linha do arquivo RNA: " << primeiraLinha << endl;
    } else {
        cerr << "Erro ao ler a primeira linha do arquivo RNA." << endl;
    }

    rnaFile.close(); // Fechar o arquivo após a leitura
    return 0;
    return 0;
}
