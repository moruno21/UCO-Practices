#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

#include "slist.hpp"

int
main(int argc, const char* argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: test_stack test_case" << std::endl;
            return EXIT_FAILURE;
        }
        std::string filename = argv[1];

        std::ifstream input (argv[1]);
        if (!input)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }

        auto l = SList<int>::create();

        while(input)
        {
            std::string operation;
            input >> operation;
            if (input)
            {
                if (operation=="IS_EMPTY")
                {
                  std::cout <<"Is it empty? " <<  (l->is_empty()? "Y": "N") << std::endl;
                }
                else if (operation == "FRONT")
                {
                    std::cout << "Head item: " << l->front() << std::endl;
                }
                else if (operation == "CURRENT")
                {
                    std::cout << "Current item: " << l->current() << std::endl;
                }
                else if (operation == "PUSH_FRONT")
                {
                    int v;
                    input >> v;
                    std::cout << "Inserting front " << v << std::endl;
                    l->push_front(v);
                }
                else if (operation == "POP_FRONT")
                {
                    std::cout << "Removing front " << l->current() << std::endl;
                    l->pop_front();
                }
                else if (operation == "INSERT")
                {
                    int v;
                    input >> v;
                    std::cout << "Inserting " << v << std::endl;
                    l->insert(v);
                }
                else if (operation == "REMOVE")
                {
                    std::cout << "Removing " << l->current() << std::endl;
                    l->remove();
                }
                else if (operation == "UNFOLD")
                {                    
                    try
                    {
                        l = SList<int>::create(input);
                    }
                    catch (std::runtime_error const& e)
                    {
                        std::cout << "Wrong input format." << std::endl;
                        return EXIT_FAILURE;
                    }
                }
                else if (operation == "FOLD")
                {
                    std::cout << "Folding: ";
                    l->fold(std::cout);
                    std::cout << std::endl;
                }
                else if (operation == "HAS")
                {
                    int v;
                    input >> v;
                    std::cout << "Has it " << v << "?: "
                              << (l->has(v) ? "Y" : "N") << std::endl;
                }
                else if (operation == "HAS_NEXT")
                {
                    std::cout << "Has next? : "
                              << (l->has_next() ? "Y" : "N") << std::endl;
                }
                else if (operation == "NEXT")
                {
                    std::cout << "Next item: " << l->next() << std::endl;
                }
                else if (operation == "GOTO_FIRST")
                {
                    std::cout << "Going to head." << std::endl;
                    l->goto_first();
                }
                else if (operation == "GOTO_NEXT")
                {
                    std::cout << "Going to next." << std::endl;
                    l->goto_next();
                }
                else if (operation == "FIND")
                {
                    int v;
                    input >> v;
                    std::cout << "Finding value " << v << "?: "
                              << (l->find(v) ? "Y" : "N") << std::endl;
                }
                else if (operation == "FIND_NEXT")
                {
                    int v;
                    input >> v;
                    std::cout << "Finding next for value " << v << "?: "
                              << (l->find_next(v) ? "Y" : "N") << std::endl;
                }
                else
                {
                    std::cerr << "Error: operation not found? '"
                              << operation << "'." << std::endl;
                    return EXIT_FAILURE;
                }
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

