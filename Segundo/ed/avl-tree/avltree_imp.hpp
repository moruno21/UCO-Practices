#pragma once

#include "avltree.hpp"

#ifdef assert
//We undefined this macro to not shadow our implementation of assert.
#undef assert
#endif

/**
 * @brief Check an assertion.
 * In Debug mode, if the assertion is not met, a segfault is generated.
 * @param assertion
 */
inline void assert(bool assertion)
{
#ifndef NDEBUG
    (void)((assertion) || (__assert("Assert violation!", __FILE__, __LINE__), 0));
#endif
}

/****
 * AVLTNode class implementation.
****/

template <class T>
AVLTNode<T>::AVLTNode(T const &it, AVLTNode<T>::Ref parent,
                      AVLTNode<T>::Ref left, AVLTNode<T>::Ref right) : item_(it), parent_(parent), left_(left), right_(right), height_(0)
{
    //TODO
    this->compute_height(); //Cuando creamos un nodo tenemos que computar su altura
    assert(check_height_invariant());
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::create(T const &it,
                                              AVLTNode<T>::Ref parent,
                                              AVLTNode<T>::Ref left,
                                              AVLTNode<T>::Ref right)
{
    return std::make_shared<AVLTNode<T>>(it, parent, left, right);
}

template <class T>
const T &AVLTNode<T>::item() const
{
    //TODO
    //Devolvemos el item del nodo
    return this->item_;
}

template <class T>
int AVLTNode<T>::height() const
{
    //TODO
    //Devolvemos la altura del nodo
    return this->height_;
}

template <class T>
int AVLTNode<T>::balance_factor() const
{
    int bf = 0;
    //TODO
    int lfth = 0;
    int rgth = 0;
    if (has_left() == true)
    {
        left_->compute_height();
        lfth = left_->height() + 1;
    }
    if (has_right() == true)
    {
        right_->compute_height();
        rgth = right_->height() + 1;
    }

    bf = rgth - lfth;
    return bf;
}

template <class T>
bool AVLTNode<T>::has_parent() const
{
    //TODO
    //Devolvemos true siempre que el parent no sea nullptr

    return this->parent_ != nullptr;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::parent() const
{
    //TODO
    //Devolvemos el padre
    return this->parent_;
}

template <class T>
bool AVLTNode<T>::has_left() const
{
    //TODO
    //Devolvemos true siempre que el left no sea nullptr

    return this->left_ != nullptr;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::left() const
{
    //TODO
    //Devolvemos el nodo left
    return this->left_;
}

template <class T>
bool AVLTNode<T>::has_right() const
{
    //TODO
    //Devolvemos true siempre que el right no sea nullptr

    return this->right_ != nullptr;
    ;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::right() const
{
    //TODO
    //Devolvemos el nodo left
    return this->right_;
}

template <class T>
bool AVLTNode<T>::check_height_invariant() const
{
    bool ret_val = false;
    //TODO
    int left_height = -1, right_height = -1; //Al comienzo las alturas son -1 porque un nodo que no existe no tiene altura, y cuando se cree tendrá 0 = -1 + 1

    if (this->has_left()) //Si tiene izquierdo, asignamos la altura de este a la altura izquierda
        left_height = this->left_->height();

    if (this->has_right()) //Si tiene derecho, asignamos la altura de este a la altura derecho
        right_height = this->right_->height();

    if (this->height() == 1 + std::max(left_height, right_height))
        ret_val = true;

    return ret_val;
}

template <class T>
void AVLTNode<T>::set_item(const T &new_it)
{
    //TODO
    //Asignamos el nuevo item al item
    this->item_ = new_it;
    assert(item() == new_it);
}

template <class T>
void AVLTNode<T>::set_parent(AVLTNode<T>::Ref const &new_parent)
{
    //TODO
    //Asignamos el nuevo padre a padre_
    //Cada vez que modifiquemos el padre, la altura puede cambiar por lo que hay que recalcular la altura
    this->parent_ = new_parent;
    this->compute_height();
    //
    assert(parent() == new_parent);
}

template <class T>
void AVLTNode<T>::remove_parent()
{
    //TODO
    //Borramos el padre
    //Cada vez que modifiquemos el padre, la altura puede cambiar por lo que hay que recalcular la altura
    this->parent_ = nullptr;
    this->compute_height();
    assert(!has_parent());
}

template <class T>
void AVLTNode<T>::set_left(AVLTNode<T>::Ref const &new_child)
{
    //TODO
    //Asignamos el nuevo left a left
    //Cada vez que modifiquemos el izquiedo, la altura puede cambiar por lo que hay que recalcular la altura
    this->left_ = new_child;
    this->compute_height();

    assert(check_height_invariant());
    assert(left() == new_child);
}

template <class T>
void AVLTNode<T>::remove_left()
{
    //TODO
    //Borramos el nodo left_
    //Cada vez que modifiquemos el izquiedo, la altura puede cambiar por lo que hay que recalcular la altura
    this->left_ = nullptr;
    this->compute_height();

    //
    assert(check_height_invariant());
    assert(!has_left());
}

template <class T>
void AVLTNode<T>::set_right(AVLTNode<T>::Ref const &new_child)
{
    //TODO
    //Asignamos el nuevo right a right_
    //Cada vez que modifiquemos el derecho, la altura puede cambiar por lo que hay que recalcular la altura

    this->right_ = new_child;
    this->compute_height();
    assert(check_height_invariant());
    assert(right() == new_child);
}

template <class T>
void AVLTNode<T>::remove_right()
{
    //TODO

    //Borramos el nodo right_
    //Cada vez que modifiquemos el derecho, la altura puede cambiar por lo que hay que recalcular la altura

    this->right_ = nullptr;
    this->compute_height();

    assert(check_height_invariant());
    assert(!has_right());
}

template <class T>
void AVLTNode<T>::compute_height()
{
    //TODO
    if (!this->has_right() && !this->has_left()) //Si no tiene ningun hijo, tiene altura 0
    {
        this->height_ = 0;
        if (this->has_parent()) //Si tiene padre, calculamos la altura de dicho padre
            this->parent_->compute_height();
    }

    else
    {
        int left_height = 0, right_height = 0;

        if (this->has_left()) //Entramos si tiene izquiedo
            left_height = this->left_->height() + 1;

        if (this->has_right()) //Entramos si tiene derecho
            right_height = this->right_->height() + 1;

        if (this->has_parent()) //Lo que hacemos aqui es comprobar si tiene padre, para computar su altura recursivamente
            this->parent_->compute_height();

        //En estas condiciones guardamos en this->height la altura más grande de las 2

        if (left_height > right_height)
            this->height_ = left_height;

        else
            this->height_ = right_height;
    }
    assert(check_height_invariant());
}

/***
 * AVLTree class implementation.
 ***/

template <class T>
AVLTree<T>::AVLTree()
{
    //TODO
    this->root_ = nullptr;
    this->parent_ = nullptr;
    this->current_ = nullptr;

    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
}

template <class T>
AVLTree<T>::AVLTree(T const &item)
{
    //TODO
    this->root_ = typename AVLTNode<T>::Ref(new AVLTNode<T>(item, nullptr, nullptr, nullptr));

    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create()
{
    return std::make_shared<AVLTree<T>>();
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create(T const &item)
{
    return std::make_shared<AVLTree<T>>(item);
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create(std::istream &in) noexcept(false)
{
    auto tree = AVLTree<T>::create();
    std::string token;
    in >> token;
    if (!in)
        throw std::runtime_error("Wrong input format");

    //TODO
    if (token == "[") //En el caso en el que el stream no empiece por [, la única opción es que comience por []
    {
        T data; //En este item almacenamos el item que leamos del stream y que meteremos en el árbol
        in >> data;
        tree = AVLTree<T>::create(data);

        auto l_subtree = AVLTree<T>::create(in);
        auto r_subtree = AVLTree<T>::create(in);
        tree->set_left(l_subtree);
        tree->set_right(r_subtree);

        in >> token;
    }
    else if (token != "[]") //Sí el stream representa un árbol vacío y el formato no es [], nos da error de formato
        throw std::runtime_error("Wrong input format");

    if (!tree->is_a_binary_search_tree())
        throw std::runtime_error("It is not a binary search tree");
    if (!tree->is_a_balanced_tree())
        throw std::runtime_error("It is not an avl bstree");

    return tree;
}

#ifdef __ONLY_BSTREE__
/**
 * @brief Create a BSTree by inserting the median of an ordered sequence.
 * @param data is an ordered sequence of keys.
 * @param begin,
 * @param end specify a [begin, end) indexing interval of data to use.
 * @pre data values are in order.
 * @pre 0 <= begin <= end <=data.size()
 */
template <class T>
void create_inserting_median(std::vector<T> const &data,
                             size_t begin,
                             size_t end,
                             typename AVLTree<T>::Ref &tree)
{
    assert(begin <= end);
    assert(end <= data.size());

    //TODO
    //Hint: use a recursive design by inserting the median of input
    // (begin, end] interval
    //and recursively, apply to each sub-interval [begin, median),
    //[median+1, end).
    if ((end - begin) >= 1) //Entramos siempre que la resta mayor o igual a 1
    {
        tree->insert(data[begin + ((end - begin) / 2)]);
        //Llamamos recursivamente a la funcion
        create_inserting_median(data, begin, begin + ((end - begin) / 2), tree);
        //Llamamos recursivamente a la funcion
        create_inserting_median(data, (begin + ((end - begin) / 2)) + 1, end, tree);
    }
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create(std::vector<T> &data)
{
    assert(data.size() > 0);
    auto tree = AVLTree<T>::create();
    std::sort(data.begin(), data.end());
    create_inserting_median(data, 0, data.size(), tree);
    return tree;
}
#endif //#ifdef __ONLY_BSTREE__

template <class T>
bool AVLTree<T>::is_empty() const
{
    //TODO
    return this->root_ == nullptr;
}

template <class T>
T const &AVLTree<T>::item() const
{
    return this->root_->item();
}

template <class T>
std::ostream &AVLTree<T>::fold(std::ostream &out) const
{
    //TODO
    if (this->root_ == nullptr) //Caso en el que el árbol está vacío. El output será []
        out << "[]";

    else //Caso en el que el árbol no está vacío
    {
        out << "[ ";
        out << this->item();
        out << " ";
        this->left()->fold(out);
        out << " ";
        this->right()->fold(out);
        out << " ]";
    }
    //
    return out;
}

template <class T>
bool AVLTree<T>::current_exists() const
{
    //TODO
    auto node_aux = this->root_; //Creamos un nodo que utilizaremos de ayuda

    for (int i = 0; i == i; i++) //Bucle infinito
    {
        if (this->current_ == nullptr) //Si current es nullptr pues no existe
            return false;

        //Vamos por la derecha
        if (node_aux->item() < this->current_->item())
        {
            if (node_aux->has_right())
                node_aux = node_aux->right();
            else
                return false;
        }

        //Vamos por la izquierda
        else if (node_aux->item() > this->current_->item())
        {
            if (node_aux->has_left())
                node_aux = node_aux->left();
            else
                return false;
        }
        else
            return true;
    }
}

template <class T>
T const &AVLTree<T>::current() const
{
    assert(current_exists());
    //TODO
    return this->current_->item(); //Devolvemos el item de current
}

template <class T>
int AVLTree<T>::current_level() const
{
    assert(current_exists());
    int level = 0;
    //TODO
    auto node_aux = this->root_; //Creamos un nodo que tendra el valor de root_ y nos servira de ayuda
    while (this->current_ != node_aux)
    {
        if (node_aux->item() > this->current_->item()) //Entramos si el item del nodo es mayor que el item de current
            node_aux = node_aux->left();

        else if (this->current_->item() > node_aux->item()) //Entramos si el item del nodo es menor que el item de current
            node_aux = node_aux->right();

        level++;
    }
    return level;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::left() const
{
    assert(!is_empty());
    //TODO
    //Declaramos el subarbol y lo creamos
    AVLTree<T>::Ref subleft = AVLTree<T>::create();

    if (this->root_->has_left())
    {
        subleft->create_root(root_->left()->item());
        subleft->root_->set_parent(nullptr);
        subleft->root_->set_left(root_->left()->left());
        subleft->root_->set_right(root_->left()->right());
    }

    return subleft;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::right() const
{
    assert(!is_empty());
    //TODO
    //Declaramos el subarbol y lo creamos
    AVLTree<T>::Ref subright = AVLTree<T>::create();

    if (this->root_->has_right())
    {
        subright->create_root(root_->right()->item());
        subright->root_->set_parent(nullptr);
        subright->root_->set_left(root_->right()->left());
        subright->root_->set_right(root_->right()->right());
    }

    return subright;
}

template <class T>
int AVLTree<T>::size() const
{
    int s = 0;
    //TODO
    //Llamamos recursivamente a la funcion hasta que encontremos arboles vacios
    if (!this->is_empty())
        s = right()->size() + left()->size() + 1;

    return s;
}

template <class T>
int AVLTree<T>::height() const
{
    int h = -1;
    //TODO
    //La altura del arbol será la altura del nodo raiz
    if (!this->is_empty())
        h = this->root_->height();
    return h;
}

template <class T>
int AVLTree<T>::balance_factor() const
{
#ifdef __ONLY_BSTREE__
    return 0;
#else
    int bf = 0;
    //TODO
    //Simplemente basta con calcular el balance_factor de la raiz
    if (!is_empty())
        bf = this->root_->balance_factor();
    return bf;
#endif
}

template <class T>
bool AVLTree<T>::has(const T &k) const
{
#ifndef NDEBUG
    bool old_current_exists = current_exists();
    T old_current;
    if (old_current_exists)
        old_current = current();
#endif
    bool found = true;

    //TODO
    auto node_aux = this->root_;

    for (int i = 0; i == i; i++) //Bucle infinito utilizamos los break para salir de el en caso de que hayamos terminado
    {
        if (node_aux->item() > k) //k esta por la izquierda
        {
            if (node_aux->has_left()) //SI el nodo tiene izquierdo entramos
                node_aux = node_aux->left();
            else
            {
                found = false;
                break;
            }
        }
        else if (node_aux->item() < k) //k esta por la derecha
        {
            if (node_aux->has_right()) //Si el nodo tiene derecho entramos
                node_aux = node_aux->right();
            else
            {
                found = false;
                break;
            }
        }
        else
            break;
    }
    //
#ifndef NDEBUG
    assert(!old_current_exists || old_current == current());
#endif
    return found;
}

template <class T>
bool AVLTree<T>::is_a_binary_search_tree() const
{
    bool is_bst = true;
    //TODO
    if (!this->is_empty())
    {
        if (this->root_->has_left()) //Entramos si tiene izquierdo
        {
            if (!(item() > left()->item()))
                is_bst = false;
        }

        if (this->root_->has_right())                      //Entramos si tiene derecho
            is_bst = is_bst && (item() < right()->item()); //Aqui tenemos que empezar a comparar con el valor anterior que tiene is_bst

        //Aqui tambien tenemos que comparar el valor anterior de is_bst
        //No sera un bst si alguno de sus subarboles no lo es
        is_bst = is_bst && this->right()->is_a_binary_search_tree() && this->left()->is_a_binary_search_tree();
    }
    return is_bst;
}

template <class T>
bool AVLTree<T>::is_a_balanced_tree() const
{
#ifdef __ONLY_BSTREE__
    return true;
#else
    bool is_balanced = true;
    //TODO
    if (this->root_ != nullptr)
    {
        int balance_factor = std::abs(this->root_->balance_factor()); //Calculamos el balance factor en valor absoluto
        //Si no se cumple alguna de las condiciones del if, entonces el arbol no esta balanceado
        if (balance_factor > 1 || !this->right()->is_a_balanced_tree() || !this->left()->is_a_balanced_tree())
            is_balanced = false;
    }
    return is_balanced;
#endif
}

template <class T>
void AVLTree<T>::create_root(T const &item)
{
    assert(is_empty());
    //TODO
    //Creamos la raiz del arbol poniendole el item que recibimos de la funcion
    this->root_ = AVLTNode<T>::create(item, nullptr, nullptr, nullptr);

    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(this->item() == item);
}

template <class T>
bool AVLTree<T>::search(T const &k)
{
    bool found = false;
    //TODO
    this->parent_ = nullptr;
    this->current_ = this->root_;
    while (this->current_ != nullptr) //Mientras current no sea nulo y no encontremos el valor entramos en el bucle
    {
        if (this->current_->item() == k) //Entramos en el bucle si encontramos el nodo
        {
            found = true;
            break;
        } //Si lo encontramos saldremos del bucle al acabar
        else
        {
            this->parent_ = this->current_; //EL padre sera nuestro actual current, ya que current pasara a ser o su hijo izq o dcho
            if (this->current_->item() < k) //Si el tenemos es menor que el que buscamos, tenemos que ir a la derecha
                this->current_ = this->current_->right();
            else //Si el que tenemos es mayor que el que buscamos, tenemos que ir a la izquierda
                this->current_ = this->current_->left();
        }
    }
    assert(!found || current() == k);
    assert(found || !current_exists());
    return found;
}

template <class T>
void AVLTree<T>::insert(T const &k)
{
    if (!search(k))
    {
        //TODO
        if (this->is_empty()) //Si no hay ruta, entramos
        {
            this->current_ = AVLTNode<T>::create(k, nullptr, nullptr, nullptr); //Creamos un nodo current que tendra de item k
            this->root_ = this->current_;                                       //Asignamos current a la raiz
        }
        else
        {
            this->current_ = AVLTNode<T>::create(k, this->parent_, nullptr, nullptr); //Creamos el nodo que tendra de item k tambien le asignamos el padre
            if (this->parent_->item() < k)
                this->parent_->set_right(this->current_);
            else
                this->parent_->set_left(this->current_);
        }
#ifdef __ONLY_BSTREE__
        assert(is_a_binary_search_tree());
#else
        assert(is_a_binary_search_tree());
        make_balanced();
        assert(is_a_balanced_tree());
#endif
    }

    //check postconditions.
    assert(current_exists());
    assert(current() == k);
}

template <class T>
void AVLTree<T>::remove()
{
    //check preconditions.
    assert(current_exists());

    bool replace_with_subtree = true;
    typename AVLTNode<T>::Ref subtree;

    //TODO
    // Check which of cases 0,1,2,3 we have.

    if (!this->current_->has_right() && !this->current_->has_left()) //Si no tenemos ni izq ni dcho, entramos
        subtree = nullptr;

    else if (!this->current_->has_left()) //Entramos si no tiene izq
        subtree = this->current_->right();

    else if (!this->current_->has_right()) //Entramos si no tiene dcho
        subtree = this->current_->left();

    else //Entramos si tenemos izquierdo y derecho
        replace_with_subtree = false;

    if (replace_with_subtree)
    {
        //TODO
        //Manage cases 0,1,2
        if (this->parent_ == nullptr) //Entramos si el padre es nulo
            this->root_ = subtree;

        else if (this->current_ == this->parent_->left()) //Entramos si el actual es igual al izq del padre
            this->parent_->set_left(subtree);

        else if (this->current_ == this->parent_->right()) //Entramos si el actual es igual al dcho del padre
            this->parent_->set_right(subtree);

        this->current_ = nullptr;

#ifdef _ONLY_BSTREE_
        assert(is_a_binary_search_tree());
        assert(!current_exists());
#else
        assert(is_a_binary_search_tree());
        make_balanced();
        assert(is_a_balanced_tree());
        assert(!current_exists());
#endif
    }
    else
    {
        //TODO
        //Manage case 3.
        auto x = this->current_;
        find_inorder_sucessor();
        x->set_item(this->current_->item());
        remove();
    }
}

template <class T>
AVLTree<T>::AVLTree(typename AVLTNode<T>::Ref root_node)
{
    //TODO
    //Asignamos el nuevo nodo a la raiz
    this->root_ = root_node;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create(typename AVLTNode<T>::Ref root)
{
    AVLTree<T>::Ref ret_v(new AVLTree<T>(root));
    return ret_v;
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTree<T>::root() const
{
    //TODO
    //Devuelves la raiz
    return this->root_;
}

template <class T>
void AVLTree<T>::set_left(typename AVLTree<T>::Ref &subtree)
{
    assert(!is_empty());
    //TODO
    if (subtree->is_empty()) //Si le pasamos un arbol vacio, seteamos nullptr
        this->root_->set_left(nullptr);

    else
        this->root_->set_left(AVLTNode<T>::create(subtree->root_->item(), this->root_, subtree->root_->left(), subtree->root_->right()));

    assert(subtree->is_empty() || left()->item() == subtree->item());
    assert(!subtree->is_empty() || left()->is_empty());
}

template <class T>
void AVLTree<T>::set_right(typename AVLTree<T>::Ref &subtree)
{
    assert(!is_empty());
    //TODO

    if (subtree->is_empty()) //Si le pasamos un arbol vacio, seteamos nullptr
        this->root_->set_right(nullptr);

    else
        this->root_->set_right(AVLTNode<T>::create(subtree->root_->item(), this->root_, subtree->root_->left(), subtree->root_->right()));

    assert(subtree->is_empty() || right()->item() == subtree->item());
    assert(!subtree->is_empty() || right()->is_empty());
}

template <class T>
void AVLTree<T>::find_inorder_sucessor()
{
    assert(current_exists());
#ifndef NDEBUG
    T old_curr = current();
#endif
    //TODO

    this->parent_ = this->current_;
    this->current_ = this->current_->right(); //El sucesor es el siguiente mayor, por lo que primero deberemos ir a la derecha

    while (this->current_->has_left()) //Despues de ir a la derecha, iremos todo lo que podamos a la izquierda
    {
        this->parent_ = this->current_;
        this->current_ = this->current_->left();
    }
    assert(current_exists());
#ifndef NDEBUG
    assert(current() > old_curr);
#endif
}

template <class T>
void AVLTree<T>::rotate_left(typename AVLTNode<T>::Ref node)
{
    //TODO
    auto lc = node->left(); //Creamos el nodo que tendra el valor del izquiedo

    if (!node->has_parent()) //Entramos si el nodo no tiene padre
        root_ = lc;

    else if (node == node->parent()->right()) //Entramos si el nodo es igual al derecho del padre de nodo
        node->parent()->set_right(lc);

    else if (node == node->parent()->left()) //Entramos si el nodo es igual al izquiedo del padre de nodo
        node->parent()->set_left(lc);

    lc->set_parent(node->parent()); //Seteamos el padre

    if (lc->has_right()) //SI el nodo lc tiene derecho
    {
        node->set_left(lc->right());
        lc->right()->set_parent(node);
    }
    else
        node->remove_left();

    lc->set_right(node);  //Seteamos el derecho de lc
    node->set_parent(lc); //Seteamos el padre de node

    //Calculamos la altura de estos nodos al acabar
    node->compute_height();
    lc->compute_height();
}

template <class T>
void AVLTree<T>::rotate_right(typename AVLTNode<T>::Ref node)
{
    //TODO
    auto rc = node->right(); //Creamos el nodo que tendra el valor del derecho

    if (!node->has_parent()) //Entramos si el nodo no tiene padre
        root_ = rc;

    else if (node == node->parent()->right()) //Entramos si el nodo es igual al derecho del padre de nodo
        node->parent()->set_right(rc);

    else if (node == node->parent()->left()) //Entramos si el nodo es igual al izquierdo del padre de nodo
        node->parent()->set_left(rc);

    rc->set_parent(node->parent()); //Seteamos el padre

    if (rc->has_left()) //Si el nodo rc tiene izquierdo
    {
        node->set_right(rc->left());
        rc->left()->set_parent(node);
    }
    else
        node->remove_right();

    rc->set_left(node);   //Seteamos el izquierdo de rc
    node->set_parent(rc); //Seteamos el padre de node

    //Calculamos la altura de estos nodos al acabar
    node->compute_height();
    rc->compute_height();
}

template <class T>
void AVLTree<T>::make_balanced()
{
#ifdef __ONLY_BSTREE__
    return;
#else
    //TODO
    while (this->parent_ != nullptr)
    {
        this->parent_->compute_height();          //COmputamos la altura de parent
        int bf = this->parent_->balance_factor(); //Calculamos el balance factor de parent

        if (bf <= -2) //Entramos si el balance factor es invalido (por abajo)
        {
            auto child = this->parent_->left();     //Creamos el nodo
            int bf_child = child->balance_factor(); //Calculamos el balance factor del nodo

            if (bf_child <= 0) //Si este balance factor es menor que 1, solo rotamos a la izquierda
                rotate_left(this->parent_);

            else //Aplicamos las rotaciones
            {
                rotate_right(child);
                rotate_left(this->parent_);
            }
        }
        else if (bf >= 2) //Entramos si el balance factor es invalido (por arriba)
        {
            auto child = this->parent_->right();    //Creamos el nodo
            int bf_child = child->balance_factor(); //Calculamos el balance factor del nodo

            if (bf_child >= 0) //Si este balance factor es menor que 1, solo rotamos a la derecha
                rotate_right(this->parent_);
            else //Aplicamos las rotaciones
            {
                rotate_left(child);
                rotate_right(this->parent_);
            }
        }
        else //Entramos si el balance factor es correcto
            this->parent_ = this->parent_->parent();
    }

#endif //__ONLY_BSTREE__
}
