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

    cout << "ARGC:" << argc << " optind: " << optind << "\n";

    for (int i = optind; i < argc; i++)
    {
        if (argc - optind > 1)
            throw runtime_error("Fatal Error: too many filenames\n\tUsage: " + program_name + " <flags> filename\n");
        if (argc - optind == 0)
            throw runtime_error("Fatal Error: no filename provided\n\tUsage: " + program_name + " <flags> filename\n");
        filename = argv[i];
    }

    if (live_char == dead_char)
        throw runtime_error("Fatal Error: live character cannot be the same as dead character");

    // DEBUGGING
    cout << "Golly Input: " << golly_input << "\n"
         << "Live Char: " << live_char << "\n"
         << "Dead Char: " << dead_char << "\n"
         << "Infinite: " << infinite << "\n"
         << "Filename: " << filename << "\n";

    // Rule r();
    Board b(filename);
    system("sleep 3");
    system("clear");
    cout << b;
    system("sleep 1");
    system("clear");

    while (true)
    {
        cout << ++b;
        system("sleep 1");
        system("clear");
    }

    // call board and rule here

    return 0;
}
