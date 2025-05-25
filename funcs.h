#include <eigen3/Eigen/Dense>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace Eigen;

std::pair<MatrixXd, VectorXd> readCSV(const std::string& filename);

void writeCSV(const VectorXd& x, const std::string& filename);

VectorXd gaussianElimination(MatrixXd A, VectorXd b);

void generateRandomSystem(int size, const std::string& filename, int seed = 42);
