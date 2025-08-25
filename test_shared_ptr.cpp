#include <gtest/gtest.h>

#include "shared_ptr.hpp"

TEST(shared_ptr, empty) {
    shared_ptr<int> shared1;
    ASSERT_TRUE(shared1.empty());
    
    shared_ptr<int> shared2 = shared_ptr<int>(new int(42));
    ASSERT_FALSE(shared2.empty());
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
        ASSERT_FALSE(destructed);
    }
    ASSERT_TRUE(destructed);
}
