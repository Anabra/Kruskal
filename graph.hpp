#include <algorithm>
#include <iostream>

template <typename NL, typename EL>
Graph<NL, EL>::Graph() : num_of_nodes(0), num_of_edges(0)
{

}

template <typename NL, typename EL>
Graph<NL, EL>::~Graph()
{

}



template <typename NL, typename EL>
auto Graph<NL, EL>::insert_node(const NL& node_label) -> Context&
{
  Context empty_context;
  auto result      = contexts.insert({ node_label, empty_context });
  bool is_inserted = result.second;

  if (is_inserted)
    num_of_nodes++;

  return result.first->second;
}


template <typename NL, typename EL>
void Graph<NL, EL>::add_node (const NL& node_label)
{
  insert_node(node_label);
}


template <typename NL, typename EL>
void  Graph<NL, EL>::add_edge (const Edge& edge)
{
  // std::cerr << "add_edge" << std::endl;
  Context& c1 = insert_node(edge.from);
  Context& c2 = insert_node(edge.to);
  // std::cerr << "lambda" << std::endl;

  /// does the from node have an edge that ends in the to node?
  auto l1 = [&edge,&c1] ()
    {
      return c1.outgoing.cend() !=
      std::find_if(c1.outgoing.cbegin(),
                   c1.outgoing.cend(),
                   [&edge](auto e){return e.to == edge.to;});
    };

  // std::cerr << "if" << std::endl;
  if (l1()) return; // multi-edges

  // std::cerr << "else" << std::endl;
  c1.outgoing.push_back({edge.label, edge.to});
  c2.incoming.push_back({edge.label, edge.from});
  edges.insert(edge);
  num_of_edges++;

  // std::cerr << "done" << std::endl;
}

template <typename NL, typename EL>
auto Graph<NL, EL>::get_edges_from (const NL& node) const -> std::vector<Edge>
{
  std::vector<Edge> edge_vec;
  auto node_it = contexts.find(node);

  if (node_it != contexts.cend())
  {
    for (auto e : node_it->second.outgoing)
    {
      edge_vec.push_back({node, e.label, e.to});
    }
  }

  return edge_vec;
}

template <typename NL, typename EL>
auto Graph<NL, EL>::get_nodes_from (const NL& node) const -> std::vector<NL>
{
  std::vector<NL> nodes;
  auto node_it = contexts.find(node);

  if (node_it != contexts.cend())
  {
    for (auto e : node_it->second.outgoing)
    {
      nodes.push_back(e.to);
    }
  }

  return nodes;
}

template <typename NL, typename EL>
auto Graph<NL, EL>::get_edges_to (const NL& node) const -> std::vector<Edge>
{
  std::vector<Edge> edge_vec;
  auto node_it = contexts.find(node);

  if (node_it != contexts.cend())
  {
    for (auto e : node_it->second.incoming)
    {
      edge_vec.push_back({e.from, e.label, node});
    }
  }

  return edge_vec;
}

template <typename NL, typename EL>
auto Graph<NL, EL>::get_nodes_to (const NL& node) const -> std::vector<NL>
{
  std::vector<NL> nodes;
  auto node_it = contexts.find(node);

  if (node_it != contexts.cend())
  {
    for (auto e : node_it->second.incoming)
    {
      nodes.push_back(e.from);
    }
  }

  return nodes;
}

template <typename NL, typename EL>
auto Graph<NL, EL>::get_edges() const -> std::vector<Edge>
{
  std::vector<Edge> es;
  std::copy(edges.cbegin(), edges.cend(), std::back_inserter(es));
  return es;
}


template <typename NL, typename EL>
bool Graph<NL, EL>::is_member (const NL& node) const
{
  return contexts.find(node) != contexts.cend();
}


template <typename NL, typename EL>
void  Graph<NL, EL>::delete_node (const NL& node)
{
  if (!is_member(node)) return;

  auto in_nodes  = get_nodes_to(node);
  auto out_nodes = get_nodes_from(node);

  for (auto v : in_nodes)
  {
    edges.erase({v, 0, node});

    auto &in_edges = contexts.find(v)->second.outgoing;
    in_edges.erase(std::remove_if(in_edges.begin(),
                                  in_edges.end(),
                                  [&node](auto e){ return e.to == node; } ),
                   in_edges.cend());
  }

  for (auto v : out_nodes)
  {
    edges.erase({node, 0, v});

    auto &out_edges = contexts.find(v)->second.incoming;
    out_edges.erase(std::remove_if(out_edges.begin(),
                                   out_edges.end(),
                                   [&node](auto e){ return e.from == node; } ),
                    out_edges.cend());
  }

  contexts.erase(node);
}


template <typename NL, typename EL>
void  Graph<NL, EL>::delete_edge (const UnlabeledEdge& edge)
{
  NL from_node = edge.from;
  NL to_node   = edge.to;

  if (!is_member(from_node) || !is_member(to_node)) return;

  auto &out_edges = contexts.find(from_node)->second.outgoing;
  out_edges.erase(std::remove_if(out_edges.begin(),
                                 out_edges.end(),
                                 [&to_node](auto e){ return e.to == to_node; } ),
                  out_edges.cend());

  auto &in_edges = contexts.find(to_node)->second.incoming;
  in_edges.erase(std::remove_if(in_edges.begin(),
                                in_edges.end(),
                                [&from_node](auto e){ return e.from == from_node; } ),
                 in_edges.cend());

  edges.erase({edge.from, 0, edge.to});
}



template <typename NL, typename EL>
std::ostream& operator<< (std::ostream& os, const typename detail::edge<NL,EL>& edge)
{
  os << edge.from << " " << edge.label << " " << edge.to;
  return os;
}
