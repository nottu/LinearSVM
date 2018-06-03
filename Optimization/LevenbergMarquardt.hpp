//
// Created by Javier Peralta on 6/2/18.
//

#ifndef SVM_LEVENBERGMARQUARDT_HPP
#define SVM_LEVENBERGMARQUARDT_HPP

#define SQUARE(x) ((x)*(x))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include "../OptimizationProblem.hpp"

vect levenbergMarquardt(vect& x_0, LeastSquaresProblem &ls, unsigned max_iter, double toler, double v);

#endif //SVM_LEVENBERGMARQUARDT_HPP
