#include <iostream>
#include "Encriptacion.h"
using namespace std;

unsigned char rotateLeft(unsigned char value, int shift) {
    return (value << shift) | (value >> (8 - shift));
}

unsigned char rotateRight(unsigned char value, int shift) {
    return (value >> shift) | (value << (8 - shift));
}

// Encriptar: primero rota izquierda, luego XOR
void encrypt(char* text, int n, char key) {
    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char byte = (unsigned char)text[i];
        byte = rotateLeft(byte, n);
        byte = byte ^ key;
        text[i] = (char)byte;
    }
}

// Desencriptar: primero XOR, luego rota derecha
void decrypt(char* text, int n, char key) {
    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char byte = (unsigned char)text[i];
        byte = byte ^ key;
        byte = rotateRight(byte, n);
        text[i] = (char)byte;
    }
}

int main_encriptacion() {
    try {
        char text[256];
        int n;
        char key;

        cout << "Ingrese un texto: ";
        cin.getline(text, 256);

        if (text[0] == '\0') throw invalid_argument("El texto está vacío.");

        cout << "Ingrese el valor de rotación n: ";
        cin >> n;

        if (n <= 0 || n >= 8) throw invalid_argument("El valor de n debe estar entre 1 y 7.");

        cout << "Ingrese la clave K: ";
        cin >> key;

        char original[256];
        int len = 0;
        for (int i = 0; text[i] != '\0'; i++) {
            original[i] = text[i];
            len++;
        }
        original[len] = '\0';
        encrypt(text, n, key);
        cout << "Texto encriptado: ";
        for (int i = 0; text[i] != '\0'; i++) {
            cout << (int)(unsigned char)text[i] << " ";
        }
        cout << endl;


        decrypt(text, n, key);
        cout << "Texto desencriptado: " << text << endl;


        bool igual = true;
        for (int i = 0; original[i] != '\0' || text[i] != '\0'; i++) {
            if (original[i] != text[i]) {
                igual = false;
                break;
            }
        }

        if (igual) {
            cout << "Verificación exitosa!" << endl;
        } else {
            cout << "Error: no coinciden." << endl;
        }

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
