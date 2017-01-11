// Clone of std::priority_queue

#include <functional>
#include <vector>

template <class T, class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type>>
class heap {
  // Container must provide front(), push_back(), pop_back()
  Container data_;
  Compare cmp_ = Compare();

public:
  // Types
  typedef T value_type;
  typedef typename Container::size_type size_type;
  typedef typename Container::iterator iterator;
  typedef typename Container::const_iterator const_iterator;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;

  const_reference top() const { return data_.front(); }

  bool empty() const { return data_.empty(); }

  size_type size() const { return data_.size(); }

  void push(const value_type &value) {
    data_.push_back(value);
    swim();
  }

  void push(value_type &&value) {
    data_.push_back(std::move(value));
    swim();
  }

  template <class... Args> void emplace(Args &&... args) {
    data_.emplace_back(std::forward<Args>(args)...);
    swim();
  }

  void pop() {
    using std::swap;
    swap(data_.front(), data_.back());
    data_.pop_back();
    sink();
  }

  friend void swap(heap &first, heap &second) {
    using std::swap;
    swap(first.data_, second.data_);
    swap(first.cmp_, second.cmp_);
  }

  void swap(heap &other) { swap(*this, other); }

private:
  void swim() {
    // Swim up the last element
    using std::swap;
    size_t idx = data_.size() - 1;
    while (idx != 0) {
      size_t parent = (idx - 1) / 2;
      if (!cmp_(data_[parent], data_[idx])) {
        break;
      }
      swap(data_[parent], data_[idx]);
      idx = parent;
    }
  }

  void sink() {
    // Sink the top element
    using std::swap;
    size_t idx = 0;
    while (2 * idx < data_.size()) {
      size_t child = (2 * idx) + 1;
      if (child >= data_.size()) {
        break;
      }
      if (child + 1 < data_.size() && cmp_(data_[child], data_[child + 1])) {
        ++child;
      }
      if (!cmp_(data_[idx], data_[child])) {
        break;
      }
      swap(data_[idx], data_[child]);
      idx = child;
    }
  }
};
