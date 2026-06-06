#include "Gauss_solve.h"
#include "util.h"

#include <exception>
#include <fstream>
#include <iostream>

int main(int argc, const char *argv[]) {
    if (argc != 2 && argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input.csv [output.csv]\n";
        return 1;
    }

    try {
        GaussMatrix ab = load_csv_to_matrix(argv[1]);
        const GaussVector x = Gauss_solve(ab);

        if (argc == 3) {
            std::ofstream out(argv[2]);
            if (!out) {
                std::cerr << "Cannot open output csv file\n";
                return 1;
            }
            print_vector_as_csv(out, x);
        } else {
            print_vector_as_csv(std::cout, x);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
