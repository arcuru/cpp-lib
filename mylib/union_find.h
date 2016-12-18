#include <numeric>
#include <vector>

/**
 * Union Find data structure
 *
 * Generic implementation of the Weighted Quick Union Find data structure
 */
class union_find {
  typedef std::size_t size_t;

  std::vector<size_t> v;  //!< Root pointers
  std::vector<size_t> sz; //!< Size of rooted tree

  /**
   * Find root of set for the given element. Non-const so it squashes tree for
   * faster future lookups.
   * @param  a Element to search for
   * @return   Root ID associated with input Element
   */
  size_t root(size_t a) {
    if (v[a] != a)
      v[a] = root(v[a]);
    return v[a];
  }

public:
  explicit union_find(size_t n) : v(n), sz(n, 1) {
    std::iota(v.begin(), v.end(), size_t(0));
  }

  /**
   * Connect two elements. Connects the smaller tree under the bigger for a max
   * height of logN.
   * @param a Element 1
   * @param b Element 2
   */
  void unite(size_t a, size_t b) {
    const auto rootA = root(a);
    const auto rootB = root(b);
    if (rootA == rootB)
      return;
    if (sz[rootA] > sz[rootB]) {
      v[rootB] = rootA;
      sz[rootA] += sz[rootB];
    } else {
      v[rootA] = rootB;
      sz[rootB] += sz[rootA];
    }
  }

  /**
   * Check if two elements are in the same set
   * @param  a Element 1
   * @param  b Element 2
   * @return   True if elements are connected
   */
  bool find(size_t a, size_t b) { return root(a) == root(b); }

  /**
   * Get number of elements.
   * @return Number of elements in data structure
   */
  size_t size() const noexcept { return v.size(); }
};
