// Copyright 2018 Zakhar Ushakov <hvarzahar@gmail.com>

#include <header.hpp>
#include <gtest/gtest.h>


TEST(constructor, raw) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    EXPECT_EQ(sh.get(), iter);
}

TEST(constructor, copy) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    SharedPtr<int> sh1(sh);
    EXPECT_EQ(sh1.get(), iter);
    EXPECT_EQ(sh.use_count(), 2);
}

TEST(constructor, move) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    SharedPtr<int> sh1(std::move(sh));
    EXPECT_EQ(sh1.get(), iter);
}

TEST(oper, copy) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    SharedPtr<int> sh1 = sh;
    EXPECT_EQ(sh1.get(), iter);
}

TEST(oper, move) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    SharedPtr<int> sh1 = std::move(sh);
    EXPECT_EQ(sh1.get(), iter);
}

TEST(oper, Bool) {
    SharedPtr<int> sh2;
    SharedPtr<int> sh(new int (5));
    EXPECT_EQ(sh.operator bool(), true);
    EXPECT_EQ(sh2.operator bool(), false);
}

TEST(oper, dereferencing) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    EXPECT_EQ(*sh, 5);
}

TEST(oper, pointer) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    EXPECT_EQ(sh.operator->(), iter);
}

TEST(oper, equality) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    const SharedPtr<int>& sh2(sh);
    EXPECT_EQ(sh == sh2, true);
}

TEST(function, get) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    EXPECT_EQ(sh.get(), iter);
}

TEST(function, swap) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    int* iter2 = new int (6);
    SharedPtr<int> sh2(iter2);
    sh.swap(sh2);
    EXPECT_EQ(sh.get(), iter2);
}

TEST(function, reset) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    sh.reset();
    EXPECT_EQ(sh.get(), nullptr);
}

TEST(function, reset_it) {
    int* iter = new int (5);
    int* iter2 = new int (6);
    SharedPtr<int> sh(iter);
    sh.reset(iter2);
    EXPECT_EQ(sh.get(), iter2);
}

TEST(function, use_count) {
    int* iter = new int (5);
    SharedPtr<int> sh(iter);
    [[maybe_unused]] SharedPtr<int> sh2(sh);
    EXPECT_EQ(sh.use_count(), 2);
}

TEST(control_block, constructor) {
    control_block block;
    EXPECT_EQ(block.get_counter(), 0);
}

TEST(control_block, increment) {
    control_block block;
    block.increment();
    EXPECT_EQ(block.get_counter(), 1);
}

TEST(control_block, decrement) {
    control_block block;
    block.increment();
    block.decrement();
    EXPECT_EQ(block.get_counter(), 0);
}
