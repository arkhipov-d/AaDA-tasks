#pragma once

#include <iterator>
#include <utility>

template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return;
    }

    for (Iterator i = begin; i != end; ++i)
    {
        bool swapped = false;

        for (Iterator j = begin; std::next(j) != end; ++j)
        {
            Iterator nxt = std::next(j);

            if (*nxt < *j)
            {
                using std::swap;
                swap(*j, *nxt);
                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }
}

template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (std::distance(begin, end) <= 1)
    {
        return;
    }

    Iterator left = begin;
    Iterator right = std::prev(end);
    auto pivot = *(begin + std::distance(begin, end) / 2);

    while (left <= right)
    {
        while (*left < pivot)
        {
            ++left;
        }

        while (pivot < *right)
        {
            --right;
        }

        if (left <= right)
        {
            using std::swap;
            swap(*left, *right);
            ++left;

            if (right == begin)
            {
                break;
            }

            --right;
        }
    }

    quick_sort(begin, right + 1);
    quick_sort(left, end);
}