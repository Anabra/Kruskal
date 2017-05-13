template <class T, class ToInt, class NthDigit>
void counting_sort(std::vector<T>& vec, int base, ToInt f, NthDigit nth)
{
  std::vector<int> digits;

  digits.reserve(base);
  for (int i = 0; i < base; i++)
    digits[i] = 0;

  for(auto cit = vec.cbegin(); cit != vec.cend(); cit++)
    digits[nth(f(*cit))]++;

  // quasi-renaming digits
  std::vector<int> sum_digits = std::move(digits);

  for (int i = 1; i < base; i++)
    sum_digits[i] += sum_digits[i-1];

  std::vector<int> places;
  places.resize(vec.size());

  for (int i = vec.size()-1; i >= 0; i--)
    places[i] = --sum_digits[nth(f(vec[i]))];


  for (unsigned int i = 0; i < vec.size(); i++)
  {
    int from = i;
    T cur = vec[from];

    int to = places[from];
    T next = vec[to];

    // -1 means, that we already plaved that elemnt into the right place
    while(to != -1)
    {
      places[from] = -1;

      vec[to] = cur;
      cur = next;
      from = to;
      to = places[from];
      next = vec[to];
    }
  }

}

template<class ForwardIt, class Compare>
ForwardIt maximum(ForwardIt first, ForwardIt last, Compare cmp)
{
    if (first == last)
    {
        return last;
    }
    ForwardIt largest = first;
    ++first;
    for (; first != last; ++first)
    {
      if (cmp(*largest, *first))
          largest = first;
    }
    return largest;
}


// Constraints:
// T must be copy-constructible
// ToInt :: const T& -> int (const)
template <class T, class ToInt>
void radix_sort(std::vector<T>& vec, ToInt f)
{
  int n = (int)ceil(log10(
    f(*maximum(vec.cbegin(),
               vec.cend(),
               [&f](const T& lhs, const T& rhs) {return f(lhs) < f(rhs);} )))
             );

  for (int k = 1; k <= n; k++)
  {
    counting_sort(vec, 10, f, nth_digit(k));
  }
}
