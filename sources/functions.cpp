#include <header.hpp>


void control_block::decrement() noexcept {
  std::lock_guard<std::mutex> lg(mutex);
  ++counter;
}

void control_block::increment() noexcept {
  std::lock_guard<std::mutex> lg(mutex);
  --counter;
}

template <typename T>
SharedPtr<T>::SharedPtr() noexcept {
  shared_ptr = nullptr;
  cb = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) noexcept {
  shared_ptr = ptr;
  cb = new control_block;
  cb->increment();
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &r) noexcept {
  shared_ptr = r.shared_ptr;
  cb = r.cb;
  cb->increment();
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &&r) noexcept {
  shared_ptr = std::move(r.shared_ptr);
  cb = std::move(r.cb);
}

template <typename T>
SharedPtr<T>::~SharedPtr<T>() = default;


template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr<T> &r) -> SharedPtr<T> & {
  if (this != r) {
    shared_ptr = r.shared_ptr;
    cb = r.cb;
    cb->increment();
  }
  return *this;
}

template <typename T>
auto SharedPtr<T>::operator=(SharedPtr<T> &&r) noexcept -> SharedPtr<T> & {
  shared_ptr = std::move(r.shared_ptr);
  cb = std::move(r.cb);
  return *this;
}

template <typename T>
auto SharedPtr<T>::operator==(const SharedPtr<T> &r) const -> bool {
  return shared_ptr == r.shared_ptr && cb == r.cb;
}


//template <typename T>
//SharedPtr<T>::
