#ifndef __FLOYD_ALGORITHM_HPP__
#define __FLOYD_ALGORITHM_HPP__

#include <stack>
#include <utility>
#include <valarray>

#include "graph.hpp"
#include "graph_utils.hpp"

/**
 * @brief Compute the weight matrix.
 * @arg[in] g is a weighted graph.
 * @arg[out] W is the Weight matrix.
 */
template <class T>
void compute_weight_matrix(WGraph<T> &g, FMatrix &W)
{
    W = FMatrix(g.size(), g.size(),
                std::numeric_limits<float>::infinity());

    //TODO: compute the WMatrix.
    //Hint: scan all the edges. Use the node.label() to index the matrix.
    //Hint: Assume the graph is directed.
    //Hint: Review how to move the cursors.

    g.goto_first_node(); //Vamos al comienzo
    while (g.has_current_node())
    {
        while (g.has_current_edge()) //Entramos mientras el nodo tenga lado
        {
            auto first = g.current_edge()->first();   //Guardamos el primero
            auto first_label = first->label();        //Valor que usaremos para la matriz de abajo
            auto second = g.current_edge()->second(); //Guardamos el segundo
            auto second_label = second->label();      //Valor que usaremos para la matriz de abajo

            W[first_label][second_label] = g.weight(first, second); //Lo igualamos al peso

            g.goto_next_edge(); //Cuando acabemos, pasamos al siguiente
        }
        g.goto_next_node(); //Cuando acabemos con un nodo, pasamos al siguiente
    }
}

/**
 * @brief Search for the minium path between vertices using the Floyd's algorithm.
 * @arg[in] g is a weighted graph.
 * @arg[out] D is the Distances matrix.
 * @arg[out] I is the Intermediate matrix.
 * @pre the weigths meet the triangular inequality: d(u,v) <= d(u,k) + d(k,v) for all u!=v!=k.
 * @post if none path between u,v exists then D[u][v]==inf and I[u][v]==-1
 * @post if an edge (u,v:w) exists then D[u][v]==w and I[u][v]==-1
 * @post if a path between u,v exits then D[u][v]<inf and D[u][v]==k, k is vertex in the minimum path linking u with v.
 */
template <class T>
void floyd_algorithm(WGraph<T> &g, FMatrix &D, IMatrix &I)
{
    compute_weight_matrix<T>(g, D);
    //Set self-distances to zero.
    for (size_t i = 0; i < g.size(); ++i)
        D[i][i] = 0.0;

    I = IMatrix(g.size(), g.size(), -1);

    //TODO: Codify the Floyd algorithm.
    //Para el algoritmo de Floyd tenemos que hacer 3 bucles anidados
    for (size_t a = 0; a < g.size(); a++) //Primer bucle
    {
        for (size_t b = 0; b < g.size(); b++) //Segundo bucle
        {
            for (size_t c = 0; c < g.size(); c++) //Tercer bucle
            {
                if (D[a][c] + D[b][a] < D[b][c]) //Si la suma no llega a valer lo mismo que D[b][c], entramos
                {
                    D[b][c] = D[a][c] + D[b][a]; //Seteamos el valor al valor de la suma
                    I[b][c] = a;                 //Cmabiamos el valor de I[b][c]
                }
            }
        }
    }
}

//Creamos esta funcion para que pueda funcionar floyd_compute_path (funcion de abajo)
void floyd_function_aux(size_t u, size_t v, IMatrix const &I, std::vector<size_t> &path)
{
    if (I[u][v] >= 0) //Solo entramos si el valor no es negativo
    {
        floyd_function_aux(u, I[u][v], I, path); //Llamamos recursivamente a la funcion
        auto new_value = I[u][v];                //Guardamos el valor correspondiente
        path.push_back(new_value);               //Hacemos push del valor creado arriba
        floyd_function_aux(I[u][v], v, I, path); //Llamamos recursivamente a la funcion
    }
}

/**
 * @brief Given the Floyd's Intermidiate matrix, compute the path.
 * @arg[in] u is the label of the start vertex.
 * @arg[in] v is the label of the end vertex.
 * @arg[in] I is the Floyd's Intermidiate matrix.
 * @arg[out] path is a vector with the sequence of vertex's labels for
 *           the minimum path linking u with v.
 * @pre Let D be the Floyd's D matrix corresponding with I, D[u][v]<inf.
 * @post u is the first item of path.
 * @post v is the last item of path.
 */
inline void
floyd_compute_path(size_t u, size_t v, IMatrix const &I,
                   std::vector<size_t> &path)
{
    //Prec: distance (u,v) < inf
    std::stack<std::pair<size_t, size_t>> s;
    path.resize(0);

    //TODO: Find the path.

    path.push_back(u);                 //Hacemos push del valor u
    floyd_function_aux(u, v, I, path); //Usamos la funcion auxiliar para que pueda funcionar esta funcion
    path.push_back(v);                 //Hacemos push del valor v
}

#endif //__FLOYD_ALGORITHM_HPP__
