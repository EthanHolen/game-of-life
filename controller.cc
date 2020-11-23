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

void display_bd(Board board, double t_between)
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
        timeout(t_between);
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
    double time_between = 200;
    int opt;

    // opterr = 0;

    while ((opt = getopt(argc, argv, "g:l:d:t:")) != -1)
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
        case 't':
            if (atof(optarg) <= 0)
                throw runtime_error("-t error: time interval must be larger than 0");
            time_between = 1000 * atof(optarg);
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

    // setup rule
    Rule rul;
    rul.golly(golly_input);

    // setup board
    Board my_board(filename, rul, live_char, dead_char);

    display_bd(my_board, time_between);

    return 0;
}
