//
// Created by Javier Peralta on 5/31/18.
//

#ifndef SVM_DIFFERENTIALEVOLUTION_HPP
#define SVM_DIFFERENTIALEVOLUTION_HPP

#include "../Data.hpp"
#include "../OptimizationProblem.hpp"

class DifferentialEvolution {
public:
  friend class Individual;
  class Individual;
private:
  unsigned max_evals;
  unsigned num_vars;

  double __cr, __F;
  OptimizationProblem *__problem;
  bool minimize;
  std::vector<Individual> population;
  std::vector<int> get_parent_idx();
public:
  DifferentialEvolution(std::vector<Individual> &pop, unsigned max_evals, double cr, double F, OptimizationProblem *problem, ProblemType type = ProblemType::MINIMIZE);
  Individual getBest();
  bool iterate();
};

class DifferentialEvolution::Individual{
  friend class DifferentialEvolution;
protected:
  vect data;
  double value;
public:
  vect get_data();
  double get_value();
  void set_value(double val);
  explicit Individual(vect &dat);
  Individual(vect &dat, double val);
};

#endif //SVM_DIFFERENTIALEVOLUTION_HPP
