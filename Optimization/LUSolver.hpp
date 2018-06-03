//
// Created by Javier Peralta on 6/2/18.
//

#ifndef SVM_LUSOLVER_HPP
#define SVM_LUSOLVER_HPP

#include "../Data.hpp"
vect lowerSol(matrix a , vect b);
vect upperSol(matrix a , vect b);

bool luFactor(matrix &A, matrix &l, matrix &u);
vect luSolver(matrix &A, vect b);
#endif //SVM_LUSOLVER_HPP
