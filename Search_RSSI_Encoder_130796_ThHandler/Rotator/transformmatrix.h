#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include "transformmatrix.h"
#include "matrix_algebra.h"
#include <iostream>
#include <Eigen_Library/Eigen/Eigen>
#include <Eigen_Library/Eigen/src/Core/Matrix.h>
#include <Eigen_Library/Eigen/Dense>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 
using namespace std;
using namespace Eigen;


class TransformMatrix
{
public:
    double juliandate(VectorXd date);

public:
    MatrixXd dcmecef2ned(double lat, double lon);

public:
    VectorXd ecef2lla(VectorXd p);

public:
    VectorXd lla2ecef(VectorXd lla);

public:
    VectorXd geodetic2ecef(double phi, double lambda, double h, VectorXd ellipsoid);

public:
    VectorXd ecef2geodetic(double x, double y,double z, VectorXd ellipsoid);

public:
    MatrixXd dcmeci2ecefExact(double Jd);

public:
    double Jd2t(double Jd);

public:
    VectorXd days2mdh ( double year,double days);

public:
    VectorXd Jd2t2(double Jd);

public:
    MatrixXd PMatrix(double tt);

public:
    MatrixXd NMatrix(double tt);

public:
    MatrixXd SpMatrix(double Jd);

public:
    MatrixXd SpMatrix_dot(double Jd);

public:
    MatrixXd WMatrix(double Jd);

public:
    double deg2rad(double angleInDegrees);

public:
    double rad2deg(double angleInRadiant);

public:
    double fit_epsilon_m(double t);

public:
    double GMST(double DT);

public:
    double dms2degrees(VectorXd DMS);
};

#endif // TRANSFORMMATRIX_H
