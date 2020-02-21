//
// Created by Petr on 21.02.2020.
//

#ifndef UTILITIES_SAFE_H
#define UTILITIES_SAFE_H

template <typename T> class Safe final {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using const_pointer = const T *;

  class Access;
  template <typename... Args> explicit Safe(Args... args) : value(std::forward<Args...>(args)...) {}
  Safe(const Safe &other) {
    value = other.value;
    mtx = std::mutex{};
  }
  Safe &operator=(const Safe &other) {
    if (this == &other) {
      return *this;
    }
    value = other.value;
    mtx = std::mutex{};
    return *this;
  }
  Safe(Safe &&other) = delete;
  Safe &operator=(Safe &&other) = delete;

  Access get() { return Access{value, mtx}; }
  const Access get() const { return Access{value, mtx}; }

  Access operator->() { return get(); }
  const Access operator->() const { return get(); }

private:
  std::mutex mtx;
  value_type value;
};

template <typename T> class Safe<T>::Access {
public:
  Access(T &value, std::mutex &mtx) : value(value), lck(mtx) {}
  Access(const Access &other) = delete;
  Access(Access &&other) = delete;
  Access &operator=(const Access &other) = delete;
  Access &operator=(Access &&other) = delete;

  Access &operator=(const T &other) {
    value = other;
    return *this;
  }
  operator reference() { return value; }
  operator const_reference() const { return value; }

  reference operator*() noexcept { return value; }
  const_reference operator*() const noexcept { return value; }
  pointer operator->() noexcept { return &value; }
  const_pointer operator->() const noexcept { return &value; }

private:
  reference value;
  std::unique_lock<std::mutex> lck;
};

#endif // UTILITIES_SAFE_H
