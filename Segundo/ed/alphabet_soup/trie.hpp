#pragma once
#include <memory>
#include <string>
#include <vector>
#include <map>


/**
 * @brief Models a node of a Trie.
 *
 * The path from the root to this node represents a prefix and
 * the node represents all the following possible prefixes when a new symbol is
 * added.
 *
 * For example: if we have the keys '1231', '1232, '1233' a node will represent
 * the prefix '123' and it will have three child nodes for symbols '1', '2' and
 * '3' respectively.
 *
 * When a node represent a leaf node, it will have a value equal to the key
 * that is represented by the branch from the root to this leaf node.
 */
class TrieNode
{
public:
    /** @brief a reference to a trie node.*/
    typedef std::shared_ptr<TrieNode> Ref;

    /** @name Life cicle.*/
    /** @{*/
    /**
     * @brief Default Constructor.
     */
    TrieNode ();

    /**
     * @brief Create a TrieNode.
     * @return a shared reference to the node created.
     */
    static Ref create();
    /** @}*/

    /** @name Observers. */
    /** @{*/

    /**
     * @brief Has it the node a child for the symbol k?
     */
    bool has(char k) const;

    /**
     * @brief The child for the symbol k?
     * @return a const reference to the node.
     * @pre has(k)
     */
    Ref child(char k) const;

    /**
     * @brief Get the key stored in the node.
     * @return the key stored or a empty string if this node has not a value.
     */
    std::string const& value() const;

    /**
     * @brief Get a map representing the children of this node.
     * @return a const reference to the map.
     */
    std::map<char, Ref> const& children() const;

    /** @} */

    /** @name Modifiers. */
    /** @{*/

    /**
     * @brief Set the value stored in this node.
     * @post value()==new_v
     */
    void set_value(std::string const& new_v);

    /**
     * @brief Add a new child node.
     * @arg[in] k is the next symbol of a using this as prefix.
     * @arg[in] node is the new child node.
     * @post if this node represent a prefix "P*", the new child represent
     * the prefix 'Pk*'.
     */
    void insert(char k, Ref node);

    /** @}*/

protected:

    std::map<char, Ref> children_;
    std::string value_;

};

/**
 * @brief Represents a Trie.
 * A Trie is a m-path tree to store keys based on prefixes.
 */
class Trie
{
public:

    /** @brief a reference to a Trie.*/
    typedef std::shared_ptr<Trie> Ref;

    /** @name Life cicle. */
    /** @{*/

    /**
     * @brief Default Constructor.
     */
    Trie ();

    /**
     * @brief Create a Trie.
     * @return a shared reference to the node created.
     */
    static Ref create();

    /** @}*/

    /** @name Observers. */
    /** @{*/

    /**
     * @brief Get the root node.
     * The root node represent the empty "" prefix.
     * @return a const reference to the root node.
     */
    TrieNode::Ref root() const;

    /**
     * @brief find a key.
     * @param[i] k the key to be found.
     * @return true if the key is stored into the tree.
     * @warning the process must be O(m) with m the key length.
     */
    bool has(std::string const& k) const;

    /**
     * @brief Retrieve all the stored keys given a prefix.
     * @param[in] P is the prefix.
     * @return all the stored keys that match "P*" regular expresion.
     * @warning the process must be O(K) with k the number of stored
     * keys that match "P*".
     */
    std::vector<std::string> keys(std::string const& P=std::string("")) const;

    /** @} */

    /** @name Modifiers. */
    /** @{*/

    /**
     * @brief insert a new key into the tree.
     * @param[in] k is the key to be stored.
     */
    void insert(std::string const& k);

    /** @}*/

protected:

    /**
     * @brief Find the node that represents this prefix.
     * @param[in] P is the prefix to be found.
     * @return a reference to the node or nullptr if that prefix is not stored.
     * @post all the stored keys that match "P*" regular expression are
     * descendants of this node.
     */
    TrieNode::Ref find_node(std::string const& P) const;

    /**
     * @brief Preorder traversal to retrieve keys.
     * This method executes a preorder traversal to get the stored keys
     * that are descendats of this node.
     * @param[in] node is the root node to start the traversal.
     * @param[out] keys is a array to save the retrieved keys.
     */
    void preorder_traversal(TrieNode::Ref const& node,
                            std::vector<std::string> & keys) const;

    //TODO
    TrieNode::Ref root_;
    //
};

