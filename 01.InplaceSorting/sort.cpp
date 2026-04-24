#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "collvalue.h"
#include "sorting.h"

void fill_random(std::vector<CollInt>& v, int n)
{
    v.clear();
    for (int i = 0; i < n; ++i)
    {
        v.push_back(rand() % 1000);
    }
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    std::vector<CollInt> v;

    std::cout << "N\tAlgorithm\tComparisons\tSwaps\tMoves\n";

    for (int n = 10; n <= 100; n += 30)
    {
        fill_random(v, n);

        CollInt::reset();
        bubble_sort(v.begin(), v.end());
        std::cout << n << "\tBubble\t\t"
            << CollInt::comps << "\t\t"
            << CollInt::swaps << "\t\t"
            << CollInt::moves << "\n";

        fill_random(v, n);

        CollInt::reset();
        quick_sort(v.begin(), v.end());
        std::cout << n << "\tQuick\t\t"
            << CollInt::comps << "\t\t"
            << CollInt::swaps << "\t\t"
            << CollInt::moves << "\n";
    }

    return 0;
}