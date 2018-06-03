//
// Created by Javier Peralta on 6/2/18.
//

#include "LUSolver.hpp"
#include <cmath>
vect lowerSol(matrix a , vect b){
  vect sol(b);
  auto nr = b.size(), nc = a[0].size();
  for (unsigned i = 0; i < nr; ++i) {
    double tmp = b[i];
    for (unsigned j = 0; j < i && j < nc; ++j) {
      tmp -= sol[j] * a[i][j];
    }
    tmp /= a[i][i];
    sol[i] = tmp;
  }
  return sol;
}
vect upperSol(matrix a , vect b){
  vect sol(b);
  auto nr = b.size(), nc = a[0].size();
  for (int i = (int) nr -1; i >= 0; i--) {
    double tmp = b[i];
    for (auto j = i+1; j < nc; ++j) {
      tmp -= sol[j] * a[i][j];
    }
    tmp /= a[i][i];
    sol[i] = tmp;
  }
  return sol;
}
bool luFactor(matrix& a, matrix& l, matrix& u){
  auto nr = a.size(), nc = a[0].size();
  for (int i = 0; i < nr; ++i) {
    u[i][i] = 1;
    for (int j = 0; j <= i && j <nc; ++j) {
      double lij = a[i][j];
      for (int k = 0; k < j; ++k) {
        lij -= l[i][k]*u[k][j];
      }
      l[i][j] = lij;
    }
    for (int j = i+1; j < nc; ++j) {
      double lij = a[i][j];
      if(fabs(l[i][i]) < 1E-4)
        return false;
      for (int k = 0; k < i; ++k) {
        lij -= l[i][k]*u[k][j];
      }
      lij /= l[i][i];
      u[i][j] = lij;
    }
  }
  return true;
}
vect luSolver(matrix &A, vect b){
  matrix l(A), u(A);
  luFactor(A, l, u);
  vect sol = lowerSol(l, b);
  sol = upperSol(u, sol);
  return sol;
}