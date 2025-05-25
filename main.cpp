#include "funcs.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input.csv>\n";
        return 1;
    }
    
    try {
        auto [A, b] = readCSV(argv[1]);
        VectorXd x = gaussianElimination(A, b);
        writeCSV(x, "solution.csv");
        std::cout << "Solution saved to solution.csv\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
    }
    
    return 0;
}
