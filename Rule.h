#ifndef RULE_H_INCLUDED
#define RULE_H_INCLUDED

#include <iostream>
#include <vector>

class Rule
{
public:
    // functions
    Rule();                  // default constructor
    ~Rule() = default;       // Destructor
    void conway();           // sets golly_string to conways rule
    void golly(std::string); // sets a different golly string
    std::string golly();     // returns current golly_string in effect
    bool eval(bool, bool, bool,
              bool, bool, bool,
              bool, bool, bool); // evaluates board arguments with golly_string

private:
    //  vars
    std::string golly_string;
    std::vector<int> s_vals;
    std::vector<int> b_vals;

    // functions
    bool evaluate_grid(bool[]);
    void process_golly(std::string);
};

#endif
