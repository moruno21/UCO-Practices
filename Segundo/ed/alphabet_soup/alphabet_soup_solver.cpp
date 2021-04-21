#include "alphabet_soup_solver.hpp"
#include "trie.hpp"

/**
 * @brief scan a cell looking for the next letter of a word.
 * @param row and
 * @param col are the current cell coordinates.
 * @param dy and
 * @param dx are direction vector to follow the next letter.
 * @param soup is the alphabet soup where looking for.
 * @param node is the current node of the trie.
 * @param scan_result save the current chain. Is a pair of <word, cells_coordinates [row,col]>
 *
 */
void
scan_cell(int row, int col, int dy, int dx, AlphabetSoup const& soup,
          TrieNode::Ref node,
          ScanResult & scan_result)
{
    //ALGORITHM
    //1. If this node is a leaf node (Leaf nodes has value != "").
    //1.1 Save the word in the first item of the scan_result pair and finish recursion.
    //2. Else, we can have tree cases.
    //2.1.1 This is the first letter of word (dx==dy==0)
    //2.1.2 Scan all the 3x3 neighbourhood for the next letter.
    //2.2.1 This is a next right letter, so we need scan the next in the direction (dy, dx).
    //2.3 if a word was found (first item of the scan_result pair != ""), we push the current
    //    cell's coordinates [row,col] into the second item of scan_result.

    if (node->value() != "")
    {
        //Case 0: This node has a key value
        //so we have just found a word and stop the recursion.
        //TODO: update scan_result.first with the key value found.

        //
    }
    else
    {
        if (row>=0 && row<soup.rows() && col>=0 && col<soup.cols())
        {
            auto const cell_v = soup.cell(row, col);
            if (node->has(cell_v))
            {
                //Recursion case: looking for the next letter.

                node = node->child(cell_v);
                bool found = false;
                if (dx == 0 && dy == 0)
                {
                    //TODO:
                    //Case 1: It is the first letter, so we must scan all eight
                    //neighbours, if possible, to find a word.
                    for (int i = std::max(row-1, 0); i<std::min(row+2, soup.rows()) && !found; ++i)
                        for (int j = std::max(col-1, 0); j< std::min(col+2, soup.cols()) && !found; ++j)
                        {
                            if (i!=row || j!=col) //we don't want to scan the central cell again.
                            {
                                //TODO
                                //recursive call to scan_cell to scan for the
                                //next letter in the direction dy=i-row, dx=j-col.



                                //
                                //found a word?
                                found = (scan_result.first != "");
                            }
                        }
                }
                else
                {
                    //TODO:
                    //Case 2: It is middle letter, so we follow the scanning
                    //direction (dx,dy) if we can.

                    //
                    //Found a word?
                    found = (scan_result.first != "");
                }
                if (found)
                {
                    //TODO
                    //A word was found for this chain so push the current cell
                    //coordinates pair <row,cols> into the
                    //stack scan_result.second


                    //
                }
            }
            //else Case 3: This chain is not a valid key prefix.
        }
        //else Case 4: We are out of the soup grid so this is not a valid word.
    }
}

std::vector< ScanResult >
alphabet_soup_solver(AlphabetSoup& soup, std::vector<std::string> const& words)
{
    std::vector< ScanResult > results;
    auto trie = Trie::create();

    //Generate a trie with the words to be found as keys.
    for (size_t i = 0; i<words.size(); ++i)
        trie->insert(words[i]);

    //We scan all the soup to find a first letter of any key.
    for (int row = 0; row < soup.rows(); ++row)
    {
        for (int col = 0; col < soup.cols(); ++col)
        {
            auto scan_result = std::make_pair(std::string(""),
                                              std::stack<std::pair<int,int>>());
            //Scan from this cell. This is the first letter so dx==dy==0.
            scan_cell(row, col, 0, 0, soup, trie->root(), scan_result);
            if (scan_result.first!="")
              //A word was found so save it into the results.
              results.push_back(scan_result);
        }
    }
    return results;
}

