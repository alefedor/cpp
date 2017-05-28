#include "../include/BoardView.h"
#include <cstdio>

BoardView::BoardView(Board &b, bool silent = false):b(b), silent(silent){}

void BoardView::ShowBoard() const{
    printf("\n");
    for (size_t i = 0; i < 10; i++){
        for (size_t j = 0; j < 10; j++)
            printf("%c", b.GetCell(i, j));
        printf("\n");
    }
}

void BoardView::StartGameCycle(){
    bool cur_player = 0;
    char players[] = {'O', 'X'};
    while (b.IsWin() == State::NotFinished){
        int x = -1, y = -1;
        if (!this -> silent)
            ShowBoard();
        while (true){
            printf("%c move: ", players[cur_player]);
            scanf("%d%d", &x, &y);
            if (x == -1 && y == -1)
                return;
            if (b.CanMove(x, y))
                break;
            printf("Bad move!\n");
        }
        b.Move(x, y, players[cur_player]);
        cur_player = 1 - cur_player;
    }
    ShowBoard();
    State st = b.IsWin();
    if (st == State::Draw)
        printf("Draw.\n");
    else
    if (st == State::OWins)
        printf("O wins!\n");
    else
        printf("X wins!\n");
}
