#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <utility>

#include "alphabet_soup.hpp"


/**
 * @brief Define the result of a scanning process.
 * It is a pair <first-item, second-item>.
 * The first item is the string with the found key if any.
 * The second item is a stack of pairs <row,col> which are the coordinates
 *   of the key's letters in the soup grid.
 */
typedef std::pair<std::string, std::stack <std::pair<int, int> >> ScanResult;

/**
 * @brief Solve a alphabet soup.
 * @param soup is the alphabet soup to be resolved.
 * @param words are the words to look for.
 * @return a vector of pairs <word, cells_coordinates [row,col]>, one for
 *         each found word.
 */
std::vector<ScanResult>
alphabet_soup_solver(AlphabetSoup& soup, std::vector<std::string> const& words);

