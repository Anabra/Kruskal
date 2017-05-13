#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <vector>
#include <unordered_map>
#include <initializer_list>

namespace detail
{
  struct predecessor
  {
    predecessor() {};
    predecessor(int pred, int size) : pred(pred), size(size) {}

    int pred;
    int size;
  };
}

// Constraints:
// T must be hashable
// T must have equality operator
// T must be copy-constructible
template <class T>
class disjoint_set
{
public:
  disjoint_set() = default;
  disjoint_set(std::initializer_list<T> elements);
  ~disjoint_set() = default;

  int size() const { return elems.size(); }
  int subset_size(const T& elem) { return sets[indices.find(find(elem))->second].size; }

  T    find      (const T&);
  void merge     (const T&, const T&);
  bool connected (const T&, const T&);

  void add (const T&);


private:
  std::vector<detail::predecessor> sets;
  std::unordered_map<T, int> indices;
  std::vector<T> elems;
};



#include "disjoint_set.hpp"

#endif // DISJOINT_SET_H
