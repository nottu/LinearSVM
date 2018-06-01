//
// Created by Javier Peralta on 5/31/18.
//

#ifndef SVM_SVMDE_HPP
#define SVM_SVMDE_HPP

#include "Data.hpp"
#include "OptimizationProblem.hpp"

class SVMDE {
public:
  friend class SVMDE_Problem;
  class SVMDE_Problem;
  Data dat;
public:
  explicit SVMDE(Data &d);
};

class SVMDE::SVMDE_Problem : OptimizationProblem {
  unsigned dim;
  unsigned sz;
  double c;
  double mu;
  Data dat;
public:
  SVMDE_Problem(Data &d, double m, double cte);

  double evaluateFunction(vect& vals);
  double get_mu();
  void set_mu(double m);

  double fitnessValue(vect& vals, vect& errors);
  vect restrictions(vect& vals, double beta0, vect& errors);
};

#endif //SVM_SVMDE_HPP
