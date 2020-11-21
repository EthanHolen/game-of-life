#include "Board.h"
#include "Rule.h"
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sstream>

using namespace std;

string program_name;

void display_bd(Board board)
{
    initscr();

    Board current_board = board;

    stringstream a;
    a << board;
    string z = a.str();
    int i = 0;

    while (1)
    {
        erase();

        ++current_board;

        stringstream temp;
        temp << current_board;

        addstr(temp.str().c_str());

        addstr("Press any key to exit");

        refresh();
        timeout(60);
        // clear();
        // refresh();
        if (getch() != ERR)
            break;
    }

    endwin();
}

int main(int argc, char *argv[])
{
    program_name = argv[0];

    string golly_input = "B3/S23";
    string filename = "";
    char live_char = 'O';
    char dead_char = '.';
    bool infinite = false;
    int opt;

    // opterr = 0;

    while ((opt = getopt(argc, argv, "g:l:d:i")) != -1)
    {
        switch (opt)
        {
        case 'g':
            golly_input = optarg;
            break;
        case 'l':
            live_char = *optarg;
            break;
        case 'd':
            dead_char = *optarg;
            break;
        case '?':
            if (optopt == 'd' || optopt == 'g' || optopt == 'l')
                cerr << "Option " << optopt << " requires an  argument\n";
            else if (isprint(optopt))
                cerr << "Unknown option " << optopt << "\n";
            else
                cerr << "Unknown option character " << optopt << ".\n";
            return 1;
        default:
            abort();
        }
    }

    for (int i = optind; i < argc; i++)
    {
        if (argc - optind > 1)
            throw runtime_error("Fatal Error: too many filenames\n\tUsage: " + program_name + " <flags> filename\n");
        filename = argv[i];
    }

    if (live_char == dead_char)
        throw runtime_error("Fatal Error: live character cannot be the same as dead character");

    // DEBUGGING
    // cout << "Golly Input: " << golly_input << "\n"
    //      << "Live Char: " << live_char << "\n"
    //      << "Dead Char: " << dead_char << "\n"
    //      << "Infinite: " << infinite << "\n"
    //      << "Filename: " << filename << "\n";

    // setup rule
    Rule rul;

    rul.golly(golly_input);

    // setup board

    // Board b(filename, rl, live_char, dead_char);
    Board my_board(filename, rul, live_char, dead_char);

    //ncurses setup

    display_bd(my_board);

    // call board and rule here

    return 0;
}
