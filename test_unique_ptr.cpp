#include <gtest/gtest.h>

#include "unique_ptr.hpp"

TEST(unique_ptr, default_ctor) {
    unique_ptr<int> uptr;
    EXPECT_EQ(uptr.get(), nullptr);
}

TEST(unique_ptr, ctor_1) {
    unique_ptr<int> uptr_empty(nullptr);
    EXPECT_EQ(uptr_empty.get(), nullptr);

    unique_ptr<int> uptr(new int(42));
    EXPECT_EQ(*uptr.get(), 42);
}

TEST(unique_ptr, assign_op) {
    unique_ptr<int> uptr_initially_empty;
    uptr_initially_empty = new int(42);
    EXPECT_EQ(*uptr_initially_empty.get(), 42);

    unique_ptr<int> uptr_initially_non_empty(new int(12));
    uptr_initially_non_empty = new int(24);
    EXPECT_EQ(*uptr_initially_non_empty.get(), 24);
}

TEST(unique_ptr, move_ctor) {
    unique_ptr<int> uptr1(new int(42));
    unique_ptr<int> uptr2(std::move(uptr1));
    EXPECT_EQ(uptr1.get(), nullptr);
    EXPECT_EQ(*uptr2.get(), 42);
}
