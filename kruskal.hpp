#include <algorithm>

// Constraints:
// EdgeLabel must be numerical type
// ...
template <typename NodeLabel, typename EdgeLabel>
Graph<NodeLabel, EdgeLabel> kruskal (const Graph<NodeLabel, EdgeLabel>& g)
{
  Graph<NodeLabel, EdgeLabel> spanning_tree;
  auto edges = g.get_edges();

  disjoint_set<NodeLabel> h;
  for (auto node_it = g.cbegin(); node_it != g.cend(); node_it++)
  {
    h.add(*node_it);
  }

  radix_sort(edges, [](const auto& edge){ return edge.label; });

  for (auto edge : edges)
  {
    if (!h.connected(edge.from, edge.to))
    {
      h.merge(edge.from, edge.to);
      spanning_tree.add_edge(edge);
    }
  }

  return spanning_tree;
}
