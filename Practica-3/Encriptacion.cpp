#include <iostream>
#include "Encriptacion.h"
using namespace std;

unsigned char rotateLeft(unsigned char value, int shift) {
    return (value << shift) | (value >> (8 - shift));
}

unsigned char rotateRight(unsigned char value, int shift) {
    return (value >> shift) | (value << (8 - shift));
}
void printBits(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1);
    }
    printf(" ");
}


void encrypt(char* text, int n, char key) {
    printf("Encriptado:\n");
    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char byte = (unsigned char)text[i];
        byte = rotateLeft(byte, n);
        byte = byte ^ (unsigned char)key;
        text[i] = (char)byte;
        printBits(byte);
    }
    printf("\n");
}

void decrypt(char* text, int n, char key) {
    printf("Desencriptado:\n");
    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char byte = (unsigned char)text[i];
        byte = byte ^ (unsigned char)key;
        byte = rotateRight(byte, n);
        text[i] = (char)byte;
        printBits(byte);
    }
    printf("\n");
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
