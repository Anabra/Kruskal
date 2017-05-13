#ifndef GRAPH_DETAIL_H
#define GRAPH_DETAIL_H

#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <functional>

template <typename NodeLabel, typename EdgeLabel>
class Graph;

namespace detail
{
  template <typename NodeLabel, typename EdgeLabel>
  class node_iterator;
}

template <typename NL, typename EL>
bool operator== (const detail::node_iterator<NL, EL>& lhs,
                 const detail::node_iterator<NL, EL>& rhs)
{
  return lhs.cit == rhs.cit;
}

template <typename NL, typename EL>
bool operator!= (const detail::node_iterator<NL, EL>& lhs,
                 const detail::node_iterator<NL, EL>& rhs)
{
  return !(lhs == rhs);
}

namespace detail
{
  template <typename NodeLabel, typename EdgeLabel>
  struct edge_to
  {
    EdgeLabel label;
    NodeLabel to;
  };

  template <typename NodeLabel, typename EdgeLabel>
  struct edge_from
  {
    EdgeLabel label;
    NodeLabel from;
  };

  template <typename NodeLabel, typename EdgeLabel>
  struct edge
  {
    NodeLabel from;
    EdgeLabel label;
    NodeLabel to;
  };

  template <typename NodeLabel, typename EdgeLabel>
  struct unlabeled_edge
  {
    NodeLabel from;
    NodeLabel to;
  };

  template <typename NodeLabel, typename EdgeLabel>
  struct context
  {
  private:
    using EdgesTo   = std::vector< edge_to  <NodeLabel, EdgeLabel> >;
    using EdgesFrom = std::vector< edge_from<NodeLabel, EdgeLabel> >;

  public:
    EdgesFrom incoming;
    EdgesTo   outgoing;
  };

  template <typename NodeLabel, typename EdgeLabel>
  class node_iterator
  {
  public:
    node_iterator() {}

    node_iterator  operator++(int)
    {
      node_iterator it(*this);
      cit++;
      return it;
    }
    node_iterator&   operator++()       { ++cit; return *this; }
    NodeLabel        operator*()  const { return cit->first;   }
    const NodeLabel* operator->() const { return &(cit->first); }


  private:
    using Context      = detail::context <NodeLabel, EdgeLabel>;
    using map_iterator = typename
                         std::unordered_map<NodeLabel, Context>::const_iterator;

    node_iterator(const map_iterator& cit) : cit(cit) {}

    map_iterator cit;

    friend bool operator== <NodeLabel, EdgeLabel>
                (const node_iterator<NodeLabel, EdgeLabel>& lhs,
                 const node_iterator<NodeLabel, EdgeLabel>& rhs);

    friend class Graph<NodeLabel, EdgeLabel>;
  };

  template <class T>
  inline void hash_combine(std::size_t& seed, const T& v)
  {
      std::hash<T> hasher;
      seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

  template <typename NL, typename EL>
  struct edge_hash
  {
  public:
    size_t operator() (const typename Graph<NL, EL>::Edge& e) const
    {
      size_t result = node_hasher(e.from);
      detail::hash_combine(result, e.label);
      detail::hash_combine(result, e.to);

      return result;
    }

  private:
    std::hash<NL> node_hasher;
  };

  template <typename NL, typename EL>
  struct edge_equal
  {
    bool operator()(const typename Graph<NL, EL>::Edge& lhs,
                    const typename Graph<NL, EL>::Edge& rhs) const
    {
      return lhs.to == rhs.to && lhs.from == rhs.from;
    }
  };

}


#endif // GRAPH_DETAIL_H
