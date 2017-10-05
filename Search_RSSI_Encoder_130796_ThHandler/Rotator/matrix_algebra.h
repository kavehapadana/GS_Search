#ifndef MATRIX_ALGEBRA_H
#define MATRIX_ALGEBRA_H

#include <iostream>
#include <Eigen_Library/Eigen/Eigen>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <Eigen_Library/Eigen/src/Core/Matrix.h>
#include <Eigen_Library/Eigen/Dense>
 
using namespace Eigen;
using namespace std;

class Matrix_Algebra
{
public:
    MatrixXd Kron(MatrixXd A, MatrixXd B);
public:
    MatrixXd Pow(MatrixXd A, double pow_);
public:
    MatrixXd vec2mat(VectorXd A, int N_col);
public:
    MatrixXd circshift(MatrixXd A, int shiftsize);
public:
    MatrixXd fliplr(MatrixXd A);
public:
    VectorXd Vec(MatrixXd A);
public:
    VectorXd MinVec(VectorXd v);
public:
    VectorXd MaxVec(VectorXd v);
public:
    MatrixXd chol(MatrixXd A);
public:
    VectorXd Vector_Vertical_Concat(VectorXd A, VectorXd B);
public:
    MatrixXd Matrix_select(int N1, int N2, int M1, int M2, MatrixXd A);
public:
    MatrixXd Matrix_select_set(int N1, int N2, int M1, int M2, MatrixXd A, MatrixXd B);
public:
    MatrixXd Matrix_Horizon_Concat(MatrixXd A, MatrixXd B);
public:
    MatrixXd Matrix_Vertical_Concat(MatrixXd A, MatrixXd B);
public:
    VectorXd power_eig(MatrixXd A, int length);
};

#endif // MATRIX_ALGEBRA_H
