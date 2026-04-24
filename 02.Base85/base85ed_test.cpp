#include <gtest/gtest.h>

#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>

#include "base85ed.h"

static std::vector<uint8_t> cstr2v(const char* s)
{
    return std::vector<uint8_t>(s, s + std::string(s).size());
}

TEST(Base85Encode, ShortCases)
{
    EXPECT_EQ(base85::encode(cstr2v("")), cstr2v(""));
    EXPECT_EQ(base85::encode(cstr2v("1")), cstr2v("F#"));
    EXPECT_EQ(base85::encode(cstr2v("12")), cstr2v("F){"));
    EXPECT_EQ(base85::encode(cstr2v("123")), cstr2v("F)}j"));
    EXPECT_EQ(base85::encode(cstr2v("1234")), cstr2v("F)}kW"));
}

TEST(Base85Decode, ShortCases)
{
    EXPECT_EQ(base85::decode(cstr2v("")), cstr2v(""));
    EXPECT_EQ(base85::decode(cstr2v("F#")), cstr2v("1"));
    EXPECT_EQ(base85::decode(cstr2v("F){")), cstr2v("12"));
    EXPECT_EQ(base85::decode(cstr2v("F)}j")), cstr2v("123"));
    EXPECT_EQ(base85::decode(cstr2v("F)}kW")), cstr2v("1234"));
}

TEST(Base85RoundTrip, Text)
{
    std::vector<uint8_t> data = cstr2v("hello world");
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, Empty)
{
    std::vector<uint8_t> data;
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, BinaryData)
{
    std::vector<uint8_t> data = { 0, 1, 2, 3, 4, 5, 100, 200, 255 };
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, DifferentSizes)
{
    for (int n = 1; n <= 20; ++n)
    {
        std::vector<uint8_t> data;

        for (int i = 0; i < n; ++i)
        {
            data.push_back(static_cast<uint8_t>(i * 7 + 3));
        }

        EXPECT_EQ(base85::decode(base85::encode(data)), data);
    }
}

TEST(Base85Decode, InvalidCharacter)
{
    EXPECT_THROW(base85::decode(cstr2v("\"")), std::runtime_error);
}

TEST(Base85Decode, InvalidLength)
{
    EXPECT_THROW(base85::decode(cstr2v("A")), std::runtime_error);
}
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}