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


