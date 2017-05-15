#ifndef GRAPH_H
#define GRAPH_H

#include "graph_detail.h"

// Constraints:
// NodeLabes must be unique
// Graph::Edge must be hashable
// NodeLabel must copy-constructible
// NodeLabel must have equality operator
// NodeLabel must be copy-constructible
template <typename NodeLabel, typename EdgeLabel>
class Graph
{
public:
  using Edge           = detail::edge           <NodeLabel, EdgeLabel>;
  using UnlabeledEdge  = detail::unlabeled_edge <NodeLabel, EdgeLabel>;
  using const_iterator = detail::node_iterator  <NodeLabel, EdgeLabel>;


  Graph() : num_of_nodes(0) {};
  ~Graph() = default;

  void                   add_edge       (const Edge&);
  void                   add_node       (const NodeLabel&);
  std::vector<Edge>      get_edges_from (const NodeLabel&) const;
  std::vector<NodeLabel> get_nodes_from (const NodeLabel&) const;
  std::vector<Edge>      get_edges_to   (const NodeLabel&) const;
  std::vector<NodeLabel> get_nodes_to   (const NodeLabel&) const;

  std::vector<Edge>  get_edges()  const;

  bool is_member   (const NodeLabel&) const;

  void delete_node (const NodeLabel&);
  void delete_edge (const UnlabeledEdge&);

  int edge_count() const { return edges.size(); }
  int node_count() const { return num_of_nodes; }

  const_iterator cbegin() const { return detail::node_iterator<NodeLabel, EdgeLabel>(contexts.cbegin()); }
  const_iterator cend()   const { return detail::node_iterator<NodeLabel, EdgeLabel>(contexts.cend()); }

private:
  using Context   = detail::context   <NodeLabel, EdgeLabel>;
  using EdgeHash  = detail::edge_hash <NodeLabel, EdgeLabel>;
  using EdgeEqual = detail::edge_equal<NodeLabel, EdgeLabel>;

  Context& insert_node (const NodeLabel&);

  int num_of_nodes;

  std::unordered_set<Edge, EdgeHash, EdgeEqual> edges;
  std::unordered_map<NodeLabel, Context> contexts;
};


#include "graph.hpp"

#endif // GRAPH_H
