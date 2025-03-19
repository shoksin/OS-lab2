#include <gtest/gtest.h>
#include <vector>
#include <Windows.h>
#include "threads.h"

class ThreadTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ThreadTest, MinMaxThreadTest) {
    std::vector<int> array = {5, 2, 9, 1, 7};
    ThreadData data;
    data.array = &array;

    MinMaxThread(&data);

    EXPECT_EQ(data.min_value, 1);
    EXPECT_EQ(data.max_value, 9);
    EXPECT_EQ(data.min_index, 3);
    EXPECT_EQ(data.max_index, 2);
}

TEST_F(ThreadTest, AverageThreadTest) {
    std::vector<int> array = {5, 2, 9, 1, 7};
    ThreadData data;
    data.array = &array;

    AverageThread(&data);

    EXPECT_DOUBLE_EQ(data.avg_value, 4.8);
}

TEST_F(ThreadTest, ReplaceMinMaxTest) {
    std::vector<int> array = {5, 2, 9, 1, 7};
    std::vector<double> expected = {5.0, 2.0, 4.8, 4.8, 7.0};
    
    ThreadData data;
    data.array = &array;
    
    MinMaxThread(&data);
    AverageThread(&data);
    
    std::vector<double> result(array.size());
    
    for (int i = 0;i<array.size();i++){
        result[i] = array[i];
        if (i == data.min_index || i == data.max_index) {
            result[i] = data.avg_value;
        }
    }
    
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_NEAR(result[i], expected[i], 0.001);
    }
}

TEST_F(ThreadTest, SingleElementArrayTest) {
    std::vector<int> array = {6};
    ThreadData data;
    data.array = &array;
    
    MinMaxThread(&data);
    AverageThread(&data);
    
    EXPECT_EQ(data.min_value, 6);
    EXPECT_EQ(data.max_value, 6);
    EXPECT_EQ(data.min_index, 0);
    EXPECT_EQ(data.max_index, 0);
    EXPECT_DOUBLE_EQ(data.avg_value, 6.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}