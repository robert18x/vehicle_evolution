#include <gtest/gtest.h>
#include "hello.h"

TEST(test, test1){
    EXPECT_TRUE(true);
}

TEST(test, test2){
    EXPECT_EQ(add(1,1), 2);
}
