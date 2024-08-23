#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Função para contar palavras em uma linha e preencher o mapa de frequência
int countWordsAndFillMap(const string &line, unordered_map<string, int> &wordFreq) {
    stringstream ss(line);
    string word;
    int wordCount = 0;

    while (ss >> word) {
        wordCount++;
        wordFreq[word]++;
    }

    return wordCount;
}

int main() {
    string inputFileName = "input.txt";   // Arquivo de entrada
    string outputFileName = "output.txt"; // Arquivo de saída

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open()) {
        cerr << "Não foi possível abrir o arquivo de entrada!" << endl;
        return 1;
    }

    unordered_map<string, int> wordFreq;
    int totalWords = 0;
    int totalLines = 0;
    string line;

    while (getline(inputFile, line)) {
        totalLines++;
        totalWords += countWordsAndFillMap(line, wordFreq);
    }

    inputFile.close();

    // Encontrar a palavra mais frequente
    string mostFrequentWord;
    int maxFreq = 0;

    for (const auto &entry : wordFreq) {
        if (entry.second > maxFreq) {
            maxFreq = entry.second;
            mostFrequentWord = entry.first;
        }
    }

    double averageWordsPerLine = (totalLines > 0) ? static_cast<double>(totalWords) / totalLines : 0;

    // Escrever as estatísticas no arquivo de saída
    outputFile << "Número total de palavras: " << totalWords << endl;
    outputFile << "Número total de linhas: " << totalLines << endl;
    outputFile << "Número médio de palavras por linha: " << averageWordsPerLine << endl;
    outputFile << "Palavra mais frequente: " << mostFrequentWord << " (ocorrências: " << maxFreq << ")" << endl;

    outputFile.close();

    cout << "Estatísticas geradas e salvas no arquivo " << outputFileName << endl;

    return 0;
}
