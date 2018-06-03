//
// Created by Javier Peralta on 6/2/18.
//
#include "LevenbergMarquardt.hpp"
#include "LUSolver.hpp"

vect levenbergMarquardt(vect& x_0, LeastSquaresProblem &ls, unsigned max_iter, double toler, double v){
  vect x1(x_0), xn;
  auto n = (unsigned) x1.size();
  vect r    = ls.evaluateFunction(x1);
  matrix J  = ls.evaluateJacobian(x1);
  matrix JJ = Matrix::transposedMultiply(J, J);
  double l = 0;
  for (int i = 0; i < n; ++i) l = MAX(l, JJ[i][i]);
  matrix lI = Matrix::getIdentity(n);

  vect g = Matrix::multiplyTransposed_vector(J, r);
  int i = 0;
  double norm = Vector::norm2(g);
  while(norm > toler && i < max_iter){
    for (int j = 0; j < n; ++j) lI[j][j] = l;
    JJ = Matrix::addMatrix(JJ, lI);
    Vector::scale(g, -1);
    vect p = luSolver(JJ, g);
    double fx = Vector::dotProduct(r, r); //should divide by 2
    xn = Vector::add(x1, p);// xn = x1 + p
    r = ls.evaluateFunction(xn);
    double fxn = Vector::dotProduct(r, r); //should divide by 2
    if(fxn <= fx){
      x1 = xn;
      l /= v;
      J  = ls.evaluateJacobian(x1);
      JJ = Matrix::transposedMultiply(J, J);// recalculate JJ
      g = Matrix::multiplyTransposed_vector(J, r);//recalc g
      norm = Vector::norm2(g);
    } else {
      l *= v;
      r = ls.evaluateFunction(x1); //reset r
      Vector::scale(g, -1); //reset g
    }
    i++;
  }
  if (i >= max_iter){
    printf("exit by max iter!!!\t norm %g\n", norm);
  }
  return x1;
}