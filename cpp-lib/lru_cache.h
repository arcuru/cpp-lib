#include <list>
#include <unordered_map>
#include <utility>

/**
 * Least Recently Used Cache
 *
 * Stores key/value pairs, while keeping track of the least recently accessed
 * key for removal once the size is exceeded.
 */
template <class Key, class Value> class lru_cache {

  typedef Key key_type;
  typedef Value value_type;
  typedef std::list<key_type> list_type;
  typedef std::unordered_map<
      key_type, std::pair<value_type, typename list_type::iterator>>
      map_type; //!< Hash map for fast lookups

  list_type m_list;
  map_type m_map;
  size_t m_capacity;

  void pop_back() {
    auto it = --m_list.end();
    m_map.erase(*it);
    m_list.erase(it);
  }

public:
  explicit lru_cache(size_t n) : m_capacity(n) {}

  size_t size() const { return m_map.size(); }

  size_t capacity() const { return m_capacity; }

  bool empty() const { return m_map.empty(); }

  bool contains(const key_type &key) const {
    return m_map.find(key) != m_map.end();
  }

  void clear() {
    m_map.clear();
    m_list.clear();
  }

  value_type get(const key_type &key) {
    auto it = m_map.find(key);
    if (it == m_map.end()) {
      throw;
    }
    auto l_it = it->second.second;
    if (l_it != m_list.begin()) {
      m_list.erase(l_it);
      m_list.push_front(key);
      it->second = std::make_pair(it->second.first, m_list.begin());
    }
    return it->second.first;
  }

  void insert(const key_type &key, const value_type &value) {
    auto it = m_map.find(key);
    if (it == m_map.end()) {
      if (size() >= m_capacity) {
        pop_back();
      }
      m_list.push_front(key);
      m_map[key] = std::make_pair(value, m_list.begin());
    }
  }
};
