#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>
#include <valarray>

#include "city.hpp"
#include "graph.hpp"
#include "floyd_algorithm.hpp"

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
            return EXIT_FAILURE;
        }
        std::string command;
        input_file >> command;
        std::string type;
        input_file >> type;
        input_file.ignore();
        FMatrix D;
        IMatrix I;
        if (type == "INTEGER")
        {
            auto g = create_wgraph<int>(input_file);
            if (!g)
            {
                std::cerr << "Error: could not load a valid wgraph for cities." << std::endl;
                return EXIT_FAILURE;
            }
            if (command=="COMPUTE_WMATRIX")
            {
                compute_weight_matrix<int>(*g, D);
                std::cout << D << std::endl;
            }
            else
            {
                int u_name, v_name;
                input_file >> u_name >> v_name;
                auto u = g->find(u_name);
                if (! u)
                {
                    std::cerr << "Error: could find city named '"<< u->item() << "'." << std::endl;
                    return EXIT_FAILURE;
                }
                auto v = g->find(v_name);
                if (! v)
                {
                    std::cerr << "Error: could find city named '"<< v->item() << "'." << std::endl;
                    return EXIT_FAILURE;
                }
                floyd_algorithm(*g, D, I);
                if (command == "COMPUTE_FLOYD_MATRIXS")
                {
                    std::cout << "D Matrix:" << std::endl;
                    std::cout << D << std::endl;
                    std::cout << "I Matrix:" << std::endl;
                    std::cout << I << std::endl;
                }
                else
                {
                    if ( command != "COMPUTE_FLOYD_PATH")
                    {
                        std::cerr << "Error: unknown command '"<<
                                     command << "'," << std::endl;
                        return EXIT_FAILURE;
                    }

                    float distance = D[u->label()][v->label()];
                    std::cout << "Distance " << u->item() << " to "
                              << v->item() << " = " << distance << std::endl;
                    std::vector<size_t> path;
                    std::cout << "Path: [ ";
                    if (distance<std::numeric_limits<float>::infinity())
                    {
                        floyd_compute_path(u->label(), v->label(), I, path);
                        for (size_t i=0; i<path.size(); ++i)
                            std::cout << g->node(path[i])->item() << ' ';
                    }
                    std::cout << ']' << std::endl;
                    std::cout << std::endl;
                }
            }
        }
        else if (type == "STRING")
        {
            auto g = create_wgraph<std::string>(input_file);
            if (!g)
            {
                std::cerr << "Error: could not load a valid wgraph for cities." << std::endl;
                return EXIT_FAILURE;
            }
            if (command=="COMPUTE_WMATRIX")
            {
                compute_weight_matrix<std::string>(*g, D);
                std::cout << D << std::endl;
            }
            else
            {
                std::string u_name, v_name;
                input_file >> u_name >> v_name;
                auto u = g->find(u_name);
                if (! u)
                {
                    std::cerr << "Error: could find city named '"<< u->item() << "'." << std::endl;
                    return EXIT_FAILURE;
                }
                auto v = g->find(v_name);
                if (! v)
                {
                    std::cerr << "Error: could find city named '"<< v->item() << "'." << std::endl;
                    return EXIT_FAILURE;
                }
                floyd_algorithm(*g, D, I);
                if (command == "COMPUTE_FLOYD_MATRIXS")
                {
                    std::cout << "D Matrix:" << std::endl;
                    std::cout << D << std::endl;
                    std::cout << "I Matrix:" << std::endl;
                    std::cout << I << std::endl;
                }
                else
                {
                    if ( command != "COMPUTE_FLOYD_PATH")
                    {
                        std::cerr << "Error: unknown command '"<<
                                     command << "'," << std::endl;
                        return EXIT_FAILURE;
                    }

                    float distance = D[u->label()][v->label()];
                    std::cout << "Distance " << u->item() << " to "
                              << v->item() << " = " << distance << std::endl;
                    std::vector<size_t> path;
                    std::cout << "Path: [ ";
                    if (distance<std::numeric_limits<float>::infinity())
                    {
                        floyd_compute_path(u->label(), v->label(), I, path);
                        for (size_t i=0; i<path.size(); ++i)
                            std::cout << g->node(path[i])->item() << ' ';
                    }
                    std::cout << ']' << std::endl;
                    std::cout << std::endl;
                }
            }
        }
        else if(type == "CITY")
        {
            auto g = create_wgraph<City>(input_file);
            if (!g)
            {
                std::cerr << "Error: could not load a valid wgraph for cities." << std::endl;
                return EXIT_FAILURE;
            }
            if (command=="COMPUTE_WMATRIX")
            {
                compute_weight_matrix<City>(*g, D);
                std::cout << D << std::endl;
            }
            else
            {
                std::string u_name, v_name;
                input_file >> u_name >> v_name;
                auto u = g->find(City(u_name));
                if (! u)
                {
                    std::cerr << "Error: could find city named '"<< u->item() << "'." << std::endl;
                    return EXIT_FAILURE;
                }
                auto v = g->find(City(v_name));
                if (! v)
                {
                    std::cerr << "Error: could find city named '"<< v->item() << "'." << std::endl;
                    return EXIT_FAILURE;
                }
                floyd_algorithm(*g, D, I);
                if (command == "COMPUTE_FLOYD_MATRIXS")
                {
                    std::cout << "D Matrix:" << std::endl;
                    std::cout << D << std::endl;
                    std::cout << "I Matrix:" << std::endl;
                    std::cout << I << std::endl;
                }
                else
                {
                    if ( command != "COMPUTE_FLOYD_PATH")
                    {
                        std::cerr << "Error: unknown command '"<<
                                     command << "'," << std::endl;
                        return EXIT_FAILURE;
                    }
                    float distance = D[u->label()][v->label()];
                    std::cout << "Distance " << u->item().name << " to "
                              << v->item().name << " = " << distance << " km." << std::endl;
                    std::vector<size_t> path;
                    std::cout << "Path: [ ";
                    if (distance<std::numeric_limits<float>::infinity())
                    {
                        floyd_compute_path(u->label(), v->label(), I, path);
                        for (size_t i=0; i<path.size(); ++i)
                            std::cout << g->node(path[i])->item().name << ' ';
                    }
                    std::cout << ']' << std::endl;
                    std::cout << std::endl;
                }
            }
        }
        else
        {
            std::cerr << "Error: unknown graph type." << std::endl;
            return EXIT_FAILURE;
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

