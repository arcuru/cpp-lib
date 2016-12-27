#include <algorithm>
#include <utility>
#include <vector>

// This is just a wrapper for std::vector with all the access
// methods of set. Doing sets this way provides the following:
//      Should be faster for small sets
//      Faster lookups than 'set', but not 'unordered_set'
//      Very fast iteration
//      Slower inserts

// This is a re-write (essentially) of boost::flat_set
// ****I'm not aware of any reason to use this instead of boost::flat_set

template <class T> class flat_set {
private:
  std::vector<T> data_; //!< Data storage for the set

public:
  // Types
  typedef std::size_t size_type;
  typedef T value_type;
  typedef typename std::vector<T>::iterator iterator;
  typedef typename std::vector<T>::const_iterator const_iterator;

  // Helper
  friend void swap(flat_set &first, flat_set &second) {
    using std::swap;
    swap(first.data_, second.data_);
  }

  // Constructors
  flat_set() : data_() {}

  flat_set(const flat_set &x) : data_(x.data_) {}

  flat_set(flat_set &&x) : flat_set() { swap(*this, x); }

  // Iterators
  //  These functions return iterators into the set
  //  *Just passthroughs to the vector

  iterator begin() noexcept { return data_.begin(); }
  const_iterator begin() const noexcept { return data_.begin(); }
  const_iterator cbegin() const noexcept { return data_.cbegin(); }
  iterator end() noexcept { return data_.end(); }
  const_iterator end() const noexcept { return data_.end(); }
  const_iterator cend() const noexcept { return data_.cend(); }

  // Capacity Checks
  bool empty() const noexcept { return data_.empty(); }
  size_type size() const noexcept { return data_.size(); }
  size_type max_size() const noexcept { return data_.max_size(); }

  // Modifiers

  void clear() noexcept { data_.clear(); }

  std::pair<iterator, bool> insert(const value_type &val) {
    auto it = find(val);
    if (it == data_.end() || *it != val) {
      data_.insert(it, val);
      return {it, true};
    }
    return {it, false};
  }

  size_type erase(const value_type &val) {
    auto it = find(val);
    if (it == data_.end())
      return 0;
    data_.erase(it);
    return 1;
  }

  void swap(flat_set &x) { swap(*this, x); }

  // Operations

  iterator find(const value_type &val) {
    auto it = std::lower_bound(data_.begin(), data_.end(), val);
    if (it == data_.end() || *it == val)
      return it;
    return data_.end();
  }

  const_iterator find(const value_type &val) const {
    auto it = std::lower_bound(data_.begin(), data_.end(), val);
    if (it == data_.end() || *it == val)
      return it;
    return data_.end();
  }

  size_type count(const value_type &val) const {
    return find(val) != data_.cend();
  }

  iterator lower_bound(const value_type &val) {
    return std::lower_bound(data_.begin(), data_.end(), val);
  }

  const_iterator lower_bound(const value_type &val) const {
    return std::lower_bound(data_.cbegin(), data_.cend(), val);
  }

  iterator upper_bound(const value_type &val) {
    return std::upper_bound(data_.begin(), data_.end(), val);
  }

  const_iterator upper_bound(const value_type &val) const {
    return std::upper_bound(data_.cbegin(), data_.cend(), val);
  }

  std::pair<iterator, iterator> equal_range(const value_type &val) {
    return std::equal_range(data_.begin(), data_.end(), val);
  }

  std::pair<const_iterator, const_iterator>
  equal_range(const value_type &val) const {
    return std::equal_range(data_.cbegin(), data_.cend(), val);
  }
};
