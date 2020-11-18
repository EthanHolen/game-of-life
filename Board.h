#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include "Rule.h"

class Board
{
public:
    Board(std::string, Rule rule = Rule(), char live_c = 'O', char dead_c = '.'); //default constructor
    ~Board() = default;                                                           // Destructor
    Board operator++();                                                           //pre-increment
    friend std::ostream &operator<<(std::ostream &, const Board &);               // output

private:
    void fill_board(std::istream &);
    void increment_generation();
    bool is_living_neighbor(int x, int y);

    std::vector<std::vector<char>> current_board;
    std::string file;
    Rule current_rule;
    char live;
    char dead;
};

#endif
