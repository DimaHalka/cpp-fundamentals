#include <gtest/gtest.h>

#include "factory.h"


TEST(factory, reg_unreg) {
    auto creator = [](){
        return std::unique_ptr<factory_creatable>();
    };
    factory::instance().register_type("type", creator);
    EXPECT_TRUE(factory::instance().is_registered("type"));
    factory::instance().unregister_type("type");
    EXPECT_FALSE(factory::instance().is_registered("type"));
}


TEST(factory, create) {
    class c1 : public factory_creatable {};
    auto c1_creator = [](){ return std::unique_ptr<c1>(); };

    factory::instance().register_type("c1", c1_creator);
    auto p_object1 = factory::instance().create("c1");
    auto p_object2 = factory::instance().create("c1");
    EXPECT_THROW(factory::instance().create("c2"), std::runtime_error);
    factory::instance().unregister_type("c1");
    EXPECT_THROW(factory::instance().create("c1"), std::runtime_error);
}
