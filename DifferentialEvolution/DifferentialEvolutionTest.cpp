
//
// Created by Javier Peralta on 5/31/18.
//

#include <vector>
#include <iostream>

#include "DifferentialEvolutionTest.hpp"
#include "DifferentialEvolution.hpp"

using namespace std;

void DifferentialEvolutionTest::runTest(Test test, unsigned n_vars){
  TestProblem problem(test, n_vars);
  unsigned n_pop = 30;
  double min = -20, max = 20;
  vector<DifferentialEvolution::Individual> pop; pop.reserve(n_pop);
  for (int i = 0; i < n_pop; ++i) {
    vect data; data.reserve(n_vars);
    for (int j = 0; j < n_vars; ++j) {
      auto number = ((double)rand()/(double)RAND_MAX)* (max - min) + min;
      data.emplace_back(number);
    }
    double eval = problem.evaluateFunction(data);
    DifferentialEvolution::Individual indi(data, eval);
    pop.emplace_back(indi);
  }
  DifferentialEvolution de(pop, 150 * 1000, 0.5, 0.75, &problem, ProblemType::MINIMIZE);
  while(de.iterate());
  DifferentialEvolution::Individual best = de.getBest();
  cout << "best " << best.get_value();
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