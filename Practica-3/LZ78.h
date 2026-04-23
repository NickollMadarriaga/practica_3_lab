#ifndef LZ78_H
#define LZ78_H
#include <iostream>
using namespace std;

struct Entry {
    int prefix;
    char c;
};

struct Pair {
    int index;
    char c;
};

int findEntry(Entry* dict, int size, int prefix, char c);
void compressLZ78(const char* input, Pair* output, int& outputSize);
void decompressLZ78(Pair* pairs, int size, char* result);
int main_LZ78();

#endif
