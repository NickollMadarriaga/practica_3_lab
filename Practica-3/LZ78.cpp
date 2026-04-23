#include <iostream>
#include "LZ78.h"
#include <stdexcept>
using namespace std;

int findEntry(Entry* dict, int size, int prefix, char c) {
    for (int i = 1; i < size; i++) {
        if (dict[i].prefix == prefix && dict[i].c == c) {
            return i;
        }
    }
    return -1;
}

void compressLZ78(const char* input, Pair* output, int& outputSize) {
    Entry* dict = new Entry[1000];
    int dictSize = 1;
    int currentPrefix = 0;
    outputSize = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        int index = findEntry(dict, dictSize, currentPrefix, c);

        if (index != -1) {
            currentPrefix = index;
        } else {
            output[outputSize].index = currentPrefix;
            output[outputSize].c = c;
            outputSize++;
            dict[dictSize].prefix = currentPrefix;
            dict[dictSize].c = c;
            dictSize++;
            currentPrefix = 0;
        }
    }

    if (currentPrefix != 0) {
        output[outputSize].index = currentPrefix;
        output[outputSize].c = '\0';
        outputSize++;
    }

    delete[] dict;
}

void decompressLZ78(Pair* pairs, int size, char* result) {
    Entry* dict = new Entry[1000];
    int dictSize = 1;
    int resultLen = 0;

    for (int i = 0; i < size; i++) {
        char temp[500];
        int tempLen = 0;

        int idx = pairs[i].index;
        while (idx != 0) {
            temp[tempLen++] = dict[idx].c;
            idx = dict[idx].prefix;
        }

        for (int j = tempLen - 1; j >= 0; j--) {
            result[resultLen++] = temp[j];
        }

        if (pairs[i].c != '\0') {
            result[resultLen++] = pairs[i].c;
        }

        dict[dictSize].prefix = pairs[i].index;
        dict[dictSize].c = pairs[i].c;
        dictSize++;
    }

    result[resultLen] = '\0';
    delete[] dict;
}

int main_LZ78() {
    try {
        char input[256];
        cout << "Ingrese una cadena de texto: ";
        cin.getline(input, 256);

        if (input[0] == '\0') throw invalid_argument("La cadena está vacía.");

        Pair* compressed = new Pair[1000];
    int outputSize =0;
        compressLZ78(input, compressed, outputSize);

    cout << "Salida (indice, caracter):" << endl;
    for (int i = 0; i < outputSize; i++) {
        if (compressed[i].c != '\0') {
            cout << "(" << compressed[i].index << ", " << compressed[i].c << ")" << endl;
        }
    }

        char decompressed[5000];
        decompressLZ78(compressed, outputSize, decompressed);

        cout << "Descomprimido: " << decompressed << endl;

        bool igual = true;
        for (int i = 0; input[i] != '\0' || decompressed[i] != '\0'; i++) {
            if (input[i] != decompressed[i]) {
                igual = false;
                break;
            }
        }


        cout << (igual ? "Verificación exitosa!" : "Error: no coinciden.") << endl;

        delete[] compressed;

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}