#include "Gauss_solve.h"
#include "util.h"

#include <gtest/gtest.h>

#include <cmath>
#include <cstdio>
#include <fstream>
#include <random>
#include <stdexcept>
#include <string>

namespace {

void expect_vector_near(const GaussVector &actual, const GaussVector &expected, double eps = 1e-9) {
    ASSERT_EQ(actual.size(), expected.size());
    for (Eigen::Index i = 0; i < actual.size(); ++i) {
        EXPECT_NEAR(actual(i), expected(i), eps) << "at index " << i;
    }
}

} // namespace

TEST(GaussSolve, SolvesSmallSystem) {
    GaussMatrix ab(2, 3);
    ab << 2.0, 1.0, 5.0,
          1.0, -1.0, 1.0;

    const GaussVector actual = Gauss_solve(ab);

    GaussVector expected(2);
    expected << 2.0, 1.0;
    expect_vector_near(actual, expected);
}

TEST(GaussSolve, SwapsRowsWhenPivotIsZero) {
    GaussMatrix ab(2, 3);
    ab << 0.0, 2.0, 4.0,
          1.0, 1.0, 3.0;

    const GaussVector actual = Gauss_solve(ab);

    GaussVector expected(2);
    expected << 1.0, 2.0;
    expect_vector_near(actual, expected);
}

TEST(GaussSolve, SolvesThreeByThreeSystem) {
    GaussMatrix ab(3, 4);
    ab << 3.0, 2.0, -4.0, 3.0,
          2.0, 3.0, 3.0, 15.0,
          5.0, -3.0, 1.0, 14.0;

    const GaussVector actual = Gauss_solve(ab);

    GaussVector expected(3);
    expected << 3.0, 1.0, 2.0;
    expect_vector_near(actual, expected);
}

TEST(GaussSolve, ThrowsOnSingularSystem) {
    GaussMatrix ab(2, 3);
    ab << 1.0, 2.0, 3.0,
          2.0, 4.0, 6.0;

    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}

TEST(GaussSolve, SolvesReproducibleLargeSystem) {
    constexpr Eigen::Index n = 100;
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    GaussMatrix a(n, n);
    GaussVector expected(n);

    for (Eigen::Index i = 0; i < n; ++i) {
        double row_abs_sum = 0.0;
        for (Eigen::Index j = 0; j < n; ++j) {
            const double value = dist(gen);
            a(i, j) = value;
            row_abs_sum += std::abs(value);
        }
        a(i, i) += row_abs_sum + 1.0; // strict diagonal dominance
        expected(i) = dist(gen);
    }

    const GaussVector b = a * expected;
    GaussMatrix ab(n, n + 1);
    ab.leftCols(n) = a;
    ab.col(n) = b;

    const GaussVector actual = Gauss_solve(ab);
    EXPECT_LT((actual - expected).norm(), 1e-7);
}

TEST(CsvUtils, ReadsHeaderAndNumericRows) {
    const std::string filename = "gauss_csv_test_input.csv";
    {
        std::ofstream out(filename);
        out << "a1,a2,b\n";
        out << "2,1,5\n";
        out << "1,-1,1\n";
    }

    const GaussMatrix matrix = load_csv_to_matrix(filename.c_str());
    std::remove(filename.c_str());

    ASSERT_EQ(matrix.rows(), 2);
    ASSERT_EQ(matrix.cols(), 3);
    EXPECT_DOUBLE_EQ(matrix(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(matrix(1, 2), 1.0);
}
