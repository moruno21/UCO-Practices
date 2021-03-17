#ifndef __CHECK_BRAKETS_HPP__
#include <iostream>

/**
 * @brief Checks if the input stream has balanced brackets.
 *
 * The brackets to check are '{}', '()' and '[]'.
 * The priority is to mark the closed bracket. For example,
 * if the input was '{[}]', the return value should be 3.
 *
 * @param input is a text stream.
 * @return Returns the value 0 if all the brackets are well balanced, or the
 *         input character index for the bracket that is not balanced otherwise.
 */
size_t check_brackets(std::istream& input);

#endif //__CHECK_BRAKETS_HPP__
