#include <gtest/gtest.h>
#include <vector>

#include "sorting.h"

TEST(BubbleSort, Basic)
{
    std::vector<int> v = { 5, 1, 4, 2, 8 };
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({ 1, 2, 4, 5, 8 }));
}

TEST(BubbleSort, Empty)
{
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(BubbleSort, OneElement)
{
    std::vector<int> v = { 42 };
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({ 42 }));
}

TEST(BubbleSort, Duplicates)
{
    std::vector<int> v = { 3, 1, 3, 2, 1 };
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({ 1, 1, 2, 3, 3 }));
}

TEST(QuickSort, Basic)
{
    std::vector<int> v = { 5, 1, 4, 2, 8 };
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({ 1, 2, 4, 5, 8 }));
}

TEST(QuickSort, Empty)
{
    std::vector<int> v;
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(QuickSort, OneElement)
{
    std::vector<int> v = { 42 };
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({ 42 }));
}

TEST(QuickSort, Duplicates)
{
    std::vector<int> v = { 3, 1, 3, 2, 1 };
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({ 1, 1, 2, 3, 3 }));
}
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}