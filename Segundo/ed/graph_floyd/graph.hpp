#ifndef __ED_GRAPH_HPP__
#define __ED_GRAPH_HPP__

#include <cassert>
#include <cstdlib>
#include <memory>
#include <vector>
#include <limits>

template<class T> class WGraph;

/**
 * @brief Class to model the Node of a Graph ADT.
 * @ingroup graph
 */
template <class T>
class GraphNode
{
public:
    /** @brief Models a reference to a Node.*/
    typedef std::shared_ptr< GraphNode<T> > Ref;

  /** @name Makers*/
  /**@{*/

    /** @brief Makes a new node.
     * @args label is the label of the new node.
     * @args item is the item saved in the node.
     * @pre no othe node in the graph has the same label.
     * @post not isVisited()
     */
     GraphNode(size_t label, T const& item):
         _label(label), _item(item), _visited(false)
     {}

     /** @brief Makes a new node.
     * @args label is the label of the new node.
     * @args item is the item saved in the node.
     * @pre no othe node in the graph has the same label.
     * @post not isVisited()
     */
     static typename GraphNode<T>::Ref make(size_t label, const T& item)
     {
         return std::make_shared< GraphNode<T> >(label, item);
     }

    ~GraphNode() {}
  /**@}*/

  /** @name Observers*/
  /**@{*/

  /** @brief Get data saved.
      @return a reference to the data saved in the node.
   */
  T const& item() const
  {
      return _item;
  }

  /** @brief get the label of the node.
   * @return the node's label.
   * @post no other node in the graph has this label.
   */
   size_t label() const
   {
       return _label;
   }

   /** @brief Has been the node visited?
    * return true if the node was visited.
    */
   bool is_visited() const
   {
       return _visited;
   }

  /**@}*/

  /** @name Modifiers*/
  /** @{*/

   /**@brief Set data saved in the node.
   * @arg[in] item is the data to save in.
   * @post set_item()==item
   */
   void set_item(T const& new_item)
   {
       _item = new_item;
   }

   /** @brief Set the flag visited.*/
   void set_visited(bool new_state)
   {
       _visited = new_state;
   }
  /** @} */

protected:

    size_t _label;
    T _item;
    bool _visited;
};

/**
 * @brief Class to model the Edge of a Graph ADT.
 * A edged is directed link u -> v.
 * @ingroup graph
 */
template <class T, class E>
class GraphEdge
{
public:

  /** @brief a referece to a node.*/
  typedef typename GraphNode<T>::Ref NodeRef;

  /** @brief Models a reference to an Edge.*/
  typedef std::shared_ptr< GraphEdge <T, E> > Ref;

  /** @name Makers*/
  /** @{*/
    /**
    * @brief Makes a new node.
    * @arg[in] u the first node.
    * @arg[in] v the second node.
    * @arg[in] item the data to save.
    * @post first()==u and second()=v
    */
    GraphEdge(NodeRef& u,
              NodeRef& v,
              E const& item):
        _u(u), _v(v), _item(item)
    {}

    /**
    * @brief Makes a new node.
    * @arg[in] u the first node.
    * @arg[in] v the second node.
    * @arg[in] item the data to save.
    * @post first()==u and second()=v
    */
    static Ref make(NodeRef& u,
                    NodeRef& v,
                    E const& item)
    {
        return std::make_shared< GraphEdge<T, E> > (u, v, item);
    }

    ~GraphEdge() {}
  /** @}*/

  /** @name Observers*/
  /** @{*/

  /** @brief Get data item. */
    E const& item() const
    {
        return _item;
    }

  /** @brief Is node u an end of this edge.
  * @args[in] u is a node to test.
  * @return true is u is one of the edge's ends.
  */
  bool has(NodeRef const& u) const
  {
      return u==_u || u==_v;
  }

  /** @brief The other end node that is not u.
  * @args[in] u is a end node.
  * @return the other end node that is not u.
  * @pre has(u)
  * @post has(retVal) and other(retVal)=u
  */
  NodeRef const& other(NodeRef const& u) const
  {
      assert( has(u) );      
      if (u == _u)
          return _v;
      else
          return _u;
  }

  /** @brief The other end node that is not u.
  * @args[in] u is a end node.
  * @return the other end node that is not u.
  * @pre has(u)
  * @post has(retVal) and other(retVal)=u
  */
  NodeRef& other(NodeRef const& u)
  {
      assert( has(u) );
      if (u == _u)
          return _v;
      else
          return _u;
  }

  /** @brief the start node when a directed edge.
  * @return the start node.
  */
  NodeRef const & first() const
  {
      return _u;
  }

  /** @brief the start node when a directed edge.
  * @return the start node.
  */
  NodeRef & first()
  {
      return _u;
  }

  /** @brief the end node when a directed edge.
  * @return the end node.
  */
  NodeRef const& second() const
  {
      return _v;
  }

  /** @brief the end node when a directed edge.
  * @return the end node.
  */
  NodeRef & second()
  {
      return _v;
  }

  /**@}*/

  /** @name Modifiers*/
  /** @{*/

   /**@brief Set data saved in the node.
   * @arg[in] item is the data to save in.
   * @post getData()==item
   */
   void set_item(E const& item)
   {
       _item = item;
   }

  /** @} */
private:

    NodeRef _u;
    NodeRef _v;
    E _item;
};

/**
 * @brief Models the Weighted Graph ADT.
 * A Weighted graph is directed graph where all nodes are connected with all
 * by default with infinity weigth.
 * Two nodes u,v are adjacent if the weight of the edge u->v is less than infinity.
 * @ingroup graph
 *
 */
template <class T>
class WGraph
{
public:

    /** @brief a ref to a graph's node. */
    typedef typename GraphNode<T>::Ref NodeRef;

    /** @brief a ref to a graph's edge. */
    typedef typename GraphEdge<T, float>::Ref EdgeRef;


  /** @name Makers*/
  /** @{*/

    /**
     * @brief Makes a Weighted Graph with capicity nodes.
     * @pre capacity >= 0
     */
    WGraph (size_t capacity=0):
        _nodes(capacity),
        _a_mat(capacity,
               std::vector<float>(capacity,
                                  std::numeric_limits<float>::infinity())),
        _curr_node(capacity), _curr_edge(capacity)
    {}

    ~WGraph () {}

  /** @}*/

  /** @name Observers*/
  /**@{*/

    /**
    * @brief is the graph empty?
    * @return true if there is not any node.
    */
    bool is_empty() const
    {
        return _size == 0;
    }

    /**
    * @brief is the graph empty?
    * @return true if there is not any node.
    */
    bool is_full() const
    {
        return _size == _nodes.size();
    }

    /**
     * @brief Get current number of nodes.
     * @post not is_empty() implies (0<retVal<capacity())
     */
    size_t size() const
    {
        return _size;
    }

    /**
     * @brief Get the max number of nodes to be added.
     * @return return the graph's capacity.
     */
    size_t capacity() const
    {
        return _nodes.size();
    }

    /** @brief is u a node of this graph?
     * @pre u is not nullptr.
     * @return if its true.
     */
    bool has( NodeRef const& u) const
    {
        assert (u.get() != nullptr);
        return u->label() < capacity() &&
                _nodes[u->label()].get() == u.get();
    }

    /**
    * @brief Are nodes u and v adjacents?
    * Two nodes are adjacents if the weigth of the edge u->v is less than inf.
    * @arg[in] u ,
    * @arg[in] v are nodes.
    * @return true if the weight of the edge u->v < inf.
    * @pre u and v are nodes of the graph.
    */
    bool are_adjacent (NodeRef& u,
                       NodeRef& v) const
    {
        assert( has(u) && has(v) );
        return _a_mat[u->label()][v->label()] <
                std::numeric_limits<float>::infinity();
    }

    /**
    * @brief Is the node cursor valid?
    * @return true if the node cursor references to a valid node.
    */
    bool has_current_node() const
    {
        return _curr_node < _size;
    }

    /**
    * @brief Get the current node.
    * @return a reference to the current node.
    * @pre has_current_node()
    */
    NodeRef const& current_node() const
    {
        assert(has_current_node());
        return _nodes[_curr_node];
    }

    /**
    * @brief Get the current node.
    * @return a reference to the current node.
    * @pre has_current_node()
    */
    NodeRef & current_node()
    {
        assert(has_current_node());
        return _nodes[_curr_node];
    }

    /**
    * @brief Is the edge cursor valid?.
    * @pre has_current_node()
    * @return true if the edge cursor references a valid edge.
    */
    bool has_current_edge() const
    {
        assert(has_current_node());
        return _curr_edge<_size;
    }

    /**
     * @brief Get the weight of current edge.
     * @pre has_current_edge()
     */
    float current_weight() const
    {
        assert(has_current_edge());
        return _a_mat[_curr_node][_curr_edge];
    }

    /**
     * @brief Get the weight of a u->v edge.
     * @pre has(u) and has(v)
     */
    float weight(NodeRef u, NodeRef v) const
    {
        assert(has(u));
        assert(has(v));
        return _a_mat[u->label()][v->label()];
    }

    /**
    * @brief Get the current edge.
    * @return a reference to the current edge.
    * @pre has_current_edge()
    * @post retVal->has(current_node()).
    */
    EdgeRef current_edge() const
    {
        assert(has_current_edge());
        return GraphEdge<T, float>::make(_nodes[_curr_node],
                                         _nodes[_curr_edge],
                                         _a_mat[_curr_node][_curr_edge]);
    }

    /**
    * @brief Get the current edge.
    * @return a reference to the current edge.
    * @pre has_current_edge()
    * @post retVal->first().get() == current_node().get().
    */
    EdgeRef current_edge()
    {
        assert(has_current_edge());
        return GraphEdge<T, float>::make(_nodes[_curr_node],
                                         _nodes[_curr_edge],
                                         _a_mat[_curr_node][_curr_edge]);
    }

    /**
     * @brief get a node by its label.
     * @pre label< size()
     */
    NodeRef const& node(size_t label) const
    {
        assert(label<size());
        return _nodes[label];
    }

    /**
     * @brief get a node by its label.
     * @pre label< size()
     */
    NodeRef & node(size_t label)
    {
        assert(label<size());
        return _nodes[label];
    }

    /**
    * @brief Get the edge link to vertex.
    * @arg[in] u is the first vertex
    * @arg[in] v is the second vertex.
    * @return a reference to the edge.
    * @pre has(u)
    * @pre has(v)
    */
    EdgeRef edge(NodeRef & u, NodeRef & v)
    {
        assert(has(u));
        assert(has(v));
        return GraphEdge<T, float>::make(u, v, _a_mat[u->label()][v->label()]);
    }

  /** @}*/

  /** @name Modifiers*/
  /** @{*/

    /** @name Cursor Management*/
    /** @{*/
        /**
         * @brief set the visited state for all then nodes.
         */
        void set_visited(bool state)
        {
            for(size_t n=0;n<_size;++n)
                _nodes[n]->set_visited(state);
        }

        /**
        * @brief Goto to the first node.        
        * @post is_empty() implies not has_current_node().        
        * @post not has_current_edge() or current_edge()->first() == current_node()
        */
        void goto_first_node()
        {
                _curr_node = 0;
                if (has_current_node())
                    goto_first_edge();
        }

        /**
        * @brief Goto to the first edge incident in curr_node() with weigth < inf.
        * @pre has_current_node()
        * @post not has_current_edge() or current_edge()->first() == current_node()
        */
        void goto_first_edge()
        {
            assert(has_current_node());
            _curr_edge = 0;
            while(_curr_edge<_size &&
                  _a_mat[_curr_node][_curr_edge]==std::numeric_limits<float>::infinity())
                ++_curr_edge;
        }

        /**
        * @brief Move the cursor to the next node if there is.
        * The edge cursor is also affected.
        * @pre has_current_node().
        * @post not has_current_edge() or current_edge()->first() == current_node()
        */
        void goto_next_node()
        {
            assert(has_current_node());
            ++_curr_node;
            if (has_current_node())
                goto_first_edge();
        }

        /**
        * @brief Move the cursor to the next edge with weight < inf.
        * @pre has_current_edge().
        * @post not has_current_edge() or current_edge()->first() == current_node()
        */
        void goto_next_edge()
        {
            assert(has_current_edge());
            do
            {
                ++_curr_edge;
            }
            while(_curr_edge<_size &&
                  _a_mat[_curr_node][_curr_edge]==std::numeric_limits<float>::infinity());
        }

        /**
        * @brief Move the cursor to a node.
        * @arg[in] u is a node.
        * @pre has(u)
        * @post has_current_node() && current_node().get()==u.get().
        */
        void goto_node(NodeRef const& u)
        {
            assert(has(u));
            _curr_node = u->label();
            goto_first_edge();
        }

        /**
        * @brief Move the node and graph cursors.
        * @arg[in] u,
        * @arg[in] v are nodes.
        * @pre has(u) and has(v)
        * @pre weight(u, v)<inf
        * @post current_node()==u
        * @post current_edge()->second() == v
        */
        void goto_edge(NodeRef const& u,
                       NodeRef const& v)
        {
            assert(has(u) && has(v));
            assert(weight(u, v)<std::numeric_limits<float>::infinity());
            _curr_node = u->label();
            _curr_edge = v->label();
        }

        /**
        * @brief Move the node and graph cursors.
        * @arg[in] e is graph's edge.
        * @pre has(e->first()) and has(e->second())
        * @pre e->item()<inf
        * @post current_node()==u.get()
        * @post current_edge()->second() == v.get()
        */
        void goto_edge(EdgeRef const& e)
        {
            assert(has(e->first()));
            assert(has(e->second()));
            assert(e->item()<std::numeric_limits<float>::infinity());
            goto_edge(e->first(), e->second());
        }

        /**
         * @brief find the fisrt node given its key.
         * @return the a ref to the node.
         * @post retVal.get()==nulptr or current_node()->item()==key
         */
        NodeRef find(const T& key)
        {
            NodeRef n;
            bool found=false;
            goto_first_node();
            while(has_current_node() && !found)
            {
                if (current_node()->item()==key)
                    found = true;
                else
                    goto_next_node();
            }
            if (found)
                n = current_node();
            return n;
        }

        /**
         * @brief find the next node given its key.
         * @return true if it is found a node.
         * @pre has_current_node()
         * @post not retVal or current_node()->item()==key
         */
        bool find_next(const T& key)
        {
            assert(has_current_node());
            bool found = false;
            do
            {
                goto_next_node();
                if (has_current_node() && current_node()->item()==key)
                    found = true;
            }
            while(has_current_node() && !found);
            return found;
        }

    /** @} */

    /** @name Graph editing */
    /** @{ */

        /**
         * @brief Set the weight of current edge.
         * @pre has_current_edge()
         */
        void set_current_weight(float new_w)
        {
            assert(has_current_edge());
            _a_mat[_curr_node][_curr_edge] = new_w;
        }

        /**
         * @brief Set the weight of u->v edge.
         * @pre has(u) and has(v).
         */
        void set_weight(NodeRef u, NodeRef v, float new_w)
        {
            assert(has(u));
            assert(has(v));
            _a_mat[u->label()][v->label()] = new_w;
        }

        /**
        * @brief Add a new node.
        * @arg[in] item is the data item to be save in the new node.
        * @pre not is_full()
        * @post has_current_node() and current_node()->item() == item
        * @post not has_current_edge()
        */
        void add_node(T const& item)
        {
            assert(! is_full());
            _nodes[_size] = GraphNode<T>::make(_size, item);
            _curr_node = _size;
            _curr_edge = _size+1;
            ++_size;
            assert(has_current_node() && current_node()->item()==item);
            assert(!has_current_edge());
        }

    /** @} */

  /** @} */
        protected:

    std::vector< NodeRef > _nodes;
    std::vector< std::vector<float> > _a_mat;
    size_t _size = 0;
    size_t _curr_node;
    size_t _curr_edge;
};




#endif
