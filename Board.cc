#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
// #include <sstream>

using namespace std;

Board::Board(string filename, Rule rule, char live_c, char dead_c)
{
    file = filename;
    current_rule = rule;
    live = live_c;
    dead = dead_c;

    if (filename == "")
    {
        fill_board(lines);
    }
    else
    {
        ifstream current_file(file);
        if (current_file.fail())
            throw runtime_error("The file " + file + " could not be found");
        fill_board(current_file);
    }
}

void Board::increment_generation()
{
    vector<vector<char>> temp_board = current_board;

    int height = current_board.size();
    for (int y = 0; y < height; y++)
    {

        int width = current_board[y].size();
        for (int x = 0; x < width; x++)
        {

            bool nw, n, ne,
                w, me, e,
                sw, s, se;

            // TOP
            // check nw
            nw = is_living_neighbor(x - 1, y - 1);

            // check n
            n = is_living_neighbor(x, y - 1);

            // check ne
            ne = is_living_neighbor(x + 1, y - 1);

            // MIDDLE
            // check w
            w = is_living_neighbor(x - 1, y);

            // check me
            me = is_living_neighbor(x, y);

            // check e
            e = is_living_neighbor(x + 1, y);

            // BOTTOM
            // check sw
            sw = is_living_neighbor(x - 1, y + 1);

            // check s
            s = is_living_neighbor(x, y + 1);

            // check se
            se = is_living_neighbor(x + 1, y + 1);

            // helpful debugging
            // cout << nw << n << ne << "\n"
            //      << w << me << e << "\n"
            //      << sw << s << se << "\n"
            //      << "\n";

            if (current_rule.eval(nw, n, ne, w, me, e, sw, s, se))
                temp_board[y][x] = live;
            else
                temp_board[y][x] = dead;
        }
    }
    current_board = temp_board;
}

bool Board::is_living_neighbor(int x, int y)
{
    int height = current_board.size() - 1;
    int width = current_board[0].size() - 1;

    // enforce wrap around
    if (y < 0)
        y += (height + 1);
    else if (y > height)
        y %= (height + 1);

    if (x < 0)
        x += (width + 1);
    else if (x > width)
        x %= (width + 1);

    if (current_board[y][x] == live)
    {
        return true;
    }
    return false;
}

void Board::fill_board(istream &stream)
{
    vector<char> temp;
    string line;

    // break input into lines
    while (getline(stream, line))
    {
        for (char c : line)
            if (c == live || c == dead)
                temp.push_back(c);
            else
                throw runtime_error("Error reading the file " + file + " bad character found: " + c);

        current_board.push_back(temp);
        temp.clear();
    }

    if (current_board.size() < 2)
        throw runtime_error("The grid in " + file + " must be at least 2x2");

    size_t line_size = current_board[0].size();

    if (line_size < 2)
        throw runtime_error("The grid in " + file + " must be at least 2x2");

    for (auto row : current_board)
        if (row.size() != line_size)
            throw runtime_error("Each line in " + file + " must be the same length");
}
void Board::fill_board(string line_string)
{

    stringstream stream(line_string);
    vector<char> temp;
    string line;

    // break input into lines
    while (getline(stream, line, '\n'))
    {
        for (char c : line)
            if (c == live || c == dead)
                temp.push_back(c);
            else
                throw runtime_error("Error reading the file " + file + " bad character found: " + c);

        current_board.push_back(temp);
        temp.clear();
    }

    if (current_board.size() < 2)
        throw runtime_error("The grid in " + file + " must be at least 2x2");

    size_t line_size = current_board[0].size();

    if (line_size < 2)
        throw runtime_error("The grid in " + file + " must be at least 2x2");

    for (auto row : current_board)
        if (row.size() != line_size)
            throw runtime_error("Each line in " + file + " must be the same length");
}

Board Board::operator++()
{
    increment_generation();
    return *this;
}

ostream &
operator<<(ostream &stream, const Board &brd)
{
    for (size_t i = 0; i < brd.current_board.size(); i++)
    {
        for (size_t j = 0; j < brd.current_board[i].size(); j++)
        {
            stream << brd.current_board[i][j];
        }
        stream << "\n";
    }
    // stream << "\n";
    return stream;
}
