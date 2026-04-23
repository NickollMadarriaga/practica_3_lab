#include <iostream>
#include <cstring>
using namespace std;

void xorCipher(char* text, char key) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = text[i] ^ key;
    }
}

int main() {
    try {
        char text[256];
        char key;

        cout << "Ingrese un texto: ";
        cin.getline(text, 256);

        if (text[0] == '\0') throw invalid_argument("El texto está vacío.");

        cout << "Ingrese la clave (un carácter): ";
        cin.get(key);

        // Encriptar
        char encrypted[256];
        for (int i = 0; text[i] != '\0'; i++) {
            encrypted[i] = text[i];
        }
        encrypted[strlen(text)] = '\0';

        xorCipher(encrypted, key);
        cout << "Texto encriptado: " << encrypted << endl;

        // Desencriptar (aplicar XOR de nuevo con la misma clave)
        xorCipher(encrypted, key);
        cout << "Texto desencriptado: " << encrypted << endl;

        // Verificar
        bool igual = true;
        for (int i = 0; text[i] != '\0' || encrypted[i] != '\0'; i++) {
            if (text[i] != encrypted[i]) {
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
