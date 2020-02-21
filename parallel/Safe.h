//
// Created by Petr on 21.02.2020.
//

#ifndef UTILITIES_SAFE_H
#define UTILITIES_SAFE_H

template <typename T, typename Mutex = std::mutex> class Safe final {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using const_pointer = const T *;

  enum class AccessType { Full, ReadOnly };

  template <typename U = T, AccessType = AccessType::Full> class Access;
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

  Access<T, AccessType::Full> get() { return Access<T, AccessType::Full>{value, mtx}; }
  Access<T, AccessType::ReadOnly> get() const { return Access<T, AccessType::ReadOnly>{value, mtx}; }

  Access<T, AccessType::Full> writeAccess() { return Access<T, AccessType::Full>{value, mtx}; }
  Access<T, AccessType::ReadOnly> readOnlyAccess() const { return Access<T, AccessType::ReadOnly>{value, mtx}; }

  Access<T, AccessType::Full> operator->() { return get(); }
  Access<T, AccessType::ReadOnly> operator->() const { return get(); }

  reference unsafe() { return value; }
  const_reference unsafe() const { return value; }

private:
  mutable Mutex mtx;
  value_type value;
};

template <typename T, typename Mutex> template <typename U, typename Safe<T, Mutex>::AccessType AccessPolicy>
class Safe<T, Mutex>::Access {
  using reference_type = std::conditional_t<AccessPolicy == Safe<T>::AccessType::Full, reference, const_reference>;
  using pointer_type = std::conditional_t<AccessPolicy == Safe<T>::AccessType::Full, pointer, const_pointer>;

public:
  Access(reference_type value, std::mutex &mtx) : value(value), lck(mtx) {}
  Access(const Access &other) = delete;
  Access(Access &&other) = delete;
  Access &operator=(const Access &other) = delete;
  Access &operator=(Access &&other) = delete;

  reference_type operator*() noexcept { return value; }
  const_reference operator*() const noexcept { return value; }
  pointer_type operator->() noexcept { return &value; }
  const_pointer operator->() const noexcept { return &value; }

private:
  reference_type value;
  std::unique_lock<std::mutex> lck;
};

#endif // UTILITIES_SAFE_H
