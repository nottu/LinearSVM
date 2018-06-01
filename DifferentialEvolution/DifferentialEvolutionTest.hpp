//
// Created by Javier Peralta on 5/31/18.
//

#ifndef SVM_DIFFERENTIALEVOLUTIONTEST_HPP
#define SVM_DIFFERENTIALEVOLUTIONTEST_HPP

#include "DifferentialEvolution.hpp"
#include "../OptimizationProblem.hpp"

enum class Test {shpere};

class DifferentialEvolutionTest {
public:
  static void runTest(Test test, unsigned n_vars);
};

class TestProblem : public OptimizationProblem {
  int n_vars;
  Test test;
  double evaluateSphere(vect vals);
public:
  TestProblem(Test tst, int num_vars);
  double evaluateFunction(vect vals) override ;
};

#endif //SVM_DIFFERENTIALEVOLUTIONTEST_HPP
