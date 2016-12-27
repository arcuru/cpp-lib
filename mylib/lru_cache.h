
/**
 * Least Recently Used Cache
 *
 * Stores key/value pairs, while keeping track of the least recently accessed
 * key for removal once the size is exceeded.
 */
template <class key_type, class value_type> class lru_cache {

  struct ll_node {
    ll_node *next;
    ll_node *prev;
    key_type key;
    value_type val;
  };

  std::unordered_map<key_type, ll_node *> hmap; //!< Hash map for fast lookups
  ll_node *head(nullptr);
  ll_node *tail(nullptr);
  std::size_t max_size;

  void touch(ll_node *node) {
    assert(node != nullptr);

    if (head == node)
      return;

    node->prev->next = node->next;

    if (tail == node) {
      tail = node->prev;
      tail->next = nullptr;
    } else {
      node->next->prev = node->prev;
    }

    node->next = head;
    node->prev = nullptr;
    head = node;
  }

public:
  explicit lru_cache(std::size_t n) : max_size(n) {}

  value_type &get(const key_type &key) {
    auto it = hmap.find(key);
    if (it == hmap.end()) {
      insert(key); // TODO: this is inefficient, and maybe not what you wnat
      it = hmap.find(key);
    }
    touch(it->second);
    return it->second->val;
  }

  void insert(const key_type &key) {
    auto &it = hmap[key];
    if (it == nullptr) {
      it = new ll_node();
    }
    it->next = head;
    it->prev = nullptr;
    it->key = key;
    if (head != nullptr)
      head->prev = it;
    head = it;
    if (tail == nullptr)
      tail = it;
  }

  void pop_back() {
    if (tail == nullptr)
      return;
    hmap.erase(hmap.find(tail->key));
    if (head == tail) {
        head = nullptr;
        delete tail;
        tail = nullptr;
        return;
    }
    auto new_tail = tail->prev;
    if (tail->prev != nullptr)
        tail->prev->next = nullptr;
    delete tail;
    tail = new_tail;
  }
};
