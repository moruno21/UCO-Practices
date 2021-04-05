#ifndef __ED_BTree_Utils_HPP__
#define __ED_BTree_Utils_HPP__

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include "btree.hpp"

/**
 * @brief Compute the height of a tree.
 * The tree's height is the longitude of the longest branch connecting the root
 * node with a leaf node, or -1 if the tree was empty.
 *
 * @param t is the tree.
 * @return the tree's height or -1 if it is a empty tree.
 * @pre t!=nullptr
 */
template <class T>
int compute_height(typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    int ret_val = -1;

    //TODO
    if (t->is_empty())
        return ret_val;
    //Llamamos recursivamente a la función para que después entren en los ifs y vaya sumando
    int left_height = compute_height<T>(t->left());
    int right_height = compute_height<T>(t->right());

    if (right_height > left_height)
        ret_val = right_height + 1;
    else
        ret_val = left_height + 1;

    return ret_val;
}

/**
 * @brief Compute the number of nodes in the tree.
 *
 * @param t is the tree.
 * @return the number of nodes in the tree.
 * @pre t!=nullptr
 * @post t->is_empty() and ret_val==0
 * @post !t->is_empty() and ret_val>0
 */
template <class T>
size_t compute_size(typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    size_t ret_val = 0;

    //TODO
    if (!t->is_empty())
    {
        ret_val = compute_size<T>(t->right()) + compute_size<T>(t->left());
        ret_val++;
    }

    assert(!t->is_empty() || ret_val == 0);
    assert(t->is_empty() || ret_val > 0);
    return ret_val;
}

/**
 * @brief Prefix processing of a binary tree
 * The template class Processor must have an closure interface:
 *
 * bool Processor::operator()(T const& item).
 *
 * that makes something with item and returning true when the processing must
 * continue or false to stop it.
 *
 * A lambda expression can be used too.
 *
 * @return true if all nodes were processed.
 * @pre tree!=nullptr
 */
template <class T, typename Processor>
bool prefix_process(typename BTree<T>::Ref tree, Processor &p)
{
    assert(tree != nullptr);
    bool retVal = true;

    //TODO
    if (!tree->is_empty())
    {
        retVal = p(tree->item());
        retVal = retVal && prefix_process<T, Processor>(tree->left(), p);
        retVal = retVal && prefix_process<T, Processor>(tree->right(), p);
    }

    return retVal;
}

/**
 * @brief Infix processing of a binary tree.
 * The template class Processor must have an apply interface:
 *
 * bool Processor::operator()(T const& item).
 *
 * that makes something with item and returning true when the processing must
 * continue or false to stop it.
 *
 * A lambda expression can be used too.
 *
 * @return true if all nodes were processed.
 * @pre tree!=nullptr
 */
template <class T, class Processor>
bool infix_process(typename BTree<T>::Ref tree, Processor &p)
{
    assert(tree != nullptr);
    bool retVal = true;

    //TODO
    if (!tree->is_empty())
    {
        retVal = infix_process<T, Processor>(tree->left(), p);
        retVal = retVal && p(tree->item());
        retVal = retVal && infix_process<T, Processor>(tree->right(), p);
    }
    return retVal;
}

/**
 * @brief Postfix processing of a binary tree.
 * The template class Processor must have an apply interface:
 *
 * bool Processor::operator()(T const& item).
 *
 * that makes something with item and returning true when the processing must
 * continue or false to stop it.
 *
 * A lambda expression can be used too.
 *
 * @return true if all nodes were processed.
 * @pre tree!=nullptr
 */
template <class T, class Processor>
bool postfix_process(typename BTree<T>::Ref tree, Processor &p)
{
    assert(tree != nullptr);
    bool retVal = true;

    //TODO
    if (!tree->is_empty())
    {
        retVal = postfix_process<T, Processor>(tree->left(), p);
        retVal = retVal && postfix_process<T, Processor>(tree->right(), p);
        retVal = retVal && p(tree->item());
    }

    return retVal;
}

/**
 * @brief Bread-first processing of a btree.
 * The template class Processor must have an apply interface:
 *
 * bool Processor::operator()(T const& item).
 *
 * that makes something with item and returning true when the processing must
 * continue or false to stop it.
 *
 * A lambda expression can be used too.
 *
 * @return true if all nodes were processed.
 * @pre tree!=nullptr
 */
template <class T, class Processor>
bool breadth_first_process(typename BTree<T>::Ref tree, Processor &p)
{
    assert(tree != nullptr);
    bool ret_val = true;

    //TODO
    typename BTree<T>::Ref subtree;
    std::queue<typename BTree<T>::Ref> q;
    q.push(tree); //Encolamos el árbol antes de empezar

    while (!q.empty() && ret_val)
    {
        subtree = q.front();      //Igualamos al subtree al frente de la cola
        if (!subtree->is_empty()) //Mientras que el subtree no esté vacío, entramos en la condición
        {
            ret_val = p(subtree->item());
            q.push(subtree->left());  //Metemos el árbol izquierdo en la cola
            q.push(subtree->right()); //Metemos el árbol derecho en la cola
        }
        q.pop();
    }

    return ret_val;
}

/**
 * @brief Check is a binary tree is in order.
 * A binary tree is in order whether it is the empty tree or
 * when for each subtree, the root node is greater than all its proper left
 * descendants and less than all its proper right descendants.
 *
 * @param tree is the tree to be checked.
 * @return true if the input tree is in order.
 */
template <class T>
bool check_btree_in_order(typename BTree<T>::Ref const &tree)
{
    bool ret_val = true;

    //TODO

    if (!tree->is_empty())
    {
        if (!tree->left()->is_empty()) //Si está vacío, no hacec falta que entremos
        {
            auto maxValue = [=]() -> T { //Función lambda que calcula el valor máximo
                auto current = tree->left();
                while (!current->right()->is_empty())
                    current = current->right();
                return current->item();
            };
            if (maxValue() > tree->item()) //Comparamos con el valor máximo que hemos calculado. Si no se cumple, automáticamente el árbol no está ordenado
                ret_val = false;
        }

        if (!tree->right()->is_empty()) //Si está vacío, no hacec falta que entremos
        {
            auto minValue = [=]() -> T { //Función lambda que calcula el valor mínimo
                auto current = tree->right();
                while (!current->left()->is_empty())
                    current = current->left();
                return current->item();
            };
            if (minValue() < tree->item()) //Comparamos con el valor mínimo que hemos calculado. Si no se cumple, automáticamente el árbol no está ordenado
                ret_val = false;
        }

        if (!check_btree_in_order<T>(tree->left()) || !check_btree_in_order<T>(tree->right())) //Comprobamos que ninguno de los subárboles estén desordenados
            ret_val = false;
    }

    return ret_val;
}

/**
 * @brief Search a item into the tree.
 *
 * The input tree must be in order, a optimized search process can be used.
 *
 * @param tree is a in order binary tree.
 * @param v is the value to be found.
 * @pre check_btree_in_order(tree)
 * @return true if the value is in the tree.
 */
template <class T>
bool has_in_order(typename BTree<T>::Ref tree, T const &v)
{
    assert(check_btree_in_order<T>(tree));
    bool ret_val = false;

    //TODO
    if (!tree->is_empty()) //Si el árbol está vacío no entramos porque obviamente no habría nada que buscar
    {
        if (v < tree->item()) //Si el valor que buscamos es menor que el nodo raiz, buscamos por la rama izquierda ya que el árbol está ordenado
            ret_val = has_in_order<T>(tree->left(), v);
        else if (v > tree->item()) //Si el valor que buscamos es mayor que el nodo raiz, buscamos por la rama izquierda ya que el árbol está ordenado
            ret_val = has_in_order<T>(tree->right(), v);
        else //Si es igual, devolvemos true, ya que lo habremos encontrado
            ret_val = true;
    }
    return ret_val;
}

/**
 * @brief Insert in orde a value intro a binary tree.
 * @see check_btree_in_order to know what is mean this.
 * If the value is already in tree, nothing is inserted.
 *
 * @param tree is the tree where inserting.
 * @param v is the value to be inserted.
 *
 * @pre check_btree_in_order(tree)
 * @post has_in_order(tree, v)
 */
template <class T>
void insert_in_order(typename BTree<T>::Ref tree, T const &v)
{
    assert(check_btree_in_order<T>(tree));

    //TODO
    if (tree->is_empty()) //Si el árbol está vacío, creamos directamente el nodo raiz
        tree->create_root(v);

    else if (v < tree->item()) //Si el valor que queremos insertar es menor que el item del nodo raiz, vamos por la izquierda
    {
        if (tree->left()->is_empty())
            tree->set_left(BTree<T>::create(v));
        else
            insert_in_order<T>(tree->left(), v);
    }
    else if (v > tree->item()) //Si el valor que queremos insertar es mayor que el item del nodo raiz, vamos por la derecha
    {
        if (tree->right()->is_empty())
            tree->set_right(BTree<T>::create(v));
        else
            insert_in_order<T>(tree->right(), v);
    }

    assert(has_in_order<T>(tree, v));
}

#endif
