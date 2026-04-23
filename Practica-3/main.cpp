#include <iostream>
#include "LZ78.h"
#include "RLE.h"
#include "Encriptacion.h"
using namespace std;

int main() {
    int opcion;

    cout << "=== MENU ===" << endl;
    cout << "1. RLE" << endl;
    cout << "2. LZ78" << endl;
    cout << "3. Encriptacion" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    cin.ignore(); // limpiar el buffer antes de getline

    if (opcion == 1) {
        main_RLE();
    } else if (opcion == 2) {
        main_LZ78();
    } else if (opcion == 3) {
        main_encriptacion();
    } else {
        cout << "Opcion no válida." << endl;
    }

    return 0;
}
