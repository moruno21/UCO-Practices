#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

#include "ip_utils.hpp"
#include "hash_table.hpp"

std::istream&
operator>>(std::istream& in, std::vector<int>& v)
{
    size_t size;
    in >> size;
    if (in)
    {
        v.resize(size);
        for (size_t i=0;i<size && in; ++i)
            in >> v[i];
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
        HashTable<IP, int, IpToInt> hash_table(m);
        std::string command;
        while(input_file >> command)
        {
            if (command=="hash")
            {
                IP ip;
                input_file >> ip;
                size_t k = IpToInt()(ip);
                std::cout << hash_table.hash(k) << std::endl;
            }
            else if (command == "has")
            {
                IP ip;
                input_file >> ip;
                std::cout << (hash_table.has(ip) ? "yes" : "no") << std::endl;
            }
            else if (command=="insert")
            {
                IP ip;
                input_file >> ip;
                hash_table.insert(ip, 0);
            } else if (command=="find")
            {
                IP ip;
                input_file >> ip;
                if (hash_table.find(ip))
                    std::cout << "Value '" << ip << "' found." << std::endl;
                else
                    std::cout << "Value '" << ip << "' not found." << std::endl;
            } else if (command=="remove")
            {
                hash_table.remove();
            }
            else if (command=="set_value")
            {
                int v;
                input_file >> v;
                input_file.ignore(); //flush newline.
                hash_table.set_value(v);
            }
            else if (command=="show")
            {
                hash_table.goto_begin();
                std::cout << "Table: [";
                while(hash_table.is_valid())
                {
                    std::cout << hash_table.get_key() << ':' << hash_table.get_value() << ' ';
                    hash_table.goto_next();
                }
                std::cout << "]" << std::endl;
            }
            else if (command=="is_valid")
            {
                std::cout << "Is valid?: " << (hash_table.is_valid() ? "True" : "False") << std::endl;
            }
            else if (command=="get_key")
            {
                if (hash_table.is_valid())
                    std::cout << "Current key: '" << hash_table.get_key() << "'." << std::endl;
                else
                    std::cout << "Current key: not a valid position." << std::endl;
            }
            else if (command=="get_value")
            {
                if (hash_table.is_valid())
                    std::cout << "Current value: '" << hash_table.get_value() << "'." << std::endl;
                else
                    std::cout << "Current value: not a valid position." << std::endl;
            }
            else
            {
                std::cerr << "Error: unkown command '" << command << "'." << std::endl;
                return EXIT_FAILURE;
            }
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

