//
// Created by Javier Peralta on 5/31/18.
//

#ifndef SVM_OPTIMIZATIONPROBLEM_HPP
#define SVM_OPTIMIZATIONPROBLEM_HPP

#include "Data.hpp"

enum class ProblemType{MINIMIZE, MAXIMIZE};

class OptimizationProblem {
public:
  virtual double evaluateFunction(vect vals) = 0;
};


#endif //SVM_OPTIMIZATIONPROBLEM_HPP
