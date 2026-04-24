#include <iostream>
#include <string>
#include "RLE.h"
using namespace std;

string rleCompress(const string& input) {
    string result = "";
    int count = 1;

    for (int i = 0; i < input.length(); i++) {
        if (i + 1 < input.length() && input[i] == input[i + 1]) {
            count++;
        } else {
            result += input[i];
            result += "/";
            result += to_string(count);
            result += "/";
            count = 1;
        }
    }

    return result;
}


string rleDecompress(const string& input) {
    string result = "";
    int i = 0;

    while (i < input.length()) {
        char c = input[i];
        i += 2;

        string numStr = "";

        while (i < input.length() && input[i] != '/') {
            numStr += input[i];
            i++;
        }

        i++;

        int count = stoi(numStr);

        for (int j = 0; j < count; j++) {
            result += c;
        }
    }

    return result;
}


int main_RLE() {
    try {
        string input;
        cout << "Ingrese una cadena de texto: ";
        getline(cin, input);

        if (input.empty()) throw invalid_argument("La cadena está vacía.");

        string compressed = rleCompress(input);
        cout << "Comprimido: " << compressed << endl;

        string decompressed = rleDecompress(compressed);
        cout << "Descomprimido: " << decompressed << endl;

        if (input == decompressed) {
            cout << "Verificación exitosa!" << endl;
        } else {
            cout << "Error: no coinciden." << endl;
        }

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
