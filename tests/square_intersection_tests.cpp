// tests/hello_test.cc
#include <gtest/gtest.h>

TEST(HelloTest, ReturnsHelloBazel) {
    EXPECT_EQ("Hello, Bazel!", "Hello, Bazel!");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
