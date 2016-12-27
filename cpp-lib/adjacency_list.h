#include <utility>
#include <vector>
using std::size_t;

/**
 * Weighted edge struct
 * Holds values for the destination node and the weight
 *
 * TODO: Use something other than int for weight?
 */
struct weighted {
  size_t d;
  int w;

  weighted(size_t dest, int weight) : d(dest), w(weight) {}
  int get_weight() const { return w; }
  size_t get_dest() const { return d; }
};

/**
 * Unweighted edge struct
 * Holds value for the destination node and returns a constant for the weight.
 * Essentially, this transforms an unweight graph to a weighted graph with
 * weights of 1
 */
struct unweighted {
  size_t d;

  unweighted(size_t dest, int weight) : d(dest) {}
  int get_weight() const { return 1; }
  size_t get_dest() const { return d; }
};

/**
 * Adjacenty List graph
 * Class to hold algorithms and structures for operations on a graph stored in
 * an adjacency list.
 *
 * Configurable to use weighted or unweighted edges.
 * Directed graphs only. TODO: Configure to swap between both types.
 */
template <class EdgeType = unweighted> class adjacency_list {

  std::vector<std::vector<EdgeType>> G;

public:
  explicit adjacency_list(size_t N) : G(N) {}

  /**
   * Get number of nodes in graph
   * @return Number of vertices in graph
   */
  size_t size() const { return G.size(); }

  /**
   * Add an edge to the graph
   * @param a      First node to connect
   * @param b      Second node to connect
   * @param weight Optional weight of edge
   */
  void add_edge(size_t a, size_t b, int weight = 1) {
    G[a].emplace_back(b, weight);
  }

  /**
   * Get the list of edges connected to the given node
   * @param a      Query node
   * @return All edges connected to query node
   */
  const std::vector<EdgeType> &neighbors(size_t a) const { return G[a]; }
};
