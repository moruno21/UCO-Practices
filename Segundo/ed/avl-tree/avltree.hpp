#pragma once

#include <cassert>
#include <exception>
#include <functional>
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

/**
 * @brief a AVLTree's Node.
 * Models a node of AVLTree.
 * @invariant height = 1 + max{ left's height, right's height }
*/
template <class T>
class AVLTNode
{
public:
   /** @brief Define a shared reference to a AVLTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
   typedef std::shared_ptr<AVLTNode<T>> Ref;

   /** @name Life cicle.*/
   /** @{*/

   /**
     * @brief Create a AVLTNode.
     * @param it is the node's item value.
     * @param parent is a link to the parent node of this.
     * @param left is a link to the left child node.
     * @param right is a link to the right child node.
     * @return a shared reference to node created.
     */
   AVLTNode(T const &it = T(), AVLTNode<T>::Ref parent = nullptr,
            AVLTNode<T>::Ref left = nullptr, AVLTNode<T>::Ref right = nullptr);

   /**
     * @brief Create a AVLTNode.
     * @param it is the node's item value.
     * @param parent is a link to the parent node of this.
     * @param left is a link to the left child node.
     * @param right is a link to the right child node.
     * @return a shared reference to node created.
     */
   static typename AVLTNode<T>::Ref create(T const &it = T(),
                                           AVLTNode<T>::Ref parent = nullptr,
                                           AVLTNode<T>::Ref left = nullptr,
                                           AVLTNode<T>::Ref right = nullptr);
   /** @brief Destroy a AVLTNode. **/
   ~AVLTNode()
   {
   }

   /** @}*/

   /** @name Observers.*/
   /** @{*/

   /** @brief Get the data item.*/
   const T &item() const;

   /**
     * @brief Get the node's height.
     * @post time analysis: O(1).
     */
   int height() const;

   /**
     * @brief Get the balance factor of the node.
     * @post time analysis: O(1).
     */
   int balance_factor() const;

   /** @brief Has it a parent?*/
   bool has_parent() const;

   /** @brief get the parent.*/
   AVLTNode<T>::Ref parent() const;

   /** @brief Has it a left child?*/
   bool has_left() const;

   /** @brief get the left child.*/
   AVLTNode<T>::Ref left() const;

   /** @brief Has it a right child? */
   bool has_right() const;

   /** @brief get the right child.*/
   AVLTNode<T>::Ref right() const;

   /** @}*/

   /** @name Modifiers.*/
   /** @{*/

   /**
     * @brief Set the data item.
     * @post item() == new_it
     */
   void set_item(const T &new_it);

   /**
     * @brief Set the parent.
     * @post parent()==new_parent
     */
   void set_parent(AVLTNode<T>::Ref const &new_parent);

   /**
     * @brief Remove link to the left child.
     * @post !has_parent()
     */
   void remove_parent();

   /**
     * @brief Set the left child.
     * @post left()==new_child
     */
   void set_left(AVLTNode<T>::Ref const &new_child);

   /**
     * @brief Remove link to the left child.
     * @post !has_left()
     */
   void remove_left();

   /**
     * @brief Set the right child.
     * @post right()==new_child
     */
   void set_right(AVLTNode<T>::Ref const &new_child);

   /**
     * @brief Remove link to the right child.
     * @post !has_right()
     */
   void remove_right();

   /**
     * @brief Compute height.
     * @post Time analysis: O(1)
     */
   void compute_height();

protected:
   /**
     * @brief Check the AVLTNode invariant.
     * @return true if height() == 1 + max{ left's height, right's height }
     */
   bool check_height_invariant() const;

   //TODO
   T item_;
   AVLTNode<T>::Ref parent_;
   AVLTNode<T>::Ref left_;
   AVLTNode<T>::Ref right_;
   int height_;
   //
};

/**
 * @brief ADT AVLTree.
 * A AVLTree is a binary tree that meets the next two invariants:
 * is_a_binary_search_tree()
 * is_a_balanced_tree()
 */
template <class T>
class AVLTree
{
public:
   /** @brief Define a shared reference to a AVLTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
   typedef std::shared_ptr<AVLTree<T>> Ref;

   /** @name Life cicle.*/
   /** @{*/

   /**
     * @brief Create an empty AVLTree.
     * @post is_empty()
     */
   AVLTree();

   /**
     * @brief Create a leaf tree.
     * @post is_empty()
     */
   AVLTree(T const &item);

   /**
     * @brief Create an empty AVLTree.
     * @return a shared reference to the new tree.
     */
   static typename AVLTree<T>::Ref create();

   /**
     * @brief Create a leaf tree.
     * @post is_empty()
     */
   static typename AVLTree<T>::Ref create(T const &item);

   /**
     * @brief Unfold an AVLTree from an input stream.
     * The input format will be:
     * '[]' for the empty tree.
     * '[ '<item>' '<left-subtree>' '<right-subtree>' ]'
     *
     * For example a tree with three nodes:
     * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
     *
     * @param in is the input stream.
     * @param parent is the parent node of the node to be unfolded.
     * @return The node unfolded on success.
     * @warning std::runtime_error("Wrong input format"),
     * std::runtime_error("It is not a binary search tree") or
     * std::runtime_error("It is not an avl bstree") will throw if an error
     * happend.
     */
   static typename AVLTree<T>::Ref create(std::istream &in) noexcept(false);

#ifdef __ONLY_BSTREE__
   /**
     * @brief create a perfectly balanced BSTree.
     * @param data are the keys to be stored.
     * @return the created tree.
     * @pre data.size()>0
     * @post for each subtree: |right()->size() - left()->size()|<=1
     */
   static typename AVLTree<T>::Ref create(std::vector<T> &data);
#endif //#ifdef __ONLY_BSTREE__

   /** @brief Destroy a AVLTree.**/
   ~AVLTree()
   {
   }

   /** @}*/

   /** @name Observers*/

   /** @{*/

   /** @brief is the list empty?.*/
   bool is_empty() const;

   /** @brief Get the root item.
   * @pre not is_empty();
   */
   T const &item() const;

   /**
   * @brief Fold an AVLTree into an output stream.
   *  * The output format will be:
   * [ <item> <left> <right> ] or [] if it is a empty tree.
   * @param out is the output stream.
   * @return the output stream.
  */
   std::ostream &fold(std::ostream &out) const;

   /** @brief Is the cursor at a valid position?*/
   bool current_exists() const;

   /**
   * @brief Get the current's item.
   * @return The item save in current node.
   * @pre current_exist()
   */
   T const &current() const;

   /**
   * @brief Computes the current's level (depth) in the tree.
   * @return the level (depth) of current in the tree.
   * @pre current_exist()
   * @post Time analysis: O(N)
   */
   int current_level() const;

   /**
   * @brief Get the left subtree.
   * @pre !is_empty()
   */
   typename AVLTree<T>::Ref left() const;

   /**
   * @brief Get the right subtree.
   * @pre !is_empty()
   */
   typename AVLTree<T>::Ref right() const;

   /**
   * @brief Return the number of keys stored in the tree.
   * @return the tree's size.
   */
   int size() const;

   /**
   * @brief Return the tree's height.
   * @return the tree's height.
   * @post Time analysis: O(1)
   */
   int height() const;

   /**
   * @brief Get balance factor of the tree.
   * @return the tree's balanced factor.
   * @post Time analysis: O(1)
   */
   int balance_factor() const;

   /**
   * @brief Has the tree got this key
   * @post !old.current_exists() || old.current()==current()
   */
   bool has(const T &k) const;

   /** @}*/

   /** @name Modifiers*/

   /** @{*/

   /**
   * @brief Create the Root node.
   * @param item is value of the root's item.
   * @pre is_empty()
   * @post !is_empty()
   * @post item()==item
   */
   void create_root(T const &item);

   /**
   * @brief Search a key moving the cursor.
   * @post retV implies current()==k
   * @post not retv implies not current_exits()
   */
   bool search(T const &k);

   /**
   * @brief Insert a new key in the tree.
   * @warning if k is already in the tree, only it is updated.
   * @post current_exists()
   * @post current()==k
   */
   void insert(T const &k);

   /**
   * @brief remove current from the tree.
   * @pre current_exists()
   * @post not current_exists()
   */
   void remove();

   /** @}*/

protected:
   /**
   * @brief Check the binary search tree invariant.
   * @return true if in-order traversal follow an ordered key sequence.
   * @post Time Analysis: O(N)
   */
   bool is_a_binary_search_tree() const;

   /**
   * @brief Check the balanced tree invariant.
   * A tree is balanced is empty or the left and right subtrees are balanced and
   * its balance factor is in {-1,0,1}.
   * @return true if left and right trees are balanced and this tree is balanced.
   */
   bool is_a_balanced_tree() const;

   /** @brief Create a AVLTree using a given node as root.*/
   AVLTree(typename AVLTNode<T>::Ref root_node);

   /**
   * @brief Create a AVLTree node the giving node as root.
   * @param root is the root of the new tree.
   * @return a shared reference to the new tree.
   */
   static typename AVLTree<T>::Ref create(typename AVLTNode<T>::Ref root);

   /** @brief Get the root node.*/
   typename AVLTNode<T>::Ref const &root() const;

   /**
   * @brief Attach a new subtree as left child.
   * @param subtree is the tree to be attached.
   * @post (subtree->is_empty() || left()->item()==subtree->item())
   * @post (!subtree->is_empty() || left()->is_empty())
   * @warning this method does not check invariants.
   */
   void set_left(typename AVLTree<T>::Ref &subtree);

   /**
   * @brief Attach a new subtree as right child.
   * @param subtree is the tree to be attached.
   * @post (subtree->is_empty()|| right()->item()==subtree->item())
   * @post (!subtree->is_empty()|| right()->is_empty())
   * @warning this method does not check invariants.
   */
   void set_right(typename AVLTree<T>::Ref &subtree);

   /**
   * @brief find the sucessor in order of current.
   * @pre current_exist()
   * @post current_exist() && !current_->has_left()
   * @post current()>old.current()
   */
   void find_inorder_sucessor();

   /**
   * @brief rotate_left
   *                 n            c
   *                / \          / \
   *               c   C  ->    A   n
   *              / \              / \
   *             A   B            B  C
   * @param node is the node to be rotated.
   */
   void rotate_left(typename AVLTNode<T>::Ref node);

   /**
   * @brief Rotate the node to the right.
   *                 n            c
   *                / \          / \
   *               A   c  ->    n   C
   *                  / \      / \
   *                 B   C    A   B
   * @param node is the node to be rotated.
   */
   void rotate_right(typename AVLTNode<T>::Ref node);

   /**
   * @brief make a balanced tree.
   * Process from parent_ going up to the root.
   */
   void make_balanced();

   //TODO
   //Chose a representation for this TAD.
   typename AVLTNode<T>::Ref root_;
   typename AVLTNode<T>::Ref current_;
   typename AVLTNode<T>::Ref parent_;
   //
};
