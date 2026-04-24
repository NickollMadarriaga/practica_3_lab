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


