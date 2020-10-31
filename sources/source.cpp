// Copyright 2018 Your Name <your_email>

#include <header.hpp>

int main () {
  int* iter = new int (5);
  SharedPtr<int> sh(iter);
  return 0;
}