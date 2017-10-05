#ifndef ITERATIVE_ESTIMATION_H
#define ITERATIVE_ESTIMATION_H

#include <iostream>
#include <Eigen_Library/Eigen/Eigen>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <Eigen_Library/Eigen/src/Core/Matrix.h>
#include <Eigen_Library/Eigen/Dense>

using namespace std;
using namespace Eigen;

class Iterative_Estimation
{

public:
    VectorXd runge_kutta_keppler(double dt, VectorXd state0);

public:
    VectorXd dynamics_parameters(VectorXd state0);

public:
    MatrixXd jacobian_state(MatrixXd s_hat, double dT);

public:
    MatrixXd EKF(MatrixXd POS, MatrixXd s_hat, MatrixXd M, double update_rate, MatrixXd C, MatrixXd Q, double just_propagate);

public:
    MatrixXd NAUKF2(MatrixXd POS, MatrixXd state_hat, MatrixXd P, double update_rate, MatrixXd C, MatrixXd Q, double just_propagate, MatrixXd X_ecef2ned, VectorXd R_ef, double lambda_S, double Jd0, double n_time, double flag_dplr);

public:
    MatrixXd NAUKF3(MatrixXd POS, MatrixXd state_hat, MatrixXd P, double dT, MatrixXd C, MatrixXd Q, double just_propagate, MatrixXd X_ecef2ned, VectorXd R_ef, double lambda_S, double Time_in_JulianDate, double flag_dplr);
};

#endif // ITERATIVE_ESTIMATION_H
