#include "Rule.h"
#include <iostream>
#include <string>

using namespace std;

// default Constructor
Rule::Rule()
{
    golly_string = "B3/S23";
    process_golly(golly_string);
}

void Rule::conway()
{
    golly_string = "B3/S23";
    process_golly(golly_string);
}

void Rule::golly(string new_rule)
{
    golly_string = new_rule;
    process_golly(golly_string);
}

string Rule::golly()
{
    return golly_string;
}

bool Rule::eval(bool nw, bool n, bool ne,
                bool w, bool me, bool e,
                bool sw, bool s, bool se)
{
    bool grid[9];

    grid[0] = nw;
    grid[1] = n;
    grid[2] = ne;

    grid[3] = w;
    grid[4] = me;
    grid[5] = e;

    grid[6] = sw;
    grid[7] = s;
    grid[8] = se;

    return evaluate_grid(grid);
}

bool Rule::evaluate_grid(bool grid[])
{
    // get the center of the grid
    bool center_boi = grid[4];
    int num_neighbors = 0;

    // loop through grid not including 4 and add up the neighbors
    for (size_t i = 0; i < 9; i++)
    {
        if (grid[i] && i != 4)
            num_neighbors++;
    }

    // if the center is alive then check
    // if it has the right number of neighbors to survive
    if (center_boi)
    {
        for (int val : s_vals)
            if (num_neighbors == val)
                return true;
    }
    // if it isn't check if it can be born
    else if (!center_boi)
        for (int val : b_vals)
            if (num_neighbors == val)
                return true;

    // otherwise kill it
    return false;
}

void Rule::process_golly(string golly_input)
{
    // bool bProcessed = false;
    b_vals.clear();
    s_vals.clear();

    while (!golly_input.empty())
    {

        if (golly_input[0] == 'B')
        {

            // bProcessed = true;
            golly_input.erase(0, 1);

            while (golly_input[0] != '/' && isdigit(golly_input[0]))
            {
                if (b_vals.empty() || (golly_input[0] - 48) > b_vals[b_vals.size() - 1])
                {
                    b_vals.push_back(golly_input[0] - 48);
                    golly_input.erase(0, 1);
                }
                else
                {
                    throw runtime_error("Bad golly string: " + golly_input);
                }
            }
            golly_input.erase(0, 1);
        }
        if (golly_input[0] == 'S')
        {

            // bProcessed = true;
            golly_input.erase(0, 1);

            while (isdigit(golly_input[0]))
            {
                if (s_vals.empty() || (golly_input[0] - 48) > s_vals[s_vals.size() - 1])
                {
                    s_vals.push_back(golly_input[0] - 48);
                    golly_input.erase(0, 1);
                }
                else
                {
                    throw runtime_error("Bad golly string: " + golly_input);
                }
            }
            golly_input.erase(0, 1);
        }
        else
        {
            b_vals.clear();
            s_vals.clear();
            throw runtime_error("Bad golly string: " + golly_input);
        }
    }

    if (b_vals.size() == 0)
        b_vals.push_back(0);

    if (s_vals.size() == 0)
        s_vals.push_back(0);
}
