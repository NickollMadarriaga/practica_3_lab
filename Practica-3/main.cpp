

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "RLE.h"
#include "LZ78.h"
#include "Encriptacion.h"

using namespace std;

string leerArchivo(string nombre) {
    ifstream file(nombre);

    if (!file) {
        throw runtime_error("No se pudo abrir el archivo");
    }

    string texto = "", linea;

    while (getline(file, linea)) {
        texto += linea;
        texto += '\n';
    }

    file.close();

    if (texto == "") {
        throw runtime_error("El archivo esta vacio");
    }

    return texto;
}

void escribirArchivo(string nombre, string contenido) {
    ofstream file(nombre);

    if (!file) {
        throw runtime_error("No se pudo escribir el archivo");
    }

    file << contenido;
    file.close();
}

int main() {

    try {

        int metodo;
        cout << "1. RLE\n2. LZ78\nOpcion: ";
        cin >> metodo;
        cin.ignore();

        if (metodo != 1 && metodo != 2) {
            throw invalid_argument("Opcion invalida");
        }

        string nombreEntrada;
        cout << "Archivo de entrada: ";
        getline(cin, nombreEntrada);

        string original = leerArchivo(nombreEntrada);

        cout << "\nTexto original:\n" << original << endl;

        string comprimido = "";

        if (metodo == 1) {

            comprimido = rleCompress(original);
            cout << "\nComprimido (RLE):\n" << comprimido << endl;

        } else {

            char input[5000];

            for (int i = 0; i < original.length(); i++) {
                input[i] = original[i];
            }
            input[original.length()] = '\0';

            Pair* compressed = new Pair[2000];
            int outputSize = 0;

            compressLZ78(input, compressed, outputSize);

            cout << "\nSalida (indice, caracter):" << endl;
            for (int i = 0; i < outputSize; i++) {
                if (compressed[i].c != '\0') {
                    cout << "(" << compressed[i].index << ", "
                         << compressed[i].c << ")" << endl;
                }
            }


            for (int i = 0; i < outputSize; i++) {
                comprimido += to_string(compressed[i].index);
                comprimido += ",";
                comprimido += to_string((unsigned char)compressed[i].c);
                if (i < outputSize - 1) comprimido += "|";
            }

            delete[] compressed;
        }

        int n;
        char key;

        cout << "\nRotacion (1-7): ";
        cin >> n;

        if (n <= 0 || n >= 8) {
            throw invalid_argument("n debe estar entre 1 y 7");
        }

        cout << "Clave: ";
        cin >> key;

        char buffer[10000];

        for (int i = 0; i < comprimido.length(); i++) {
            buffer[i] = comprimido[i];
        }
        buffer[comprimido.length()] = '\0';

        encrypt(buffer, n, key);

        cout << "\nEncriptado:\n" << buffer << endl;

        decrypt(buffer, n, key);

        string desencriptado = buffer;

        string recuperado = "";

        if (metodo == 1) {

            recuperado = rleDecompress(desencriptado);

        } else {

            Pair pares[2000];
            int count = 0;

            int i = 0;
            while (i < desencriptado.length()) {

                string idx = "";
                while (desencriptado[i] != ',') {
                    idx += desencriptado[i];
                    i++;
                }
                i++;

                    string ascii = "";
                while (i < desencriptado.length() && desencriptado[i] != '|') {
                    ascii += desencriptado[i];
                    i++;
                }
                if (i < desencriptado.length()) i++;

                pares[count].index = stoi(idx);
                pares[count].c = (char)stoi(ascii);

                count++;
            }

            char salida[5000];
            decompressLZ78(pares, count, salida);

            cout << "\nDescomprimido: " << salida << endl;

            recuperado = salida;
        }

    cout << "\nTexto recuperado:\n" << recuperado << endl;

    if (original == recuperado) {
        cout << "\nTODO BIEN\n";
    } else {
        cout << "\nERROR\n";
    }

    string nombreSalida;
    cout << "\nArchivo de salida: ";
    cin.ignore();
    getline(cin, nombreSalida);

    escribirArchivo(nombreSalida, recuperado);

}

    catch (const invalid_argument& e) {
        cout << "\nError de entrada: " << e.what() << endl;
    }

    catch (const runtime_error& e) {
        cout << "\nError de ejecucion: " << e.what() << endl;
    }

    catch (...) {
        cout << "\nError desconocido" << endl;
    }

    return 0;
}
