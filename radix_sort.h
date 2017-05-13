#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include <vector>
#include <cmath>

struct nth_digit
{
public:
  nth_digit(int n) : n(n) {}

  int operator()(int k) const
  {
    return ((k % (int)std::pow(10,n)) - (k % (int)std::pow(10,n-1))) / (int)pow(10,n-1);
  }

private:
  int n;
};


template <class T, class ToInt, class NthDigit>
void counting_sort(std::vector<T>& vec, int base, ToInt f, NthDigit nth);

template <class T, class ToInt>
void radix_sort(std::vector<T>& vec, ToInt f);


#include "radix_sort.hpp"


#endif // RADIX_SORT_H
