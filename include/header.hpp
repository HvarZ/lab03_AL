// Copyright 2018 Zakhar Ushakov <hvarzahar@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <atomic>
#include <mutex>
#include <iostream>
#include <stdexcept>
#include <utility>

using std::cout;
using std::endl;

class control_block {
 private:
  std::atomic_uint counter;
 public:
  control_block() noexcept;
  void increment() noexcept;
  void decrement() noexcept;
  auto get_counter() const noexcept -> size_t;
};

template <typename T>
class SharedPtr {
 private:
  T* shared_ptr;
  control_block* cb;

 public:
  SharedPtr() noexcept;
  explicit SharedPtr(T* ptr);
  SharedPtr(const SharedPtr& r) noexcept;
  SharedPtr(SharedPtr&& r) noexcept;
  ~SharedPtr();
  auto operator=(const SharedPtr& r) -> SharedPtr&;
  auto operator=(SharedPtr&& r) noexcept -> SharedPtr&;


  explicit operator bool() const noexcept;
  auto operator*() const noexcept -> T&;
  auto operator->() const noexcept -> T*;
  auto operator==(const SharedPtr& r) const -> bool;

  auto get() const -> T*;
  void reset() noexcept;
  void reset(T* ptr);
  void swap(SharedPtr& r);
  [[nodiscard]] auto use_count() const -> size_t;
};



control_block::control_block() noexcept  : counter(0) {}

void control_block::increment() noexcept {
  ++counter;
}

void control_block::decrement() noexcept {
  --counter;
}

auto control_block::get_counter() const noexcept -> size_t {
  return counter;
}

template <typename T>
SharedPtr<T>::SharedPtr() noexcept {
  shared_ptr = nullptr;
  cb = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr)  {
  shared_ptr = ptr;
  cb = new control_block;
  cb->increment();
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &r) noexcept {
  shared_ptr = r.shared_ptr;
  r.cb->increment();
  cb = r.cb;
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
    r.cb->increment();
    cb = r.cb;
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
auto SharedPtr<T>::operator*() const noexcept -> T & {
  return *shared_ptr;
}

template <typename T>
auto SharedPtr<T>::operator->() const noexcept -> T * {
  return shared_ptr;
}

template <typename T>
auto SharedPtr<T>::get() const -> T * {
  return shared_ptr;
}


template <typename T>
void SharedPtr<T>::reset() noexcept {
  this->~SharedPtr();
  shared_ptr = nullptr;
  cb = nullptr;
}

template <typename T>
void SharedPtr<T>::reset(T *ptr) {
  this->~SharedPtr();
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


#endif // INCLUDE_HEADER_HPP_
