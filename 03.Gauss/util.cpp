#include "util.h"

#include <cerrno>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

std::string trim(const std::string &s) {
    const auto first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const auto last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, last - first + 1);
}

std::vector<std::string> split_csv_line(const std::string &line) {
    std::vector<std::string> cells;
    std::stringstream ss(line);
    std::string cell;

    while (std::getline(ss, cell, ',')) {
        cells.push_back(trim(cell));
    }

    if (!line.empty() && line.back() == ',') {
        cells.emplace_back();
    }

    return cells;
}

bool parse_double(const std::string &s, double &value) {
    const auto trimmed = trim(s);
    if (trimmed.empty()) {
        return false;
    }

    char *end = nullptr;
    errno = 0;
    value = std::strtod(trimmed.c_str(), &end);
    if (end == trimmed.c_str() || errno == ERANGE) {
        return false;
    }

    while (*end != '\0') {
        if (!std::isspace(static_cast<unsigned char>(*end))) {
            return false;
        }
        ++end;
    }

    return true;
}

} // namespace

GaussMatrix load_csv_to_matrix(const char *filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Cannot open input csv file");
    }

    std::vector<std::vector<double>> rows;
    std::string line;
    std::size_t width = 0;

    while (std::getline(in, line)) {
        if (trim(line).empty()) {
            continue;
        }

        const auto cells = split_csv_line(line);
        std::vector<double> row;
        row.reserve(cells.size());

        bool numeric_row = true;
        for (const auto &cell : cells) {
            double value = 0.0;
            if (!parse_double(cell, value)) {
                numeric_row = false;
                break;
            }
            row.push_back(value);
        }

        if (!numeric_row) {
            if (rows.empty()) {
                continue; // optional header line
            }
            throw std::runtime_error("Non-numeric value in csv body");
        }

        if (row.empty()) {
            continue;
        }

        if (width == 0) {
            width = row.size();
        } else if (row.size() != width) {
            throw std::runtime_error("Csv rows have different lengths");
        }

        rows.push_back(std::move(row));
    }

    if (rows.empty()) {
        throw std::runtime_error("Csv file does not contain numeric rows");
    }

    GaussMatrix matrix(static_cast<Eigen::Index>(rows.size()), static_cast<Eigen::Index>(width));
    for (Eigen::Index i = 0; i < matrix.rows(); ++i) {
        for (Eigen::Index j = 0; j < matrix.cols(); ++j) {
            matrix(i, j) = rows[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)];
        }
    }

    return matrix;
}

void print_matrix_as_csv(std::ostream &out, const GaussMatrix &matrix, int prec) {
    out << std::fixed << std::setprecision(prec);
    for (Eigen::Index i = 0; i < matrix.rows(); ++i) {
        for (Eigen::Index j = 0; j < matrix.cols(); ++j) {
            if (j != 0) {
                out << ',';
            }
            out << matrix(i, j);
        }
        out << '\n';
    }
}

void print_vector_as_csv(std::ostream &out, const GaussVector &vector, int prec) {
    out << "x\n";
    out << std::fixed << std::setprecision(prec);
    for (Eigen::Index i = 0; i < vector.size(); ++i) {
        out << vector(i) << '\n';
    }
}
