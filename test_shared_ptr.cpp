#include <gtest/gtest.h>

#include "shared_ptr.hpp"

namespace {
  bool destruction_happened = false;

  class destruction_observer {
  public:
    ~destruction_observer() {
      destruction_happened = true;
    }
  };
}

TEST(shared_ptr, ctor_default) {
  shared_ptr<char> ptr;

  EXPECT_EQ(ptr.get(), nullptr);
  EXPECT_EQ(ptr.ref_count(), 0);
}

TEST(shared_ptr, ctor_ptr) {
  char* c = new char;
  *c = 42;

  shared_ptr<char> ptr(c);

  EXPECT_EQ(ptr.get(), c);
  EXPECT_EQ(ptr.ref_count(), 1);
}

TEST(shared_ptr, dtor) {
  destruction_happened = false;
  destruction_observer* h = new destruction_observer;

  {
    shared_ptr<destruction_observer> ptr(h);
    EXPECT_EQ(ptr.get(), h);
  }

  EXPECT_TRUE(destruction_happened);
}

TEST(shared_ptr, copy_ctor) {
  destruction_happened = false;
  destruction_observer* h = new destruction_observer;

  auto* p_ptr1 = new shared_ptr<destruction_observer>(h);
  auto* p_ptr2 = new shared_ptr<destruction_observer>(*p_ptr1);

  delete p_ptr1;
  EXPECT_FALSE(destruction_happened);

  delete p_ptr2;
  EXPECT_TRUE(destruction_happened);
}

TEST(shared_ptr, empty) {
  shared_ptr<char> ptr1;
  EXPECT_TRUE(ptr1.empty());

  shared_ptr<char> ptr2(nullptr);
  EXPECT_TRUE(ptr2.empty());

  shared_ptr<char> ptr3(new char(42));
  EXPECT_FALSE(ptr3.empty());
}

TEST(shared_ptr, op_bool) {
  shared_ptr<char> ptr1;
  EXPECT_FALSE(ptr1);

  shared_ptr<char> ptr2(nullptr);
  EXPECT_FALSE(ptr2);

  shared_ptr<char> ptr3(new char(42));
  EXPECT_TRUE(ptr3);
}

TEST(shared_ptr, op_log_not) {
  shared_ptr<char> ptr1;
  EXPECT_TRUE(!ptr1);

  shared_ptr<char> ptr2(nullptr);
  EXPECT_TRUE(!ptr2);

  shared_ptr<char> ptr3(new char(42));
  EXPECT_FALSE(!ptr3);
}
