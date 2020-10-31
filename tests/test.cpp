// Copyright 2018 Zakhar Ushakov <hvarzahar@gmail.com>

#include <header.hpp>
#include <gtest/gtest.h>


/*TEST(Constructor, empty) {
    SharedPtr<int> sh;
    EXPECT_EQ(sh.get(), nullptr);
}*/

TEST(Constructor, raw) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    EXPECT_EQ(sh.get(), iter);
}

TEST(Constructor, copy) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    const SharedPtr<int>& sh1(sh);
    EXPECT_EQ(sh1.get(), iter);
}

/*TEST(Constructor, move) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    SharedPtr<int> sh1(sh);
}*/

TEST(Operator, copy) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    const SharedPtr<int>& sh1 = sh;
    EXPECT_EQ(sh1.get(), iter);
}

TEST(Operator, Bool) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    EXPECT_EQ(sh.operator bool(), true);
}

TEST(Operator, dereferencing) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    EXPECT_EQ(*sh, 5);
}

TEST(Operator, pointer) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    EXPECT_EQ(sh.operator->(), iter);
}

TEST(Operator, equality) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    const SharedPtr<int>& sh2(sh);
    EXPECT_EQ(sh == sh2, true);
}

TEST(Function, get) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    EXPECT_EQ(sh.get(), iter);
}

TEST(Function, swap) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    int* iter2 = new int (6);
    SharedPtr<int> sh2(iter2);
    sh.swap(sh2);
    EXPECT_EQ(sh.get(), iter2);
}

TEST(Function, use_count) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    [[maybe_unused]] SharedPtr<int> sh2(sh);
    EXPECT_EQ(sh.use_count(), 2);
}

