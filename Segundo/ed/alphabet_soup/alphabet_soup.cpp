#include "alphabet_soup.hpp"

std::istream&
operator>>(std::istream & in, AlphabetSoup& soup)
{
    int rows, cols;
    in >> rows >> cols;
    if (in)
    {
        soup.resize(rows, cols);
        in.ignore(); //remove newline.
        std::string row;
        for(int i=0;i<rows && in; ++i)
        {
            in >> row;
            if (in)
                soup.set_row(i, row);
        }
    }
    return in;
}

std::ostream&
operator<<(std::ostream& out, AlphabetSoup const& soup)
{
    out << soup.rows() << ' ' << soup.cols() << std::endl;
    for (int i=0;i<soup.rows();++i)
        out << soup.row(i) << std::endl;
    return out;
}


