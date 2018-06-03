//
// Created by Javier Peralta on 5/30/18.
//

#ifndef SVM_OMP_HPP
#define SVM_OMP_HPP

#include "Data.hpp"
#include "OptimizationProblem.hpp"

class OMP {
  Data dat;
  vect u;
  vect r;
  unsigned t;
  std::vector<unsigned> I;
  std::vector<unsigned> L;
  void updateResidual();
  void getLambda();
  void updateU();
  friend class OMP_LS;
  class OMP_LS;
public:
  OMP(Data &dat, unsigned s);
  bool iterate(double threshold);
  int predict(vect& x);
  void printHyper();
};

class OMP::OMP_LS : public LeastSquaresProblem {
  OMP *parent;
  double h=0.01;
public:
  OMP_LS(OMP *parent);
  vect evaluateFunction (vect& vals) override;
  matrix evaluateJacobian(vect& vals) override ;
};

#endif //SVM_OMP_HPP
