// Copyright 2018 Your Name <your_email>

#include <header.hpp>

int main () {
  int* it = new int [10];
  SharedPtr<int> sh = SharedPtr<int>(it);

  cout << endl;

  return 0;
}