#include <vector>
#include <cstdint>
#include <stdexcept>

#include "base85ed.h"

static const char alphabet[] =
"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

static int value_of(uint8_t c)
{
    for (int i = 0; i < 85; ++i)
    {
        if (static_cast<uint8_t>(alphabet[i]) == c)
        {
            return i;
        }
    }

    throw std::runtime_error("invalid base85 character");
}

std::vector<uint8_t> base85::encode(std::vector<uint8_t> const& bytes)
{
    std::vector<uint8_t> result;

    for (size_t i = 0; i < bytes.size(); i += 4)
    {
        size_t left = bytes.size() - i;
        size_t block_size = left < 4 ? left : 4;

        uint32_t value = 0;

        for (size_t j = 0; j < 4; ++j)
        {
            value <<= 8;

            if (j < block_size)
            {
                value += bytes[i + j];
            }
        }

        char encoded[5];

        for (int j = 4; j >= 0; --j)
        {
            encoded[j] = alphabet[value % 85];
            value /= 85;
        }

        for (size_t j = 0; j < block_size + 1; ++j)
        {
            result.push_back(static_cast<uint8_t>(encoded[j]));
        }
    }

    return result;
}

std::vector<uint8_t> base85::decode(std::vector<uint8_t> const& b85str)
{
    std::vector<uint8_t> result;

    if (b85str.size() % 5 == 1)
    {
        throw std::runtime_error("invalid base85 length");
    }

    for (size_t i = 0; i < b85str.size(); i += 5)
    {
        size_t left = b85str.size() - i;
        size_t block_size = left < 5 ? left : 5;

        uint32_t value = 0;

        for (size_t j = 0; j < 5; ++j)
        {
            value *= 85;

            if (j < block_size)
            {
                value += value_of(b85str[i + j]);
            }
            else
            {
                value += 84;
            }
        }

        uint8_t decoded[4];

        for (int j = 3; j >= 0; --j)
        {
            decoded[j] = static_cast<uint8_t>(value & 255);
            value >>= 8;
        }

        size_t bytes_to_write = block_size - 1;

        for (size_t j = 0; j < bytes_to_write; ++j)
        {
            result.push_back(decoded[j]);
        }
    }

    return result;
}