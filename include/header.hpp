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
  T* _ptr;
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



control_block::control_block() noexcept  : counter(1) {}

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
SharedPtr<T>::SharedPtr() noexcept : _ptr(nullptr), cb(nullptr) {}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) : _ptr(ptr), cb(new control_block){}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &r) noexcept : _ptr(r._ptr),
                                                          cb(r.cb){
  if (cb) {
    cb->increment();
  }
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &&r) noexcept : _ptr(r._ptr), cb(r.cb) {
  r.cb = nullptr;
  r.cb = nullptr;
}

template <typename T>
SharedPtr<T>::~SharedPtr<T>() {
  if (cb) {
    cb->decrement();
    if (cb->get_counter() == 0) {
      delete _ptr;
      delete cb;
    }
  }
}


template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr<T> &r) -> SharedPtr<T> & {
  if (this != &r) {
      SharedPtr<T>(r).swap(*this);
  }
  return *this;
}


template <typename T>
auto SharedPtr<T>::operator=(SharedPtr<T> &&r) noexcept -> SharedPtr<T> & {
  if (this != &r) {
    SharedPtr<T>(r).swap(*this);
  }
  return *this;
}

template <typename T>
auto SharedPtr<T>::operator==(const SharedPtr<T> &r) const -> bool {
  return _ptr == r._ptr;
}


template <typename T>
SharedPtr<T>::operator bool() const noexcept {
  return _ptr != nullptr;
}


template <typename T>
auto SharedPtr<T>::operator*() const noexcept -> T & {
  return *_ptr;
}

template <typename T>
auto SharedPtr<T>::operator->() const noexcept -> T * {
  return _ptr;
}

template <typename T>
auto SharedPtr<T>::get() const -> T * {
  return _ptr;
}


template <typename T>
void SharedPtr<T>::reset() noexcept {
  SharedPtr<T> sh;
  this->swap(sh);
}

template <typename T>
void SharedPtr<T>::reset(T *ptr) {
  SharedPtr<T> sh(ptr);
  this->swap(sh);
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr<T> &r) {
  std::swap(_ptr, r._ptr);
  std::swap(cb, r.cb);
}

template <typename T>
auto SharedPtr<T>::use_count() const -> size_t {
  return cb ? cb->get_counter() : 0;
}

#endif // INCLUDE_HEADER_HPP_
