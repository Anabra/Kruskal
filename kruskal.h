#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"
#include "radix_sort.h"
#include "disjoint_set.h"

template <typename NodeLabel, typename EdgeLabel>
Graph<NodeLabel, EdgeLabel> kruskal (const Graph<NodeLabel, EdgeLabel>&);

#include "kruskal.hpp"

#endif // KRUSKAL_H
