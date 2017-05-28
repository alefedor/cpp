#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cassert>

enum class State:char{
    Draw, OWins, XWins, NotFinished
};

class Board{
  private:
    char **data;
    Board(const Board& b); //operator copy is prohibited
    void operator=(const Board& b); //operator = is prohibited

  public:
    Board();
    ~Board();
    void Move(int x, int y, char c);
    bool CanMove(int x, int y) const;
    State IsWin() const;
    char GetCell(int x, int y) const;
    State GetPlayer(char c) const;
    bool Check(int i, int j, int dx, int dy) const;
};
