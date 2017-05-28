#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Board.h"
#include "../include/BoardView.h"



int main(int argc, char **argv){
    bool silent = true;
    if (argc < 2 || strcmp(argv[1], "silent") != 0)
        silent = false;
    Board b;
    BoardView bw(b, silent);
    bw.StartGameCycle();
    return 0;
}
