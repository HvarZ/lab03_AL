// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <atomic>
#include <mutex>
#include <iostream>

std::mutex mutex;
using std::cout;
using std::endl;

struct control_block {
  std::atomic_uint counter;
  void increment() noexcept;
  void decrement() noexcept;
};

template <typename T>
class SharedPtr {
 private:
  T* shared_ptr;
  control_block* cb;

 public:
  explicit SharedPtr() noexcept;
  explicit SharedPtr(T* ptr) noexcept;
  SharedPtr(const SharedPtr& r) noexcept;
  SharedPtr(SharedPtr&& r) noexcept;
  ~SharedPtr();
  auto operator=(const SharedPtr& r) -> SharedPtr&;
  auto operator=(SharedPtr&& r) noexcept -> SharedPtr&;

  // проверяет, указывает ли указатель на объект
  explicit operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;
  auto operator==(const SharedPtr& r) const -> bool;

  auto get() -> T*;
  void reset();
  void reset(T* ptr);
  void swap(SharedPtr& r);
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
  [[nodiscard]] auto use_count() const -> size_t;
};


#endif // INCLUDE_HEADER_HPP_
