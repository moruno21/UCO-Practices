#ifndef __GRAPH_UTILS_HPP__
#define __GRAPH_UTILS_HPP__

#include <iostream>
#include <memory>
#include <string>
#include <valarray>

#include "graph.hpp"

/**
 * @brief A matrix of scalars.
 * The matrix is a valarray of valarray's of type T.
 */
template <class T>
class Matrix : public std::valarray<std::valarray<T>>
{
public:
    /**
     * @brief Create an empty Matrix.
     */
    Matrix()
    {
        assert(is_empty());
    }

    /**
     * @brief Create a matrix.
     * @param rows the number of rows.
     * @param cols the number of cols.
     * @param fill_v the value used to initialize the elements.
     * @pre rows==0 || cols>0
     */
    Matrix(size_t rows, size_t cols, const T fill_v = T(0))
    {
        assert(rows == 0 || cols > 0);
        resize_matrix(rows, cols, fill_v);
    }

    /**
     * @brief resize the matrix to a new size
     * @param rows the number of rows.
     * @param cols the number of columns.
     * @param fill_v the value used to initialize the elements.
     * @pre rows==0 || cols>0
     */
    void resize_matrix(size_t rows, size_t cols, const T fill_v = T(0))
    {
        assert(rows == 0 || cols > 0);
        this->resize(rows, std::valarray<T>(fill_v, cols));
    }

    /**
     * @brief Get the number of rows.
     * @return the number of rows.
     */
    size_t rows() const
    {
        return this->size();
    }

    /**
     * @brief Get the number of columns.
     * @return the number of columns.
     */
    size_t cols() const
    {
        return (is_empty() ? 0 : (*this)[0].size());
    }

    /**
     * @brief Is the matrix empty.
     * @return true if the matrix is empty.
     */
    bool is_empty() const
    {
        return rows() == 0;
    }
};

/**
 * @brief Output the matrix to output stream.
 * @param out the output stream.
 * @return the modified stream.
 */
template <class T>
std::ostream &operator<<(std::ostream &out, Matrix<T> const &m)
{
    if (!m.is_empty())
    {
        out << "[ ";
        for (size_t r = 0; r < m.rows(); ++r)
        {
            out << '[' << m[r][0];
            for (size_t c = 1; c < m.cols(); ++c)
                out << ',' << m[r][c];
            out << ']';
            if (r < (m.rows() - 1))
                out << ',' << std::endl;
        }
        out << " ]";
    }
    else
        out << "[]";
    return out;
}

/**
 * @brief A matrix of floats;
 */
typedef Matrix<float> FMatrix;

/**
 * @brief A matrix of integers;
 */
typedef Matrix<float> IMatrix;

/**
 * @brief Fold a weighted graph to an output stream.
 * Output format:
 * DIRECTED
 * <num. nodes>
 * <node item_0>
 * ...
 * <node item_N-1>
 * <num. edges>
 * <u_0> <v_0> <weight_0>
 * ...
 * <u_E-1> <v_E-1> <weight_E-1>
 */
template <class T>
bool fold_wgraph(std::ostream &out, WGraph<T> &g)
{
    out << "DIRECTED" << std::endl;
    out << g.size() << std::endl;
    for (size_t n = 0; n < g.size(); ++n)
        out << g.node(n)->item() << std::endl;
    std::vector<typename WGraph<T>::EdgeRef> edges;
    g.goto_first_node();
    while (g.has_current_node())
    {
        g.goto_first_edge();
        while (g.has_current_edge())
        {
            edges.push_back(g.current_edge());
            g.goto_next_edge();
        }
        g.goto_next_node();
    }
    out << edges.size() << std::endl;
    for (size_t e = 0; e < edges.size(); ++e)
        out << edges[e]->first()->label() << ' '
            << edges[e]->second()->label() << ' '
            << edges[e]->item() << std::endl;
    if (out)
        return true;
    else
        return false;
}

/**
 * @brief Create a Graph from txt representation.
 * If the graph is non directed, only one input u-v edge is needed but
 * it will be duplicated as u->v and v->u.
 *
 * Input Format:
 *
 * [DIRECTED|NON_DIRECTED]
 * <NUM-VERTICES>
 * <ITEM_1>
 * <ITEM_2>
 * ...
 * <ITEM_N>
 * <NUM-EDGES>
 * <ITEM_U> <ITEM_V> <WEIGTH>
 * ...
 *
 * @arg[in,out] in is the input stream.
 * @return a reference to the graph or nullptr if input error.
 * @warning std::runtime_error("Wrong graph") is throw if bad input format.
 */
template <class T>
std::shared_ptr<WGraph<T>> create_wgraph(std::istream &in) noexcept(false)
{
    assert(in);
    std::shared_ptr<WGraph<T>> graph; //The returned graph.
    bool is_directed = true;
    std::string type;
    in >> type;
    if (type != "DIRECTED")
        is_directed = false;

    size_t size;
    in >> size;
    if (!in)
        return nullptr;
    graph = std::make_shared<WGraph<T>>(size);

    //TODO: read the input file and build the graph.
    //Hint: Review how to add new nodes, edges to the graph.
    //Renember if the graph is non directed, each edge u--v generate two
    //directed edges u-->v and v-->u.
    //If the input format is wrong, the throw std::runtime_error("Wrong graph").

    size_t iterator = 0;    //Variable que usaremos para iterar
    while (iterator < size) //Iteramos hasta que alcancemos el tamaño
    {
        if (!in)
            std::runtime_error("Wrong graph"); //Si el formato es erróneo, salimos
        T new_value;
        in >> new_value;            //Volcamos in en el nuevo valor
        graph->add_node(new_value); //Insertamos el nuevo valor que hemos creado arriba
        iterator++;                 //Aumentamos la variable
    }

    size_t edges; //Numero de lados
    in >> edges;  //Volcamos el numero de lados de in a edges

    iterator = 0; //Ponemos el iterador a 0 para volver a iterar en el siguiente bucle
    while (iterator < edges)
    {
        T u, v;  //Creamos estos tres valores para volcar el contenido de in
        float w; //Creamos estos tres valores para volcar el contenido de in
        in >> u; //Volcamos in en u
        in >> v; //Volcamos in en v
        in >> w; //Volcamos in en w

        auto new_u = graph->find(u);
        auto new_v = graph->find(v);

        graph->set_weight(new_u, new_v, w); //Seteamos el peso

        if (!is_directed) //Si no es dirigido, repetimos el paso anterior
            graph->set_weight(graph->find(v), graph->find(u), w);

        iterator++; //Aumentamos la variable con la que iteramos
    }
    return graph;
}

#endif //__GRAPH_UTILS_HPP__
