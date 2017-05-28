#pragma once
#include "Board.h"
#include <stdio.h>
#include <stdlib.h>

class BoardView{
  private:
    Board &b;
    bool silent;
    BoardView(const BoardView& bw); //operator copy is prohibited
    void operator=(const BoardView& bw); //operator = is prohibited

  public:
    BoardView(Board &b, bool silent);
    void StartGameCycle();
    void ShowBoard() const;
};
