#include <stdexcept>

template <class T>
disjoint_set<T>::disjoint_set(std::initializer_list<T> elements)
{
  for(auto it = elements.begin(); it != elements.end(); it++)
    add(*it);
}


template <class T>
T disjoint_set<T>::find(const T& elem)
{
  int ind  = indices.find(elem)->second;
  int root = sets[ind].pred;
  std::vector<int> shrinkables;

  while (ind != root)
  {
    shrinkables.push_back(ind);
    ind = root;
    root = sets[root].pred;
  }

  for(unsigned int i = 0; i < shrinkables.size(); i++)
  {
    sets[shrinkables[i]].pred = root;
  }

  return elems[ind];
}

template <class T>
void disjoint_set<T>::merge(const T& lhs, const T& rhs)
{
  int lhs_root = indices.find(find(lhs))->second;
  int rhs_root = indices.find(find(rhs))->second;

  if (lhs_root == rhs_root) return;

  if      (sets[lhs_root].size < sets[rhs_root].size)
    sets[lhs_root].pred = rhs_root;
  else if (sets[lhs_root].size > sets[rhs_root].size)
    sets[rhs_root].pred = lhs_root;
  else
  {
    sets[rhs_root].pred = lhs_root;
    sets[lhs_root].size++;
  }
}

std::ostream& operator<< (std::ostream& os, const detail::predecessor& p)
{
  return os << "(" << p.pred << " " << p.size << ") ";
}

template <class T>
bool disjoint_set<T>::connected(const T& lhs, const T& rhs)
{
  return find(lhs) == find(rhs);
}

template <class T>
void disjoint_set<T>::add(const T& elem)
{
  int n = size();
  sets.push_back({n,0});
  elems.push_back(elem);
  indices.insert({elem,n});
}




















//
