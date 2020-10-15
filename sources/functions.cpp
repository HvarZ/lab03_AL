#include <header.hpp>

std::mutex mutex;

control_block::control_block() noexcept  : counter(0){};

void control_block::increment() noexcept {
  std::lock_guard<std::mutex> lg(mutex);
  ++counter;
}

void control_block::decrement() noexcept {
  std::lock_guard<std::mutex> lg(mutex);
  --counter;
}

auto control_block::get_counter() const noexcept -> size_t {
  std::lock_guard<std::mutex> lg(mutex);
  return counter;
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
SharedPtr<T>::~SharedPtr<T>() {
  cb->decrement();
  if (cb->get_counter() == 0) {
    delete shared_ptr;
    delete cb;
  }
}


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
  return shared_ptr == r.shared_ptr;
}


template <typename T>
SharedPtr<T>::operator bool() const noexcept {
  return shared_ptr != nullptr;
}


template <typename T>
auto SharedPtr<T>::operator*() const -> T & {
  return *shared_ptr;
}

template <typename T>
auto SharedPtr<T>::operator->() const -> T * {
  return shared_ptr;
}

template <typename T>
auto SharedPtr<T>::get() const -> T * {
  return shared_ptr;
}


template <typename T>
void SharedPtr<T>::reset() noexcept {
  this->SharedPtr<T>::~SharedPtr();
  shared_ptr = nullptr;
  cb = nullptr;
}

template <typename T>
void SharedPtr<T>::reset(T *ptr) {
  this->SharedPtr<T>::~SharedPtr();
  shared_ptr = ptr;
  cb = new control_block;
  cb->increment();
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr<T> &r) {
  std::swap(shared_ptr, r.shared_ptr);
  std::swap(cb, r.cb);
}

template <typename T>
auto SharedPtr<T>::use_count() const -> size_t {
  return cb->get_counter();
}



