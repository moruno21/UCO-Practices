#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

#include "ip_utils.hpp"
#include "hash_table.hpp"
#include "dos_detector.hpp"

/** @brief Load the log from an stream.*/
std::istream&
operator>>(std::istream& in, Log& log)
{
    log.resize(0);
    while(in)
    {
        LogEntry entry;
        in >> entry.time >> entry.ip;
        if (in)
        {
            log.push_back(entry);
        }
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

        size_t m;
        input_file >> m;
        if (!input_file)
        {
            std::cerr << "Error: wrong input format in filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }
        int max_acc;
        input_file >> max_acc;
        if (!input_file)
        {
            std::cerr << "Error: wrong input format in filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }
        Log log;
        input_file >> log;
        if (!input_file && !input_file.eof())
        {
            std::cerr << "Error: wrong input format in filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }

        dos_detector(log, max_acc, m);

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

