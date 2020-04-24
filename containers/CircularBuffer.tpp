

template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::iterator CircularBuffer<T, Size>::begin() {
  iterator iter;
  iter.bufferPtr = &data;
  iter.offset = head;
  iter.index = 0;
  iter.reverse = false;
  return iter;
}

template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::const_iterator CircularBuffer<T, Size>::begin() const {
  return begin();
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::const_iterator CircularBuffer<T, Size>::cbegin() const {
  return begin();
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::iterator CircularBuffer<T, Size>::rbegin() {
  iterator iter;
  iter.bufferPtr = &data;
  iter.offset = head;
  iter.index = 0;
  iter.reverse = true;
  return iter;
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::const_iterator CircularBuffer<T, Size>::rbegin() const {
  return rbegin();
}
template <typename T, std::size_t Size>
typename CircularBuffer<T, Size>::const_iterator CircularBuffer<T, Size>::crbegin() const {
  return rbegin();
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::iterator CircularBuffer<T, Size>::end() {
  iterator iter;
  iter.bufferPtr = &data;
  iter.offset = head;
  iter.index = contentsSize;
  iter.reverse = false;
  return iter;
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::const_iterator CircularBuffer<T, Size>::end() const {
  return end();
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::const_iterator CircularBuffer<T, Size>::cend() const {
  return end();
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::iterator CircularBuffer<T, Size>::rend() {
  iterator iter;
  iter.bufferPtr = &data;
  iter.offset = tail;
  iter.index = contentsSize;
  iter.reverse = true;
  return iter;
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::const_iterator CircularBuffer<T, Size>::rend() const {
  return rend();
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::const_iterator CircularBuffer<T, Size>::crend() const {
  return rend();
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::reference CircularBuffer<T, Size>::front() {
  return data[head];
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::reference CircularBuffer<T, Size>::top() {
  return front();
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::reference CircularBuffer<T, Size>::back() {
  return data[tail];
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::const_reference CircularBuffer<T, Size>::front() const {
  return data[head];
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::const_reference CircularBuffer<T, Size>::top() const {
  return front();
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::const_reference CircularBuffer<T, Size>::back() const {
  return data[tail];
}
template <typename T, std::size_t Size> void CircularBuffer<T, Size>::clear() {
  head = 1;
  tail = 0;
  contentsSize = 0;
}
template <typename T, std::size_t Size> void CircularBuffer<T, Size>::push_back(const value_type &item) {
  ++tail;
  ++contentsSize;
  if (tail == Size) {
    tail = 0;
  }
  if (contentsSize > Size) {
    pop_front();
  }
  data[tail] = item;
}
template <typename T, std::size_t Size> void CircularBuffer<T, Size>::push(const value_type &item) { push_back(item); }
template <typename T, std::size_t Size> template <typename... Args> void CircularBuffer<T, Size>::emplace_back(Args &&... args) {
  ++tail;
  ++contentsSize;
  if (tail == Size) {
    tail = 0;
  }
  if (contentsSize > Size) {
    pop_front();
  }
  data[tail] = T{std::forward<Args>(args)...};
}
template <typename T, std::size_t Size> template <typename... Args> void CircularBuffer<T, Size>::emplace(Args &&... args) {
  emplace_back(std::forward<Args>(args)...);
}
template <typename T, std::size_t Size> void CircularBuffer<T, Size>::pop_front() {
  if (contentsSize == 0) {
    return;
  }
  ++head;
  --contentsSize;
  if (head == Size) {
    head = 0;
  }
}
template <typename T, std::size_t Size> void CircularBuffer<T, Size>::pop() { pop_front(); }
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::size_type CircularBuffer<T, Size>::size() {
  return contentsSize;
}
template <typename T, std::size_t Size>
constexpr typename CircularBuffer<T, Size>::CircularBuffer::size_type CircularBuffer<T, Size>::capacity() const {
  return Size;
}
template <typename T, std::size_t Size> typename CircularBuffer<T, Size>::size_type CircularBuffer<T, Size>::max_size() const {
  return size_type(-1) / sizeof(value_type);
}
template <typename T, std::size_t Size> bool CircularBuffer<T, Size>::empty() const { return contentsSize == 0; }
template <typename T, std::size_t Size> bool CircularBuffer<T, Size>::full() const { return contentsSize == Size; }
template <typename T, std::size_t Size>
typename CircularBuffer<T, Size>::reference CircularBuffer<T, Size>::operator[](CircularBuffer::size_type index) {
  index += head;
  index %= Size;
  return data[index];
}
template <typename T, std::size_t Size>
typename CircularBuffer<T, Size>::const_reference CircularBuffer<T, Size>::operator[](CircularBuffer::size_type index) const {
  index += head;
  index %= Size;
  return data[index];
}
template <typename T, std::size_t Size>
typename CircularBuffer<T, Size>::reference CircularBuffer<T, Size>::at(CircularBuffer::size_type index) {
  if (index < contentsSize) {
    return operator[](index);
  }
  throw std::out_of_range("CircularBuffer index out of range");
}
template <typename T, std::size_t Size>
typename CircularBuffer<T, Size>::const_reference CircularBuffer<T, Size>::at(CircularBuffer::size_type index) const {
  if (index < contentsSize) {
    return operator[](index);
  }
  throw std::out_of_range("CircularBuffer index out of range");
}
template <typename T, std::size_t Size> void CircularBuffer<T, Size>::swap(CircularBuffer &other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(contentsSize, other.contentsSize);
  std::swap(data, other.data);
}
