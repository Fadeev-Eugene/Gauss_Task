#include <gtest/gtest.h>
#include <eigen3/Eigen/Dense>
#include <fstream>
#include <vector>
#include "funcs.h" 

using namespace Eigen;

TEST(GaussianEliminationTest, Solves2x2System) {
    MatrixXd A(2, 2);
    A << 2, 1, 
         1, 1;
    VectorXd b(2);
    b << 3, 2;
    
    VectorXd x = gaussianElimination(A, b);
    
    EXPECT_NEAR(x(0), 1.0, 1e-6);
    EXPECT_NEAR(x(1), 1.0, 1e-6);
}

TEST(GaussianEliminationTest, ThrowsOnSingularMatrix) {
    MatrixXd A(2, 2);
    A << 1, 2,
         2, 4;
    VectorXd b(2);
    b << 3, 6;
    
    EXPECT_THROW(gaussianElimination(A, b), std::runtime_error);
}


TEST(CSVIOTest, ReadsAndWritesConsistently) {
    const std::string test_filename = "test_system.csv";
    const int system_size = 3;
    
    generateRandomSystem(system_size, test_filename);
    
    auto [A, b] = readCSV(test_filename);
    VectorXd x = gaussianElimination(A, b);
    
    const std::string solution_filename = "test_solution.csv";
    writeCSV(x, solution_filename);
    
    std::ifstream file(solution_filename);
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    
    std::vector<double> values;
    std::string cell;
    while (std::getline(ss, cell, ',')) {
        values.push_back(std::stod(cell));
    }
    
    VectorXd saved_x = Map<VectorXd>(values.data(), values.size());
    ASSERT_EQ(x.size(), saved_x.size());
    EXPECT_TRUE(x.isApprox(saved_x, 1e-6));
}

TEST(RandomSystemTest, GeneratesValidSystem) {
    const std::string filename = "random_system.csv";
    const int size = 100;
    
    generateRandomSystem(size, filename);
    
    auto [A, b] = readCSV(filename);
    
    ASSERT_EQ(A.rows(), size);
    ASSERT_EQ(A.cols(), size);
    ASSERT_EQ(b.size(), size);
    
    FullPivLU<MatrixXd> lu(A);
    EXPECT_TRUE(lu.isInvertible());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
