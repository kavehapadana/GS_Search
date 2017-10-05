#include "transformmatrix.h"
#include "matrix_algebra.h"
#include <iostream>
#include <Eigen_Library/Eigen/Eigen>
#include <Eigen_Library/Eigen/src/Core/Matrix.h>
#include <Eigen_Library/Eigen/Dense>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
 
using namespace std;
using namespace Eigen;

double TransformMatrix::juliandate(VectorXd date)
{
    //date[0] = year;
    //date[1] = month;
    //date[2] = day;
    //date[3] = hour;
    //date[4] = min;
    //date[5] = sec;
    if (date(1)<=2.0)
    {
        date(0) = date(0) - 1.0;
        date(1)= date(1) + 12.0;
    }
    double Jd = floor( 365.25*(date(0) + 4716.0)) + floor( 30.6001*( date(1) + 1.0)) + 2.0 -floor( date(0)/100.0 ) + floor( floor( date(0)/100.0 )/4.0 ) + date(2) - 1524.5 + (date(3) + date(4)/60.0 + date(5)/3600.0)/24.0;
    return Jd;
}

MatrixXd TransformMatrix::dcmecef2ned(double lat, double lon)
{
    // lat & lon in degree

    double ang_lat = deg2rad(lat);
    double ang_lon = deg2rad(lon);

    double cang1 = cos(ang_lat);
    double sang1 = sin(ang_lat);

    double cang2 = cos(ang_lon);
    double sang2 = sin(ang_lon);

    MatrixXd dcm = MatrixXd::Zero(3,3);

    dcm(0, 0) = -cang2*sang1;
    dcm(0, 1) = -sang2 * sang1;
    dcm(0, 2) = cang1;

    dcm(1, 0) = -sang2;
    dcm(1, 1) = cang2;
    dcm(1, 2) = 0.0;

    dcm(2, 0) = -cang2 * cang1;
    dcm(2, 1) = -sang2 * cang1;
    dcm(2, 2) = -sang1;

    return dcm;
}

VectorXd TransformMatrix::ecef2lla(VectorXd p)
{
    double f=1.0/298.257223563;
    double R = 6378137.0;
    VectorXd ellipsoid=VectorXd::Zero(2);
    ellipsoid(0)=R;
    ellipsoid(1) = sqrt(1.0 - (1.0 - f) * (1.0 - f));
    VectorXd phi_lambda_h = ecef2geodetic(p(0), p(1), p(2), ellipsoid);
    phi_lambda_h(0) = rad2deg(phi_lambda_h(0));
    phi_lambda_h(1) = rad2deg(phi_lambda_h(1));
    return phi_lambda_h;
}

VectorXd TransformMatrix::lla2ecef(VectorXd lla)
{
    double f = 1.0 / 298.257223563;
    double R = 6378137.0;
    VectorXd ellipsoid = VectorXd::Zero(2);
    ellipsoid(0) = R;
    ellipsoid(1) = sqrt(1.0 - (1.0 - f) * (1.0 - f));
    VectorXd xyz = geodetic2ecef(deg2rad(lla(0)), deg2rad(lla(1)), lla(2), ellipsoid);
    return xyz;
}

VectorXd TransformMatrix::geodetic2ecef(double phii, double lambdaa, double h, VectorXd ellipsoid)
{
    double a  = ellipsoid(0);
    double e2 = ellipsoid(1) * ellipsoid(1);
    double sinphi = sin(phii);
    double cosphi = cos(phii);
    double N = a / sqrt(1.0 - e2 * sinphi * sinphi);
    double x = (N + h) * cosphi * cos(lambdaa);
    double y = (N + h) * cosphi * sin(lambdaa);
    double z = (N * (1.0 - e2) + h) * sinphi;
    VectorXd xyz = VectorXd::Zero(3);
    xyz(0) = x; xyz(1) = y; xyz(2) = z;
    return xyz;
}

VectorXd TransformMatrix::ecef2geodetic(double x, double y,double z, VectorXd ellipsoid)
{
    double a  = ellipsoid(0);
    double e2 = pow(ellipsoid(1),2.0);
    double ep2 = e2 / (1.0 - e2);
    double f = 1.0 - sqrt(1.0 - e2);
    double b = a * (1.0 - f);
    double lambda = atan2(y, x);
    double rho = sqrt(x * x + y * y);
    double beta = atan2(z, (1.0 - f) * rho);
    double phi = atan2(z + b * ep2 * pow(sin(beta), 3.0), rho - a * e2 * pow(cos(beta), 3.0));
    double betaNew = atan2((1.0 - f) * sin(phi), cos(phi));
    int count = 0;
    while( beta!=betaNew && count<5)
    {
        beta = betaNew;
        phi = atan2(z + b * ep2 * pow(sin(beta), 3.0), rho - a * e2 * pow(cos(beta), 3.0));
        betaNew = atan2((1.0 - f) * sin(phi), cos(phi));
        count = count + 1;
    }
    double sinphi = sin(phi);
    double N = a / sqrt(1.0 - e2 * sinphi*sinphi);
    double h = rho * cos(phi) + (z + e2 * N * sinphi) * sinphi - N;
    VectorXd phi_lambda_h = VectorXd::Zero(3);
    phi_lambda_h(0) = phi;
    phi_lambda_h(1) = lambda;
    phi_lambda_h(2) = h;
    return phi_lambda_h;
}

MatrixXd TransformMatrix::dcmeci2ecefExact(double Jd)
{
    Matrix_Algebra E;
    double t = Jd2t(Jd);

    MatrixXd P = PMatrix(t);

    MatrixXd N = NMatrix(t);

    MatrixXd Sp = SpMatrix(Jd);

    MatrixXd Sp_dot = SpMatrix_dot(Jd);

    // Matrix W = WMatrix(Jd);

    //Matrix dcm = W * Sp * N * P;
    MatrixXd dcm = Sp * N * P;

    MatrixXd dcm_dot = Sp_dot * N * P;

    MatrixXd Out_DCM=E.Matrix_Horizon_Concat(dcm, dcm_dot);
    return Out_DCM;
}

double TransformMatrix::Jd2t(double Jd)
{
    double J2000 = 2451545.0;
    double t = (Jd - J2000) / 36525.0;
    return t;
}


VectorXd TransformMatrix::Jd2t2(double jd)
{
  double temp   = jd-2415019.5;
  double tu     = temp / 365.25;
  double year   = 1900.0 + floor( tu );
  double leapyrs= floor( ( year-1901.0 )*0.25 );
  double days   = temp - ((year-1900.0)*365.0 + leapyrs );

  // ------------ check for case of beginning of a year -------------
  if (days < 1.0)
    {
      year   = year - 1.0;
      leapyrs= floor( ( year-1901.0 )*0.25 );
      days   = temp - ((year-1900.0)*365.0 + leapyrs );
    }

  // ------------------- find remaining data  -----------------------
  VectorXd Out_aux= days2mdh( year,days );
  VectorXd Out=VectorXd::Zero(6);
  Out(0)=year;
  Out(1)=Out_aux(0);
  Out(2)=Out_aux(1);
  Out(3)=Out_aux(2);
  Out(4)=Out_aux(3);
  Out(5)=Out_aux(4);

  return Out;
}

VectorXd TransformMatrix::days2mdh(double year,double days)
{
  // --------------- set up array of days in month  --------------
  VectorXd lmonth=VectorXd::Zero(12);
  for(int i= 1 ;i<= 12; i++)
    {
      lmonth(i-1) = 31.0;
      if (i == 2)
        {
          lmonth(i-1)= 28.0;
        }
      if (i == 4 || i == 6 || i == 9 || i == 11 )
        {
          lmonth(i-1)= 30.0;
        }
    }

  double dayofyr= floor(days );

  //  ----------------- find month and day of month ---------------
  if ( remainder(year-1900.0,4.0) == 0 )
    {
      lmonth(2-1)= 29.0;
    }

  int i= 1;
  double inttemp= 0.0;
  while ( ( dayofyr > inttemp + lmonth(i-1) ) && ( i < 12 ) )
    {
      inttemp= inttemp + lmonth(i-1);
      i= i+1;
    }

  double mon= double(i);
  double day= dayofyr - inttemp;

  // ----------------- find hours minutes and seconds ------------
  double temp= (days - dayofyr )*24.0;
  double hr  = ( temp>=0 )*floor(temp)+(temp<0)*ceil(temp);
  temp= (temp-hr) * 60.0;
  double minute = ( temp>=0 )*floor(temp)+(temp<0)*ceil(temp);
  double sec = (temp-minute) * 60.0;

  VectorXd Out=VectorXd::Zero(5);
  Out(0)=mon;
  Out(1)=day;
  Out(2)=hr;
  Out(3)=minute;
  Out(4)=sec;
  return Out;
}



MatrixXd TransformMatrix::PMatrix(double tt)
{
    double zetaA_ArcSec = 2306.2181 * tt + 0.30188 * tt * tt + 0.017998 * tt * tt * tt;
    double thetaA_ArcSec = 2004.3109 * tt - 0.42665 * tt * tt - 0.041833 * tt * tt * tt;
    double zA_ArcSec = 2306.2181 * tt + 1.09468 * tt*tt + 0.018203 * tt*tt*tt;

    double zetaA = deg2rad(zetaA_ArcSec / 3600.0);
    double thetaA = deg2rad(thetaA_ArcSec / 3600.0);
    double zA = deg2rad(zA_ArcSec / 3600.0);

    double c1 = cos(zetaA);
    double c2 = cos(thetaA);
    double c3 = cos(zA);
    double s1 = sin(zetaA);
    double s2 = sin(thetaA);
    double s3 = sin(zA);

    MatrixXd P = MatrixXd::Identity(3, 3);
    P(0, 0) = c1 * c2 * c3 - s1 * s3;
    P(0, 1) = -s1 * c2 * c3 - c1 * s3;
    P(0, 2) = -s2 * c3;

    P(1, 0) = c1 * c2 * s3 + s1 * c3;
    P(1, 1) = -s1 * c2 * s3 + c1 * c3;
    P(1, 2) = -s2 * s3;

    P(2, 0) = c1 * s2;
    P(2, 1) = -s1 * s2;
    P(2, 2) = c2;
    return P;
}

MatrixXd TransformMatrix::NMatrix(double tt)
{
    double Depsilon = deg2rad(-5.926 / 3600.0);
    double epsilon_m = fit_epsilon_m(tt);
    double epsilon_t = epsilon_m + Depsilon;
    double Dpsi = deg2rad(14.646 / 3600.0);

    double c1 = cos(epsilon_m);
    double c2 = cos(epsilon_t);
    double c3 = cos(Dpsi);
    double s1 = sin(epsilon_m);
    double s2 = sin(epsilon_t);
    double s3 = sin(Dpsi);

    MatrixXd N = MatrixXd::Identity(3, 3);
    N(0, 0) = c3;
    N(0, 1) = -c1 * s3;
    N(0, 2) = -s1 * s3;

    N(1, 0) = c2 * s3;
    N(1, 1) = c1 * c2 * c3 + s1 * s2;
    N(1, 2) = s1 * c2 * c3 - c1 * s2;

    N(2, 0) = s2 * s3;
    N(2, 1) = c1 * s2 * c3 - s1 * c2;
    N(2, 2) = s1 * s2 * c3 + c1 * c2;
    return N;
}


MatrixXd TransformMatrix::SpMatrix(double Jd)
{
    double TT=Jd;
    double t=Jd2t(TT);

    double J2000=2451545.0;
    double UTC = Jd;
    double DUT1 = 0.0;
    double UT1 = UTC + DUT1;
    double DT = UT1 - J2000;
    double epsilon_m = fit_epsilon_m(t);

    double Dpsi=deg2rad(14.646/3600.0);

    double alphaG = GMST(DT) + Dpsi * cos(epsilon_m);

    double c = cos(alphaG);
    double s = sin(alphaG);

    MatrixXd Sp = MatrixXd::Identity(3, 3);
    Sp(0, 0) = c;
    Sp(0, 1) = s;
    Sp(0, 2) = 0.0;

    Sp(1, 0) = -s;
    Sp(1, 1) = c;
    Sp(1, 2) = 0.0;

    Sp(2, 0) = 0.0;
    Sp(2, 1) = 0.0;
    Sp(2, 2) = 1.0;
    return Sp;
}

MatrixXd TransformMatrix::SpMatrix_dot(double Jd)
{
//    double Day_sec=1.0;
    double Day_sec=86400.0;
    double TT = Jd;
    double t = Jd2t(TT);

    double J2000 = 2451545.0;
    double UTC = Jd;
    double DUT1 = 0.0;
    double UT1 = UTC + DUT1;
    double DT = UT1 - J2000;
    double epsilon_m = fit_epsilon_m(t);

    double Dpsi = deg2rad(14.646 / 3600.0);

    double alphaG = GMST(DT) + Dpsi * cos(epsilon_m);

    double c = cos(alphaG);
    double s = sin(alphaG);

    MatrixXd Sp = MatrixXd::Identity(3, 3);
    Sp(0, 0) = -s;
    Sp(0, 1) = c;
    Sp(0, 2) = 0.0;

    Sp(1, 0) = -c;
    Sp(1, 1) = -s;
    Sp(1, 2) = 0.0;

    Sp(2, 0) = 0.0;
    Sp(2, 1) = 0.0;
    Sp(2, 2) = 0.0;

    Sp = (1.0 / Day_sec) * 6.30038809898489355227 * Sp;
    return Sp;
}

MatrixXd TransformMatrix::WMatrix(double Jd)
{
    VectorXd dms1=VectorXd::Zero(3);
    VectorXd dms2=VectorXd::Zero(3);
    dms1(2)=0.130957e-3;
    dms2(2)=0.203177e-3;
    double xp = deg2rad(dms2degrees(dms1));
    double yp = deg2rad(dms2degrees(dms2));

    MatrixXd W = MatrixXd::Identity(3, 3);
    W(0, 0) = 1.0;
    W(0, 1) = 0.0;
    W(0, 2) = xp;

    W(1, 0) = 0.0;
    W(1, 1) = 1.0;
    W(1, 2) = -yp;

    W(2, 0) = -xp;
    W(2, 1) = yp;
    W(2, 2) = 1.0;

    return W;
}

double TransformMatrix::deg2rad(double angleInDegrees)
{
    double PI=3.14159265358979323;
    double angleInRadians = (PI / 180.0) * angleInDegrees;
    return angleInRadians;
}

double TransformMatrix::rad2deg(double angleInRadiant)
{
    double PI=3.14159265358979323;
    double angleInDegree = (180.0 / PI) * angleInRadiant;
    return angleInDegree;
}

double TransformMatrix::fit_epsilon_m(double t)
{
    double epsilon_mi_ArcSec = 84381.448 - 46.8150 * t - 0.00059 * t * t + 0.001813 * t * t * t;
    double epsilon_mi = deg2rad(epsilon_mi_ArcSec / 3600.0);
    return epsilon_mi;
}

double TransformMatrix::GMST(double DT)
{
    double alphaGmst = 4.894961212823058751375704430 + DT * (6.300388098984893552276513720 + DT * (5.075209994113591478053805523e-15 + DT * (-9.253097568194335640067190688e-24)));
    return alphaGmst;
}

double TransformMatrix::dms2degrees(VectorXd DMS)
{
    double DeGree = DMS(0) + DMS(1) / 60.0 + DMS(2) / 3600.0;
    return DeGree;
}
