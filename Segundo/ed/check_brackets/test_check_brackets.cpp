#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include "check_brackets.hpp"

int
main(int argc, const char* argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: check_brackets filename" << std::endl;
            return EXIT_FAILURE;
        }
        std::ifstream input (argv[1]);
        if (!input)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            std::cerr << "Usage: check_brackets filename" << std::endl;
            return EXIT_FAILURE;
        }
        size_t pos = check_brackets(input);
        if (pos==0)
            std::cout << "Success" << std::endl;
        else
            std::cout << pos << std::endl;
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

