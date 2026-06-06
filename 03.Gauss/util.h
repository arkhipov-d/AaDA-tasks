#pragma once

#include <Eigen/Dense>

#include <iosfwd>

using GaussVector = Eigen::VectorXd;
using GaussMatrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

GaussMatrix load_csv_to_matrix(const char *filename);
void print_matrix_as_csv(std::ostream &out, const GaussMatrix &matrix, int prec = 10);
void print_vector_as_csv(std::ostream &out, const GaussVector &vector, int prec = 10);
