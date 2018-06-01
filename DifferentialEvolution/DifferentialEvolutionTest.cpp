
//
// Created by Javier Peralta on 5/31/18.
//

#include <vector>

#include "DifferentialEvolutionTest.hpp"
#include "DifferentialEvolution.hpp"

using namespace std;

void DifferentialEvolutionTest::runTest(Test test, unsigned n_vars){
  TestProblem problem(test, n_vars);
  unsigned n_pop = 30;
  double min = -20, max = 20;
  vector<DifferentialEvolution::Individual> data;
  data.reserve(n_pop);
  for (int i = 0; i < n_vars; ++i) {
    auto number = ((double)rand()/(double)RAND_MAX)* (max - min) + min;
    data.emplace_back(number);
  }
}
double TestProblem::evaluateSphere(vect vals){
  double val = 0;
  for (auto& var: vals){
    val += var * var;
  }
  return val;
}
TestProblem::TestProblem(Test tst, int num_vars){}
double TestProblem::evaluateFunction(vect vals){
  switch (test){
    case Test::shpere:
      return evaluateSphere(vals);
  }
}