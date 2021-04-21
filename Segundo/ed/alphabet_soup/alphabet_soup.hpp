#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

/** @brief Models an alfabet soup. */
class AlphabetSoup
{
public:
    /** @name Life cicle.*/
    /** @{*/

    /** @brief constructor. */
    AlphabetSoup(int rows=0, int cols=0):
        alphabet_soup_(static_cast<size_t>(rows),
                       std::string(static_cast<size_t>(cols), ' ')),
        cols_(cols)
    {}

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /** @brief how many rows there are?*/
    int rows() const
    {
       return static_cast<int>(alphabet_soup_.size());
    }

    /** @brief how many columns there are?*/
    int cols() const
    {
        return cols_;
    }

    /** @brief Get the contents of a cell.
     * @pre 0<=row<rows()
     * @pre 0<=col<cols()
     */
    char cell(int r, int c) const
    {
        assert(0<=r && r<rows());
        assert(0<=c && c<cols());
        return row(r)[static_cast<size_t>(c)];
    }

    /**
     * @brief Get read only reference to a row of the soup.
     * @return a ro reference to the row.
     * @pre 0<=row<rows()
     */
    std::string const& row(int row) const
    {
        assert(0<=row && row<rows());
        return alphabet_soup_[static_cast<size_t>(row)];
    }

    /** @} */

    /** @name Modifiers.*/
    /** @{*/

    /**
     * @brief set a row.
     * @pre 0<=row<rows()
     * @pre row_v.size()==cols()
     */
    void set_row(int row, std::string& row_v)
    {
        assert(0<=row && row<rows());
        assert(static_cast<int>(row_v.size()) == cols());
        alphabet_soup_[static_cast<size_t>(row)] = row_v;
    }

    /**
     * @brief set the content of a cell.
     * @pre 0<=row<rows()
     * @pre 0<=col<cols()
     * @pre v.size()==1
     */
    void set_cell(int row, int col, char v)
    {
        assert(0<=row && row<rows());
        assert(0<=col && col<cols());
        alphabet_soup_[static_cast<size_t>(row)][static_cast<size_t>(col)] = v;
    }

    /**
     * @brief resize the soup.
     * @post rows()==rows.
     * @post cols()==cols.
     * @post cell()==" " for all cells.
     */
    void resize(int rows, int cols)
    {
        cols_=cols;
        alphabet_soup_.resize(static_cast<size_t>(rows),
                              std::string(static_cast<size_t>(cols), ' '));
    }

    /** @} */

protected:
    std::vector<std::string> alphabet_soup_;
    int cols_;
};

/** @brief load a soup from an input stream.*/
std::istream& operator>> (std::istream& in, AlphabetSoup& soup);

/** @brief output a soup to an output stream.*/
std::ostream& operator<< (std::ostream& in, AlphabetSoup const& soup);


