/**
 * Implementation of Heap Sort algorithm.
 *
 * If you ever need to write a working, efficient, non-specialized sorting
 * algorithm on a whiteboard in an hour, this is probably what you want to
 * write.
 */
#pragma once
#include <vector>

namespace detail {

template <class T>
void bubble_down(std::vector<T> &v, std::size_t i, std::size_t N) {
  auto child = 2 * i + 1;
  auto r_child = child + 1;
  if (child >= N)
    return;

  // Find largest child
  if (r_child < N && v[r_child] > v[child])
    std::swap(child, r_child);

  if (v[child] > v[i]) {
    std::swap(v[i], v[child]);
    bubble_down(v, child, N);
  }
}
}

template <class T> void heap_sort(std::vector<T> &v) {
  // Make heap
  for (std::size_t i = 1 + v.size() / 2; i-- > 0;)
    detail::bubble_down(v, i, v.size());

  // Pop continuously from the heap
  for (std::size_t i = v.size(); i-- > 0;) {
    std::swap(v[0], v[i]);
    detail::bubble_down(v, 0, i);
  }
}
