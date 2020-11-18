#include "Board.h"
#include "Rule.h"
#include "Board.h"
#include "Rule.h"
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

string program_name;

int main(int argc, char *argv[])
{
    program_name = argv[0];

    string golly_input = "B3/S23";
    string filename = "";
    vector<int> s_vals;
    vector<int> b_vals;
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
        case 'i':
            infinite = true;
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
        if (argc - optind != 1)
        {
            cerr << program_name << " ERROR: Incorrect Usage: too many filenames\n\t" << program_name << " <flags> filename\n";
            return 1;
        }
        filename = argv[i];
    }

    if (live_char == dead_char)
        throw runtime_error("live character cannot be the same as dead character");

    // DEBUGGING
    // cout << "Golly Input: " << golly_input << "\n"
    //      << "Live Char: " << live_char << "\n"
    //      << "Dead Char: " << dead_char << "\n"
    //      << "Infinite: " << infinite << "\n"
    //      << "Filename: " << filename << "\n";

    // call board and rule here

    return 0;
}
