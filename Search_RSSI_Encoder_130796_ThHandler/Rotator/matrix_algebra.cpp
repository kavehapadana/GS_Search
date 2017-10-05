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

MatrixXd Matrix_Algebra::Kron(MatrixXd A,MatrixXd B)
{
    MatrixXd C=MatrixXd::Zero(A.rows()*B.rows(),A.cols()*B.cols());
    for (int i = 0; i < A.rows(); i++)
    {
        for (int j = 0; j < A.cols(); j++)
        {
            C.block(i*B.rows(),j*B.cols(),B.rows(),B.cols())=A(i,j)*B;
        }
    }
    return C;
}

MatrixXd Matrix_Algebra::Pow(MatrixXd A, double pow_)
{
    MatrixXd C = MatrixXd::Zero(A.rows(), A.cols());
    for (int i = 0; i < A.rows();i++)
    {
        for (int j = 0; j < A.cols(); j++)
        {
            C(i, j) = pow(A(i,j),pow_);
        }
    }
    return C;
}

MatrixXd Matrix_Algebra::vec2mat(VectorXd A, int N_col)
{
    int N_row=ceil((double)A.rows()/N_col);
    VectorXd A2=VectorXd::Zero(N_row*N_col);
    for (int i=0;i<A.rows();i++)
    {
        A2(i)=A(i);
    }
    MatrixXd C=MatrixXd::Zero(N_row,N_col);
    for(int i=0;i<N_col;i++)
    {
        C.block(0,i,N_row,1)=A2.block(i*N_row,0,N_row,1);
    }
    return C;
}


MatrixXd Matrix_Algebra::circshift(MatrixXd A, int shiftsize)
{
    int N_row = A.rows();
    int N_col = A.cols();
    while(shiftsize>N_row)
    {
        shiftsize=shiftsize-N_row;
    }
    MatrixXd B = MatrixXd::Identity(N_row, N_col);
    B.block(shiftsize,0,N_row-shiftsize,N_col)=A.block(0,0,N_row-shiftsize,N_col);
    B.block(0,0,shiftsize,N_col)=A.block(N_row-shiftsize,0,shiftsize,N_col);
    return B;
}


MatrixXd Matrix_Algebra::fliplr(MatrixXd A)
{
    int N_row = A.rows();
    int N_col = A.cols();
    MatrixXd B = MatrixXd::Identity(N_row, N_col);
    for (int i = 0; i < N_col; i++)
    {
        B.block(0,i,B.rows(),1)=A.block(0,N_col - 1 - i,B.rows(),1);
        //B.SetColumnVector(A.GetColumnVector(N_col - 1 - i), i);
    }
    return B;
}


VectorXd Matrix_Algebra::Vec(MatrixXd A)
{
    int M=A.cols();
    int N=A.rows();
    VectorXd B=VectorXd::Zero(N*M);
    for (int i=0;i<M;i++)
    {
        B.block(i*N,0,N,1)=A.block(0,i,N,1);
    }
    return B;
}

VectorXd Matrix_Algebra::MaxVec(VectorXd v)
{
    int length = 0;
    double maxval = v(0);
    length = v.rows();
    int indx = 0;
    int i = 1;
    for (i = 1; i < length; i++)
    {
        if (v(i) > maxval)
        {
            maxval = v(i);
            indx = i;
        }
    }
    double ii = (double)indx;
    VectorXd out1(2);
    out1(1) = ii;
    out1(0) = maxval;
    return out1;
}

VectorXd Matrix_Algebra::MinVec(VectorXd v)
{
    int length = 0;
    double minval = v(0);
    length = v.rows();
    double indx = 0;
    int i = 1;
    for (i = 1; i < length; i++)
    {
        if (v(i) < minval)
        {
            minval = v(i);
            indx = i;
        }
    }
    double ii = (double)indx;
    VectorXd out1(2);
    out1(1) = ii;
    out1(0) = minval;
    return out1;
}

MatrixXd Matrix_Algebra::chol(MatrixXd A)
{
    double A1 = 1;
    double A2 = 1e10;
    double eps = A1 / A2;
    int Length;
    Length = A.cols();
    MatrixXd L = MatrixXd::Zero(Length, Length);
    int def = 1;
    for (int i = 0; i < Length; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            double s = A(i, j);
            for (int k = 0; k <= j - 1; k++)
            {
                s = s - L(i, k) * L(j, k);
            }
            if (j < i)
            {
                if (L(j, j) > eps)
                {
                    L(i, j) = s / L(j, j);
                }
                else
                {
                    L(i, j) = 0;
                }
            }
            else
            {
                if (s < -eps)
                {
                    s = 0;
                    def = -1;
                }
                else if (s < eps)
                {
                    s = 0;
                    if (def > 0)
                    {
                        def = 0;
                    }
                }
                L(j, j) = sqrt(s);
            }
        }
    }
    if (def < 0)
    {
        //Matrix is not P.D.
    }
    return L;
}


VectorXd Matrix_Algebra::Vector_Vertical_Concat(VectorXd A, VectorXd B)
{
    int LengthA = A.rows();
    int LengthB = B.rows();
    VectorXd C = VectorXd::Zero(LengthA + LengthB);
    C.block(0,0,LengthA,1)=A;
    C.block(LengthA,0,LengthB,1)=B;
    return C;
}

MatrixXd Matrix_Algebra::Matrix_select(int N1, int N2, int M1, int M2, MatrixXd A)
{
    MatrixXd C = MatrixXd::Zero(N2 - N1 + 1, M2 - M1 + 1);
    C=A.block(N1,M1,N2-N1+1,M2-M1+1);
    return C;
}

MatrixXd Matrix_Algebra::Matrix_select_set(int N1, int N2, int M1, int M2, MatrixXd A, MatrixXd B)
{
    A.block(N1,M1,N2-N1,M2-M1)=B;
    return A;
}

MatrixXd Matrix_Algebra::Matrix_Horizon_Concat(MatrixXd A, MatrixXd B)
{
    int colA = A.cols();
    int rowA = A.rows();
    int colB = B.cols();
    int rowB = B.rows();
    if (rowA == 0)
    {
        MatrixXd C = B;
        return C;
    }
    else
    {
        double row= (rowA>rowB)*rowA+(rowA<=rowB)*rowB;
        MatrixXd C = MatrixXd::Zero(row, colA + colB);
        C.block(0,0,rowA,colA)=A;
        C.block(0,colA,rowB,colB)=B;
        return C;
    }
}

MatrixXd Matrix_Algebra::Matrix_Vertical_Concat(MatrixXd A, MatrixXd B)
{
    int colA = A.cols();
    int rowA = A.rows();
    int colB = B.cols();
    int rowB = B.rows();
    if (colA == 0)
    {
        MatrixXd C = B;
        return C;
    }
    else
    {
        double col= (colA>colB)*colA+(colA<=colB)*colB;
        MatrixXd C = MatrixXd::Zero(rowA+rowB, col);
        C.block(0,0,rowA,colA)=A;
        C.block(rowA,0,rowB,colB)=B;
        return C;
    }
}

VectorXd Matrix_Algebra::power_eig(MatrixXd A, int length)
{
    double lambda = 0;
    VectorXd v=VectorXd::Ones(length);
    int Flag = 7;
    while (Flag > 1)
    {
        Flag = Flag - 1;
        VectorXd w=VectorXd::Zero(length);
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                w(i) = w(i) + A(i, j) * v(j);
            }
        }
        int indx = 0;

        VectorXd maxx = MaxVec(w);

        indx = (int)maxx(1);
        lambda = w(indx);
        for (int i = 0; i < length; i++)
        {
            v(i) = w(i) / lambda;
        }
    }
    double I = 0;
    for (int i = 0; i < length; i++)
    {
        I = I + v(i) * v(i);
    }
    I = sqrt(I);
    VectorXd E_lambda=VectorXd::Zero(length + 1);
    E_lambda(0) = lambda;
    for (int i = 1; i <= length; i++)
    {
        E_lambda(i) = v(i - 1) / I;
    }
    return E_lambda;
}
