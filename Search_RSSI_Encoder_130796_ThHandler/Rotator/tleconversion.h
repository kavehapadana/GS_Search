#ifndef TLE2ANGLE_H
#define TLE2ANGLE_H

#include "tleconversion.h"
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


class Tleconversion
{
public:
  VectorXd tle2angle(char *longstr1,char *longstr2, double tsince,  double lambda_S, VectorXd LLA_GS, bool relative_or_absolute_time);

public:
  VectorXd tle2rveci(char *Longstr1, char *Longstr2, double Tsince , bool relative_or_absolute_time);
};
#endif // TLE2ANGLE_H
