#include "Gauss_solve.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix &ab) {
    constexpr double eps = 1e-12;

    const Eigen::Index n = ab.rows();
    if (n == 0 || ab.cols() != n + 1) {
        throw std::runtime_error("Expected an augmented n x (n + 1) matrix");
    }

    for (Eigen::Index col = 0; col < n; ++col) {
        Eigen::Index pivot_row = col;
        double best_abs = std::abs(ab(col, col));

        for (Eigen::Index row = col + 1; row < n; ++row) {
            const double cur_abs = std::abs(ab(row, col));
            if (cur_abs > best_abs) {
                best_abs = cur_abs;
                pivot_row = row;
            }
        }

        if (best_abs < eps) {
            throw std::runtime_error("The system matrix is singular or nearly singular");
        }

        if (pivot_row != col) {
            ab.row(col).swap(ab.row(pivot_row));
        }

        for (Eigen::Index row = col + 1; row < n; ++row) {
            const double factor = ab(row, col) / ab(col, col);
            if (std::abs(factor) < eps) {
                ab(row, col) = 0.0;
                continue;
            }

            ab.row(row).tail(n + 1 - col) -= factor * ab.row(col).tail(n + 1 - col);
            ab(row, col) = 0.0;
        }
    }

    GaussVector x(n);
    for (Eigen::Index row = n - 1; row >= 0; --row) {
        double rhs = ab(row, n);
        if (row + 1 < n) {
            rhs -= ab.row(row).segment(row + 1, n - row - 1).dot(x.segment(row + 1, n - row - 1));
        }

        const double diag = ab(row, row);
        if (std::abs(diag) < eps) {
            throw std::runtime_error("The system matrix is singular or nearly singular");
        }
        x(row) = rhs / diag;

        if (row == 0) {
            break;
        }
    }

    return x;
}
