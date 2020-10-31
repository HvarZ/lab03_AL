// Copyright 2020 Zakhar Ushakov <hvarzahar@gmail.com>

#include <header.hpp>

int main() {
  int* iter = new int (5);
  SharedPtr<int> sh(iter);
  [[maybe_unused]] const SharedPtr<int>& sh2(sh);

  return 0;
}
