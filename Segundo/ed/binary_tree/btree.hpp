#ifndef __ED_BTree_HPP__
#define __ED_BTree_HPP__

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <sstream>

/** @brief a BTree's Node.*/
template <class T>
class BTNode
{
public:
    /** @brief Define a shared reference to a BTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr<BTNode<T>> Ref;

    /** @name Life cicle.*/
    /** @{*/

    /** @brief Create a BTNode.
     * @post n_children() == 0
     */
    BTNode(T const &it = T(), BTNode<T>::Ref left = nullptr, BTNode<T>::Ref right = nullptr)
    {
        //TODO
        this->item_ = it;
        this->left_ = left;
        this->right_ = right;
    }

    /**
     * @brief Create a BTNode using dynamic memory.
     * @param it the value save in the node.
     * @param left links to the left child.
     * @param right links to the right child.
     * @return a shared referente to the new node.
     */
    static typename BTNode<T>::Ref create(T const &it, BTNode<T>::Ref left = nullptr, BTNode<T>::Ref right = nullptr)
    {
        return std::make_shared<BTNode<T>>(it, left, right);
    }

    /** @brief Destroy a BTNode. **/
    ~BTNode()
    {
    }

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /** @brief Get the data item.*/
    const T &item() const
    {
        //TODO
        return this->item_;
    }

    /** @brief Has it a left child?*/
    bool has_left() const
    {
        //TODO
        return this->left_ != nullptr;
    }

    /** @brief get the left child.*/
    BTNode<T>::Ref left() const
    {
        //TODO
        return this->left_;
    }

    /** @brief Has it a right child? */
    bool has_right() const
    {
        //TODO
        return this->right_ != nullptr;
    }

    /** @brief get the right child.*/
    BTNode<T>::Ref right() const
    {
        //TODO
        return this->right_;
    }
    /** @}*/

    /** @name Modifiers.*/
    /** @{*/

    /** @brief Set the data item.*/
    void set_item(const T &new_it)
    {
        //TODO
        this->item_ = new_it;
    }

    /** @brief Set the left child.*/
    void set_left(BTNode<T>::Ref new_child)
    {
        //TODO
        this->left_ = new_child;
    }

    /** @brief Remove link to the left child. */
    void remove_left()
    {
        //TODO: hint see std::share_ptr doc.
        this->left_ = nullptr;
    }

    /** @brief Set the right child.*/
    void set_right(BTNode<T>::Ref new_child)
    {
        //TODO
        this->right_ = new_child;
    }

    /** @brief Remove linkt to the right child. */
    void remove_right()
    {
        //TODO: hint see std::share_ptr doc.
        this->right_ = nullptr;
    }

protected:
    //TODO
    T item_;
    BTNode<T>::Ref right_;
    BTNode<T>::Ref left_;
};

/**
 * @brief ADT BTree.
 * Models a BTree of T.
 */
template <class T>
class BTree
{
public:
    /** @brief Define a shared reference to a BTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr<BTree<T>> Ref;

    /** @name Life cicle.*/
    /** @{*/

    /** @brief Create an empty BTree.
     * @post is_empty()
     */
    BTree()
    {
        //TODO
        this->root_ = nullptr;
    }

    /** @brief Create Leaf BTree.
   * @post not is_empty()
   */
    BTree(const T &item)
    {
        //TODO
        this->root_ = typename BTNode<T>::Ref(new BTNode<T>(item, nullptr, nullptr)); //Realmente nullptr se pasa por defecto
    }

    /**
   * @brief Create an empty BTree.
   * @return a shared referente to the new tree.
   */
    static typename BTree<T>::Ref create()
    {
        return std::make_shared<BTree<T>>();
    }

    /**
   * @brief Create a leaf BTree.
   * @param item is the root's item.
   * @return a shared referente to the new tree.
   */
    static typename BTree<T>::Ref create(T const &item)
    {
        return std::make_shared<BTree<T>>(item);
    }

    /**
   * @brief Load a tree from a input stream.
   *
   * The input format will be:
   * '[]' for the empty tree.
   * '[ <item> <left-subtree> <right-subtree> ']'
   *
   * For example a tree with three nodes:
   * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
   *
   * @return a reference to the tree created.
   * @warning runtime_error will throw if worng input format was found.
   */
    static typename BTree<T>::Ref create(std::istream &in) noexcept(false)
    {
        auto tree = BTree<T>::create();
        std::string token;
        in >> token;
        if (!in)
            throw std::runtime_error("Wrong input format.");

        //TODO
        if (token == "[") //En el caso en el que el stream no empiece por [, la única opción es que comience por []
        {
            T new_item; //En este item almacenamos el item que leamos del stream y que meteremos en el árbol
            in >> token;
            std::istringstream aux(token); //Hay que hacerlo igual que en la práctica 1, ya que no podemos cargar el valor de token directamente en el new_item
            aux >> new_item;
            tree->create_root(new_item);
            tree->set_left(create(in));
            tree->set_right(create(in));
            in >> token;      //Si no añado esta línea, los tests fallan, no acabo de entender el por qué
            if (token != "]") //Si el stream no acaba en ], nos da error de formato
                throw std::runtime_error("Wrong input format.");
        }
        else if (token != "[]") //Sí el stream representa un árbol vacío y el formato no es [], nos da error de formato
            throw std::runtime_error("Wrong input format.");
        return tree;
    }

    /** @brief Destroy a BTree.**/
    ~BTree()
    {
    }
    /** @}*/

    /** @name Observers*/

    /** @{*/

    /** @brief is the list empty?.*/
    bool is_empty() const
    {
        //TODO
        return this->root_ == nullptr;
    }

    /** @brief Get the root item.
   * @pre not is_empty();
   */
    T const &item() const
    {
        assert(!is_empty());
        //TODO
        return this->root_->item();
    }

    /**
   * @brief Get the left subtree.
   * @return a reference to the left subtree.
   * @pre !is_empty()
   */
    typename BTree<T>::Ref left() const
    {
        assert(!is_empty());
        BTree<T>::Ref l_subtree;

        //TODO
        l_subtree = BTree<T>::create(); //Hay que crearlo, ya que arriba solamente se declara
        l_subtree->root_ = this->root_->left();

        return l_subtree;
    }

    /**
   * @brief Get the right subtree.
   * @return a reference to the right subtree.
   * @pre !is_empty()   
   */
    typename BTree<T>::Ref right() const
    {
        assert(!is_empty());
        BTree<T>::Ref r_subtree;

        //TODO
        r_subtree = BTree<T>::create(); //Hay que crearlo, ya que arriba solamente se declara
        r_subtree->root_ = this->root_->right();

        return r_subtree;
    }

    /**
   * @brief Fold a binary tree.
   *
   * The output format will be:
   * '[]' for the empty tree.
   * '[ <item> <left-subtree> <right-subtree> ']'
   *
   * For example a tree with three nodes:
   * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
   *
   * @param out is the output stream.
   * @param tree is the tree.
   * @return the output stream.
   * @pre tree!=nullptr
   */
    std::ostream &fold(std::ostream &out) const
    {
        //TODO

        if (this->root_ == nullptr) //Caso en el que el árbol está vacío. El output será []
        {
            out << "[]";
        }
        else //Caso en el que el árbol no está vacío
        {
            out << "[ ";
            out << this->root_->item();
            out << " ";
            this->left()->fold(out);
            out << " ";
            this->right()->fold(out);
            out << " ]";
        }
        return out;
    }

    /** @}*/

    /** @name Modifiers*/

    /** @{*/

    /**
   * @brief set the roor's item.
   * @pre not is_empty()
   */
    void set_item(const T &new_it)
    {
        assert(!is_empty());
        //TODO
        this->root_->set_item(new_it);
    }

    /**
   * @brief Create the root node.
   * item is the new root item.
   * @post !is_empty()
   */
    void create_root(T const &item)
    {
        //TODO
        this->root_ = typename BTNode<T>::Ref(new BTNode<T>(item, nullptr, nullptr)); //Creamos un puntero a nodo con item = item
        assert(!is_empty());
    }

    /**
   * @brief Remove the link to the root node.
   * @post is_empty()
   */
    void remove_root()
    {
        //TODO
        assert(is_empty());
        this->root_ = nullptr;
    }

    /**
   * @brief Attach a new subtree as left child of root.
   * @param new_left is the new left subtree.
   * @pre !is_empty()
   */
    void set_left(typename BTree<T>::Ref new_left)
    {
        assert(!is_empty());
        //TODO
        this->root_->set_left(new_left->root_);
    }

    /**
   * @brief Detach the left child of root.
   * @pre !is_empty()
   */
    void remove_left()
    {
        assert(!is_empty());
        //TODO
        this->root_->remove_left();
    }

    /**
   * @brief Attach a new subtree as right child of root.
   * @param t is the new right subtree.
   */
    void set_right(typename BTree<T>::Ref t)
    {
        assert(!is_empty());
        //TODO
        this->root_->set_right(t->root_);
    }

    /**
   * @brief Detach the right child of root.
   * @pre !is_empty()
   */
    void remove_right()
    {
        assert(!is_empty());
        //TODO
        this->root_->remove_right();
    }

    /** @}*/

protected:
    //TODO
    typename BTNode<T>::Ref root_;
};
#endif
