//
// Created by Javier Peralta on 5/31/18.
//

#include "SVMDE.hpp"

#include <vector>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define HINGE(x) MAX(x, 0)

using namespace std;

//Sabemos que beta es una combinación lineal de los vectores de soporte, inicializamos cada individuo con
// valores de x_i aleatorios, uno para y_i = -1 y otro con y_i = 1
DifferentialEvolution::Individual SVMDE::generateIndividual(SVMDE_Problem &problem){
  vect betas;
  betas.reserve(num_vars);
  auto alp = 0.5; //( (double) rand()) / ((double) RAND_MAX);
  unsigned idx = rand() % num_instances;
  for(auto &v : dat.x[idx]) betas.push_back(v * alp);
  int cat = dat.y[idx];
  do {
    idx = rand() % num_instances;
  } while(dat.y[idx] == cat);
  for(int i = 0; i < num_vars; ++i) betas[i] += (dat.x[idx][i] * (1 - alp));
  int beta0 = 10 - rand() % 20;
  betas.push_back(beta0);
  auto fit = problem.evaluateFunction(betas);
  return DifferentialEvolution::Individual(betas, fit);
}

SVMDE::SVMDE(Data &d, unsigned n, unsigned ev) : dat(d), n_pop(n), max_evals(ev) {
  num_instances = (unsigned) d.x.size();
  num_vars = 1 + (unsigned) d.x.at(0).size();
}
vect SVMDE::getHyper() {
  SVMDE_Problem problem(dat, 1);
  vector<DifferentialEvolution::Individual> pop;
  for (int i = 0; i < n_pop; ++i) {
    auto indi = generateIndividual(problem);
    pop.emplace_back(indi);
  }
  DifferentialEvolution de(pop, max_evals, 0.5, 0.75, &problem, ProblemType::MINIMIZE);
  while(de.iterate());
  auto best = de.getBest();
  return best.get_data();
}

SVMDE::SVMDE_Problem::SVMDE_Problem(Data &d, double cte) : dat(d) ,c(cte) {
  dim = (unsigned) d.x[0].size();
  sz  = (unsigned) d.x.size();
}

double SVMDE::SVMDE_Problem::evaluateFunction(vect& vals){
  vect betas(vals.begin(), vals.begin() + dim);
  double alpha = vals[dim];
  double val = c * Vector::norm2(betas);
  for (int i = 0; i < sz; ++i) {
    double classif = Vector::dotProduct(betas, dat.x[i]) + alpha;
    double errClas = HINGE(1 - dat.y[i]*classif);
    val += errClas;
  }
  return val;
}