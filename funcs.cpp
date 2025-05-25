#include "funcs.h"

using namespace Eigen;

std::pair<MatrixXd, VectorXd> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<double> data;
    std::string line;
    
    int rows = 0;
    int cols = 0;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        int current_cols = 0;
        
        while (std::getline(ss, cell, ',')) {
            data.push_back(std::stod(cell));
            current_cols++;
        }
        
        if (cols == 0) cols = current_cols;
        assert(current_cols == cols && "Inconsistent row size");
        rows++;
    }
    
    MatrixXd mat(rows, cols-1);
    VectorXd vec(rows);
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols-1; ++j) {
            mat(i, j) = data[i*cols + j];
        }
        vec(i) = data[i*cols + (cols-1)];
    }
    
    return {mat, vec};
}

void writeCSV(const VectorXd& x, const std::string& filename) {
    std::ofstream file(filename);
    static const Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n");
    file << x.transpose().format(CSVFormat) << "\n";
}

VectorXd gaussianElimination(MatrixXd A, VectorXd b) {
    const int n = A.rows();
    assert(n == A.cols() && "Matrix must be square");
    
    MatrixXd Ab(n, n+1);
    Ab << A, b;

    for (int i = 0; i < n; ++i) {
        int maxRow = i;
        for (int k = i+1; k < n; ++k)
            if (abs(Ab(k,i)) > abs(Ab(maxRow,i))) 
                maxRow = k;

        Ab.row(i).swap(Ab.row(maxRow));

        if (Ab(i,i) == 0)
            throw std::runtime_error("Matrix is singular");

        for (int k = i+1; k < n; ++k) {
            double factor = Ab(k,i) / Ab(i,i);
            Ab.row(k) -= factor * Ab.row(i);
        }
    }

    VectorXd x(n);
    for (int i = n-1; i >= 0; --i) {
        x(i) = Ab(i,n);
        for (int j = i+1; j < n; ++j)
            x(i) -= Ab(i,j) * x(j);
        x(i) /= Ab(i,i);
    }
    
    return x;
}

void generateRandomSystem(int size, const std::string& filename, int seed) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    
    MatrixXd A = MatrixXd::Zero(size, size);
    VectorXd x = VectorXd::Random(size);
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            A(i,j) = dist(rng);
        A(i,i) += 2.0 * size;
    }
    
    VectorXd b = A * x;
    
    std::ofstream file(filename);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            file << A(i,j) << ",";
        file << b(i) << "\n";
    }
}



