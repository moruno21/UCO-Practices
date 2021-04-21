#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <string>

#include "alphabet_soup_solver.hpp"

std::istream&
load_words(std::istream& in, std::vector<std::string>& words)
{
    size_t n_words;
    in >> n_words;
    if (in)
    {
        in.ignore(); //remove newline.
        words.resize(n_words);
        for(size_t i=0;i<n_words && (in >> words[i]); ++i);
    }
    return in;
}

int
main(int argc, const char* argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
        std::ifstream input_file (argv[1]);
        if (!input_file)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
        std::vector<std::string> words;
        if (! load_words(input_file, words))
        {
            std::cerr << "Error: worng input format. Could not read the words list." << std::endl;
            return  EXIT_FAILURE;
        }
        AlphabetSoup soup;
        input_file >> soup;
        if (!input_file)
        {
            std::cerr << "Error: worng input format. Could not read the soup." << std::endl;
            return  EXIT_FAILURE;
        }
        auto results = alphabet_soup_solver(soup, words);
        for (size_t i=0; i<results.size(); ++i)
        {
            std::cout << results[i].first << ':';
            while(!results[i].second.empty())
            {
                auto cell = results[i].second.top();
                std::cout << " [" << cell.first+1 << ',' << cell.second+1 << ']';
                results[i].second.pop();
            }
            std::cout << std::endl;
        }
    }
    catch(std::runtime_error &e)
    {
        std::cerr << "Run time exception: " << e.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }
    catch(...)
    {
        std::cerr << "Catched unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}

