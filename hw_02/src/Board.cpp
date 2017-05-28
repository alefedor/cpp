#include "../include/Board.h"

Board::Board(){
    data = new char*[10];
    for (size_t i = 0; i < 10; i++)
        data[i] = new char[10];
    for (size_t i = 0; i < 10; i++)
        for (size_t j = 0; j < 10; j++)
            data[i][j] = '.';
}

Board::~Board(){
    for (size_t i = 0; i < 10; i++)
        delete []data[i];
    delete []data;
}

void Board::Move(int x, int y, char c){
    data[x][y] = c;
}

bool Board::CanMove(int x, int y) const{
    return (0 <= x && x < 10 && 0 <= y && y < 10 && data[x][y] == '.');
}

State Board::GetPlayer(char c) const{
    return (c == 'O' ? State::OWins : State::XWins);
}

bool Board::Check(int i, int j, int dx, int dy) const{
    if (data[i][j] == '.')
        return false;
    bool Equal = true;
        for (int k = 1; k < 5; k++)
            if (data[i + k * dx][j + k * dy] != data[i][j])
                Equal = false;
    return Equal;
}

State Board::IsWin() const{
    bool NoMoves = true;
    for (size_t i = 0; i < 10; i++)
        for (size_t j = 0; j < 10; j++){
            if (data[i][j] == '.')
                NoMoves = false;
            if (i >= 4){
                if (Check(i, j, -1, 0))
                    return GetPlayer(data[i][j]);
            }
            if (j >= 4){
                if (Check(i, j, 0, -1))
                    return GetPlayer(data[i][j]);
            }
            if (i >= 4 && j >= 4){
                if (Check(i, j, -1, -1))
                    return GetPlayer(data[i][j]);
            }
            if (i >= 4 && j < 6){
                if (Check(i, j, -1, 1))
                    return GetPlayer(data[i][j]);
            }
        }
    if (NoMoves)
        return State::Draw;
    else
        return State::NotFinished;
}

char Board::GetCell(int x, int y) const{
    return data[x][y];
}
