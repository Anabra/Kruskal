#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include "kruskal.h"

using namespace std;


template <typename T>
ostream& operator<<(ostream& os, const std::vector<T>& vec)
{
    if ( !vec.empty() )
    {
        for(auto it = vec.cbegin(); it != vec.cend(); ++it)
        {
            os << *it << " ";
        }
        os << endl;
    }
    return os;
}


template <typename NodeLabel, typename EdgeLabel>
void parse_undirected_graph(istream& in, Graph<NodeLabel, EdgeLabel>& g)
{
  int num_of_nodes;
  int num_of_edges;

  in >> num_of_nodes;
  NodeLabel v;
  for (int i = 0; i < num_of_nodes; i++)
  {
    in >> v;
    g.add_node(v);
  }

  in >> num_of_edges;
  NodeLabel to;
  NodeLabel from;
  EdgeLabel label;
  for (int i = 0; i < num_of_edges; i++)
  {
    in >> from >> to >> label;
    g.add_edge({from, label, to});
    g.add_edge({to, label, from});
  }
}

int main(int argc, char *argv[])
{
  ifstream in_file(argv[1]);
  ofstream out_file("output.txt");

  Graph<string, int> g;
  parse_undirected_graph(in_file, g);

  Graph<string, int> mst = kruskal(g);

  for (auto edge : mst.get_edges())
  {
    cout     << edge << endl;
    out_file << edge << endl;
  }
}
