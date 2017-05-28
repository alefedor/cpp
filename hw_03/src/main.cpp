#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "huffman.h"

using namespace std;

void parseError(){
    cerr << "Invalid arguments\n";
    exit(1);
}

void parseArgs(int pos, char** argv, char* &type, char* &fin, char* &fout){
    if (pos == 6)
        return;
    if (strcmp(argv[pos], "-c") == 0 || strcmp(argv[pos], "-u") == 0){
        type = argv[pos];
        parseArgs(pos + 1, argv, type, fin, fout);
    }else
    if (strcmp(argv[pos], "-f") == 0 || strcmp(argv[pos], "--file") == 0){
        if (pos + 1 == 6)
            parseError();
        fin = argv[pos + 1];
        parseArgs(pos + 2, argv, type, fin, fout);
    }else
    if (strcmp(argv[pos], "-o") == 0 || strcmp(argv[pos], "--output") == 0){
        if (pos + 1 == 6)
            parseError();
        fout = argv[pos + 1];
        parseArgs(pos + 2, argv, type, fin, fout);
    }else
        parseError();
}

void checkFiles(ifstream &in, ofstream &out){
    if (!in.good() || !out.good()){
        if (!in.good())
            cerr << "Error on opening file for reading\n";
        if (!out.good())
            cerr << "Error on opening file for writing\n";
        exit(2);
    }
}

int main(int argc, char **argv){
    ios_base::sync_with_stdio(0);
    if (argc != 6)
        parseError();
    char *type = NULL, *fin = NULL, *fout = NULL;
    parseArgs(1, argv, type, fin, fout);
    if (!type || !fin || !fout)
        parseError();
    Archiver ar;
    try{
        if (type[1] == 'c'){
            ifstream in(fin, ifstream::binary);
            ofstream out(fout, ofstream::binary);
            checkFiles(in, out);
            ar.pack(in, out);
        }else{
            ifstream in(fin, ifstream::binary);
            ofstream out(fout, ofstream::binary);
            checkFiles(in, out);
            ar.unpack(in, out);
        }
    }
    catch (ArchiverException &e){
        cerr << e.what() << "\n";
    }
    return 0;
}
