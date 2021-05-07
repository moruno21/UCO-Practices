#include <cassert>
#include "trie.hpp"

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

TrieNode::TrieNode(){
    //TODO
    //Hint: Do you need to do something?
    //No hay que hacer nada
};

TrieNode::Ref TrieNode::create()
{
    return std::make_shared<TrieNode>();
}

bool TrieNode::has(char k) const
{
    bool ret_v = false;
    //TODO
    //Vamos iterando hasta que el valor sea true
    for (auto x = this->children_.begin(); x != this->children_.end(); x++)
    {
        if (x->first == k)
        { //Vamos comprobando si es el valor o no
            ret_v = true;
            break; //Si ya lo hemos encontrado, salimos del bucle
        }
    }
    return ret_v;
}

TrieNode::Ref
TrieNode::child(char k) const
{
    assert(has(k));
    TrieNode::Ref ret_v;
    //TODO
    auto aux_children = this->children_;
    ret_v = aux_children[k];
    //
    return ret_v;
}

std::string const &
TrieNode::value() const
{
    return this->value_;
}

const std::map<char, TrieNode::Ref> &TrieNode::children() const
{
    return this->children_;
}

void TrieNode::set_value(std::string const &new_v)
{
    this->value_ = new_v;
}

void TrieNode::insert(char k, Ref node)
{
    //TODO
    auto new_insert = std::make_pair(k, node); //Creamos el par que vamos a insertar
    this->children_.insert(new_insert);        //Insertamos el par
    //
}

Trie::Trie()
{
    //TODO
    //Hint: Do you need to do something?
}

Trie::Ref Trie::create()
{
    return std::make_shared<Trie>();
}

TrieNode::Ref Trie::root() const
{
    //TODO
    return this->root_;
}

bool Trie::has(std::string const &k) const
{
    bool found = false;
    //TODO Sacada de las diapositivas
    //Remember: The Trie can have a prefix==k but does not store the key k.
    if (this->root_ != nullptr) //Primero tenemos que comprobar que la raiz no este vacía, ya que nos daría violación de segmento
    {
        auto aux_node = this->find_node(k); //Guardamos el resultado en el nodo auxiliar
        //Lo habremos encontrado si los tamaños coinciden y el nodo auxiliar no esta vacio
        found = (aux_node != nullptr);
        found = found && (k.size() == aux_node->value().size());
    }
    //
    return found;
}

std::vector<std::string>
Trie::keys(std::string const &pref) const
{
    std::vector<std::string> keys;
    //TODO
    auto aux_node = this->find_node(pref); //Creamos el nodo donde guardaremos el resultado de la busqueda
    if (aux_node != nullptr)
        this->preorder_traversal(aux_node, keys); //Hacemos esto si el nodo no esta vacio
    //
    return keys;
}

void Trie::insert(std::string const &k)
{
    //TODO

    if (this->root_ == nullptr) //Utilizamos este caso para cuando la raiz este vacia
    {
        auto new_root = std::make_shared<TrieNode>(TrieNode()); //Si la raiz esta vacia creamos un nodo
        this->root_ = new_root;                                 //Asignamos la nueva raiz que hemos creado
    }

    TrieNode::Ref aux_node = this->root_; //Creamos nuestro nodo auxiliar que sera igual a la raiz

    for (unsigned x = 0; x < k.size(); x++) //Recorremos todo el string
    {
        if (aux_node->has(k[x])) //Si el caracter ya esta, entramos
            aux_node = aux_node->child(k[x]);

        else if (!aux_node->has(k[x])) //Si no está, entramos aqui
        {
            auto new_node = std::make_shared<TrieNode>(TrieNode()); //Creamos el nuevo nodo
            aux_node->insert(k[x], new_node);                       //Insertamos el nuevo nodo con el valor x de k
            aux_node = new_node;                                    //Cambiamos el valor de aux_node
        }
    }
    aux_node->set_value(k); //Cuando acabemos el bucle, seteamos el valor k
    assert(has(k));
}

TrieNode::Ref
Trie::find_node(std::string const &pref) const
{
    TrieNode::Ref node;
    //TODO
    node = this->root_;
    for (unsigned x = 0; node->has(pref[x]) && pref.length() >= x; x++) //Vamos buscando el nodo
        node = node->child(pref[x]);                                    //Vamos bajando por los hijos

    return node; //Devolvemos el nodo
}

void Trie::preorder_traversal(TrieNode::Ref const &node,
                              std::vector<std::string> &keys) const
{
    //TODO
    if (node->value() != "") //Si es un nodo hoja, entramos. Si no, no
    {
        std::string node_value = node->value();
        keys.push_back(node_value);
    }

    for (auto x = node->children().begin(); x != node->children().end(); x++) //Llamamos recursivamente a la funcion hasta que lleguemos al final
        this->preorder_traversal(x->second, keys);
}
