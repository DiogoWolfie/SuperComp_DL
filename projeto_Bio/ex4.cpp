#include <iostream>
#include <fstream>
#include <string>
#include <mpi.h>
#include <omp.h>
#include <vector>
#include <algorithm>
using namespace std;



void traduzirRNA(const string& sequencia, ofstream& aminoacido) {
    vector<string> prolina = {"CCA", "CCG", "CCU", "CCC"};
    vector<string> serina = {"UCU", "UCA", "UCG", "UCC"};
    vector<string> glutamina = {"CAG", "CAA"};
    vector<string> treonina = {"ACA", "ACC", "ACU", "ACG"};
    vector<string> metionina = {"AUG"};
    vector<string> stop = {"UGA"};
    vector<string> cisteina = {"UGC", "UGU"};
    vector<string> valina = {"GUG", "GUA", "GUC", "GUU"};

    vector<string> resultado; 

    #pragma omp parallel
    {
        vector<string> localResultado; 

        #pragma omp for
        for (size_t i = 0; i < sequencia.size() - 2; i += 3) { // Avança de 3 em 3 caracteres
            string codon = sequencia.substr(i, 3);

            if (std::find(prolina.begin(), prolina.end(), codon) != prolina.end()) {
                localResultado.push_back("Prolina");
            } else if (std::find(serina.begin(), serina.end(), codon) != serina.end()) {
                localResultado.push_back("Serina");
            } else if (std::find(glutamina.begin(), glutamina.end(), codon) != glutamina.end()) {
                localResultado.push_back("Glutamina");
            } else if (std::find(treonina.begin(), treonina.end(), codon) != treonina.end()) {
                localResultado.push_back("Treonina");
            } else if (std::find(metionina.begin(), metionina.end(), codon) != metionina.end()) {
                localResultado.push_back("Metionina");
            } else if (std::find(stop.begin(), stop.end(), codon) != stop.end()) {
                localResultado.push_back("STOP");
            } else if (std::find(cisteina.begin(), cisteina.end(), codon) != cisteina.end()) {
                localResultado.push_back("Cisteina");
            } else if (std::find(valina.begin(), valina.end(), codon) != valina.end()) {
                localResultado.push_back("Valina");
            }
        }

        #pragma omp critical
        resultado.insert(resultado.end(), localResultado.begin(), localResultado.end());
    }

    // Grava os resultados no arquivo de saída
    for (const string& amino : resultado) {
        aminoacido << amino << " ";
        if (amino == "STOP") break; 
    }
    aminoacido << endl;
}


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 1; i <= 22; i++) {
        string arquivoRNA = "RNA" + to_string(i) + ".fa";
        string aminoacidos = "aminoacidos" + to_string(i) + ".fa";

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

        ofstream aminoacidosFile(aminoacidos, ios::app);
        if (!aminoacidosFile.is_open()) {
            cerr << "Erro ao abrir o arquivo de saída: " << aminoacidos << endl;
            delete[] buffer;
            MPI_File_close(&arquivo);
            continue;
        }

        traduzirRNA(string(buffer), aminoacidosFile);

        delete[] buffer;
        MPI_File_close(&arquivo);

        aminoacidosFile.close();
    }

    MPI_Finalize();
    return 0;
}
