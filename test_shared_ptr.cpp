#include <gtest/gtest.h>

#include "shared_ptr.hpp"

TEST(shared_ptr, empty) {
    shared_ptr<int> shared1;
    EXPECT_TRUE(shared1.empty());
    EXPECT_EQ(shared1.ref_count(), 0);
    
    shared_ptr<int> shared2 = shared_ptr<int>(new int(42));
    EXPECT_FALSE(shared2.empty());
    EXPECT_EQ(shared2.ref_count(), 1);
}

struct helper {
    explicit helper(bool* p) {
        mp_flag = p;
    }
    
    ~helper(){
        assert(*mp_flag == false);
        *mp_flag = true;
    }
    
    bool* mp_flag;
};

TEST(shared_ptr, copy_ctor) {
    bool destructed = false;
    {
        shared_ptr<helper> shared1(new helper(&destructed));
        shared_ptr<helper> shared2(shared1);
        EXPECT_EQ(shared1.ref_count(), 2);
        EXPECT_EQ(shared2.ref_count(), 2);
        EXPECT_FALSE(destructed);
    }
    EXPECT_TRUE(destructed);
}

TEST(shared_ptr, move_ctor) {
    bool destructed = false;
    {
        shared_ptr<helper> shared1(new helper(&destructed));
        shared_ptr<helper> shared2(std::move(shared1));
        EXPECT_TRUE(shared1.empty());
        EXPECT_FALSE(shared2.empty());        
    }
    EXPECT_TRUE(destructed);
}

TEST(shared_ptr, reset_sole_owner) {
    bool destructed = false;
    shared_ptr<helper> shared1(new helper(&destructed));
    EXPECT_EQ(shared1.ref_count(), 1);
    shared1.reset();
    EXPECT_EQ(shared1.ref_count(), 0);
    EXPECT_TRUE(destructed);
}
