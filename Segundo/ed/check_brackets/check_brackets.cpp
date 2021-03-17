#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include "check_brackets.hpp"
#include "stack.hpp"

class Bracket
{
public:
    Bracket()
        : _c(0), _pos(0)
    {
    }
    Bracket(char c, size_t pos)
        : _c(c), _pos(pos)
    {
    }

    bool match_with(char o) const
    {
        return ((_c == '{' && o == '}') ||
                (_c == '[' && o == ']') ||
                (_c == '(' && o == ')'));
    }
    size_t pos() const
    {
        return _pos;
    }
    bool operator==(Bracket const &other) const
    {
        return _c == other._c && _pos == other._pos;
    }

protected:
    char _c;
    size_t _pos;
};

size_t
check_brackets(std::istream &input)
{
    size_t pos = 0;
    bool unbalanced_found = false;
    auto stack = Stack<Bracket>::create();
    char next_c;
    while (input && !unbalanced_found)
    {
        ++pos;
        input >> next_c;
        if (input)
        {
            if (next_c == '(' || next_c == '{' || next_c == '[')
            {
                //TODO: process an opening bracket.
                Bracket bracket_first(next_c, pos);
                stack->push(bracket_first);
            }
            else if (next_c == ')' || next_c == '}' || next_c == ']')
            {
                //TODO: process a closing bracket. */
                if (stack->is_empty() || stack->top().match_with(next_c) == false)
                {
                    Bracket bracket_second(next_c, pos);
                    stack->push(bracket_second);
                    unbalanced_found = true; //Y asi salimos del while
                }

                else
                {
                    stack->pop();
                }
            }
        }
    }

    size_t ret_val = 0;

    //TODO: Compute the return value.
    if (unbalanced_found == true) //Entramos si hemos encontrado un desbalance
    {
        ret_val = pos;
        }

    else if (stack->is_empty() == false) //Solo entramos si la pila no se ha vaciado
    {
        ret_val = stack->top().pos();
    }

    return ret_val;
}
