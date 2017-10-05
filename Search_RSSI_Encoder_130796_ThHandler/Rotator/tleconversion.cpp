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
#include <Rotator/SGP4/sgp4ext.h>
#include <Rotator/SGP4/sgp4io.h>
#include <Rotator/SGP4/sgp4unit.h>
#include <QtDebug>
#include <QDateTime>

using namespace std;
using namespace Eigen;

VectorXd Tleconversion::tle2angle(char *longstr1, char *longstr2, double tsince, double lambda_S, VectorXd LLA_GS, bool relative_or_absolute_time)
{

  TransformMatrix E2;
  double day_minutes=24.0*60.0;
  double ro[3];
  double vo[3];
  char typerun, typeinput, opsmode;
  gravconsttype whichconst;
  elsetrec satrec;
  double startmfe, stopmfe, deltamin;

  typerun='c';
  typeinput = 'm';
  opsmode = 'a';
  whichconst = wgs72;

  twoline2rv(longstr1,longstr2,typerun,typeinput,opsmode,whichconst, startmfe, stopmfe, deltamin, satrec);

  double Jd0=satrec.jdsatepoch;
  double Jd = Jd0+(tsince/day_minutes);
  if(relative_or_absolute_time==false)
    {
      Jd=tsince;
      tsince=(tsince-Jd0)*24.0*60.0;
    }
  sgp4(whichconst, satrec, tsince, ro, vo);
  VectorXd r_eci=VectorXd::Zero(3);
  VectorXd v_eci=VectorXd::Zero(3);
  for (int i=0;i<3;i++)
    {
      r_eci(i)=ro[i];
      v_eci(i)=vo[i];
    }


  VectorXd R_ef = E2.lla2ecef(LLA_GS) / 1e3; //[km]
  MatrixXd X_ecef2ned = E2.dcmecef2ned(LLA_GS(0), LLA_GS(1));
  VectorXd y = VectorXd::Zero(3);

  MatrixXd E_eci2ecefs = E2.dcmeci2ecefExact(Jd);
  MatrixXd E_eci2ecef=E_eci2ecefs.block(0,0,3,3);
  MatrixXd E_eci2ecef_dot = E_eci2ecefs.block(0,3,3,3);
  VectorXd rho_ned = X_ecef2ned * (E_eci2ecef * r_eci - R_ef);
  VectorXd rho_nwu=rho_ned;
  rho_nwu(1) = -rho_ned(1); rho_nwu(2) = -rho_ned(2);
  double rho_aux_norm = sqrt(pow(rho_nwu(0), 2.0) + pow(rho_nwu(1), 2.0));
  y(0) = atan2(rho_nwu(2), rho_aux_norm);
  y(1) = atan2(rho_nwu(1), -rho_nwu(0));
  y(1)=pi+y(1);
  double PI=3.141592653589;
  //(y(1)>360.0/180.0*PI)*(y(1)-360.0/180.0*PI)+(0.0<y(1) & y(1)<360.0/180.0*PI)*y(1)+(y(1)<0.0)*(-y(1));
  VectorXd y_aux2 = X_ecef2ned * (E_eci2ecef_dot * r_eci + E_eci2ecef * v_eci);
//  y_aux2(1) = y_aux2(1);
//  y_aux2(2) = y_aux2(2);

  VectorXd nwu2ned=VectorXd::Zero(3);
  nwu2ned(0)=-1.0;nwu2ned(1)=1.0;nwu2ned(2)=1.0;
  VectorXd y_aux3=y_aux2.cwiseProduct(nwu2ned);
  VectorXd y_aux4 = (y_aux3.cwiseProduct(rho_nwu)) / (rho_nwu.norm());
  y(2) = (y_aux4.sum()) / lambda_S;
  return y;
}

VectorXd Tleconversion::tle2rveci(char *Longstr1, char *Longstr2, double Tsince, bool relative_or_absolute_time)
{
  double ro2[3];
  double vo2[3];
  char typerun2, typeinput2, opsmode2;
  gravconsttype whichconst2;
  elsetrec satrec2;
  double startmfe2, stopmfe2, deltamin2;

  typerun2='c';
  typeinput2 = 'm';
  opsmode2 = 'a';
  whichconst2 = wgs72;

  twoline2rv(Longstr1,Longstr2,typerun2,typeinput2,opsmode2,whichconst2, startmfe2, stopmfe2, deltamin2, satrec2);
  double Jd0=satrec2.jdsatepoch;
  if(relative_or_absolute_time==false)
    {
      Tsince=(Tsince-Jd0)*24.0*60.0;
    }

  sgp4(whichconst2, satrec2, Tsince, ro2, vo2);

  VectorXd rv_eci2=VectorXd::Zero(3+3);
  for (int i=0;i<3;i++)
    {
      rv_eci2(i)=ro2[i];
      rv_eci2(i+3)=vo2[i];
    }
  return rv_eci2;
}
