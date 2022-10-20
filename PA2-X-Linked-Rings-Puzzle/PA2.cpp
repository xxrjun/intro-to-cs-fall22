/**
 * @file PA2.cpp
 * @author NCU MIS 109403019 鄒翔宇 [@xxrjun](https://github.com/xxrjun)
 * @brief
 * @version 0.1
 * @date 2022-10-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <math.h>
#include <string>

using namespace std;

/* Declaration of functions */
void get_input_state(int x, int *x_linked_ring);                   // Get the input state of X-Linked Ring from user.
void display_x_linked_ring(int x, int *x_linked_ring);             // Display entire X-Linked ring
void S_rule(int end_idx, int *x_linked_ring, int *operation_info); // Doing S-Rule, operation info [idx_turned, turn_up_or_down(1:up, 0:down)]
void R_rule(int end_idx, int *x_linked_ring, int *operation_info); // Doing R-Rule, operation info [idx_turned, turn_up_or_down(1:up, 0:down)]
int solving_rings(int x, int *x_linked_ring, int *operation_info); // Solving X-Linked rings, return total steps to solve.
int finite_automation_function(int x, const int *input);           // returns the last number of input after doing finite automation function for solving X-Linked rings
bool is_solved(int x, int *x_linked_ring);                         // Returns true if X-Linked Rings is solved.
string get_ordinal(int num);                                       // Returns the ordinal string of input number.
int perfect_steps_to_solve(int x);                                 // [unused] Returns the number of minimum steps to solve.

/* Declaration of helper functions*/
void get_input_state(int counter, int x, int *x_linked_ring);                                     // helper function for get_input_state()
void display_x_linked_ring(int counter, int x, int *x_linked_ring);                               // helper function for display_x_linked_ring()
int solve_with_a_rule(char rule, int x, int *x_linked_ring, int *operation_info);                 // helper function for solving_rings(). Solve X-Linked Rings with S or R Rule
int finite_automation_function(char mode, int counter, int x, int last_number, const int *input); // helper function for finite_automation_function.
bool is_solved(int counter, int x, int *x_linked_ring);                                           // helper function for is_solved()

/* Entry point */
int main()
{
    int x = 0;
    int *operation_info = new int[2];

    /* Get how many X-Linekd Ring would be solve. */
    cout << "Welcome to play X-Linked Ring!" << endl;
    cout << "How many X-Linked Ring do you want to solve?" << endl;
    cin >> x;
    cout << endl;

    int *x_linked_ring = new int[x];

    /* Get input state of X-Linked Ring. */
    cout << "What the " << x << "-Linked Ring look like?" << endl;
    cout << "Please enter the rings state from inside to outside." << endl;
    cout << "If the ring is on the sword, please input 1. Otherwise, please enter 0." << endl;
    get_input_state(0, x, x_linked_ring); /* Using recursion function to get user */
    cout << endl;

    /* Print out current state of X-Linked Ring and two rules effects*/
    cout << "The rings state of " << x << "-Linked Ring is: ";
    display_x_linked_ring(x, x_linked_ring);
    cout << "If run R-rule once,the rings state of " << x << "-Linked Ring is : ";
    R_rule(x - 1, x_linked_ring, operation_info);
    display_x_linked_ring(x, x_linked_ring);
    R_rule(x - 1, x_linked_ring, operation_info); // reverse back;
    cout << "If run S-rule once,the rings state of " << x << "-Linked Ring is : ";
    S_rule(x - 1, x_linked_ring, operation_info);
    display_x_linked_ring(x, x_linked_ring);
    S_rule(x - 1, x_linked_ring, operation_info); // reverse back;
    cout << endl;

    /* Solving Rings */
    int total_steps = solving_rings(x, x_linked_ring, operation_info);
    cout << endl;

    /* Finished, print steps to solve and say goodbye.*/
    cout << "The " << x << "-Linked Ring is solved in " << total_steps << " step." << endl;
    cout << "Thanks for using!! Goodbye ~" << endl;

    return 0;
}

/* Implementation of functions */

/**
 * @brief Get the input state of X-Linked Ring from user.
 *
 * @param x
 * @param x_linked_ring
 */
void get_input_state(int x, int *x_linked_ring)
{
    int counter = 0;
    get_input_state(counter, x, x_linked_ring);
}

void get_input_state(int counter, int x, int *x_linked_ring)
{

    if (counter == x)
        return;

    cout << "What the state of " << get_ordinal(counter + 1) << " rings?" << endl;

    int input = 0;
    cin >> input;
    /* Exit program if input is invalid*/
    if (input != 0 && input != 1)
    {
        exit(0);
    }
    x_linked_ring[counter] = input;

    get_input_state(counter + 1, x, x_linked_ring);
}

/**
 * @brief Display entire X-Linked Ring.
 *
 * @param x
 * @param x_linked_ring
 */
void display_x_linked_ring(int x, int *x_linked_ring)
{
    int counter = 0;
    display_x_linked_ring(counter, x, x_linked_ring);
    cout << endl;
}

void display_x_linked_ring(int counter, int x, int *x_linked_ring)
{
    if (counter == x)
    {
        return;
    }

    cout << x_linked_ring[counter];

    display_x_linked_ring(counter + 1, x, x_linked_ring);
}

/**
 * @brief Doing S-Rule for X-Linked Ring.
 *
 * @param end_idx
 * @param x_linked_ring
 * @return int* x_linked_ring after S-Rule
 */
void S_rule(int end_idx, int *x_linked_ring, int *operation_info)
{
    /* Not found.*/
    if (end_idx == 0)
    {
        return;
    }

    /* Done S_rule and return X-Linked Ring*/
    if (x_linked_ring[end_idx] == 1)
    {
        operation_info[0] = end_idx - 1;

        if (x_linked_ring[end_idx - 1] == 0)
        {
            x_linked_ring[end_idx - 1] = 1;
            operation_info[1] = 1;
        }
        else
        {
            x_linked_ring[end_idx - 1] = 0;
            operation_info[1] = 0;
        }

        return;
    }

    /* Other cases */
    S_rule(end_idx - 1, x_linked_ring, operation_info);
}

/**
 * @brief Doing R-Rule for X-Linked Ring.
 *
 * @param end_idx
 * @param x_linked_ring
 */
void R_rule(int end_idx, int *x_linked_ring, int *operation_info)
{
    operation_info[0] = end_idx;

    if (x_linked_ring[end_idx] == 0)
    {
        x_linked_ring[end_idx] = 1;
        operation_info[1] = 1;
    }
    else
    {
        x_linked_ring[end_idx] = 0;
        operation_info[1] = 0;
    }
}

/**
 * @brief Sovling X-Linked Rings
 *
 * @param x
 * @param x_linked_ring
 */
int solving_rings(int x, int *x_linked_ring, int *operation_info)
{
    cout << "That start to solve the " << x << "-Linked Ring." << endl;

    char start_rule = '0';
    int counter = 0;

    int last_number_after_automation_function = finite_automation_function(x, x_linked_ring);

    if (last_number_after_automation_function == 0) // even number, start solving steps in S->R->S->...
    {
        cout << "Start with S-rule !!" << endl;
        start_rule = 'S';
        counter = solve_with_a_rule(start_rule, x, x_linked_ring, operation_info);
    }
    else // odd number, start solving steps in R->S->R->...
    {
        cout << "Start with R-rule !!" << endl;
        start_rule = 'R';
        counter = solve_with_a_rule(start_rule, x, x_linked_ring, operation_info);
    }

    return counter;
}

int solve_with_a_rule(char rule, int x, int *x_linked_ring, int *operation_info)
{
    if (is_solved(x, x_linked_ring))
    {
        return 0;
    }

    if (rule == 'S')
    {
        S_rule(x - 1, x_linked_ring, operation_info);
        rule = 'R';
    }
    else
    {
        R_rule(x - 1, x_linked_ring, operation_info);
        rule = 'S';
    }

    string turn = operation_info[1] == 1 ? "up" : "down";

    cout << "!! Turn the " << get_ordinal(operation_info[0] + 1) << " ring " << turn << " !!" << endl;
    cout << "The rings state of " << x << "-Linked Ring is: ";
    display_x_linked_ring(x, x_linked_ring);
    cout << endl;

    return 1 + solve_with_a_rule(rule, x, x_linked_ring, operation_info);
}

/**
 * @brief Finite Automation function for sovling X-Linked Ring
 *
 * @param input
 * @return int
 */
int finite_automation_function(int x, const int *input)
{

    char mode = 'n'; // n meas normal, s means 0, 1 should be swtich
    int last_number = 0;

    last_number = finite_automation_function(mode, 0, x, last_number, input);

    return last_number;
}

int finite_automation_function(char mode, int counter, int x, int last_number, const int *input)
{
    if (counter == x)
    {
        return last_number;
    }

    int input_num = input[counter];

    if (mode == 'n') // normal mode
    {

        last_number = input_num;

        if (last_number == 1)
        {
            /* Change to be switch mode*/
            mode = 's';
        }
    }
    else // switch mode
    {
        last_number = 1 ? input_num == 0 : 0;

        if (last_number == 0)
        {
            /* Change to be normal mode*/
            mode = 'n';
        }
    }

    return finite_automation_function(mode, counter + 1, x, last_number, input);
}

/**
 * @brief Get the perfect steps to solve X-Linked Ring.
 *
 * @param x
 * @return int
 */
int get_steps_to_solve(int x)
{
    return (pow(2, x + 1) + ((pow(-1, x + 1) - 1) / 2) - 1) / 3;
}

/**
 * @brief Whether the X-Linked Ring is solved.
 *
 * @param x
 * @param x_linked_ring
 * @return true if the X-Linked Ring is solved, otherwise false
 */
bool is_solved(int x, int *x_linked_ring)
{
    int counter = 0;

    return is_solved(counter, x, x_linked_ring);
}

bool is_solved(int counter, int x, int *x_linked_ring)
{
    if (counter == x)
    {
        return true;
    }

    if (x_linked_ring[counter] == 1)
    {
        return false;
    }

    return is_solved(counter + 1, x, x_linked_ring);
}

/**
 * @brief Get the ordinal string of input number
 *
 * @param num
 * @return string
 */
string get_ordinal(int num)
{
    switch (num)
    {
    case 1: // 1st
        return "1st";
    case 2: // 2nd
        return "2nd";
    case 3: // 3rd
        return "3rd";
    default: // nth
        return to_string(num) + "th";
    }
}