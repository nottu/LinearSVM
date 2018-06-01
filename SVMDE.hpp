//
// Created by Javier Peralta on 5/31/18.
//

#ifndef SVM_SVMDE_HPP
#define SVM_SVMDE_HPP

#include "Data.hpp"
#include "DifferentialEvolution/DifferentialEvolution.hpp"
#include "OptimizationProblem.hpp"

class SVMDE {
public:
  friend class SVMDE_Problem;
  class SVMDE_Problem;
private:
  unsigned n_pop, max_evals, num_vars, num_instances;
  Data dat;
  DifferentialEvolution::Individual generateIndividual(SVMDE_Problem &problem);
public:
  SVMDE(Data &d, unsigned n_pop=30, unsigned max_evals=15000);
  vect getHyper();
};

class SVMDE::SVMDE_Problem : public OptimizationProblem {
  unsigned dim;
  unsigned sz;
  double c;
  double mu;
  Data dat;
public:
  SVMDE_Problem(Data &d, double cte);

  double evaluateFunction(vect& vals) override;
};

#endif //SVM_SVMDE_HPP
