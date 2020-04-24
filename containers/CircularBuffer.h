//
// Created by Petr on 24.04.2020.
//

#ifndef UTILITIES_CIRCULARBUFFER_H
#define UTILITIES_CIRCULARBUFFER_H
#include <array>

template <typename T, std::size_t Size> class CircularBuffer {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using container_type = std::array<T, Size>;

  CircularBuffer() = default;
  CircularBuffer(const CircularBuffer &other) = default;
  CircularBuffer(CircularBuffer &&other) noexcept = default;
  CircularBuffer &operator=(const CircularBuffer &other) = default;
  CircularBuffer &operator=(CircularBuffer &&other) noexcept = default;

  template <bool isconst> class iter;
  using iterator = iter<false>;
  using const_iterator = iter<true>;

  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;
  iterator rbegin();
  const_iterator rbegin() const;
  const_iterator crbegin() const;
  iterator end();
  const_iterator end() const;
  const_iterator cend() const;
  iterator rend();
  const_iterator rend() const;
  const_iterator crend() const;

  reference front();
  reference top();
  reference back();
  const_reference front() const;
  const_reference top() const;
  const_reference back() const;
  void clear();

  void push_back(const value_type &item);
  void push(const value_type &item);
  template <typename... Args> void emplace_back(Args &&... args);
  template <typename... Args> void emplace(Args &&... args);

  void pop_front();
  void pop();

  size_type size();
  [[nodiscard]] constexpr size_type capacity() const;
  [[nodiscard]] size_type max_size() const;

  [[nodiscard]] bool empty() const;
  [[nodiscard]] bool full() const;

  reference operator[](size_type index);
  const_reference operator[](size_type index) const;
  reference at(size_type index);
  const_reference at(size_type index) const;

  void swap(CircularBuffer &other);

private:
  size_type head = 1;
  size_type tail = 0;
  size_type contentsSize = 0;
  container_type data{};
};

template <typename T, std::size_t Size> template <bool isconst> class CircularBuffer<T, Size>::iter {
  bool isSameDir(const iter &other) { return reverse == other.reverse; }

public:
  using value_type = CircularBuffer::value_type;
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = long long;
  using reference = typename std::conditional_t<isconst, T const &, T &>;
  using pointer = typename std::conditional_t<isconst, T const *, T *>;
  using container_pointer = typename std::conditional_t<isconst, std::array<T, Size> const *, std::array<T, Size> *>;

  iter() : bufferPtr(nullptr), offset(0), index(0), reverse(false) {} //
  iter(const iter &i) : bufferPtr(i.bufferPtr), offset(i.offset), index(i.index), reverse(i.reverse) {}

  explicit iter(iter<false> &&other)
      : bufferPtr(other.bufferPtr), offset(other.offset), index(other.index), reverse(other.reverse) {}

  reference operator*() {
    if (reverse) {
      return (*bufferPtr)[(bufferPtr->size() + offset - index) % (bufferPtr->size())];
    }
    return (*bufferPtr)[(offset + index) % (bufferPtr->size())];
  }
  reference operator[](size_type idx) {
    iter iter = *this;
    iter.index += idx;
    return *iter;
  }
  pointer operator->() { return &(operator*()); }

  iter &operator++() {
    ++index;
    return *this;
  };
  iter operator++(int) {
    iter iter = *this;
    ++index;
    return iter;
  }
  iter &operator--() {
    --index;
    return *this;
  }
  iter operator--(int) {
    iter iter = *this;
    --index;
    return iter;
  }
  friend iter operator+(iter lhs, int rhs) {
    lhs.index += rhs;
    return lhs;
  }
  friend iter operator+(int lhs, iter rhs) {
    rhs.index += lhs;
    return rhs;
  }
  iter &operator+=(int n) {
    index += n;
    return *this;
  }
  friend iter operator-(iter lhs, int rhs) {
    lhs.index -= rhs;
    return lhs;
  }
  friend difference_type operator-(const iter &lhs, const iter &rhs) {
    lhs.index -= rhs;
    return lhs.index - rhs.index;
  }
  iter &operator-=(int n) {
    index -= n;
    return *this;
  }
  bool operator==(const iter &other) {
    if (isSameDir(other)) {
      return (index + offset == other.index + other.offset);
    }
    return false;
  }
  bool operator!=(const iter &other) {
    if (isSameDir(other)) {
      return !this->operator==(other);
    }
    return true;
  }
  bool operator<(const iter &other) {
    if (isSameDir(other)) {
      return (index + offset < other.index + other.offset);
    }
    return false;
  }
  bool operator<=(const iter &other) {
    if (isSameDir(other)) {
      return (index + offset <= other.index + other.offset);
    }
    return false;
  }
  bool operator>(const iter &other) {
    if (isSameDir(other)) {
      return !this->operator<=(other);
    }
    return false;
  }
  bool operator>=(const iter &other) {
    if (isSameDir(other)) {
      return !this->operator<(other);
    }
    return false;
  }

private:
  container_pointer bufferPtr;
  size_type offset;
  size_type index;
  bool reverse;
  friend class CircularBuffer;
};

#include "CircularBuffer.tpp"

#endif // UTILITIES_CIRCULARBUFFER_H
